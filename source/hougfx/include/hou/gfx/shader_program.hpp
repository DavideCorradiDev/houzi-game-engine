// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_SHADER_PROGRAM_HPP
#define HOU_GFX_SHADER_PROGRAM_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/gfx_export.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/character_encodings.hpp"

#include "hou/mth/matrix_fwd.hpp"

#include "hou/gfx/shader_fwd.hpp"

#include "hou/gl/gl_program_handle.hpp"

#include <string>



namespace hou
{

class HOU_GFX_API shader_program : public non_copyable
{
public:
  static void bind(const shader_program& program);
  static void unbind();

public:
  shader_program(const vertex_shader& vs, const fragment_shader& fs);
  shader_program(
    const vertex_shader& vs, const fragment_shader& fs, const geometry_shader& gs);
  shader_program(shader_program&& other);
  virtual ~shader_program() = 0;

  const gl::program_handle& get_handle() const;
  bool is_bound() const;
  uint get_uniform_location(const std::string& uniformName) const;

private:
  shader_program(
    const vertex_shader& vs, const fragment_shader& fs, const geometry_shader* gs);

private:
  gl::program_handle m_handle;
};

}  // namespace hou

#endif
