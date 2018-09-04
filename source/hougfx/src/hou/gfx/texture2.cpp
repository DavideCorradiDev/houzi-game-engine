// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture2.hpp"

#include "hou/cor/assertions.hpp"

#include "hou/gl/gl_functions.hpp"

#include "hou/mth/math_functions.hpp"

#include <cmath>



namespace hou
{

const vec2u& texture2::get_max_size()
{
  static const vec2u max_size(narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_size()));
  return max_size;
}



positive<uint> texture2::get_max_mipmap_level_count(const vec2u& size)
{
  return 1u
    + static_cast<uint>(
        log(static_cast<float>(std::max(size.x(), size.y())), 2));
}



texture2::texture2(const vec2u& size, texture_format format,
  positive<uint> mipmap_level_count, bool)
  : texture2_base(texture_type::texture2, size, format)
  , m_mipmap_level_count(mipmap_level_count)
{
  HOU_PRECOND(size.x() > 0 && size.x() <= get_max_size().x());
  HOU_PRECOND(size.y() > 0 && size.y() <= get_max_size().y());
  HOU_PRECOND(mipmap_level_count <= get_max_mipmap_level_count(size));

  gl::set_texture_storage_2d(get_handle(), mipmap_level_count,
    static_cast<GLenum>(format), size.x(), size.y());
}



texture2::texture2(const pixel_view2& pv, texture_format format,
  positive<uint> mipmap_level_count)
  : texture2(pv.get_size(), format, mipmap_level_count, true)
{
  set_image(pv);
}



texture2::texture2(
  const vec2u& size, texture_format format, positive<uint> mipmap_level_count)
  : texture2(size, format, mipmap_level_count, true)
{
  clear();
}



texture_filter texture2::get_filter() const
{
  return get_filter_internal();
}



void texture2::set_filter(texture_filter filter)
{
  set_filter_internal(filter);
}



positive<uint> texture2::get_mipmap_level_count() const
{
  return m_mipmap_level_count;
}



positive<uint> texture2::get_sample_count() const
{
  return 1u;
}



bool texture2::is_mipmapped() const
{
  return true;
}



bool texture2::is_multisampled() const
{
  return false;
}



texture2::wrap_mode texture2::get_wrap_mode() const
{
  return {texture_wrap_mode(gl::get_texture_wrap_mode_s(get_handle())),
    texture_wrap_mode(gl::get_texture_wrap_mode_t(get_handle()))};
}



void texture2::set_wrap_mode(const wrap_mode& wm)
{
  gl::set_texture_wrap_mode_s(get_handle(), static_cast<GLenum>(wm[0]));
  gl::set_texture_wrap_mode_t(get_handle(), static_cast<GLenum>(wm[1]));
}



std::vector<uint8_t> texture2::get_image() const
{
  return get_sub_image(vec2u::zero(), get_size());
}



std::vector<uint8_t> texture2::get_sub_image(
  const vec2u& offset, const vec2u& size) const
{
  vec2u bounds = offset + size;
  HOU_PRECOND(std::equal(bounds.begin(), bounds.end(), get_size().begin(),
    get_size().end(), std::less_equal<uint>()));

  gl::set_unpack_alignment(1u);
  std::vector<uint8_t> buffer(
    gl::compute_texture_size_bytes(size.x(), size.y(), 1u,
      gl::get_texture_external_format_for_internal_format(
        static_cast<GLenum>(get_format()))),
    0u);

  // clang-format off
  gl::get_texture_sub_image(get_handle(),
    offset.x(), offset.y(), 0,                            // offset
    size.x(), size.y(), 1,                                // size
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



void texture2::set_image(const pixel_view2& pv)
{
  set_sub_image(vec2u::zero(), pv);
}



void texture2::set_sub_image(const vec2u& offset, const pixel_view2& pv)
{
  HOU_PRECOND(pv.get_bytes_per_pixel() == get_bytes_per_pixel(get_format()));

  vec2u bounds = offset + pv.get_size();
  HOU_PRECOND(std::equal(bounds.begin(), bounds.end(), get_size().begin(),
    get_size().end(), std::less_equal<uint>()));

  // clang-format off
  gl::set_texture_sub_image_2d(get_handle(),
    0,                                                    // level
    offset.x(), offset.y(),                               // offset
    pv.get_size().x(), pv.get_size().y(),                 // size
    gl::get_texture_external_format_for_internal_format(
      static_cast<GLenum>(get_format())),                 // external format
    gl::get_texture_data_type_for_internal_format(
      static_cast<GLenum>(get_format())),                 // data type
    reinterpret_cast<const void*>(pv.get_data()));        // data
  // clang-format on

  gl::generate_mip_map(get_handle());
}



void texture2::clear()
{
  gl::reset_texture_sub_image_2d(get_handle(), 0, 0, 0, get_size().x(),
    get_size().y(), static_cast<GLenum>(get_format()));
  gl::generate_mip_map(get_handle());
}

}  // namespace hou
