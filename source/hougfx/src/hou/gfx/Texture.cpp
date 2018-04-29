// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/math_functions.hpp"

#include "hou/gfx/gl_type.hpp"
#include "hou/gfx/texture_channel_mapping.hpp"



namespace hou
{

namespace
{

GLenum pixelFormatToGlPixelFormat(pixel_format format);

template <TextureType type>
bool isTextureSizeValid(const typename texture_t<type>::size_type& size);

template <TextureType type>
bool isMipMapLevelCountValid(
  uint mipMapLevelCount, const typename texture_t<type>::size_type& size);

template <TextureType type>
uint getMaxMipMapLevelCountForSize(const typename texture_t<type>::size_type& size);

template <TextureType type>
uint getMipMapRelevantSize(const typename texture_t<type>::size_type& size);

template <size_t dim>
size_t computeImageBufferSize(const vec<uint, dim>& imSize, pixel_format fmt);

template <size_t dim>
bool elementWiseLowerOrEqual(
  const vec<uint, dim>& lhs, const vec<uint, dim>& rhs);

vec1u getTexture1Size(const gl::texture_handle& th, uint mipMapLevel);

vec2u getTexture2Size(const gl::texture_handle& th, uint mipMapLevel);

vec3u getTexture3Size(const gl::texture_handle& th, uint mipMapLevel);

std::array<texture_wrap_mode, 1u> getTexture1WrapMode(
  const gl::texture_handle& th);

std::array<texture_wrap_mode, 2u> getTexture2WrapMode(
  const gl::texture_handle& th);

std::array<texture_wrap_mode, 3u> getTexture3WrapMode(
  const gl::texture_handle& th);

void setTexture1WrapMode(
  const gl::texture_handle& th, const std::array<texture_wrap_mode, 1u>& wm);

void setTexture2WrapMode(
  const gl::texture_handle& th, const std::array<texture_wrap_mode, 2u>& wm);

void setTexture3WrapMode(
  const gl::texture_handle& th, const std::array<texture_wrap_mode, 3u>& wm);



GLenum pixelFormatToGlPixelFormat(pixel_format format)
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



template <TextureType type>
bool isTextureSizeValid(const typename texture_t<type>::size_type& size)
{
  using Tex = texture_t<type>;
  typename Tex::size_type maxSize = Tex::get_max_size();
  for(size_t i = 0; i < size.get_size(); ++i)
  {
    if(size(i) < 1u || size(i) > maxSize(i))
    {
      return false;
    }
  }
  return true;
}



template <TextureType type>
bool isMipMapLevelCountValid(
  uint mipMapLevelCount, const typename texture_t<type>::size_type& size)
{
  return mipMapLevelCount > 0
    && mipMapLevelCount <= getMaxMipMapLevelCountForSize<type>(size);
}



template <TextureType type>
uint getMaxMipMapLevelCountForSize(const typename texture_t<type>::size_type& size)
{
  return 1u
    + static_cast<uint>(
        log(static_cast<float>(getMipMapRelevantSize<type>(size)), 2));
}



template <>
uint getMipMapRelevantSize<TextureType::texture1>(
  const typename texture_t<TextureType::texture1>::size_type& size)
{
  return size(0);
}



template <>
uint getMipMapRelevantSize<TextureType::texture1_array>(
  const typename texture_t<TextureType::texture1_array>::size_type& size)
{
  return size(0);
}



template <>
uint getMipMapRelevantSize<TextureType::texture2>(
  const typename texture_t<TextureType::texture2>::size_type& size)
{
  return std::max(size(0), size(1));
}



template <>
uint getMipMapRelevantSize<TextureType::texture2_array>(
  const typename texture_t<TextureType::texture2_array>::size_type& size)
{
  return std::max(size(0), size(1));
}



template <>
uint getMipMapRelevantSize<TextureType::texture3>(
  const typename texture_t<TextureType::texture3>::size_type& size)
{
  return std::max(std::max(size(0), size(1)), size(2));
}



template <>
uint getMipMapRelevantSize<TextureType::multisample_texture2>(
  const typename texture_t<TextureType::multisample_texture2>::size_type&)
{
  return 1u;
}



template <>
uint getMipMapRelevantSize<TextureType::multisample_texture2_array>(
  const typename texture_t<TextureType::multisample_texture2_array>::size_type&)
{
  return 1u;
}



template <size_t dim>
size_t computeImageBufferSize(const vec<uint, dim>& imSize, pixel_format fmt)
{
  HOU_EXPECT_DEV(gl::get_unpack_alignment() == 1u);
  size_t byteCount = 1u;
  for(size_t i = 0; i < imSize.get_size(); ++i)
  {
    byteCount *= imSize(i);
  }
  return byteCount * get_pixel_format_byte_count(fmt);
}



template <size_t dim>
bool elementWiseLowerOrEqual(
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



vec1u getTexture1Size(const gl::texture_handle& th, uint mipMapLevel)
{
  return vec1u(static_cast<uint>(gl::get_texture_width(th, mipMapLevel)));
}



vec2u getTexture2Size(const gl::texture_handle& th, uint mipMapLevel)
{
  return vec2u(static_cast<uint>(gl::get_texture_width(th, mipMapLevel)),
    static_cast<uint>(gl::get_texture_height(th, mipMapLevel)));
}



vec3u getTexture3Size(const gl::texture_handle& th, uint mipMapLevel)
{
  return vec3u(static_cast<uint>(gl::get_texture_width(th, mipMapLevel)),
    static_cast<uint>(gl::get_texture_height(th, mipMapLevel)),
    static_cast<uint>(gl::get_texture_depth(th, mipMapLevel)));
}



std::array<texture_wrap_mode, 1u> getTexture1WrapMode(const gl::texture_handle& th)
{
  return {texture_wrap_mode(get_texture_wrap_mode_s(th))};
}



std::array<texture_wrap_mode, 2u> getTexture2WrapMode(const gl::texture_handle& th)
{
  return {texture_wrap_mode(get_texture_wrap_mode_s(th)),
    texture_wrap_mode(get_texture_wrap_mode_t(th))};
}



std::array<texture_wrap_mode, 3u> getTexture3WrapMode(const gl::texture_handle& th)
{
  return {texture_wrap_mode(get_texture_wrap_mode_s(th)),
    texture_wrap_mode(get_texture_wrap_mode_t(th)),
    texture_wrap_mode(get_texture_wrap_mode_r(th))};
}



void setTexture1WrapMode(
  const gl::texture_handle& th, const std::array<texture_wrap_mode, 1u>& wm)
{
  set_texture_wrap_mode_s(th, static_cast<GLenum>(wm[0]));
}



void setTexture2WrapMode(
  const gl::texture_handle& th, const std::array<texture_wrap_mode, 2u>& wm)
{
  set_texture_wrap_mode_s(th, static_cast<GLenum>(wm[0]));
  set_texture_wrap_mode_t(th, static_cast<GLenum>(wm[1]));
}



void setTexture3WrapMode(
  const gl::texture_handle& th, const std::array<texture_wrap_mode, 3u>& wm)
{
  set_texture_wrap_mode_s(th, static_cast<GLenum>(wm[0]));
  set_texture_wrap_mode_t(th, static_cast<GLenum>(wm[1]));
  set_texture_wrap_mode_r(th, static_cast<GLenum>(wm[2]));
}

}  // namespace



void texture::bind(const texture& ph_texture, uint textureUnit)
{
  HOU_EXPECT(textureUnit < get_texture_unit_count());
  gl::bind_texture(ph_texture.mGlTextureHandle, textureUnit);
}



void texture::unbind(uint textureUnit)
{
  HOU_EXPECT(textureUnit < get_texture_unit_count());
  gl::unbind_texture(textureUnit);
}



uint texture::get_texture_unit_count()
{
  return static_cast<uint>(gl::get_max_texture_image_units());
}



texture::texture(TextureType type, uint mipMapLevelCount, uint sampleCount,
  bool fixedSampleLocations)
  : mGlTextureHandle(gl::texture_handle::create(static_cast<GLenum>(type)))
  , m_mipmap_level_count(mipMapLevelCount)
  , m_sample_count(sampleCount)
  , m_fixed_sample_locations(fixedSampleLocations)
{}



texture::texture(texture&& other)
  : mGlTextureHandle(std::move(other.mGlTextureHandle))
  , m_mipmap_level_count(std::move(other.m_mipmap_level_count))
  , m_sample_count(std::move(other.m_sample_count))
  , m_fixed_sample_locations(std::move(other.m_fixed_sample_locations))
{}



texture::~texture()
{}



const gl::texture_handle& texture::get_handle() const
{
  return mGlTextureHandle;
}



bool texture::is_bound(uint textureUnit) const
{
  HOU_EXPECT(textureUnit < get_texture_unit_count());
  return gl::is_texture_bound(mGlTextureHandle, textureUnit);
}



texture_format texture::get_format() const
{
  return texture_format(gl::get_texture_format(mGlTextureHandle));
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
    texture_channel(get_texture_swizzle_r(mGlTextureHandle)),
    texture_channel(get_texture_swizzle_g(mGlTextureHandle)),
    texture_channel(get_texture_swizzle_b(mGlTextureHandle)),
    texture_channel(get_texture_swizzle_a(mGlTextureHandle)));
}



void texture::setChannelMapping(const texture_channel_mapping& mapping)
{
  set_texture_swizzle_r(mGlTextureHandle, static_cast<GLenum>(mapping.get_r()));
  set_texture_swizzle_g(mGlTextureHandle, static_cast<GLenum>(mapping.get_g()));
  set_texture_swizzle_b(mGlTextureHandle, static_cast<GLenum>(mapping.get_b()));
  set_texture_swizzle_a(mGlTextureHandle, static_cast<GLenum>(mapping.get_a()));
}



uint texture::get_width() const
{
  return static_cast<uint>(gl::get_texture_width(mGlTextureHandle, 0));
}



uint texture::get_height() const
{
  return static_cast<uint>(gl::get_texture_height(mGlTextureHandle, 0));
}



uint texture::get_depth() const
{
  return static_cast<uint>(gl::get_texture_depth(mGlTextureHandle, 0));
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
vec1u texture_t<TextureType::texture1>::get_max_size()
{
  return vec1u(static_cast<uint>(gl::get_max_texture_size()));
}



template <>
vec2u texture_t<TextureType::texture1_array>::get_max_size()
{
  return vec2u(static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_layers()));
}



template <>
vec2u texture_t<TextureType::texture2>::get_max_size()
{
  return vec2u(static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_size()));
}



