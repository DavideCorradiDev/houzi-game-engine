// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/non_copyable.hpp"

#include "hou/gfx/pixel_view.hpp"
#include "hou/gfx/texture_channel_mapping.hpp"
#include "hou/gfx/texture_filter.hpp"
#include "hou/gfx/texture_format.hpp"
#include "hou/gfx/texture_type.hpp"
#include "hou/gfx/texture_wrap_mode.hpp"

#include "hou/gfx/gfx_config.hpp"

#include "hou/gl/gl_texture_handle.hpp"

#include "hou/cor/checked_variable.hpp"

#include "hou/mth/matrix_fwd.hpp"

#ifndef HOU_GFX_TEXTURE_HPP
#define HOU_GFX_TEXTURE_HPP

namespace hou
{

namespace exp
{

/**
 * Represents a texture, that is an image residing in the graphical memory.
 *
 * This class is a parent class from which different concrete texture types are
 * derived.
 */
class HOU_GFX_API texture : public non_copyable
{
public:
  /**
   * Binds the texture to the given texture unit.
   *
   * \param tex the texture to be bound.
   *
   * \param tu the texture unit. Must be lower than the number of
   * available texture units.
   */
  static void bind(const texture& tex, uint tu);

  /**
   * Unbinds the current texture from the given texture unit.
   *
   * \param tu the texture unit. Must be lower than the number of
   * available texture units.
   */
  static void unbind(uint tu);

  /**
   * Retrieves the number of available texture units.
   *
   * \return the number of available texture units.
   */
  static uint get_texture_unit_count();

public:
  /**
   * Creates a texture.
   *
   * \param type the texture type.
   *
   * \param format the texture format.
   */
  texture(texture_type type, texture_format format);

  /**
   * Move constructor.
   *
   * \param other the other texture.
   */
  texture(texture&& other) noexcept = default;

  /**
   * Destructor.
   */
  virtual ~texture() = 0;

  /**
   * Retrieves a reference to the OpenGL texture handle.
   *
   * \return a reference to the OpenGL texture handle.
   */
  const gl::texture_handle& get_handle() const noexcept;

  /**
   * Retrieves the type of this texture.
   *
   * \return the type of this texture.
   */
  texture_type get_type() const noexcept;

  /**
   * Retrieves the format of this texture.
   *
   * \return the format of this texture.
   */
  texture_format get_format() const noexcept;

  /** Retrieves the channel mapping of the texture.
   *
   * \return the channel mapping.
   */
  texture_channel_mapping get_channel_mapping() const;

  /** Sets the channel mapping of the texture.
   *
   * \param mapping the channel mapping.
   */
  void set_channel_mapping(const texture_channel_mapping& mapping);

  /**
   * Checks if this texture is currently bound to the given texture unit.
   *
   * \param tu the texture unit. Must be lower than the number of
   * available texture units.
   *
   * \return the result of the check.
   */
  bool is_bound(uint tu) const;

protected:
  texture_filter get_filter_internal() const;
  void set_filter_internal(texture_filter filter);

private:
  gl::texture_handle m_handle;
  texture_type m_type;
  texture_format m_format;
};



class HOU_GFX_API texture2_base : public texture
{
public:
  /**
   * Creates a texture with the given type, size, and format.
   *
   * \param type the type.
   *
   * \param size the size.
   *
   * \format the format.
   */
  texture2_base(texture_type type, const vec2u& size, texture_format format);

  /**
   * Move constructor.
   *
   * \param other the other texture.
   */
  texture2_base(texture2_base&& other) noexcept = default;

  /**
   * Destructor.
   */
  virtual ~texture2_base() = 0;

  /**
   * Gets the size of the texture.
   *
   * \return the size of the texture.
   */
  const vec2u& get_size() const noexcept;

