// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/vertex_attrib_format.hpp"

#include "hou/cor/std_string.hpp"



namespace hou
{

vertex_attrib_format::vertex_attrib_format(gl_type type, uint element_count,
  uint byte_offset, bool must_be_normalized) noexcept
  : m_type(type)
  , m_element_count(element_count)
  , m_byte_offset(byte_offset)
  , m_must_be_normalized(must_be_normalized)
{}



gl_type vertex_attrib_format::get_type() const noexcept
{
  return m_type;
}



uint vertex_attrib_format::get_element_count() const noexcept
{
  return m_element_count;
}



uint vertex_attrib_format::get_byte_offset() const noexcept
{
  return m_byte_offset;
}



bool vertex_attrib_format::must_be_normalized() const noexcept
{
  return m_must_be_normalized;
}



bool operator==(
  const vertex_attrib_format& lhs, const vertex_attrib_format& rhs) noexcept
{
  return lhs.get_type() == rhs.get_type()
    && lhs.get_element_count() == rhs.get_element_count()
    && lhs.get_byte_offset() == rhs.get_byte_offset()
    && lhs.must_be_normalized() == rhs.must_be_normalized();
}



bool operator!=(
  const vertex_attrib_format& lhs, const vertex_attrib_format& rhs) noexcept
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const vertex_attrib_format& vf)
{
  return os << "{type = " << vf.get_type()
            << ", element_count = " << vf.get_element_count()
            << ", byte_offset = " << vf.get_byte_offset()
            << ", must_be_normalized = " << to_string(vf.must_be_normalized())
            << "}";
}

}  // namespace hou
