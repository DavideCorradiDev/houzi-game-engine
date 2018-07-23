// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_HPP
#define HOU_GFX_TEXTURE_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gfx/gl_type.hpp"
#include "hou/gfx/texture_filter.hpp"
#include "hou/gfx/texture_format.hpp"
#include "hou/gfx/texture_fwd.hpp"
#include "hou/gfx/texture_wrap_mode.hpp"

#include "hou/gfx/gfx_config.hpp"

#include "hou/cor/checked_variable.hpp"
#include "hou/cor/narrow_cast.hpp"

#include "hou/mth/matrix_fwd.hpp"

#include "hou/gl/gl_functions.hpp"
#include "hou/gl/gl_texture_handle.hpp"

#include "hou/sys/image.hpp"

#include <vector>



namespace hou
{

class texture_channel_mapping;

/** Represents a texture, that is an image residing in the graphical memory.
 *
 * This class is a parent class from which different concrete texture types are
 * derived.
 */
class HOU_GFX_API texture : public non_copyable
{
public:
  /** Binds the texture to the given texture unit.
   *
   * \param tex the texture to be bound.
   *
   * \param tu the texture unit. Must be lower than the number of
   * available texture units.
   */
  static void bind(const texture& tex, uint tu);

  /** Unbinds the current texture from the given texture unit.
   *
   * \param tu the texture unit. Must be lower than the number of
   * available texture units.
   */
  static void unbind(uint tu);

  /** Retrieves the number of available texture units.
   *
   * \return the number of available texture units.
   */
  static uint get_texture_unit_count();

public:
  /** Creates a texture of the given parameters.
   *
   * \param type the type of the texture.
   *
   * \param format the texture format.
   *
   * \param width the texture width.
   *
   * \param height the texture height.
   *
   * \param depth the texture depth.
   *
   * \param mipmap_level_count the number of mip map levels in the texture.
   *
   * \param sample_count the number of samples in the texture.
   *
   * \param fixed_sample_locations whether the location of the samples is fixed.
   */
  texture(texture_type type, texture_format format, positive<uint> width,
    positive<uint> height, positive<uint> depth,
    positive<uint> mipmap_level_count, positive<uint> sample_count,
    bool fixed_sample_locations);

  /** Move constructor.
   *
   * \param other the other texture.
   */
  texture(texture&& other) noexcept = default;

  /** Destructor.
   */
  virtual ~texture() = 0;

  /** Retrieves a reference to the OpenGL texture handle.
   *
   * \return a reference to the OpenGL texture handle.
   */
  const gl::texture_handle& get_handle() const noexcept;

  /** Checks if this texture is currently bound to the given texture unit.
   *
   * \param tu the texture unit. Must be lower than the number of
   * available texture units.
   *
   * \return the result of the check.
   */
  bool is_bound(uint tu) const;

  /** Retrieves the format of this texture.
   *
   * \return the format of this texture.
   */
  texture_format get_format() const;

  /** Retrieves the number of mip map levels of this texture.
   *
   * \return the number of mip map levels of this texture.
   */
  positive<uint> get_mipmap_level_count() const;

  /** Retrieves the number of samples of this texture.
   *
   * \return the number of samples of this texture.
   */
  positive<uint> get_sample_count() const;

  /** Retrieves whether the samples of this texture have fixed positions.
   *
   * \return whether the samples of this texture have fixed positions.
   */
  bool has_fixed_sample_locations() const;

  /** Retrieves the width of the texture.
   *
   * \param level the mipmap level.
   *
   * \return the width of the texture.
   */
  uint get_width(uint level = 0u) const;

  /** Retrieves the height of the texture.
   *
   * \param level the mipmap level.
   *
   * \return the height of the texture.
   */
  uint get_height(uint level = 0u) const;

  /** Retrieves the depth of the texture.
   *
   * \param level the mipmap level.
   *
   * \return the depth of the texture.
   */
  uint get_depth(uint level = 0u) const;

  /** Retrieves a vector containing the width of the texture.
   *
   * \param level the mipmap level.
   *
   * \return a vector containing the width of the texture.
   */
  vec1u get_size1(uint level = 0u) const;

  /** Retrieves a vector containing the width and height of the texture.
   *
   * \param level the mipmap level.
   *
   * \return a vector containing the width and height of the texture.
   */
  vec2u get_size2(uint level = 0u) const;

  /** Retrieves a vector containing the width, height and depth of the texture.
   *
   * \param level the mipmap level.
   *
   * \return a vector containing the width, height and depth of the texture.
   */
  vec3u get_size3(uint level = 0u) const;

  /** Retrieves the channel mapping of the texture.
   *
   * \return the channel mapping.
   */
  texture_channel_mapping get_channel_mapping() const;

  /** Sets the channel mapping of the texture.
   *
   * \param mapping the channel mapping.
   */
  void setChannelMapping(const texture_channel_mapping& mapping);

  /** Retrieves the type of the texture.
   *
   * \return the type of the texture.
   */
  virtual texture_type get_type() const = 0;

