// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/Texture.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/math_functions.hpp"

#include "hou/gfx/GlType.hpp"
#include "hou/gfx/TextureChannelMapping.hpp"



namespace hou
{

namespace
{

GLenum pixelFormatToGlPixelFormat(pixel_format format);

template <TextureType type>
bool isTextureSizeValid(const typename TextureT<type>::size_type& size);

template <TextureType type>
bool isMipMapLevelCountValid(
  uint mipMapLevelCount, const typename TextureT<type>::size_type& size);

template <TextureType type>
uint getMaxMipMapLevelCountForSize(const typename TextureT<type>::size_type& size);

template <TextureType type>
uint getMipMapRelevantSize(const typename TextureT<type>::size_type& size);

template <size_t dim>
size_t computeImageBufferSize(const vec<uint, dim>& imSize, pixel_format fmt);

template <size_t dim>
bool elementWiseLowerOrEqual(
  const vec<uint, dim>& lhs, const vec<uint, dim>& rhs);

vec1u getTexture1Size(const gl::TextureHandle& th, uint mipMapLevel);

vec2u getTexture2Size(const gl::TextureHandle& th, uint mipMapLevel);

vec3u getTexture3Size(const gl::TextureHandle& th, uint mipMapLevel);

std::array<TextureWrapMode, 1u> getTexture1WrapMode(
  const gl::TextureHandle& th);

std::array<TextureWrapMode, 2u> getTexture2WrapMode(
  const gl::TextureHandle& th);

std::array<TextureWrapMode, 3u> getTexture3WrapMode(
  const gl::TextureHandle& th);

void setTexture1WrapMode(
  const gl::TextureHandle& th, const std::array<TextureWrapMode, 1u>& wm);

void setTexture2WrapMode(
  const gl::TextureHandle& th, const std::array<TextureWrapMode, 2u>& wm);

void setTexture3WrapMode(
  const gl::TextureHandle& th, const std::array<TextureWrapMode, 3u>& wm);



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
bool isTextureSizeValid(const typename TextureT<type>::size_type& size)
{
  using Tex = TextureT<type>;
  typename Tex::size_type maxSize = Tex::getMaxSize();
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
  uint mipMapLevelCount, const typename TextureT<type>::size_type& size)
{
  return mipMapLevelCount > 0
    && mipMapLevelCount <= getMaxMipMapLevelCountForSize<type>(size);
}



template <TextureType type>
uint getMaxMipMapLevelCountForSize(const typename TextureT<type>::size_type& size)
{
  return 1u
    + static_cast<uint>(
        log(static_cast<float>(getMipMapRelevantSize<type>(size)), 2));
}



template <>
uint getMipMapRelevantSize<TextureType::Texture1>(
  const typename TextureT<TextureType::Texture1>::size_type& size)
{
  return size(0);
}



template <>
uint getMipMapRelevantSize<TextureType::Texture1Array>(
  const typename TextureT<TextureType::Texture1Array>::size_type& size)
{
  return size(0);
}



template <>
uint getMipMapRelevantSize<TextureType::Texture2>(
  const typename TextureT<TextureType::Texture2>::size_type& size)
{
  return std::max(size(0), size(1));
}



template <>
uint getMipMapRelevantSize<TextureType::Texture2Array>(
  const typename TextureT<TextureType::Texture2Array>::size_type& size)
{
  return std::max(size(0), size(1));
}



template <>
uint getMipMapRelevantSize<TextureType::Texture3>(
  const typename TextureT<TextureType::Texture3>::size_type& size)
{
  return std::max(std::max(size(0), size(1)), size(2));
}



template <>
uint getMipMapRelevantSize<TextureType::MultisampleTexture2>(
  const typename TextureT<TextureType::MultisampleTexture2>::size_type&)
{
  return 1u;
}



template <>
uint getMipMapRelevantSize<TextureType::MultisampleTexture2Array>(
  const typename TextureT<TextureType::MultisampleTexture2Array>::size_type&)
{
  return 1u;
}



template <size_t dim>
size_t computeImageBufferSize(const vec<uint, dim>& imSize, pixel_format fmt)
{
  HOU_EXPECT_DEV(gl::getUnpackAlignment() == 1u);
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



vec1u getTexture1Size(const gl::TextureHandle& th, uint mipMapLevel)
{
  return vec1u(static_cast<uint>(gl::getTextureWidth(th, mipMapLevel)));
}



vec2u getTexture2Size(const gl::TextureHandle& th, uint mipMapLevel)
{
  return vec2u(static_cast<uint>(gl::getTextureWidth(th, mipMapLevel)),
    static_cast<uint>(gl::getTextureHeight(th, mipMapLevel)));
}



vec3u getTexture3Size(const gl::TextureHandle& th, uint mipMapLevel)
{
  return vec3u(static_cast<uint>(gl::getTextureWidth(th, mipMapLevel)),
    static_cast<uint>(gl::getTextureHeight(th, mipMapLevel)),
    static_cast<uint>(gl::getTextureDepth(th, mipMapLevel)));
}



std::array<TextureWrapMode, 1u> getTexture1WrapMode(const gl::TextureHandle& th)
{
  return {TextureWrapMode(getTextureWrapModeS(th))};
}



std::array<TextureWrapMode, 2u> getTexture2WrapMode(const gl::TextureHandle& th)
{
  return {TextureWrapMode(getTextureWrapModeS(th)),
    TextureWrapMode(getTextureWrapModeT(th))};
}



std::array<TextureWrapMode, 3u> getTexture3WrapMode(const gl::TextureHandle& th)
{
  return {TextureWrapMode(getTextureWrapModeS(th)),
    TextureWrapMode(getTextureWrapModeT(th)),
    TextureWrapMode(getTextureWrapModeR(th))};
}



void setTexture1WrapMode(
  const gl::TextureHandle& th, const std::array<TextureWrapMode, 1u>& wm)
{
  setTextureWrapModeS(th, static_cast<GLenum>(wm[0]));
}



void setTexture2WrapMode(
  const gl::TextureHandle& th, const std::array<TextureWrapMode, 2u>& wm)
{
  setTextureWrapModeS(th, static_cast<GLenum>(wm[0]));
  setTextureWrapModeT(th, static_cast<GLenum>(wm[1]));
}



void setTexture3WrapMode(
  const gl::TextureHandle& th, const std::array<TextureWrapMode, 3u>& wm)
{
  setTextureWrapModeS(th, static_cast<GLenum>(wm[0]));
  setTextureWrapModeT(th, static_cast<GLenum>(wm[1]));
  setTextureWrapModeR(th, static_cast<GLenum>(wm[2]));
}

}  // namespace



void Texture::bind(const Texture& texture, uint textureUnit)
{
  HOU_EXPECT(textureUnit < getTextureUnitCount());
  gl::bindTexture(texture.mGlTextureHandle, textureUnit);
}



void Texture::unbind(uint textureUnit)
{
  HOU_EXPECT(textureUnit < getTextureUnitCount());
  gl::unbindTexture(textureUnit);
}



uint Texture::getTextureUnitCount()
{
  return static_cast<uint>(gl::getMaxTextureImageUnits());
}



Texture::Texture(TextureType type, uint mipMapLevelCount, uint sampleCount,
  bool fixedSampleLocations)
  : mGlTextureHandle(gl::TextureHandle::create(static_cast<GLenum>(type)))
  , mMipMapLevelCount(mipMapLevelCount)
  , mSampleCount(sampleCount)
  , mFixedSampleLocations(fixedSampleLocations)
{}



Texture::Texture(Texture&& other)
  : mGlTextureHandle(std::move(other.mGlTextureHandle))
  , mMipMapLevelCount(std::move(other.mMipMapLevelCount))
  , mSampleCount(std::move(other.mSampleCount))
  , mFixedSampleLocations(std::move(other.mFixedSampleLocations))
{}



Texture::~Texture()
{}



const gl::TextureHandle& Texture::getHandle() const
{
  return mGlTextureHandle;
}



bool Texture::isBound(uint textureUnit) const
{
  HOU_EXPECT(textureUnit < getTextureUnitCount());
  return gl::isTextureBound(mGlTextureHandle, textureUnit);
}



TextureFormat Texture::get_format() const
{
  return TextureFormat(gl::getTextureFormat(mGlTextureHandle));
}



uint Texture::getMipMapLevelCount() const
{
  return mMipMapLevelCount;
}



uint Texture::getSampleCount() const
{
  return mSampleCount;
}



bool Texture::hasFixedSampleLocations() const
{
  return mFixedSampleLocations;
}



TextureChannelMapping Texture::getChannelMapping() const
{
  return TextureChannelMapping(
    TextureChannel(getTextureSwizzleR(mGlTextureHandle)),
    TextureChannel(getTextureSwizzleG(mGlTextureHandle)),
    TextureChannel(getTextureSwizzleB(mGlTextureHandle)),
    TextureChannel(getTextureSwizzleA(mGlTextureHandle)));
}



void Texture::setChannelMapping(const TextureChannelMapping& mapping)
{
  setTextureSwizzleR(mGlTextureHandle, static_cast<GLenum>(mapping.get_r()));
  setTextureSwizzleG(mGlTextureHandle, static_cast<GLenum>(mapping.get_g()));
  setTextureSwizzleB(mGlTextureHandle, static_cast<GLenum>(mapping.get_b()));
  setTextureSwizzleA(mGlTextureHandle, static_cast<GLenum>(mapping.get_a()));
}



uint Texture::getWidth() const
{
  return static_cast<uint>(gl::getTextureWidth(mGlTextureHandle, 0));
}



uint Texture::getHeight() const
{
  return static_cast<uint>(gl::getTextureHeight(mGlTextureHandle, 0));
}



uint Texture::getDepth() const
{
  return static_cast<uint>(gl::getTextureDepth(mGlTextureHandle, 0));
}



vec1u Texture::getSize1() const
{
  return vec1u(getWidth());
}



vec2u Texture::getSize2() const
{
  return vec2u(getWidth(), getHeight());
}



vec3u Texture::getSize3() const
{
  return vec3u(getWidth(), getHeight(), getDepth());
}



template <>
vec1u TextureT<TextureType::Texture1>::getMaxSize()
{
  return vec1u(static_cast<uint>(gl::getMaxTextureSize()));
}



template <>
vec2u TextureT<TextureType::Texture1Array>::getMaxSize()
{
  return vec2u(static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureLayers()));
}



template <>
vec2u TextureT<TextureType::Texture2>::getMaxSize()
{
  return vec2u(static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureSize()));
}



