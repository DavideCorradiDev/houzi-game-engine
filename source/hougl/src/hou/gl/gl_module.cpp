// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_module.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/open_gl.hpp"

#include "hou/sys/window.hpp"

#include "SDL2/SDL_video.h"



namespace hou
{

namespace prv
{

namespace
{

bool init_gl_extensions();

bool init_gl_extensions()
{
  // A dummy OpenGL context need be created in order to initialiaze the OpenGL
  // extensions.
  window w("OpenGlInitialization", vec2u(1u, 1u));
  gl::context c(gl::context_settings::get_basic(), w);
  gl::context::set_current(c, w);
  return gladLoadGLLoader(SDL_GL_GetProcAddress) != 0;
}

}  // namespace

std::string gl_module_impl::get_name()
{
  return u8"OpenGL";
}



bool gl_module_impl::on_initialize()
{
  return init_gl_extensions();
}



void gl_module_impl::on_terminate() noexcept
{}

}  // namespace prv

}  // namespace hou
