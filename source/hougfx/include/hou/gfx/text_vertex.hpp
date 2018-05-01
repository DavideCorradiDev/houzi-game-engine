// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_VERTEX_HPP
#define HOU_GFX_TEXT_VERTEX_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/pragmas.hpp"

#include "hou/mth/matrix.hpp"

#include "hou/gfx/mesh.hpp"



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
  /** Type to be used as accuracy in close comparison checks for mesh.
   */
  using comparison_type = float;

public:
  /** Retrieves the vertex_format.
   */
  static const vertex_format& get_vertex_format();

public:
  /** Builds a text_vertex object with all elements set to 0.
   */
  text_vertex();

  /** Builds a text_vertex object with the given position and texture
   * coordinates.
   *
   * \param position the vertex position.
   *
   * \param tex_coords the vertex texture coordinates.
   */
  text_vertex(const vec2f& position, const vec3f& tex_coords);

  /** Gets the vertex position.
   *
   * \return the vertex position.
   */
  vec2f get_position() const;

  /** Sets the vertex position.
   *
   * \param pos the vertex position.
   */
  void set_position(const vec2f& pos);

  /** Gets the vertex texture coordinates.
   *
   * \return the vertex texture coordinates.
   */
  vec3f get_texture_coordinates() const;

  /** Sets the vertex texture coordinates.
   *
   * \param tex_coords the vertex texture coordinates.
   */
  void set_texture_coordinates(const vec3f& tex_coords);

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
HOU_GFX_API bool operator==(const text_vertex& lhs, const text_vertex& rhs);

/** Checks if two text_vertex objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return true if the two objects are not equal.
 */
HOU_GFX_API bool operator!=(const text_vertex& lhs, const text_vertex& rhs);

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
  text_vertex::comparison_type acc
  = std::numeric_limits<text_vertex::comparison_type>::epsilon());

/** Writes the object into a stream.
 *
 * \param os the stream.
 *
 * \param v the text_vertex.
 *
 * \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const text_vertex& v);

/** mesh text_vertex.
 *
 * Used to represent renderable text blocks.
 */
using text_mesh = mesh_t<text_vertex>;

}  // namespace hou

#endif
