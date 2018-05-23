// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture.hpp"

#include "hou/gfx/texture_channel_mapping.hpp"

#include "hou/cor/narrow_cast.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/matrix.hpp"



namespace hou
{

namespace
{

template <texture_type Type>
bool is_texture_size_valid(const typename texture_t<Type>::size_type& s);

template <texture_type Type>
bool is_mipmap_level_count_valid(positive<uint> mipmap_level_count,
  const typename texture_t<Type>::size_type& s);

template <texture_type Type>
positive<uint> get_max_mipmap_level_count_for_size(
  const typename texture_t<Type>::size_type& s);

template <texture_type Type>
uint get_mipmap_relevant_size(const typename texture_t<Type>::size_type& s);

template <size_t dim>
bool element_wise_lower_or_equal(
  const vec<uint, dim>& lhs, const vec<uint, dim>& rhs);

vec1u get_texture1_size(const gl::texture_handle& th, uint mipmap_level);

vec2u get_texture2_size(const gl::texture_handle& th, uint mipmap_level);

vec3u get_texture3_size(const gl::texture_handle& th, uint mipmap_level);

std::array<texture_wrap_mode, 1u> get_texture1_wrap_mode(
  const gl::texture_handle& th);

std::array<texture_wrap_mode, 2u> get_texture2_wrap_mode(
  const gl::texture_handle& th);

std::array<texture_wrap_mode, 3u> get_texture3_wrap_mode(
  const gl::texture_handle& th);

void set_texture1_wrap_mode(
  const gl::texture_handle& th, const std::array<texture_wrap_mode, 1u>& wm);

void set_texture2_wrap_mode(
  const gl::texture_handle& th, const std::array<texture_wrap_mode, 2u>& wm);

void set_texture3_wrap_mode(
  const gl::texture_handle& th, const std::array<texture_wrap_mode, 3u>& wm);



template <texture_type Type>
bool is_texture_size_valid(const typename texture_t<Type>::size_type& s)
{
  using tex = texture_t<Type>;
  typename tex::size_type max_size = tex::get_max_size();
  for(size_t i = 0; i < s.size(); ++i)
  {
    if(s(i) < 1u || s(i) > max_size(i))
    {
      return false;
    }
  }
  return true;
}



template <texture_type Type>
bool is_mipmap_level_count_valid(positive<uint> mipmap_level_count,
  const typename texture_t<Type>::size_type& s)
{
  return mipmap_level_count <= get_max_mipmap_level_count_for_size<Type>(s);
}



template <texture_type Type>
positive<uint> get_max_mipmap_level_count_for_size(
  const typename texture_t<Type>::size_type& s)
{
  return 1u
    + static_cast<uint>(
        log(static_cast<float>(get_mipmap_relevant_size<Type>(s)), 2));
}



template <>
uint get_mipmap_relevant_size<texture_type::texture1>(
  const typename texture_t<texture_type::texture1>::size_type& s)
{
  return s(0);
}



template <>
uint get_mipmap_relevant_size<texture_type::texture1_array>(
  const typename texture_t<texture_type::texture1_array>::size_type& s)
{
  return s(0);
}



template <>
uint get_mipmap_relevant_size<texture_type::texture2>(
  const typename texture_t<texture_type::texture2>::size_type& s)
{
  return std::max(s(0), s(1));
}



template <>
uint get_mipmap_relevant_size<texture_type::texture2_array>(
  const typename texture_t<texture_type::texture2_array>::size_type& s)
{
  return std::max(s(0), s(1));
}



template <>
uint get_mipmap_relevant_size<texture_type::texture3>(
  const typename texture_t<texture_type::texture3>::size_type& s)
{
  return std::max(std::max(s(0), s(1)), s(2));
}



template <>
uint get_mipmap_relevant_size<texture_type::multisample_texture2>(
  const typename texture_t<texture_type::multisample_texture2>::size_type&)
{
  return 1u;
}



template <>
uint get_mipmap_relevant_size<texture_type::multisample_texture2_array>(
  const typename texture_t<
    texture_type::multisample_texture2_array>::size_type&)
{
  return 1u;
}



template <size_t dim>
bool element_wise_lower_or_equal(
  const vec<uint, dim>& lhs, const vec<uint, dim>& rhs)
{
  return std::equal(
    lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::less_equal<uint>());
}



vec1u get_texture1_size(const gl::texture_handle& th, uint mipmap_level)
{
  return vec1u(narrow_cast<uint>(gl::get_texture_width(th, mipmap_level)));
}



vec2u get_texture2_size(const gl::texture_handle& th, uint mipmap_level)
{
  return vec2u(narrow_cast<uint>(gl::get_texture_width(th, mipmap_level)),
    narrow_cast<uint>(gl::get_texture_height(th, mipmap_level)));
}



vec3u get_texture3_size(const gl::texture_handle& th, uint mipmap_level)
{
  return vec3u(narrow_cast<uint>(gl::get_texture_width(th, mipmap_level)),
    narrow_cast<uint>(gl::get_texture_height(th, mipmap_level)),
    narrow_cast<uint>(gl::get_texture_depth(th, mipmap_level)));
}



std::array<texture_wrap_mode, 1u> get_texture1_wrap_mode(
  const gl::texture_handle& th)
{
  return {texture_wrap_mode(get_texture_wrap_mode_s(th))};
}



std::array<texture_wrap_mode, 2u> get_texture2_wrap_mode(
  const gl::texture_handle& th)
{
  return {texture_wrap_mode(get_texture_wrap_mode_s(th)),
    texture_wrap_mode(get_texture_wrap_mode_t(th))};
}



std::array<texture_wrap_mode, 3u> get_texture3_wrap_mode(
  const gl::texture_handle& th)
{
  return {texture_wrap_mode(get_texture_wrap_mode_s(th)),
    texture_wrap_mode(get_texture_wrap_mode_t(th)),
    texture_wrap_mode(get_texture_wrap_mode_r(th))};
}



void set_texture1_wrap_mode(
  const gl::texture_handle& th, const std::array<texture_wrap_mode, 1u>& wm)
{
  set_texture_wrap_mode_s(th, static_cast<GLenum>(wm[0]));
}



void set_texture2_wrap_mode(
  const gl::texture_handle& th, const std::array<texture_wrap_mode, 2u>& wm)
{
  set_texture_wrap_mode_s(th, static_cast<GLenum>(wm[0]));
  set_texture_wrap_mode_t(th, static_cast<GLenum>(wm[1]));
}



void set_texture3_wrap_mode(
  const gl::texture_handle& th, const std::array<texture_wrap_mode, 3u>& wm)
{
  set_texture_wrap_mode_s(th, static_cast<GLenum>(wm[0]));
  set_texture_wrap_mode_t(th, static_cast<GLenum>(wm[1]));
  set_texture_wrap_mode_r(th, static_cast<GLenum>(wm[2]));
}

}  // namespace



void texture::bind(const texture& tex, uint tu)
{
  HOU_PRECOND(tu < get_texture_unit_count());
  gl::bind_texture(tex.m_gl_texture_handle, tu);
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



texture::texture(texture_type type, positive<uint> mipmap_level_count,
  positive<uint> sample_count, bool fixed_sample_locations)
  : m_gl_texture_handle(gl::texture_handle::create(static_cast<GLenum>(type)))
  , m_mipmap_level_count(mipmap_level_count)
  , m_sample_count(sample_count)
  , m_fixed_sample_locations(fixed_sample_locations)
{}



texture::~texture()
{}



const gl::texture_handle& texture::get_handle() const noexcept
{
  return m_gl_texture_handle;
}



bool texture::is_bound(uint tu) const
{
  HOU_PRECOND(tu < get_texture_unit_count());
  return gl::is_texture_bound(m_gl_texture_handle, tu);
}



texture_format texture::get_format() const
{
  return texture_format(gl::get_texture_format(m_gl_texture_handle));
}



positive<uint> texture::get_mipmap_level_count() const
{
  return m_mipmap_level_count;
}



positive<uint> texture::get_sample_count() const
{
  return m_sample_count;
}



bool texture::has_fixed_sample_locations() const
{
  return m_fixed_sample_locations;
}



texture_channel_mapping texture::get_channel_mapping() const
{
  return texture_channel_mapping(
    texture_channel(get_texture_swizzle_r(m_gl_texture_handle)),
    texture_channel(get_texture_swizzle_g(m_gl_texture_handle)),
    texture_channel(get_texture_swizzle_b(m_gl_texture_handle)),
    texture_channel(get_texture_swizzle_a(m_gl_texture_handle)));
}



void texture::setChannelMapping(const texture_channel_mapping& mapping)
{
  set_texture_swizzle_r(
    m_gl_texture_handle, static_cast<GLenum>(mapping.get_r()));
  set_texture_swizzle_g(
    m_gl_texture_handle, static_cast<GLenum>(mapping.get_g()));
  set_texture_swizzle_b(
    m_gl_texture_handle, static_cast<GLenum>(mapping.get_b()));
  set_texture_swizzle_a(
    m_gl_texture_handle, static_cast<GLenum>(mapping.get_a()));
}



uint texture::get_width() const
{
  return narrow_cast<uint>(gl::get_texture_width(m_gl_texture_handle, 0));
}



uint texture::get_height() const
{
  return narrow_cast<uint>(gl::get_texture_height(m_gl_texture_handle, 0));
}



uint texture::get_depth() const
{
  return narrow_cast<uint>(gl::get_texture_depth(m_gl_texture_handle, 0));
}



vec1u texture::get_size1() const
{
  return vec1u(get_width());
}



vec2u texture::get_size2() const
{
  return vec2u(get_width(), get_height());
}



vec3u texture::get_size3() const
{
  return vec3u(get_width(), get_height(), get_depth());
}



template <texture_type Type>
size_t texture_t<Type>::compute_image_buffer_size(
  const size_type& im_size, pixel_format fmt)
{
  HOU_DEV_ASSERT(gl::get_unpack_alignment() == 1u);
  size_t byte_count = 1u;
  for(size_t i = 0; i < im_size.size(); ++i)
  {
    byte_count *= im_size(i);
  }
  return byte_count * get_pixel_format_byte_count(fmt);
}



template <texture_type Type>
GLenum texture_t<Type>::pixel_format_to_gl_pixel_format(pixel_format format)
{
  switch(format)
  {
    case pixel_format::r:
      return GL_RED;
    case pixel_format::rg:
      return GL_RG;
    case pixel_format::rgb:
      return GL_RGB;
    case pixel_format::rgba:
      return GL_RGBA;
    default:
      HOU_UNREACHABLE();
      return GL_RED;
  }
}



template <>
vec1u texture_t<texture_type::texture1>::get_max_size()
{
  return vec1u(narrow_cast<uint>(gl::get_max_texture_size()));
}



template <>
vec2u texture_t<texture_type::texture1_array>::get_max_size()
{
  return vec2u(narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_layers()));
}



template <>
vec2u texture_t<texture_type::texture2>::get_max_size()
{
  return vec2u(narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_size()));
}



