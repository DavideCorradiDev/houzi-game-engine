// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_OBJECT_HANDLE_HPP
#define HOU_GL_GL_OBJECT_HANDLE_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gl/gl_export.hpp"

#include "hou/gl/open_gl.hpp"

#include "hou/cor/basic_types.hpp"



namespace hou
{

namespace gl
{

class HOU_GL_API object_handle : public non_copyable
{
public:
  object_handle(GLuint name);
  object_handle(object_handle&& other) noexcept;
  virtual ~object_handle() = 0;

  GLuint get_name() const noexcept;
  uint32_t get_uid() const noexcept;

private:
  GLuint m_name;
  uint32_t m_uid;
};



class HOU_GL_API shared_object_handle : public object_handle
{
public:
  shared_object_handle(GLuint name);
  shared_object_handle(shared_object_handle&& other) noexcept;
  virtual ~shared_object_handle() = 0;

  uint32_t get_owning_sharing_group_uid() const noexcept;

private:
  uint32_t m_owning_sharing_group_uid;
};



class HOU_GL_API non_shared_object_handle : public object_handle
{
public:
  non_shared_object_handle(GLuint name);
  non_shared_object_handle(non_shared_object_handle&& other) noexcept;
  virtual ~non_shared_object_handle() = 0;

  uint32_t get_owning_context_uid() const noexcept;

private:
  uint32_t m_owning_context_uid;
};

}  // namespace gl

}  // namespace hou

#endif
