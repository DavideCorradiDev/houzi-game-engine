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
  context_settings(const version& vrs, context_profile profile,
    uint depth_byte_count, uint stencil_byte_count, uint sample_count) noexcept;

  const version& get_version() const noexcept;
  void set_version(const version& vrs) noexcept;
  context_profile get_profile() const noexcept;
  void set_profile(context_profile value) noexcept;
  uint get_depth_byte_count() const noexcept;
  void set_depth_byte_count(uint value) noexcept;
  uint get_stencil_byte_count() const noexcept;
  void set_stencil_byte_count(uint value) noexcept;
  uint get_sample_count() const noexcept;
  void set_sample_count(uint value) noexcept;

public:
  static const context_settings standard;

private:
  version m_version;
  context_profile m_profile;
  uint m_depth_byte_count;
  uint m_stencil_byte_count;
  uint m_sample_count;
};

HOU_GL_API bool operator==(
  const context_settings& l, const context_settings& r) noexcept;
HOU_GL_API bool operator!=(
  const context_settings& l, const context_settings& r) noexcept;

}  // namespace gl

}  // namespace hou

#endif
