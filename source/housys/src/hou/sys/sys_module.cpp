// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/sys_module.hpp"

#include "GLFW/glfw3.h"



namespace hou
{

namespace prv
{

bool sys_module_impl::on_setup()
{
  return glfwInit() == GLFW_TRUE;
}



void sys_module_impl::on_teardown() noexcept
{
  glfwTerminate();
}

}

}  // namespace hou
