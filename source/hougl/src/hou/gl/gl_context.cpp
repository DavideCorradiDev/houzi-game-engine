// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_context.hpp"

#include "hou/gl/gl_context_exceptions.hpp"

#include "hou/cor/assertions.hpp"

#include "hou/sys/window.hpp"

#include <map>
#include <mutex>

#include "SDL_syswm.h"
#include "SDL_video.h"



namespace hou
{

namespace gl
{

namespace
{

class current_context_guard : public non_copyable
{
public:
  current_context_guard();
  ~current_context_guard();

private:
  SDL_GLContext m_ctx_bkp;
  SDL_Window* m_wnd_bkp;
};



class context_attributes_guard : public non_copyable
{
public:
  context_attributes_guard(const context_settings& cs, bool share_lists);
  ~context_attributes_guard();

private:
  void save_context_settings();
  void update_context_settings(const context_settings& cs) const;

private:
  context_settings m_settings_bkp;
  int m_share_bkp;
};



uint32_t generate_uid();

SDL_GLContext create_context(const context_settings& cs, const SDL_Window* wnd);

SDL_GLContext create_context_ext(const context_settings& cs,
  const SDL_Window* wnd, const void* sharing_ctx);

std::map<const context::impl_type*, context*>& get_context_registry();

std::mutex& get_context_registry_mutex();



current_context_guard::current_context_guard()
  : m_ctx_bkp(SDL_GL_GetCurrentContext())
  , m_wnd_bkp(SDL_GL_GetCurrentWindow())
{}



current_context_guard::~current_context_guard()
{
  HOU_CHECK_N(SDL_GL_MakeCurrent(m_wnd_bkp, m_ctx_bkp) == 0,
    context_switch_error, SDL_GetError());
}



context_attributes_guard::context_attributes_guard(
  const context_settings& cs, bool share)
  : m_settings_bkp()
  , m_share_bkp(0)
{
  save_context_settings();
  update_context_settings(cs);

  SDL_GL_GetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, &m_share_bkp);
  SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, share ? 1 : 0);
}



context_attributes_guard::~context_attributes_guard()
{
  SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, m_share_bkp);

  update_context_settings(m_settings_bkp);
}



void context_attributes_guard::save_context_settings()
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



void context_attributes_guard::update_context_settings(
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
  SDL_GL_SetAttribute(
    SDL_GL_BUFFER_SIZE, cs.get_color_format().get_bit_count());

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, cs.get_depth_bit_count());

  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, cs.get_stencil_bit_count());

  SDL_GL_SetAttribute(
    SDL_GL_MULTISAMPLEBUFFERS, cs.get_multisample_buffer_count());

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, cs.get_sample_count());

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, cs.double_buffer());

  SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, cs.srgb_capable());

  SDL_GL_SetAttribute(SDL_GL_STEREO, cs.stereo());

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



uint32_t generate_uid()
{
  static uid_generator uid_gen(1u);
  return uid_gen.generate();
}



SDL_GLContext create_context(const context_settings& cs, const SDL_Window* wnd)
{
  // Note: contexts must alwasy be created with the share list parameter.
  // This enable contexts created in the future to share lists with them.
  static constexpr bool share_lists = true;
  context_attributes_guard attr_scope(cs, share_lists);
  SDL_GLContext ctx = SDL_GL_CreateContext(
    const_cast<window::impl_type*>(const_cast<SDL_Window*>(wnd)));
  HOU_CHECK_N(ctx != nullptr, context_creation_error, SDL_GetError());
  HOU_CHECK_N(SDL_GL_MakeCurrent(const_cast<SDL_Window*>(wnd), ctx) == 0,
    context_switch_error, SDL_GetError());
  HOU_CHECK_N(gladLoadGLLoader(SDL_GL_GetProcAddress) != 0,
    context_creation_error, SDL_GetError());

  return ctx;
}



SDL_GLContext create_context_ext(const context_settings& cs,
  const SDL_Window* wnd, const void* sharing_ctx)
{
  // The current context will be changed while constructing the new context.
  // Make sure that after the constructor has been called, the originally
  // current context will be restored.
  current_context_guard ctx_guard;

  // Dummy temp window for the sharing or temp context.
  window tmp_wnd("ExtensionInitializationWindow", vec2u(1u, 1u));
  if(sharing_ctx == nullptr)
  {
    // If no sharing ctx is specified, create a temporary dummy one with
    // basic gl settings to make sure extensions are properly initialized when
    // creating the new context.
    // If a sharing ctx has been specified, the extensions have already been
    // initialized for it.
    sharing_ctx
      = create_context(context_settings::get_basic(), tmp_wnd.get_impl());
  }
  // Make sharing_ctx current, so that the newly created context will share lists
  // with it.
  // If no sharing_ctx was provided, a temp one has been created, meaning that
  // the new context will share lists with it which ends up having no tangible
  // effect.
  HOU_CHECK_N(
    SDL_GL_MakeCurrent(tmp_wnd.get_impl(), const_cast<void*>(sharing_ctx)) == 0,
    context_switch_error, SDL_GetError());
  HOU_ASSERT(sharing_ctx == SDL_GL_GetCurrentContext());

  // Create the actual context.
  return create_context(cs, wnd);
}



