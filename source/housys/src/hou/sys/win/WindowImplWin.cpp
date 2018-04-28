// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/WindowImpl.hpp"

#include "hou/sys/Image.hpp"
#include "hou/sys/Keyboard.hpp"
#include "hou/sys/Mouse.hpp"
#include "hou/sys/VideoMode.hpp"
#include "hou/sys/WindowEvent.hpp"
#include "hou/sys/win/WinError.hpp"

#include "hou/cor/Error.hpp"

#include "hou/mth/Rectangle.hpp"
#include "hou/sys/WindowStyle.hpp"

#include <mutex>
#include <tchar.h>



// Extra macros to extract information from windows messages.
#define GET_REPEAT_COUNT_LPARAM(lp) ((UINT)((lp) & 0xffff))
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

constexpr uint bitsPerByte = 8u;
constexpr const wchar_t* houClassName = L"HziWindowClass";
std::mutex houClassMutex;
uint windowCount(0);

std::mutex fullscreenMutex;
WindowImpl* fullscreenWindow(nullptr);



DWORD windowStyleToWinWindowStyle(WindowStyle style);
DWORD windowStyleToWinWindowStyleEx(WindowStyle style);

void activateFullscreenMode(WindowImpl& window, const VideoMode& videoMode);
void deactivateFullscreenMode();
bool isFullscreenWindow(const WindowImpl& window);

Recti clientToFrameRect(HWND hwnd, const Recti& rect);

void setWindowIcon(HWND hwnd, HICON hicon);
HICON createCustomIcon(const Image2RGBA& icon);
HICON getSystemIcon();

KeyCode winKeyToKeyCode(UINT key);
KeyCode getKeyCodeWParam(WPARAM wParam);
ScanCode getScanCodeLParam(LPARAM lParam);



DWORD windowStyleToWinWindowStyle(WindowStyle style)
{
  switch(style)
  {
    case WindowStyle::Windowed:
      return WS_POPUP | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
    case WindowStyle::WindowedResizable:
      return WS_POPUP | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU
        | WS_MAXIMIZEBOX | WS_SIZEBOX;
    case WindowStyle::Fullscreen:
      return WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
    default:
      return 0;
  }
}



DWORD windowStyleToWinWindowStyleEx(WindowStyle style)
{
  switch(style)
  {
    case WindowStyle::Windowed:
      return 0;
    case WindowStyle::WindowedResizable:
      return 0;
    case WindowStyle::Fullscreen:
      return WS_EX_APPWINDOW;
    default:
      return 0;
  }
}



void activateFullscreenMode(WindowImpl& window, const VideoMode& videoMode)
{
  std::lock_guard<std::mutex> lock(fullscreenMutex);

  HOU_EXPECT_DEV(fullscreenWindow == nullptr);

  DEVMODE devmode;
  devmode.dmSize = sizeof(DEVMODE);
  devmode.dmPelsWidth = videoMode.get_resolution().x();
  devmode.dmPelsHeight = videoMode.get_resolution().y();
  devmode.dmBitsPerPel = videoMode.getBytesPerPixel() * bitsPerByte;
  devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
  HOU_WIN_ENSURE(ChangeDisplaySettings(&devmode, CDS_FULLSCREEN)
    == DISP_CHANGE_SUCCESSFUL);

  fullscreenWindow = &window;
}



void deactivateFullscreenMode()
{
  std::lock_guard<std::mutex> lock(fullscreenMutex);

  HOU_EXPECT_DEV(fullscreenWindow != nullptr);

  HOU_WIN_ENSURE(ChangeDisplaySettings(nullptr, 0) == DISP_CHANGE_SUCCESSFUL);
  fullscreenWindow = nullptr;
}



bool isFullscreenWindow(const WindowImpl& window)
{
  std::lock_guard<std::mutex> lock(fullscreenMutex);
  return(&window == fullscreenWindow);
}