template <>
vec3u texture_t<TextureType::texture2_array>::get_max_size()
{
  return vec3u(static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_layers()));
}



template <>
vec3u texture_t<TextureType::texture3>::get_max_size()
{
  return vec3u(static_cast<uint>(gl::get_max_3d_texture_size()),
    static_cast<uint>(gl::get_max_3d_texture_size()),
    static_cast<uint>(gl::get_max_3d_texture_size()));
}



template <>
vec2u texture_t<TextureType::multisample_texture2>::get_max_size()
{
  return vec2u(static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_size()));
}



template <>
vec3u texture_t<TextureType::multisample_texture2_array>::get_max_size()
{
  return vec3u(static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_size()),
    static_cast<uint>(gl::get_max_texture_layers()));
}



template <TextureType type>
uint texture_t<type>::get_max_mipmap_level_count(const size_type& size)
{
  return is_texture_type_mipmapped(type)
    ? getMaxMipMapLevelCountForSize<type>(size)
    : 1u;
}



template <TextureType type>
uint texture_t<type>::get_max_sample_count()
{
  return is_texture_type_multisampled(type) ? gl::get_max_texture_samples() : 1u;
}



template <>
template <>
texture_t<TextureType::texture1>::texture_t<TextureType::texture1, void>(
  const size_type& size, texture_format format, uint mipMapLevelCount)
  : texture(TextureType::texture1, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::texture1>(size)
    && isMipMapLevelCountValid<TextureType::texture1>(mipMapLevelCount, size));
  gl::set_texture_storage_1d(
    mGlTextureHandle, mipMapLevelCount, static_cast<GLenum>(format), size.x());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <>
