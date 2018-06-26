// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_SHADER_HANDLE_HPP
#define HOU_GL_GL_SHADER_HANDLE_HPP

#include "hou/gl/gl_object_handle.hpp"

#include "hou/gl/gl_config.hpp"



namespace hou
{

namespace gl
{

class HOU_GL_API shader_handle : public shared_object_handle
{
public:
  static shader_handle create(GLenum type);

public:
  shader_handle(shader_handle&& other) noexcept = default;
  virtual ~shader_handle();

  GLenum get_type() const noexcept;

private:
  shader_handle(GLuint name, GLenum type);

private:
  GLenum m_type;
};

HOU_GL_API void compile_shader(const shader_handle& shd, const GLchar* src);

}  // namespace gl

}  // namespace hou

#endif
