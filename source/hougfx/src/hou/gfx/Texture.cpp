// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/Texture.hpp"

#include "hou/mth/Matrix.hpp"
#include "hou/mth/MathFunctions.hpp"

#include "hou/gfx/GlType.hpp"
#include "hou/gfx/TextureChannelMapping.hpp"



namespace hou
{

namespace
{

GLenum pixelFormatToGlPixelFormat(PixelFormat format);

template <TextureType type>
bool isTextureSizeValid(const typename TextureT<type>::Size& size);

template <TextureType type>
bool isMipMapLevelCountValid(
  uint mipMapLevelCount, const typename TextureT<type>::Size& size);

template <TextureType type>
uint getMaxMipMapLevelCountForSize(const typename TextureT<type>::Size& size);

template <TextureType type>
uint getMipMapRelevantSize(const typename TextureT<type>::Size& size);

template <size_t dim>
size_t computeImageBufferSize(const Vec<uint, dim>& imSize, PixelFormat fmt);

template <size_t dim>
bool elementWiseLowerOrEqual(
  const Vec<uint, dim>& lhs, const Vec<uint, dim>& rhs);

Vec1u getTexture1Size(const gl::TextureHandle& th, uint mipMapLevel);

Vec2u getTexture2Size(const gl::TextureHandle& th, uint mipMapLevel);

Vec3u getTexture3Size(const gl::TextureHandle& th, uint mipMapLevel);

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



GLenum pixelFormatToGlPixelFormat(PixelFormat format)
{
  switch(format)
  {
  case PixelFormat::R:
    return GL_RED;
  case PixelFormat::RG:
    return GL_RG;
  case PixelFormat::RGB:
    return GL_RGB;
  case PixelFormat::RGBA:
    return GL_RGBA;
  default:
    return GL_RED;
  }
}



template <TextureType type>
bool isTextureSizeValid(const typename TextureT<type>::Size& size)
{
  using Tex = TextureT<type>;
  typename Tex::Size maxSize = Tex::getMaxSize();
  for(size_t i = 0; i < size.getSize(); ++i)
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
  uint mipMapLevelCount, const typename TextureT<type>::Size& size)
{
  return mipMapLevelCount > 0
    && mipMapLevelCount <= getMaxMipMapLevelCountForSize<type>(size);
}



template <TextureType type>
uint getMaxMipMapLevelCountForSize(const typename TextureT<type>::Size& size)
{
  return 1u
    + static_cast<uint>(
        log(static_cast<float>(getMipMapRelevantSize<type>(size)), 2));
}



template <>
uint getMipMapRelevantSize<TextureType::Texture1>(
  const typename TextureT<TextureType::Texture1>::Size& size)
{
  return size(0);
}



template <>
uint getMipMapRelevantSize<TextureType::Texture1Array>(
  const typename TextureT<TextureType::Texture1Array>::Size& size)
{
  return size(0);
}



template <>
uint getMipMapRelevantSize<TextureType::Texture2>(
  const typename TextureT<TextureType::Texture2>::Size& size)
{
  return std::max(size(0), size(1));
}



template <>
uint getMipMapRelevantSize<TextureType::Texture2Array>(
  const typename TextureT<TextureType::Texture2Array>::Size& size)
{
  return std::max(size(0), size(1));
}



template <>
uint getMipMapRelevantSize<TextureType::Texture3>(
  const typename TextureT<TextureType::Texture3>::Size& size)
{
  return std::max(std::max(size(0), size(1)), size(2));
}



template <>
uint getMipMapRelevantSize<TextureType::MultisampleTexture2>(
  const typename TextureT<TextureType::MultisampleTexture2>::Size&)
{
  return 1u;
}



template <>
uint getMipMapRelevantSize<TextureType::MultisampleTexture2Array>(
  const typename TextureT<TextureType::MultisampleTexture2Array>::Size&)
{
  return 1u;
}



template <size_t dim>
size_t computeImageBufferSize(const Vec<uint, dim>& imSize, PixelFormat fmt)
{
  HOU_EXPECT_DEV(gl::getUnpackAlignment() == 1u);
  size_t byteCount = 1u;
  for(size_t i = 0; i < imSize.getSize(); ++i)
  {
    byteCount *= imSize(i);
  }
  return byteCount * getPixelFormatByteCount(fmt);
}



template <size_t dim>
bool elementWiseLowerOrEqual(
  const Vec<uint, dim>& lhs, const Vec<uint, dim>& rhs)
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



Vec1u getTexture1Size(const gl::TextureHandle& th, uint mipMapLevel)
{
  return Vec1u(static_cast<uint>(gl::getTextureWidth(th, mipMapLevel)));
}



Vec2u getTexture2Size(const gl::TextureHandle& th, uint mipMapLevel)
{
  return Vec2u(static_cast<uint>(gl::getTextureWidth(th, mipMapLevel)),
    static_cast<uint>(gl::getTextureHeight(th, mipMapLevel)));
}



Vec3u getTexture3Size(const gl::TextureHandle& th, uint mipMapLevel)
{
  return Vec3u(static_cast<uint>(gl::getTextureWidth(th, mipMapLevel)),
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



TextureFormat Texture::getFormat() const
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
  setTextureSwizzleR(mGlTextureHandle, static_cast<GLenum>(mapping.getR()));
  setTextureSwizzleG(mGlTextureHandle, static_cast<GLenum>(mapping.getG()));
  setTextureSwizzleB(mGlTextureHandle, static_cast<GLenum>(mapping.getB()));
  setTextureSwizzleA(mGlTextureHandle, static_cast<GLenum>(mapping.getA()));
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



Vec1u Texture::getSize1() const
{
  return Vec1u(getWidth());
}



Vec2u Texture::getSize2() const
{
  return Vec2u(getWidth(), getHeight());
}



Vec3u Texture::getSize3() const
{
  return Vec3u(getWidth(), getHeight(), getDepth());
}



template <>
Vec1u TextureT<TextureType::Texture1>::getMaxSize()
{
  return Vec1u(static_cast<uint>(gl::getMaxTextureSize()));
}



template <>
Vec2u TextureT<TextureType::Texture1Array>::getMaxSize()
{
  return Vec2u(static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureLayers()));
}



template <>
Vec2u TextureT<TextureType::Texture2>::getMaxSize()
{
  return Vec2u(static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureSize()));
}



template <>
Vec3u TextureT<TextureType::Texture2Array>::getMaxSize()
{
  return Vec3u(static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureLayers()));
}



template <>
Vec3u TextureT<TextureType::Texture3>::getMaxSize()
{
  return Vec3u(static_cast<uint>(gl::getMax3dTextureSize()),
    static_cast<uint>(gl::getMax3dTextureSize()),
    static_cast<uint>(gl::getMax3dTextureSize()));
}



template <>
Vec2u TextureT<TextureType::MultisampleTexture2>::getMaxSize()
{
  return Vec2u(static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureSize()));
}



