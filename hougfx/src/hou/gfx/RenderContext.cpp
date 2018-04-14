// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/RenderContext.hpp"

#include "hou/gl/GlContextSettings.hpp"
#include "hou/gl/GlUtils.hpp"

#include "hou/sys/VideoMode.hpp"



namespace hou
{

namespace
{

constexpr uint bitsPerByte = 8u;
constexpr char* defaultWindowName = "HouziHiddenWindow";

}



void RenderContext::setCurrent(RenderContext& context)
{
  gl::Context::setCurrent(context.mGlContext, context.mDefaultWindow);
}



void RenderContext::unsetCurrent(RenderContext& context)
{
  gl::Context::unsetCurrent();
}



uint RenderContext::getRenderingColorByteCount()
{
  return 4u;
}



uint RenderContext::getRenderingDepthByteCount()
{
  return 3u;
}



uint RenderContext::getRenderingStencilByteCount()
{
  return 1u;
}



RenderContext::RenderContext()
  : mExtensionInitializer()
  , mDefaultWindow(defaultWindowName,
      VideoMode(Vec2u::zero(), getRenderingColorByteCount() * bitsPerByte),
      WindowStyle::Windowed)
  , mGlContext(
      gl::ContextSettings(gl::Version(4u, 5u), gl::ContextProfile::Core,
        getRenderingDepthByteCount() * bitsPerByte,
        getRenderingStencilByteCount() * bitsPerByte, 0u),
      mDefaultWindow)
{
  setCurrent(*this);

  gl::setUnpackAlignment(1);
  gl::setPackAlignment(1);

  // Multisampled default framebuffer is never used.
  gl::disableMultisampling();

  gl::enableBlending();
  gl::setBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



RenderContext::RenderContext(RenderContext&& other)
  : mExtensionInitializer()
  , mDefaultWindow(std::move(other.mDefaultWindow))
  , mGlContext(std::move(other.mGlContext))
{}



bool RenderContext::isCurrent() const
{
  return mGlContext.isCurrent();
}



RenderContext::ExtensionInitializer::ExtensionInitializer()
{
  gl::initExtensions();
}

}  // namespace hou
