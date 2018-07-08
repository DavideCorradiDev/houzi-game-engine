// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_context_settings.hpp"

#include "hou/cor/std_string.hpp"



namespace hou
{

namespace gl
{

namespace
{

context_settings make_basic_settings() noexcept;
context_settings make_default_core_settings() noexcept;
context_settings make_default_es_settings() noexcept;



context_settings make_basic_settings() noexcept
{
  context_settings cs;
  cs.set_version(version(1u, 0u));
  cs.set_color_format(color_format(3u, 3u, 2u, 0u));
  cs.set_depth_bit_count(16u);
  cs.set_stencil_bit_count(0u);
  cs.set_profile(context_profile::any);
  cs.set_srgb_capable(false);
  return cs;
}



context_settings make_default_core_settings() noexcept
{
  return context_settings();
}



context_settings make_default_es_settings() noexcept
{
  context_settings cs;
  cs.set_version(version(3u, 2u));
  cs.set_profile(context_profile::es);
  cs.set_srgb_capable(false);
  return cs;
}

}  // namespace



const context_settings& context_settings::get_basic() noexcept
{
  static const context_settings cs = make_basic_settings();
  return cs;
}



const context_settings& context_settings::get_default_core() noexcept
{
  static const context_settings cs = make_default_core_settings();
  return cs;
}



const context_settings& context_settings::get_default_es() noexcept
{
  static const context_settings cs = make_default_es_settings();
  return cs;
}



context_settings::context_settings() noexcept
  : m_version(4u, 5u)
  , m_profile(context_profile::core)
  , m_color_format(8u, 8u, 8u, 0u)
  , m_depth_bit_count(24u)
  , m_stencil_bit_count(8u)
  , m_multisample_buffer_count(0u)
  , m_sample_count(0u)
  , m_double_buffer(true)
  , m_srgb_capable(true)
  , m_stereo(false)
  , m_debug_mode(false)
  , m_forward_compatibility_mode(false)
  , m_robust_access(false)
  , m_reset_isolation(false)
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



const color_format& context_settings::get_color_format() const noexcept
{
  return m_color_format;
}



void context_settings::set_color_format(const color_format& cf) noexcept
{
  m_color_format = cf;
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



uint context_settings::get_multisample_buffer_count() const noexcept
{
  return m_multisample_buffer_count;
}



void context_settings::set_multisample_buffer_count(uint value) noexcept
{
  m_multisample_buffer_count = value;
}



uint context_settings::get_sample_count() const noexcept
{
  return m_sample_count;
}



void context_settings::set_sample_count(uint value) noexcept
{
  m_sample_count = value;
}



bool context_settings::double_buffer() const noexcept
{
  return m_double_buffer;
}



void context_settings::set_double_buffer(bool value)
{
  m_double_buffer = value;
}



bool context_settings::srgb_capable() const noexcept
{
  return m_srgb_capable;
}



void context_settings::set_srgb_capable(bool value) noexcept
{
  m_srgb_capable = value;
}



bool context_settings::stereo() const noexcept
{
  return m_stereo;
}



void context_settings::set_stereo(bool value) noexcept
{
  m_stereo = value;
}



bool context_settings::debug_mode() const noexcept
{
  return m_debug_mode;
}



void context_settings::set_debug_mode(bool value) noexcept
{
  m_debug_mode = value;
}



bool context_settings::forward_compatibility_mode() const noexcept
{
  return m_forward_compatibility_mode;
}



void context_settings::set_forward_compatibility_mode(bool value) noexcept
{
  m_forward_compatibility_mode = value;
}



bool context_settings::robust_access() const noexcept
{
  return m_robust_access;
}



void context_settings::set_robust_access(bool value) noexcept
{
  m_robust_access = value;
}



bool context_settings::reset_isolation() const noexcept
{
  return m_reset_isolation;
}



void context_settings::set_reset_isolation(bool value) noexcept
{
  m_reset_isolation = value;
}



bool operator==(
  const context_settings& lhs, const context_settings& rhs) noexcept
{
  return lhs.get_version() == rhs.get_version()
    && lhs.get_profile() == rhs.get_profile()
    && lhs.get_color_format() == rhs.get_color_format()
    && lhs.get_depth_bit_count() == rhs.get_depth_bit_count()
    && lhs.get_stencil_bit_count() == rhs.get_stencil_bit_count()
    && lhs.get_multisample_buffer_count() == rhs.get_multisample_buffer_count()
    && lhs.get_sample_count() == rhs.get_sample_count()
    && lhs.double_buffer() == rhs.double_buffer()
    && lhs.srgb_capable() == rhs.srgb_capable() && lhs.stereo() == rhs.stereo()
    && lhs.debug_mode() == rhs.debug_mode()
    && lhs.forward_compatibility_mode() == rhs.forward_compatibility_mode()
    && lhs.robust_access() == rhs.robust_access()
    && lhs.reset_isolation() == rhs.reset_isolation();
}



bool operator!=(
  const context_settings& lhs, const context_settings& rhs) noexcept
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const context_settings& cs)
{
  return os << "{gl_version = " << cs.get_version()
            << ", gl_profile = " << cs.get_profile()
            << ", color_format = " << cs.get_color_format()
            << ", depth_bit_count = " << cs.get_depth_bit_count()
            << ", stencil_bit_count = " << cs.get_stencil_bit_count()
            << ", multisample_buffer_count = "
            << cs.get_multisample_buffer_count()
            << ", sample_count = " << cs.get_sample_count()
            << ", double_buffer = " << to_string(cs.double_buffer())
            << ", srgb_capable = " << to_string(cs.srgb_capable())
            << ", stereo = " << to_string(cs.stereo())
            << ", debug_mode = " << to_string(cs.debug_mode())
            << ", forward_compatibility_mode = "
            << to_string(cs.forward_compatibility_mode())
            << ", robust_access = " << to_string(cs.robust_access())
            << ", reset_isolation = " << to_string(cs.reset_isolation()) << "}";
}

}  // namespace gl

}  // namespace hou
