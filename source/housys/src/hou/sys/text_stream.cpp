// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/text_stream.hpp"



namespace hou
{

text_stream::text_position text_stream::create_position_object(long value) noexcept
{
  return text_position(value);
}



long text_stream::convert_position_object(text_stream::text_position pos) noexcept
{
  return pos.m_value;
}



const text_stream::text_position text_stream::text_position::start(0u);



text_stream::text_position::text_position(long value) noexcept
  : m_value(value)
{}



bool operator==(text_stream::text_position lhs, text_stream::text_position rhs) noexcept
{
  return lhs.m_value == rhs.m_value;
}



bool operator!=(text_stream::text_position lhs, text_stream::text_position rhs) noexcept
{
  return lhs.m_value != rhs.m_value;
}



std::ostream& operator<<(std::ostream& os, text_stream::text_position p)
{
  return os << p.m_value;
}

}  // namespace hou