template <>
vec3u TextureT<TextureType::Texture2Array>::getMaxSize()
{
  return vec3u(static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureLayers()));
}



template <>
vec3u TextureT<TextureType::Texture3>::getMaxSize()
{
  return vec3u(static_cast<uint>(gl::getMax3dTextureSize()),
    static_cast<uint>(gl::getMax3dTextureSize()),
    static_cast<uint>(gl::getMax3dTextureSize()));
}



template <>
vec2u TextureT<TextureType::MultisampleTexture2>::getMaxSize()
{
  return vec2u(static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureSize()));
}



template <>
vec3u TextureT<TextureType::MultisampleTexture2Array>::getMaxSize()
{
  return vec3u(static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureLayers()));
}



template <TextureType type>
uint TextureT<type>::getMaxMipMapLevelCount(const size_type& size)
{
  return isTextureTypeMipMapped(type)
    ? getMaxMipMapLevelCountForSize<type>(size)
    : 1u;
}



template <TextureType type>
uint TextureT<type>::getMaxSampleCount()
{
  return isTextureTypeMultisampled(type) ? gl::getMaxTextureSamples() : 1u;
}



template <>
template <>
TextureT<TextureType::Texture1>::TextureT<TextureType::Texture1, void>(
  const size_type& size, TextureFormat format, uint mipMapLevelCount)
  : Texture(TextureType::Texture1, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::Texture1>(size)
    && isMipMapLevelCountValid<TextureType::Texture1>(mipMapLevelCount, size));
  gl::setTextureStorage1d(
    mGlTextureHandle, mipMapLevelCount, static_cast<GLenum>(format), size.x());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <>
