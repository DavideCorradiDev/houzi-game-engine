// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTEX_ARRAY_HPP
#define HOU_GFX_VERTEX_ARRAY_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/gfx_export.hpp"

#include "hou/cor/basic_types.hpp"

#include "hou/gl/gl_vertex_array_handle.hpp"



namespace hou
{

class vertex_buffer;
class vertex_format;

/** Represents a vertex_array object.
 */
class HOU_GFX_API vertex_array : public non_copyable
{
public:
  /** Binds the vertex_array to the current graphic_context.
   *
   * \param va the vertex_array to be bound.
   */
  static void bind(const vertex_array& va);

  /** Unbinds the currently bound vertex_array, if present.
   */
  static void unbind();

  /** Retrieves the maximum number of vertex_buffer objects that can be bound to
   * a single vertex_array object.
   *
   * \return the maximum number of vertex_buffer objects that can be bound.
   */
  static uint get_max_binding_index();

public:
  /** default constructor.
   */
  vertex_array();

  /** Move constructor.
   *
   * \param other the other vertex_array.
   */
  vertex_array(vertex_array&& other);

  /** Retrieves the reference to the OpenGL vertex array object.
   *
   * \return the reference to the OpenGL vertex array object.
   */
  const gl::vertex_array_handle& get_handle() const;

  /** Checks if the vertex_array is currently bound.
   *
   * \return the result of the check.
   */
  bool is_bound() const;

  /** Binds a vertex_buffer as a vertex buffer.
   *
   * The data in the vertex_buffer represents vertex data.
   * Throws if binding index is greater than the maximum binding index.
   *
   * \param vb the vertex_buffer to be bound.
   *
   * \param binding_index the binding index to be used.
   *
   * \param vf the format of the vertices contained in vb.
   */
  void set_vertex_data(
    const vertex_buffer& vb, uint binding_index, const vertex_format& vf);

  /** Binds a vertex_buffer as an element buffer.
   *
   * The data in the vertex_buffer represents indices referring to element of
   * the bound vertex buffer.
   *
   * \param eb the vertex_buffer to be bound.
   */
  void set_element_data(const vertex_buffer& eb);

private:
  gl::vertex_array_handle m_handle;
};

}  // namespace hou

#endif
