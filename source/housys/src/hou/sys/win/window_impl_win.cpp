// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/window_impl.hpp"

#include "hou/sys/image.hpp"
#include "hou/sys/keyboard.hpp"
#include "hou/sys/mouse.hpp"
#include "hou/sys/video_mode.hpp"
#include "hou/sys/win/win_error.hpp"

#include "hou/cor/assertions.hpp"

#include "hou/mth/rectangle.hpp"
#include "hou/sys/window_style.hpp"

#include <mutex>
#include <tchar.h>



// Extra macros to extract information from windows messages.
#define GET_REPEAT_COUNT_LPARAM(lp) ((UINT)((lp)&0xffff))
#define GET_SCAN_CODE_LPARAM(lp) ((UINT)(((lp) >> 16) & 0x00ff))
#define GET_EXTENDED_KEY_LPARAM(lp) ((BOOL)(((lp) & (1 << 24)) != 0))
#define GET_ALT_KEY_PRESSED_LPARAM(lp) ((BOOL)(((lp) & (1 << 29)) != 0))
#define GET_KEY_PREVIOUSLY_DOWN_LPARAM(lp) ((BOOL)(((lp) & (1 << 30)) != 0))
#define GET_KEY_PRESSED_LPARAM(lp) ((BOOL)(((lp) & (1 << 31)) == 0))