template <>
vec3u texture_t<texture_type::texture2_array>::get_max_size()
{
  return vec3u(narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_layers()));
}



template <>
vec3u texture_t<texture_type::texture3>::get_max_size()
{
  return vec3u(narrow_cast<uint>(gl::get_max_3d_texture_size()),
    narrow_cast<uint>(gl::get_max_3d_texture_size()),
    narrow_cast<uint>(gl::get_max_3d_texture_size()));
}



template <>
vec2u texture_t<texture_type::multisample_texture2>::get_max_size()
{
  return vec2u(narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_size()));
}



template <>
vec3u texture_t<texture_type::multisample_texture2_array>::get_max_size()
{
  return vec3u(narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_layers()));
}



template <texture_type Type>
positive<uint> texture_t<Type>::get_max_mipmap_level_count(const size_type& s)
{
  return is_texture_type_mipmapped(Type)
    ? get_max_mipmap_level_count_for_size<Type>(s)
    : positive<uint>(1u);
}



template <texture_type Type>
positive<uint> texture_t<Type>::get_max_sample_count()
{
  return positive<uint>(
    is_texture_type_multisampled(Type) ? gl::get_max_texture_samples() : 1u);
}



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<Type>::clear(const pixel_t<PF>& px)
{
  set_image<PF, Type2, Enable>(image<PF>(get_size(), px));
}



