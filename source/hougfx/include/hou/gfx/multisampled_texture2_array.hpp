// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_MULTISAMPLED_TEXTURE2_ARRAY_HPP
#define HOU_GFX_MULTISAMPLED_TEXTURE2_ARRAY_HPP

#include "hou/gfx/texture3_base.hpp"

namespace hou
{

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
   * Retrieves whether the samples of this texture have fixed positions.
   *
   * \return whether the samples of this texture have fixed positions.
   */
  bool has_fixed_sample_locations() const noexcept;

  // texture overrides
  positive<uint> get_mipmap_level_count() const final;
  positive<uint> get_sample_count() const final;
  bool is_mipmapped() const final;
  bool is_multisampled() const final;

private:
  positive<uint> m_sample_count;
  bool m_fixed_sample_locations;
};

}  // namespace hou

#endif
