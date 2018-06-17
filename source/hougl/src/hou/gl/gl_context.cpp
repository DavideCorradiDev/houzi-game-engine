// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_context.hpp"

#include "hou/gl/gl_exceptions.hpp"

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

thread_local static window::uid_type g_current_window_uid(0u);



//class context_attributes_scope
//{
//public:
//  context_attributes_scope(const context_settings& cs, context* sharing_ctx);
//  ~context_attributes_scope();
//
//private:
//  void set_attributes(const context_settings& cs, context* sharing_ctx);
//
//private:
//  context* m_context_bkp;
//  context_settings m_settings_bkp;
//};

uint32_t generate_uid();

void set_attributes(const context_settings& settings, context* sharing_ctx);



void set_attributes(const context_settings& settings, context* sharing_ctx)
{
  SDL_GL_ResetAttributes();

  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_MAJOR_VERSION, settings.get_version().get_major());
  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_MINOR_VERSION, settings.get_version().get_minor());

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
    settings.get_profile() == context_profile::core
      ? SDL_GL_CONTEXT_PROFILE_CORE
      : SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, settings.get_depth_bit_count());

  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, settings.get_stencil_bit_count());

  if(sharing_ctx != nullptr)
  {
    SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, SDL_TRUE);
  }
}



uint32_t generate_uid()
{
  static uid_generator uid_gen(1u);
  return uid_gen.generate();
}



// context_attributes_scope::context_attributes_scope(
//   const context_settings& cs, context* sharing_ctx);
// {
//   set_attributes(cs);
// }
// 
// 
// 
// context_attributes_scope::~context_attributes_scope()
// {
//   set_attributes(m_settings_bkp);
//   if(m_context_bkp)
//   {
//     context::set_current(m_context_bkp);
//   }
// }
// 
// 
// 
// void context_attributes_scope::set_attributes(
//   const context_settings& cs, context* sharing_ctx)
// {
//   SDL_GL_ResetAttributes();
// 
//   SDL_GL_SetAttribute(
//     SDL_GL_CONTEXT_MAJOR_VERSION, settings.get_version().get_major());
//   SDL_GL_SetAttribute(
//     SDL_GL_CONTEXT_MINOR_VERSION, settings.get_version().get_minor());
// 
//   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
//     settings.get_profile() == context_profile::core
//       ? SDL_GL_CONTEXT_PROFILE_CORE
//       : SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
// 
//   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, settings.get_depth_bit_count());
// 
//   SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, settings.get_stencil_bit_count());
// 
//   if(sharing_ctx != nullptr)
//   {
//     SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, SDL_TRUE);
//   }
// }

}  // namespace



void context::set_current(context& ctx, window& wnd)
{
  if(!ctx.is_current() || g_current_window_uid != wnd.get_uid())
  {
    HOU_CHECK_0(SDL_GL_MakeCurrent(wnd.get_impl(), ctx.get_impl()) == 0,
      context_switch_error);
    g_current_context = &ctx;
    g_current_window_uid = wnd.get_uid();
  }
}



void context::unset_current()
{
  if(get_current() != nullptr)
  {
    HOU_CHECK_0(
      SDL_GL_MakeCurrent(nullptr, nullptr) == 0, context_switch_error);
    g_current_context = nullptr;
    g_current_window_uid = 0u;
  }
}



context* context::get_current() noexcept
{
  return g_current_context;
}



context::context(const context_settings& settings, window& wnd)
  : non_copyable()
  , m_impl(nullptr)
  , m_uid(generate_uid())
  , m_sharing_group_uid(m_uid)
  , m_tracking_data()
{
  set_attributes(settings, nullptr);
  m_impl = SDL_GL_CreateContext(wnd.get_impl());
  HOU_CHECK_0(m_impl != nullptr, context_creation_error);
}



