// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTEX_FORMAT
#define HOU_GFX_VERTEX_FORMAT

#include "hou/gfx/gfx_export.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/span.hpp"
#include "hou/cor/std_vector.hpp"

#include "hou/gfx/vertex_attrib_format.hpp"

#include <iostream>



namespace hou
{

/** Describes the format of a ph_vertex.
 */
class HOU_GFX_API vertex_format
{
public:
  /** Retrieves the maximum number of allowed vertex_attrib_format.
   */
  static uint get_max_attrib_format_count();

public:
  /** span constructor.
   *
   *  Creates a vertex_format with the specified offset, stride, and
   * vertex_attrib_format objects.
   *
   *  \param offset the offset from the begining of the buffer in bytes.
   *  \param stride the intervals at which the ph_vertex repeats in the buffer in
   * bytes. \param vertexAttribFormats the format of the ph_vertex attributes.
   */
  vertex_format(ptrdiff_t offset, uint stride,
    const span<const vertex_attrib_format>& vertexAttribFormats);

  /** vertex_attrib_format move constructor.
   *
   *  Creates a vertex_format with the specified offset, stride, and
   * vertex_attrib_format objects.
   *
   *  \param offset the offset from the begining of the buffer.
   *  \param stride the intervals at which the ph_vertex repeats in the buffer.
   *  \param vertexAttribFormats the format of the ph_vertex attributes.
   */
  vertex_format(ptrdiff_t offset, uint stride,
    std::vector<vertex_attrib_format>&& vertexAttribFormats);

  /** Retrieves the offset of the ph_vertex from the beginning of the buffer in
   * bytes
   *
   *  \return the offset of the ph_vertex from the beginning of the buffer in
   * bytes.
   */
  ptrdiff_t get_offset() const;

  /** Retrieves the intervals at which the ph_vertex repeats in the buffer in
   * bytes.
   *
   *  \return the intervals at which the ph_vertex repeats in the buffer in bytes.
   */
  uint get_stride() const;

  /** Retrieves the format of the ph_vertex attributes.
   *
   *  \return the format of the ph_vertex attributes.
   */
  const std::vector<vertex_attrib_format>& get_vertex_attrib_formats() const;

private:
  ptrdiff_t m_offset;
  uint m_stride;
  std::vector<vertex_attrib_format> m_vertex_attrib_formats;
};

/** Checks if two vertex_format objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_GFX_API bool operator==(const vertex_format& lhs, const vertex_format& rhs);

/** Checks if two vertex_format objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_GFX_API bool operator!=(const vertex_format& lhs, const vertex_format& rhs);

/** Writes the object into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param vf the vertex_format.
 *  \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const vertex_format& vf);

}  // namespace hou

#endif
