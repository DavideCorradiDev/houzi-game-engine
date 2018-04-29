// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_HPP
#define HOU_GFX_TEXTURE_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/gfx_export.hpp"

#include "hou/mth/matrix_fwd.hpp"

#include "hou/gfx/texture_filter.hpp"
#include "hou/gfx/texture_format.hpp"
#include "hou/gfx/texture_fwd.hpp"
#include "hou/gfx/texture_wrap_mode.hpp"

#include "hou/gl/gl_texture_handle.hpp"
#include "hou/gl/gl_functions.hpp"

#include "hou/sys/image.hpp"

#include <vector>



namespace hou
{

class texture_channel_mapping;

/** Represents a texture, that is an ph_image residing in the graphical memory.
 *
 * This class is a parent class from which different concrete texture types are
 * derived.
 */
class HOU_GFX_API texture : public non_copyable
{
public:
  /** Binds the ph_texture to the given ph_texture unit.
   *
   * \param ph_texture the ph_texture to be bound.
   *
   * \param textureUnit the ph_texture unit. Must be lower than the number of
   * available ph_texture units.
   */
  static void bind(const texture& ph_texture, uint textureUnit);

  /** Unbinds the current ph_texture from the given ph_texture unit.
   *
   * \param textureUnit the ph_texture unit. Must be lower than the number of
   * available ph_texture units.
   */
  static void unbind(uint textureUnit);

  /** Retrieves the number of available ph_texture units.
   *
   * \return the number of available ph_texture units.
   */
  static uint get_texture_unit_count();

public:
  /** Creates a ph_texture of the given parameters.
   *
   * \param type the type of the ph_texture.
   *
   * \param mipMapLevelCount the number of mip map levels in the ph_texture.
   *
   * \param sampleCount the number of samples in the ph_texture.
   *
   * \param fixedSampleLocations whether the location of the samples is fixed.
   */
  texture(texture_type type, uint mipMapLevelCount, uint sampleCount,
    bool fixedSampleLocations);

  /** Move constructor.
   *
   * \param other the other ph_texture.
   */
  texture(texture&& other);

  /** Destructor.
   */
  virtual ~texture() = 0;

  /** Retrieves a reference to the OpenGL ph_texture handle.
   *
   * \return a reference to the OpenGL ph_texture handle.
   */
  const gl::texture_handle& get_handle() const;

  /** Checks if this texture is currently bound to the given ph_texture unit.
   *
   * \param textureUnit the ph_texture unit. Must be lower than the number of
   * available ph_texture units.
   *
   * \return the result of the check.
   */
  bool is_bound(uint textureUnit) const;

  /** Retrieves the format of this ph_texture.
   *
   * \return the format of this ph_texture.
   */
  texture_format get_format() const;

  /** Retrieves the number of mip map levels of this ph_texture.
   *
   * \return the number of mip map levels of this ph_texture.
   */
  uint get_mipmap_level_count() const;

  /** Retrieves the number of samples of this ph_texture.
   *
   * \return the number of samples of this ph_texture.
   */
  uint get_sample_count() const;

  /** Retrieves whether the samples of this ph_texture have fixed positions.
   *
   * \return whether the samples of this ph_texture have fixed positions.
   */
  bool has_fixed_sample_locations() const;

  /** Retrieves the width of the ph_texture.
   *
   * \return the width of the ph_texture.
   */
  uint get_width() const;

  /** Retrieves the height of the ph_texture.
   *
   * \return the height of the ph_texture.
   */
  uint get_height() const;

  /** Retrieves the depth of the ph_texture.
   *
   * \return the depth of the ph_texture.
   */
  uint get_depth() const;

  /** Retrieves a vector containing the width of the ph_texture.
   *
   * \return a vector containing the width of the ph_texture.
   */
  vec1u get_size1() const;

  /** Retrieves a vector containing the width and height of the ph_texture.
   *
   * \return a vector containing the width and height of the ph_texture.
   */
  vec2u get_size2() const;

  /** Retrieves a vector containing the width, height and depth of the ph_texture.
   *
   * \return a vector containing the width, height and depth of the ph_texture.
   */
  vec3u get_size3() const;

  /** Retrieves the channel mapping of the ph_texture.
   *
   * \return the channel mapping.
   */
  texture_channel_mapping get_channel_mapping() const;

  /** Sets the channel mapping of the ph_texture.
   *
   * \param mapping the channel mapping.
   */
  void setChannelMapping(const texture_channel_mapping& mapping);