template <>
template <>
texture_t<texture_type::texture1>::texture_t(
  const size_type& s, texture_format format, positive<uint> mipmap_level_count)
  : texture(texture_type::texture1, mipmap_level_count, 1u, true)
{
  HOU_PRECOND(is_texture_size_valid<texture_type::texture1>(s));
  HOU_PRECOND(
    is_mipmap_level_count_valid<texture_type::texture1>(mipmap_level_count, s));
  gl::set_texture_storage_1d(
    get_handle(), mipmap_level_count, static_cast<GLenum>(format), s.x());
  clear(pixel_rgba(0u, 0u, 0u, 0u));
}



template <>
template <>
texture_t<texture_type::texture1_array>::texture_t(
  const size_type& s, texture_format format, positive<uint> mipmap_level_count)
  : texture(texture_type::texture1_array, mipmap_level_count, 1u, true)
{
  HOU_PRECOND(is_texture_size_valid<texture_type::texture1_array>(s));
  HOU_PRECOND(is_mipmap_level_count_valid<texture_type::texture1_array>(
    mipmap_level_count, s));
  gl::set_texture_storage_2d(get_handle(), mipmap_level_count,
    static_cast<GLenum>(format), s.x(), s.y());
  clear(pixel_rgba(0u, 0u, 0u, 0u));
}



