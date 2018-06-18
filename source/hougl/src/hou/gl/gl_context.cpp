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



class context_attributes_scope
{
public:
  context_attributes_scope(const context_settings& cs);
  ~context_attributes_scope();

private:
  void save_context_settings();
  void update_context_settings(const context_settings& cs) const;

private:
  context_settings m_settings_bkp;
};

uint32_t generate_uid();



uint32_t generate_uid()
{
  static uid_generator uid_gen(1u);
  return uid_gen.generate();
}



context_attributes_scope::context_attributes_scope(const context_settings& cs)
  : m_settings_bkp()
{
  save_context_settings();
  update_context_settings(cs);
}



context_attributes_scope::~context_attributes_scope()
{
  update_context_settings(m_settings_bkp);
}



void context_attributes_scope::save_context_settings()
{
  int major_version = 0;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major_version);
  int minor_version = 0;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor_version);
  m_settings_bkp.set_version(gl::version(major_version, minor_version));

  int profile = 0;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);
  switch(profile)
  {
    case 0:
      m_settings_bkp.set_profile(context_profile::any);
      break;
    case SDL_GL_CONTEXT_PROFILE_COMPATIBILITY:
      m_settings_bkp.set_profile(context_profile::compatibility);
      break;
    case SDL_GL_CONTEXT_PROFILE_CORE:
      m_settings_bkp.set_profile(context_profile::core);
      break;
    case SDL_GL_CONTEXT_PROFILE_ES:
      m_settings_bkp.set_profile(context_profile::es);
      break;
    default:
      m_settings_bkp.set_profile(context_profile::any);
      break;
  }

  int red_size = 0;
  SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &red_size);
  int green_size = 0;
  SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &green_size);
  int blue_size = 0;
  SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &blue_size);
  int alpha_size = 0;
  SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &alpha_size);
  m_settings_bkp.set_color_format(
    color_format(red_size, green_size, blue_size, alpha_size));

  int depth_size = 0;
  SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &depth_size);
  m_settings_bkp.set_depth_bit_count(depth_size);

  int stencil_size = 0;
  SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, &stencil_size);
  m_settings_bkp.set_stencil_bit_count(stencil_size);

  int multisample_buffer_count = 0;
  SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &multisample_buffer_count);
  m_settings_bkp.set_multisample_buffer_count(multisample_buffer_count);

  int sample_count = 0;
  SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &sample_count);
  m_settings_bkp.set_sample_count(sample_count);

  int double_buffer = 0;
  SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &double_buffer);
  m_settings_bkp.set_double_buffer(double_buffer);

  int srgb_capable = 0;
  SDL_GL_GetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, &srgb_capable);
  m_settings_bkp.set_srgb_capable(srgb_capable);

  int stereo = 0;
  SDL_GL_GetAttribute(SDL_GL_STEREO, &stereo);
  m_settings_bkp.set_stereo(stereo);

  int share_with_current_context = 0;
  SDL_GL_GetAttribute(
    SDL_GL_SHARE_WITH_CURRENT_CONTEXT, &share_with_current_context);
  m_settings_bkp.set_share_with_current_context(share_with_current_context);

  int ctx_flags = 0;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_FLAGS, &ctx_flags);
  m_settings_bkp.set_debug_mode(ctx_flags & SDL_GL_CONTEXT_DEBUG_FLAG);
  m_settings_bkp.set_forward_compatibility_mode(
    ctx_flags & SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  m_settings_bkp.set_robust_access(
    ctx_flags & SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG);
  m_settings_bkp.set_reset_isolation(
    ctx_flags & SDL_GL_CONTEXT_RESET_ISOLATION_FLAG);
}



void context_attributes_scope::update_context_settings(
  const context_settings& cs) const
{
  SDL_GL_ResetAttributes();

  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_MAJOR_VERSION, cs.get_version().get_major());
  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_MINOR_VERSION, cs.get_version().get_minor());

  int profile = 0;
  switch(cs.get_profile())
  {
    case context_profile::any:
      profile = 0;
      break;
    case context_profile::compatibility:
      profile = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;
      break;
    case context_profile::core:
      profile = SDL_GL_CONTEXT_PROFILE_CORE;
      break;
    case context_profile::es:
      profile = SDL_GL_CONTEXT_PROFILE_ES;
      break;
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profile);

  SDL_GL_SetAttribute(
    SDL_GL_RED_SIZE, cs.get_color_format().get_red_bit_count());
  SDL_GL_SetAttribute(
    SDL_GL_GREEN_SIZE, cs.get_color_format().get_green_bit_count());
  SDL_GL_SetAttribute(
    SDL_GL_BLUE_SIZE, cs.get_color_format().get_blue_bit_count());
  SDL_GL_SetAttribute(
    SDL_GL_ALPHA_SIZE, cs.get_color_format().get_alpha_bit_count());

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, cs.get_depth_bit_count());

  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, cs.get_stencil_bit_count());

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, cs.get_multisample_buffer_count());

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, cs.get_sample_count());

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, cs.double_buffer());

  SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, cs.srgb_capable());

  SDL_GL_SetAttribute(SDL_GL_STEREO, cs.stereo());

  SDL_GL_SetAttribute(
    SDL_GL_SHARE_WITH_CURRENT_CONTEXT, cs.share_with_current_context());

  int ctx_flags = 0;
  if(cs.debug_mode())
  {
    ctx_flags |= SDL_GL_CONTEXT_DEBUG_FLAG;
  }
  if(cs.forward_compatibility_mode())
  {
    ctx_flags |= SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
  }
  if(cs.robust_access())
  {
    ctx_flags |= SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG;
  }
  if(cs.reset_isolation())
  {
    ctx_flags |= SDL_GL_CONTEXT_RESET_ISOLATION_FLAG;
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, ctx_flags);
}

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



context::context(const context_settings& cs, window& wnd)
  : non_copyable()
  , m_impl(nullptr)
  , m_uid(generate_uid())
  , m_sharing_group_uid(m_uid)
  , m_tracking_data()
{
  context_attributes_scope attr_scope(cs);

  m_impl = SDL_GL_CreateContext(wnd.get_impl());
  HOU_CHECK_0(m_impl != nullptr, context_creation_error);

  if(cs.share_with_current_context() && get_current() != nullptr)
  {
    m_sharing_group_uid = get_current()->m_sharing_group_uid;
  }
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
