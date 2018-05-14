// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_VERTEX_HPP
#define HOU_GFX_TEXT_VERTEX_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/cor/pragmas.hpp"

#include "hou/gl/open_gl.hpp"

#include "hou/mth/matrix.hpp"



namespace hou
{

class vertex_format;

HOU_PRAGMA_PACK_PUSH(1)

/** Represents a vertex used to render text.
 *
 * The vertex contains information about its position and texture coordinates.
 */
class HOU_GFX_API text_vertex
{
public:
  /** Retrieves the vertex_format.
   */
  static const vertex_format& get_vertex_format();

public:
  /** Builds a text_vertex object with all elements set to 0.
   */
  text_vertex() noexcept;

  /** Builds a text_vertex object with the given position and texture
   * coordinates.
   *
   * \param position the vertex position.
   *
   * \param tex_coords the vertex texture coordinates.
   */
  text_vertex(const vec2f& position, const vec3f& tex_coords) noexcept;

  /** Gets the vertex position.
   *
   * \return the vertex position.
   */
  vec2f get_position() const noexcept;

  /** Sets the vertex position.
   *
   * \param pos the vertex position.
   */
  void set_position(const vec2f& pos) noexcept;

  /** Gets the vertex texture coordinates.
   *
   * \return the vertex texture coordinates.
   */
  vec3f get_texture_coordinates() const noexcept;

  /** Sets the vertex texture coordinates.
   *
   * \param tex_coords the vertex texture coordinates.
   */
  void set_texture_coordinates(const vec3f& tex_coords) noexcept;

private:
  static constexpr size_t s_position_size = 2u;
  static constexpr size_t s_texture_coordinates_size = 3u;

private:
  GLfloat m_position[s_position_size];
  GLfloat m_tex_coords[s_texture_coordinates_size];
};

HOU_PRAGMA_PACK_POP()

/** Checks if two text_vertex objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return true if the two objects are equal.
 */
HOU_GFX_API bool operator==(
  const text_vertex& lhs, const text_vertex& rhs) noexcept;

/** Checks if two text_vertex objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return true if the two objects are not equal.
 */
HOU_GFX_API bool operator!=(
  const text_vertex& lhs, const text_vertex& rhs) noexcept;

/** Checks if two text_vertex objects are equal with the specified accuracy.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \param acc the accuracy.
 *
 * \return true if the two objects are equal.
 */
HOU_GFX_API bool close(const text_vertex& lhs, const text_vertex& rhs,
  float acc = std::numeric_limits<float>::epsilon()) noexcept;

/** Writes the object into a stream.
 *
 * \param os the stream.
 *
 * \param v the text_vertex.
 *
 * \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const text_vertex& v);

}  // namespace hou

#endif