template <>
template <>
texture_t<texture_type::texture2>::texture_t(
  const size_type& s, texture_format format, positive<uint> mipmap_level_count)
  : texture(texture_type::texture2, mipmap_level_count, 1u, true)
{
  HOU_PRECOND(is_texture_size_valid<texture_type::texture2>(s));
  HOU_PRECOND(
    is_mipmap_level_count_valid<texture_type::texture2>(mipmap_level_count, s));
  gl::set_texture_storage_2d(get_handle(), mipmap_level_count,
    static_cast<GLenum>(format), s.x(), s.y());
  clear(pixel_rgba(0u, 0u, 0u, 0u));
}



template <>
template <>
texture_t<texture_type::texture2_array>::texture_t(
  const size_type& s, texture_format format, positive<uint> mipmap_level_count)
  : texture(texture_type::texture2_array, mipmap_level_count, 1u, true)
{
  HOU_PRECOND(is_texture_size_valid<texture_type::texture2_array>(s));
  HOU_PRECOND(is_mipmap_level_count_valid<texture_type::texture2_array>(
    mipmap_level_count, s));
  gl::set_texture_storage_3d(get_handle(), mipmap_level_count,
    static_cast<GLenum>(format), s.x(), s.y(), s.z());
  clear(pixel_rgba(0u, 0u, 0u, 0u));
}



template <>
template <>
texture_t<texture_type::texture3>::texture_t(
  const size_type& s, texture_format format, positive<uint> mipmap_level_count)
  : texture(texture_type::texture3, mipmap_level_count, 1u, true)
{
  HOU_PRECOND(is_texture_size_valid<texture_type::texture3>(s));
  HOU_PRECOND(
    is_mipmap_level_count_valid<texture_type::texture3>(mipmap_level_count, s));
  gl::set_texture_storage_3d(get_handle(), mipmap_level_count,
    static_cast<GLenum>(format), s.x(), s.y(), s.z());
  clear(pixel_rgba(0u, 0u, 0u, 0u));
}



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
texture_t<Type>::texture_t(
  const image<PF>& im, texture_format format, positive<uint> mipmap_level_count)
  : texture_t(im.get_size(), format, mipmap_level_count)
{
  set_image<PF, Type2, Enable>(im);
}