Recti clientToFrameRect(HWND hwnd, const Recti& rect)
{
  RECT winRect = {rect.l(), rect.t(), rect.r(), rect.b()};
  HOU_ENSURE(AdjustWindowRect(&winRect, GetWindowLong(hwnd, GWL_STYLE)
    , false)!= 0);
  return Recti(winRect.left, winRect.top, winRect.right - winRect.left
    , winRect.bottom - winRect.top);
}



void setWindowIcon(HWND hwnd, HICON hicon)
{
  // No possible failure.
  SendMessageW(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hicon));
  SendMessageW(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hicon));
}



HICON createCustomIcon(const Image2RGBA& icon)
{
  static constexpr size_t iconPixelByteCount = 4u;

  // Swap red and blue channels for Windows.
  std::vector<uint8_t> invPixels(icon.getPixels().size()
    * icon.getPixelByteCount());

  for(size_t i = 0; i < icon.getPixels().size(); ++i)
  {
    invPixels[i * iconPixelByteCount + 0] = icon.getPixels()[i].getB();
    invPixels[i * iconPixelByteCount + 1] = icon.getPixels()[i].getG();
    invPixels[i * iconPixelByteCount + 2] = icon.getPixels()[i].getR();
    invPixels[i * iconPixelByteCount + 3] = icon.getPixels()[i].getA();
  }

  HINSTANCE module = GetModuleHandle(nullptr);
  HOU_WIN_ENSURE(module != nullptr);
  return CreateIcon(module, icon.getSize().x(), icon.getSize().y()
    , 1 /*cplanes*/, 32 /*bbp*/, nullptr, invPixels.data());
}



HICON getSystemIcon()
{
  return LoadIcon(nullptr, IDI_APPLICATION);
}