template <>
Vec3u TextureT<TextureType::MultisampleTexture2Array>::getMaxSize()
{
  return Vec3u(static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureSize()),
    static_cast<uint>(gl::getMaxTextureLayers()));
}



template <TextureType type>
uint TextureT<type>::getMaxMipMapLevelCount(const Size& size)
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
  const Size& size, TextureFormat format, uint mipMapLevelCount)
  : Texture(TextureType::Texture1, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::Texture1>(size)
    && isMipMapLevelCountValid<TextureType::Texture1>(mipMapLevelCount, size));
  gl::setTextureStorage1d(
    mGlTextureHandle, mipMapLevelCount, static_cast<GLenum>(format), size.x());
  clear(PixelRGBA(0u, 0u, 0u, 0u));
}



template <>
template <>
TextureT<TextureType::Texture1Array>::TextureT<TextureType::Texture1Array,
  void>(const Size& size, TextureFormat format, uint mipMapLevelCount)
  : Texture(TextureType::Texture1Array, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::Texture1Array>(size)
    && isMipMapLevelCountValid<TextureType::Texture1Array>(
         mipMapLevelCount, size));
  gl::setTextureStorage2d(mGlTextureHandle, mipMapLevelCount,
    static_cast<GLenum>(format), size.x(), size.y());
  clear(PixelRGBA(0u, 0u, 0u, 0u));
}



