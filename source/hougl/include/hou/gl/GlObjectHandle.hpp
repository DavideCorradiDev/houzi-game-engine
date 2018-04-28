// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_OBJECT_HANDLE_HPP
#define HOU_GL_GL_OBJECT_HANDLE_HPP

#include "hou/gl/GlExport.hpp"
#include "hou/cor/non_copyable.hpp"

#include "hou/gl/OpenGl.hpp"

#include "hou/cor/basic_types.hpp"



namespace hou
{

namespace gl
{

class HOU_GL_API ObjectHandle
  : public non_copyable
{
public:
  ObjectHandle(GLuint name);
  ObjectHandle(ObjectHandle&& other);
  virtual ~ObjectHandle() = 0;

  GLuint getName() const;
  uint32_t getUid() const;

private:
  GLuint mName;
  uint32_t mUid;
};



class HOU_GL_API SharedObjectHandle
  : public ObjectHandle
{
public:
  SharedObjectHandle(GLuint name);
  SharedObjectHandle(SharedObjectHandle&& other);
  virtual ~SharedObjectHandle() = 0;

  uint32_t getOwningSharingGroupUid() const;

private:
  uint32_t mOwningSharingGroupUid;
};



class HOU_GL_API NonSharedObjectHandle
  : public ObjectHandle
{
public:
  NonSharedObjectHandle(GLuint name);
  NonSharedObjectHandle(NonSharedObjectHandle&& other);
  virtual ~NonSharedObjectHandle() = 0;

  uint32_t getOwningContextUid() const;

private:
  uint32_t mOwningContextUid;
};

}

}

#endif