std::map<const context::impl_type*, context*>& get_context_registry()
{
  static std::map<const context::impl_type*, context*> context_registry;
  return context_registry;
}



std::mutex& get_context_registry_mutex()
{
  static std::mutex context_registry_mutex;
  return context_registry_mutex;
}

}  // namespace



context& context::get_from_impl(not_null<const impl_type*> impl)
{
  std::lock_guard<std::mutex> lock(get_context_registry_mutex());
  auto it = get_context_registry().find(impl.get());
  HOU_POSTCOND(it != get_context_registry().end() && it->second != nullptr);
  return *(it->second);
}



void context::set_current(context& ctx, window& wnd)
{
  if(!ctx.is_current() || &wnd != get_current_window())
  {
    HOU_CHECK_N(SDL_GL_MakeCurrent(wnd.get_impl(), ctx.get_impl()) == 0,
      context_switch_error, SDL_GetError());
  }
}



void context::unset_current()
{
  if(get_current() != nullptr)
  {
    HOU_CHECK_N(SDL_GL_MakeCurrent(nullptr, nullptr) == 0, context_switch_error,
      SDL_GetError());
  }
}



context* context::get_current()
{
  impl_type* ctx_impl = SDL_GL_GetCurrentContext();
  return ctx_impl == nullptr ? nullptr : &get_from_impl(ctx_impl);
}



window* context::get_current_window()
{
  window::impl_type* wnd_impl = SDL_GL_GetCurrentWindow();
  return wnd_impl == nullptr ? nullptr : &window::get_from_impl(wnd_impl);
}



context::context(const context_settings& cs, const window& wnd)
  : context(cs, wnd, nullptr)
{}



context::context(
  const context_settings& cs, const window& wnd, const context& sharing_ctx)
  : context(cs, wnd, &sharing_ctx)
{}



context::context(
  const context_settings& cs, const window& wnd, const context* sharing_ctx)
  : non_copyable()
  , m_impl(create_context_ext(cs, wnd.get_impl(),
      sharing_ctx == nullptr ? nullptr : sharing_ctx->get_impl()))
  , m_uid(generate_uid())
  , m_sharing_group_uid(
      sharing_ctx == nullptr ? m_uid : sharing_ctx->m_sharing_group_uid)
  , m_tracking_data()
  , m_settings(cs)
{
  std::lock_guard<std::mutex> lock(get_context_registry_mutex());
  get_context_registry().insert(std::make_pair(m_impl, this));
}



context::context(context&& other) noexcept
  : non_copyable()
  , m_impl(std::move(other.m_impl))
  , m_uid(std::move(other.m_uid))
  , m_sharing_group_uid(std::move(other.m_sharing_group_uid))
  , m_tracking_data(std::move(other.m_tracking_data))
  , m_settings(std::move(other.m_settings))
{
  other.m_impl = nullptr;
  other.m_uid = 0u;

  std::lock_guard<std::mutex> lock(get_context_registry_mutex());
  get_context_registry().at(m_impl) = this;
}



context::~context()
{
  if(m_impl != nullptr)
  {
    SDL_GL_DeleteContext(m_impl);
    std::lock_guard<std::mutex> lock(get_context_registry_mutex());
    get_context_registry().erase(m_impl);
  }
}



const context::impl_type* context::get_impl() const noexcept
{
  return m_impl;
}



context::impl_type* context::get_impl() noexcept
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
  return m_impl == SDL_GL_GetCurrentContext();
}



const context_settings& context::get_settings() const noexcept
{
  return m_settings;
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
  , m_bound_texture_targets(1u, 0)
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
    m_bound_texture_targets.resize(size, 0);
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
    return 0;
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
  HOU_ASSERT(m_bound_textures.size() > unit);
  HOU_ASSERT(m_bound_texture_targets.size() > unit);
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



void context::tracking_data::set_current_viewport(
  const recti& viewport) noexcept
{
  m_current_viewport = viewport;
}

}  // namespace gl

}  // namespace hou
