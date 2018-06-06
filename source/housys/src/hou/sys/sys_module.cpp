// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/sys_module.hpp"



namespace hou
{

namespace prv
{

bool sys_module_impl::on_initialize()
{
  return true;
}



void sys_module_impl::on_terminate() noexcept
{}

}  // namespace prv

}  // namespace hou
