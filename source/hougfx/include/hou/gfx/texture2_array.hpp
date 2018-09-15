// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE2_ARRAY_HPP
#define HOU_GFX_TEXTURE2_ARRAY_HPP

#include "hou/gfx/mipmapped_texture3.hpp"

namespace hou
{

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

}  // namespace hou

#endif