template <>
texture_t<TextureType::texture1_array>::texture_t<TextureType::texture1_array,
  void>(const size_type& size, texture_format format, uint mipMapLevelCount)
  : texture(TextureType::texture1_array, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::texture1_array>(size)
    && isMipMapLevelCountValid<TextureType::texture1_array>(
         mipMapLevelCount, size));
  gl::set_texture_storage_2d(mGlTextureHandle, mipMapLevelCount,
    static_cast<GLenum>(format), size.x(), size.y());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <>
template <>
texture_t<TextureType::texture2>::texture_t<TextureType::texture2, void>(
  const size_type& size, texture_format format, uint mipMapLevelCount)
  : texture(TextureType::texture2, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::texture2>(size)
    && isMipMapLevelCountValid<TextureType::texture2>(mipMapLevelCount, size));
  gl::set_texture_storage_2d(mGlTextureHandle, mipMapLevelCount,
    static_cast<GLenum>(format), size.x(), size.y());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <>
template <>
texture_t<TextureType::texture2_array>::texture_t<TextureType::texture2_array,
  void>(const size_type& size, texture_format format, uint mipMapLevelCount)
  : texture(TextureType::texture2_array, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::texture2_array>(size)
    && isMipMapLevelCountValid<TextureType::texture2_array>(
         mipMapLevelCount, size));
  gl::set_texture_storage_3d(mGlTextureHandle, mipMapLevelCount,
    static_cast<GLenum>(format), size.x(), size.y(), size.z());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <>
