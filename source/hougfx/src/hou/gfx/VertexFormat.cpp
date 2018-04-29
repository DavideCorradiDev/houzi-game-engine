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



vertex_format::vertex_format(ptrdiff_t offset, uint stride,
  const span<const vertex_attrib_format>& vertexAttribFormats)
  : m_offset(offset)
  , m_stride(stride)
  , m_vertex_attrib_formats(vertexAttribFormats.begin(), vertexAttribFormats.end())
{
  HOU_EXPECT(m_vertex_attrib_formats.size() <= get_max_attrib_format_count());
}



vertex_format::vertex_format(ptrdiff_t offset, uint stride,
  std::vector<vertex_attrib_format>&& vertexAttribFormats)
  : m_offset(offset)
  , m_stride(stride)
  , m_vertex_attrib_formats(std::move(vertexAttribFormats))
{
  HOU_EXPECT(m_vertex_attrib_formats.size() <= get_max_attrib_format_count());
}



ptrdiff_t vertex_format::get_offset() const
{
  return m_offset;
}



uint vertex_format::get_stride() const
{
  return m_stride;
}



const std::vector<vertex_attrib_format>& vertex_format::get_vertex_attrib_formats()
  const
{
  return m_vertex_attrib_formats;
}



bool operator==(const vertex_format& lhs, const vertex_format& rhs)
{
  return lhs.get_offset() == rhs.get_offset()
    && lhs.get_stride() == rhs.get_stride()
    && lhs.get_vertex_attrib_formats() == rhs.get_vertex_attrib_formats();
}



bool operator!=(const vertex_format& lhs, const vertex_format& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const vertex_format& vf)
{
  return os << "{Offset = " << vf.get_offset() << ", Stride = " << vf.get_stride()
            << ", VertexAttribFormats = " << vf.get_vertex_attrib_formats() << "}";
}

}  // namespace hou