template <>
TextureT<TextureType::Texture1Array>::TextureT<TextureType::Texture1Array,
  void>(const size_type& size, TextureFormat format, uint mipMapLevelCount)
  : Texture(TextureType::Texture1Array, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::Texture1Array>(size)
    && isMipMapLevelCountValid<TextureType::Texture1Array>(
         mipMapLevelCount, size));
  gl::setTextureStorage2d(mGlTextureHandle, mipMapLevelCount,
    static_cast<GLenum>(format), size.x(), size.y());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <>
template <>
TextureT<TextureType::Texture2>::TextureT<TextureType::Texture2, void>(
  const size_type& size, TextureFormat format, uint mipMapLevelCount)
  : Texture(TextureType::Texture2, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::Texture2>(size)
    && isMipMapLevelCountValid<TextureType::Texture2>(mipMapLevelCount, size));
  gl::setTextureStorage2d(mGlTextureHandle, mipMapLevelCount,
    static_cast<GLenum>(format), size.x(), size.y());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <>
template <>
TextureT<TextureType::Texture2Array>::TextureT<TextureType::Texture2Array,
  void>(const size_type& size, TextureFormat format, uint mipMapLevelCount)
  : Texture(TextureType::Texture2Array, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::Texture2Array>(size)
    && isMipMapLevelCountValid<TextureType::Texture2Array>(
         mipMapLevelCount, size));
  gl::setTextureStorage3d(mGlTextureHandle, mipMapLevelCount,
    static_cast<GLenum>(format), size.x(), size.y(), size.z());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <>
