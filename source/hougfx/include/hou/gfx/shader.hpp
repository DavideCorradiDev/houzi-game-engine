// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_SHADER_HPP
#define HOU_GFX_SHADER_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gfx/shader_fwd.hpp"

#include "hou/gfx/gfx_export.hpp"

#include "hou/gl/gl_shader_handle.hpp"

#include <string>



namespace hou
{

/** Represents a generic interface for a shader.
 */
class HOU_GFX_API shader : public non_copyable
{
public:
  /** Creates a shader with the given source code and type.
   *
   * Throws if the source code cannot be compiled.
   *
   * \param source the shader source code.
   *
   * \param type the shader type.
   */
  shader(const std::string& source, shader_type type);

  /** Move constructor.
   *
   * \param other the other shader.
   */
  shader(shader&& other) noexcept;

  /** Destructor.
   */
  virtual ~shader() = 0;

  /** Retrieves the OpenGL shader handle.
   *
   * \return the OpenGL shader handle.
   */
  const gl::shader_handle& get_handle() const;

private:
  gl::shader_handle m_handle;
};



/** Represents a concrete instance of a type of shader.
 *
 * \tparam Type the shader type.
 */
template <shader_type Type>
class HOU_GFX_API shader_t : public shader
{
public:
  /** Creates a shader with the given source code.
   *
   * Throws if the source code cannot be compiled.
   *
   * \param source the shader source code.
   */
  explicit shader_t(const std::string& source);

  /** Move constructor.
   *
   * \param other the other shader.
   */
  shader_t(shader_t&& other) noexcept = default;
};

}  // namespace hou

#endif
