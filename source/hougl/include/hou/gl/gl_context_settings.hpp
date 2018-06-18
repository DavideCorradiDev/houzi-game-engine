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

class HOU_GL_API context_settings
{
public:
  static const context_settings& get_basic() noexcept;

  static const context_settings& get_default() noexcept;

public:
  context_settings() noexcept;

  const version& get_version() const noexcept;
  void set_version(const version& value) noexcept;

  context_profile get_profile() const noexcept;
  void set_profile(context_profile value) noexcept;

  const color_format& get_color_format() const noexcept;
  void set_color_format(const color_format& cf) noexcept;

  uint get_depth_bit_count() const noexcept;
  void set_depth_bit_count(uint value) noexcept;

  uint get_stencil_bit_count() const noexcept;
  void set_stencil_bit_count(uint value) noexcept;

  uint get_multisample_buffer_count() const noexcept;
  void set_multisample_buffer_count(uint value) noexcept;

  uint get_sample_count() const noexcept;
  void set_sample_count(uint value) noexcept;

  bool double_buffer() const noexcept;
  void set_double_buffer(bool value);

  bool srgb_capable() const noexcept;
  void set_srgb_capable(bool value) noexcept;

  bool stereo() const noexcept;
  void set_stereo(bool value) noexcept;

  bool share_with_current_context() const noexcept;
  void set_share_with_current_context(bool value) noexcept;

  bool debug_mode() const noexcept;
  void set_debug_mode(bool value) noexcept;

  bool forward_compatibility_mode() const noexcept;
  void set_forward_compatibility_mode(bool value) noexcept;

  bool robust_access() const noexcept;
  void set_robust_access(bool value) noexcept;

  bool reset_isolation() const noexcept;
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
  bool m_share_with_current_context;
  bool m_debug_mode;
  bool m_forward_compatibility_mode;
  bool m_robust_access;
  bool m_reset_isolation;
};

HOU_GL_API bool operator==(
  const context_settings& lhs, const context_settings& rhs) noexcept;

HOU_GL_API bool operator!=(
  const context_settings& lhs, const context_settings& rhs) noexcept;

HOU_GL_API std::ostream& operator<<(
  std::ostream& os, const context_settings& cs);

}  // namespace gl

}  // namespace hou

#endif