namespace hou
{

namespace prv
{

namespace
{

constexpr uint bits_per_byte = 8u;



constexpr const wchar_t* hou_wnd_class_name = L"HziWindowClass";

std::mutex hou_wnd_class_mutex;

uint window_count(0);



std::mutex fullscreen_mutex;

window_impl* fullscreen_window(nullptr);



DWORD window_style_to_win_window_style(window_style style);

DWORD window_style_to_win_window_style_ex(window_style style);



void activate_fullscreen_mode(window_impl& wnd, const video_mode& vm);

void deactivate_fullscreen_mode();

bool is_fullscreen_window(const window_impl& wnd);



recti client_to_frame_rect(HWND hwnd, const recti& rect);



void set_window_icon(HWND hwnd, HICON hicon);

HICON create_custom_icon(const image2_rgba& icon);

HICON get_system_icon();



key_code win_key_to_key_code(UINT key);

key_code get_key_code_wparam(WPARAM wparam);

scan_code get_scan_code_lparam(LPARAM lparam);



DWORD window_style_to_win_window_style(window_style style)
{
  switch(style)
  {
    case window_style::windowed:
      return WS_POPUP | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
    case window_style::windowed_resizable:
      return WS_POPUP | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU
        | WS_MAXIMIZEBOX | WS_SIZEBOX;
    case window_style::fullscreen:
      return WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
    default:
      HOU_UNREACHABLE();
      return 0;
  }
}



DWORD window_style_to_win_window_style_ex(window_style style)
{
  switch(style)
  {
    case window_style::windowed:
      return 0;
    case window_style::windowed_resizable:
      return 0;
    case window_style::fullscreen:
      return WS_EX_APPWINDOW;
    default:
      HOU_UNREACHABLE();
      return 0;
  }
}



void activate_fullscreen_mode(window_impl& wnd, const video_mode& vm)
{
  std::lock_guard<std::mutex> lock(fullscreen_mutex);

  HOU_DEV_ASSERT(fullscreen_window == nullptr);

  DEVMODE devmode;
  devmode.dmSize = sizeof(DEVMODE);
  devmode.dmPelsWidth = vm.get_resolution().x();
  devmode.dmPelsHeight = vm.get_resolution().y();
  devmode.dmBitsPerPel = vm.get_bytes_per_pixel() * bits_per_byte;
  devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
  HOU_WIN_CHECK(
    ChangeDisplaySettings(&devmode, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL);

  fullscreen_window = &wnd;
}



void deactivate_fullscreen_mode()
{
  std::lock_guard<std::mutex> lock(fullscreen_mutex);

  HOU_DEV_ASSERT(fullscreen_window != nullptr);

  HOU_WIN_CHECK(ChangeDisplaySettings(nullptr, 0) == DISP_CHANGE_SUCCESSFUL);
  fullscreen_window = nullptr;
}



bool is_fullscreen_window(const window_impl& wnd)
{
  std::lock_guard<std::mutex> lock(fullscreen_mutex);
  return (&wnd == fullscreen_window);
}



recti client_to_frame_rect(HWND hwnd, const recti& rect)
{
  RECT win_rect = {rect.l(), rect.t(), rect.r(), rect.b()};
  HOU_WIN_CHECK(
    AdjustWindowRect(&win_rect, GetWindowLong(hwnd, GWL_STYLE), false) != 0);
  return recti(win_rect.left, win_rect.top, win_rect.right - win_rect.left,
    win_rect.bottom - win_rect.top);
}



void set_window_icon(HWND hwnd, HICON hicon)
{
  // No possible failure.
  SendMessageW(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hicon));
  SendMessageW(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hicon));
}



HICON create_custom_icon(const image2_rgba& icon)
{
  static constexpr size_t bytes_per_pixel = 4u;

  // Swap red and blue channels for Windows.
  std::vector<uint8_t> invPixels(
    icon.get_pixels().size() * icon.get_pixel_byte_count());

  for(size_t i = 0; i < icon.get_pixels().size(); ++i)
  {
    invPixels[i * bytes_per_pixel + 0] = icon.get_pixels()[i].get_b();
    invPixels[i * bytes_per_pixel + 1] = icon.get_pixels()[i].get_g();
    invPixels[i * bytes_per_pixel + 2] = icon.get_pixels()[i].get_r();
    invPixels[i * bytes_per_pixel + 3] = icon.get_pixels()[i].get_a();
  }

  HINSTANCE module = GetModuleHandle(nullptr);
  HOU_WIN_CHECK(module != nullptr);
  return CreateIcon(module, icon.get_size().x(), icon.get_size().y(),
    1 /*cplanes*/, 32 /*bbp*/, nullptr, invPixels.data());
}



HICON get_system_icon()
{
  return LoadIcon(nullptr, IDI_APPLICATION);
}



key_code win_key_to_key_code(UINT key)
{
  switch(key)
  {
    case VK_ESCAPE:
      return key_code::escape;

    case VK_PRINT:
      return key_code::print;
    case VK_SNAPSHOT:
      return key_code::print_screen;
    case VK_PAUSE:
      return key_code::pause;
    case VK_EXECUTE:
      return key_code::execute;
    case VK_SELECT:
      return key_code::select;
    case VK_HELP:
      return key_code::help;
    case VK_SLEEP:
      return key_code::sleep;
    case VK_APPS:
      return key_code::apps;
    case VK_LWIN:
      return key_code::l_system;
    case VK_RWIN:
      return key_code::r_system;

    case VK_F1:
      return key_code::f1;
    case VK_F2:
      return key_code::f2;
    case VK_F3:
      return key_code::f3;
    case VK_F4:
      return key_code::f4;
    case VK_F5:
      return key_code::f5;
    case VK_F6:
      return key_code::f6;
    case VK_F7:
      return key_code::f7;
    case VK_F8:
      return key_code::f8;
    case VK_F9:
      return key_code::f9;
    case VK_F10:
      return key_code::f10;
    case VK_F11:
      return key_code::f11;
    case VK_F12:
      return key_code::f12;
    case VK_F13:
      return key_code::f13;
    case VK_F14:
      return key_code::f14;
    case VK_F15:
      return key_code::f15;
    case VK_F16:
      return key_code::f16;
    case VK_F17:
      return key_code::f17;
    case VK_F18:
      return key_code::f18;
    case VK_F19:
      return key_code::f19;
    case VK_F20:
      return key_code::f20;
    case VK_F21:
      return key_code::f21;
    case VK_F22:
      return key_code::f22;
    case VK_F23:
      return key_code::f23;
    case VK_F24:
      return key_code::f24;

    case VK_NUMPAD0:
      return key_code::numpad0;
    case VK_NUMPAD1:
      return key_code::numpad1;
    case VK_NUMPAD2:
      return key_code::numpad2;
    case VK_NUMPAD3:
      return key_code::numpad3;
    case VK_NUMPAD4:
      return key_code::numpad4;
    case VK_NUMPAD5:
      return key_code::numpad5;
    case VK_NUMPAD6:
      return key_code::numpad6;
    case VK_NUMPAD7:
      return key_code::numpad7;
    case VK_NUMPAD8:
      return key_code::numpad8;
    case VK_NUMPAD9:
      return key_code::numpad9;

    case VK_ADD:
      return key_code::add;
    case VK_SUBTRACT:
      return key_code::subtract;
    case VK_MULTIPLY:
      return key_code::multiply;
    case VK_DIVIDE:
      return key_code::divide;
    case VK_DECIMAL:
      return key_code::decimal;
    case VK_SEPARATOR:
      return key_code::separator;

    case VK_PRIOR:
      return key_code::page_up;
    case VK_NEXT:
      return key_code::page_down;
    case VK_END:
      return key_code::end;
    case VK_HOME:
      return key_code::home;
    case VK_INSERT:
      return key_code::ins;
    case VK_DELETE:
      return key_code::del;
    case VK_BACK:
      return key_code::backspace;

    case VK_LEFT:
      return key_code::left;
    case VK_RIGHT:
      return key_code::right;
    case VK_UP:
      return key_code::up;
    case VK_DOWN:
      return key_code::down;

    case '0':
      return key_code::num0;
    case '1':
      return key_code::num1;
    case '2':
      return key_code::num2;
    case '3':
      return key_code::num3;
    case '4':
      return key_code::num4;
    case '5':
      return key_code::num5;
    case '6':
      return key_code::num6;
    case '7':
      return key_code::num7;
    case '8':
      return key_code::num8;
    case '9':
      return key_code::num9;

    case 'A':
      return key_code::a;
    case 'B':
      return key_code::b;
    case 'C':
      return key_code::c;
    case 'D':
      return key_code::d;
    case 'E':
      return key_code::e;
    case 'F':
      return key_code::f;
    case 'G':
      return key_code::g;
    case 'H':
      return key_code::h;
    case 'I':
      return key_code::i;
    case 'J':
      return key_code::j;
    case 'K':
      return key_code::k;
    case 'L':
      return key_code::l;
    case 'M':
      return key_code::m;
    case 'N':
      return key_code::n;
    case 'O':
      return key_code::o;
    case 'P':
      return key_code::p;
    case 'Q':
      return key_code::q;
    case 'R':
      return key_code::r;
    case 'S':
      return key_code::s;
    case 'T':
      return key_code::t;
    case 'U':
      return key_code::u;
    case 'V':
      return key_code::v;
    case 'X':
      return key_code::x;
    case 'Y':
      return key_code::y;
    case 'W':
      return key_code::w;
    case 'Z':
      return key_code::z;

    case VK_OEM_1:
      return key_code::semicolon;
    case VK_OEM_2:
      return key_code::slash;
    case VK_OEM_3:
      return key_code::tilde;
    case VK_OEM_4:
      return key_code::l_bracket;
    case VK_OEM_5:
      return key_code::backslash;
    case VK_OEM_6:
      return key_code::r_bracket;
    case VK_OEM_7:
      return key_code::quote;
    case VK_OEM_8:
      return key_code::special1;
    case VK_OEM_102:
      return key_code::special2;
    case VK_OEM_COMMA:
      return key_code::comma;
    case VK_OEM_PERIOD:
      return key_code::period;
    case VK_OEM_PLUS:
      return key_code::equal;
    case VK_OEM_MINUS:
      return key_code::dash;
    case VK_SPACE:
      return key_code::space;
    case VK_RETURN:
      return key_code::enter;
    case VK_TAB:
      return key_code::tab;

    case VK_CAPITAL:
      return key_code::caps_lock;
    case VK_NUMLOCK:
      return key_code::num_lock;
    case VK_SCROLL:
      return key_code::scroll_lock;

    case VK_CONTROL:
      return key_code::l_ctrl;
    case VK_LCONTROL:
      return key_code::l_ctrl;
    case VK_RCONTROL:
      return key_code::r_ctrl;
    case VK_MENU:
      return key_code::l_alt;
    case VK_LMENU:
      return key_code::l_alt;
    case VK_RMENU:
      return key_code::r_alt;
    case VK_SHIFT:
      return key_code::l_shift;
    case VK_LSHIFT:
      return key_code::l_shift;
    case VK_RSHIFT:
      return key_code::r_shift;

    case VK_JUNJA:
      return key_code::junja;
    case VK_FINAL:
      return key_code::final;
    case VK_HANJA:
      return key_code::hanja;
    case VK_CONVERT:
      return key_code::convert;
    case VK_NONCONVERT:
      return key_code::non_convert;
    case VK_ACCEPT:
      return key_code::accept;
    case VK_MODECHANGE:
      return key_code::mode_change;
    case VK_PROCESSKEY:
      return key_code::process_key;

    case VK_BROWSER_BACK:
      return key_code::browser_back;
    case VK_BROWSER_FORWARD:
      return key_code::browser_forward;
    case VK_BROWSER_REFRESH:
      return key_code::browser_refresh;
    case VK_BROWSER_STOP:
      return key_code::browser_stop;
    case VK_BROWSER_SEARCH:
      return key_code::browser_search;
    case VK_BROWSER_FAVORITES:
      return key_code::browser_favorites;
    case VK_BROWSER_HOME:
      return key_code::browser_home;

    case VK_VOLUME_UP:
      return key_code::volume_up;
    case VK_VOLUME_DOWN:
      return key_code::volume_down;
    case VK_VOLUME_MUTE:
      return key_code::volume_mute;

    case VK_MEDIA_NEXT_TRACK:
      return key_code::media_next_track;
    case VK_MEDIA_PREV_TRACK:
      return key_code::media_previous_track;
    case VK_MEDIA_STOP:
      return key_code::media_stop;
    case VK_MEDIA_PLAY_PAUSE:
      return key_code::media_play_pause;
    case VK_LAUNCH_MEDIA_SELECT:
      return key_code::launch_media_select;
    case VK_LAUNCH_MAIL:
      return key_code::launch_mail;
    case VK_LAUNCH_APP1:
      return key_code::launch_app1;
    case VK_LAUNCH_APP2:
      return key_code::launch_app2;

    case VK_ATTN:
      return key_code::attn;
    case VK_CRSEL:
      return key_code::cr_sel;
    case VK_EXSEL:
      return key_code::ex_sel;
    case VK_EREOF:
      return key_code::erase_eof;
    case VK_PLAY:
      return key_code::play;
    case VK_ZOOM:
      return key_code::zoom;
    case VK_PA1:
      return key_code::pa1;
    case VK_CLEAR:
      return key_code::clear;
    case VK_PACKET:
      return key_code::packet;

    default:
      HOU_UNREACHABLE();
      return key_code::enter;
  }
}



key_code get_key_code_wparam(WPARAM wparam)
{
  return win_key_to_key_code(static_cast<UINT>(wparam));
}



scan_code get_scan_code_lparam(LPARAM lparam)
{
  UINT sc = GET_SCAN_CODE_LPARAM(lparam);
  if(GET_EXTENDED_KEY_LPARAM(lparam))
  {
    sc += 0xe000;
  }
  return scan_code(sc);
}

}  // namespace



window_impl::window_impl(
  const std::string& title, const video_mode& vm, window_style style)
  : non_copyable()
  , m_handle(nullptr)
  , m_cursor_grabbed(false)
  , m_key_repeat_enabled(false)
  , m_event_queue()
  , m_hdc(nullptr)
  , m_cursor_handle(nullptr)
  , m_icon_handle(nullptr)
  , m_cached_utf16_char(0)
  , m_mouse_in_window(false)
  , m_previous_size(vm.get_resolution())
{
  HOU_PRECOND(style != window_style::fullscreen
    || (vm.is_fullscreen_mode() && fullscreen_window == nullptr));

  register_window_class();

  // Create the window.
  // clang-format off
  m_handle = CreateWindowExW(
      window_style_to_win_window_style_ex(style),   // dwExStyle
      hou_wnd_class_name,                           // lpClassName
      convert_encoding<wide, utf8>(title).c_str(),  // lpWindowName
      window_style_to_win_window_style(style),      // dwStyle
      0, 0,                                         // Position
      0, 0,                                         // size_type
      nullptr,                                      // hWndParent
      nullptr,                                      // hMenu
      GetModuleHandle(nullptr),                     // hInstance
      nullptr);                                     // lpParam
  // clang-format on
  HOU_WIN_CHECK(m_handle != nullptr);

  // Set client size. CreateWindowEx sets frame position and size, but we want
  // the arguments passed to the constructor to refer to client position and
  // size.
  vec2i position = (style == window_style::fullscreen)
    ? vec2i(0, 0)
    : vec2i(
        video_mode::get_desktop_mode().get_resolution() - vm.get_resolution())
      / 2;
  set_client_rect(recti(position, vm.get_resolution()));

  // Set a pointer to the window class in the window user data (used in
  // the window procedure).
  SetLastError(0);
  SetWindowLongPtrW(m_handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
  HOU_WIN_CHECK(GetLastError() == 0);

  // Initialize handle to device context.
  m_hdc = GetDC(m_handle);
  HOU_WIN_CHECK(m_hdc != nullptr);

  // Activate fullscreen mode if necessary.
  if(style == window_style::fullscreen)
  {
    activate_fullscreen_mode(*this, vm);
  }

  // Check if the mouse is inside the client area. If yes, also capture the
  // cursor (this is necessary to correctly generate events related to mouse
  // movement).
  m_mouse_in_window
    = is_point_in_rectangle(get_client_rect(), mouse::get_position());
  set_mouse_captured(m_mouse_in_window);
}



window_impl::window_impl(window_impl&& other)
  : non_copyable()
  , m_handle(std::move(other.m_handle))
  , m_cursor_grabbed(std::move(other.m_cursor_grabbed))
  , m_key_repeat_enabled(std::move(other.m_key_repeat_enabled))
  , m_event_queue(std::move(other.m_event_queue))
  , m_hdc(std::move(other.m_hdc))
  , m_cursor_handle(std::move(other.m_cursor_handle))
  , m_icon_handle(std::move(other.m_icon_handle))
  , m_cached_utf16_char(std::move(other.m_cached_utf16_char))
  , m_mouse_in_window(std::move(other.m_mouse_in_window))
{
  {
    std::lock_guard<std::mutex> lock(fullscreen_mutex);
    if(fullscreen_window == &other)
    {
      fullscreen_window = this;
    }
  }

  // Update pointer to the window class in the window user data.
  SetLastError(0);
  SetWindowLongPtrW(m_handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
  HOU_WIN_CHECK(GetLastError() == 0);

  other.m_handle = nullptr;
  other.m_hdc = nullptr;
  other.m_cursor_handle = nullptr;
  other.m_icon_handle = nullptr;
}



window_impl::~window_impl()
{
  HOU_DISABLE_EXCEPTIONS_BEGIN
  destroy_icon();
  destroy_cursor();
  destroy_window();
  HOU_DISABLE_EXCEPTIONS_END
}



recti window_impl::get_frame_rect() const
{
  RECT rect = {0, 0, 0, 0};
  HOU_WIN_CHECK(GetWindowRect(m_handle, &rect) != 0);
  return recti(
    rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
}



void window_impl::set_frame_rect(const recti& value)
{
  HOU_WIN_CHECK(SetWindowPos(m_handle, nullptr, value.x(), value.y(), value.w(),
                  value.h(), SWP_NOZORDER)
    != 0);
  if(m_cursor_grabbed)
  {
    grab_mouse_cursor();
  }
}



recti window_impl::get_client_rect() const
{
  // Note returned x and y are always 0 with GetClientRect.
  RECT rect = {0, 0, 0, 0};
  HOU_WIN_CHECK(GetClientRect(m_handle, &rect) != 0);

  POINT origin = {0, 0};
  HOU_WIN_CHECK(ClientToScreen(m_handle, &origin) != 0);

  return recti(origin.x, origin.y, rect.right, rect.bottom);
}



void window_impl::set_client_rect(const recti& value)
{
  set_frame_rect(client_to_frame_rect(m_handle, value));
}



void window_impl::set_title(const std::string& title)
{
  HOU_WIN_CHECK(
    SetWindowTextW(m_handle, convert_encoding<wide, utf8>(title).c_str()) != 0);
}



bool window_impl::is_visible() const noexcept
{
  return IsWindowVisible(m_handle);
}



void window_impl::set_visible(bool value)
{
  // No possible failure.
  ShowWindow(m_handle, value ? SW_SHOW : SW_HIDE);
  if(value)
  {
    HOU_WIN_CHECK(UpdateWindow(m_handle) != 0);
  }
}



void window_impl::set_icon(const image2_rgba& icon)
{
  destroy_icon();
  m_icon_handle = create_custom_icon(icon);
  HOU_WIN_CHECK(m_icon_handle != nullptr);
  set_window_icon(m_handle, m_icon_handle);
}



void window_impl::set_system_icon()
{
  destroy_icon();
  m_icon_handle = nullptr;
  HICON iconHandle = get_system_icon();
  HOU_WIN_CHECK(iconHandle != nullptr);
  set_window_icon(m_handle, iconHandle);
}



void window_impl::grab_mouse_cursor()
{
  RECT rect;
  HOU_WIN_CHECK(GetClientRect(m_handle, &rect) != 0);

  SetLastError(0);
  MapWindowPoints(m_handle, nullptr, reinterpret_cast<LPPOINT>(&rect), 2);
  HOU_WIN_CHECK(GetLastError() == 0);

  HOU_WIN_CHECK(ClipCursor(&rect) != 0);
}



void window_impl::ungrab_mouse_cursor()
{
  HOU_WIN_CHECK(ClipCursor(nullptr) != 0);
}



bool window_impl::is_mouse_captured() const
{
  return GetCapture() == m_handle;
}



void window_impl::set_mouse_captured(bool value)
{
  if(is_mouse_captured() != value)
  {
    if(value)
    {
      SetCapture(m_handle);
    }
    else
    {
      BOOL success = ReleaseCapture();
      HOU_WIN_CHECK(success != 0);
    }
  }
}



bool window_impl::has_focus() const noexcept
{
  return GetFocus() == m_handle;
}



bool window_impl::request_focus() const noexcept
{
  // Allow focus stealing only within the current process.
  // Cannot fail.
  DWORD thisPid = GetWindowThreadProcessId(m_handle, nullptr);
  DWORD foregroundPid
    = GetWindowThreadProcessId(GetForegroundWindow(), nullptr);

  if(thisPid == foregroundPid)
  {
    BOOL success = SetForegroundWindow(m_handle);
    return success != 0;
  }
  else
  {
    // Flash if not allowed to steal focus.
    FLASHWINFO info;
    info.cbSize = sizeof(FLASHWINFO);
    info.hwnd = m_handle;
    info.dwFlags = FLASHW_TRAY;
    info.dwTimeout = 0;
    info.uCount = 3;
    FlashWindowEx(&info);
    return false;
  }
}



void window_impl::update_event_queue()
{
  MSG msg;
  // Cannot fail.
  while(PeekMessageW(&msg, m_handle, 0, 0, PM_REMOVE))
  {
    // Cannot fail.
    TranslateMessage(&msg);
    // Cannot fail.
    DispatchMessage(&msg);
  }
}



void window_impl::swap_buffers()
{
  HOU_WIN_CHECK(SwapBuffers(m_hdc) != 0);
}



void window_impl::register_window_class()
{
  std::lock_guard<std::mutex> lock(hou_wnd_class_mutex);
  if(window_count == 0)
  {
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = &hou::prv::window_impl::wnd_procedure;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = hou_wnd_class_name;
    wcex.hIconSm = nullptr;

    HOU_WIN_CHECK(RegisterClassExW(&wcex) != 0);
  }
  ++window_count;
  HOU_DEV_ASSERT(window_count > 0);
}



void window_impl::unregister_window_class()
{
  std::lock_guard<std::mutex> lock(hou_wnd_class_mutex);
  HOU_DEV_ASSERT(window_count > 0);
  --window_count;
  if(window_count == 0)
  {
    HOU_WIN_CHECK(
      UnregisterClassW(hou_wnd_class_name, GetModuleHandle(nullptr)) != 0);
  }
}



LRESULT CALLBACK window_impl::wnd_procedure(
  HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
  window_impl* wnd = hwnd
    ? reinterpret_cast<window_impl*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA))
    : nullptr;

  if(wnd != nullptr)
  {
    wnd->filter_event(umsg, wparam, lparam);
  }

  // Do not forward close messages and sys command messages.
  if(umsg == WM_CLOSE || ((umsg == WM_SYSCOMMAND) && (wparam == SC_KEYMENU)))
  {
    return 0;
  }

  return DefWindowProcW(hwnd, umsg, wparam, lparam);
}



void window_impl::filter_event(UINT umsg, WPARAM wparam, LPARAM lparam)
{
  HOU_DEV_ASSERT(m_handle != nullptr);

  switch(umsg)
  {
    case WM_CLOSE:
    {
      push_event(window_event::closed());
      break;
    }

    case WM_SETFOCUS:
    {
      is_mouse_cursor_grabbed() ? grab_mouse_cursor() : ungrab_mouse_cursor();
      push_event(window_event::focus_gained());
      break;
    }

    case WM_KILLFOCUS:
    {
      m_previous_size = get_client_rect().get_size();
      ungrab_mouse_cursor();
      push_event(window_event::focus_lost());
      break;
    }

    case WM_ENTERSIZEMOVE:
    {
      ungrab_mouse_cursor();
      break;
    }

    case WM_EXITSIZEMOVE:
    {
      is_mouse_cursor_grabbed() ? grab_mouse_cursor() : ungrab_mouse_cursor();
      vec2u current_size = get_client_rect().get_size();
      if(current_size != m_previous_size)
      {
        push_event(window_event::resized(current_size.x(), current_size.y()));
      }
      break;
    }

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    {
      if(is_key_repeat_enabled() || !GET_KEY_PREVIOUSLY_DOWN_LPARAM(lparam))
      {
        push_event(window_event::key_pressed(get_key_code_wparam(wparam),
          get_scan_code_lparam(lparam), keyboard::get_modifier_keys_state()));
      }
      break;
    }

    case WM_KEYUP:
    case WM_SYSKEYUP:
    {
      push_event(window_event::key_released(get_key_code_wparam(wparam),
        get_scan_code_lparam(lparam), keyboard::get_modifier_keys_state()));
      break;
    }

    case WM_CHAR:
    {
      // Check if key repeat is enabled or if previous key state is up.
      if(is_key_repeat_enabled() || !GET_KEY_PREVIOUSLY_DOWN_LPARAM(lparam))
      {
        char32_t character = static_cast<char32_t>(wparam);
        // First code unit of surrogate pair.
        if((character >= 0xD800) && (character <= 0xD8FF))
        {
          m_cached_utf16_char = static_cast<char16_t>(character);
        }
        else
        {
          // Second code unit of surrogate pair.
          if((character >= 0xDC00) && (character <= 0xDFFF))
          {
            char16_t p_utf16[]
              = {m_cached_utf16_char, static_cast<char16_t>(character)};
            convert_encoding<utf32, utf16>(p_utf16, p_utf16 + 2, &character);
            m_cached_utf16_char = 0;
          }

          push_event(window_event::text_entered(character));
        }
      }
      break;
    }

    case WM_MOUSEMOVE:
    {
      // Windows mouseleave event seems unreliable, it does not always fires an
      // event when the mouse leaves the client. For this reason we check
      // manually. In order to do so, the mouse has to be captured, so that
      // mousemove events are generated when the mouse is outside of the client
      // area as well.

      vec2i pos(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));

      recti client_rect = get_client_rect();
      client_rect.set_position(vec2i());

      bool mouse_currently_in_window = is_point_in_rectangle(client_rect, pos);

      // Generate mouse move event only if the mouse is inside the client.
      if(mouse_currently_in_window)
      {
        push_event(window_event::mouse_moved(pos.x(), pos.y()));
      }

      if(!m_mouse_in_window && mouse_currently_in_window)
      {
        push_event(window_event::mouse_entered());
      }
      else if(m_mouse_in_window && !mouse_currently_in_window)
      {
        push_event(window_event::mouse_left());
      }

      m_mouse_in_window = mouse_currently_in_window;
      set_mouse_captured(mouse_currently_in_window);

      break;
    }

    case WM_LBUTTONDOWN:
    {
      push_event(window_event::mouse_button_pressed(
        mouse_button::lb, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
      break;
    }

    case WM_LBUTTONUP:
    {
      push_event(window_event::mouse_button_released(
        mouse_button::lb, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
      break;
    }

    case WM_RBUTTONDOWN:
    {
      push_event(window_event::mouse_button_pressed(
        mouse_button::rb, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
      break;
    }

    case WM_RBUTTONUP:
    {
      push_event(window_event::mouse_button_released(
        mouse_button::rb, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
      break;
    }

    case WM_MBUTTONDOWN:
    {
      push_event(window_event::mouse_button_pressed(
        mouse_button::mb, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
      break;
    }

    case WM_MBUTTONUP:
    {
      push_event(window_event::mouse_button_released(
        mouse_button::mb, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
      break;
    }

    case WM_XBUTTONDOWN:
    {
      push_event(window_event::mouse_button_pressed(
        GET_XBUTTON_WPARAM(wparam) == 1 ? mouse_button::xb1 : mouse_button::xb2,
        GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
      break;
    }

    case WM_XBUTTONUP:
    {
      push_event(window_event::mouse_button_released(
        GET_XBUTTON_WPARAM(wparam) == 1 ? mouse_button::xb1 : mouse_button::xb2,
        GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
      break;
    }

    case WM_MOUSEWHEEL:
    {
      static constexpr int wheel_increment = 120;
      push_event(window_event::mouse_wheel_moved(mouse_wheel::vertical,
        GET_WHEEL_DELTA_WPARAM(wparam) / wheel_increment, GET_X_LPARAM(lparam),
        GET_Y_LPARAM(lparam)));
      break;
    }

    case WM_MOUSEHWHEEL:
    {
      static constexpr int wheel_increment = 120;
      push_event(window_event::mouse_wheel_moved(mouse_wheel::horizontal,
        GET_WHEEL_DELTA_WPARAM(wparam) / wheel_increment, GET_X_LPARAM(lparam),
        GET_Y_LPARAM(lparam)));
      break;
    }
  }
}



void window_impl::destroy_icon()
{
  if(m_icon_handle != nullptr)
  {
    HOU_WIN_CHECK(DestroyIcon(m_icon_handle) != 0);
  }
}



void window_impl::destroy_cursor()
{
  if(m_cursor_handle != nullptr)
  {
    HOU_WIN_CHECK(DestroyCursor(m_cursor_handle) != 0);
  }
}



void window_impl::destroy_window()
{
  if(m_handle != nullptr)
  {
    if(is_fullscreen_window(*this))
    {
      deactivate_fullscreen_mode();
    }
    HOU_WIN_CHECK(DestroyWindow(m_handle) != 0);
    unregister_window_class();
  }
}

}  // namespace prv

}  // namespace hou
