// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/RenderContext.hpp"

#include "hou/gl/GlContextSettings.hpp"
#include "hou/gl/GlTextureHandle.hpp"
#include "hou/gl/GlUtils.hpp"

#include "hou/sys/VideoMode.hpp"



namespace hou
{

void RenderContext::setCurrent(RenderContext& context)
{
  gl::Context::setCurrent(context.mGlContext, context.mDefaultWindow);
}



uint RenderContext::getMaxTextureSampleCount()
{
  return static_cast<uint>(gl::getMaxTextureSamples());
}



uint RenderContext::getMaxTextureSize()
{
  return static_cast<uint>(gl::getMaxTextureSize());
}



uint RenderContext::getTextureUnitCount()
{
  return static_cast<uint>(gl::getMaxTextureImageUnits());
}



uint RenderContext::getRenderingColorBitCount()
{
  return 32u;
}



uint RenderContext::getRenderingDepthBitCount()
{
  return 24u;
}



uint RenderContext::getRenderingStencilBitCount()
{
  return 8u;
}



RenderContext::RenderContext()
  : mExtensionInitializer()
  , mDefaultWindow("HouziWindow", VideoMode(Vec2u(0u, 0u)
    , getRenderingColorBitCount()), WindowStyle::Windowed)
  , mGlContext(gl::ContextSettings(gl::Version(4u, 5u), gl::ContextProfile::Core
    , getRenderingDepthBitCount(), getRenderingStencilBitCount(), 0u)
    , mDefaultWindow)
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

}