template <>
TextureT<TextureType::Texture3>::TextureT<TextureType::Texture3, void>(
  const size_type& size, TextureFormat format, uint mipMapLevelCount)
  : Texture(TextureType::Texture3, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::Texture3>(size)
    && isMipMapLevelCountValid<TextureType::Texture3>(mipMapLevelCount, size));
  gl::setTextureStorage3d(mGlTextureHandle, mipMapLevelCount,
    static_cast<GLenum>(format), size.x(), size.y(), size.z());
  clear(pixelrgba(0u, 0u, 0u, 0u));
}



template <TextureType type>
template <pixel_format fmt, TextureType t, typename Enable>
TextureT<type>::TextureT(
  const image<fmt>& ph_image, TextureFormat format, uint mipMapLevelCount)
  : TextureT(ph_image.get_size(), format, mipMapLevelCount)
{
  set_image(ph_image);
}



template <>
template <TextureType t, typename Enable>
TextureT<TextureType::MultisampleTexture2>::TextureT(const size_type& size,
  TextureFormat format, uint sampleCount, bool fixedSampleLocations)
  : Texture(
      TextureType::MultisampleTexture2, 1u, sampleCount, fixedSampleLocations)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::MultisampleTexture2>(size)
    && sampleCount > 0u
    && sampleCount <= static_cast<uint>(gl::getMaxTextureSamples()));
  setTextureStorage2dMultisample(mGlTextureHandle, sampleCount,
    static_cast<GLenum>(format), size.x(), size.y(), fixedSampleLocations);
}



template <>
template <TextureType t, typename Enable>
TextureT<TextureType::MultisampleTexture2Array>::TextureT(const size_type& size,
  TextureFormat format, uint sampleCount, bool fixedSampleLocations)
  : Texture(TextureType::MultisampleTexture2Array, 1u, sampleCount,
      fixedSampleLocations)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::MultisampleTexture2Array>(size)
    && sampleCount > 0u
    && sampleCount <= static_cast<uint>(gl::getMaxTextureSamples()));
  setTextureStorage3dMultisample(mGlTextureHandle, sampleCount,
    static_cast<GLenum>(format), size.x(), size.y(), size.z(),
    fixedSampleLocations);
}



