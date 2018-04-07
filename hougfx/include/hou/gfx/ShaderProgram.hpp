// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_SHADER_PROGRAM_HPP
#define HOU_GFX_SHADER_PROGRAM_HPP

#include "hou/cor/NonCopyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/CharacterEncodings.hpp"

#include "hou/mth/MatrixFwd.hpp"

#include "hou/gfx/ShaderFwd.hpp"

#include "hou/gl/GlProgramHandle.hpp"

#include <string>



namespace hou
{

class HOU_GFX_API ShaderProgram : public NonCopyable
{
public:
  static void bind(const ShaderProgram& program);
  static void unbind();

public:
  ShaderProgram(const VertexShader& vs, const FragmentShader& fs);
  ShaderProgram(
    const VertexShader& vs, const FragmentShader& fs, const GeometryShader& gs);
  ShaderProgram(ShaderProgram&& other);
  virtual ~ShaderProgram() = 0;

  const gl::ProgramHandle& getHandle() const;
  bool isBound() const;
  uint getUniformLocation(const std::string& uniformName) const;

private:
  ShaderProgram(
    const VertexShader& vs, const FragmentShader& fs, const GeometryShader* gs);

private:
  gl::ProgramHandle mHandle;
};

}  // namespace hou

#endif