  /**
   * Gets the size in bytes of the texture.
   *
   * \return the size in bytes of the texture.
   */
  size_t get_byte_count() const;

private:
  vec2u m_size;
};



class HOU_GFX_API texture2 : public texture2_base
{
public:
  /**
   * Wrap mode type.
   */
  using wrap_mode = std::array<texture_wrap_mode, 2u>;

public:
  /**
   * Retrieves the maximum allowed size for the texture.
   *
   * \return a vector containing the maximum size on each dimension.
   */
  static const vec2u& get_max_size();

  /** Retrieves the maximum allowed number of mip map levels for a given texture
   * size.
   *
   * \return the maximum number of allowed mip map levels.
   */
  static positive<uint> get_max_mipmap_level_count(const vec2u& size);

public:
  /**
   * Creates a texture with the given size, format, and number of mip map
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
  texture2(const vec2u& size, texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);

  /**
   * Creates a texture with the given image, format, and number of mip map
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
  texture2(const pixel_view2& pv, texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);

  /**
   * Move constructor.
   *
   * \param other the other texture.
   */
  texture2(texture2&& other) noexcept = default;

  /**
   * Retrieves the number of mip map levels of this texture.
   *
   * \return the number of mip map levels of this texture.
   */
  positive<uint> get_mipmap_level_count() const noexcept;

  /**
   * Retrieves the texture filter.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \return the texture filter.
   */
  texture_filter get_filter() const;

  /**
   * Sets the texture filter.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param filter the texture filter.
   */
  void set_filter(texture_filter filter);

  /**
   * Retrieves the texture wrap mode.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \return the texture wrap mode.
   */
  wrap_mode get_wrap_mode() const;

  /**
   * Sets the texture wrap mode.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param wrap_mode_type the texture wrap mode.
   */
  void set_wrap_mode(const wrap_mode& wm);

  /**
   * Retrieve the contents of the texture as an image object.
   *
   * \note this function is not supported and will throw if called on a system
   * using GL ES.
   *
   * \throws hou::unsupported_error if on a platform using GL ES.
   *
   * \return an image with the content of the texture.
   */
  std::vector<uint8_t> get_image() const;

  /**
   * Retrieves the contents of a sub-region of the texture as an image object.
   *
   * \note this function is not supported and will throw if called on a system
   * using GL ES.
   *
   * \throws hou::precondition_violation if offset + size > get_size().
   *
   * \throws hou::unsupported_error if on a platform using GL ES.
   *
   * \param offset a pixel offset represeinting the top-left corner of the
   * sub-region
   *
   * \param size the size of the sub-region
   *
   * \return an image with the content of the texture in the specified
   * sub-region.
   */
  std::vector<uint8_t> get_sub_image(
    const vec2u& offset, const vec2u& size) const;

  /**
   * Sets the content of the texture.
   *
   * \param im an image representing the content of the texture.
   */
  void set_image(const pixel_view2& pv);

  /**
   * Sets the content of a sub-region of the texture.
   *
   * \throws hou::precondition_violation if offset + pv.get_size() > get_size().
   *
   * \param offset an offset representing the top-left cornern of the
   * sub-region.
   *
   * \param im an image representing the content of the texture.
   */
  void set_sub_image(const vec2u& offset, const pixel_view2& pv);

  /**
   * Clears the texture to zero.
   */
  void clear();

private:
  texture2(const vec2u& size, texture_format format,
    positive<uint> mipmap_level_count, bool);

private:
  positive<uint> m_mipmap_level_count;
};



class HOU_GFX_API multisampled_texture2 : public texture2_base
{
public:
  /**
   * Retrieves the maximum allowed size for the texture.
   *
   * \return a vector containing the maximum size on each dimension.
   */
  static const vec2u& get_max_size();

  /** Retrieves the maximum amount of samples per pixel.
   *
   * \return the maximum amount of samples per pixel.
   */
  static positive<uint> get_max_sample_count();

public:
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
  multisampled_texture2(const vec2u& size,
    texture_format format = texture_format::rgba,
    positive<uint> sample_count = 1u, bool fixed_sample_locations = true);