template <>
texture_t<TextureType::texture3>::texture_t<TextureType::texture3, void>(
  const size_type& size, texture_format format, uint mipMapLevelCount)
  : texture(TextureType::texture3, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::texture3>(size)
    && isMipMapLevelCountValid<TextureType::texture3>(mipMapLevelCount, size));
  gl::set_texture_storage_3d(mGlTextureHandle, mipMapLevelCount,
    static_cast<GLenum>(format), size.x(), size.y(), size.z());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <TextureType type>
template <pixel_format fmt, TextureType t, typename Enable>
texture_t<type>::texture_t(
  const image<fmt>& ph_image, texture_format format, uint mipMapLevelCount)
  : texture_t(ph_image.get_size(), format, mipMapLevelCount)
{
  set_image(ph_image);
}



template <>
template <TextureType t, typename Enable>
texture_t<TextureType::multisample_texture2>::texture_t(const size_type& size,
  texture_format format, uint sampleCount, bool fixedSampleLocations)
  : texture(
      TextureType::multisample_texture2, 1u, sampleCount, fixedSampleLocations)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::multisample_texture2>(size)
    && sampleCount > 0u
    && sampleCount <= static_cast<uint>(gl::get_max_texture_samples()));
  set_texture_storage_2d_multisample(mGlTextureHandle, sampleCount,
    static_cast<GLenum>(format), size.x(), size.y(), fixedSampleLocations);
}



template <>
template <TextureType t, typename Enable>
texture_t<TextureType::multisample_texture2_array>::texture_t(const size_type& size,
  texture_format format, uint sampleCount, bool fixedSampleLocations)
  : texture(TextureType::multisample_texture2_array, 1u, sampleCount,
      fixedSampleLocations)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::multisample_texture2_array>(size)
    && sampleCount > 0u
    && sampleCount <= static_cast<uint>(gl::get_max_texture_samples()));
  set_texture_storage_3d_multisample(mGlTextureHandle, sampleCount,
    static_cast<GLenum>(format), size.x(), size.y(), size.z(),
    fixedSampleLocations);
}



template <TextureType type>
texture_t<type>::texture_t(texture_t&& other)
  : texture(std::move(other))
{}



