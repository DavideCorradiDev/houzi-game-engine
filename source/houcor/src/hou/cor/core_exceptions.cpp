// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/core_exceptions.hpp"



namespace hou
{

numeric_overflow::numeric_overflow(const std::string& path, uint line)
  : exception(path, line, "Numeric overflow.")
{}

numeric_underflow::numeric_underflow(const std::string& path, uint line)
  : exception(path, line, "Numeric underflow.")
{}

}  // namespace hou
