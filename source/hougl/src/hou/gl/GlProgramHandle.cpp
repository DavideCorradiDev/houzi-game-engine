// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/GlProgramHandle.hpp"

#include "hou/gl/GlCheck.hpp"
#include "hou/gl/GlContext.hpp"
#include "hou/gl/GlError.hpp"
#include "hou/gl/GlShaderHandle.hpp"

#include "hou/cor/Error.hpp"
#include "hou/cor/character_encodings.hpp"



namespace hou
{

namespace gl
{

ProgramHandle ProgramHandle::create()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name = glCreateProgram();
  HOU_GL_CHECK_ERROR();
  return ProgramHandle(name);
}



ProgramHandle::ProgramHandle(ProgramHandle&& other)
  : SharedObjectHandle(std::move(other))
{}



ProgramHandle::~ProgramHandle()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(*this);
  glDeleteProgram(getName());
  HOU_GL_CHECK_ERROR();
}



ProgramHandle::ProgramHandle(GLuint name)
  : SharedObjectHandle(name)
{}



void bindProgram(const ProgramHandle& program)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  if(!isProgramBound(program))
  {
    glUseProgram(program.getName());
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundProgram(program.getUid());
  }
}



void unbindProgram()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(isProgramBound())
  {
    glUseProgram(0u);
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundProgram(0u);
  }
}



bool isProgramBound(const ProgramHandle& program)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  return Context::getCurrent()->mTrackingData.getBoundProgram()
    == program.getUid();
}



bool isProgramBound()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return Context::getCurrent()->mTrackingData.getBoundProgram() != 0u;
}



GLuint getBoundProgramName()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLint name;
  glGetIntegerv(GL_CURRENT_PROGRAM, &name);
  HOU_GL_CHECK_ERROR();
  return static_cast<GLuint>(name);
}



void attachShader(const ProgramHandle& program, const ShaderHandle& shader)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glAttachShader(program.getName(), shader.getName());
  HOU_GL_CHECK_ERROR();
}



void linkProgram(const ProgramHandle& program)
{
  static constexpr size_t maxInfoLogSize = 1024;

  HOU_GL_CHECK_CONTEXT_EXISTENCE();

  glLinkProgram(program.getName());
  HOU_GL_CHECK_ERROR();

  GLint success = 0;
  glGetProgramiv(program.getName(), GL_LINK_STATUS, &success);
  HOU_GL_CHECK_ERROR();
  if(success == 0)
  {
    GLchar infoLog[maxInfoLogSize];
    glGetProgramInfoLog(program.getName(), maxInfoLogSize, nullptr, infoLog);
    HOU_GL_CHECK_ERROR();
    HOU_RUNTIME_ERROR(getText(GlError::ProgramLinking), infoLog);
  }
}



GLint getProgramUniformLocation(const ProgramHandle& program
  , const GLchar* name)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  GLint location = glGetUniformLocation(program.getName(), name);
  HOU_GL_CHECK_ERROR();
  HOU_RUNTIME_CHECK(location != -1, getText(GlError::ProgramInvalidUniform)
    , name);
  return location;
}



void setProgramUniformi(const ProgramHandle& program, GLint location
  , GLint v0)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform1i(program.getName(), location, v0);
  HOU_GL_CHECK_ERROR();
}



void setProgramUniformi(const ProgramHandle& program, GLint location
  , GLint v0, GLint v1)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform2i(program.getName(), location, v0, v1);
  HOU_GL_CHECK_ERROR();
}



void setProgramUniformi(const ProgramHandle& program, GLint location
  , GLint v0, GLint v1, GLint v2)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform3i(program.getName(), location, v0, v1, v2);
  HOU_GL_CHECK_ERROR();
}



void setProgramUniformi(const ProgramHandle& program, GLint location
  , GLint v0, GLint v1, GLint v2, GLint v3)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform4i(program.getName(), location, v0, v1, v2, v3);
  HOU_GL_CHECK_ERROR();
}



void setProgramUniformu(const ProgramHandle& program, GLuint location
  , GLuint v0)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform1ui(program.getName(), location, v0);
  HOU_GL_CHECK_ERROR();
}



void setProgramUniformu(const ProgramHandle& program, GLuint location
  , GLuint v0, GLuint v1)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform2ui(program.getName(), location, v0, v1);
  HOU_GL_CHECK_ERROR();
}



void setProgramUniformu(const ProgramHandle& program, GLuint location
  , GLuint v0, GLuint v1, GLuint v2)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform3ui(program.getName(), location, v0, v1, v2);
  HOU_GL_CHECK_ERROR();
}



void setProgramUniformu(const ProgramHandle& program, GLuint location
  , GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform4ui(program.getName(), location, v0, v1, v2, v3);
  HOU_GL_CHECK_ERROR();
}



void setProgramUniformf(const ProgramHandle& program, GLint location
  , GLfloat v0)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform1f(program.getName(), location, v0);
  HOU_GL_CHECK_ERROR();
}



void setProgramUniformf(const ProgramHandle& program, GLint location
  , GLfloat v0, GLfloat v1)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform2f(program.getName(), location, v0, v1);
  HOU_GL_CHECK_ERROR();
}



void setProgramUniformf(const ProgramHandle& program, GLint location
  , GLfloat v0, GLfloat v1, GLfloat v2)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform3f(program.getName(), location, v0, v1, v2);
  HOU_GL_CHECK_ERROR();
}



void setProgramUniformf(const ProgramHandle& program, GLint location
  , GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform4f(program.getName(), location, v0, v1, v2, v3);
  HOU_GL_CHECK_ERROR();
}



void setProgramUniformMatrix4f(const ProgramHandle& program, GLint location
  , GLsizei count, GLboolean transpose, const GLfloat* values)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniformMatrix4fv(program.getName(), location, count, transpose
    , values);
  HOU_GL_CHECK_ERROR();
}


}

}