template <TextureType type>
TextureT<type>::TextureT(TextureT&& other)
  : Texture(std::move(other))
{}



template <TextureType type>
TextureT<type>::~TextureT()
{}



template <>
typename TextureT<TextureType::Texture1>::size_type
  TextureT<TextureType::Texture1>::get_size() const
{
  return getSize1();
}



template <>
typename TextureT<TextureType::Texture1Array>::size_type
  TextureT<TextureType::Texture1Array>::get_size() const
{
  return getSize2();
}



template <>
typename TextureT<TextureType::Texture2>::size_type
  TextureT<TextureType::Texture2>::get_size() const
{
  return getSize2();
}



template <>
typename TextureT<TextureType::Texture2Array>::size_type
  TextureT<TextureType::Texture2Array>::get_size() const
{
  return getSize3();
}



template <>
typename TextureT<TextureType::Texture3>::size_type
  TextureT<TextureType::Texture3>::get_size() const
{
  return getSize3();
}



template <>
typename TextureT<TextureType::MultisampleTexture2>::size_type
  TextureT<TextureType::MultisampleTexture2>::get_size() const
{
  return getSize2();
}



template <>
typename TextureT<TextureType::MultisampleTexture2Array>::size_type
  TextureT<TextureType::MultisampleTexture2Array>::get_size() const
{
  return getSize3();
}



template <TextureType type>
template <TextureType t, typename Enable>
TextureFilter TextureT<type>::getFilter() const
{
  switch(getTextureMinFilter(mGlTextureHandle))
  {
  case GL_NEAREST_MIPMAP_NEAREST:
    return TextureFilter::Nearest;
  case GL_NEAREST_MIPMAP_LINEAR:
    return TextureFilter::Linear;
  case GL_LINEAR_MIPMAP_NEAREST:
    return TextureFilter::Bilinear;
  case GL_LINEAR_MIPMAP_LINEAR:
    return TextureFilter::Trilinear;
  default:
    HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum),
      static_cast<GLenum>(getTextureMinFilter(mGlTextureHandle)));
  }
}