  /**
   * Move constructor.
   *
   * \param other the other texture.
   */
  multisampled_texture2(multisampled_texture2&& other) noexcept = default;

  /**
   * Retrieves the number of samples of this texture.
   *
   * \return the number of samples of this texture.
   */
  positive<uint> get_sample_count() const noexcept;

  /**
   * Retrieves whether the samples of this texture have fixed positions.
   *
   * \return whether the samples of this texture have fixed positions.
   */
  bool has_fixed_sample_locations() const noexcept;

private:
  positive<uint> m_sample_count;
  bool m_fixed_sample_locations;
};



class HOU_GFX_API texture3_base : public texture
{
public:
  /**
   * Creates a texture with the given type, size, and format.
   *
   * \param type the type.
   *
   * \param size the size.
   *
   * \format the format.
   */
  texture3_base(texture_type type, const vec3u& size, texture_format format);

  /**
   * Move constructor.
   *
   * \param other the other texture.
   */
  texture3_base(texture3_base&& other) noexcept = default;

  /**
   * Destructor.
   */
  virtual ~texture3_base() = 0;

  /**
   * Gets the size of the texture.
   *
   * \return the size of the texture.
   */
  const vec3u& get_size() const noexcept;

  /**
   * Gets the size in bytes of the texture.
   *
   * \return the size in bytes of the texture.
   */
  size_t get_byte_count() const;

private:
  vec3u m_size;
};



class HOU_GFX_API mipmapped_texture3 : public texture3_base
{
public:
  /**
   * Wrap mode type.
   */
  using wrap_mode = std::array<texture_wrap_mode, 3u>;

public:
  /**
   * Creates a texture with the given size, format, and number of mip map
   * levels.
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
  mipmapped_texture3(texture_type type, const vec3u& size, texture_format format,
    positive<uint> mipmap_level_count);

  /**
   * Move constructor.
   *
   * \param other the other texture.
   */
  mipmapped_texture3(mipmapped_texture3&& other) noexcept = default;

  /**
   * Destructor.
   */
  virtual ~mipmapped_texture3() = 0;

  /**
   * Retrieves the number of mip map levels of this texture.
   *
   * \return the number of mip map levels of this texture.
   */
  positive<uint> get_mipmap_level_count() const noexcept;

  /**
   * Retrieves the texture filter.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \return the texture filter.
   */
  texture_filter get_filter() const;

  /**
   * Sets the texture filter.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param filter the texture filter.
   */
  void set_filter(texture_filter filter);

  /**
   * Retrieves the texture wrap mode.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \return the texture wrap mode.
   */
  wrap_mode get_wrap_mode() const;

  /**
   * Sets the texture wrap mode.
   *
   * \tparam Type2 dummy parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param wrap_mode_type the texture wrap mode.
   */
  void set_wrap_mode(const wrap_mode& wm);

  /**
   * Retrieve the contents of the texture as an image object.
   *
   * \note this function is not supported and will throw if called on a system
   * using GL ES.
   *
   * \throws hou::unsupported_error if on a platform using GL ES.
   *
   * \return an image with the content of the texture.
   */
  std::vector<uint8_t> get_image() const;

  /**
   * Retrieves the contents of a sub-region of the texture as an image object.
   *
   * \note this function is not supported and will throw if called on a system
   * using GL ES.
   *
   * \throws hou::precondition_violation if offset + size > get_size().
   *
   * \throws hou::unsupported_error if on a platform using GL ES.
   *
   * \param offset a pixel offset represeinting the top-left corner of the
   * sub-region
   *
   * \param size the size of the sub-region
   *
   * \return an image with the content of the texture in the specified
   * sub-region.
   */
  std::vector<uint8_t> get_sub_image(
    const vec3u& offset, const vec3u& size) const;

