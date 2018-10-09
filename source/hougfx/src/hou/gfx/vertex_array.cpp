// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/vertex_array.hpp"

#include "hou/gfx/vertex_buffer.hpp"
#include "hou/gfx/vertex_format.hpp"

#include "hou/cor/narrow_cast.hpp"



namespace hou
{

void vertex_array::bind(const vertex_array& va)
{
  gl::bind_vertex_array(va.m_handle);
}



void vertex_array::unbind()
{
  gl::unbind_vertex_array();
}



uint vertex_array::get_max_binding_index()
{
  return gl::get_max_vertex_attrib_bindings() - 1u;
}



vertex_array::vertex_array()
  : non_copyable()
  , m_handle(gl::vertex_array_handle::create())
{}



const gl::vertex_array_handle& vertex_array::get_handle() const noexcept
{
  return m_handle;
}



bool vertex_array::is_bound() const
{
  return gl::is_vertex_array_bound(m_handle);
}




#if defined(HOU_GL_ES)

void vertex_array::set_vertex_data(
  const vertex_buffer& vb, uint binding_index, const vertex_format& vf)
{
  HOU_PRECOND(binding_index <= get_max_binding_index());

  gl::bind_vertex_array(m_handle);
  gl::bind_buffer(vb.get_handle(), GL_ARRAY_BUFFER);

  const std::vector<vertex_attrib_format>& vafs
    = vf.get_vertex_attrib_formats();
  for(GLuint i = 0; i < vafs.size(); ++i)
  {
    gl::set_vertex_attrib_pointer(i,
      narrow_cast<GLint>(vafs[i].get_element_count()),
      static_cast<GLenum>(vafs[i].get_type()),
      vafs[i].must_be_normalized() ? GL_TRUE : GL_FALSE,
      narrow_cast<GLsizei>(vf.get_stride())
        * get_gl_type_byte_size(vafs[i].get_type()),
      reinterpret_cast<GLvoid*>(
        (vf.get_byte_offset() + vafs[i].get_byte_offset())
        * get_gl_type_byte_size(vafs[i].get_type())));
    gl::enable_vertex_array_attrib(i);
  }
}



void vertex_array::set_element_data(const vertex_buffer& eb)
{
  gl::bind_vertex_array(m_handle);
  gl::bind_buffer(eb.get_handle(), GL_ELEMENT_ARRAY_BUFFER);
}

#else

void vertex_array::set_vertex_data(
  const vertex_buffer& vb, uint binding_index, const vertex_format& vf)
{
  HOU_PRECOND(binding_index <= get_max_binding_index());

  gl::set_vertex_array_vertex_buffer(m_handle,
    narrow_cast<GLuint>(binding_index), vb.get_handle(),
    narrow_cast<GLintptr>(vf.get_byte_offset()),
    narrow_cast<GLsizei>(vf.get_stride()));

  const std::vector<vertex_attrib_format>& vafs
    = vf.get_vertex_attrib_formats();
  for(GLuint i = 0; i < vafs.size(); ++i)
  {
    gl::set_vertex_array_attrib_format(m_handle, i,
      narrow_cast<GLint>(vafs[i].get_element_count()),
      static_cast<GLenum>(vafs[i].get_type()),
      vafs[i].must_be_normalized() ? GL_TRUE : GL_FALSE,
      narrow_cast<GLuint>(vafs[i].get_byte_offset()));
    gl::set_vertex_array_attrib_binding(
      m_handle, narrow_cast<GLuint>(i), narrow_cast<GLuint>(binding_index));
    gl::enable_vertex_array_attrib(m_handle, i);
  }
}



void vertex_array::set_element_data(const vertex_buffer& eb)
{
  gl::set_vertex_array_element_buffer(m_handle, eb.get_handle());
}

#endif

}  // namespace hou
