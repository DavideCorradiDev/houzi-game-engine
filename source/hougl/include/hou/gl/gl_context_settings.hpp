// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_CONTEXT_SETTINGS_HPP
#define HOU_GL_CONTEXT_SETTINGS_HPP

#include "hou/gl/gl_color_format.hpp"
#include "hou/gl/gl_context_profile.hpp"
#include "hou/gl/gl_version.hpp"

#include "hou/gl/gl_config.hpp"



namespace hou
{

namespace gl
{

/**
 * Represents a set context creation settings.
 */
class HOU_GL_API context_settings
{
public:
  /**
   * Gets widely supported basic settings.
   *
   * \note using this settings should guarantee that the context will be
   * created successfully, but does not guarantee that all functionality in
   * the library is supported.
   *
   * \return the settings.
   */
  static const context_settings& get_basic() noexcept;

  /**
   * Gets default settings for a core GL context.
   *
   * These settings guarantee that anything in the library will work properly
   * on systems supporting standard OpenGL.
   *
   * \return the settings.
   */
  static const context_settings& get_default_core() noexcept;

  /**
   * Gets default settings for a GLES context.
   *
   * These settings guarantee that anything in the library will work properly
   * on systems supporting GLES.
   *
   * \return the settings.
   */
  static const context_settings& get_default_es() noexcept;

public:
  /**
   * Creates an objects with all settings at their default values.
   */
  context_settings() noexcept;

  /**
   * Gets the requested OpenGL version.
   *
   * The default value is 4.5.
   *
   * \return the requested OpenGL version.
   */
  const version& get_version() const noexcept;

  /**
   * Sets the requested OpenGL version.
   *
   * \param value the value;
   */
  void set_version(const version& value) noexcept;

  /**
   * Gets the requested context profile.
   *
   * The default value is core profile.
   *
   * \return the context profile.
   */
  context_profile get_profile() const noexcept;

  /**
   * Sets the requested context profile.
   *
   * \param value the value;
   */
  void set_profile(context_profile value) noexcept;

  /**
   * Gets the minimum number of color bits for the different channels.
   *
   * The default value is 8 bits for each color channel (red, green, blue)
   * and 0 bits for the alpha channel.
   *
   * \return the minimum number of color bits.
   */
  const color_format& get_color_format() const noexcept;

  /**
   * Sets the minimum number of color bits.
   *
   * \param value the value.
   */
  void set_color_format(const color_format& cf) noexcept;

  /**
   * Gets the minimum number of depth bits.
   *
   * The default value is 24.
   *
   * \return the minimum number of depth bits.
   */
  uint get_depth_bit_count() const noexcept;

  /**
   * Sets the minimum number of depth bits.
   *
   * \param value the value.
   */
  void set_depth_bit_count(uint value) noexcept;

  /**
   * Gets the minimum number of stencil bits.
   *
   * The default value is 8.
   *
   * \return the minimum number of stencil bits.
   */
  uint get_stencil_bit_count() const noexcept;

  /**
   * Sets the minimum number of stencil bits.
   *
   * \param value the value.
   */
  void set_stencil_bit_count(uint value) noexcept;

  /**
   * Gets the number of sample buffers to be used for multisample anti-aliasing.
   *
   * The default value is 0.
   *
   * \return the number of sample buffers.
   */
  uint get_multisample_buffer_count() const noexcept;

  /**
   * Sets the number of sample buffers to be used for multisample anti-aliasing.
   *
   * \param value the value.
   */
  void set_multisample_buffer_count(uint value) noexcept;

  /**
   * Gets the number of samples per pixel to be used for multisample anti-aliasing.
   *
   * The default value is 0.
   *
   * \return the number of samples per pixel.
   */
  uint get_sample_count() const noexcept;

  /**
   * Sets the number of samples per pixel to be used for multisample anti-aliasing.
   *
   * \param value the value.
   */
  void set_sample_count(uint value) noexcept;

  /**
   * Gets if the output is single or double buffered.
   *
   * The default value is true.
   *
   * \return true if the output is double buffered.
   */
  bool double_buffer() const noexcept;

  /**
   * Sets if the output is single or double buffered.
   *
   * \param value the value.
   */
  void set_double_buffer(bool value);

  /**
   * Gets if the required visuals should be sRGB capable.
   *
   * The default value is true.
   *
   * \return true if the required visuals should be sRGB capable.
   */
  bool srgb_capable() const noexcept;

  /**
   * Sets if the required visuals should be sRGB capable.
   *
   * \param value the value.
   */
  void set_srgb_capable(bool value) noexcept;

  /**
   * Gets if the required output is stereo 3D.
   *
   * The default value is false.
   *
   * \return if the required output is stereo 3D.
   */
  bool stereo() const noexcept;

  /**
   * Sets if the required output is stereo 3D.
   *
   * \param value the value.
   */
  void set_stereo(bool value) noexcept;

  /**
   * Gets if OpenGL debug mode is required.
   *
   * The default value is false.
   *
   * \return if OpenGL debug mode is required.
   */
  bool debug_mode() const noexcept;

  /**
   * Sets if OpenGL debug mode is required.
   *
   * \param value the value.
   */
  void set_debug_mode(bool value) noexcept;

  /**
   * Gets if OpenGL forward compatibility mode is required.
   *
   * The default value is false.
   *
   * \return if OpenGL forward compatibility mode is required.
   */
  bool forward_compatibility_mode() const noexcept;

  /**
   * Sets if OpenGL forward compatibility mode is required.
   *
   * \param value the value.
   */
  void set_forward_compatibility_mode(bool value) noexcept;

  /**
   * Gets if OpenGL robust access mode is required.
   *
   * The default value is false.
   *
   * \return if OpenGL robust access mode is required.
   */
  bool robust_access() const noexcept;

  /**
   * Sets if OpenGL robust access mode is required.
   *
   * \param value the value.
   */
  void set_robust_access(bool value) noexcept;

  /**
   * Gets if OpenGL reset isolation mode is required.
   *
   * The default value is false.
   *
   * \return if OpenGL reset isolation mode is required.
   */
  bool reset_isolation() const noexcept;

  /**
   * Sets if OpenGL reset isolation mode is required.
   *
   * \param value the value.
   */
  void set_reset_isolation(bool value) noexcept;

private:
  version m_version;
  context_profile m_profile;
  color_format m_color_format;
  uint m_depth_bit_count;
  uint m_stencil_bit_count;
  uint m_multisample_buffer_count;
  uint m_sample_count;
  bool m_double_buffer;
  bool m_srgb_capable;
  bool m_stereo;
  bool m_debug_mode;
  bool m_forward_compatibility_mode;
  bool m_robust_access;
  bool m_reset_isolation;
};

/** Checks if two context_settings objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_GL_API bool operator==(
  const context_settings& lhs, const context_settings& rhs) noexcept;

/** Checks if two context_settings objects not are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_GL_API bool operator!=(
  const context_settings& lhs, const context_settings& rhs) noexcept;

/** Writes the object into a stream.
 *
 * \param os the stream.
 *
 * \param cs the context_settings object.
 *
 * \return a reference to os.
 */
HOU_GL_API std::ostream& operator<<(
  std::ostream& os, const context_settings& cs);

}  // namespace gl

}  // namespace hou

#endif
