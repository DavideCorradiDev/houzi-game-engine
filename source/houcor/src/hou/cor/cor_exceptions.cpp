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



out_of_range::out_of_range(const std::string& path, uint line)
  : exception(path, line, u8"Index out of range.")
{}



bad_union_access::bad_union_access(const std::string& path, uint line)
  : exception(path, line, u8"Bad union access.")
{}



narrowing_error::narrowing_error(const std::string& path, uint line)
  : exception(path, line, u8"Narrowing type cast.")
{}



invalid_value::invalid_value(const std::string& path, uint line)
  : exception(path, line, u8"Invalid value for a checked variable type.")
{}

}  // namespace hou
