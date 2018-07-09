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



module_initialization_error::module_initialization_error(
  const std::string& path, uint line, const std::string& module_name)
  : exception(path, line,
      format_string(
        u8"Failed to initialize the %s module.", module_name.c_str()))
{}



unsupported_error::unsupported_error(
  const std::string& path, uint line, const std::string& details)
  : exception(
      path, line, format_string(u8"Unsupported feature. %s", details.c_str()))
{}

}  // namespace hou
