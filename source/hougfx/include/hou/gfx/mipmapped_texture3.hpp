// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_MIPMAPPED_TEXTURE3_HPP
#define HOU_GFX_MIPMAPPED_TEXTURE3_HPP

#include "hou/gfx/texture3_base.hpp"

namespace hou
{

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
  mipmapped_texture3(texture_type type, const vec3u& size,
    texture_format format, positive<uint> mipmap_level_count);

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
  std::vector<uint8_t> get_pixels() const;

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
  std::vector<uint8_t> get_sub_pixels(
    const vec3u& offset, const vec3u& size) const;

  /**
   * Sets the content of the texture.
   *
   * \param im an image representing the content of the texture.
   */
  void set_pixels(const span<const uint8_t>& pixels);

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
  void set_sub_pixels(
    const vec3u& offset, const vec3u& size, const span<const uint8_t>& pixels);

  /**
   * Retrieve the contents of the texture as an image object.
   *
   * \note this function is not supported and will throw if called on a system
   * using GL ES.
   *
   * \throws hou::unsupported_error if on a platform using GL ES.
   *
   * \tparam PF the pixel format of the returned image.
   *
   * \return an image with the content of the texture.
   */
  template <pixel_format PF>
  image3<PF> get_image() const;

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
   * \tparam PF the pixel format of the returned image.
   *
   * \param offset a pixel offset represeinting the top-left corner of the
   * sub-region
   *
   * \param size the size of the sub-region
   *
   * \return an image with the content of the texture in the specified
   * sub-region.
   */
  template <pixel_format PF>
  image3<PF> get_sub_image(const vec3u& offset, const vec3u& size) const;

  /**
   * Sets the content of the texture.
   *
   * \throws hou::precondition_violation if pv.get_size() != get_size().
   *
   * \param pv a pixel view representing the context of the texture.
   */
  void set_image(const pixel_view3& pv);

  /**
   * Sets the content of a sub-region of the texture.
   *
   * \throws hou::precondition_violation if offset + pv.get_size() > get_size().
   *
   * \param offset an offset representing the top-left corner of the
   * sub-region.
   *
   * \param pv a pixel view representing the context of the texture.
   */
  void set_sub_image(const vec3u& offset, const pixel_view3& pv);

  /**
   * Sets the content of the texture.
   *
   * \tparam PF the pixel format of img.
   *
   * \throws hou::precondition_violation if img.get_size() != get_size().
   *
   * \param img an image representing the contents of the texture.
   */
  template <pixel_format PF>
  void set_image(const image3<PF>& img);

  /**
   * Sets the content of the texture.
   *
   * \tparam PF the pixel format of img.
   *
   * \throws hou::precondition_violation if offset + img.get_size() > get_size().
   *
   * \param offset an offset representing the top-left corner of the
   * sub-region.
   *
   * \param img an image representing the contents of the texture.
   */
  template <pixel_format PF>
  void set_sub_image(const vec3u& offset, const image3<PF>& img);

  /**
   * Clears the texture to zero.
   */
  void clear();

  // texture overrides
  positive<uint> get_mipmap_level_count() const final;
  positive<uint> get_sample_count() const final;
  bool is_mipmapped() const final;
  bool is_multisampled() const final;

private:
  positive<uint> m_mipmap_level_count;
};

}  // namespace hou

#include "hou/gfx/mipmapped_texture3.inl"

#endif
