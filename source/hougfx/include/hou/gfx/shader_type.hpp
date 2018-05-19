// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_SHADER_TYPE_HPP
#define HOU_GFX_SHADER_TYPE_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/** Represents the type of a shader.
 */
enum class shader_type : GLenum
{
  /** Fragment shader. */
  fragment = GL_FRAGMENT_SHADER,
  /** Geometry shader. */
  geometry = GL_GEOMETRY_SHADER,
  /** Vertex shader. */
  vertex = GL_VERTEX_SHADER,
  // compute = GL_COMPUTE_SHADER,
  // tess_control = GL_TESS_CONTROL_SHADER,
  // tess_evaluation = GL_TESS_EVALUATION_SHADER,
};

/** Writes the object into a stream.
 *
 * \param os the stream.
 *
 * \param st the shader_type enum.
 *
 * \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, shader_type st);

}  // namespace hou

#endif
