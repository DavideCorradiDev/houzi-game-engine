// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/GlContext.hpp"

#include "hou/cor/error.hpp"
#include "hou/cor/uid_generator.hpp"

#include "hou/sys/window.hpp"



namespace hou
{

namespace gl
{

namespace
{

uint32_t generateUid();



uint32_t generateUid()
{
  static uid_generator uidGenerator(1u);
  return uidGenerator.generate();
}

}  // namespace



void Context::setCurrent(Context& context, window& ph_window)
{
  if(!context.isCurrent() || sCurrentWindowUid != ph_window.get_uid())
  {
    prv::ContextImpl::setCurrent(context.m_impl, ph_window);
    sCurrentContext = &context;
    sCurrentWindowUid = ph_window.get_uid();
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



Context::Context(const ContextSettings& settings, const window& ph_window)
  : Context(settings, ph_window, nullptr)
{}



Context::Context(const ContextSettings& settings, const window& ph_window,
  const Context& sharedContext)
  : Context(settings, ph_window, &sharedContext)
{}



Context::Context(Context&& other)
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



Context::~Context()
{
  if(isCurrent())
  {
    unsetCurrent();
  }
}



uint32_t Context::get_uid() const
{
  return m_uid;
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



Context::Context(const ContextSettings& settings, const window& ph_window,
  const Context* sharedContext)
  : non_copyable()
  , m_impl(settings, ph_window,
      (sharedContext == nullptr) ? nullptr : &(sharedContext->m_impl))
  , m_uid(generateUid())
  , mSharingGroupUid(
      (sharedContext == nullptr) ? m_uid : sharedContext->mSharingGroupUid)
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



uint32_t Context::TrackingData::getBoundFramebuffer(GLenum target) const
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



void Context::TrackingData::setBoundFramebuffer(uint32_t uid, GLenum target)
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



GLenum Context::TrackingData::getBoundTextureTarget() const
{
  return getBoundTextureTarget(mActiveTexture);
}



GLenum Context::TrackingData::getBoundTextureTarget(GLuint unit) const
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



void Context::TrackingData::setBoundTexture(
  uint32_t uid, GLuint unit, GLenum target)
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



const recti& Context::TrackingData::getCurrentViewport() const
{
  return mCurrentViewport;
}



void Context::TrackingData::setCurrentViewport(const recti& viewport)
{
  mCurrentViewport = viewport;
}

}  // namespace gl

}  // namespace hou