template <TextureType type>
texture_t<type>::~texture_t()
{}



template <>
typename texture_t<TextureType::texture1>::size_type
  texture_t<TextureType::texture1>::get_size() const
{
  return get_size1();
}



template <>
typename texture_t<TextureType::texture1_array>::size_type
  texture_t<TextureType::texture1_array>::get_size() const
{
  return get_size2();
}



template <>
typename texture_t<TextureType::texture2>::size_type
  texture_t<TextureType::texture2>::get_size() const
{
  return get_size2();
}



template <>
typename texture_t<TextureType::texture2_array>::size_type
  texture_t<TextureType::texture2_array>::get_size() const
{
  return get_size3();
}



template <>
typename texture_t<TextureType::texture3>::size_type
  texture_t<TextureType::texture3>::get_size() const
{
  return get_size3();
}



template <>
typename texture_t<TextureType::multisample_texture2>::size_type
  texture_t<TextureType::multisample_texture2>::get_size() const
{
  return get_size2();
}



template <>
typename texture_t<TextureType::multisample_texture2_array>::size_type
  texture_t<TextureType::multisample_texture2_array>::get_size() const
{
  return get_size3();
}



template <TextureType type>
template <TextureType t, typename Enable>
texture_filter texture_t<type>::get_filter() const
{
  switch(get_texture_min_filter(mGlTextureHandle))
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
      static_cast<GLenum>(get_texture_min_filter(mGlTextureHandle)));
  }
}



template <TextureType type>
template <TextureType t, typename Enable>
void texture_t<type>::set_filter(texture_filter filter)
{
  switch(filter)
  {
  case texture_filter::nearest:
    set_texture_min_filter(mGlTextureHandle, GL_NEAREST_MIPMAP_NEAREST);
    set_texture_mag_filter(mGlTextureHandle, GL_NEAREST);
    break;
  case texture_filter::linear:
    set_texture_min_filter(mGlTextureHandle, GL_NEAREST_MIPMAP_LINEAR);
    set_texture_mag_filter(mGlTextureHandle, GL_NEAREST);
    break;
  case texture_filter::bilinear:
    set_texture_min_filter(mGlTextureHandle, GL_LINEAR_MIPMAP_NEAREST);
    set_texture_mag_filter(mGlTextureHandle, GL_LINEAR);
    break;
  case texture_filter::trilinear:
    set_texture_min_filter(mGlTextureHandle, GL_LINEAR_MIPMAP_LINEAR);
    set_texture_mag_filter(mGlTextureHandle, GL_LINEAR);
    break;
  default:
    HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<int>(filter));
    break;
  }
}



template <>
template <TextureType t, typename Enable>
typename texture_t<TextureType::texture1>::wrap_mode
  texture_t<TextureType::texture1>::get_wrap_mode() const
{
  return getTexture1WrapMode(mGlTextureHandle);
}



template <>
template <TextureType t, typename Enable>
typename texture_t<TextureType::texture1_array>::wrap_mode
  texture_t<TextureType::texture1_array>::get_wrap_mode() const
{
  return getTexture2WrapMode(mGlTextureHandle);
}



template <>
template <TextureType t, typename Enable>
typename texture_t<TextureType::texture2>::wrap_mode
  texture_t<TextureType::texture2>::get_wrap_mode() const
{
  return getTexture2WrapMode(mGlTextureHandle);
}



template <>
template <TextureType t, typename Enable>
typename texture_t<TextureType::texture2_array>::wrap_mode
  texture_t<TextureType::texture2_array>::get_wrap_mode() const
{
  return getTexture3WrapMode(mGlTextureHandle);
}



template <>
template <TextureType t, typename Enable>
typename texture_t<TextureType::texture3>::wrap_mode
  texture_t<TextureType::texture3>::get_wrap_mode() const
{
  return getTexture3WrapMode(mGlTextureHandle);
}



template <>
template <TextureType t, typename Enable>
void texture_t<TextureType::texture1>::set_wrap_mode(const wrap_mode& wrapMode)
{
  setTexture1WrapMode(mGlTextureHandle, wrapMode);
}



