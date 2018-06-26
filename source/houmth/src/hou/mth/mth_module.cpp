// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/mth_module.hpp"



namespace hou
{

namespace prv
{

std::string mth_module_impl::get_name()
{
  return u8"math";
}



bool mth_module_impl::on_initialize()
{
  return true;
}



void mth_module_impl::on_terminate() noexcept
{}

}  // namespace prv

}  // namespace hou
