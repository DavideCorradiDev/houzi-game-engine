// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/gfx_module.hpp"



namespace hou
{

namespace prv
{

std::string gfx_module_impl::get_name()
{
  return u8"graphics";
}



bool gfx_module_impl::on_initialize()
{
  return true;
}



void gfx_module_impl::on_terminate() noexcept
{}

}  // namespace prv

}  // namespace hou
