// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_context_settings.hpp"

namespace hou
{

namespace gl
{

const context_settings context_settings::standard
  = context_settings(version::standard, context_profile::core, 3u, 1u, 0u);



context_settings::context_settings(const version& vrs, context_profile profile,
  uint depth_byte_count, uint stencil_byte_count, uint sample_count)
  : m_version(vrs)
  , m_profile(profile)
  , m_depth_byte_count(depth_byte_count)
  , m_stencil_byte_count(stencil_byte_count)
  , m_sample_count(sample_count)
{}



void context_settings::set_version(const version& vrs)
{
  m_version = vrs;
}



const version& context_settings::get_version() const
{
  return m_version;
}



context_profile context_settings::get_profile() const
{
  return m_profile;
}



void context_settings::set_profile(context_profile value)
{
  m_profile = value;
}



uint context_settings::get_depth_byte_count() const
{
  return m_depth_byte_count;
}



void context_settings::set_depth_byte_count(uint value)
{
  m_depth_byte_count = value;
}



uint context_settings::get_stencil_byte_count() const
{
  return m_stencil_byte_count;
}



void context_settings::set_stencil_byte_count(uint value)
{
  m_stencil_byte_count = value;
}



uint context_settings::get_sample_count() const
{
  return m_sample_count;
}



void context_settings::set_sample_count(uint value)
{
  m_sample_count = value;
}



bool operator==(const context_settings& l, const context_settings& r)
{
  return l.get_version() == r.get_version()
    && l.get_profile() == r.get_profile()
    && l.get_depth_byte_count() == r.get_depth_byte_count()
    && l.get_stencil_byte_count() == r.get_stencil_byte_count()
    && l.get_sample_count() == r.get_sample_count();
}



bool operator!=(const context_settings& l, const context_settings& r)
{
  return !(l == r);
}

}  // namespace gl

}  // namespace hou