template <>
template <>
TextureT<TextureType::Texture2>::TextureT<TextureType::Texture2, void>(
  const Size& size, TextureFormat format, uint mipMapLevelCount)
  : Texture(TextureType::Texture2, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::Texture2>(size)
    && isMipMapLevelCountValid<TextureType::Texture2>(mipMapLevelCount, size));
  gl::setTextureStorage2d(mGlTextureHandle, mipMapLevelCount,
    static_cast<GLenum>(format), size.x(), size.y());
  clear(PixelRGBA(0u, 0u, 0u, 0u));
}



template <>
template <>
TextureT<TextureType::Texture2Array>::TextureT<TextureType::Texture2Array,
  void>(const Size& size, TextureFormat format, uint mipMapLevelCount)
  : Texture(TextureType::Texture2Array, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::Texture2Array>(size)
    && isMipMapLevelCountValid<TextureType::Texture2Array>(
         mipMapLevelCount, size));
  gl::setTextureStorage3d(mGlTextureHandle, mipMapLevelCount,
    static_cast<GLenum>(format), size.x(), size.y(), size.z());
  clear(PixelRGBA(0u, 0u, 0u, 0u));
}



template <>
template <>
TextureT<TextureType::Texture3>::TextureT<TextureType::Texture3, void>(
  const Size& size, TextureFormat format, uint mipMapLevelCount)
  : Texture(TextureType::Texture3, mipMapLevelCount, 1u, true)
{
  HOU_EXPECT(isTextureSizeValid<TextureType::Texture3>(size)
    && isMipMapLevelCountValid<TextureType::Texture3>(mipMapLevelCount, size));
  gl::setTextureStorage3d(mGlTextureHandle, mipMapLevelCount,
    static_cast<GLenum>(format), size.x(), size.y(), size.z());
  clear(PixelRGBA(0u, 0u, 0u, 0u));
}



template <TextureType type>
template <PixelFormat fmt, TextureType t, typename Enable>
TextureT<type>::TextureT(
  const Image<fmt>& image, TextureFormat format, uint mipMapLevelCount)
  : TextureT(image.getSize(), format, mipMapLevelCount)
{
  setImage(image);
}



