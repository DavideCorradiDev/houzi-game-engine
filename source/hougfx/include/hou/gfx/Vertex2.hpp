// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTEX_2_HPP
#define HOU_GFX_VERTEX_2_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/pragmas.hpp"

#include "hou/gl/OpenGL.hpp"

#include "hou/gfx/Vertex2Fwd.hpp"

#include "hou/sys/color.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/rectangle_fwd.hpp"



namespace hou
{

class VertexFormat;

HOU_PRAGMA_PACK_PUSH(1)

/** Represents a vertex in 2d space.
 *
 *  The vertex contains information about its position, texture coordinates,
 *  and ph_color.
 */
class HOU_GFX_API Vertex2
{
public:
  /** Type to be used as accuracy in close comparison checks for Mesh.
   */
  using ComparisonType = float;

public:
  /** Retrieves the VertexFormat.
   */
  static const VertexFormat& getVertexFormat();

public:
  /** Builds a Vertex2 object with all elements set to 0.
   */
  Vertex2();

  /** Builds a Vertex2 object with the given position, texture coordinates,
   *  and ph_color.
   *
   *  \param position the vertex position.
   *  \param textureCoordinates the vertex texture coordinates.
   *  \param ph_color the vertex ph_color.
   */
  Vertex2(
    const vec2f& position, const vec2f& textureCoordinates, const color& ph_color);

  /** Gets the vertex position.
   *
   *  \return the vertex position.
   */
  vec2f get_position() const;

  /** Sets the vertex position.
   *
   *  \param pos the vertex position.
   */
  void set_position(const vec2f& pos);

  /** Gets the vertex texture coordinates.
   *
   *  \return the vertex texture coordinates.
   */
  vec2f getTextureCoordinates() const;

  /** Sets the vertex texture coordinates.
   *
   *  \param textureCoordinates the vertex texture coordinates.
   */
  void setTextureCoordinates(const vec2f& textureCoordinates);

  /** Gets the vertex ph_color.
   *
   *  \return the vertex ph_color.
   */
  color get_color() const;

  /** Sets the vertex ph_color.
   *
   *  \param ph_color the vertex ph_color.
   */
  void set_color(const color& ph_color);

private:
  static constexpr size_t sPositionSize = 2u;
  static constexpr size_t sTextureCoordinatesSize = 2u;
  static constexpr size_t sColorSize = 4u;

private:
  GLfloat m_position[sPositionSize];
  GLfloat mTexCoords[sTextureCoordinatesSize];
  GLfloat mColor[sColorSize];
};

HOU_PRAGMA_PACK_POP()

/** Checks if two Vertex2 objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are equal.
 */
HOU_GFX_API bool operator==(const Vertex2& lhs, const Vertex2& rhs);

/** Checks if two Vertex2 objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are not equal.
 */
HOU_GFX_API bool operator!=(const Vertex2& lhs, const Vertex2& rhs);

/** Checks if two Vertex2 objects are equal with the specified accuracy.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \param acc the accuracy.
 *  \return true if the two objects are equal.
 */
HOU_GFX_API bool close(const Vertex2& lhs, const Vertex2& rhs,
  Vertex2::ComparisonType acc
  = std::numeric_limits<Vertex2::ComparisonType>::epsilon());

/** Writes the object into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param v the Vertex2.
 *  \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const Vertex2& v);

/** Creates a Mesh object representing a ph_rectangle shape with the given size.
 *
 *  The texture coordinates are defined so that a texture is stretched to cover
 *  the entire ph_rectangle.
 *  The ph_color is always white.
 *
 *  \param size the size of the ph_rectangle.
 *  \return the Mesh representing the ph_rectangle.
 */
HOU_GFX_API Mesh2 createRectangleMesh2(const vec2f& size);

/** Creates a Mesh2 object representing a ph_rectangle outline shape with the
 *  given size and border thickness.
 *
 *  The texture coordinates are always equal to zero.
 *  The ph_color is always white.
 *  The size refers to the outside of the border.
 *
 *  \param size the size of the ph_rectangle.
 *  \param thickness the thickness of the border of the ph_rectangle.
 *  \return the Mesh2 representing the ph_rectangle outline.
 */
HOU_GFX_API Mesh2 createRectangleOutlineMesh2(
  const vec2f& size, float thickness);

/** Creates a Mesh2 object representing an approximation of an ellipse with
 *  the given size and drawn with the given number of points.
 *
 *  The texture coordinates are always equal to zero.
 *  The ph_color is always white.
 *  The actual vertex count is equal to pointCount plus 2, as the center of
 *  the ellipse is also defined as a vertex and one vertex has to be repeated
 *  twice to close the shape.
 *
 *  \param size the size of the ellipse.
 *  \param pointCount the number of pointCount used to draw the ellipse.
 *  \return the Mesh2 representing the ellipse.
 */
HOU_GFX_API Mesh2 createEllipseMesh2(const vec2f& size, uint pointCount);


/** Creates a Mesh2 object representing an approximation of an ellipse outline
 *  with the given size and drawn with the given number of points.
 *
 *  The texture coordinates are always equal to zero.
 *  The ph_color is always white.
 *  The number of points refers to the number of points used to draw the outer
 *  and inner perimiter of the outline each.
 *  The size refers to the outside of the border.
 *
 *  The actual vertex count is equal to double pointCount plus 2, as the center
 *  of the ellipse is also defined as a vertex and one vertex has to be repeated
 *  twice to close the shape.
 *
 *  \param size the size of the ellipse.
 *  \param pointCount the number of pointCount used to draw the ellipse.
 *  \param thickness the thicknes of the outline.
 *  \return the Mesh2 representing the ellipse outline.
 */
HOU_GFX_API Mesh2 createEllipseOutlineMesh2(
  const vec2f& size, uint pointCount, float thickness);

/** Creates a Mesh2 object representing a texture quad covering the specified
 *  ph_rectangle of a texture.
 *
 *  A texture quad has a rectangular shape with the top left corner at the
 * origin and the size specified by rect, just like a normal ph_rectangle mesh.
 *  Unlike the ph_rectangle mesh, the texture coordinates are defined to coincide
 *  with the elements of rect, normalized by the actual texture size.
 *  The same texture quad may be used with different textures with the same
 * size. If a texture quad is used with a texture of a different size than the
 * one it was defined with, it will work, but the section of texture shown will
 * not correspond to the values of rect anymore. The ph_color is always white.
 *
 *  \param rect the part of the texture to be shown.
 *  \param textureSize the size of the texture to be used with the quad.
 */
HOU_GFX_API Mesh2 createTextureQuadMesh2(
  const rectf& rect, const vec2f& textureSize);

}  // namespace hou

#endif
