// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_OBJECT_HANDLE_HPP
#define HOU_GL_GL_OBJECT_HANDLE_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/open_gl.hpp"

#include "hou/gl/gl_config.hpp"



namespace hou
{

namespace gl
{

class HOU_GL_API object_handle : public non_copyable
{
public:
  using uid_type = uint32_t;

public:
  object_handle(GLuint name) noexcept;

  object_handle(object_handle&& other) noexcept;

  virtual ~object_handle() = 0;

  GLuint get_name() const noexcept;

  uid_type get_uid() const noexcept;

private:
  GLuint m_name;
  uid_type m_uid;
};



class HOU_GL_API shared_object_handle : public object_handle
{
public:
  shared_object_handle(GLuint name);

  context::uid_type get_owning_sharing_group_uid() const noexcept;

private:
  context::uid_type m_owning_sharing_group_uid;
};



class HOU_GL_API non_shared_object_handle : public object_handle
{
public:
  non_shared_object_handle(GLuint name);

  context::uid_type get_owning_context_uid() const noexcept;

private:
  context::uid_type m_owning_context_uid;
};

}  // namespace gl

}  // namespace hou

#endif
