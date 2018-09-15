// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/multisampled_texture2.hpp"



namespace hou
{

const vec2u& multisampled_texture2::get_max_size()
{
  static const vec2u max_size(narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_size()));
  return max_size;
}



positive<uint> multisampled_texture2::get_max_sample_count()
{
  return gl::get_max_texture_samples();
}



multisampled_texture2::multisampled_texture2(const vec2u& size,
  texture_format format, positive<uint> sample_count,
  bool fixed_sample_locations)
  : texture2_base(texture_type::multisampled_texture2, size, format)
  , m_sample_count(sample_count)
  , m_fixed_sample_locations(fixed_sample_locations)
{
  HOU_PRECOND(size.x() > 0 && size.x() <= get_max_size().x());
  HOU_PRECOND(size.y() > 0 && size.y() <= get_max_size().y());
  HOU_PRECOND(sample_count <= get_max_sample_count());

  gl::set_texture_storage_2d_multisample(get_handle(), sample_count,
    static_cast<GLenum>(format), size.x(), size.y(), fixed_sample_locations);
}



bool multisampled_texture2::has_fixed_sample_locations() const noexcept
{
  return m_fixed_sample_locations;
}



positive<uint> multisampled_texture2::get_mipmap_level_count() const
{
  return 1u;
}



positive<uint> multisampled_texture2::get_sample_count() const
{
  return m_sample_count;
}



bool multisampled_texture2::is_mipmapped() const
{
  return false;
}



bool multisampled_texture2::is_multisampled() const
{
  return true;
}

}  // namespace hou
