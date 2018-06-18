// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_context_settings.hpp"

namespace hou
{

namespace gl
{

const context_settings& context_settings::get_basic() noexcept
{
  static const context_settings cs(
    version(1u, 0u), context_profile::compatibility, 24u, 8u, 0u);
  return cs;
}



const context_settings& context_settings::get_default() noexcept
{
  static const context_settings cs(
    version(4u, 5u), context_profile::core, 24u, 8u, 0u);
  return cs;
}



context_settings::context_settings(const version& vrs, context_profile profile,
  uint depth_bit_count, uint stencil_bit_count, uint sample_count) noexcept
  : m_version(vrs)
  , m_profile(profile)
  , m_depth_bit_count(depth_bit_count)
  , m_stencil_bit_count(stencil_bit_count)
  , m_sample_count(sample_count)
{}



void context_settings::set_version(const version& vrs) noexcept
{
  m_version = vrs;
}



const version& context_settings::get_version() const noexcept
{
  return m_version;
}



context_profile context_settings::get_profile() const noexcept
{
  return m_profile;
}



void context_settings::set_profile(context_profile value) noexcept
{
  m_profile = value;
}



uint context_settings::get_depth_bit_count() const noexcept
{
  return m_depth_bit_count;
}



void context_settings::set_depth_bit_count(uint value) noexcept
{
  m_depth_bit_count = value;
}



uint context_settings::get_stencil_bit_count() const noexcept
{
  return m_stencil_bit_count;
}



void context_settings::set_stencil_bit_count(uint value) noexcept
{
  m_stencil_bit_count = value;
}



uint context_settings::get_sample_count() const noexcept
{
  return m_sample_count;
}



void context_settings::set_sample_count(uint value) noexcept
{
  m_sample_count = value;
}



bool operator==(const context_settings& lhs, const context_settings& rhs) noexcept
{
  return lhs.get_version() == rhs.get_version()
    && lhs.get_profile() == rhs.get_profile()
    && lhs.get_depth_bit_count() == rhs.get_depth_bit_count()
    && lhs.get_stencil_bit_count() == rhs.get_stencil_bit_count()
    && lhs.get_sample_count() == rhs.get_sample_count();
}



bool operator!=(const context_settings& lhs, const context_settings& rhs) noexcept
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const context_settings& cs)
{
  return os << "{gl_version = " << cs.get_version()
            << ", gl_profile = " << cs.get_profile()
            << ", depth_bit_count = " << cs.get_depth_bit_count()
            << ", stencil_bit_count = " << cs.get_stencil_bit_count()
            << ", sample_count = " << cs.get_sample_count() << "}";
}

}  // namespace gl

}  // namespace hou
