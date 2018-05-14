// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_SHADER_PROGRAM_HPP
#define HOU_GFX_SHADER_PROGRAM_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gfx/shader_fwd.hpp"

#include "hou/gfx/gfx_config.hpp"

#include "hou/cor/character_encodings.hpp"

#include "hou/mth/matrix_fwd.hpp"

#include "hou/gl/gl_program_handle.hpp"

#include <string>



namespace hou
{

/** Represents a shader program.
 */
class HOU_GFX_API shader_program : public non_copyable
{
public:
  /** Binds the shader program to the current render context.
   *
   * \param program the shader program.
   */
  static void bind(const shader_program& program);

  /** Unbinds the currently bound shader program from the render context.
   */
  static void unbind();

public:
  /** Creates a shader program with the given vertex and fragment shaders.
   *
   * \param vs the vertex shader.
   * \param fs the fragment shader.
   */
  shader_program(const vertex_shader& vs, const fragment_shader& fs);

  /** Creates a shader program with the given vertex, geometry, and fragment
   * shader.
   *
   * \param vs the vertex shader.
   * \param gs the graphics shader.
   * \param fs the fragment shader.
   */
  shader_program(const vertex_shader& vs, const fragment_shader& fs,
    const geometry_shader& gs);

  /** Move constructor.
   *
   * \param other the other shader_program.
   */
  shader_program(shader_program&& other) noexcept = default;

  /** Destructor.
   */
  virtual ~shader_program() = 0;

  /** Retrieves the OpenGL program handle.
   *
   * \return the OpenGL program handle.
   */
  const gl::program_handle& get_handle() const noexcept;

  /** Checks if this program is currently bound.
   *
   * \return true if this program is currently bound.
   */
  bool is_bound() const;

  /** Retrieves the location of the given uniform.
   *
   * \param uniform_name the uniform name.
   *
   * \throws hou::invalid_uniform_error if no uniform corresponds to
   * uniform_name.
   *
   * \return the uniform location.
   */
  uint get_uniform_location(const std::string& uniform_name) const;

private:
  shader_program(const vertex_shader& vs, const fragment_shader& fs,
    const geometry_shader* gs);

private:
  gl::program_handle m_handle;
};

}  // namespace hou

#endif
