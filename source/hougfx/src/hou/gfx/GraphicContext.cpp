// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/GraphicContext.hpp"

#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_functions.hpp"

#include "hou/sys/video_mode.hpp"



namespace hou
{

namespace
{

constexpr const char* defaultWindowName = "HouziHiddenWindow";

}  // namespace



void GraphicContext::set_current(GraphicContext& ph_context)
{
  gl::context::set_current(ph_context.gl_context, ph_context.mDefaultWindow);
  if(!ph_context.mInitialized)
  {
    ph_context.initialize();
  }
}



void GraphicContext::unset_current()
{
  gl::context::unset_current();
}



uint GraphicContext::getRenderingColorByteCount()
{
  return 4u;
}



uint GraphicContext::getRenderingDepthByteCount()
{
  return 3u;
}



uint GraphicContext::getRenderingStencilByteCount()
{
  return 1u;
}



GraphicContext::GraphicContext()
  : mExtensionInitializer()
  , mDefaultWindow(defaultWindowName,
      video_mode(vec2u::zero(), getRenderingColorByteCount()),
      window_style::windowed)
  , gl_context(
      gl::context_settings(gl::version(4u, 5u), gl::context_profile::core,
        getRenderingDepthByteCount(), getRenderingStencilByteCount(), 0u),
      mDefaultWindow)
  , mInitialized(false)
{}



GraphicContext::GraphicContext(GraphicContext&& other)
  : mExtensionInitializer()
  , mDefaultWindow(std::move(other.mDefaultWindow))
  , gl_context(std::move(other.gl_context))
  , mInitialized(std::move(other.mInitialized))
{}



bool GraphicContext::is_current() const
{
  return gl_context.is_current();
}



void GraphicContext::initialize()
{
  mInitialized = true;

  // Set texture pack and unpack alignment to 1 so that there is no padding.
  gl::set_unpack_alignment(1);
  gl::set_pack_alignment(1);

  // Multisampled default framebuffer is never used.
  gl::disable_multisampling();

  // Enable alpha blending.
  gl::enable_blending();
  gl::set_blending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



GraphicContext::ExtensionInitializer::ExtensionInitializer()
{
  gl::init_extensions();
}

}  // namespace hou
