// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_module.hpp"



namespace hou
{

namespace prv
{

std::string gl_module_impl::get_name()
{
  return u8"OpenGL";
}



bool gl_module_impl::on_initialize()
{
  return true;
}



void gl_module_impl::on_terminate() noexcept
{}

}  // namespace prv

}  // namespace hou
