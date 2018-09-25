// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE2_BASE_HPP
#define HOU_GFX_TEXTURE2_BASE_HPP

#include "hou/gfx/texture.hpp"


namespace hou
{

class HOU_GFX_API texture2_base : public texture
{
public:
  /**
   * Size type.
   */
  using size_type = vec2u;

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

  /**
   * Gets the size in bytes of a sub-region of the texture with the given size.
   *
   * \return the size in bytes of the texture.
   */
  size_t get_sub_texture_byte_count(const size_type& size) const;

private:
  vec2u m_size;
};

}  // namespace hou

#endif
