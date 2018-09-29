// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE3_BASE_HPP
#define HOU_GFX_TEXTURE3_BASE_HPP

#include "hou/gfx/texture.hpp"

namespace hou
{

class HOU_GFX_API texture3_base : public texture
{
public:
  /**
   * Size type.
   */
  using size_type = vec3u;

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
   * Gets the size in bytes of a sub-region of the texture with the given size.
   *
   * \return the size in bytes of the texture.
   */
  uint get_sub_texture_byte_count(const size_type& size) const;

  // texture overrides
  uint get_byte_count() const final;

private:
  vec3u m_size;
};

}  // namespace hou

#endif