KeyCode winKeyToKeyCode(UINT key)
{
  switch(key)
  {
    case VK_ESCAPE: return KeyCode::Escape;

    case VK_PRINT: return KeyCode::Print;
    case VK_SNAPSHOT: return KeyCode::PrintScreen;
    case VK_PAUSE: return KeyCode::Pause;
    case VK_EXECUTE: return KeyCode::Execute;
    case VK_SELECT: return KeyCode::Select;
    case VK_HELP: return KeyCode::Help;
    case VK_SLEEP: return KeyCode::Sleep;
    case VK_APPS: return KeyCode::Apps;
    case VK_LWIN: return KeyCode::LSystem;
    case VK_RWIN: return KeyCode::RSystem;

    case VK_F1: return KeyCode::F1;
    case VK_F2: return KeyCode::F2;
    case VK_F3: return KeyCode::F3;
    case VK_F4: return KeyCode::F4;
    case VK_F5: return KeyCode::F5;
    case VK_F6: return KeyCode::F6;
    case VK_F7: return KeyCode::F7;
    case VK_F8: return KeyCode::F8;
    case VK_F9: return KeyCode::F9;
    case VK_F10: return KeyCode::F10;
    case VK_F11: return KeyCode::F11;
    case VK_F12: return KeyCode::F12;
    case VK_F13: return KeyCode::F13;
    case VK_F14: return KeyCode::F14;
    case VK_F15: return KeyCode::F15;
    case VK_F16: return KeyCode::F16;
    case VK_F17: return KeyCode::F17;
    case VK_F18: return KeyCode::F18;
    case VK_F19: return KeyCode::F19;
    case VK_F20: return KeyCode::F20;
    case VK_F21: return KeyCode::F21;
    case VK_F22: return KeyCode::F22;
    case VK_F23: return KeyCode::F23;
    case VK_F24: return KeyCode::F24;

    case VK_NUMPAD0: return KeyCode::Numpad0;
    case VK_NUMPAD1: return KeyCode::Numpad1;
    case VK_NUMPAD2: return KeyCode::Numpad2;
    case VK_NUMPAD3: return KeyCode::Numpad3;
    case VK_NUMPAD4: return KeyCode::Numpad4;
    case VK_NUMPAD5: return KeyCode::Numpad5;
    case VK_NUMPAD6: return KeyCode::Numpad6;
    case VK_NUMPAD7: return KeyCode::Numpad7;
    case VK_NUMPAD8: return KeyCode::Numpad8;
    case VK_NUMPAD9: return KeyCode::Numpad9;

    case VK_ADD: return KeyCode::Add;
    case VK_SUBTRACT: return KeyCode::Subtract;
    case VK_MULTIPLY: return KeyCode::Multiply;
    case VK_DIVIDE: return KeyCode::Divide;
    case VK_DECIMAL: return KeyCode::Decimal;
    case VK_SEPARATOR: return KeyCode::Separator;

    case VK_PRIOR: return KeyCode::PageUp;
    case VK_NEXT: return KeyCode::PageDown;
    case VK_END: return KeyCode::End;
    case VK_HOME: return KeyCode::Home;
    case VK_INSERT: return KeyCode::Insert;
    case VK_DELETE: return KeyCode::Delete;
    case VK_BACK: return KeyCode::Backspace;

    case VK_LEFT: return KeyCode::Left;
    case VK_RIGHT: return KeyCode::Right;
    case VK_UP: return KeyCode::Up;
    case VK_DOWN: return KeyCode::Down;

    case '0': return KeyCode::Num0;
    case '1': return KeyCode::Num1;
    case '2': return KeyCode::Num2;
    case '3': return KeyCode::Num3;
    case '4': return KeyCode::Num4;
    case '5': return KeyCode::Num5;
    case '6': return KeyCode::Num6;
    case '7': return KeyCode::Num7;
    case '8': return KeyCode::Num8;
    case '9': return KeyCode::Num9;

    case 'A': return KeyCode::A;
    case 'B': return KeyCode::B;
    case 'C': return KeyCode::C;
    case 'D': return KeyCode::D;
    case 'E': return KeyCode::E;
    case 'F': return KeyCode::F;
    case 'G': return KeyCode::G;
    case 'H': return KeyCode::H;
    case 'I': return KeyCode::I;
    case 'J': return KeyCode::J;
    case 'K': return KeyCode::K;
    case 'L': return KeyCode::L;
    case 'M': return KeyCode::M;
    case 'N': return KeyCode::N;
    case 'O': return KeyCode::O;
    case 'P': return KeyCode::P;
    case 'Q': return KeyCode::Q;
    case 'R': return KeyCode::R;
    case 'S': return KeyCode::S;
    case 'T': return KeyCode::T;
    case 'U': return KeyCode::U;
    case 'V': return KeyCode::V;
    case 'X': return KeyCode::X;
    case 'Y': return KeyCode::Y;
    case 'W': return KeyCode::W;
    case 'Z': return KeyCode::Z;

    case VK_OEM_1: return KeyCode::Semicolon;
    case VK_OEM_2: return KeyCode::Slash;
    case VK_OEM_3: return KeyCode::Tilde;
    case VK_OEM_4: return KeyCode::LBracket;
    case VK_OEM_5: return KeyCode::Backslash;
    case VK_OEM_6: return KeyCode::RBracket;
    case VK_OEM_7: return KeyCode::Quote;
    case VK_OEM_8: return KeyCode::Special1;
    case VK_OEM_102: return KeyCode::Special2;
    case VK_OEM_COMMA: return KeyCode::Comma;
    case VK_OEM_PERIOD: return KeyCode::Period;
    case VK_OEM_PLUS: return KeyCode::Equal;
    case VK_OEM_MINUS: return KeyCode::Dash;
    case VK_SPACE: return KeyCode::Space;
    case VK_RETURN: return KeyCode::Enter;
    case VK_TAB: return KeyCode::Tab;

    case VK_CAPITAL: return KeyCode::CapsLock;
    case VK_NUMLOCK: return KeyCode::NumLock;
    case VK_SCROLL: return KeyCode::ScrollLock;

    case VK_CONTROL: return KeyCode::LCtrl;
    case VK_LCONTROL: return KeyCode::LCtrl;
    case VK_RCONTROL: return KeyCode::RCtrl;
    case VK_MENU: return KeyCode::LAlt;
    case VK_LMENU: return KeyCode::LAlt;
    case VK_RMENU: return KeyCode::RAlt;
    case VK_SHIFT: return KeyCode::LShift;
    case VK_LSHIFT: return KeyCode::LShift;
    case VK_RSHIFT: return KeyCode::RShift;

    case VK_JUNJA: return KeyCode::Junja;
    case VK_FINAL: return KeyCode::Final;
    case VK_HANJA: return KeyCode::Hanja;
    case VK_CONVERT: return KeyCode::Convert;
    case VK_NONCONVERT: return KeyCode::NonConvert;
    case VK_ACCEPT: return KeyCode::Accept;
    case VK_MODECHANGE: return KeyCode::ModeChange;
    case VK_PROCESSKEY: return KeyCode::ProcessKey;

    case VK_BROWSER_BACK: return KeyCode::BrowserBack;
    case VK_BROWSER_FORWARD: return KeyCode::BrowserForward;
    case VK_BROWSER_REFRESH: return KeyCode::BrowserRefresh;
    case VK_BROWSER_STOP: return KeyCode::BrowserStop;
    case VK_BROWSER_SEARCH: return KeyCode::BrowserSearch;
    case VK_BROWSER_FAVORITES: return KeyCode::BrowserFavorites;
    case VK_BROWSER_HOME: return KeyCode::BrowserHome;

    case VK_VOLUME_UP: return KeyCode::VolumeUp;
    case VK_VOLUME_DOWN: return KeyCode::VolumeDown;
    case VK_VOLUME_MUTE: return KeyCode::VolumeMute;

    case VK_MEDIA_NEXT_TRACK: return KeyCode::MediaNextTrack;
    case VK_MEDIA_PREV_TRACK: return KeyCode::MediaPreviousTrack;
    case VK_MEDIA_STOP: return KeyCode::MediaStop;
    case VK_MEDIA_PLAY_PAUSE: return KeyCode::MediaPlayPause;
    case VK_LAUNCH_MEDIA_SELECT: return KeyCode::LaunchMediaSelect;
    case VK_LAUNCH_MAIL: return KeyCode::LaunchMail;
    case VK_LAUNCH_APP1: return KeyCode::LaunchApp1;
    case VK_LAUNCH_APP2: return KeyCode::LaunchApp2;

    case VK_ATTN: return KeyCode::Attn;
    case VK_CRSEL: return KeyCode::CrSel;
    case VK_EXSEL: return KeyCode::ExSel;
    case VK_EREOF: return KeyCode::EraseEOF;
    case VK_PLAY: return KeyCode::Play;
    case VK_ZOOM: return KeyCode::Zoom;
    case VK_PA1: return KeyCode::PA1;
    case VK_CLEAR: return KeyCode::Clear;
    case VK_PACKET: return KeyCode::Packet;

    default:
      HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), key);
      return KeyCode::Enter;
  }
}



