// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gl/GlContext.hpp"

#include "hou/cor/Error.hpp"
#include "hou/cor/UidGenerator.hpp"

#include "hou/sys/Window.hpp"



namespace hou
{

namespace gl
{

namespace
{

uint32_t generateUid();



uint32_t generateUid()
{
  static UidGenerator uidGenerator(1u);
  return uidGenerator.generate();
}

}



void Context::setCurrent(Context& context, Window& window)
{
  if(!context.isCurrent() || sCurrentWindowUid != window.getUid())
  {
    prv::ContextImpl::setCurrent(context.mImpl, window);
    sCurrentContext = &context;
    sCurrentWindowUid = window.getUid();
  }
}



void Context::unsetCurrent()
{
  if(getCurrent() != nullptr)
  {
    prv::ContextImpl::unsetCurrent();
    sCurrentContext = nullptr;
    sCurrentWindowUid = 0u;
  }
}



Context* Context::getCurrent()
{
  return sCurrentContext;
}



Context::Context(const ContextSettings& settings, const Window& window)
  : Context(settings, window, nullptr)
{}



Context::Context(const ContextSettings& settings, const Window& window
  , const Context& sharedContext)
  : Context(settings, window, &sharedContext)
{}



Context::Context(Context&& other)
  : NonCopyable()
  , mImpl(std::move(other.mImpl))
  , mUid(std::move(other.mUid))
  , mSharingGroupUid(std::move(other.mSharingGroupUid))
  , mTrackingData(std::move(other.mTrackingData))
{
  if(getCurrent() == &other)
  {
    sCurrentContext = this;
  }
}



Context::~Context()
{
  if(isCurrent())
  {
    unsetCurrent();
  }
}



uint32_t Context::getUid() const
{
  return mUid;
}



uint32_t Context::getSharingGroupUid() const
{
  return mSharingGroupUid;
}



bool Context::isCurrent() const
{
  return this == sCurrentContext;
}



thread_local Context* Context::sCurrentContext(nullptr);
thread_local uint32_t Context::sCurrentWindowUid(0u);



Context::Context(const ContextSettings& settings, const Window& window
  , const Context* sharedContext)
  : NonCopyable()
  , mImpl(settings, window, (sharedContext == nullptr) ? nullptr
    : &(sharedContext->mImpl))
  , mUid(generateUid())
  , mSharingGroupUid((sharedContext == nullptr) ? mUid
    : sharedContext->mSharingGroupUid)
  , mTrackingData()
{}



Context::TrackingData::TrackingData()
  : mBoundArrayBuffer(0u)
  , mBoundElementArrayBuffer(0u)
  , mBoundDrawFramebuffer(0u)
  , mBoundReadFramebuffer(0u)
  , mBoundProgram(0u)
  , mBoundVertexArray(0u)
  , mActiveTexture(0u)
  , mBoundTextures(1u, 0u)
  , mBoundTextureTargets(1u, GL_TEXTURE_1D)
  , mCurrentViewport(0, 0, 0, 0)
{}



uint32_t Context::TrackingData::getBoundBuffer(GLenum target) const
{
  switch(target)
  {
    case GL_ARRAY_BUFFER:
      return mBoundArrayBuffer;
    case GL_ELEMENT_ARRAY_BUFFER:
      return mBoundElementArrayBuffer;
    default:
      return 0u;
  }
}



void Context::TrackingData::setBoundBuffer(uint32_t uid, GLenum target)
{
  switch(target)
  {
    case GL_ARRAY_BUFFER:
      mBoundArrayBuffer = uid;
      break;
    case GL_ELEMENT_ARRAY_BUFFER:
      mBoundElementArrayBuffer = uid;
      break;
    default:
      break;
  }
}



uint32_t Context::TrackingData::getBoundFramebuffer
  (GLenum target) const
{
  switch(target)
  {
    case GL_DRAW_FRAMEBUFFER:
      return mBoundDrawFramebuffer;
    case GL_READ_FRAMEBUFFER:
      return mBoundReadFramebuffer;
    default:
      return 0u;
  }
}



void Context::TrackingData::setBoundFramebuffer(uint32_t uid
  , GLenum target)
{
  switch(target)
  {
    case GL_DRAW_FRAMEBUFFER:
      mBoundDrawFramebuffer = uid;
      break;
    case GL_READ_FRAMEBUFFER:
      mBoundReadFramebuffer = uid;
      break;
    default:
      break;
  }
}



uint32_t Context::TrackingData::getBoundProgram() const
{
  return mBoundProgram;
}



void Context::TrackingData::setBoundProgram(uint32_t uid)
{
  mBoundProgram = uid;
}



void Context::TrackingData::resizeTextureVectors(size_t size)
{
  if(mBoundTextures.size() < size)
  {
    mBoundTextures.resize(size, 0u);
    mBoundTextureTargets.resize(size, GL_TEXTURE_1D);
  }
}



GLuint Context::TrackingData::getActiveTexture() const
{
  return mActiveTexture;
}



void Context::TrackingData::setActiveTexture(GLuint unit)
{
  mActiveTexture = unit;
  resizeTextureVectors(++unit);
}



uint32_t Context::TrackingData::getBoundTexture() const
{
  return getBoundTexture(mActiveTexture);
}



uint32_t Context::TrackingData::getBoundTexture(GLuint unit) const
{
  if(mBoundTextures.size() > unit)
  {
    return mBoundTextures[unit];
  }
  else
  {
    return 0u;
  }
}



GLenum  Context::TrackingData::getBoundTextureTarget() const
{
  return getBoundTextureTarget(mActiveTexture);
}



GLenum  Context::TrackingData::getBoundTextureTarget(GLuint unit) const
{
  if(mBoundTextureTargets.size() > unit)
  {
    return mBoundTextureTargets[unit];
  }
  else
  {
    return GL_TEXTURE_1D;
  }
}



void Context::TrackingData::setBoundTexture(uint32_t uid, GLenum target)
{
  setBoundTexture(uid, mActiveTexture, target);
}



void Context::TrackingData::setBoundTexture(uint32_t uid, GLuint unit
  , GLenum target)
{
  resizeTextureVectors(unit + 1);
  HOU_EXPECT_DEV(mBoundTextures.size() > unit);
  HOU_EXPECT_DEV(mBoundTextureTargets.size() > unit);
  mBoundTextures[unit] = uid;
  mBoundTextureTargets[unit] = target;
}



uint32_t Context::TrackingData::getBoundVertexArray() const
{
  return mBoundVertexArray;
}



void Context::TrackingData::setBoundVertexArray(uint32_t uid)
{
  mBoundVertexArray = uid;
}



const Recti& Context::TrackingData::getCurrentViewport() const
{
  return mCurrentViewport;
}



void Context::TrackingData::setCurrentViewport(const Recti& viewport)
{
  mCurrentViewport = viewport;
}

}

}

