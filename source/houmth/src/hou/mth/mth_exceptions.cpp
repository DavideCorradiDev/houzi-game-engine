// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/mth_exceptions.hpp"



namespace hou
{

inversion_error::inversion_error(const std::string& path, uint line)
  : exception(path, line, u8"The object is not invertible.")
{}

}  // namespace hou