template <TextureType type>
template <TextureType t, typename Enable>
void TextureT<type>::setFilter(TextureFilter filter)
{
  switch(filter)
  {
  case TextureFilter::Nearest:
    setTextureMinFilter(mGlTextureHandle, GL_NEAREST_MIPMAP_NEAREST);
    setTextureMagFilter(mGlTextureHandle, GL_NEAREST);
    break;
  case TextureFilter::Linear:
    setTextureMinFilter(mGlTextureHandle, GL_NEAREST_MIPMAP_LINEAR);
    setTextureMagFilter(mGlTextureHandle, GL_NEAREST);
    break;
  case TextureFilter::Bilinear:
    setTextureMinFilter(mGlTextureHandle, GL_LINEAR_MIPMAP_NEAREST);
    setTextureMagFilter(mGlTextureHandle, GL_LINEAR);
    break;
  case TextureFilter::Trilinear:
    setTextureMinFilter(mGlTextureHandle, GL_LINEAR_MIPMAP_LINEAR);
    setTextureMagFilter(mGlTextureHandle, GL_LINEAR);
    break;
  default:
    HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<int>(filter));
    break;
  }
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture1>::WrapMode
  TextureT<TextureType::Texture1>::getWrapMode() const
{
  return getTexture1WrapMode(mGlTextureHandle);
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture1Array>::WrapMode
  TextureT<TextureType::Texture1Array>::getWrapMode() const
{
  return getTexture2WrapMode(mGlTextureHandle);
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture2>::WrapMode
  TextureT<TextureType::Texture2>::getWrapMode() const
{
  return getTexture2WrapMode(mGlTextureHandle);
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture2Array>::WrapMode
  TextureT<TextureType::Texture2Array>::getWrapMode() const
{
  return getTexture3WrapMode(mGlTextureHandle);
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture3>::WrapMode
  TextureT<TextureType::Texture3>::getWrapMode() const
{
  return getTexture3WrapMode(mGlTextureHandle);
}



template <>
template <TextureType t, typename Enable>
void TextureT<TextureType::Texture1>::setWrapMode(const WrapMode& wrapMode)
{
  setTexture1WrapMode(mGlTextureHandle, wrapMode);
}



template <>
template <TextureType t, typename Enable>
void TextureT<TextureType::Texture1Array>::setWrapMode(const WrapMode& wrapMode)
{
  setTexture2WrapMode(mGlTextureHandle, wrapMode);
}



template <>
template <TextureType t, typename Enable>
void TextureT<TextureType::Texture2>::setWrapMode(const WrapMode& wrapMode)
{
  setTexture2WrapMode(mGlTextureHandle, wrapMode);
}



template <>
template <TextureType t, typename Enable>
void TextureT<TextureType::Texture2Array>::setWrapMode(const WrapMode& wrapMode)
{
  setTexture3WrapMode(mGlTextureHandle, wrapMode);
}



template <>
template <TextureType t, typename Enable>
void TextureT<TextureType::Texture3>::setWrapMode(const WrapMode& wrapMode)
{
  setTexture3WrapMode(mGlTextureHandle, wrapMode);
}



template <TextureType type>
template <pixel_format fmt, TextureType t, typename Enable>
typename TextureT<type>::template image<fmt> TextureT<type>::get_image() const
{
  gl::setUnpackAlignment(1);
  size_type size = get_size();
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::getTextureImage(mGlTextureHandle, 0u, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()), buffer.size(), buffer.data());
  return image<fmt>(size,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
typename TextureT<TextureType::Texture1>::template image<fmt>
  TextureT<TextureType::Texture1>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, get_size()));
  gl::setUnpackAlignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::getTextureSubImage(mGlTextureHandle, offset.x(), 0, 0, size.x(), 1, 1, 0,
    pixelFormatToGlPixelFormat(fmt), static_cast<GLenum>(toGlType<uint8_t>()),
    buffer.size(), buffer.data());
  return image<fmt>(size,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
typename TextureT<TextureType::Texture1Array>::template image<fmt>
  TextureT<TextureType::Texture1Array>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, get_size()));
  gl::setUnpackAlignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::getTextureSubImage(mGlTextureHandle, offset.x(), offset.y(), 0, size.x(),
    size.y(), 1, 0, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()), buffer.size(), buffer.data());
  return image<fmt>(size,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
typename TextureT<TextureType::Texture2>::template image<fmt>
  TextureT<TextureType::Texture2>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, get_size()));
  gl::setUnpackAlignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::getTextureSubImage(mGlTextureHandle, offset.x(), offset.y(), 0, size.x(),
    size.y(), 1, 0, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()), buffer.size(), buffer.data());
  return image<fmt>(size,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
typename TextureT<TextureType::Texture2Array>::template image<fmt>
  TextureT<TextureType::Texture2Array>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, get_size()));
  gl::setUnpackAlignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::getTextureSubImage(mGlTextureHandle, offset.x(), offset.y(), offset.z(),
    size.x(), size.y(), size.z(), 0, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()), buffer.size(), buffer.data());
  return image<fmt>(size,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
typename TextureT<TextureType::Texture3>::template image<fmt>
  TextureT<TextureType::Texture3>::get_sub_image(
    const offset_type& offset, const size_type& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, get_size()));
  gl::setUnpackAlignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::getTextureSubImage(mGlTextureHandle, offset.x(), offset.y(), offset.z(),
    size.x(), size.y(), size.z(), 0, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()), buffer.size(), buffer.data());
  return image<fmt>(size,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <TextureType type>
template <pixel_format fmt, TextureType t, typename Enable>
void TextureT<type>::set_image(const image<fmt>& ph_image)
{
  HOU_EXPECT(ph_image.get_size() == get_size());
  set_sub_image<fmt>(offset_type::zero(), ph_image);
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
void TextureT<TextureType::Texture1>::set_sub_image(
  const offset_type& offset, const image<fmt>& ph_image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + ph_image.get_size(), get_size()));
  gl::setTextureSubImage1d(mGlTextureHandle, 0u, offset.x(),
    ph_image.get_size().x(), pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()),
    reinterpret_cast<const void*>(ph_image.get_pixels().data()));
  generateMipMap();
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
void TextureT<TextureType::Texture1Array>::set_sub_image(
  const offset_type& offset, const image<fmt>& ph_image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + ph_image.get_size(), get_size()));
  gl::setTextureSubImage2d(mGlTextureHandle, 0, offset.x(), offset.y(),
    ph_image.get_size().x(), ph_image.get_size().y(), pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()),
    reinterpret_cast<const void*>(ph_image.get_pixels().data()));
  generateMipMap();
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
void TextureT<TextureType::Texture2>::set_sub_image(
  const offset_type& offset, const image<fmt>& ph_image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + ph_image.get_size(), get_size()));
  gl::setTextureSubImage2d(mGlTextureHandle, 0, offset.x(), offset.y(),
    ph_image.get_size().x(), ph_image.get_size().y(), pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()),
    reinterpret_cast<const void*>(ph_image.get_pixels().data()));
  generateMipMap();
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
void TextureT<TextureType::Texture2Array>::set_sub_image(
  const offset_type& offset, const image<fmt>& ph_image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + ph_image.get_size(), get_size()));
  gl::setTextureSubImage3d(mGlTextureHandle, 0, offset.x(), offset.y(),
    offset.z(), ph_image.get_size().x(), ph_image.get_size().y(), ph_image.get_size().z(),
    pixelFormatToGlPixelFormat(fmt), static_cast<GLenum>(toGlType<uint8_t>()),
    reinterpret_cast<const void*>(ph_image.get_pixels().data()));
  generateMipMap();
}