template <>
template <TextureType t, typename Enable>
void texture_t<TextureType::texture1_array>::set_wrap_mode(const wrap_mode& wrapMode)
{
  setTexture2WrapMode(mGlTextureHandle, wrapMode);
}



template <>
template <TextureType t, typename Enable>
void texture_t<TextureType::texture2>::set_wrap_mode(const wrap_mode& wrapMode)
{
  setTexture2WrapMode(mGlTextureHandle, wrapMode);
}



template <>
template <TextureType t, typename Enable>
void texture_t<TextureType::texture2_array>::set_wrap_mode(const wrap_mode& wrapMode)
{
  setTexture3WrapMode(mGlTextureHandle, wrapMode);
}



template <>
template <TextureType t, typename Enable>
void texture_t<TextureType::texture3>::set_wrap_mode(const wrap_mode& wrapMode)
{
  setTexture3WrapMode(mGlTextureHandle, wrapMode);
}



template <TextureType type>
template <pixel_format fmt, TextureType t, typename Enable>
typename texture_t<type>::template image<fmt> texture_t<type>::get_image() const
{
  gl::set_unpack_alignment(1);
  size_type size = get_size();
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::get_texture_image(mGlTextureHandle, 0u, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<fmt>(size,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
typename texture_t<TextureType::texture1>::template image<fmt>
  texture_t<TextureType::texture1>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::get_texture_sub_image(mGlTextureHandle, offset.x(), 0, 0, size.x(), 1, 1, 0,
    pixelFormatToGlPixelFormat(fmt), static_cast<GLenum>(to_gl_type<uint8_t>()),
    buffer.size(), buffer.data());
  return image<fmt>(size,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
typename texture_t<TextureType::texture1_array>::template image<fmt>
  texture_t<TextureType::texture1_array>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::get_texture_sub_image(mGlTextureHandle, offset.x(), offset.y(), 0, size.x(),
    size.y(), 1, 0, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<fmt>(size,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
typename texture_t<TextureType::texture2>::template image<fmt>
  texture_t<TextureType::texture2>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::get_texture_sub_image(mGlTextureHandle, offset.x(), offset.y(), 0, size.x(),
    size.y(), 1, 0, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<fmt>(size,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
typename texture_t<TextureType::texture2_array>::template image<fmt>
  texture_t<TextureType::texture2_array>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::get_texture_sub_image(mGlTextureHandle, offset.x(), offset.y(), offset.z(),
    size.x(), size.y(), size.z(), 0, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<fmt>(size,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
typename texture_t<TextureType::texture3>::template image<fmt>
  texture_t<TextureType::texture3>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, get_size()));
  gl::set_unpack_alignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::get_texture_sub_image(mGlTextureHandle, offset.x(), offset.y(), offset.z(),
    size.x(), size.y(), size.z(), 0, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(to_gl_type<uint8_t>()), buffer.size(), buffer.data());
  return image<fmt>(size,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <TextureType type>
template <pixel_format fmt, TextureType t, typename Enable>
void texture_t<type>::set_image(const image<fmt>& ph_image)
{
  HOU_EXPECT(ph_image.get_size() == get_size());
  set_sub_image<fmt>(offset_type::zero(), ph_image);
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
void texture_t<TextureType::texture1>::set_sub_image(
  const offset_type& offset, const image<fmt>& ph_image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + ph_image.get_size(), get_size()));
  gl::set_texture_sub_image_1d(mGlTextureHandle, 0u, offset.x(),
    ph_image.get_size().x(), pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(ph_image.get_pixels().data()));
  generate_mip_map();
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
void texture_t<TextureType::texture1_array>::set_sub_image(
  const offset_type& offset, const image<fmt>& ph_image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + ph_image.get_size(), get_size()));
  gl::set_texture_sub_image_2d(mGlTextureHandle, 0, offset.x(), offset.y(),
    ph_image.get_size().x(), ph_image.get_size().y(), pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(ph_image.get_pixels().data()));
  generate_mip_map();
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
void texture_t<TextureType::texture2>::set_sub_image(
  const offset_type& offset, const image<fmt>& ph_image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + ph_image.get_size(), get_size()));
  gl::set_texture_sub_image_2d(mGlTextureHandle, 0, offset.x(), offset.y(),
    ph_image.get_size().x(), ph_image.get_size().y(), pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(ph_image.get_pixels().data()));
  generate_mip_map();
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
void texture_t<TextureType::texture2_array>::set_sub_image(
  const offset_type& offset, const image<fmt>& ph_image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + ph_image.get_size(), get_size()));
  gl::set_texture_sub_image_3d(mGlTextureHandle, 0, offset.x(), offset.y(),
    offset.z(), ph_image.get_size().x(), ph_image.get_size().y(), ph_image.get_size().z(),
    pixelFormatToGlPixelFormat(fmt), static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(ph_image.get_pixels().data()));
  generate_mip_map();
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
void texture_t<TextureType::texture3>::set_sub_image(
  const offset_type& offset, const image<fmt>& ph_image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + ph_image.get_size(), get_size()));
  gl::set_texture_sub_image_3d(mGlTextureHandle, 0, offset.x(), offset.y(),
    offset.z(), ph_image.get_size().x(), ph_image.get_size().y(), ph_image.get_size().z(),
    pixelFormatToGlPixelFormat(fmt), static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(ph_image.get_pixels().data()));
  generate_mip_map();
}



template <TextureType type>
template <pixel_format fmt, TextureType t, typename Enable>
void texture_t<type>::clear(const pixel_t<fmt>& ph_pixel)
{
  set_image(image<fmt>(get_size(), ph_pixel));
}



template <>
template <TextureType t, typename Enable>
typename texture_t<TextureType::texture1>::size_type
  texture_t<TextureType::texture1>::get_mipmap_size(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < m_mipmap_level_count);
  return getTexture1Size(mGlTextureHandle, mipMapLevel);
}



template <>
template <TextureType t, typename Enable>
typename texture_t<TextureType::texture1_array>::size_type
  texture_t<TextureType::texture1_array>::get_mipmap_size(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < m_mipmap_level_count);
  return getTexture2Size(mGlTextureHandle, mipMapLevel);
}



template <>
template <TextureType t, typename Enable>
typename texture_t<TextureType::texture2>::size_type
  texture_t<TextureType::texture2>::get_mipmap_size(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < m_mipmap_level_count);
  return getTexture2Size(mGlTextureHandle, mipMapLevel);
}



template <>
template <TextureType t, typename Enable>
typename texture_t<TextureType::texture2_array>::size_type
  texture_t<TextureType::texture2_array>::get_mipmap_size(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < m_mipmap_level_count);
  return getTexture3Size(mGlTextureHandle, mipMapLevel);
}



