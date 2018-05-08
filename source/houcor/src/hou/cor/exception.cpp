// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/exception.hpp"

#include "hou/cor/std_string.hpp"

#include <iostream>



namespace hou
{

namespace
{
#if defined(HOU_SYSTEM_WINDOWS)
constexpr char path_separator = '\\';
#else
constexpr char path_separator = '/';
#endif


}  // namespace



namespace prv
{

std::string format_error_message(
  const std::string& path, uint line, const std::string& message)
{
  std::stringstream ss;
  ss << path.substr(path.find_last_of(path_separator) + 1) << ':' << line
     << " - " << message;
  return ss.str();
}



std::string assertion_message(const std::string& statement)
{
  return format_string(u8"Assertion failed (%s).", statement.c_str());
}

}



exception::exception(
  const std::string& path, uint line, const std::string& message)
  : std::exception()
  , m_message(std::make_shared<std::string>(
      prv::format_error_message(path, line, message)))
{}



const char* exception::what() const noexcept
{
  return m_message->c_str();
}



void terminate(const std::string& message) noexcept
{
  std::cerr << message << std::endl;
  std::terminate();
}

}  // namespace hou