template <>
template <pixel_format fmt, TextureType t, typename Enable>
void TextureT<TextureType::Texture3>::set_sub_image(
  const offset_type& offset, const image<fmt>& ph_image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + ph_image.get_size(), get_size()));
  gl::setTextureSubImage3d(mGlTextureHandle, 0, offset.x(), offset.y(),
    offset.z(), ph_image.get_size().x(), ph_image.get_size().y(), ph_image.get_size().z(),
    pixelFormatToGlPixelFormat(fmt), static_cast<GLenum>(toGlType<uint8_t>()),
    reinterpret_cast<const void*>(ph_image.get_pixels().data()));
  generateMipMap();
}



template <TextureType type>
template <pixel_format fmt, TextureType t, typename Enable>
void TextureT<type>::clear(const pixel_t<fmt>& ph_pixel)
{
  set_image(image<fmt>(get_size(), ph_pixel));
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture1>::size_type
  TextureT<TextureType::Texture1>::getMipMapSize(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < mMipMapLevelCount);
  return getTexture1Size(mGlTextureHandle, mipMapLevel);
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture1Array>::size_type
  TextureT<TextureType::Texture1Array>::getMipMapSize(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < mMipMapLevelCount);
  return getTexture2Size(mGlTextureHandle, mipMapLevel);
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture2>::size_type
  TextureT<TextureType::Texture2>::getMipMapSize(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < mMipMapLevelCount);
  return getTexture2Size(mGlTextureHandle, mipMapLevel);
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture2Array>::size_type
  TextureT<TextureType::Texture2Array>::getMipMapSize(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < mMipMapLevelCount);
  return getTexture3Size(mGlTextureHandle, mipMapLevel);
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture3>::size_type
  TextureT<TextureType::Texture3>::getMipMapSize(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < mMipMapLevelCount);
  return getTexture3Size(mGlTextureHandle, mipMapLevel);
}



