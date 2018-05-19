// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_CONTEXT_IMPL_HPP

#define HOU_GL_GL_CONTEXT_IMPL_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gl/gl_config.hpp"

#if defined(HOU_SYSTEM_WINDOWS)
#include "hou/sys/win/win.hpp"
#endif



namespace hou
{

class window;

namespace gl
{

class context_settings;

namespace prv
{

class context_impl : public non_copyable
{
public:
  static void set_current(context_impl& ctx, window& wnd);
  static void unset_current();

  context_impl(const context_settings& settings, const window& wnd,
    const context_impl* shared_context);
  context_impl(context_impl&& other) noexcept;
  ~context_impl();

private:
#if defined(HOU_SYSTEM_WINDOWS)
  HGLRC m_handle;
  HDC m_hdc;
  int m_pixel_format;
#endif
};

}  // namespace prv

}  // namespace gl

}  // namespace hou

#endif