  /** Retrieves the type of the ph_texture.
   *
   * \return the type of the ph_texture.
   */
  virtual texture_type get_type() const = 0;

  /** Retrieves the number of dimensions of the ph_texture (one-, two-, or
   * three-dimensional).
   *
   * \return the number of dimension of the ph_texture.
   */
  virtual size_t get_dimension_count() const = 0;

  /** Checks whether the ph_texture may have multiple mip map levels.
   *
   * \return the result of the check.
   */
  virtual bool is_mipmapped() const = 0;

  /** Checks whether the ph_texture may have multiple samples per ph_pixel.
   *
   * \return the result of the check.
   */
  virtual bool is_multisampled() const = 0;

protected:
  gl::texture_handle mGlTextureHandle;
  uint m_mipmap_level_count;
  uint m_sample_count;
  bool m_fixed_sample_locations;
};

/** Represents a concrete ph_texture type.
 */
template <texture_type type>
class HOU_GFX_API texture_t : public texture
{
public:
  /** Type representing the size of the ph_texture. */
  using size_type = vec<uint, get_texture_type_dimension_count(type)>;

  /** Type representing ph_texture coordinates. */
  using offset_type = size_type;

  /** Type representing the ph_texture wrap mode for each of its dimensions. */
  using wrap_mode
    = std::array<texture_wrap_mode, get_texture_type_dimension_count(type)>;

  /** Type representing an image with dimensionality matching that of the
   * ph_texture.
   *
   * \tparam ftm the format of the ph_texture.
   */
  template <pixel_format fmt>
  using image = image<get_texture_type_dimension_count(type), fmt>;

public:
  /** Retrieves the maximum allowed size for the ph_texture.
   *
   * \return a vector containing the maximum size on each dimension.
   */
  static size_type get_max_size();

  /** Retrieves the maximum allowed number of mip map levels for a given ph_texture
   * size.
   *
   * \return the maximum number of allowed mip map levels.
   */
  static uint get_max_mipmap_level_count(const size_type& size);

  /** Retrieves the maximum amount of samples per ph_pixel.
   *
   * \return the maximum amount of samples per ph_pixel.
   */
  static uint get_max_sample_count();

public:
  /** Creates a texture with the given size, format, and number of mip map
   * levels.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param size the size of the ph_texture. Each of its element must be greater
   * than zero and lower or equal than the corresponding maximum ph_texture size
   * element.
   *
   * \param format the format of the ph_texture.
   *
   * \param mipMapLevelCount the number of mip map levels in the ph_texture. It
   * must be greater then zero and lower or equal than the maximum number of
   * allowed mip map levels.
   */
  template <texture_type t = type,
    typename Enable = std::enable_if_t<is_texture_type_mipmapped(t)>>
  HOU_GFX_API explicit texture_t(const size_type& size,
    texture_format format = texture_format::rgba, uint mipMapLevelCount = 1u);

  /** Creates a texture with the given ph_image, format, and number of mip map
   * levels.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param ph_image an ph_image representing the ph_texture contents. The size of the
   * ph_image must be a valid ph_texture size.
   *
   * \param format the format of the ph_texture.
   *
   * \param mipMapLevelCount the number of mip map levels in the ph_texture. It
   * must be greater then zero and lower or equal than the maximum number of
   * allowed mip map levels.
   */
  template <pixel_format fmt, texture_type t = type,
    typename Enable = std::enable_if_t<is_texture_type_mipmapped(t)>>
  HOU_GFX_API explicit texture_t(const image<fmt>& ph_image,
    texture_format format = texture_format::rgba, uint mipMapLevelCount = 1u);

  /** Creates a texture with the given size, format, and sample specification.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param size the size of the ph_texture. Each of its element must be greater
   * than zero and lower or equal than the corresponding maximum ph_texture size
   * element.
   *
   * \param format the format of the ph_texture.
   *
   * \param sampleCount the number of samples per ph_pixel in the ph_texture. It must
   * be greater than zero and lower or equal than the maximum number of allowed
   * samples per ph_pixel.
   *
   * \param fixedSampleLocations a bool specifying if the location of the
   * samples should be fixed.
   */
  template <texture_type t = type,
    typename Enable = std::enable_if_t<is_texture_type_multisampled(t)>>
  HOU_GFX_API explicit texture_t(const size_type& size,
    texture_format format = texture_format::rgba, uint sampleCount = 1u,
    bool fixedSampleLocations = true);

