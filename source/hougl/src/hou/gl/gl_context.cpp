// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_context.hpp"

#include "hou/cor/error.hpp"
#include "hou/cor/uid_generator.hpp"

#include "hou/sys/window.hpp"



namespace hou
{

namespace gl
{

namespace
{

uint32_t generate_uid();



uint32_t generate_uid()
{
  static uid_generator uid_gen(1u);
  return uid_gen.generate();
}

}  // namespace



void context::set_current(context& ph_context, window& ph_window)
{
  if(!ph_context.is_current() || sCurrentWindowUid != ph_window.get_uid())
  {
    prv::context_impl::set_current(ph_context.m_impl, ph_window);
    sCurrentContext = &ph_context;
    sCurrentWindowUid = ph_window.get_uid();
  }
}



void context::unset_current()
{
  if(getCurrent() != nullptr)
  {
    prv::context_impl::unset_current();
    sCurrentContext = nullptr;
    sCurrentWindowUid = 0u;
  }
}



context* context::getCurrent()
{
  return sCurrentContext;
}



context::context(const context_settings& settings, const window& ph_window)
  : context(settings, ph_window, nullptr)
{}



context::context(const context_settings& settings, const window& ph_window,
  const context& sharedContext)
  : context(settings, ph_window, &sharedContext)
{}



context::context(context&& other)
  : non_copyable()
  , m_impl(std::move(other.m_impl))
  , m_uid(std::move(other.m_uid))
  , mSharingGroupUid(std::move(other.mSharingGroupUid))
  , mTrackingData(std::move(other.mTrackingData))
{
  if(getCurrent() == &other)
  {
    sCurrentContext = this;
  }
}



context::~context()
{
  if(is_current())
  {
    unset_current();
  }
}



uint32_t context::get_uid() const
{
  return m_uid;
}



uint32_t context::getSharingGroupUid() const
{
  return mSharingGroupUid;
}



bool context::is_current() const
{
  return this == sCurrentContext;
}



thread_local context* context::sCurrentContext(nullptr);
thread_local uint32_t context::sCurrentWindowUid(0u);



context::context(const context_settings& settings, const window& ph_window,
  const context* sharedContext)
  : non_copyable()
  , m_impl(settings, ph_window,
      (sharedContext == nullptr) ? nullptr : &(sharedContext->m_impl))
  , m_uid(generate_uid())
  , mSharingGroupUid(
      (sharedContext == nullptr) ? m_uid : sharedContext->mSharingGroupUid)
  , mTrackingData()
{}



context::TrackingData::TrackingData()
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



uint32_t context::TrackingData::get_bound_buffer(GLenum target) const
{
  switch(target)
  {
  case GL_ARRAY_BUFFER:
    return m_bound_array_buffer;
  case GL_ELEMENT_ARRAY_BUFFER:
    return m_bound_element_array_buffer;
  default:
    return 0u;
  }
}



void context::TrackingData::set_bound_buffer(uint32_t uid, GLenum target)
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
    break;
  }
}



uint32_t context::TrackingData::get_bound_framebuffer(GLenum target) const
{
  switch(target)
  {
  case GL_DRAW_FRAMEBUFFER:
    return m_bound_draw_framebuffer;
  case GL_READ_FRAMEBUFFER:
    return m_bound_read_framebuffer;
  default:
    return 0u;
  }
}



void context::TrackingData::set_bound_framebuffer(uint32_t uid, GLenum target)
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
    break;
  }
}



uint32_t context::TrackingData::get_bound_program() const
{
  return m_bound_program;
}



void context::TrackingData::set_bound_program(uint32_t uid)
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



GLuint context::TrackingData::get_active_texture() const
{
  return m_active_texture;
}



void context::TrackingData::set_active_texture(GLuint unit)
{
  m_active_texture = unit;
  resize_texture_vectors(++unit);
}



uint32_t context::TrackingData::get_bound_texture() const
{
  return get_bound_texture(m_active_texture);
}



uint32_t context::TrackingData::get_bound_texture(GLuint unit) const
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



GLenum context::TrackingData::get_bound_texture_target() const
{
  return get_bound_texture_target(m_active_texture);
}



GLenum context::TrackingData::get_bound_texture_target(GLuint unit) const
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
  HOU_EXPECT_DEV(m_bound_textures.size() > unit);
  HOU_EXPECT_DEV(m_bound_texture_targets.size() > unit);
  m_bound_textures[unit] = uid;
  m_bound_texture_targets[unit] = target;
}



uint32_t context::TrackingData::get_bound_vertex_array() const
{
  return m_bound_vertex_array;
}



void context::TrackingData::set_bound_vertex_array(uint32_t uid)
{
  m_bound_vertex_array = uid;
}



const recti& context::TrackingData::get_current_viewport() const
{
  return m_current_viewport;
}



void context::TrackingData::set_current_viewport(const recti& viewport)
{
  m_current_viewport = viewport;
}

}  // namespace gl

}  // namespace hou
