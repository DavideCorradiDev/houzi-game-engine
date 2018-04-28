// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/GraphicContext.hpp"

#include "hou/gl/GlContextSettings.hpp"
#include "hou/gl/GlFunctions.hpp"

#include "hou/sys/VideoMode.hpp"



namespace hou
{

namespace
{

constexpr const char* defaultWindowName = "HouziHiddenWindow";

}  // namespace



void GraphicContext::setCurrent(GraphicContext& context)
{
  gl::Context::setCurrent(context.mGlContext, context.mDefaultWindow);
  if(!context.mInitialized)
  {
    context.initialize();
  }
}



void GraphicContext::unsetCurrent()
{
  gl::Context::unsetCurrent();
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
      VideoMode(vec2u::zero(), getRenderingColorByteCount()),
      WindowStyle::Windowed)
  , mGlContext(
      gl::ContextSettings(gl::Version(4u, 5u), gl::ContextProfile::Core,
        getRenderingDepthByteCount(), getRenderingStencilByteCount(), 0u),
      mDefaultWindow)
  , mInitialized(false)
{}



GraphicContext::GraphicContext(GraphicContext&& other)
  : mExtensionInitializer()
  , mDefaultWindow(std::move(other.mDefaultWindow))
  , mGlContext(std::move(other.mGlContext))
  , mInitialized(std::move(other.mInitialized))
{}



bool GraphicContext::isCurrent() const
{
  return mGlContext.isCurrent();
}



void GraphicContext::initialize()
{
  mInitialized = true;

  // Set texture pack and unpack alignment to 1 so that there is no padding.
  gl::setUnpackAlignment(1);
  gl::setPackAlignment(1);

  // Multisampled default framebuffer is never used.
  gl::disableMultisampling();

  // Enable alpha blending.
  gl::enableBlending();
  gl::setBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



GraphicContext::ExtensionInitializer::ExtensionInitializer()
{
  gl::initExtensions();
}

}  // namespace hou
