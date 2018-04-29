// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_SHADER_PROGRAM_HPP
#define HOU_GFX_SHADER_PROGRAM_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/character_encodings.hpp"

#include "hou/mth/matrix_fwd.hpp"

#include "hou/gfx/ShaderFwd.hpp"

#include "hou/gl/gl_program_handle.hpp"

#include <string>



namespace hou
{

class HOU_GFX_API ShaderProgram : public non_copyable
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

  const gl::program_handle& getHandle() const;
  bool isBound() const;
  uint getUniformLocation(const std::string& uniformName) const;

private:
  ShaderProgram(
    const VertexShader& vs, const FragmentShader& fs, const GeometryShader* gs);

private:
  gl::program_handle m_handle;
};

}  // namespace hou

#endif
