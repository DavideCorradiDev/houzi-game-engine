// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture2_array.hpp"

#include "hou/cor/assertions.hpp"

#include "hou/mth/math_functions.hpp"

#include <cmath>



namespace hou
{

const vec3u& texture2_array::get_max_size()
{
  static const vec3u max_size(narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_layers()));
  return max_size;
}



positive<uint> texture2_array::get_max_mipmap_level_count(const vec3u& size)
{
  return 1u
    + static_cast<uint>(
        log(static_cast<float>(std::max(size.x(), size.y())), 2));
}



texture2_array::texture2_array(const vec3u& size, texture_format format,
  positive<uint> mipmap_level_count, bool)
  : mipmapped_texture3(
      texture_type::texture2_array, size, format, mipmap_level_count)
{
  HOU_PRECOND(size.x() > 0 && size.x() <= get_max_size().x());
  HOU_PRECOND(size.y() > 0 && size.y() <= get_max_size().y());
  HOU_PRECOND(size.z() > 0 && size.z() <= get_max_size().z());
  HOU_PRECOND(mipmap_level_count <= get_max_mipmap_level_count(size));

  gl::set_texture_storage_3d(get_handle(), mipmap_level_count,
    static_cast<GLenum>(format), size.x(), size.y(), size.z());
}



texture2_array::texture2_array(
  const vec3u& size, texture_format format, positive<uint> mipmap_level_count)
  : texture2_array(size, format, mipmap_level_count, true)
{
  clear();
}



texture2_array::texture2_array(const pixel_view3& pv, texture_format format,
  positive<uint> mipmap_level_count)
  : texture2_array(pv.get_size(), format, mipmap_level_count, true)
{
  set_image(pv);
}

}  // namespace hou
