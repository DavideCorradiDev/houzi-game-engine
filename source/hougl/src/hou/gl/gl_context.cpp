// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_context.hpp"

#include "hou/cor/assertions.hpp"
#include "hou/cor/uid_generator.hpp"

#include "hou/sys/window.hpp"



namespace hou
{

namespace gl
{

namespace
{

thread_local static context* g_current_context(nullptr);
thread_local static uint32_t g_current_window_uid(0u);



uint32_t generate_uid();



uint32_t generate_uid()
{
  static uid_generator uid_gen(1u);
  return uid_gen.generate();
}

}  // namespace



void context::set_current(context& ctx, window& wnd)
{
  if(!ctx.is_current() || g_current_window_uid != wnd.get_uid())
  {
    prv::context_impl::set_current(ctx.m_impl, wnd);
    g_current_context = &ctx;
    g_current_window_uid = wnd.get_uid();
  }
}



void context::unset_current()
{
  if(get_current() != nullptr)
  {
    prv::context_impl::unset_current();
    g_current_context = nullptr;
    g_current_window_uid = 0u;
  }
}



context* context::get_current() noexcept
{
  return g_current_context;
}



context::context(const context_settings& settings, const window& wnd)
  : context(settings, wnd, nullptr)
{}



context::context(const context_settings& settings, const window& wnd,
  const context& shared_context)
  : context(settings, wnd, &shared_context)
{}



context::context(context&& other) noexcept
  : non_copyable()
  , m_impl(std::move(other.m_impl))
  , m_uid(std::move(other.m_uid))
  , m_sharing_group_uid(std::move(other.m_sharing_group_uid))
  , m_tracking_data(std::move(other.m_tracking_data))
{
  if(get_current() == &other)
  {
    g_current_context = this;
  }
}



context::~context()
{
  if(is_current())
  {
    unset_current();
  }
}



uint32_t context::get_uid() const noexcept
{
  return m_uid;
}



uint32_t context::get_sharing_group_uid() const noexcept
{
  return m_sharing_group_uid;
}



bool context::is_current() const noexcept
{
  return this == g_current_context;
}



context::context(const context_settings& settings, const window& wnd,
  const context* shared_context)
  : non_copyable()
  , m_impl(settings, wnd,
      (shared_context == nullptr) ? nullptr : &(shared_context->m_impl))
  , m_uid(generate_uid())
  , m_sharing_group_uid(
      (shared_context == nullptr) ? m_uid : shared_context->m_sharing_group_uid)
  , m_tracking_data()
{}



context::TrackingData::TrackingData() noexcept
  : m_bound_array_buffer(0u)
  , m_bound_element_array_buffer(0u)
  , m_bound_draw_framebuffer(0u)
  , m_bound_read_framebuffer(0u)
  , m_bound_program(0u)
  , m_bound_vertex_array(0u)
  , m_active_texture(0u)
  , m_bound_textures(1u, 0u)
  , m_bound_texture_targets(1u, GL_TEXTURE_1D)
  , m_current_viewport(0, 0, 0, 0)
{}



uint32_t context::TrackingData::get_bound_buffer(GLenum target) const noexcept
{
  switch(target)
  {
    case GL_ARRAY_BUFFER:
      return m_bound_array_buffer;
    case GL_ELEMENT_ARRAY_BUFFER:
      return m_bound_element_array_buffer;
    default:
      HOU_UNREACHABLE();
      return 0u;
  }
}



void context::TrackingData::set_bound_buffer(
  uint32_t uid, GLenum target) noexcept
{
  switch(target)
  {
    case GL_ARRAY_BUFFER:
      m_bound_array_buffer = uid;
      break;
    case GL_ELEMENT_ARRAY_BUFFER:
      m_bound_element_array_buffer = uid;
      break;
    default:
      HOU_UNREACHABLE();
      break;
  }
}



uint32_t context::TrackingData::get_bound_framebuffer(GLenum target) const
  noexcept
{
  switch(target)
  {
    case GL_DRAW_FRAMEBUFFER:
      return m_bound_draw_framebuffer;
    case GL_READ_FRAMEBUFFER:
      return m_bound_read_framebuffer;
    default:
      HOU_UNREACHABLE();
      return 0u;
  }
}



void context::TrackingData::set_bound_framebuffer(
  uint32_t uid, GLenum target) noexcept
{
  switch(target)
  {
    case GL_DRAW_FRAMEBUFFER:
      m_bound_draw_framebuffer = uid;
      break;
    case GL_READ_FRAMEBUFFER:
      m_bound_read_framebuffer = uid;
      break;
    default:
      HOU_UNREACHABLE();
      break;
  }
}



uint32_t context::TrackingData::get_bound_program() const noexcept
{
  return m_bound_program;
}



void context::TrackingData::set_bound_program(uint32_t uid) noexcept
{
  m_bound_program = uid;
}



void context::TrackingData::resize_texture_vectors(size_t size)
{
  if(m_bound_textures.size() < size)
  {
    m_bound_textures.resize(size, 0u);
    m_bound_texture_targets.resize(size, GL_TEXTURE_1D);
  }
}



GLuint context::TrackingData::get_active_texture() const noexcept
{
  return m_active_texture;
}



void context::TrackingData::set_active_texture(GLuint unit)
{
  m_active_texture = unit;
  resize_texture_vectors(++unit);
}



uint32_t context::TrackingData::get_bound_texture() const noexcept
{
  return get_bound_texture(m_active_texture);
}



uint32_t context::TrackingData::get_bound_texture(GLuint unit) const noexcept
{
  if(m_bound_textures.size() > unit)
  {
    return m_bound_textures[unit];
  }
  else
  {
    return 0u;
  }
}



GLenum context::TrackingData::get_bound_texture_target() const noexcept
{
  return get_bound_texture_target(m_active_texture);
}



GLenum context::TrackingData::get_bound_texture_target(GLuint unit) const
  noexcept
{
  if(m_bound_texture_targets.size() > unit)
  {
    return m_bound_texture_targets[unit];
  }
  else
  {
    return GL_TEXTURE_1D;
  }
}



void context::TrackingData::set_bound_texture(uint32_t uid, GLenum target)
{
  set_bound_texture(uid, m_active_texture, target);
}



void context::TrackingData::set_bound_texture(
  uint32_t uid, GLuint unit, GLenum target)
{
  resize_texture_vectors(unit + 1);
  HOU_DEV_ASSERT(m_bound_textures.size() > unit);
  HOU_DEV_ASSERT(m_bound_texture_targets.size() > unit);
  m_bound_textures[unit] = uid;
  m_bound_texture_targets[unit] = target;
}



uint32_t context::TrackingData::get_bound_vertex_array() const noexcept
{
  return m_bound_vertex_array;
}



void context::TrackingData::set_bound_vertex_array(uint32_t uid) noexcept
{
  m_bound_vertex_array = uid;
}



const recti& context::TrackingData::get_current_viewport() const noexcept
{
  return m_current_viewport;
}



void context::TrackingData::set_current_viewport(const recti& viewport) noexcept
{
  m_current_viewport = viewport;
}

}  // namespace gl

}  // namespace hou