template <>
template <TextureType t, typename Enable>
typename texture_t<TextureType::texture3>::size_type
  texture_t<TextureType::texture3>::get_mipmap_size(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < m_mipmap_level_count);
  return getTexture3Size(mGlTextureHandle, mipMapLevel);
}



template <TextureType type>
template <pixel_format fmt, TextureType t, typename Enable>
typename texture_t<type>::template image<fmt> texture_t<type>::get_mipmap_image(
  uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < m_mipmap_level_count);
  gl::set_unpack_alignment(1);
  size_type mipMapSize = get_mipmap_size(mipMapLevel);
  std::vector<uint8_t> buffer(computeImageBufferSize(mipMapSize, fmt));
  gl::get_texture_image(mGlTextureHandle, mipMapLevel,
    pixelFormatToGlPixelFormat(fmt), static_cast<GLenum>(to_gl_type<uint8_t>()),
    buffer.size(), buffer.data());
  return image<fmt>(mipMapSize,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <TextureType type>
TextureType texture_t<type>::get_type() const
{
  return type;
}



template <TextureType type>
size_t texture_t<type>::get_dimension_count() const
{
  return get_texture_type_dimension_count(type);
}



template <TextureType type>
bool texture_t<type>::is_mipmapped() const
{
  return is_texture_type_mipmapped(type);
}



template <TextureType type>
bool texture_t<type>::is_multisampled() const
{
  return is_texture_type_multisampled(type);
}



template <TextureType type>
void texture_t<type>::generate_mip_map()
{
  if(m_mipmap_level_count > 1u)
  {
    gl::generate_mip_map(mGlTextureHandle);
  }
}



#define INSTANTIATE_TEXTURE(tt) template class texture_t<tt>;



#define INSTANTIATE_TEXTURE_MIP_MAP_FUNCTIONS(tt)                   \
  template texture_t<tt>::texture_t<tt, void>(                        \
    const texture_t<tt>::size_type&, texture_format, uint);                \
  template typename texture_t<tt>::wrap_mode                          \
    texture_t<tt>::get_wrap_mode<tt, void>() const;                    \
  template void texture_t<tt>::set_wrap_mode<tt, void>(                \
    const typename texture_t<tt>::wrap_mode&);                        \
  template texture_filter texture_t<tt>::get_filter<tt, void>() const; \
  template void texture_t<tt>::set_filter<tt, void>(texture_filter);   \
  template texture_t<tt>::size_type texture_t<tt>::get_mipmap_size<tt, void>(uint) const;



#define INSTANTIATE_TEXTURE_MULTISAMPLE_FUNCTIONS(tt) \
  template texture_t<tt>::texture_t<tt, void>(          \
    const texture_t<tt>::size_type&, texture_format, uint, bool);



#define INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, pf)           \
  template texture_t<tt>::texture_t<pf, tt, void>(                               \
    const texture_t<tt>::image<pf>&, texture_format, uint);                      \
  template texture_t<tt>::image<pf> texture_t<tt>::get_image<pf, tt, void>()      \
    const;                                                                     \
  template texture_t<tt>::image<pf> texture_t<tt>::get_sub_image<pf, tt, void>(    \
    const texture_t<tt>::offset_type&, const texture_t<tt>::size_type&) const;        \
  template void texture_t<tt>::set_image<pf, tt, void>(                          \
    const texture_t<tt>::image<pf>&);                                           \
  template void texture_t<tt>::set_sub_image<pf, tt, void>(                       \
    const texture_t<tt>::offset_type&, const texture_t<tt>::image<pf>&);         \
  template void texture_t<tt>::clear<pf, tt, void>(const pixel_t<pf>&);          \
  template texture_t<tt>::image<pf> texture_t<tt>::get_mipmap_image<pf, tt, void>( \
    uint) const;



#define INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS(tt)                              \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, pixel_format::r)   \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, pixel_format::rg)  \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, pixel_format::rgb) \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, pixel_format::rgba)



#define INSTANTIATE_TEXTURE_MIP_MAP(tt)     \
  INSTANTIATE_TEXTURE(tt)                   \
  INSTANTIATE_TEXTURE_MIP_MAP_FUNCTIONS(tt) \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS(tt)



#define INSTANTIATE_TEXTURE_MULTISAMPLE(tt) \
  INSTANTIATE_TEXTURE(tt)                   \
  INSTANTIATE_TEXTURE_MULTISAMPLE_FUNCTIONS(tt)



INSTANTIATE_TEXTURE_MIP_MAP(TextureType::texture1)
INSTANTIATE_TEXTURE_MIP_MAP(TextureType::texture1_array)
INSTANTIATE_TEXTURE_MIP_MAP(TextureType::texture2)
INSTANTIATE_TEXTURE_MIP_MAP(TextureType::texture2_array)
INSTANTIATE_TEXTURE_MIP_MAP(TextureType::texture3)
INSTANTIATE_TEXTURE_MULTISAMPLE(TextureType::multisample_texture2)
INSTANTIATE_TEXTURE_MULTISAMPLE(TextureType::multisample_texture2_array)

}  // namespace hou
