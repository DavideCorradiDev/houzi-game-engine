// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_HPP
#define HOU_GFX_TEXTURE_HPP

#include "hou/cor/NonCopyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/mth/MatrixFwd.hpp"

#include "hou/gfx/TextureFilter.hpp"
#include "hou/gfx/TextureFormat.hpp"
#include "hou/gfx/TextureFwd.hpp"
#include "hou/gfx/TextureWrapMode.hpp"

#include "hou/gl/GlTextureHandle.hpp"
#include "hou/gl/GlUtils.hpp"

#include "hou/sys/Image.hpp"

#include <vector>



namespace hou
{

class TextureChannelMapping;



class HOU_GFX_API Texture : public NonCopyable
{
public:
  static void bind(const Texture& texture, uint textureUnit);
  static void unbind(uint textureUnit);

  static uint getTextureUnitCount();

public:
  Texture(TextureType type, uint mipMapLevelCount, uint sampleCount,
    bool fixedSampleLocations);
  Texture(Texture&& other);
  virtual ~Texture() = 0;

  const gl::TextureHandle& getHandle() const;
  bool isBound(uint textureUnit) const;
  TextureFormat getFormat() const;
  uint getMipMapLevelCount() const;
  uint getSampleCount() const;
  bool hasFixedSampleLocations() const;

  uint getWidth() const;
  uint getHeight() const;
  uint getDepth() const;
  Vec1u getSize1() const;
  Vec2u getSize2() const;
  Vec3u getSize3() const;

  TextureChannelMapping getChannelMapping() const;
  void setChannelMapping(const TextureChannelMapping& mapping);

  virtual TextureType getType() const = 0;
  virtual size_t getDimensionCount() const = 0;
  virtual bool isMipMapped() const = 0;
  virtual bool isMultisampled() const = 0;

protected:
  gl::TextureHandle mGlTextureHandle;
  uint mMipMapLevelCount;
  uint mSampleCount;
  bool mFixedSampleLocations;
};

template <TextureType type>
class HOU_GFX_API TextureTemplate : public Texture
{
public:
  using Size = Vec<uint, getTextureTypeDimensionCount(type)>;
  using Coordinates = Size;
  using WrapMode
    = std::array<TextureWrapMode, getTextureTypeDimensionCount(type)>;
  template <PixelFormat fmt>
  using Image = Image<getTextureTypeDimensionCount(type), fmt>;

public:
  static Size getMaxSize();
  static uint getMaxMipMapLevelCount(const Size& size);
  static uint getMaxSampleCount();

public:
  template <TextureType t = type,
    typename Enable = std::enable_if_t<isTextureTypeMipMapped(t)>>
  HOU_GFX_API explicit TextureTemplate(const Size& size,
    TextureFormat format = TextureFormat::RGBA, uint mipMapLevelCount = 1u);
  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<isTextureTypeMipMapped(t)>>
  HOU_GFX_API explicit TextureTemplate(const Image<fmt>& image,
    TextureFormat format = TextureFormat::RGBA, uint mipMapLevelCount = 1u);
  template <TextureType t = type,
    typename Enable = std::enable_if_t<isTextureTypeMultisampled(t)>>
  HOU_GFX_API explicit TextureTemplate(const Size& size,
    TextureFormat format = TextureFormat::RGBA, uint sampleCount = 1u,
    bool fixedSampleLocations = true);
  TextureTemplate(TextureTemplate&& other);
  virtual ~TextureTemplate();

  Size getSize() const;

  template <TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API TextureFilter getFilter() const;

  template <TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API void setFilter(TextureFilter filter);

  template <TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API WrapMode getWrapMode() const;

  template <TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API void setWrapMode(const WrapMode& wrapMode);

  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API Image<fmt> getImage() const;

  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API Image<fmt> getSubImage(
    const Coordinates& offset, const Size& size) const;

  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API void setImage(const Image<fmt>& image);

  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API void setSubImage(
    const Coordinates& offset, const Image<fmt>& image);

  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API void clear(const PixelT<fmt>& pixel);

  template <TextureType t = type,
    typename Enable = std::enable_if_t<isTextureTypeMipMapped(t)>>
  HOU_GFX_API Size getMipMapSize(uint mipMapLevel) const;

  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<isTextureTypeMipMapped(t)>>
  HOU_GFX_API Image<fmt> getMipMapImage(uint mipMapLevel) const;

  TextureType getType() const override;
  size_t getDimensionCount() const override;
  bool isMipMapped() const override;
  bool isMultisampled() const override;

private:
  HOU_GFX_API void generateMipMap();
};

}  // namespace hou

#endif
