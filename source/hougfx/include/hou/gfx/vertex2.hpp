// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTEX_2_HPP
#define HOU_GFX_VERTEX_2_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/pragmas.hpp"

#include "hou/gl/open_gl.hpp"

#include "hou/gfx/vertex2_fwd.hpp"

#include "hou/sys/color.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/rectangle_fwd.hpp"



namespace hou
{

class vertex_format;

HOU_PRAGMA_PACK_PUSH(1)

/** Represents a ph_vertex in 2d space.
 *
 *  The ph_vertex contains information about its position, ph_texture coordinates,
 *  and ph_color.
 */
class HOU_GFX_API vertex2
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
  /** Builds a vertex2 object with all elements set to 0.
   */
  vertex2();

  /** Builds a vertex2 object with the given position, ph_texture coordinates,
   *  and ph_color.
   *
   *  \param position the ph_vertex position.
   *  \param textureCoordinates the ph_vertex ph_texture coordinates.
   *  \param ph_color the ph_vertex ph_color.
   */
  vertex2(
    const vec2f& position, const vec2f& textureCoordinates, const color& ph_color);

  /** Gets the ph_vertex position.
   *
   *  \return the ph_vertex position.
   */
  vec2f get_position() const;

  /** Sets the ph_vertex position.
   *
   *  \param pos the ph_vertex position.
   */
  void set_position(const vec2f& pos);

  /** Gets the ph_vertex ph_texture coordinates.
   *
   *  \return the ph_vertex ph_texture coordinates.
   */
  vec2f get_texture_coordinates() const;

  /** Sets the ph_vertex ph_texture coordinates.
   *
   *  \param textureCoordinates the ph_vertex ph_texture coordinates.
   */
  void set_texture_coordinates(const vec2f& textureCoordinates);

  /** Gets the ph_vertex ph_color.
   *
   *  \return the ph_vertex ph_color.
   */
  color get_color() const;

  /** Sets the ph_vertex ph_color.
   *
   *  \param ph_color the ph_vertex ph_color.
   */
  void set_color(const color& ph_color);

private:
  static constexpr size_t s_position_size = 2u;
  static constexpr size_t s_texture_coordinates_size = 2u;
  static constexpr size_t sColorSize = 4u;

private:
  GLfloat m_position[s_position_size];
  GLfloat m_tex_coords[s_texture_coordinates_size];
  GLfloat m_color[sColorSize];
};

HOU_PRAGMA_PACK_POP()

/** Checks if two vertex2 objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are equal.
 */
HOU_GFX_API bool operator==(const vertex2& lhs, const vertex2& rhs);

/** Checks if two vertex2 objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are not equal.
 */
HOU_GFX_API bool operator!=(const vertex2& lhs, const vertex2& rhs);

/** Checks if two vertex2 objects are equal with the specified accuracy.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \param acc the accuracy.
 *  \return true if the two objects are equal.
 */
HOU_GFX_API bool close(const vertex2& lhs, const vertex2& rhs,
  vertex2::comparison_type acc
  = std::numeric_limits<vertex2::comparison_type>::epsilon());

/** Writes the object into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param v the vertex2.
 *  \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const vertex2& v);

/** Creates a mesh object representing a ph_rectangle shape with the given size.
 *
 *  The ph_texture coordinates are defined so that a ph_texture is stretched to cover
 *  the entire ph_rectangle.
 *  The ph_color is always white.
 *
 *  \param size the size of the ph_rectangle.
 *  \return the mesh representing the ph_rectangle.
 */
HOU_GFX_API mesh2 create_rectangle_mesh2(const vec2f& size);

/** Creates a mesh2 object representing a ph_rectangle outline shape with the
 *  given size and border thickness.
 *
 *  The ph_texture coordinates are always equal to zero.
 *  The ph_color is always white.
 *  The size refers to the outside of the border.
 *
 *  \param size the size of the ph_rectangle.
 *  \param thickness the thickness of the border of the ph_rectangle.
 *  \return the mesh2 representing the ph_rectangle outline.
 */
HOU_GFX_API mesh2 create_rectangle_outline_mesh2(
  const vec2f& size, float thickness);

/** Creates a mesh2 object representing an approximation of an ellipse with
 *  the given size and drawn with the given number of points.
 *
 *  The ph_texture coordinates are always equal to zero.
 *  The ph_color is always white.
 *  The actual ph_vertex count is equal to pointCount plus 2, as the center of
 *  the ellipse is also defined as a ph_vertex and one ph_vertex has to be repeated
 *  twice to close the shape.
 *
 *  \param size the size of the ellipse.
 *  \param pointCount the number of pointCount used to draw the ellipse.
 *  \return the mesh2 representing the ellipse.
 */
HOU_GFX_API mesh2 create_ellipse_mesh2(const vec2f& size, uint pointCount);


/** Creates a mesh2 object representing an approximation of an ellipse outline
 *  with the given size and drawn with the given number of points.
 *
 *  The ph_texture coordinates are always equal to zero.
 *  The ph_color is always white.
 *  The number of points refers to the number of points used to draw the outer
 *  and inner perimiter of the outline each.
 *  The size refers to the outside of the border.
 *
 *  The actual ph_vertex count is equal to double pointCount plus 2, as the center
 *  of the ellipse is also defined as a ph_vertex and one ph_vertex has to be repeated
 *  twice to close the shape.
 *
 *  \param size the size of the ellipse.
 *  \param pointCount the number of pointCount used to draw the ellipse.
 *  \param thickness the thicknes of the outline.
 *  \return the mesh2 representing the ellipse outline.
 */
HOU_GFX_API mesh2 create_ellipse_outline_mesh2(
  const vec2f& size, uint pointCount, float thickness);

/** Creates a mesh2 object representing a ph_texture quad covering the specified
 *  ph_rectangle of a ph_texture.
 *
 *  a ph_texture quad has a rectangular shape with the top left corner at the
 * origin and the size specified by rect, just like a normal ph_rectangle ph_mesh.
 *  Unlike the ph_rectangle ph_mesh, the ph_texture coordinates are defined to coincide
 *  with the elements of rect, normalized by the actual ph_texture size.
 *  The same ph_texture quad may be used with different textures with the same
 * size. If a ph_texture quad is used with a ph_texture of a different size than the
 * one it was defined with, it will work, but the section of ph_texture shown will
 * not correspond to the values of rect anymore. The ph_color is always white.
 *
 *  \param rect the part of the ph_texture to be shown.
 *  \param textureSize the size of the ph_texture to be used with the quad.
 */
HOU_GFX_API mesh2 create_texture_quad_mesh2(
  const rectf& rect, const vec2f& textureSize);

}  // namespace hou

#endif
