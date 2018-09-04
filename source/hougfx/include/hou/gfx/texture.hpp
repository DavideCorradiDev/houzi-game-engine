// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_HPP
#define HOU_GFX_TEXTURE_HPP

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

namespace hou
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

  /**
   * Retrieves the number of mip map levels of this texture.
   *
   * \return the number of mip map levels of this texture.
   */
  virtual positive<uint> get_mipmap_level_count() const = 0;

  /**
   * Retrieves the number of samples of this texture.
   *
   * \return the number of samples of this texture.
   */
  virtual positive<uint> get_sample_count() const = 0;

  /**
   * Checks if the texture is mipmapped.
   *
   * \return true if the texture is mipmapped.
   */
  virtual bool is_mipmapped() const = 0;

  /**
   * Checks if the texture is multisampled.
   *
   * \return true if the texture is multisampled.
   */
  virtual bool is_multisampled() const = 0;

protected:
  texture_filter get_filter_internal() const;
  void set_filter_internal(texture_filter filter);

private:
  gl::texture_handle m_handle;
  texture_type m_type;
  texture_format m_format;
};

}  // namespace hou

#endif