  /** Retrieves the number of dimensions of the texture (one-, two-, or
   * three-dimensional).
   *
   * \return the number of dimension of the texture.
   */
  virtual size_t get_dimension_count() const = 0;

  /** Checks whether the texture may have multiple mip map levels.
   *
   * \return the result of the check.
   */
  virtual bool is_mipmapped() const = 0;

  /** Checks whether the texture may have multiple samples per pixel.
   *
   * \return the result of the check.
   */
  virtual bool is_multisampled() const = 0;

private:
  gl::texture_handle m_gl_texture_handle;
  texture_format m_format;
  positive<uint> m_width;
  positive<uint> m_height;
  positive<uint> m_depth;
  positive<uint> m_mipmap_level_count;
  positive<uint> m_sample_count;
  bool m_fixed_sample_locations;
};

/** Represents a concrete texture type.
 *
 * \tparam Type the texture type.
 */
template <texture_type Type>
class texture_t : public texture
{
public:
  /** Type representing the size of the texture. */
  using size_type = vec<uint, get_texture_type_dimension_count(Type)>;

  /** Type representing texture coordinates. */
  using offset_type = size_type;

  /** Type representing the texture wrap mode for each of its dimensions. */
  using wrap_mode
    = std::array<texture_wrap_mode, get_texture_type_dimension_count(Type)>;

  /** Type representing an image with dimensionality matching that of the
   * texture.
   *
   * \tparam ftm the format of the texture.
   */
  template <pixel_format PF>
  using image = image<get_texture_type_dimension_count(Type), PF>;

public:
  /** The texture type. */
  static constexpr texture_type type = Type;

  /** The number of dimensions of the texture. */
  static constexpr size_t dimension_count
    = get_texture_type_dimension_count(Type);

public:
  /** Retrieves the maximum allowed size for the texture.
   *
   * \return a vector containing the maximum size on each dimension.
   */
  static size_type get_max_size();

  /** Retrieves the maximum allowed number of mip map levels for a given texture
   * size.
   *
   * \return the maximum number of allowed mip map levels.
   */
  static positive<uint> get_max_mipmap_level_count(const size_type& size);

  /** Retrieves the maximum amount of samples per pixel.
   *
   * \return the maximum amount of samples per pixel.
   */
  static positive<uint> get_max_sample_count();

public:
  /** Creates a texture with the given size, format, and number of mip map
   * levels.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param size the size of the texture. Each of its element must be greater
   * than zero and lower or equal than the corresponding maximum texture size
   * element.
   *
   * \param format the format of the texture.
   *
   * \param mipmap_level_count the number of mip map levels in the texture. It
   * must be greater then zero and lower or equal than the maximum number of
   * allowed mip map levels.
   */
  template <texture_type Type2 = Type,
    typename Enable = std::enable_if_t<is_texture_type_mipmapped(Type2)>>
  explicit texture_t(const size_type& size,
    texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);

  /** Creates a texture with the given image, format, and number of mip map
   * levels.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param im an image representing the texture contents. The size of the
   * image must be a valid texture size.
   *
   * \param format the format of the texture.
   *
   * \param mipmap_level_count the number of mip map levels in the texture. It
   * must be greater then zero and lower or equal than the maximum number of
   * allowed mip map levels.
   */
  template <pixel_format PF, texture_type Type2 = Type,
    typename Enable = std::enable_if_t<is_texture_type_mipmapped(Type2)>>
  explicit texture_t(const image<PF>& im,
    texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);

  /** Creates a texture with the given size, format, and sample specification.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param size the size of the texture. Each of its element must be greater
   * than zero and lower or equal than the corresponding maximum texture size
   * element.
   *
   * \param format the format of the texture.
   *
   * \param sample_count the number of samples per pixel in the texture. It must
   * be greater than zero and lower or equal than the maximum number of allowed
   * samples per pixel.
   *
   * \param fixed_sample_locations a bool specifying if the location of the
   * samples should be fixed.
   */
  template <texture_type Type2 = Type,
    typename Enable = std::enable_if_t<is_texture_type_multisampled(Type2)>>
  explicit texture_t(const size_type& size,
    texture_format format = texture_format::rgba,
    positive<uint> sample_count = 1u, bool fixed_sample_locations = true);

  /** Retrieves the size of the texture.
   *
   * \return the size of the texture.
   */
  size_type get_size() const;

  /** Retrieves the texture filter.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \return the texture filter.
   */
  template <texture_type Type2 = Type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(Type2)>>
  texture_filter get_filter() const;

  /** Sets the texture filter.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param filter the texture filter.
   */
  template <texture_type Type2 = Type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(Type2)>>
  void set_filter(texture_filter filter);

  /** Retrieves the texture wrap mode.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \return the texture wrap mode.
   */
  template <texture_type Type2 = Type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(Type2)>>
  wrap_mode get_wrap_mode() const;

