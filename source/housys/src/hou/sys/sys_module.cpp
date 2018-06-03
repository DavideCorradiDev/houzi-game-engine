// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/sys_module.hpp"

#include "GLFW/glfw3.h"


#include <iostream>
namespace hou
{

namespace prv
{

namespace
{

void glfw_error_callback(int ec, const char* description);

void glfw_error_callback(int ec, const char* description)
{
  switch(ec)
  {
  }
}

}



bool sys_module_impl::on_setup()
{
  auto f = glfwSetErrorCallback(glfw_error_callback);
  return glfwInit() == GLFW_TRUE;
}



void sys_module_impl::on_teardown() noexcept
{
  glfwTerminate();
  glfwSetErrorCallback(nullptr);
}

}

}  // namespace hou