KeyCode getKeyCodeWParam(WPARAM wParam)
{
  return winKeyToKeyCode(static_cast<UINT>(wParam));
}



ScanCode getScanCodeLParam(LPARAM lParam)
{
  UINT scanCode = GET_SCAN_CODE_LPARAM(lParam);
  if(GET_EXTENDED_KEY_LPARAM(lParam))
  {
    scanCode += 0xe000;
  }
  return ScanCode(scanCode);
}

}



WindowImpl::WindowImpl(const std::string& title, const VideoMode& videoMode
  , WindowStyle style)
  : NonCopyable()
  , mHandle(nullptr)
  , mCursorGrabbed(false)
  , mKeyRepeatEnabled(false)
  , mEventQueue()
  , mHdc(nullptr)
  , mCursorHandle(nullptr)
  , mIconHandle(nullptr)
  , mCachedUtf16Char(0)
  , mMouseInWindow(false)
  , mPreviousSize(videoMode.get_resolution())
{
  HOU_EXPECT(style != WindowStyle::Fullscreen
    || (videoMode.isFullscreenMode() && fullscreenWindow == nullptr));

  registerWindowClass();

  // Create the window.
  mHandle = CreateWindowExW
    ( windowStyleToWinWindowStyleEx(style)              // dwExStyle
    , houClassName                                      // lpClassName
    , convertEncoding<utf8, wide>(title).c_str()        // lpWindowName
    , windowStyleToWinWindowStyle(style)                // dwStyle
    , 0, 0                        // Position
    , 0, 0  // Size
    , nullptr                                           // hWndParent
    , nullptr                                           // hMenu
    , GetModuleHandle(nullptr)                          // hInstance
    , nullptr);                                         // lpParam
  HOU_WIN_ENSURE(mHandle != nullptr);

  // Set client size. CreateWindowEx sets frame position and size, but we want
  // the arguments passed to the constructor to refer to client position and
  // size.
  Vec2i position = (style == WindowStyle::Fullscreen)
    ? Vec2i(0, 0)
    : Vec2i(VideoMode::getDesktopMode().get_resolution() - videoMode.get_resolution()) / 2;
  setClientRect(Recti(position, videoMode.get_resolution()));

  // Set a pointer to the window class in the window user data (used in the
  // window procedure).
  SetLastError(0);
  SetWindowLongPtrW(mHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
  HOU_WIN_ENSURE(GetLastError() == 0);

  // Initialize handle to device context.
  mHdc = GetDC(mHandle);
  HOU_WIN_ENSURE(mHdc != nullptr);

  // Activate fullscreen mode if necessary.
  if(style == WindowStyle::Fullscreen)
  {
    activateFullscreenMode(*this, videoMode);
  }

  // Check if the mouse is inside the client area. If yes, also capture the
  // cursor (this is necessary to correctly generate events related to mouse
  // movement).
  mMouseInWindow = isPointInRectangle(getClientRect(), Mouse::getPosition());
  setMouseCaptured(mMouseInWindow);
}



WindowImpl::WindowImpl(WindowImpl&& other)
  : NonCopyable()
  , mHandle(std::move(other.mHandle))
  , mCursorGrabbed(std::move(other.mCursorGrabbed))
  , mKeyRepeatEnabled(std::move(other.mKeyRepeatEnabled))
  , mEventQueue(std::move(other.mEventQueue))
  , mHdc(std::move(other.mHdc))
  , mCursorHandle(std::move(other.mCursorHandle))
  , mIconHandle(std::move(other.mIconHandle))
  , mCachedUtf16Char(std::move(other.mCachedUtf16Char))
  , mMouseInWindow(std::move(other.mMouseInWindow))
{
  {
    std::lock_guard<std::mutex> lock(fullscreenMutex);
    if(fullscreenWindow == &other)
    {
       fullscreenWindow = this;
    }
  }

  // Update pointer to the window class in the window user data.
  SetLastError(0);
  SetWindowLongPtrW(mHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
  HOU_WIN_ENSURE(GetLastError() == 0);

  other.mHandle = nullptr;
  other.mHdc = nullptr;
  other.mCursorHandle = nullptr;
  other.mIconHandle = nullptr;
}



WindowImpl::~WindowImpl()
{
  destroyIcon();
  destroyCursor();
  destroyWindow();
}



Recti WindowImpl::getFrameRect() const
{
  RECT rect = {0, 0, 0, 0};
  HOU_WIN_ENSURE(GetWindowRect(mHandle, &rect) != 0);
  return Recti(rect.left, rect.top
    , rect.right - rect.left, rect.bottom - rect.top);
}



void WindowImpl::setFrameRect(const Recti& value)
{
  HOU_WIN_ENSURE(SetWindowPos(mHandle, nullptr
    , value.x(), value.y(), value.w(), value.h()
    , SWP_NOZORDER) != 0);
  if(mCursorGrabbed)
  {
    grabMouseCursor();
  }
}



Recti WindowImpl::getClientRect() const
{
  // Note returned x and y are always 0 with GetClientRect.
  RECT rect = {0, 0, 0, 0};
  HOU_WIN_ENSURE(GetClientRect(mHandle, &rect) != 0);

  POINT origin = {0, 0};
  HOU_WIN_ENSURE(ClientToScreen(mHandle, &origin) != 0);

  return Recti(origin.x, origin.y, rect.right, rect.bottom);
}




void WindowImpl::setClientRect(const Recti& value)
{
  setFrameRect(clientToFrameRect(mHandle, value));
}



void WindowImpl::setTitle(const std::string& value)
{
  HOU_WIN_ENSURE(SetWindowTextW(mHandle
    , convertEncoding<utf8, wide>(value).c_str()) != 0);
}



bool WindowImpl::isVisible() const
{
  return IsWindowVisible(mHandle);
}



void WindowImpl::setVisible(bool value)
{
  // No possible failure.
  ShowWindow(mHandle, value ? SW_SHOW : SW_HIDE);
  if(value)
  {
    HOU_WIN_ENSURE(UpdateWindow(mHandle) != 0);
  }
}



void WindowImpl::setIcon(const Image2RGBA& icon)
{
  destroyIcon();
  mIconHandle = createCustomIcon(icon);
  HOU_WIN_ENSURE(mIconHandle != nullptr);
  setWindowIcon(mHandle, mIconHandle);
}



void WindowImpl::setSystemIcon()
{
  destroyIcon();
  mIconHandle = nullptr;
  HICON iconHandle = getSystemIcon();
  HOU_WIN_ENSURE(iconHandle != nullptr);
  setWindowIcon(mHandle, iconHandle);
}



void WindowImpl::grabMouseCursor()
{
  RECT rect;
  HOU_WIN_ENSURE(GetClientRect(mHandle, &rect) != 0);

  SetLastError(0);
  MapWindowPoints(mHandle, nullptr, reinterpret_cast<LPPOINT>(&rect), 2);
  HOU_WIN_ENSURE(GetLastError() == 0);

  HOU_WIN_ENSURE(ClipCursor(&rect) != 0);
}



void WindowImpl::ungrabMouseCursor()
{
  HOU_WIN_ENSURE(ClipCursor(nullptr) != 0);
}



bool WindowImpl::isMouseCaptured() const
{
  return GetCapture() == mHandle;
}



void WindowImpl::setMouseCaptured(bool value)
{
  if(isMouseCaptured() != value)
  {
    if(value)
    {
      SetCapture(mHandle);
    }
    else
    {
      BOOL success = ReleaseCapture();
      HOU_WIN_ENSURE(success != 0);
    }
  }
}



bool WindowImpl::hasFocus() const
{
  return GetFocus() == mHandle;
}



bool WindowImpl::requestFocus() const
{
  // Allow focus stealing only within the current process.
  // Cannot fail.
  DWORD thisPid = GetWindowThreadProcessId(mHandle, nullptr);
  DWORD foregroundPid = GetWindowThreadProcessId(GetForegroundWindow()
    , nullptr);

  if(thisPid == foregroundPid)
  {
    BOOL success = SetForegroundWindow(mHandle);
    return success != 0;
  }
  else
  {
    // Flash if not allowed to steal focus.
    FLASHWINFO info;
    info.cbSize = sizeof(FLASHWINFO);
    info.hwnd = mHandle;
    info.dwFlags = FLASHW_TRAY;
    info.dwTimeout = 0;
    info.uCount = 3;
    FlashWindowEx(&info);
    return false;
  }
}



void WindowImpl::updateEventQueue()
{
  MSG msg;
  // Cannot fail.
  while(PeekMessageW(&msg, mHandle, 0, 0, PM_REMOVE))
  {
    // Cannot fail.
    TranslateMessage(&msg);
    // Cannot fail.
    DispatchMessage(&msg);
  }
}



void WindowImpl::swapBuffers()
{
  HOU_WIN_ENSURE(SwapBuffers(mHdc) != 0);
}



void WindowImpl::registerWindowClass()
{
  std::lock_guard<std::mutex> lock(houClassMutex);
  if(windowCount == 0)
  {
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = &hou::prv::WindowImpl::wndProcedure;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = houClassName;
    wcex.hIconSm = nullptr;

    HOU_WIN_ENSURE(RegisterClassExW(&wcex) != 0);
  }
  ++windowCount;
  HOU_ENSURE_DEV(windowCount > 0);
}



void WindowImpl::unregisterWindowClass()
{
  std::lock_guard<std::mutex> lock(houClassMutex);
  HOU_EXPECT_DEV(windowCount > 0);
  --windowCount;
  if(windowCount == 0)
  {
    HOU_WIN_ENSURE(UnregisterClassW(houClassName, GetModuleHandle(nullptr))
      != 0);
  }
}



LRESULT CALLBACK WindowImpl::wndProcedure(HWND hwnd, UINT uMsg, WPARAM wParam
  , LPARAM lParam)
{
  WindowImpl* window = hwnd
    ? reinterpret_cast<WindowImpl*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA))
    : nullptr;

  if(window != nullptr)
  {
    window->filterEvent(uMsg, wParam, lParam);
  }

  // Do not forward close messages and sys command messages.
  if(uMsg == WM_CLOSE || ((uMsg == WM_SYSCOMMAND) && (wParam== SC_KEYMENU)))
  {
    return 0;
  }

  return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}