template <TextureType type>
template <pixel_format fmt, TextureType t, typename Enable>
typename TextureT<type>::template image<fmt> TextureT<type>::getMipMapImage(
  uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < mMipMapLevelCount);
  gl::setUnpackAlignment(1);
  size_type mipMapSize = getMipMapSize(mipMapLevel);
  std::vector<uint8_t> buffer(computeImageBufferSize(mipMapSize, fmt));
  gl::getTextureImage(mGlTextureHandle, mipMapLevel,
    pixelFormatToGlPixelFormat(fmt), static_cast<GLenum>(toGlType<uint8_t>()),
    buffer.size(), buffer.data());
  return image<fmt>(mipMapSize,
    reinterpret_span<const typename image<fmt>::pixel>(span<uint8_t>(buffer)));
}



template <TextureType type>
TextureType TextureT<type>::get_type() const
{
  return type;
}



template <TextureType type>
size_t TextureT<type>::get_dimension_count() const
{
  return getTextureTypeDimensionCount(type);
}



template <TextureType type>
bool TextureT<type>::isMipMapped() const
{
  return isTextureTypeMipMapped(type);
}



template <TextureType type>
bool TextureT<type>::isMultisampled() const
{
  return isTextureTypeMultisampled(type);
}



template <TextureType type>
void TextureT<type>::generateMipMap()
{
  if(mMipMapLevelCount > 1u)
  {
    gl::generateMipMap(mGlTextureHandle);
  }
}



#define INSTANTIATE_TEXTURE(tt) template class TextureT<tt>;



#define INSTANTIATE_TEXTURE_MIP_MAP_FUNCTIONS(tt)                   \
  template TextureT<tt>::TextureT<tt, void>(                        \
    const TextureT<tt>::size_type&, TextureFormat, uint);                \
  template typename TextureT<tt>::WrapMode                          \
    TextureT<tt>::getWrapMode<tt, void>() const;                    \
  template void TextureT<tt>::setWrapMode<tt, void>(                \
    const typename TextureT<tt>::WrapMode&);                        \
  template TextureFilter TextureT<tt>::getFilter<tt, void>() const; \
  template void TextureT<tt>::setFilter<tt, void>(TextureFilter);   \
  template TextureT<tt>::size_type TextureT<tt>::getMipMapSize<tt, void>(uint) const;



#define INSTANTIATE_TEXTURE_MULTISAMPLE_FUNCTIONS(tt) \
  template TextureT<tt>::TextureT<tt, void>(          \
    const TextureT<tt>::size_type&, TextureFormat, uint, bool);



#define INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, pf)           \
  template TextureT<tt>::TextureT<pf, tt, void>(                               \
    const TextureT<tt>::image<pf>&, TextureFormat, uint);                      \
  template TextureT<tt>::image<pf> TextureT<tt>::get_image<pf, tt, void>()      \
    const;                                                                     \
  template TextureT<tt>::image<pf> TextureT<tt>::get_sub_image<pf, tt, void>(    \
    const TextureT<tt>::offset_type&, const TextureT<tt>::size_type&) const;        \
  template void TextureT<tt>::set_image<pf, tt, void>(                          \
    const TextureT<tt>::image<pf>&);                                           \
  template void TextureT<tt>::set_sub_image<pf, tt, void>(                       \
    const TextureT<tt>::offset_type&, const TextureT<tt>::image<pf>&);         \
  template void TextureT<tt>::clear<pf, tt, void>(const pixel_t<pf>&);          \
  template TextureT<tt>::image<pf> TextureT<tt>::getMipMapImage<pf, tt, void>( \
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



INSTANTIATE_TEXTURE_MIP_MAP(TextureType::Texture1)
INSTANTIATE_TEXTURE_MIP_MAP(TextureType::Texture1Array)
INSTANTIATE_TEXTURE_MIP_MAP(TextureType::Texture2)
INSTANTIATE_TEXTURE_MIP_MAP(TextureType::Texture2Array)
INSTANTIATE_TEXTURE_MIP_MAP(TextureType::Texture3)
INSTANTIATE_TEXTURE_MULTISAMPLE(TextureType::MultisampleTexture2)
INSTANTIATE_TEXTURE_MULTISAMPLE(TextureType::MultisampleTexture2Array)

}  // namespace hou
