// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_CONTEXT_IMPL_HPP

#define HOU_GL_GL_CONTEXT_IMPL_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gl/gl_config.hpp"

#include "SDL2/SDL.h"


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

public:
  context_impl(const context_settings& settings, window& wnd);

  context_impl(context_impl&& other) noexcept;

  ~context_impl();

  SDL_GLContext& get_impl() noexcept;

private:
  SDL_GLContext m_impl;
};

}  // namespace prv

}  // namespace gl

}  // namespace hou

#endif