template <>
template <>
texture_t<texture_type::multisample_texture2>::texture_t(const size_type& s,
  texture_format format, positive<uint> sample_count,
  bool fixed_sample_locations)
  : texture(texture_type::multisample_texture2, 1u, sample_count,
      fixed_sample_locations)
{
  HOU_PRECOND(is_texture_size_valid<texture_type::multisample_texture2>(s));
  HOU_PRECOND(sample_count <= narrow_cast<uint>(gl::get_max_texture_samples()));
  set_texture_storage_2d_multisample(get_handle(), sample_count,
    static_cast<GLenum>(format), s.x(), s.y(), fixed_sample_locations);
}



template <>
template <>
texture_t<texture_type::multisample_texture2_array>::texture_t(
  const size_type& s, texture_format format, positive<uint> sample_count,
  bool fixed_sample_locations)
  : texture(texture_type::multisample_texture2_array, 1u, sample_count,
      fixed_sample_locations)
{
  HOU_PRECOND(
    is_texture_size_valid<texture_type::multisample_texture2_array>(s));
  HOU_PRECOND(sample_count <= narrow_cast<uint>(gl::get_max_texture_samples()));
  set_texture_storage_3d_multisample(get_handle(), sample_count,
    static_cast<GLenum>(format), s.x(), s.y(), s.z(), fixed_sample_locations);
}



template <>
typename texture_t<texture_type::texture1>::size_type
  texture_t<texture_type::texture1>::get_size() const
{
  return get_size1();
}



template <>
typename texture_t<texture_type::texture1_array>::size_type
  texture_t<texture_type::texture1_array>::get_size() const
{
  return get_size2();
}



template <>
typename texture_t<texture_type::texture2>::size_type
  texture_t<texture_type::texture2>::get_size() const
{
  return get_size2();
}



template <>
typename texture_t<texture_type::texture2_array>::size_type
  texture_t<texture_type::texture2_array>::get_size() const
{
  return get_size3();
}



template <>
typename texture_t<texture_type::texture3>::size_type
  texture_t<texture_type::texture3>::get_size() const
{
  return get_size3();
}



template <>
typename texture_t<texture_type::multisample_texture2>::size_type
  texture_t<texture_type::multisample_texture2>::get_size() const
{
  return get_size2();
}



template <>
typename texture_t<texture_type::multisample_texture2_array>::size_type
  texture_t<texture_type::multisample_texture2_array>::get_size() const
{
  return get_size3();
}



