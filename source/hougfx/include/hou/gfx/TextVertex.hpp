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

class VertexFormat;

HOU_PRAGMA_PACK_PUSH(1)

/** Represents a vertex used to render text.
 *
 *  The vertex contains information about its position and texture coordinates.
 */
class HOU_GFX_API TextVertex
{
public:
  /** Type to be used as accuracy in close comparison checks for mesh.
   */
  using ComparisonType = float;

public:
  /** Retrieves the VertexFormat.
   */
  static const VertexFormat& getVertexFormat();

public:
  /** Builds a TextVertex object with all elements set to 0.
   */
  TextVertex();

  /** Builds a TextVertex object with the given position and texture
   * coordinates.
   *
   *  \param position the vertex position.
   *  \param textureCoordinates the vertex texture coordinates.
   */
  TextVertex(const vec2f& position, const vec3f& textureCoordinates);

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
  vec3f getTextureCoordinates() const;

  /** Sets the vertex texture coordinates.
   *
   *  \param textureCoordinates the vertex texture coordinates.
   */
  void setTextureCoordinates(const vec3f& textureCoordinates);

private:
  static constexpr size_t sPositionSize = 2u;
  static constexpr size_t sTextureCoordinatesSize = 3u;

private:
  GLfloat m_position[sPositionSize];
  GLfloat mTexCoords[sTextureCoordinatesSize];
};

HOU_PRAGMA_PACK_POP()

/** Checks if two TextVertex objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are equal.
 */
HOU_GFX_API bool operator==(const TextVertex& lhs, const TextVertex& rhs);

/** Checks if two TextVertex objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are not equal.
 */
HOU_GFX_API bool operator!=(const TextVertex& lhs, const TextVertex& rhs);

/** Checks if two TextVertex objects are equal with the specified accuracy.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \param acc the accuracy.
 *  \return true if the two objects are equal.
 */
HOU_GFX_API bool close(const TextVertex& lhs, const TextVertex& rhs,
  TextVertex::ComparisonType acc
  = std::numeric_limits<TextVertex::ComparisonType>::epsilon());

/** Writes the object into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param v the TextVertex.
 *  \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const TextVertex& v);

/** mesh TextVertex.
 *
 *  Used to represent renderable text blocks.
 */
using TextMesh = mesh_t<TextVertex>;

}  // namespace hou

#endif
