// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/exception.hpp"

#include "hou/cor/std_string.hpp"



namespace hou
{

const std::string exception::what_msg
  = u8"A generic error has been encountered.";



exception::exception(const filename_type& filename, uint line) noexcept
  : std::exception()
  , m_filename(filename)
  , m_line(line)
{}



const char* exception::what() const noexcept
{
  return what_msg.c_str();
}



std::string exception::message() const
{
  return format_string("%s:%d - ", m_filename, m_line) + message_extension();
}



std::string exception::message_extension() const
{
  return what_msg;
}

}  // namespace hou
