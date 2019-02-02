// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/multisampled_texture2_array.hpp"



namespace hou
{

const vec3u& multisampled_texture2_array::get_max_size()
{
  static const vec3u max_size(narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_layers()));
  return max_size;
}



positive<uint> multisampled_texture2_array::get_max_sample_count()
{
  return gl::get_max_texture_samples();
}



multisampled_texture2_array::multisampled_texture2_array(const vec3u& size,
  texture_format format, positive<uint> sample_count,
  bool fixed_sample_locations)
  : texture3_base(texture_type::multisampled_texture2_array, size, format)
  , m_sample_count(sample_count)
  , m_fixed_sample_locations(fixed_sample_locations)
{
  HOU_PRECOND(size.x() > 0 && size.x() <= get_max_size().x());
  HOU_PRECOND(size.y() > 0 && size.y() <= get_max_size().y());
  HOU_PRECOND(size.z() > 0 && size.z() <= get_max_size().z());
  HOU_PRECOND(sample_count <= get_max_sample_count());

  gl::set_texture_storage_3d_multisample(get_handle(), sample_count,
    static_cast<GLenum>(format), size.x(), size.y(), size.z(),
    fixed_sample_locations);
}



bool multisampled_texture2_array::has_fixed_sample_locations() const noexcept
{
  return m_fixed_sample_locations;
}



positive<uint> multisampled_texture2_array::get_mipmap_level_count() const
{
  return 1u;
}



positive<uint> multisampled_texture2_array::get_sample_count() const
{
  return m_sample_count;
}



bool multisampled_texture2_array::is_mipmapped() const
{
  return false;
}



bool multisampled_texture2_array::is_multisampled() const
{
  return true;
}

}  // namespace hou