void WindowImpl::filterEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  HOU_EXPECT_DEV(mHandle != nullptr);

  switch(uMsg)
  {
    case WM_CLOSE:
    {
      pushEvent(WindowEvent::closed());
      break;
    }

    case WM_SETFOCUS:
    {
      isMouseCursorGrabbed() ? grabMouseCursor() : ungrabMouseCursor();
      pushEvent(WindowEvent::focusGained());
      break;
    }

    case WM_KILLFOCUS:
    {
      mPreviousSize = getClientRect().getSize();
      ungrabMouseCursor();
      pushEvent(WindowEvent::focusLost());
      break;
    }

    case WM_ENTERSIZEMOVE:
    {
      ungrabMouseCursor();
      break;
    }

    case WM_EXITSIZEMOVE:
    {
      isMouseCursorGrabbed() ? grabMouseCursor() : ungrabMouseCursor();
      Vec2u currentSize = getClientRect().getSize();
      if(currentSize != mPreviousSize)
      {
        pushEvent(WindowEvent::resized(currentSize.x(), currentSize.y()));
      }
      break;
    }

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    {
      if(isKeyRepeatEnabled() || !GET_KEY_PREVIOUSLY_DOWN_LPARAM(lParam))
      {
        pushEvent(WindowEvent::keyPressed
          ( getKeyCodeWParam(wParam)
          , getScanCodeLParam(lParam)
          , Keyboard::getModifierKeysState()));
      }
      break;
    }

    case WM_KEYUP:
    case WM_SYSKEYUP:
    {
      pushEvent(WindowEvent::keyReleased
        ( getKeyCodeWParam(wParam)
        , getScanCodeLParam(lParam)
        , Keyboard::getModifierKeysState()));
      break;
    }

    case WM_CHAR:
    {
      // Check if key repeat is enabled or if previous key state is up.
      if(isKeyRepeatEnabled() || !GET_KEY_PREVIOUSLY_DOWN_LPARAM(lParam))
      {
        char32_t character = static_cast<char32_t>(wParam);
        // First code unit of surrogate pair.
        if((character >= 0xD800) && (character <= 0xD8FF))
        {
          mCachedUtf16Char = static_cast<char16_t>(character);
        }
        else
        {
          // Second code unit of surrogate pair.
          if((character >= 0xDC00) && (character <= 0xDFFF))
          {
            char16_t p_utf16[] = { mCachedUtf16Char
              , static_cast<char16_t>(character) };
            convertEncoding<utf16, utf32>(p_utf16, p_utf16 + 2, &character);
            mCachedUtf16Char = 0;
          }

          pushEvent(WindowEvent::textEntered(character));
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

      Vec2i pos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

      Recti clientRect = getClientRect();
      clientRect.setPosition(Vec2i());

      bool mouseCurrentlyInWindow = isPointInRectangle(clientRect, pos);

      // Generate mouse move event only if the mouse is inside the client.
      if(mouseCurrentlyInWindow)
      {
        pushEvent(WindowEvent::mouseMoved(pos.x(), pos.y()));
      }

      if(!mMouseInWindow && mouseCurrentlyInWindow)
      {
        pushEvent(WindowEvent::mouseEntered());
      }
      else if(mMouseInWindow && !mouseCurrentlyInWindow)
      {
        pushEvent(WindowEvent::mouseLeft());
      }

      mMouseInWindow = mouseCurrentlyInWindow;
      setMouseCaptured(mouseCurrentlyInWindow);

      break;
    }

    case WM_LBUTTONDOWN:
    {
      pushEvent(WindowEvent::mouseButtonPressed(MouseButton::LB
        , GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
      break;
    }

    case WM_LBUTTONUP:
    {
      pushEvent(WindowEvent::mouseButtonReleased(MouseButton::LB
        , GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
      break;
    }

    case WM_RBUTTONDOWN:
    {
      pushEvent(WindowEvent::mouseButtonPressed(MouseButton::RB
        , GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
      break;
    }

    case WM_RBUTTONUP:
    {
      pushEvent(WindowEvent::mouseButtonReleased(MouseButton::RB
        , GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
      break;
    }

    case WM_MBUTTONDOWN:
    {
      pushEvent(WindowEvent::mouseButtonPressed(MouseButton::MB
        , GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
      break;
    }

    case WM_MBUTTONUP:
    {
      pushEvent(WindowEvent::mouseButtonReleased(MouseButton::MB
        , GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
      break;
    }

    case WM_XBUTTONDOWN:
    {
      pushEvent(WindowEvent::mouseButtonPressed
        ( GET_XBUTTON_WPARAM(wParam) == 1
        ? MouseButton::XB1 : MouseButton::XB2
        , GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
      break;
    }

    case WM_XBUTTONUP:
    {
      pushEvent(WindowEvent::mouseButtonReleased
        ( GET_XBUTTON_WPARAM(wParam) == 1
        ? MouseButton::XB1 : MouseButton::XB2
        , GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
      break;
    }

    case WM_MOUSEWHEEL:
    {
      static constexpr int wheelIncrement = 120;
      pushEvent(WindowEvent::mouseWheelMoved
        ( MouseWheel::Vertical
        , GET_WHEEL_DELTA_WPARAM(wParam) / wheelIncrement
        , GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
      break;
    }

    case WM_MOUSEHWHEEL:
    {
      static constexpr int wheelIncrement = 120;
      pushEvent(WindowEvent::mouseWheelMoved
        ( MouseWheel::Horizontal
        , GET_WHEEL_DELTA_WPARAM(wParam) / wheelIncrement
        , GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
      break;
    }
  }
}



void WindowImpl::destroyIcon()
{
  if(mIconHandle != nullptr)
  {
    HOU_WIN_FATAL_CHECK(DestroyIcon(mIconHandle) != 0, "");
  }
}



void WindowImpl::destroyCursor()
{
  if(mCursorHandle != nullptr)
  {
    HOU_WIN_FATAL_CHECK(DestroyCursor(mCursorHandle) != 0, "");
  }
}



void WindowImpl::destroyWindow()
{
  if(mHandle != nullptr)
  {
    if(isFullscreenWindow(*this))
    {
      deactivateFullscreenMode();
    }
    HOU_WIN_FATAL_CHECK(DestroyWindow(mHandle) != 0, "");
    unregisterWindowClass();
  }
}

}

}

