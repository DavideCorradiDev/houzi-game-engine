// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/GlObjectHandle.hpp"

#include "hou/gl/GlCheck.hpp"
#include "hou/gl/GlContext.hpp"

#include "hou/cor/UidGenerator.hpp"



namespace hou
{

namespace gl
{

namespace
{

uint32_t generateUid();



uint32_t generateUid()
{
  static UidGenerator gen(1u);
  return gen.generate();
}

}



ObjectHandle::ObjectHandle(GLuint name)
  : NonCopyable()
  , mName(name)
  , mUid(generateUid())
{}



ObjectHandle::ObjectHandle(ObjectHandle&& other)
  : NonCopyable()
  , mName(other.mName)
  , mUid(other.mUid)
{
  other.mName = 0u;
  other.mUid = 0u;
}



ObjectHandle::~ObjectHandle()
{}



GLuint ObjectHandle::getName() const
{
  return mName;
}



uint32_t ObjectHandle::getUid() const
{
  return mUid;
}



SharedObjectHandle::SharedObjectHandle(GLuint name)
  : ObjectHandle(name)
  , mOwningSharingGroupUid(0u)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  mOwningSharingGroupUid = Context::getCurrent()->getSharingGroupUid();
}



SharedObjectHandle::SharedObjectHandle(SharedObjectHandle&& other)
  : ObjectHandle(std::move(other))
  , mOwningSharingGroupUid(other.mOwningSharingGroupUid)
{}



SharedObjectHandle::~SharedObjectHandle()
{}



uint32_t SharedObjectHandle::getOwningSharingGroupUid() const
{
  return mOwningSharingGroupUid;
}



NonSharedObjectHandle::NonSharedObjectHandle(GLuint name)
  : ObjectHandle(name)
  , mOwningContextUid(0u)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  mOwningContextUid = Context::getCurrent()->getUid();
}



NonSharedObjectHandle::NonSharedObjectHandle(NonSharedObjectHandle&& other)
  : ObjectHandle(std::move(other))
  , mOwningContextUid(other.mOwningContextUid)
{}



NonSharedObjectHandle::~NonSharedObjectHandle()
{}



uint32_t NonSharedObjectHandle::getOwningContextUid() const
{
  return mOwningContextUid;
}

}

}

