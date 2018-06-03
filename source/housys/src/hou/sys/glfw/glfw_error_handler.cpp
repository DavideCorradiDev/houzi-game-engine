// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/glfw/glfw_error_handler.hpp"



namespace hou
{

namespace prv
{

std::map<int, glfw_error_handler::callback_type>
  glfw_error_handler::s_callbacks;



void glfw_error_handler::callback(int error, const char* description)
{
  auto callback_it = s_callbacks.find(error);
  if(callback_it != s_callbacks.end())
  {
    callback_it->second(description);
  }
}



void glfw_error_handler::set_callback(int error, callback_type callback)
{
  if(callback == nullptr)
  {
    s_callbacks.erase(error);
  }
  else
  {
    s_callbacks[error] = callback;
  }
}



void glfw_error_handler::clear_callbacks()
{
  s_callbacks.clear();
}

}  // namespace prv

}  // namespace hou
