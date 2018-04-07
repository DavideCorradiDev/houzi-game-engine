// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GL_GL_PROGRAM_HANDLE_HPP
#define HOU_GL_GL_PROGRAM_HANDLE_HPP

#include "hou/gl/GlExport.hpp"
#include "hou/gl/GlObjectHandle.hpp"



namespace hou
{

namespace gl
{

class ShaderHandle;

class HOU_GL_API ProgramHandle
  : public SharedObjectHandle
{
public:
  static ProgramHandle create();

  ProgramHandle(ProgramHandle&& other);
  virtual ~ProgramHandle();

private:
  ProgramHandle(GLuint name);
};

HOU_GL_API void bindProgram(const ProgramHandle& program);
HOU_GL_API void unbindProgram();
HOU_GL_API bool isProgramBound(const ProgramHandle& program);
HOU_GL_API bool isProgramBound();
HOU_GL_API GLuint getBoundProgramName();

HOU_GL_API void attachShader(const ProgramHandle& program
  , const ShaderHandle& shader);
HOU_GL_API void linkProgram(const ProgramHandle& program);

HOU_GL_API GLint getProgramUniformLocation(const ProgramHandle& program
  , const GLchar* name);

HOU_GL_API void setProgramUniformi(const ProgramHandle& program
  , GLint location, GLint v0);
HOU_GL_API void setProgramUniformi(const ProgramHandle& program
  , GLint location, GLint v0, GLint v1);
HOU_GL_API void setProgramUniformi(const ProgramHandle& program
  , GLint location, GLint v0, GLint v1, GLint v3);
HOU_GL_API void setProgramUniformi(const ProgramHandle& program
  , GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
HOU_GL_API void setProgramUniformu(const ProgramHandle& program
  , GLuint location, GLuint v0);
HOU_GL_API void setProgramUniformu(const ProgramHandle& program
  , GLuint location, GLuint v0, GLuint v1);
HOU_GL_API void setProgramUniformu(const ProgramHandle& program
  , GLuint location, GLuint v0, GLuint v1, GLuint v3);
HOU_GL_API void setProgramUniformu(const ProgramHandle& program
  , GLuint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
HOU_GL_API void setProgramUniformf(const ProgramHandle& program
  , GLint location, GLfloat v0);
HOU_GL_API void setProgramUniformf(const ProgramHandle& program
  , GLint location, GLfloat v0, GLfloat v1);
HOU_GL_API void setProgramUniformf(const ProgramHandle& program
  , GLint location, GLfloat v0, GLfloat v1, GLfloat v3);
HOU_GL_API void setProgramUniformf(const ProgramHandle& program
  , GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

HOU_GL_API void setProgramUniformMatrix4f(const ProgramHandle& program
  , GLint location, GLsizei count, GLboolean transpose, const GLfloat* values);

}

}

#endif

