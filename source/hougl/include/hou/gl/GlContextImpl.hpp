// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_CONTEXT_IMPL_HPP

#define HOU_GL_GL_CONTEXT_IMPL_HPP

#include "hou/config.hpp"
#include "hou/cor/non_copyable.hpp"

#include "hou/cor/basic_types.hpp"

#if defined(HOU_SYSTEM_WINDOWS)
  #include "hou/sys/win/Win.hpp"
#endif



namespace hou
{

class Window;

namespace gl
{

class ContextSettings;

namespace prv
{

class ContextImpl
  : public non_copyable
{
public:
  static void setCurrent(ContextImpl& context, Window& window);
  static void unsetCurrent();

  ContextImpl(const ContextSettings& settings, const Window& window
    , const ContextImpl* sharedContext);
  ContextImpl(ContextImpl&& other);
  ~ContextImpl();

private:
#if defined(HOU_SYSTEM_WINDOWS)
  HGLRC mHandle;
  HDC mHdc;
  int mPixelFormat;
#endif
};

}

}

}

#endif

