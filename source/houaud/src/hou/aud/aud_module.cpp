// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/aud_module.hpp"



namespace hou
{

namespace prv
{

std::string aud_module_impl::get_name()
{
  return u8"audio";
}



bool aud_module_impl::on_initialize()
{
  return true;
}



void aud_module_impl::on_terminate() noexcept
{}

}  // namespace prv

}  // namespace hou
