// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/matrix.hpp"

#include "hou/gfx/gl_type.hpp"
#include "hou/gfx/texture_channel_mapping.hpp"



namespace hou
{

namespace
{

GLenum pixel_format_to_gl_pixel_format(pixel_format format);

template <texture_type Type>
bool is_texture_size_valid(const typename texture_t<Type>::size_type& size);

template <texture_type Type>
bool is_mipmap_level_count_valid(
  uint mipmap_level_count, const typename texture_t<Type>::size_type& size);

template <texture_type Type>
uint get_max_mipmap_level_count_for_size(
  const typename texture_t<Type>::size_type& size);

template <texture_type Type>
uint get_mipmap_relevant_size(const typename texture_t<Type>::size_type& size);

template <size_t dim>
size_t compute_image_buffer_size(
  const vec<uint, dim>& imSize, pixel_format fmt);

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



GLenum pixel_format_to_gl_pixel_format(pixel_format format)
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
      return GL_RED;
  }
}



template <texture_type Type>
bool is_texture_size_valid(const typename texture_t<Type>::size_type& size)
{
  using tex = texture_t<Type>;
  typename tex::size_type max_size = tex::get_max_size();
  for(size_t i = 0; i < size.get_size(); ++i)
  {
    if(size(i) < 1u || size(i) > max_size(i))
    {
      return false;
    }
  }
  return true;
}



template <texture_type Type>
bool is_mipmap_level_count_valid(
  uint mipmap_level_count, const typename texture_t<Type>::size_type& size)
{
  return mipmap_level_count > 0
    && mipmap_level_count <= get_max_mipmap_level_count_for_size<Type>(size);
}



template <texture_type Type>
uint get_max_mipmap_level_count_for_size(
  const typename texture_t<Type>::size_type& size)
{
  return 1u
    + static_cast<uint>(
        log(static_cast<float>(get_mipmap_relevant_size<Type>(size)), 2));
}



template <>
uint get_mipmap_relevant_size<texture_type::texture1>(
  const typename texture_t<texture_type::texture1>::size_type& size)
{
  return size(0);
}



template <>
uint get_mipmap_relevant_size<texture_type::texture1_array>(
  const typename texture_t<texture_type::texture1_array>::size_type& size)
{
  return size(0);
}



template <>
uint get_mipmap_relevant_size<texture_type::texture2>(
  const typename texture_t<texture_type::texture2>::size_type& size)
{
  return std::max(size(0), size(1));
}



template <>
uint get_mipmap_relevant_size<texture_type::texture2_array>(
  const typename texture_t<texture_type::texture2_array>::size_type& size)
{
  return std::max(size(0), size(1));
}