context::context(
  const context_settings& settings, window& wnd, context& sharing_ctx)
  : non_copyable()
  , m_impl(nullptr)
  , m_uid(generate_uid())
  , m_sharing_group_uid(sharing_ctx.m_uid)
  , m_tracking_data()
{
  set_attributes(settings, &sharing_ctx);
  m_impl = SDL_GL_CreateContext(wnd.get_impl());
  HOU_CHECK_0(m_impl != nullptr, context_creation_error);
}



context::context(context&& other) noexcept
  : non_copyable()
  , m_impl(std::move(other.m_impl))
  , m_uid(std::move(other.m_uid))
  , m_sharing_group_uid(std::move(other.m_sharing_group_uid))
  , m_tracking_data(std::move(other.m_tracking_data))
{
  other.m_impl = nullptr;
  if(get_current() == &other)
  {
    g_current_context = this;
  }
}



context::~context()
{
  if(m_impl != nullptr)
  {
    SDL_GL_DeleteContext(m_impl);
    if(is_current())
    {
      unset_current();
    }
  }
}



const context::impl_type& context::get_impl() const noexcept
{
  return m_impl;
}



context::impl_type& context::get_impl() noexcept
{
  return m_impl;
}



context::uid_type context::get_uid() const noexcept
{
  return m_uid;
}



context::uid_type context::get_sharing_group_uid() const noexcept
{
  return m_sharing_group_uid;
}



bool context::is_current() const
{
  return this == g_current_context;
}



context::tracking_data::tracking_data() noexcept
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



uint32_t context::tracking_data::get_bound_buffer(GLenum target) const noexcept
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



void context::tracking_data::set_bound_buffer(
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



uint32_t context::tracking_data::get_bound_framebuffer(GLenum target) const
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



void context::tracking_data::set_bound_framebuffer(
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



uint32_t context::tracking_data::get_bound_program() const noexcept
{
  return m_bound_program;
}



void context::tracking_data::set_bound_program(uint32_t uid) noexcept
{
  m_bound_program = uid;
}



void context::tracking_data::resize_texture_vectors(size_t size)
{
  if(m_bound_textures.size() < size)
  {
    m_bound_textures.resize(size, 0u);
    m_bound_texture_targets.resize(size, GL_TEXTURE_1D);
  }
}



GLuint context::tracking_data::get_active_texture() const noexcept
{
  return m_active_texture;
}



void context::tracking_data::set_active_texture(GLuint unit)
{
  m_active_texture = unit;
  resize_texture_vectors(++unit);
}



uint32_t context::tracking_data::get_bound_texture() const noexcept
{
  return get_bound_texture(m_active_texture);
}



uint32_t context::tracking_data::get_bound_texture(GLuint unit) const noexcept
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



GLenum context::tracking_data::get_bound_texture_target() const noexcept
{
  return get_bound_texture_target(m_active_texture);
}



GLenum context::tracking_data::get_bound_texture_target(GLuint unit) const
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



void context::tracking_data::set_bound_texture(uint32_t uid, GLenum target)
{
  set_bound_texture(uid, m_active_texture, target);
}



void context::tracking_data::set_bound_texture(
  uint32_t uid, GLuint unit, GLenum target)
{
  resize_texture_vectors(unit + 1);
  HOU_DEV_ASSERT(m_bound_textures.size() > unit);
  HOU_DEV_ASSERT(m_bound_texture_targets.size() > unit);
  m_bound_textures[unit] = uid;
  m_bound_texture_targets[unit] = target;
}



uint32_t context::tracking_data::get_bound_vertex_array() const noexcept
{
  return m_bound_vertex_array;
}



void context::tracking_data::set_bound_vertex_array(uint32_t uid) noexcept
{
  m_bound_vertex_array = uid;
}



const recti& context::tracking_data::get_current_viewport() const noexcept
{
  return m_current_viewport;
}



void context::tracking_data::set_current_viewport(const recti& viewport) noexcept
{
  m_current_viewport = viewport;
}

}  // namespace gl

}  // namespace hou
