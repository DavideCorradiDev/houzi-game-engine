// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_HPP
#define HOU_GFX_TEXTURE_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/mth/MatrixFwd.hpp"

#include "hou/gfx/TextureFilter.hpp"
#include "hou/gfx/TextureFormat.hpp"
#include "hou/gfx/TextureFwd.hpp"
#include "hou/gfx/TextureWrapMode.hpp"

#include "hou/gl/GlTextureHandle.hpp"
#include "hou/gl/GlFunctions.hpp"

#include "hou/sys/Image.hpp"

#include <vector>



namespace hou
{

class TextureChannelMapping;

/** Represents a Texture, that is an image residing in the graphical memory.
 *
 * This class is a parent class from which different concrete Texture types are
 * derived.
 */
class HOU_GFX_API Texture : public non_copyable
{
public:
  /** Binds the texture to the given texture unit.
   *
   * \param texture the texture to be bound.
   *
   * \param textureUnit the texture unit. Must be lower than the number of
   * available texture units.
   */
  static void bind(const Texture& texture, uint textureUnit);

  /** Unbinds the current texture from the given texture unit.
   *
   * \param textureUnit the texture unit. Must be lower than the number of
   * available texture units.
   */
  static void unbind(uint textureUnit);

  /** Retrieves the number of available texture units.
   *
   * \return the number of available texture units.
   */
  static uint getTextureUnitCount();

public:
  /** Creates a texture of the given parameters.
   *
   * \param type the type of the texture.
   *
   * \param mipMapLevelCount the number of mip map levels in the texture.
   *
   * \param sampleCount the number of samples in the texture.
   *
   * \param fixedSampleLocations whether the location of the samples is fixed.
   */
  Texture(TextureType type, uint mipMapLevelCount, uint sampleCount,
    bool fixedSampleLocations);

  /** Move constructor.
   *
   * \param other the other texture.
   */
  Texture(Texture&& other);

  /** Destructor.
   */
  virtual ~Texture() = 0;

  /** Retrieves a reference to the OpenGL texture handle.
   *
   * \return a reference to the OpenGL texture handle.
   */
  const gl::TextureHandle& getHandle() const;

  /** Checks if this Texture is currently bound to the given texture unit.
   *
   * \param textureUnit the texture unit. Must be lower than the number of
   * available texture units.
   *
   * \return the result of the check.
   */
  bool isBound(uint textureUnit) const;

  /** Retrieves the format of this texture.
   *
   * \return the format of this texture.
   */
  TextureFormat getFormat() const;

  /** Retrieves the number of mip map levels of this texture.
   *
   * \return the number of mip map levels of this texture.
   */
  uint getMipMapLevelCount() const;

  /** Retrieves the number of samples of this texture.
   *
   * \return the number of samples of this texture.
   */
  uint getSampleCount() const;

  /** Retrieves whether the samples of this texture have fixed positions.
   *
   * \return whether the samples of this texture have fixed positions.
   */
  bool hasFixedSampleLocations() const;

  /** Retrieves the width of the texture.
   *
   * \return the width of the texture.
   */
  uint getWidth() const;

  /** Retrieves the height of the texture.
   *
   * \return the height of the texture.
   */
  uint getHeight() const;

  /** Retrieves the depth of the texture.
   *
   * \return the depth of the texture.
   */
  uint getDepth() const;

  /** Retrieves a vector containing the width of the texture.
   *
   * \return a vector containing the width of the texture.
   */
  Vec1u getSize1() const;

  /** Retrieves a vector containing the width and height of the texture.
   *
   * \return a vector containing the width and height of the texture.
   */
  Vec2u getSize2() const;

  /** Retrieves a vector containing the width, height and depth of the texture.
   *
   * \return a vector containing the width, height and depth of the texture.
   */
  Vec3u getSize3() const;

  /** Retrieves the channel mapping of the texture.
   *
   * \return the channel mapping.
   */
  TextureChannelMapping getChannelMapping() const;

