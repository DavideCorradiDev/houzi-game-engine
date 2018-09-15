// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture.hpp"

#include "hou/cor/assertions.hpp"



namespace hou
{

void texture::bind(const texture& tex, uint tu)
{
  HOU_PRECOND(tu < get_texture_unit_count());
  gl::bind_texture(tex.m_handle, tu);
}



void texture::unbind(uint tu)
{
  HOU_PRECOND(tu < get_texture_unit_count());
  gl::unbind_texture(tu);
}



uint texture::get_texture_unit_count()
{
  return narrow_cast<uint>(gl::get_max_texture_image_units());
}



texture::texture(texture_type type, texture_format format)
  : m_handle(gl::texture_handle::create(static_cast<GLenum>(type)))
  , m_type(type)
  , m_format(format)
{}



texture::~texture()
{}



const gl::texture_handle& texture::get_handle() const noexcept
{
  return m_handle;
}



texture_type texture::get_type() const noexcept
{
  return m_type;
}



texture_format texture::get_format() const noexcept
{
  return m_format;
}



texture_channel_mapping texture::get_channel_mapping() const
{
  return texture_channel_mapping(
    texture_channel(get_texture_swizzle_r(m_handle)),
    texture_channel(get_texture_swizzle_g(m_handle)),
    texture_channel(get_texture_swizzle_b(m_handle)),
    texture_channel(get_texture_swizzle_a(m_handle)));
}



void texture::set_channel_mapping(const texture_channel_mapping& mapping)
{
  set_texture_swizzle_r(m_handle, static_cast<GLenum>(mapping.get_r()));
  set_texture_swizzle_g(m_handle, static_cast<GLenum>(mapping.get_g()));
  set_texture_swizzle_b(m_handle, static_cast<GLenum>(mapping.get_b()));
  set_texture_swizzle_a(m_handle, static_cast<GLenum>(mapping.get_a()));
}



bool texture::is_bound(uint tu) const
{
  HOU_PRECOND(tu < get_texture_unit_count());
  return gl::is_texture_bound(m_handle, tu);
}



texture_filter texture::get_filter_internal() const
{
  switch(gl::get_texture_min_filter(get_handle()))
  {
    case GL_NEAREST_MIPMAP_NEAREST:
      return texture_filter::nearest;
    case GL_NEAREST_MIPMAP_LINEAR:
      return texture_filter::linear;
    case GL_LINEAR_MIPMAP_NEAREST:
      return texture_filter::bilinear;
    case GL_LINEAR_MIPMAP_LINEAR:
      return texture_filter::trilinear;
    default:
      HOU_UNREACHABLE();
      return texture_filter::nearest;
  }
}



void texture::set_filter_internal(texture_filter filter)
{
  switch(filter)
  {
    case texture_filter::nearest:
      set_texture_min_filter(get_handle(), GL_NEAREST_MIPMAP_NEAREST);
      set_texture_mag_filter(get_handle(), GL_NEAREST);
      break;
    case texture_filter::linear:
      set_texture_min_filter(get_handle(), GL_NEAREST_MIPMAP_LINEAR);
      set_texture_mag_filter(get_handle(), GL_NEAREST);
      break;
    case texture_filter::bilinear:
      set_texture_min_filter(get_handle(), GL_LINEAR_MIPMAP_NEAREST);
      set_texture_mag_filter(get_handle(), GL_LINEAR);
      break;
    case texture_filter::trilinear:
      set_texture_min_filter(get_handle(), GL_LINEAR_MIPMAP_LINEAR);
      set_texture_mag_filter(get_handle(), GL_LINEAR);
      break;
    default:
      HOU_UNREACHABLE();
      break;
  }
}

}  // namespace hou
