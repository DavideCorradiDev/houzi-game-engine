// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTEX_ATTRIB_FORMAT_HPP
#define HOU_GFX_VERTEX_ATTRIB_FORMAT_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"

#include "hou/gfx/GlType.hpp"

#include <iostream>



namespace hou
{

/** Class representing the format of an attribute of a vertex.
 */
class HOU_GFX_API VertexAttribFormat
{
public:
  /** Constructor.
   *
   *  \param type the attribute type.
   *  \param elementCount the number of elements forming the attribute.
   *  \param byteOffset the byte offset from the beginning of the vertex.
   *  \param mustBeNormalized whether the value of this attribute must be
   *  normalized or not.
   */
  VertexAttribFormat(
    GlType type, uint elementCount, uint byteOffset, bool mustBeNormalized);

  /** Retrieves the attribute type.
   *
   *  \return the attribute type.
   */
  GlType getType() const;

  /** Retrieves the number of elements of the attribute.
   *
   *  \return the number of elements of the attribute.
   */
  uint getElementCount() const;

  /** Retrieves the offset from the start of the vertex object.
   *
   *  \return the offset from the start of the vertex object.
   */
  uint getByteOffset() const;

  /** Retrieves whether the attribute values must be normalized.
   *
   *  \return true if the attribute values must be normalized.
   */
  bool mustBeNormalized() const;

private:
  GlType mType;
  uint mElementCount;
  uint mByteOffset;
  GLboolean mMustBeNormalized;
};

/** Checks if two VertexAttribFormat objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_GFX_API bool operator==(
  const VertexAttribFormat& l, const VertexAttribFormat& r);

/** Checks if two VertexAttribFormat objects not are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_GFX_API bool operator!=(
  const VertexAttribFormat& l, const VertexAttribFormat& r);

/** Writes the object into a stream.
 *
 *  \param os the stream.
 *  \param vf the VertexAttribFormat.
 *  \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(
  std::ostream& os, const VertexAttribFormat& vf);

}  // namespace hou

#endif
