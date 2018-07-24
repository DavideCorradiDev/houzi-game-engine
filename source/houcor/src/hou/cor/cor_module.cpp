// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/cor_module.hpp"



namespace hou
{

namespace prv
{

std::string cor_module_impl::get_name()
{
  return u8"core";
}



bool cor_module_impl::on_initialize()
{
  return true;
}



void cor_module_impl::on_terminate() noexcept
{}

}  // namespace prv

}  // namespace hou
