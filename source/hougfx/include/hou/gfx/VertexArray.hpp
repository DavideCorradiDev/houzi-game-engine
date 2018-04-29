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

class VertexBuffer;
class VertexFormat;

/** Represents a VertexArray object.
 */
class HOU_GFX_API VertexArray : public non_copyable
{
public:
  /** Binds the VertexArray to the current graphic_context.
   *
   *  \param vertexArray the VertexArray to be bound.
   */
  static void bind(const VertexArray& vertexArray);

  /** Unbinds the currently bound VertexArray, if present.
   */
  static void unbind();

  /** Retrieves the maximum number of VertexBuffer objects that can be bound to
   * a single VertexArray object.
   *
   *  \return the maximum number of VertexBuffer objects that can be bound.
   */
  static uint getMaxBindingIndex();

public:
  /** default constructor.
   */
  VertexArray();

  /** Move constructor.
   *
   *  \param other the other VertexArray.
   */
  VertexArray(VertexArray&& other);

  /** Retrieves the reference to the OpenGL vertex array object.
   *
   *  \return the reference to the OpenGL vertex array object.
   */
  const gl::vertex_array_handle& get_handle() const;

  /** Checks if the VertexArray is currently bound.
   *
   *  \return the result of the check.
   */
  bool isBound() const;

  /** Binds a VertexBuffer as a vertex buffer.
   *
   *  The data in the VertexBuffer represents vertex data.
   *  Throws if binding index is greater than the maximum binding index.
   *
   *  \param vb the VertexBuffer to be bound.
   *  \param bindingIndex the binding index to be used.
   *  \param vf the format of the vertices contained in vb.
   */
  void setVertexData(
    const VertexBuffer& vb, uint bindingIndex, const VertexFormat& vf);

  /** Binds a VertexBuffer as an element buffer.
   *
   *  The data in the VertexBuffer represents indices referring to element of
   *  the bound vertex buffer.
   *
   *  \param eb the VertexBuffer to be bound.
   */
  void setElementData(const VertexBuffer& eb);

private:
  gl::vertex_array_handle m_handle;
};

}  // namespace hou

#endif