  /** Move constructor.
   *
   * \param other the other ph_texture.
   */
  texture_t(texture_t&& other);
  virtual ~texture_t();

  /** Retrieves the size of the ph_texture.
   *
   * \return the size of the ph_texture.
   */
  size_type get_size() const;

  /** Retrieves the ph_texture filter.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \return the ph_texture filter.
   */
  template <texture_type t = type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(t)>>
  HOU_GFX_API texture_filter get_filter() const;


  /** Sets the ph_texture filter.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param filter the ph_texture filter.
   */
  template <texture_type t = type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(t)>>
  HOU_GFX_API void set_filter(texture_filter filter);

  /** Retrieves the ph_texture wrap mode.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \return the ph_texture wrap mode.
   */
  template <texture_type t = type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(t)>>
  HOU_GFX_API wrap_mode get_wrap_mode() const;


  /** Sets the ph_texture wrap mode.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param wrapMode the ph_texture wrap mode.
   */
  template <texture_type t = type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(t)>>
  HOU_GFX_API void set_wrap_mode(const wrap_mode& wrapMode);

  /** Retrieve the contents of the texture as an image object.
   *
   * \tparam fmt the pixel_format of the output image.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \return an image with the content of the ph_texture.
   */
  template <pixel_format fmt, texture_type t = type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(t)>>
  HOU_GFX_API image<fmt> get_image() const;

  /** Retrieves the contents of a sub-region of the texture as an image object.
   *
   * Throws if the subregion exceeds the boundaries of th ph_image.
   *
   * \tparam fmt the pixel_format of the output image.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param offset a ph_pixel offset represeinting the top-left corner of the
   * sub-region
   *
   * \param size the size of the sub-region
   *
   * \return an image with the content of the ph_texture in the specified
   * sub-region.
   */
  template <pixel_format fmt, texture_type t = type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(t)>>
  HOU_GFX_API image<fmt> get_sub_image(
    const offset_type& offset, const size_type& size) const;

  /** Sets the content of the texture.
   *
   * \tparam fmt the pixel_format of the input image.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param ph_image an ph_image representing the content of the texture.
   */
  template <pixel_format fmt, texture_type t = type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(t)>>
  HOU_GFX_API void set_image(const image<fmt>& ph_image);


  /** Sets the content of a sub-region of the texture.
   *
   * Throws if the subregion exceeds the boundaries of the ph_image.
   *
   * \tparam fmt the pixel_format of the input image.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param offset an offset representing the top-left cornern of the
   * sub-region.
   *
   * \param ph_image an ph_image representing the content of the texture.
   */
  template <pixel_format fmt, texture_type t = type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(t)>>
  HOU_GFX_API void set_sub_image(
    const offset_type& offset, const image<fmt>& ph_image);

  /** Clear the ph_texture with the specified ph_pixel value.
   *
   * \tparam fmt the pixel_format of the input ph_pixel value.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param ph_pixel the ph_pixel value.
   */
  template <pixel_format fmt, texture_type t = type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(t)>>
  HOU_GFX_API void clear(const pixel_t<fmt>& ph_pixel);

  /** Retrieves the size of the specified mip map level.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param mipMapLevel the mipMapLevevel. It must be lower than the number of
   * mip map levels of the texture.
   *
   * \return the size of the specified mip map level.
   */
  template <texture_type t = type,
    typename Enable = std::enable_if_t<is_texture_type_mipmapped(t)>>
  HOU_GFX_API size_type get_mipmap_size(uint mipMapLevel) const;

  /** Retrieves the content of the specified mip map level of the texture as an
   * image object.
   *
   * \tparam fmt the pixel_format of the input ph_pixel value.
   *
   * \tparam t dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param mipMapLevel the mipMapLevevel. It must be lower than the number of
   * mip map levels of the texture.
   *
   * \return an image containing the data of the specified mip map level.
   */
  template <pixel_format fmt, texture_type t = type,
    typename Enable = std::enable_if_t<is_texture_type_mipmapped(t)>>
  HOU_GFX_API image<fmt> get_mipmap_image(uint mipMapLevel) const;

  // texture overrides.
  texture_type get_type() const override;
  size_t get_dimension_count() const override;
  bool is_mipmapped() const override;
  bool is_multisampled() const override;

private:
  HOU_GFX_API void generate_mip_map();
};

}  // namespace hou

#endif