template <>
template <TextureType t, typename Enable>
TextureT<TextureType::MultisampleTexture2>::TextureT(const Size& size,
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
TextureT<TextureType::MultisampleTexture2Array>::TextureT(const Size& size,
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
typename TextureT<TextureType::Texture1>::Size
  TextureT<TextureType::Texture1>::getSize() const
{
  return getSize1();
}



template <>
typename TextureT<TextureType::Texture1Array>::Size
  TextureT<TextureType::Texture1Array>::getSize() const
{
  return getSize2();
}



template <>
typename TextureT<TextureType::Texture2>::Size
  TextureT<TextureType::Texture2>::getSize() const
{
  return getSize2();
}



template <>
typename TextureT<TextureType::Texture2Array>::Size
  TextureT<TextureType::Texture2Array>::getSize() const
{
  return getSize3();
}



template <>
typename TextureT<TextureType::Texture3>::Size
  TextureT<TextureType::Texture3>::getSize() const
{
  return getSize3();
}



template <>
typename TextureT<TextureType::MultisampleTexture2>::Size
  TextureT<TextureType::MultisampleTexture2>::getSize() const
{
  return getSize2();
}



template <>
typename TextureT<TextureType::MultisampleTexture2Array>::Size
  TextureT<TextureType::MultisampleTexture2Array>::getSize() const
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
template <PixelFormat fmt, TextureType t, typename Enable>
typename TextureT<type>::template Image<fmt> TextureT<type>::getImage() const
{
  gl::setUnpackAlignment(1);
  Size size = getSize();
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::getTextureImage(mGlTextureHandle, 0u, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()), buffer.size(), buffer.data());
  return Image<fmt>(size,
    reinterpret_span<const typename Image<fmt>::Pixel>(span<uint8_t>(buffer)));
}



template <>
template <PixelFormat fmt, TextureType t, typename Enable>
typename TextureT<TextureType::Texture1>::template Image<fmt>
  TextureT<TextureType::Texture1>::getSubImage(
    const Coordinates& offset, const Size& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, getSize()));
  gl::setUnpackAlignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::getTextureSubImage(mGlTextureHandle, offset.x(), 0, 0, size.x(), 1, 1, 0,
    pixelFormatToGlPixelFormat(fmt), static_cast<GLenum>(toGlType<uint8_t>()),
    buffer.size(), buffer.data());
  return Image<fmt>(size,
    reinterpret_span<const typename Image<fmt>::Pixel>(span<uint8_t>(buffer)));
}



template <>
template <PixelFormat fmt, TextureType t, typename Enable>
typename TextureT<TextureType::Texture1Array>::template Image<fmt>
  TextureT<TextureType::Texture1Array>::getSubImage(
    const Coordinates& offset, const Size& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, getSize()));
  gl::setUnpackAlignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::getTextureSubImage(mGlTextureHandle, offset.x(), offset.y(), 0, size.x(),
    size.y(), 1, 0, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()), buffer.size(), buffer.data());
  return Image<fmt>(size,
    reinterpret_span<const typename Image<fmt>::Pixel>(span<uint8_t>(buffer)));
}



template <>
template <PixelFormat fmt, TextureType t, typename Enable>
typename TextureT<TextureType::Texture2>::template Image<fmt>
  TextureT<TextureType::Texture2>::getSubImage(
    const Coordinates& offset, const Size& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, getSize()));
  gl::setUnpackAlignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::getTextureSubImage(mGlTextureHandle, offset.x(), offset.y(), 0, size.x(),
    size.y(), 1, 0, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()), buffer.size(), buffer.data());
  return Image<fmt>(size,
    reinterpret_span<const typename Image<fmt>::Pixel>(span<uint8_t>(buffer)));
}



template <>
template <PixelFormat fmt, TextureType t, typename Enable>
typename TextureT<TextureType::Texture2Array>::template Image<fmt>
  TextureT<TextureType::Texture2Array>::getSubImage(
    const Coordinates& offset, const Size& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, getSize()));
  gl::setUnpackAlignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::getTextureSubImage(mGlTextureHandle, offset.x(), offset.y(), offset.z(),
    size.x(), size.y(), size.z(), 0, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()), buffer.size(), buffer.data());
  return Image<fmt>(size,
    reinterpret_span<const typename Image<fmt>::Pixel>(span<uint8_t>(buffer)));
}



template <>
template <PixelFormat fmt, TextureType t, typename Enable>
typename TextureT<TextureType::Texture3>::template Image<fmt>
  TextureT<TextureType::Texture3>::getSubImage(
    const Coordinates& offset, const Size& size) const
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, getSize()));
  gl::setUnpackAlignment(1);
  std::vector<uint8_t> buffer(computeImageBufferSize(size, fmt));
  gl::getTextureSubImage(mGlTextureHandle, offset.x(), offset.y(), offset.z(),
    size.x(), size.y(), size.z(), 0, pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()), buffer.size(), buffer.data());
  return Image<fmt>(size,
    reinterpret_span<const typename Image<fmt>::Pixel>(span<uint8_t>(buffer)));
}