  /** Sets the texture wrap mode.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param wrap_mode the texture wrap mode.
   */
  template <texture_type Type2 = Type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(Type2)>>
  void set_wrap_mode(const wrap_mode& wrap_mode);

  /** Retrieve the contents of the texture as an image object.
   *
   * \note this function is not supported and will throw if called on a system
   * using GL ES.
   *
   * \throws hou::unsupported_error if on a platform using GL ES.
   *
   * \tparam PF the pixel_format of the output image.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \return an image with the content of the texture.
   */
  // Note: the texture_t::image alias cannot be used because otherwise MSVC
  // cannot make the connection between the declaration and the definition.
  template <pixel_format PF, texture_type Type2 = Type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(Type2)>>
  ::hou::image<texture_t<Type>::dimension_count, PF> get_image() const;

  /** Retrieves the contents of a sub-region of the texture as an image object.
   *
   * Throws if the subregion exceeds the boundaries of th image.
   *
   * \note this function is not supported and will throw if called on a system
   * using GL ES.
   *
   * \throws hou::unsupported_error if on a platform using GL ES.
   *
   * \tparam PF the pixel_format of the output image.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param offset a pixel offset represeinting the top-left corner of the
   * sub-region
   *
   * \param size the size of the sub-region
   *
   * \return an image with the content of the texture in the specified
   * sub-region.
   */
  template <pixel_format PF, texture_type Type2 = Type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(Type2)>>
  ::hou::image<texture_t<Type>::dimension_count, PF> get_sub_image(
    const offset_type& offset, const size_type& size) const;

  /** Sets the content of the texture.
   *
   * \tparam PF the pixel_format of the input image.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param im an image representing the content of the texture.
   */
  template <pixel_format PF, texture_type Type2 = Type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(Type2)>>
  void set_image(const image<PF>& im);

  /** Sets the content of a sub-region of the texture.
   *
   * Throws if the subregion exceeds the boundaries of the image.
   *
   * \tparam PF the pixel_format of the input image.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param offset an offset representing the top-left cornern of the
   * sub-region.
   *
   * \param im an image representing the content of the texture.
   */
  template <pixel_format PF, texture_type Type2 = Type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(Type2)>>
  void set_sub_image(const offset_type& offset, const image<PF>& im);

  /** Clear the texture with the specified pixel value.
   *
   * \tparam PF the pixel_format of the input pixel value.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param px the pixel value.
   */
  template <pixel_format PF, texture_type Type2 = Type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(Type2)>>
  void clear(const pixel<PF>& px);

  /** Resets all texture pixel values to 0.
   *
   * \tparam Enable enabling parameter.
   */
  template <texture_type Type2 = Type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(Type2)>>
  void reset();

  /** Retrieves the size of the specified mip map level.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param mipmap_level the mipMapLevevel. It must be lower than the number of
   * mip map levels of the texture.
   *
   * \return the size of the specified mip map level.
   */
  template <texture_type Type2 = Type,
    typename Enable = std::enable_if_t<is_texture_type_mipmapped(Type2)>>
  size_type get_mipmap_size(uint mipmap_level) const;

  /** Retrieves the content of the specified mip map level of the texture as an
   * image object.
   *
   * \tparam PF the pixel_format of the input pixel value.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param mipmap_level the mipMapLevevel. It must be lower than the number of
   * mip map levels of the texture.
   *
   * \return an image containing the data of the specified mip map level.
   */
  template <pixel_format PF, texture_type Type2 = Type,
    typename Enable = std::enable_if_t<is_texture_type_mipmapped(Type2)>>
  // Note: the texture_t::image alias cannot be used because otherwise MSVC
  // cannot make the connection between the declaration and the definition.
  ::hou::image<texture_t<Type>::dimension_count, PF> get_mipmap_image(
    uint mipmap_level) const;

  // texture overrides.
  texture_type get_type() const override;
  size_t get_dimension_count() const override;
  bool is_mipmapped() const override;
  bool is_multisampled() const override;

private:
  static bool is_texture_size_valid(const size_type& s);

  static bool is_mipmap_level_count_valid(
    positive<uint> mipmap_level_count, const size_type& s);

  static positive<uint> get_max_mipmap_level_count_for_size(const size_type& s);

  static bool element_wise_lower_or_equal(
    const size_type& lhs, const size_type& rhs);

  static size_t compute_image_buffer_size(
    const size_type& im_size, pixel_format fmt);

  static GLenum pixel_format_to_gl_pixel_format(pixel_format format);

private:
  void generate_mip_map();

  template <pixel_format PF, texture_type Type2 = Type,
    typename Enable = std::enable_if_t<!is_texture_type_multisampled(Type2)>>
  void set_sub_image_internal(const offset_type& offset, const image<PF>& im);

  template <pixel_format PF>
  ::hou::image<texture_t<Type>::dimension_count, PF> get_image_internal(
    pixel_format pf, const size_type& s,
    const std::vector<uint8_t>& buffer) const;
};

}  // namespace hou



#include "hou/gfx/texture.inl"

#endif