  /** Sets the channel mapping of the texture.
   *
   * \param mapping the channel mapping.
   */
  void setChannelMapping(const TextureChannelMapping& mapping);

  /** Retrieves the type of the texture.
   *
   * \return the type of the texture.
   */
  virtual TextureType getType() const = 0;

  /** Retrieves the number of dimensions of the texture (one-, two-, or
   * three-dimensional).
   *
   * \return the number of dimension of the texture.
   */
  virtual size_t getDimensionCount() const = 0;

  /** Checks whether the texture may have multiple mip map levels.
   *
   * \return the result of the check.
   */
  virtual bool isMipMapped() const = 0;

  /** Checks whether the texture may have multiple samples per pixel.
   *
   * \return the result of the check.
   */
  virtual bool isMultisampled() const = 0;

protected:
  gl::TextureHandle mGlTextureHandle;
  uint mMipMapLevelCount;
  uint mSampleCount;
  bool mFixedSampleLocations;
};

/** Represents a concrete texture type.
 */
template <TextureType type>
class HOU_GFX_API TextureT : public Texture
{
public:
  /** Type representing the size of the texture. */
  using Size = Vec<uint, getTextureTypeDimensionCount(type)>;

  /** Type representing texture coordinates. */
  using Coordinates = Size;

  /** Type representing the texture wrap mode for each of its dimensions. */
  using WrapMode
    = std::array<TextureWrapMode, getTextureTypeDimensionCount(type)>;

  /** Type representing an Image with dimensionality matching that of the
   * texture.
   *
   * \tparam ftm the format of the texture.
   */
  template <PixelFormat fmt>
  using Image = Image<getTextureTypeDimensionCount(type), fmt>;

public:
  /** Retrieves the maximum allowed size for the texture.
   *
   * \return a vector containing the maximum size on each dimension.
   */
  static Size getMaxSize();

  /** Retrieves the maximum allowed number of mip map levels for a given texture
   * size.
   *
   * \return the maximum number of allowed mip map levels.
   */
  static uint getMaxMipMapLevelCount(const Size& size);

  /** Retrieves the maximum amount of samples per pixel.
   *
   * \return the maximum amount of samples per pixel.
   */
  static uint getMaxSampleCount();

public:
  /** Creates a Texture with the given size, format, and number of mip map
   * levels.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param size the size of the texture. Each of its element must be greater
   * than zero and lower or equal than the corresponding maximum texture size
   * element.
   *
   * \param format the format of the texture.
   *
   * \param mipMapLevelCount the number of mip map levels in the texture. It
   * must be greater then zero and lower or equal than the maximum number of
   * allowed mip map levels.
   */
  template <TextureType t = type,
    typename Enable = std::enable_if_t<isTextureTypeMipMapped(t)>>
  HOU_GFX_API explicit TextureT(const Size& size,
    TextureFormat format = TextureFormat::RGBA, uint mipMapLevelCount = 1u);

  /** Creates a Texture with the given image, format, and number of mip map
   * levels.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param image an image representing the texture contents. The size of the
   * image must be a valid texture size.
   *
   * \param format the format of the texture.
   *
   * \param mipMapLevelCount the number of mip map levels in the texture. It
   * must be greater then zero and lower or equal than the maximum number of
   * allowed mip map levels.
   */
  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<isTextureTypeMipMapped(t)>>
  HOU_GFX_API explicit TextureT(const Image<fmt>& image,
    TextureFormat format = TextureFormat::RGBA, uint mipMapLevelCount = 1u);

  /** Creates a Texture with the given size, format, and sample specification.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param size the size of the texture. Each of its element must be greater
   * than zero and lower or equal than the corresponding maximum texture size
   * element.
   *
   * \param format the format of the texture.
   *
   * \param sampleCount the number of samples per pixel in the texture. It must
   * be greater than zero and lower or equal than the maximum number of allowed
   * samples per pixel.
   *
   * \param fixedSampleLocations a bool specifying if the location of the
   * samples should be fixed.
   */
  template <TextureType t = type,
    typename Enable = std::enable_if_t<isTextureTypeMultisampled(t)>>
  HOU_GFX_API explicit TextureT(const Size& size,
    TextureFormat format = TextureFormat::RGBA, uint sampleCount = 1u,
    bool fixedSampleLocations = true);