  /**
   * Sets the content of the texture.
   *
   * \param im an image representing the content of the texture.
   */
  void set_image(const pixel_view3& pv);

  /**
   * Sets the content of a sub-region of the texture.
   *
   * \throws hou::precondition_violation if offset + pv.get_size() > get_size().
   *
   * \param offset an offset representing the top-left cornern of the
   * sub-region.
   *
   * \param im an image representing the content of the texture.
   */
  void set_sub_image(const vec3u& offset, const pixel_view3& pv);

  /**
   * Clears the texture to zero.
   */
  void clear();

private:
  positive<uint> m_mipmap_level_count;
};



class HOU_GFX_API texture2_array : public mipmapped_texture3
{
public:
  /**
   * Retrieves the maximum allowed size for the texture.
   *
   * \return a vector containing the maximum size on each dimension.
   */
  static const vec3u& get_max_size();

  /** Retrieves the maximum allowed number of mip map levels for a given texture
   * size.
   *
   * \return the maximum number of allowed mip map levels.
   */
  static positive<uint> get_max_mipmap_level_count(const vec3u& size);

public:
  /**
   * Creates a texture with the given size, format, and number of mip map
   * levels.
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
  texture2_array(const vec3u& size,
    texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);

  /**
   * Creates a texture with the given image, format, and number of mip map
   * levels.
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
  texture2_array(const pixel_view3& pv,
    texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);

  /**
   * Move constructor.
   *
   * \param other the other texture.
   */
  texture2_array(texture2_array&& other) noexcept = default;

private:
  texture2_array(const vec3u& pv, texture_format format,
    positive<uint> mipmap_level_count, bool);
};



class HOU_GFX_API texture3 : public mipmapped_texture3
{
public:
  /**
   * Retrieves the maximum allowed size for the texture.
   *
   * \return a vector containing the maximum size on each dimension.
   */
  static const vec3u& get_max_size();

  /** Retrieves the maximum allowed number of mip map levels for a given texture
   * size.
   *
   * \return the maximum number of allowed mip map levels.
   */
  static positive<uint> get_max_mipmap_level_count(const vec3u& size);

public:
  /**
   * Creates a texture with the given size, format, and number of mip map
   * levels.
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
  texture3(const vec3u& size, texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);

  /**
   * Creates a texture with the given image, format, and number of mip map
   * levels.
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
  texture3(const pixel_view3& pv, texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);

  /**
   * Move constructor.
   *
   * \param other the other texture.
   */
  texture3(texture3&& other) noexcept = default;

private:
  texture3(const vec3u& pv, texture_format format,
    positive<uint> mipmap_level_count, bool);
};



class HOU_GFX_API multisampled_texture2_array : public texture3_base
{
public:
  /**
   * Retrieves the maximum allowed size for the texture.
   *
   * \return a vector containing the maximum size on each dimension.
   */
  static const vec3u& get_max_size();

  /** Retrieves the maximum amount of samples per pixel.
   *
   * \return the maximum amount of samples per pixel.
   */
  static positive<uint> get_max_sample_count();

public:
  /** Creates a texture with the given size, format, and sample specification.
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
  multisampled_texture2_array(const vec3u& size,
    texture_format format = texture_format::rgba,
    positive<uint> sample_count = 1u, bool fixed_sample_locations = true);

  /**
   * Move constructor.
   *
   * \param other the other texture.
   */
  multisampled_texture2_array(multisampled_texture2_array&& other) noexcept
    = default;

  /**
   * Retrieves the number of samples of this texture.
   *
   * \return the number of samples of this texture.
   */
  positive<uint> get_sample_count() const noexcept;

  /**
   * Retrieves whether the samples of this texture have fixed positions.
   *
   * \return whether the samples of this texture have fixed positions.
   */
  bool has_fixed_sample_locations() const noexcept;

private:
  positive<uint> m_sample_count;
  bool m_fixed_sample_locations;
};

}  // namespace exp

}  // namespace hou

#endif
