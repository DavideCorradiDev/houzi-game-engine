// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_CONTEXT_SETTINGS_HPP
#define HOU_GL_CONTEXT_SETTINGS_HPP

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
  context_settings(const version& vrs, context_profile profile,
    uint depth_bit_count, uint stencil_bit_count, uint sample_count) noexcept;

  const version& get_version() const noexcept;
  void set_version(const version& value) noexcept;

  context_profile get_profile() const noexcept;
  void set_profile(context_profile value) noexcept;

  // color bits.
  // display_format_mask get_display_format() const noexcept;
  // void set_display_format(display_format value) noexcept;

  uint get_depth_bit_count() const noexcept;
  void set_depth_bit_count(uint value) noexcept;

  uint get_stencil_bit_count() const noexcept;
  void set_stencil_bit_count(uint value) noexcept;

  uint get_multisample_buffer_count() const noexcept;
  void set_multisample_buffer_count(uint value) const noexcept;

  uint get_sample_count() const noexcept;
  void set_sample_count(uint value) noexcept;

  bool double_buffer() const noexcept;
  void set_double_buffer(bool value);

  bool srgb_capable() const noexcept;
  void set_srgb_capable(bool value);

  bool share_with_current_context() const noexcept;
  void set_share_with_current_context(bool value) const noexcept;

  // gl flags.

private:
  version m_version;
  context_profile m_profile;
  uint m_depth_bit_count;
  uint m_stencil_bit_count;
  uint m_sample_count;
  bool m_srgb_capable;
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
