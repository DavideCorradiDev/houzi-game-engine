// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_MESH2_HPP
#define HOU_GFX_MESH2_HPP

#include "hou/gfx/mesh.hpp"
#include "hou/gfx/mesh2_fwd.hpp"
#include "hou/gfx/vertex2.hpp"

#include "hou/gfx/gfx_config.hpp"

#include "hou/mth/rectangle_fwd.hpp"



namespace hou
{
/** Creates a mesh object representing a rectangle shape with the given size.
 *
 * The texture coordinates are defined so that a texture is stretched to cover
 * the entire rectangle.
 * The color is always white.
 *
 * \param size the size of the rectangle.
 *
 * \return the mesh representing the rectangle.
 */
HOU_GFX_API mesh2 create_rectangle_mesh2(const vec2f& size);

/** Creates a mesh2 object representing a rectangle outline shape with the
 * given size and border thickness.
 *
 * The texture coordinates are always equal to zero.
 * The color is always white.
 * The size refers to the outside of the border.
 *
 * \param size the size of the rectangle.
 *
 * \param thickness the thickness of the border of the rectangle.
 *
 * \return the mesh2 representing the rectangle outline.
 */
HOU_GFX_API mesh2 create_rectangle_outline_mesh2(
  const vec2f& size, float thickness);

/** Creates a mesh2 object representing an approximation of an ellipse with
 * the given size and drawn with the given number of points.
 *
 * The texture coordinates are always equal to zero.
 * The color is always white.
 * The actual vertex count is equal to pointCount plus 2, as the center of
 * the ellipse is also defined as a vertex and one vertex has to be repeated
 * twice to close the shape.
 *
 * \param size the size of the ellipse.
 *
 * \param pointCount the number of pointCount used to draw the ellipse.
 *
 * \return the mesh2 representing the ellipse.
 */
HOU_GFX_API mesh2 create_ellipse_mesh2(const vec2f& size, uint pointCount);


/** Creates a mesh2 object representing an approximation of an ellipse outline
 * with the given size and drawn with the given number of points.
 *
 * The texture coordinates are always equal to zero.
 * The color is always white.
 * The number of points refers to the number of points used to draw the outer
 * and inner perimiter of the outline each.
 * The size refers to the outside of the border.
 *
 * The actual vertex count is equal to double pointCount plus 2, as the center
 * of the ellipse is also defined as a vertex and one vertex has to be repeated
 * twice to close the shape.
 *
 * \param size the size of the ellipse.
 *
 * \param pointCount the number of pointCount used to draw the ellipse.
 *
 * \param thickness the thicknes of the outline.
 *
 * \return the mesh2 representing the ellipse outline.
 */
HOU_GFX_API mesh2 create_ellipse_outline_mesh2(
  const vec2f& size, uint pointCount, float thickness);

/** Creates a mesh2 object representing a texture quad covering the specified
 * rectangle of a texture.
 *
 * A texture quad has a rectangular shape with the top left corner at the
 * origin and the size specified by rect, just like a normal rectangle
 * mesh. Unlike the rectangle mesh, the texture coordinates are defined
 * to coincide with the elements of rect, normalized by the actual texture size.
 * The same texture quad may be used with different textures with the same
 * size. If a texture quad is used with a texture of a different size than the
 * one it was defined with, it will work, but the section of texture shown will
 * not correspond to the values of rect anymore. The color is always white.
 *
 * \param rect the part of the texture to be shown.
 *
 * \param textureSize the size of the texture to be used with the quad.
 */
HOU_GFX_API mesh2 create_texture_quad_mesh2(
  const rectf& rect, const vec2f& textureSize);
}

#endif
