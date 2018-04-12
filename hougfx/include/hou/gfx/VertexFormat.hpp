// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_VERTEX_FORMAT
#define HOU_GFX_VERTEX_FORMAT

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/Span.hpp"
#include "hou/cor/StdVector.hpp"

#include "hou/gfx/VertexAttribFormat.hpp"

#include <iostream>



namespace hou
{

/** Describes the format of a vertex.
 */
class HOU_GFX_API VertexFormat
{
public:
  /** Retrieves the maximum number of allowed VertexAttribFormat.
   */
  static uint getMaxAttribFormatCount();

public:
  /** Span constructor.
   *
   *  Creates a VertexFormat with the specified offset, stride, and
   * VertexAttribFormat objects.
   *
   *  \param offset the offset from the begining of the buffer in bytes.
   *  \param stride the intervals at which the vertex repeats in the buffer in
   * bytes. \param vertexAttribFormats the format of the vertex attributes.
   */
  VertexFormat(ptrdiff_t offset, uint stride,
    const Span<const VertexAttribFormat>& vertexAttribFormats);

  /** VertexAttribFormat move constructor.
   *
   *  Creates a VertexFormat with the specified offset, stride, and
   * VertexAttribFormat objects.
   *
   *  \param offset the offset from the begining of the buffer.
   *  \param stride the intervals at which the vertex repeats in the buffer.
   *  \param vertexAttribFormats the format of the vertex attributes.
   */
  VertexFormat(ptrdiff_t offset, uint stride,
    std::vector<VertexAttribFormat>&& vertexAttribFormats);

  /** Retrieves the offset of the vertex from the beginning of the buffer in
   * bytes
   *
   *  \return the offset of the vertex from the beginning of the buffer in
   * bytes.
   */
  ptrdiff_t getOffset() const;

  /** Retrieves the intervals at which the vertex repeats in the buffer in
   * bytes.
   *
   *  \return the intervals at which the vertex repeats in the buffer in bytes.
   */
  uint getStride() const;

  /** Retrieves the format of the vertex attributes.
   *
   *  \return the format of the vertex attributes.
   */
  const std::vector<VertexAttribFormat>& getVertexAttribFormats() const;

private:
  ptrdiff_t mOffset;
  uint mStride;
  std::vector<VertexAttribFormat> mVertexAttribFormats;
};

/** Checks if two VertexFormat objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_GFX_API bool operator==(const VertexFormat& lhs, const VertexFormat& rhs);

/** Checks if two VertexFormat objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_GFX_API bool operator!=(const VertexFormat& lhs, const VertexFormat& rhs);

/** Writes the object into a stream.
 *
 *  \param os the stream.
 *  \param vf the VertexFormat.
 *  \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const VertexFormat& vf);

}  // namespace hou

#endif
