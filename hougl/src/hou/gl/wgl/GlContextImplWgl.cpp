// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gl/GlContextImpl.hpp"

#include "hou/gl/GlContextSettings.hpp"
#include "hou/gl/GlError.hpp"
#include "hou/gl/OpenGl.hpp"

#include "hou/sys/Window.hpp"
#include "hou/sys/win/WinError.hpp"



namespace hou
{

namespace gl
{

namespace prv
{

namespace
{

constexpr uint bitsPerByte = 8u;

int choosePixelFormat(
  HDC hdc, uint colorByteCount, const ContextSettings& settings);
void setPixelFormat(HDC hdc, int formatNumber);
bool hasPixelFormat(HDC hdc);



int choosePixelFormat(
  HDC hdc, uint colorByteCount, const ContextSettings& settings)
{
  HOU_EXPECT_DEV(hdc != nullptr);

  int format;

  if(wglChoosePixelFormatARB)
  {
    const int attributesList[] = {
      WGL_DRAW_TO_WINDOW_ARB, GL_TRUE, WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
      WGL_DOUBLE_BUFFER_ARB, GL_TRUE, WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
      WGL_COLOR_BITS_ARB, static_cast<int>(colorByteCount * bitsPerByte),
      WGL_DEPTH_BITS_ARB,
      static_cast<int>(settings.getDepthByteCount() * bitsPerByte),
      WGL_STENCIL_BITS_ARB,
      static_cast<int>(settings.getStencilByteCount() * bitsPerByte),
      WGL_SAMPLE_BUFFERS_ARB, settings.getAntialiasingLevel() == 0 ? 0 : 1,
      WGL_SAMPLES_ARB, static_cast<int>(settings.getAntialiasingLevel()),
      0  // End
    };

    UINT numFormats;
    HOU_WIN_RUNTIME_CHECK(wglChoosePixelFormatARB(hdc, attributesList, nullptr,
                            1, &format, &numFormats)
        != 0,
      getText(GlError::ContextCreate));
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
    pfd.cColorBits = static_cast<BYTE>(colorByteCount * bitsPerByte);
    pfd.cDepthBits
      = static_cast<BYTE>(settings.getDepthByteCount() * bitsPerByte);
    pfd.cStencilBits
      = static_cast<BYTE>(settings.getStencilByteCount() * bitsPerByte);
    pfd.cAlphaBits = colorByteCount == 4 ? 1 : 0;

    format = ChoosePixelFormat(hdc, &pfd);
  }

  HOU_RUNTIME_CHECK(format != 0, getText(GlError::ContextCreate));
  return format;
}



void setPixelFormat(HDC hdc, int formatNumber)
{
  HOU_EXPECT_DEV(hdc != nullptr);
  HOU_EXPECT_DEV(formatNumber != 0);

  if(!hasPixelFormat(hdc))
  {
    PIXELFORMATDESCRIPTOR format;
    format.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    format.nVersion = 1;
    HOU_WIN_RUNTIME_CHECK(
      DescribePixelFormat(hdc, formatNumber, format.nSize, &format) != 0,
      getText(GlError::ContextCreate));
    HOU_WIN_RUNTIME_CHECK(SetPixelFormat(hdc, formatNumber, &format) != 0,
      getText(GlError::ContextCreate));
  }
}



bool hasPixelFormat(HDC hdc)
{
  HOU_EXPECT_DEV(hdc != nullptr);
  return GetPixelFormat(hdc) != 0;
}

}  // namespace



void ContextImpl::setCurrent(ContextImpl& context, Window& window)
{
  context.mHdc = GetDC(window.getWindowHandle());
  HOU_ENSURE(context.mHdc != nullptr);

  setPixelFormat(context.mHdc, context.mPixelFormat);

  HOU_WIN_RUNTIME_CHECK(wglMakeCurrent(context.mHdc, context.mHandle) != 0,
    getText(GlError::ContextMakeCurrent));
}



void ContextImpl::unsetCurrent()
{
  HOU_WIN_RUNTIME_CHECK(wglMakeCurrent(nullptr, nullptr) != 0,
    getText(GlError::ContextMakeCurrent));
}



ContextImpl::ContextImpl(const ContextSettings& settings, const Window& window,
  const ContextImpl* sharedContext)
  : NonCopyable()
  , mHandle(nullptr)
  , mHdc(GetDC(window.getWindowHandle()))
  , mPixelFormat(choosePixelFormat(mHdc, window.getBytesPerPixel(), settings))
{
  HOU_EXPECT(mHdc != nullptr);

  setPixelFormat(mHdc, mPixelFormat);

  HGLRC shared = (sharedContext != nullptr) ? sharedContext->mHandle : nullptr;

  if(wglCreateContextAttribsARB)
  {
    int wglProfile = settings.getProfile() == ContextProfile::Core
      ? WGL_CONTEXT_CORE_PROFILE_BIT_ARB
      : WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;

    int attr[]
      = { WGL_CONTEXT_MAJOR_VERSION_ARB,
          static_cast<int>(settings.getVersion().getMajor()),
          WGL_CONTEXT_MINOR_VERSION_ARB,
          static_cast<int>(settings.getVersion().getMinor()),
          WGL_CONTEXT_PROFILE_MASK_ARB,
          wglProfile,
#if defined(HOU_DEBUG)
          WGL_CONTEXT_FLAGS_ARB,
          WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
          0  // End
        };

    mHandle = wglCreateContextAttribsARB(mHdc, shared, attr);
    HOU_WIN_RUNTIME_CHECK(mHandle != nullptr, getText(GlError::ContextCreate));
  }
  else
  {
    mHandle = wglCreateContext(mHdc);
    HOU_WIN_RUNTIME_CHECK(mHandle != nullptr, getText(GlError::ContextCreate));
    if(shared != nullptr)
    {
      HOU_WIN_RUNTIME_CHECK(
        wglShareLists(shared, mHandle) != 0, getText(GlError::ContextCreate));
    }
  }

  HOU_ENSURE_DEV(mHandle != nullptr);
}



ContextImpl::ContextImpl(ContextImpl&& other)
  : NonCopyable()
  , mHandle(std::move(other.mHandle))
  , mHdc(std::move(other.mHdc))
  , mPixelFormat(std::move(other.mPixelFormat))
{
  other.mHandle = nullptr;
  other.mHdc = nullptr;
}



ContextImpl::~ContextImpl()
{
  if(mHandle != nullptr)
  {
    HOU_FATAL_CHECK(
      wglDeleteContext(mHandle) != 0, getText(GlError::ContextDestroy));
  }
}

}  // namespace prv

}  // namespace gl

}  // namespace hou
