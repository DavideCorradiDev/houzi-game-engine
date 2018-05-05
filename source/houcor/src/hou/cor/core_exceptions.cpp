// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/core_exceptions.hpp"



namespace hou
{

overflow_error::overflow_error(const std::string& path, uint line)
  : exception(path, line, "Numeric overflow.")
{}



underflow_error::underflow_error(const std::string& path, uint line)
  : exception(path, line, "Numeric underflow.")
{}

}  // namespace hou
