// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/sys_module.hpp"

#include "hou/sys/sys_exceptions.hpp"

#include "hou/sys/glfw/glfw_error_handler.hpp"

#include "hou/cor/assertions.hpp"

#include "GLFW/glfw3.h"


#include <iostream>
namespace hou
{

namespace prv
{

namespace
{

void platform_error_callback(const char* description)
{
  HOU_ERROR_N(platform_error, description);
}



void out_of_memory_callback(const char*)
{
  HOU_ERROR_STD_0(std::bad_alloc);
}



void invalid_argument_callback(const char*)
{
  HOU_ERROR_0(precondition_violation);
}

}



bool sys_module_impl::on_initialize()
{
  if(glfwInit() != GLFW_TRUE)
  {
    return false;
  }

  prv::glfw_error_handler::set_callback(
    GLFW_PLATFORM_ERROR, platform_error_callback);
  prv::glfw_error_handler::set_callback(
    GLFW_OUT_OF_MEMORY, out_of_memory_callback);
  prv::glfw_error_handler::set_callback(
    GLFW_INVALID_ENUM, invalid_argument_callback);
  prv::glfw_error_handler::set_callback(
    GLFW_INVALID_VALUE, invalid_argument_callback);
  glfwSetErrorCallback(&prv::glfw_error_handler::callback);
  return true;
}



void sys_module_impl::on_terminate() noexcept
{
  glfwTerminate();

  glfwSetErrorCallback(nullptr);
  prv::glfw_error_handler::set_callback(GLFW_PLATFORM_ERROR, nullptr);
  prv::glfw_error_handler::set_callback(GLFW_OUT_OF_MEMORY, nullptr);
  prv::glfw_error_handler::set_callback(GLFW_INVALID_ENUM, nullptr);
  prv::glfw_error_handler::set_callback(GLFW_INVALID_VALUE, nullptr);
}

}

}  // namespace hou
