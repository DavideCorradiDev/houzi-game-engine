// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/vertex_format.hpp"

#include "hou/gl/gl_vertex_array_handle.hpp"



namespace hou
{

uint vertex_format::get_max_attrib_format_count()
{
  return gl::get_max_vertex_attribs();
}



vertex_format::vertex_format(
  ptrdiff_t offset, uint stride, const span<const vertex_attrib_format>& vafs)
  : m_offset(offset)
  , m_stride(stride)
  , m_vertex_attrib_formats(vafs.begin(), vafs.end())
{
  HOU_PRECOND(m_vertex_attrib_formats.size() <= get_max_attrib_format_count());
}



vertex_format::vertex_format(
  ptrdiff_t offset, uint stride, std::vector<vertex_attrib_format>&& vafs)
  : m_offset(offset)
  , m_stride(stride)
  , m_vertex_attrib_formats(std::move(vafs))
{
  HOU_PRECOND(m_vertex_attrib_formats.size() <= get_max_attrib_format_count());
}



ptrdiff_t vertex_format::get_offset() const noexcept
{
  return m_offset;
}



uint vertex_format::get_stride() const noexcept
{
  return m_stride;
}



const std::vector<vertex_attrib_format>&
  vertex_format::get_vertex_attrib_formats() const noexcept
{
  return m_vertex_attrib_formats;
}



bool operator==(const vertex_format& lhs, const vertex_format& rhs) noexcept
{
  return lhs.get_offset() == rhs.get_offset()
    && lhs.get_stride() == rhs.get_stride()
    && lhs.get_vertex_attrib_formats() == rhs.get_vertex_attrib_formats();
}



bool operator!=(const vertex_format& lhs, const vertex_format& rhs) noexcept
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const vertex_format& vf)
{
  return os << "{offset = " << vf.get_offset()
            << ", stride = " << vf.get_stride()
            << ", vertex_attrib_formats = " << vf.get_vertex_attrib_formats()
            << "}";
}

}  // namespace hou
