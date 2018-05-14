// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTEX_2_HPP
#define HOU_GFX_VERTEX_2_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/cor/pragmas.hpp"

#include "hou/gl/open_gl.hpp"

#include "hou/mth/matrix.hpp"

#include "hou/sys/color.hpp"



namespace hou
{

class vertex_format;

HOU_PRAGMA_PACK_PUSH(1)

/** Represents a vertex in 2d space.
 *
 * The vertex contains information about its position, texture coordinates,
 * and color.
 */
class HOU_GFX_API vertex2
{
public:
  /** Retrieves the vertex_format.
   */
  static const vertex_format& get_vertex_format();

public:
  /** Builds a vertex2 object with all elements set to 0.
   */
  vertex2() noexcept;

  /** Builds a vertex2 object with the given position, texture coordinates,
   * and color.
   *
   * \param position the vertex position.
   *
   * \param tex_coords the vertex texture coordinates.
   *
   * \param color the vertex color.
   */
  vertex2(const vec2f& position, const vec2f& tex_coords,
    const color& color) noexcept;

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
  vec2f get_texture_coordinates() const noexcept;
  /** Sets the vertex texture coordinates.
   *
   * \param tex_coords the vertex texture coordinates.
   */
  void set_texture_coordinates(const vec2f& tex_coords) noexcept;

  /** Gets the vertex color.
   *
   * \return the vertex color.
   */
  color get_color() const noexcept;

  /** Sets the vertex color.
   *
   * \param color the vertex color.
   */
  void set_color(const color& color) noexcept;

private:
  static constexpr size_t s_position_size = 2u;
  static constexpr size_t s_texture_coordinates_size = 2u;
  static constexpr size_t s_color_size = 4u;

private:
  GLfloat m_position[s_position_size];
  GLfloat m_tex_coords[s_texture_coordinates_size];
  GLfloat m_color[s_color_size];
};

HOU_PRAGMA_PACK_POP()

/** Checks if two vertex2 objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return true if the two objects are equal.
 */
HOU_GFX_API bool operator==(const vertex2& lhs, const vertex2& rhs) noexcept;

/** Checks if two vertex2 objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return true if the two objects are not equal.
 */
HOU_GFX_API bool operator!=(const vertex2& lhs, const vertex2& rhs) noexcept;

/** Checks if two vertex2 objects are equal with the specified accuracy.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \param acc the accuracy.
 *
 * \return true if the two objects are equal.
 */
HOU_GFX_API bool close(const vertex2& lhs, const vertex2& rhs,
  float acc = std::numeric_limits<float>::epsilon()) noexcept;

/** Writes the object into a stream.
 *
 * \param os the stream.
 *
 * \param v the vertex2.
 *
 * \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const vertex2& v);

}  // namespace hou

#endif
