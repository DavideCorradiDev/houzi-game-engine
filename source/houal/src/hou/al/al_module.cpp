// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_module.hpp"

#include "hou/al/open_al.hpp"



namespace hou
{

namespace prv
{

std::string al_module_impl::get_name()
{
  return u8"OpenAL";
}



bool al_module_impl::on_initialize()
{
  alGetError();
  return true;
}



void al_module_impl::on_terminate() noexcept
{}

}  // namespace prv

}  // namespace hou
