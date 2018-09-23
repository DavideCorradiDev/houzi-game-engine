// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE2_HPP
#define HOU_GFX_TEXTURE2_HPP

#include "hou/gfx/texture2_base.hpp"

#include "hou/sys/image_fwd.hpp"



namespace hou
{

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
   * Retrieves the contents of the texture as a sequence of bytes.
   *
   * \throws hou::unsupported_error if on a platform using GL ES.
   *
   * \return the texture contents as a sequence of bytes.
   */
  std::vector<uint8_t> get_pixels() const;

  /**
   * Retrieves the contents of a sub-region of the texture as a sequence of bytes.
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
   * \return the contents of the texture sub-region  as a sequence of bytes.
   */
  std::vector<uint8_t> get_sub_pixels(
    const vec2u& offset, const vec2u& size) const;

  /**
   * Sets the content of the texture.
   *
   * \throws hou::precondition_violation if the size of pixels does not
   * corresponds to the size of the texture in bytes.
   *
   * \param pv a pixel view representing the context of the texture.
   */
  void set_pixels(const span<const uint8_t>& pixels);

  /**
   * Sets the content of a sub-region of the texture.
   *
   * \throws hou::precondition_violation if offset + size > get_size().
   *
   * \throws hou::precondition_violation if the size of pixels does not
   * correspond to the required size.
   *
   * \param offset an offset representing the top-left cornern of the
   * sub-region.
   *
   * \param pv a pixel view representing the context of the texture.
   */
  void set_sub_pixels(
    const vec2u& offset, const vec2u& size, const span<const uint8_t>& pixels);

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
  image2<PF> get_image() const;

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
  image2<PF> get_sub_image(const vec2u& offset, const vec2u& size) const;

  /**
   * Sets the content of the texture.
   *
   * \throws hou::precondition_violation if pv.get_size() != get_size().
   *
   * \param pv a pixel view representing the context of the texture.
   */
  void set_image(const pixel_view2& pv);

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
  void set_sub_image(const vec2u& offset, const pixel_view2& pv);

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
  void set_image(const image2<PF>& img);

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
  void set_sub_image(const vec2u& offset, const image2<PF>& img);

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
  texture2(const vec2u& size, texture_format format,
    positive<uint> mipmap_level_count, bool);

private:
  positive<uint> m_mipmap_level_count;
};

}  // namespace hou



#include "hou/gfx/texture2.inl"

#endif