template <texture_type Type>
template <texture_type Type2, typename Enable>
texture_filter texture_t<Type>::get_filter() const
{
  switch(get_texture_min_filter(get_handle()))
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



template <texture_type Type>
template <texture_type Type2, typename Enable>
void texture_t<Type>::set_filter(texture_filter filter)
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



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture1>::wrap_mode
  texture_t<texture_type::texture1>::get_wrap_mode() const
{
  return get_texture1_wrap_mode(get_handle());
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture1_array>::wrap_mode
  texture_t<texture_type::texture1_array>::get_wrap_mode() const
{
  return get_texture2_wrap_mode(get_handle());
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture2>::wrap_mode
  texture_t<texture_type::texture2>::get_wrap_mode() const
{
  return get_texture2_wrap_mode(get_handle());
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture2_array>::wrap_mode
  texture_t<texture_type::texture2_array>::get_wrap_mode() const
{
  return get_texture3_wrap_mode(get_handle());
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture3>::wrap_mode
  texture_t<texture_type::texture3>::get_wrap_mode() const
{
  return get_texture3_wrap_mode(get_handle());
}



template <>
template <texture_type Type2, typename Enable>
void texture_t<texture_type::texture1>::set_wrap_mode(
  const wrap_mode& wrap_mode)
{
  set_texture1_wrap_mode(get_handle(), wrap_mode);
}



template <>
template <texture_type Type2, typename Enable>
void texture_t<texture_type::texture1_array>::set_wrap_mode(
  const wrap_mode& wrap_mode)
{
  set_texture2_wrap_mode(get_handle(), wrap_mode);
}



template <>
template <texture_type Type2, typename Enable>
void texture_t<texture_type::texture2>::set_wrap_mode(
  const wrap_mode& wrap_mode)
{
  set_texture2_wrap_mode(get_handle(), wrap_mode);
}



template <>
template <texture_type Type2, typename Enable>
void texture_t<texture_type::texture2_array>::set_wrap_mode(
  const wrap_mode& wrap_mode)
{
  set_texture3_wrap_mode(get_handle(), wrap_mode);
}



template <>
template <texture_type Type2, typename Enable>
void texture_t<texture_type::texture3>::set_wrap_mode(
  const wrap_mode& wrap_mode)
{
  set_texture3_wrap_mode(get_handle(), wrap_mode);
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
typename texture_t<texture_type::texture1>::template image<PF>
  texture_t<texture_type::texture1>::get_sub_image(
    const offset_type& offset, const size_type& s) const
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + s, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(compute_image_buffer_size(s, PF));
  gl::get_texture_sub_image(get_handle(), offset.x(), 0, 0, s.x(), 1, 1, 0,
    pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<PF>(s,
    reinterpret_span<const typename image<PF>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
typename texture_t<texture_type::texture1_array>::template image<PF>
  texture_t<texture_type::texture1_array>::get_sub_image(
    const offset_type& offset, const size_type& s) const
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + s, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(compute_image_buffer_size(s, PF));
  gl::get_texture_sub_image(get_handle(), offset.x(), offset.y(), 0, s.x(),
    s.y(), 1, 0, pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<PF>(s,
    reinterpret_span<const typename image<PF>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
typename texture_t<texture_type::texture2>::template image<PF>
  texture_t<texture_type::texture2>::get_sub_image(
    const offset_type& offset, const size_type& s) const
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + s, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(compute_image_buffer_size(s, PF));
  gl::get_texture_sub_image(get_handle(), offset.x(), offset.y(), 0, s.x(),
    s.y(), 1, 0, pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<PF>(s,
    reinterpret_span<const typename image<PF>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
typename texture_t<texture_type::texture2_array>::template image<PF>
  texture_t<texture_type::texture2_array>::get_sub_image(
    const offset_type& offset, const size_type& s) const
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + s, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(compute_image_buffer_size(s, PF));
  gl::get_texture_sub_image(get_handle(), offset.x(), offset.y(), offset.z(),
    s.x(), s.y(), s.z(), 0, pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<PF>(s,
    reinterpret_span<const typename image<PF>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
typename texture_t<texture_type::texture3>::template image<PF>
  texture_t<texture_type::texture3>::get_sub_image(
    const offset_type& offset, const size_type& s) const
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + s, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(compute_image_buffer_size(s, PF));
  gl::get_texture_sub_image(get_handle(), offset.x(), offset.y(), offset.z(),
    s.x(), s.y(), s.z(), 0, pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<PF>(s,
    reinterpret_span<const typename image<PF>::pixel>(span<uint8_t>(buffer)));
}



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<Type>::set_image(const image<PF>& im)
{
  HOU_PRECOND(im.get_size() == get_size());
  set_sub_image<PF, Type2, Enable>(offset_type::zero(), im);
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<texture_type::texture1>::set_sub_image(
  const offset_type& offset, const image<PF>& im)
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + im.get_size(), get_size()));
  gl::set_texture_sub_image_1d(get_handle(), 0u, offset.x(), im.get_size().x(),
    pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(im.get_pixels().data()));
  generate_mip_map();
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<texture_type::texture1_array>::set_sub_image(
  const offset_type& offset, const image<PF>& im)
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + im.get_size(), get_size()));
  gl::set_texture_sub_image_2d(get_handle(), 0, offset.x(), offset.y(),
    im.get_size().x(), im.get_size().y(), pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(im.get_pixels().data()));
  generate_mip_map();
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<texture_type::texture2>::set_sub_image(
  const offset_type& offset, const image<PF>& im)
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + im.get_size(), get_size()));
  gl::set_texture_sub_image_2d(get_handle(), 0, offset.x(), offset.y(),
    im.get_size().x(), im.get_size().y(), pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(im.get_pixels().data()));
  generate_mip_map();
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<texture_type::texture2_array>::set_sub_image(
  const offset_type& offset, const image<PF>& im)
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + im.get_size(), get_size()));
  gl::set_texture_sub_image_3d(get_handle(), 0, offset.x(), offset.y(),
    offset.z(), im.get_size().x(), im.get_size().y(), im.get_size().z(),
    pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(im.get_pixels().data()));
  generate_mip_map();
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<texture_type::texture3>::set_sub_image(
  const offset_type& offset, const image<PF>& im)
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + im.get_size(), get_size()));
  gl::set_texture_sub_image_3d(get_handle(), 0, offset.x(), offset.y(),
    offset.z(), im.get_size().x(), im.get_size().y(), im.get_size().z(),
    pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(im.get_pixels().data()));
  generate_mip_map();
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture1>::size_type
  texture_t<texture_type::texture1>::get_mipmap_size(uint mipmap_level) const
{
  HOU_PRECOND(mipmap_level < get_mipmap_level_count());
  return get_texture1_size(get_handle(), mipmap_level);
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture1_array>::size_type
  texture_t<texture_type::texture1_array>::get_mipmap_size(
    uint mipmap_level) const
{
  HOU_PRECOND(mipmap_level < get_mipmap_level_count());
  return get_texture2_size(get_handle(), mipmap_level);
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture2>::size_type
  texture_t<texture_type::texture2>::get_mipmap_size(uint mipmap_level) const
{
  HOU_PRECOND(mipmap_level < get_mipmap_level_count());
  return get_texture2_size(get_handle(), mipmap_level);
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture2_array>::size_type
  texture_t<texture_type::texture2_array>::get_mipmap_size(
    uint mipmap_level) const
{
  HOU_PRECOND(mipmap_level < get_mipmap_level_count());
  return get_texture3_size(get_handle(), mipmap_level);
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture3>::size_type
  texture_t<texture_type::texture3>::get_mipmap_size(uint mipmap_level) const
{
  HOU_PRECOND(mipmap_level < get_mipmap_level_count());
  return get_texture3_size(get_handle(), mipmap_level);
}



template <texture_type Type>
texture_type texture_t<Type>::get_type() const
{
  return Type;
}



template <texture_type Type>
size_t texture_t<Type>::get_dimension_count() const
{
  return get_texture_type_dimension_count(Type);
}



template <texture_type Type>
bool texture_t<Type>::is_mipmapped() const
{
  return is_texture_type_mipmapped(Type);
}



template <texture_type Type>
bool texture_t<Type>::is_multisampled() const
{
  return is_texture_type_multisampled(Type);
}



template <texture_type Type>
void texture_t<Type>::generate_mip_map()
{
  if(get_mipmap_level_count() > 1u)
  {
    gl::generate_mip_map(get_handle());
  }
}



template class HOU_GFX_API texture_t<texture_type::texture1>;
template class HOU_GFX_API texture_t<texture_type::texture1_array>;
template class HOU_GFX_API texture_t<texture_type::texture2>;
template class HOU_GFX_API texture_t<texture_type::texture2_array>;
template class HOU_GFX_API texture_t<texture_type::texture3>;
template class HOU_GFX_API texture_t<texture_type::multisample_texture2>;
template class HOU_GFX_API texture_t<texture_type::multisample_texture2_array>;

}  // namespace hou
