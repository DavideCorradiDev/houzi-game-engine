// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_context_impl.hpp"

#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_exceptions.hpp"

#include "hou/sys/window.hpp"



namespace hou
{

namespace gl
{

namespace prv
{

void context_impl::set_current(context_impl& ctx, window& wnd)
{
  HOU_CHECK_0(SDL_GL_MakeCurrent(wnd.get_impl(), ctx.get_impl()) == 0,
    context_switch_error);
}



void context_impl::unset_current()
{
  HOU_CHECK_0(SDL_GL_MakeCurrent(nullptr, nullptr) == 0, context_switch_error);
}



context_impl::context_impl(const context_settings& settings, window& wnd)
  : m_impl(nullptr)
{
  SDL_GL_ResetAttributes();
  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_MAJOR_VERSION, settings.get_version().get_major());
  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_MINOR_VERSION, settings.get_version().get_minor());
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
    settings.get_profile() == context_profile::core
      ? SDL_GL_CONTEXT_PROFILE_CORE
      : SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
  m_impl = SDL_GL_CreateContext(wnd.get_impl());
  SDL_GL_ResetAttributes();
  HOU_CHECK_0(m_impl != nullptr, context_creation_error);
}



context_impl::context_impl(context_impl&& other) noexcept
  : m_impl(std::move(other.m_impl))
{
  other.m_impl = nullptr;
}



context_impl::~context_impl()
{
  if(m_impl != nullptr)
  {
    SDL_GL_DeleteContext(m_impl);
  }
}



SDL_GLContext& context_impl::get_impl() noexcept
{
  return m_impl;
}

}  // namespace prv

}  // namespace gl

}  // namespace hou
