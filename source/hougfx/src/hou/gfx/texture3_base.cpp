// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture3_base.hpp"

#include "hou/gl/gl_functions.hpp"



namespace hou
{

texture3_base::texture3_base(
  texture_type type, const vec3u& size, texture_format format)
  : texture(type, format)
  , m_size(size)
{}



texture3_base::~texture3_base()
{}



const vec3u& texture3_base::get_size() const noexcept
{
  return m_size;
}



size_t texture3_base::get_byte_count() const
{
  return get_sub_texture_byte_count(m_size);
}



size_t texture3_base::get_sub_texture_byte_count(const size_type& size) const
{
  gl::set_unpack_alignment(1u);
  return gl::compute_texture_size_bytes(size.x(), size.y(), size.z(),
    gl::get_texture_external_format_for_internal_format(
      static_cast<GLenum>(get_format())));
}

}  // namespace hou
