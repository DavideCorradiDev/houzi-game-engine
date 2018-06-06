// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/sys_module.hpp"

#include "SDL2/SDL.h"



namespace hou
{

namespace prv
{

std::string sys_module_impl::get_name()
{
  return u8"system";
}



bool sys_module_impl::on_initialize()
{
  return SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) == 0;
}



void sys_module_impl::on_terminate() noexcept
{
  SDL_Quit();
}

}  // namespace prv

}  // namespace hou