template <TextureType type>
template <PixelFormat fmt, TextureType t, typename Enable>
void TextureT<type>::setImage(const Image<fmt>& image)
{
  HOU_EXPECT(image.getSize() == getSize());
  setSubImage<fmt>(Coordinates::zero(), image);
}



template <>
template <PixelFormat fmt, TextureType t, typename Enable>
void TextureT<TextureType::Texture1>::setSubImage(
  const Coordinates& offset, const Image<fmt>& image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + image.getSize(), getSize()));
  gl::setTextureSubImage1d(mGlTextureHandle, 0u, offset.x(),
    image.getSize().x(), pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()),
    reinterpret_cast<const void*>(image.getPixels().data()));
  generateMipMap();
}



template <>
template <PixelFormat fmt, TextureType t, typename Enable>
void TextureT<TextureType::Texture1Array>::setSubImage(
  const Coordinates& offset, const Image<fmt>& image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + image.getSize(), getSize()));
  gl::setTextureSubImage2d(mGlTextureHandle, 0, offset.x(), offset.y(),
    image.getSize().x(), image.getSize().y(), pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()),
    reinterpret_cast<const void*>(image.getPixels().data()));
  generateMipMap();
}



template <>
template <PixelFormat fmt, TextureType t, typename Enable>
void TextureT<TextureType::Texture2>::setSubImage(
  const Coordinates& offset, const Image<fmt>& image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + image.getSize(), getSize()));
  gl::setTextureSubImage2d(mGlTextureHandle, 0, offset.x(), offset.y(),
    image.getSize().x(), image.getSize().y(), pixelFormatToGlPixelFormat(fmt),
    static_cast<GLenum>(toGlType<uint8_t>()),
    reinterpret_cast<const void*>(image.getPixels().data()));
  generateMipMap();
}



template <>
template <PixelFormat fmt, TextureType t, typename Enable>
void TextureT<TextureType::Texture2Array>::setSubImage(
  const Coordinates& offset, const Image<fmt>& image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + image.getSize(), getSize()));
  gl::setTextureSubImage3d(mGlTextureHandle, 0, offset.x(), offset.y(),
    offset.z(), image.getSize().x(), image.getSize().y(), image.getSize().z(),
    pixelFormatToGlPixelFormat(fmt), static_cast<GLenum>(toGlType<uint8_t>()),
    reinterpret_cast<const void*>(image.getPixels().data()));
  generateMipMap();
}



template <>
template <PixelFormat fmt, TextureType t, typename Enable>
void TextureT<TextureType::Texture3>::setSubImage(
  const Coordinates& offset, const Image<fmt>& image)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + image.getSize(), getSize()));
  gl::setTextureSubImage3d(mGlTextureHandle, 0, offset.x(), offset.y(),
    offset.z(), image.getSize().x(), image.getSize().y(), image.getSize().z(),
    pixelFormatToGlPixelFormat(fmt), static_cast<GLenum>(toGlType<uint8_t>()),
    reinterpret_cast<const void*>(image.getPixels().data()));
  generateMipMap();
}



template <TextureType type>
template <PixelFormat fmt, TextureType t, typename Enable>
void TextureT<type>::clear(const PixelT<fmt>& pixel)
{
  setImage(Image<fmt>(getSize(), pixel));
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture1>::Size
  TextureT<TextureType::Texture1>::getMipMapSize(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < mMipMapLevelCount);
  return getTexture1Size(mGlTextureHandle, mipMapLevel);
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture1Array>::Size
  TextureT<TextureType::Texture1Array>::getMipMapSize(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < mMipMapLevelCount);
  return getTexture2Size(mGlTextureHandle, mipMapLevel);
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture2>::Size
  TextureT<TextureType::Texture2>::getMipMapSize(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < mMipMapLevelCount);
  return getTexture2Size(mGlTextureHandle, mipMapLevel);
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture2Array>::Size
  TextureT<TextureType::Texture2Array>::getMipMapSize(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < mMipMapLevelCount);
  return getTexture3Size(mGlTextureHandle, mipMapLevel);
}