  /** Move constructor.
   *
   * \param other the other texture.
   */
  TextureT(TextureT&& other);
  virtual ~TextureT();

  /** Retrieves the size of the texture.
   *
   * \return the size of the texture.
   */
  Size getSize() const;

  /** Retrieves the texture filter.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \return the texture filter.
   */
  template <TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API TextureFilter getFilter() const;


  /** Sets the texture filter.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param filter the texture filter.
   */
  template <TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API void setFilter(TextureFilter filter);

  /** Retrieves the texture wrap mode.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \return the texture wrap mode.
   */
  template <TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API WrapMode getWrapMode() const;


  /** Sets the texture wrap mode.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param wrapMode the texture wrap mode.
   */
  template <TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API void setWrapMode(const WrapMode& wrapMode);

  /** Retrieve the contents of the Texture as an Image object.
   *
   * \tparam fmt the PixelFormat of the output Image.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \return an Image with the content of the texture.
   */
  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API Image<fmt> getImage() const;

  /** Retrieves the contents of a sub-region of the Texture as an Image object.
   *
   * Throws if the subregion exceeds the boundaries of th image.
   *
   * \tparam fmt the PixelFormat of the output Image.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param offset a pixel offset represeinting the top-left corner of the
   * sub-region
   *
   * \param size the size of the sub-region
   *
   * \return an Image with the content of the texture in the specified
   * sub-region.
   */
  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API Image<fmt> getSubImage(
    const Coordinates& offset, const Size& size) const;

  /** Sets the content of the Texture.
   *
   * \tparam fmt the PixelFormat of the input Image.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param image an image representing the content of the Texture.
   */
  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API void setImage(const Image<fmt>& image);


  /** Sets the content of a sub-region of the Texture.
   *
   * Throws if the subregion exceeds the boundaries of the image.
   *
   * \tparam fmt the PixelFormat of the input Image.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param offset an offset representing the top-left cornern of the
   * sub-region.
   *
   * \param image an image representing the content of the Texture.
   */
  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API void setSubImage(
    const Coordinates& offset, const Image<fmt>& image);

  /** Clear the texture with the specified pixel value.
   *
   * \tparam fmt the PixelFormat of the input pixel value.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param pixel the pixel value.
   */
  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<!isTextureTypeMultisampled(t)>>
  HOU_GFX_API void clear(const PixelT<fmt>& pixel);

  /** Retrieves the size of the specified mip map level.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param mipMapLevel the mipMapLevevel. It must be lower than the number of
   * mip map levels of the Texture.
   *
   * \return the size of the specified mip map level.
   */
  template <TextureType t = type,
    typename Enable = std::enable_if_t<isTextureTypeMipMapped(t)>>
  HOU_GFX_API Size getMipMapSize(uint mipMapLevel) const;

  /** Retrieves the content of the specified mip map level of the Texture as an
   * Image object.
   *
   * \tparam fmt the PixelFormat of the input pixel value.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param mipMapLevel the mipMapLevevel. It must be lower than the number of
   * mip map levels of the Texture.
   *
   * \return an Image containing the data of the specified mip map level.
   */
  template <PixelFormat fmt, TextureType t = type,
    typename Enable = std::enable_if_t<isTextureTypeMipMapped(t)>>
  HOU_GFX_API Image<fmt> getMipMapImage(uint mipMapLevel) const;

  // Texture overrides.
  TextureType getType() const override;
  size_t getDimensionCount() const override;
  bool isMipMapped() const override;
  bool isMultisampled() const override;

private:
  HOU_GFX_API void generateMipMap();
};

}  // namespace hou

#endif