template <>
uint get_mipmap_relevant_size<texture_type::texture3>(
  const typename texture_t<texture_type::texture3>::size_type& size)
{
  return std::max(std::max(size(0), size(1)), size(2));
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
size_t compute_image_buffer_size(const vec<uint, dim>& imSize, pixel_format fmt)
{
  HOU_EXPECT_DEV(gl::get_unpack_alignment() == 1u);
  size_t byte_count = 1u;
  for(size_t i = 0; i < imSize.get_size(); ++i)
  {
    byte_count *= imSize(i);
  }
  return byte_count * get_pixel_format_byte_count(fmt);
}



template <size_t dim>
bool element_wise_lower_or_equal(
  const vec<uint, dim>& lhs, const vec<uint, dim>& rhs)
{
  for(size_t i = 0; i < dim; ++i)
  {
    if(lhs(i) > rhs(i))
    {
      return false;
    }
  }
  return true;
}



vec1u get_texture1_size(const gl::texture_handle& th, uint mipmap_level)
{
  return vec1u(static_cast<uint>(gl::get_texture_width(th, mipmap_level)));
}



vec2u get_texture2_size(const gl::texture_handle& th, uint mipmap_level)
{
  return vec2u(static_cast<uint>(gl::get_texture_width(th, mipmap_level)),
    static_cast<uint>(gl::get_texture_height(th, mipmap_level)));
}



vec3u get_texture3_size(const gl::texture_handle& th, uint mipmap_level)
{
  return vec3u(static_cast<uint>(gl::get_texture_width(th, mipmap_level)),
    static_cast<uint>(gl::get_texture_height(th, mipmap_level)),
    static_cast<uint>(gl::get_texture_depth(th, mipmap_level)));
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
  HOU_EXPECT(tu < get_texture_unit_count());
  gl::bind_texture(tex.m_gl_texture_handle, tu);
}



void texture::unbind(uint tu)
{
  HOU_EXPECT(tu < get_texture_unit_count());
  gl::unbind_texture(tu);
}



uint texture::get_texture_unit_count()
{
  return static_cast<uint>(gl::get_max_texture_image_units());
}



texture::texture(texture_type type, uint mipmap_level_count, uint sample_count,
  bool fixed_sample_locations)
  : m_gl_texture_handle(gl::texture_handle::create(static_cast<GLenum>(type)))
  , m_mipmap_level_count(mipmap_level_count)
  , m_sample_count(sample_count)
  , m_fixed_sample_locations(fixed_sample_locations)
{}



texture::texture(texture&& other)
  : m_gl_texture_handle(std::move(other.m_gl_texture_handle))
  , m_mipmap_level_count(std::move(other.m_mipmap_level_count))
  , m_sample_count(std::move(other.m_sample_count))
  , m_fixed_sample_locations(std::move(other.m_fixed_sample_locations))
{}



texture::~texture()
{}



const gl::texture_handle& texture::get_handle() const
{
  return m_gl_texture_handle;
}



bool texture::is_bound(uint tu) const
{
  HOU_EXPECT(tu < get_texture_unit_count());
  return gl::is_texture_bound(m_gl_texture_handle, tu);
}



texture_format texture::get_format() const
{
  return texture_format(gl::get_texture_format(m_gl_texture_handle));
}



uint texture::get_mipmap_level_count() const
{
  return m_mipmap_level_count;
}



uint texture::get_sample_count() const
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
  return static_cast<uint>(gl::get_texture_width(m_gl_texture_handle, 0));
}



uint texture::get_height() const
{
  return static_cast<uint>(gl::get_texture_height(m_gl_texture_handle, 0));
}



uint texture::get_depth() const
{
  return static_cast<uint>(gl::get_texture_depth(m_gl_texture_handle, 0));
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



template <>
vec1u texture_t<texture_type::texture1>::get_max_size()
{
  return vec1u(static_cast<uint>(gl::get_max_texture_size()));
}



template <>
vec2u texture_t<texture_type::texture1_array>::get_max_size()
{
  return vec2u(static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_layers()));
}



template <>
vec2u texture_t<texture_type::texture2>::get_max_size()
{
  return vec2u(static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_size()));
}



template <>
vec3u texture_t<texture_type::texture2_array>::get_max_size()
{
  return vec3u(static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_layers()));
}



template <>
vec3u texture_t<texture_type::texture3>::get_max_size()
{
  return vec3u(static_cast<uint>(gl::get_max_3d_texture_size()),
    static_cast<uint>(gl::get_max_3d_texture_size()),
    static_cast<uint>(gl::get_max_3d_texture_size()));
}



template <>
vec2u texture_t<texture_type::multisample_texture2>::get_max_size()
{
  return vec2u(static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_size()));
}



template <>
vec3u texture_t<texture_type::multisample_texture2_array>::get_max_size()
{
  return vec3u(static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_layers()));
}



template <texture_type Type>
uint texture_t<Type>::get_max_mipmap_level_count(const size_type& size)
{
  return is_texture_type_mipmapped(Type)
    ? get_max_mipmap_level_count_for_size<Type>(size)
    : 1u;
}



template <texture_type Type>
uint texture_t<Type>::get_max_sample_count()
{
  return is_texture_type_multisampled(Type) ? gl::get_max_texture_samples()
                                            : 1u;
}



