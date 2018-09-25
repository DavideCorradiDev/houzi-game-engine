// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture2_base.hpp"

#include "hou/gl/gl_functions.hpp"



namespace hou
{

texture2_base::texture2_base(
  texture_type type, const vec2u& size, texture_format format)
  : texture(type, format)
  , m_size(size)
{}



texture2_base::~texture2_base()
{}



const vec2u& texture2_base::get_size() const noexcept
{
  return m_size;
}



size_t texture2_base::get_byte_count() const
{
  return get_sub_texture_byte_count(m_size);
}



size_t texture2_base::get_sub_texture_byte_count(const size_type& size) const
{
  gl::set_unpack_alignment(1u);
  return gl::compute_texture_size_bytes(size.x(), size.y(), 1u,
    gl::get_texture_external_format_for_internal_format(
      static_cast<GLenum>(get_format())));
}

}  // namespace hou
