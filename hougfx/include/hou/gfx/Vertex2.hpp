// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_VERTEX_2_HPP
#define HOU_GFX_VERTEX_2_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"

#include "hou/sys/Color.hpp"

#include "hou/mth/Matrix.hpp"



namespace hou
{

class VertexFormat;

/** Represents a vertex in 2d space.
 *
 *  The vertex contains information about its position, texture coordinates,
 *  and color.
 */
class HOU_GFX_API Vertex2
{
public:
  using value_type = float;

public:
  static const VertexFormat& getVertexFormat();

public:
  /** Builds a Vertex2 object with all elements set to 0.
   */
  Vertex2();

  /** Builds a Vertex2 object with the given position, texture coordinates,
   *  and color.
   *
   *  \param position the vertex position.
   *  \param textureCoordinates the vertex texture coordinates.
   *  \param color the vertex color.
   */
  Vertex2(const Vec2f& position, const Vec2f& textureCoordinates
    , const Color& color);

  /** Gets the vertex position.
   *
   *  \return the vertex position.
   */
  Vec2f getPosition() const;

  /** Sets the vertex position.
   *
   *  \param pos the vertex position.
   */
  void setPosition(const Vec2f& pos);

  /** Gets the vertex texture coordinates.
   *
   *  \return the vertex texture coordinates.
   */
  Vec2f getTextureCoordinates() const;

  /** Sets the vertex texture coordinates.
   *
   *  \param textureCoordinates the vertex texture coordinates.
   */
  void setTextureCoordinates(const Vec2f& textureCoordinates);

  /** Gets the vertex color.
   *
   *  \return the vertex color.
   */
  Color getColor() const;

  /** Sets the vertex color.
   *
   *  \param color the vertex color.
   */
  void setColor(const Color& color);

private:
  static constexpr size_t sPositionSize = 2u;
  static constexpr size_t sTextureCoordinatesSize = 2u;
  static constexpr size_t sColorSize = 4u;

private:
  float mPosition[sPositionSize];
  float mTexCoords[sTextureCoordinatesSize];
  float mColor[sColorSize];
};

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
HOU_GFX_API bool close(const Vertex2& lhs, const Vertex2& rhs
  , float acc = std::numeric_limits<float>::epsilon());

/** Writes the object into a stream.
 *
 *  \param os the stream.
 *  \param v the Vertex2.
 *  \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const Vertex2& v);

}

#endif

