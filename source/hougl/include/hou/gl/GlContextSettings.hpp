// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_CONTEXT_SETTINGS_HPP
#define HOU_GL_CONTEXT_SETTINGS_HPP

#include "hou/gl/gl_export.hpp"

#include "hou/gl/gl_context_profile.hpp"
#include "hou/gl/gl_version.hpp"

#include "hou/cor/basic_types.hpp"



namespace hou
{

namespace gl
{

class HOU_GL_API context_settings
{
public:
  context_settings(const version& ph_version, context_profile profile,
    uint depthByteCount, uint stencilByteCount, uint sampleCount);

  const version& get_version() const;
  void set_version(const version& ph_version);
  context_profile get_profile() const;
  void set_profile(context_profile value);
  uint get_depth_byte_count() const;
  void set_depth_byte_count(uint value);
  uint get_stencil_byte_count() const;
  void set_stencil_byte_count(uint value);
  uint get_sample_count() const;
  void setSampleCount(uint value);

public:
  static const context_settings default;

private:
  version m_version;
  context_profile m_profile;
  uint m_depth_byte_count;
  uint m_stencil_byte_count;
  uint m_sample_count;
};

HOU_GL_API bool operator==(const context_settings& l, const context_settings& r);
HOU_GL_API bool operator!=(const context_settings& l, const context_settings& r);

}  // namespace gl

}  // namespace hou

#endif
