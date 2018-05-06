// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/cor_exceptions.hpp"



namespace hou
{

overflow_error::overflow_error(const std::string& path, uint line)
  : exception(path, line, u8"Numeric overflow.")
{}



underflow_error::underflow_error(const std::string& path, uint line)
  : exception(path, line, u8"Numeric underflow.")
{}



unreachable_code_error::unreachable_code_error(const std::string& path, uint line)
  : exception(path, line, u8"An unreachable part of code has been reached.")
{}

}  // namespace hou