template <>
template <>
texture_t<texture_type::texture1>::texture_t<texture_type::texture1, void>(
  const size_type& size, texture_format format, uint mipmap_level_count)
  : texture(texture_type::texture1, mipmap_level_count, 1u, true)
{
  HOU_EXPECT(is_texture_size_valid<texture_type::texture1>(size)
    && is_mipmap_level_count_valid<texture_type::texture1>(
         mipmap_level_count, size));
  gl::set_texture_storage_1d(m_gl_texture_handle, mipmap_level_count,
    static_cast<GLenum>(format), size.x());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <>
template <>
texture_t<texture_type::texture1_array>::texture_t<texture_type::texture1_array,
  void>(const size_type& size, texture_format format, uint mipmap_level_count)
  : texture(texture_type::texture1_array, mipmap_level_count, 1u, true)
{
  HOU_EXPECT(is_texture_size_valid<texture_type::texture1_array>(size)
    && is_mipmap_level_count_valid<texture_type::texture1_array>(
         mipmap_level_count, size));
  gl::set_texture_storage_2d(m_gl_texture_handle, mipmap_level_count,
    static_cast<GLenum>(format), size.x(), size.y());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <>
template <>
texture_t<texture_type::texture2>::texture_t<texture_type::texture2, void>(
  const size_type& size, texture_format format, uint mipmap_level_count)
  : texture(texture_type::texture2, mipmap_level_count, 1u, true)
{
  HOU_EXPECT(is_texture_size_valid<texture_type::texture2>(size)
    && is_mipmap_level_count_valid<texture_type::texture2>(
         mipmap_level_count, size));
  gl::set_texture_storage_2d(m_gl_texture_handle, mipmap_level_count,
    static_cast<GLenum>(format), size.x(), size.y());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <>
template <>
texture_t<texture_type::texture2_array>::texture_t<texture_type::texture2_array,
  void>(const size_type& size, texture_format format, uint mipmap_level_count)
  : texture(texture_type::texture2_array, mipmap_level_count, 1u, true)
{
  HOU_EXPECT(is_texture_size_valid<texture_type::texture2_array>(size)
    && is_mipmap_level_count_valid<texture_type::texture2_array>(
         mipmap_level_count, size));
  gl::set_texture_storage_3d(m_gl_texture_handle, mipmap_level_count,
    static_cast<GLenum>(format), size.x(), size.y(), size.z());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <>
template <>
texture_t<texture_type::texture3>::texture_t<texture_type::texture3, void>(
  const size_type& size, texture_format format, uint mipmap_level_count)
  : texture(texture_type::texture3, mipmap_level_count, 1u, true)
{
  HOU_EXPECT(is_texture_size_valid<texture_type::texture3>(size)
    && is_mipmap_level_count_valid<texture_type::texture3>(
         mipmap_level_count, size));
  gl::set_texture_storage_3d(m_gl_texture_handle, mipmap_level_count,
    static_cast<GLenum>(format), size.x(), size.y(), size.z());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
texture_t<Type>::texture_t(
  const image<PF>& im, texture_format format, uint mipmap_level_count)
  : texture_t(im.get_size(), format, mipmap_level_count)
{
  set_image(im);
}



template <>
template <texture_type Type2, typename Enable>
texture_t<texture_type::multisample_texture2>::texture_t(const size_type& size,
  texture_format format, uint sample_count, bool fixed_sample_locations)
  : texture(texture_type::multisample_texture2, 1u, sample_count,
      fixed_sample_locations)
{
  HOU_EXPECT(is_texture_size_valid<texture_type::multisample_texture2>(size)
    && sample_count > 0u
    && sample_count <= static_cast<uint>(gl::get_max_texture_samples()));
  set_texture_storage_2d_multisample(m_gl_texture_handle, sample_count,
    static_cast<GLenum>(format), size.x(), size.y(), fixed_sample_locations);
}



template <>
template <texture_type Type2, typename Enable>
texture_t<texture_type::multisample_texture2_array>::texture_t(
  const size_type& size, texture_format format, uint sample_count,
  bool fixed_sample_locations)
  : texture(texture_type::multisample_texture2_array, 1u, sample_count,
      fixed_sample_locations)
{
  HOU_EXPECT(
    is_texture_size_valid<texture_type::multisample_texture2_array>(size)
    && sample_count > 0u
    && sample_count <= static_cast<uint>(gl::get_max_texture_samples()));
  set_texture_storage_3d_multisample(m_gl_texture_handle, sample_count,
    static_cast<GLenum>(format), size.x(), size.y(), size.z(),
    fixed_sample_locations);
}



template <texture_type Type>
texture_t<Type>::texture_t(texture_t&& other)
  : texture(std::move(other))
{}



template <texture_type Type>
texture_t<Type>::~texture_t()
{}



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
  switch(get_texture_min_filter(m_gl_texture_handle))
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
      HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum),
        static_cast<GLenum>(get_texture_min_filter(m_gl_texture_handle)));
  }
}



template <texture_type Type>
template <texture_type Type2, typename Enable>
void texture_t<Type>::set_filter(texture_filter filter)
{
  switch(filter)
  {
    case texture_filter::nearest:
      set_texture_min_filter(m_gl_texture_handle, GL_NEAREST_MIPMAP_NEAREST);
      set_texture_mag_filter(m_gl_texture_handle, GL_NEAREST);
      break;
    case texture_filter::linear:
      set_texture_min_filter(m_gl_texture_handle, GL_NEAREST_MIPMAP_LINEAR);
      set_texture_mag_filter(m_gl_texture_handle, GL_NEAREST);
      break;
    case texture_filter::bilinear:
      set_texture_min_filter(m_gl_texture_handle, GL_LINEAR_MIPMAP_NEAREST);
      set_texture_mag_filter(m_gl_texture_handle, GL_LINEAR);
      break;
    case texture_filter::trilinear:
      set_texture_min_filter(m_gl_texture_handle, GL_LINEAR_MIPMAP_LINEAR);
      set_texture_mag_filter(m_gl_texture_handle, GL_LINEAR);
      break;
    default:
      HOU_LOGIC_ERROR(
        get_text(cor_error::invalid_enum), static_cast<int>(filter));
      break;
  }
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture1>::wrap_mode
  texture_t<texture_type::texture1>::get_wrap_mode() const
{
  return get_texture1_wrap_mode(m_gl_texture_handle);
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture1_array>::wrap_mode
  texture_t<texture_type::texture1_array>::get_wrap_mode() const
{
  return get_texture2_wrap_mode(m_gl_texture_handle);
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture2>::wrap_mode
  texture_t<texture_type::texture2>::get_wrap_mode() const
{
  return get_texture2_wrap_mode(m_gl_texture_handle);
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture2_array>::wrap_mode
  texture_t<texture_type::texture2_array>::get_wrap_mode() const
{
  return get_texture3_wrap_mode(m_gl_texture_handle);
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture3>::wrap_mode
  texture_t<texture_type::texture3>::get_wrap_mode() const
{
  return get_texture3_wrap_mode(m_gl_texture_handle);
}



template <>
template <texture_type Type2, typename Enable>
void texture_t<texture_type::texture1>::set_wrap_mode(
  const wrap_mode& wrap_mode)
{
  set_texture1_wrap_mode(m_gl_texture_handle, wrap_mode);
}



template <>
template <texture_type Type2, typename Enable>
void texture_t<texture_type::texture1_array>::set_wrap_mode(
  const wrap_mode& wrap_mode)
{
  set_texture2_wrap_mode(m_gl_texture_handle, wrap_mode);
}



template <>
template <texture_type Type2, typename Enable>
void texture_t<texture_type::texture2>::set_wrap_mode(
  const wrap_mode& wrap_mode)
{
  set_texture2_wrap_mode(m_gl_texture_handle, wrap_mode);
}



template <>
template <texture_type Type2, typename Enable>
void texture_t<texture_type::texture2_array>::set_wrap_mode(
  const wrap_mode& wrap_mode)
{
  set_texture3_wrap_mode(m_gl_texture_handle, wrap_mode);
}



template <>
template <texture_type Type2, typename Enable>
void texture_t<texture_type::texture3>::set_wrap_mode(
  const wrap_mode& wrap_mode)
{
  set_texture3_wrap_mode(m_gl_texture_handle, wrap_mode);
}



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
typename texture_t<Type>::template image<PF> texture_t<Type>::get_image() const
{
  gl::set_unpack_alignment(1);
  size_type size = get_size();
  std::vector<uint8_t> buffer(compute_image_buffer_size(size, PF));
  gl::get_texture_image(m_gl_texture_handle, 0u,
    pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<PF>(size,
    reinterpret_span<const typename image<PF>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
typename texture_t<texture_type::texture1>::template image<PF>
  texture_t<texture_type::texture1>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(element_wise_lower_or_equal(offset + size, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(compute_image_buffer_size(size, PF));
  gl::get_texture_sub_image(m_gl_texture_handle, offset.x(), 0, 0, size.x(), 1,
    1, 0, pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<PF>(size,
    reinterpret_span<const typename image<PF>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
typename texture_t<texture_type::texture1_array>::template image<PF>
  texture_t<texture_type::texture1_array>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(element_wise_lower_or_equal(offset + size, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(compute_image_buffer_size(size, PF));
  gl::get_texture_sub_image(m_gl_texture_handle, offset.x(), offset.y(), 0,
    size.x(), size.y(), 1, 0, pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<PF>(size,
    reinterpret_span<const typename image<PF>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
typename texture_t<texture_type::texture2>::template image<PF>
  texture_t<texture_type::texture2>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(element_wise_lower_or_equal(offset + size, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(compute_image_buffer_size(size, PF));
  gl::get_texture_sub_image(m_gl_texture_handle, offset.x(), offset.y(), 0,
    size.x(), size.y(), 1, 0, pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<PF>(size,
    reinterpret_span<const typename image<PF>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
typename texture_t<texture_type::texture2_array>::template image<PF>
  texture_t<texture_type::texture2_array>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(element_wise_lower_or_equal(offset + size, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(compute_image_buffer_size(size, PF));
  gl::get_texture_sub_image(m_gl_texture_handle, offset.x(), offset.y(),
    offset.z(), size.x(), size.y(), size.z(), 0,
    pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<PF>(size,
    reinterpret_span<const typename image<PF>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
typename texture_t<texture_type::texture3>::template image<PF>
  texture_t<texture_type::texture3>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(element_wise_lower_or_equal(offset + size, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(compute_image_buffer_size(size, PF));
  gl::get_texture_sub_image(m_gl_texture_handle, offset.x(), offset.y(),
    offset.z(), size.x(), size.y(), size.z(), 0,
    pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<PF>(size,
    reinterpret_span<const typename image<PF>::pixel>(span<uint8_t>(buffer)));
}



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<Type>::set_image(const image<PF>& im)
{
  HOU_EXPECT(im.get_size() == get_size());
  set_sub_image<PF>(offset_type::zero(), im);
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<texture_type::texture1>::set_sub_image(
  const offset_type& offset, const image<PF>& im)
{
  HOU_EXPECT(element_wise_lower_or_equal(offset + im.get_size(), get_size()));
  gl::set_texture_sub_image_1d(m_gl_texture_handle, 0u, offset.x(),
    im.get_size().x(), pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(im.get_pixels().data()));
  generate_mip_map();
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<texture_type::texture1_array>::set_sub_image(
  const offset_type& offset, const image<PF>& im)
{
  HOU_EXPECT(element_wise_lower_or_equal(offset + im.get_size(), get_size()));
  gl::set_texture_sub_image_2d(m_gl_texture_handle, 0, offset.x(), offset.y(),
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
  HOU_EXPECT(element_wise_lower_or_equal(offset + im.get_size(), get_size()));
  gl::set_texture_sub_image_2d(m_gl_texture_handle, 0, offset.x(), offset.y(),
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
  HOU_EXPECT(element_wise_lower_or_equal(offset + im.get_size(), get_size()));
  gl::set_texture_sub_image_3d(m_gl_texture_handle, 0, offset.x(), offset.y(),
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
  HOU_EXPECT(element_wise_lower_or_equal(offset + im.get_size(), get_size()));
  gl::set_texture_sub_image_3d(m_gl_texture_handle, 0, offset.x(), offset.y(),
    offset.z(), im.get_size().x(), im.get_size().y(), im.get_size().z(),
    pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(im.get_pixels().data()));
  generate_mip_map();
}



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<Type>::clear(const pixel_t<PF>& px)
{
  set_image(image<PF>(get_size(), px));
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture1>::size_type
  texture_t<texture_type::texture1>::get_mipmap_size(uint mipmap_level) const
{
  HOU_EXPECT(mipmap_level < m_mipmap_level_count);
  return get_texture1_size(m_gl_texture_handle, mipmap_level);
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture1_array>::size_type
  texture_t<texture_type::texture1_array>::get_mipmap_size(
    uint mipmap_level) const
{
  HOU_EXPECT(mipmap_level < m_mipmap_level_count);
  return get_texture2_size(m_gl_texture_handle, mipmap_level);
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture2>::size_type
  texture_t<texture_type::texture2>::get_mipmap_size(uint mipmap_level) const
{
  HOU_EXPECT(mipmap_level < m_mipmap_level_count);
  return get_texture2_size(m_gl_texture_handle, mipmap_level);
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture2_array>::size_type
  texture_t<texture_type::texture2_array>::get_mipmap_size(
    uint mipmap_level) const
{
  HOU_EXPECT(mipmap_level < m_mipmap_level_count);
  return get_texture3_size(m_gl_texture_handle, mipmap_level);
}



template <>
template <texture_type Type2, typename Enable>
typename texture_t<texture_type::texture3>::size_type
  texture_t<texture_type::texture3>::get_mipmap_size(uint mipmap_level) const
{
  HOU_EXPECT(mipmap_level < m_mipmap_level_count);
  return get_texture3_size(m_gl_texture_handle, mipmap_level);
}



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
typename texture_t<Type>::template image<PF> texture_t<Type>::get_mipmap_image(
  uint mipmap_level) const
{
  HOU_EXPECT(mipmap_level < m_mipmap_level_count);
  gl::set_unpack_alignment(1);
  size_type mipMapSize = get_mipmap_size(mipmap_level);
  std::vector<uint8_t> buffer(compute_image_buffer_size(mipMapSize, PF));
  gl::get_texture_image(m_gl_texture_handle, mipmap_level,
    pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<PF>(mipMapSize,
    reinterpret_span<const typename image<PF>::pixel>(span<uint8_t>(buffer)));
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
  if(m_mipmap_level_count > 1u)
  {
    gl::generate_mip_map(m_gl_texture_handle);
  }
}



#define INSTANTIATE_TEXTURE(tt) template class texture_t<tt>;



#define INSTANTIATE_TEXTURE_MIP_MAP_FUNCTIONS(tt) \
  template texture_t<tt>::texture_t<tt, void>( \
    const texture_t<tt>::size_type&, texture_format, uint); \
  template typename texture_t<tt>::wrap_mode \
    texture_t<tt>::get_wrap_mode<tt, void>() const; \
  template void texture_t<tt>::set_wrap_mode<tt, void>( \
    const typename texture_t<tt>::wrap_mode&); \
  template texture_filter texture_t<tt>::get_filter<tt, void>() const; \
  template void texture_t<tt>::set_filter<tt, void>(texture_filter); \
  template texture_t<tt>::size_type texture_t<tt>::get_mipmap_size<tt, void>( \
    uint) const;



#define INSTANTIATE_TEXTURE_MULTISAMPLE_FUNCTIONS(tt) \
  template texture_t<tt>::texture_t<tt, void>( \
    const texture_t<tt>::size_type&, texture_format, uint, bool);



#define INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, pf) \
  template texture_t<tt>::texture_t<pf, tt, void>( \
    const texture_t<tt>::image<pf>&, texture_format, uint); \
  template texture_t<tt>::image<pf> texture_t<tt>::get_image<pf, tt, void>() \
    const; \
  template texture_t<tt>::image<pf> \
    texture_t<tt>::get_sub_image<pf, tt, void>( \
      const texture_t<tt>::offset_type&, const texture_t<tt>::size_type&) \
      const; \
  template void texture_t<tt>::set_image<pf, tt, void>( \
    const texture_t<tt>::image<pf>&); \
  template void texture_t<tt>::set_sub_image<pf, tt, void>( \
    const texture_t<tt>::offset_type&, const texture_t<tt>::image<pf>&); \
  template void texture_t<tt>::clear<pf, tt, void>(const pixel_t<pf>&); \
  template texture_t<tt>::image<pf> \
    texture_t<tt>::get_mipmap_image<pf, tt, void>(uint) const;



#define INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS(tt) \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, pixel_format::r) \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, pixel_format::rg) \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, pixel_format::rgb) \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, pixel_format::rgba)



#define INSTANTIATE_TEXTURE_MIP_MAP(tt) \
  INSTANTIATE_TEXTURE(tt) \
  INSTANTIATE_TEXTURE_MIP_MAP_FUNCTIONS(tt) \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS(tt)



#define INSTANTIATE_TEXTURE_MULTISAMPLE(tt) \
  INSTANTIATE_TEXTURE(tt) \
  INSTANTIATE_TEXTURE_MULTISAMPLE_FUNCTIONS(tt)



INSTANTIATE_TEXTURE_MIP_MAP(texture_type::texture1)
INSTANTIATE_TEXTURE_MIP_MAP(texture_type::texture1_array)
INSTANTIATE_TEXTURE_MIP_MAP(texture_type::texture2)
INSTANTIATE_TEXTURE_MIP_MAP(texture_type::texture2_array)
INSTANTIATE_TEXTURE_MIP_MAP(texture_type::texture3)
INSTANTIATE_TEXTURE_MULTISAMPLE(texture_type::multisample_texture2)
INSTANTIATE_TEXTURE_MULTISAMPLE(texture_type::multisample_texture2_array)

}  // namespace hou
