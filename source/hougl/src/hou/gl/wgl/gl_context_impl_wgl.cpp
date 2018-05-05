// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_context_impl.hpp"

#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_error.hpp"
#include "hou/gl/open_gl.hpp"

#include "hou/sys/win/win_error.hpp"
#include "hou/sys/window.hpp"



namespace hou
{

namespace gl
{

namespace prv
{

namespace
{

constexpr uint bits_per_byte = 8u;

int choose_pixel_format(
  HDC hdc, uint color_byte_count, const context_settings& settings);
void set_pixel_format(HDC hdc, int format_number);
bool has_pixel_format(HDC hdc);



int choose_pixel_format(
  HDC hdc, uint color_byte_count, const context_settings& settings)
{
  HOU_DEV_PRECOND(hdc != nullptr);

  int format;

  if(wglChoosePixelFormatARB)
  {
    const int attributes_list[] = {
      WGL_DRAW_TO_WINDOW_ARB, GL_TRUE, WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
      WGL_DOUBLE_BUFFER_ARB, GL_TRUE, WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
      WGL_COLOR_BITS_ARB, static_cast<int>(color_byte_count * bits_per_byte),
      WGL_DEPTH_BITS_ARB,
      static_cast<int>(settings.get_depth_byte_count() * bits_per_byte),
      WGL_STENCIL_BITS_ARB,
      static_cast<int>(settings.get_stencil_byte_count() * bits_per_byte),
      WGL_SAMPLE_BUFFERS_ARB, settings.get_sample_count() == 0 ? 0 : 1,
      WGL_SAMPLES_ARB, static_cast<int>(settings.get_sample_count()),
      0  // End
    };

    UINT num_formats;
    HOU_WIN_RUNTIME_CHECK(wglChoosePixelFormatARB(hdc, attributes_list, nullptr,
                            1, &format, &num_formats)
        != 0,
      get_text(gl_error::context_create));
  }
  else
  {
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = static_cast<BYTE>(color_byte_count * bits_per_byte);
    pfd.cDepthBits
      = static_cast<BYTE>(settings.get_depth_byte_count() * bits_per_byte);
    pfd.cStencilBits
      = static_cast<BYTE>(settings.get_stencil_byte_count() * bits_per_byte);
    pfd.cAlphaBits = color_byte_count == 4 ? 1 : 0;

    format = ChoosePixelFormat(hdc, &pfd);
  }

  DEPRECATED_HOU_RUNTIME_CHECK(format != 0, get_text(gl_error::context_create));
  return format;
}



void set_pixel_format(HDC hdc, int format_number)
{
  HOU_DEV_PRECOND(hdc != nullptr);
  HOU_DEV_PRECOND(format_number != 0);

  if(!has_pixel_format(hdc))
  {
    PIXELFORMATDESCRIPTOR format;
    format.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    format.nVersion = 1;
    HOU_WIN_RUNTIME_CHECK(
      DescribePixelFormat(hdc, format_number, format.nSize, &format) != 0,
      get_text(gl_error::context_create));
    HOU_WIN_RUNTIME_CHECK(SetPixelFormat(hdc, format_number, &format) != 0,
      get_text(gl_error::context_create));
  }
}



bool has_pixel_format(HDC hdc)
{
  HOU_DEV_PRECOND(hdc != nullptr);
  return GetPixelFormat(hdc) != 0;
}

}  // namespace



void context_impl::set_current(context_impl& ctx, window& wnd)
{
  ctx.m_hdc = GetDC(wnd.get_handle());
  HOU_POSTCOND(ctx.m_hdc != nullptr);

  set_pixel_format(ctx.m_hdc, ctx.m_pixel_format);

  HOU_WIN_RUNTIME_CHECK(wglMakeCurrent(ctx.m_hdc, ctx.m_handle) != 0,
    get_text(gl_error::context_make_current));
}



void context_impl::unset_current()
{
  HOU_WIN_RUNTIME_CHECK(wglMakeCurrent(nullptr, nullptr) != 0,
    get_text(gl_error::context_make_current));
}



context_impl::context_impl(const context_settings& settings, const window& wnd,
  const context_impl* shared_context)
  : non_copyable()
  , m_handle(nullptr)
  , m_hdc(GetDC(wnd.get_handle()))
  , m_pixel_format(
      choose_pixel_format(m_hdc, wnd.get_bytes_per_pixel(), settings))
{
  HOU_PRECOND(m_hdc != nullptr);

  set_pixel_format(m_hdc, m_pixel_format);

  HGLRC shared
    = (shared_context != nullptr) ? shared_context->m_handle : nullptr;

  if(wglCreateContextAttribsARB)
  {
    int wgl_profile = settings.get_profile() == context_profile::core
      ? WGL_CONTEXT_CORE_PROFILE_BIT_ARB
      : WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;

    int attr[]
      = { WGL_CONTEXT_MAJOR_VERSION_ARB,
          static_cast<int>(settings.get_version().get_major()),
          WGL_CONTEXT_MINOR_VERSION_ARB,
          static_cast<int>(settings.get_version().get_minor()),
          WGL_CONTEXT_PROFILE_MASK_ARB,
          wgl_profile,
#if defined(HOU_DEBUG)
          WGL_CONTEXT_FLAGS_ARB,
          WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
          0  // End
        };

    m_handle = wglCreateContextAttribsARB(m_hdc, shared, attr);
    HOU_WIN_RUNTIME_CHECK(
      m_handle != nullptr, get_text(gl_error::context_create));
  }
  else
  {
    m_handle = wglCreateContext(m_hdc);
    HOU_WIN_RUNTIME_CHECK(
      m_handle != nullptr, get_text(gl_error::context_create));
    if(shared != nullptr)
    {
      HOU_WIN_RUNTIME_CHECK(wglShareLists(shared, m_handle) != 0,
        get_text(gl_error::context_create));
    }
  }

  HOU_DEV_POSTCOND(m_handle != nullptr);
}



context_impl::context_impl(context_impl&& other)
  : non_copyable()
  , m_handle(std::move(other.m_handle))
  , m_hdc(std::move(other.m_hdc))
  , m_pixel_format(std::move(other.m_pixel_format))
{
  other.m_handle = nullptr;
  other.m_hdc = nullptr;
}



context_impl::~context_impl()
{
  if(m_handle != nullptr)
  {
    DEPRECATED_HOU_FATAL_CHECK(
      wglDeleteContext(m_handle) != 0, get_text(gl_error::context_destroy));
  }
}

}  // namespace prv

}  // namespace gl

}  // namespace hou
