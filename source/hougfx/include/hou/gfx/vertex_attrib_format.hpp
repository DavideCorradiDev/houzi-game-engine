// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTEX_ATTRIB_FORMAT_HPP
#define HOU_GFX_VERTEX_ATTRIB_FORMAT_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/cor/basic_types.hpp"

#include "hou/gfx/gl_type.hpp"

#include <iostream>



namespace hou
{

/** Class representing the format of an attribute of a ph_vertex.
 */
class HOU_GFX_API vertex_attrib_format
{
public:
  /** Constructor.
   *
   * \param type the attribute type.
   *
   * \param element_count the number of elements forming the attribute.
   *
   * \param byte_offset the byte offset from the beginning of the ph_vertex.
   *
   * \param must_be_normalized whether the value of this attribute must be
   * normalized or not.
   */
  vertex_attrib_format(gl_type type, uint element_count, uint byte_offset,
    bool must_be_normalized);

  /** Retrieves the attribute type.
   *
   * \return the attribute type.
   */
  gl_type get_type() const;

  /** Retrieves the number of elements of the attribute.
   *
   * \return the number of elements of the attribute.
   */
  uint get_element_count() const;

  /** Retrieves the offset from the start of the ph_vertex object.
   *
   * \return the offset from the start of the ph_vertex object.
   */
  uint get_byte_offset() const;

  /** Retrieves whether the attribute values must be normalized.
   *
   * \return true if the attribute values must be normalized.
   */
  bool must_be_normalized() const;

private:
  gl_type m_type;
  uint m_element_count;
  uint m_byte_offset;
  GLboolean m_must_be_normalized;
};

/** Checks if two vertex_attrib_format objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_GFX_API bool operator==(
  const vertex_attrib_format& lhs, const vertex_attrib_format& rhs);

/** Checks if two vertex_attrib_format objects not are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_GFX_API bool operator!=(
  const vertex_attrib_format& lhs, const vertex_attrib_format& rhs);

/** Writes the object into a ph_stream.
 *
 * \param os the ph_stream.
 *
 * \param vf the vertex_attrib_format.
 *
 * \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(
  std::ostream& os, const vertex_attrib_format& vf);

}  // namespace hou

#endif