template <>
template <TextureType t, typename Enable>
typename TextureT<TextureType::Texture3>::Size
  TextureT<TextureType::Texture3>::getMipMapSize(uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < mMipMapLevelCount);
  return getTexture3Size(mGlTextureHandle, mipMapLevel);
}



template <TextureType type>
template <PixelFormat fmt, TextureType t, typename Enable>
typename TextureT<type>::template Image<fmt> TextureT<type>::getMipMapImage(
  uint mipMapLevel) const
{
  HOU_EXPECT(mipMapLevel < mMipMapLevelCount);
  gl::setUnpackAlignment(1);
  Size mipMapSize = getMipMapSize(mipMapLevel);
  std::vector<uint8_t> buffer(computeImageBufferSize(mipMapSize, fmt));
  gl::getTextureImage(mGlTextureHandle, mipMapLevel,
    pixelFormatToGlPixelFormat(fmt), static_cast<GLenum>(toGlType<uint8_t>()),
    buffer.size(), buffer.data());
  return Image<fmt>(mipMapSize,
    reinterpret_span<const typename Image<fmt>::Pixel>(span<uint8_t>(buffer)));
}



template <TextureType type>
TextureType TextureT<type>::getType() const
{
  return type;
}



template <TextureType type>
size_t TextureT<type>::getDimensionCount() const
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
    const TextureT<tt>::Size&, TextureFormat, uint);                \
  template typename TextureT<tt>::WrapMode                          \
    TextureT<tt>::getWrapMode<tt, void>() const;                    \
  template void TextureT<tt>::setWrapMode<tt, void>(                \
    const typename TextureT<tt>::WrapMode&);                        \
  template TextureFilter TextureT<tt>::getFilter<tt, void>() const; \
  template void TextureT<tt>::setFilter<tt, void>(TextureFilter);   \
  template TextureT<tt>::Size TextureT<tt>::getMipMapSize<tt, void>(uint) const;



#define INSTANTIATE_TEXTURE_MULTISAMPLE_FUNCTIONS(tt) \
  template TextureT<tt>::TextureT<tt, void>(          \
    const TextureT<tt>::Size&, TextureFormat, uint, bool);



#define INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, pf)           \
  template TextureT<tt>::TextureT<pf, tt, void>(                               \
    const TextureT<tt>::Image<pf>&, TextureFormat, uint);                      \
  template TextureT<tt>::Image<pf> TextureT<tt>::getImage<pf, tt, void>()      \
    const;                                                                     \
  template TextureT<tt>::Image<pf> TextureT<tt>::getSubImage<pf, tt, void>(    \
    const TextureT<tt>::Coordinates&, const TextureT<tt>::Size&) const;        \
  template void TextureT<tt>::setImage<pf, tt, void>(                          \
    const TextureT<tt>::Image<pf>&);                                           \
  template void TextureT<tt>::setSubImage<pf, tt, void>(                       \
    const TextureT<tt>::Coordinates&, const TextureT<tt>::Image<pf>&);         \
  template void TextureT<tt>::clear<pf, tt, void>(const PixelT<pf>&);          \
  template TextureT<tt>::Image<pf> TextureT<tt>::getMipMapImage<pf, tt, void>( \
    uint) const;



#define INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS(tt)                              \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, PixelFormat::R)   \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, PixelFormat::RG)  \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, PixelFormat::RGB) \
  INSTANTIATE_TEXTURE_IMAGE_FUNCTIONS_FOR_PIXEL_FORMAT(tt, PixelFormat::RGBA)



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
