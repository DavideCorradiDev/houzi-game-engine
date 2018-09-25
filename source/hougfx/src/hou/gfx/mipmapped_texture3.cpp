// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/mipmapped_texture3.hpp"

#include "hou/cor/assertions.hpp"

#include "hou/gl/gl_functions.hpp"



namespace hou
{

mipmapped_texture3::mipmapped_texture3(texture_type type, const vec3u& size,
  texture_format format, positive<uint> mipmap_level_count)
  : texture3_base(type, size, format)
  , m_mipmap_level_count(mipmap_level_count)
{}



mipmapped_texture3::~mipmapped_texture3()
{}



texture_filter mipmapped_texture3::get_filter() const
{
  return get_filter_internal();
}



void mipmapped_texture3::set_filter(texture_filter filter)
{
  set_filter_internal(filter);
}



mipmapped_texture3::wrap_mode mipmapped_texture3::get_wrap_mode() const
{
  return {texture_wrap_mode(gl::get_texture_wrap_mode_s(get_handle())),
    texture_wrap_mode(gl::get_texture_wrap_mode_t(get_handle())),
    texture_wrap_mode(gl::get_texture_wrap_mode_r(get_handle()))};
}



void mipmapped_texture3::set_wrap_mode(const wrap_mode& wm)
{
  gl::set_texture_wrap_mode_s(get_handle(), static_cast<GLenum>(wm[0]));
  gl::set_texture_wrap_mode_t(get_handle(), static_cast<GLenum>(wm[1]));
  gl::set_texture_wrap_mode_r(get_handle(), static_cast<GLenum>(wm[2]));
}


std::vector<uint8_t> mipmapped_texture3::get_pixels() const
{
  return get_sub_pixels(vec3u::zero(), get_size());
}



std::vector<uint8_t> mipmapped_texture3::get_sub_pixels(
  const vec3u& offset, const vec3u& size) const
{
  vec3u bounds = offset + size;
  HOU_PRECOND(std::equal(bounds.begin(), bounds.end(), get_size().begin(),
    get_size().end(), std::less_equal<uint>()));

  std::vector<uint8_t> buffer(get_sub_texture_byte_count(size), 0u);
  // clang-format off
  gl::get_texture_sub_image(get_handle(),
    offset.x(), offset.y(), offset.z(),                   // offset
    size.x(), size.y(), size.z(),                         // size
    0,                                                    // level
    gl::get_texture_external_format_for_internal_format(
      static_cast<GLenum>(get_format())),                 // external format
    gl::get_texture_data_type_for_internal_format(
      static_cast<GLenum>(get_format())),                 // data type
    narrow_cast<GLsizei>(buffer.size()),                  // data size
    buffer.data());                                       // data
  // clang-format on

  return buffer;
}



void mipmapped_texture3::set_pixels(const span<const uint8_t>& pixels)
{
  set_sub_pixels(vec3u::zero(), get_size(), pixels);
}



void mipmapped_texture3::set_sub_pixels(
  const vec3u& offset, const vec3u& size, const span<const uint8_t>& pixels)
{
  HOU_PRECOND(pixels.size() == get_sub_texture_byte_count(size));
  vec3u bounds = offset + size;
  HOU_PRECOND(std::equal(bounds.begin(), bounds.end(), get_size().begin(),
    get_size().end(), std::less_equal<uint>()));

  // clang-format off
  gl::set_texture_sub_image_3d(get_handle(),
    0,                                                        // level
    offset.x(), offset.y(), offset.z(),                       // offset
    size.x(), size.y(), size.z(),                             // size
    gl::get_texture_external_format_for_internal_format(
      static_cast<GLenum>(get_format())),                     // external format
    gl::get_texture_data_type_for_internal_format(
      static_cast<GLenum>(get_format())),                     // data type
    reinterpret_cast<const void*>(pixels.data()));            // data
  // clang-format on

  gl::generate_mip_map(get_handle());
}



void mipmapped_texture3::set_image(const pixel_view3& pv)
{
  HOU_PRECOND(pv.get_size() == get_size());
  set_sub_image(vec3u::zero(), pv);
}



void mipmapped_texture3::set_sub_image(
  const vec3u& offset, const pixel_view3& pv)
{
  set_sub_pixels(offset, pv.get_size(),
    span<const uint8_t>(pv.get_data(), pv.get_byte_count()));
}



void mipmapped_texture3::clear()
{
  gl::reset_texture_sub_image_3d(get_handle(), 0, 0, 0, 0, get_size().x(),
    get_size().y(), get_size().z(), static_cast<GLenum>(get_format()));
  gl::generate_mip_map(get_handle());
}



positive<uint> mipmapped_texture3::get_mipmap_level_count() const
{
  return m_mipmap_level_count;
}



positive<uint> mipmapped_texture3::get_sample_count() const
{
  return 1u;
}



bool mipmapped_texture3::is_mipmapped() const
{
  return true;
}



bool mipmapped_texture3::is_multisampled() const
{
  return false;
}

}  // namespace hou
