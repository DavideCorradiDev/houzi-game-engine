// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_MESH_HPP
#define HOU_GFX_MESH_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/cor/non_copyable.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/span.hpp"
#include "hou/cor/std_vector.hpp"

#include "hou/gfx/mesh_draw_mode.hpp"
#include "hou/gfx/mesh_fill_mode.hpp"
#include "hou/gfx/vertex_buffer.hpp"
#include "hou/gfx/vertex_array.hpp"

#include <iostream>



namespace hou
{

/** Represents a ph_mesh.
 *
 *  The ph_vertex information of a mesh object is stored in the VRAM.
 *  There must be a current ph_context to create a mesh object.
 *  a mesh object should be used only if the owning ph_context is current.
 *
 *  \tparam T the type of ph_vertex stored by the ph_mesh.
 */
class HOU_GFX_API mesh : public non_copyable
{
public:
  /** Draws a mesh object with the current ph_shader and ph_texture.
   *
   *  The draw operation automatically binds the ph_mesh to the current
   * graphic_context.
   *
   *  \param ph_mesh the mesh to be drawn.
   */
  static void draw(const mesh& ph_mesh);

public:
  /** Destructor.
   */
  virtual ~mesh() = 0;

  /** Gets the mesh_draw_mode.
   *
   *  \return the mesh_draw_mode.
   */
  mesh_draw_mode get_draw_mode() const;

  /** Gets the mesh_fill_mode.
   *
   *  \return the mesh_fill_mode.
   */
  mesh_fill_mode get_fill_mode() const;

  /** Gets the number of vertices in the ph_mesh.
   *
   *  \return the number of vertices in the ph_mesh.
   */
  uint get_vertex_count() const;

protected:
  /** Generic constructor.
   *
   *  To be used by derived classes.
   *
   *  \param drawMode the mesh_draw_mode.
   *  \param fillMode the mesh_fill_mode.
   *  \param vertexCount the number of vertices.
   */
  mesh(mesh_draw_mode drawMode, mesh_fill_mode fillMode, uint vertexCount);

  /** Move constructor.
   *
   *  \param other the other mesh_t object.
   */
  mesh(mesh&& other);

protected:
  mesh_draw_mode m_draw_mode;
  mesh_fill_mode m_fill_mode;
  uint m_vertex_count;
  vertex_array m_vao;
};

/** Represents a ph_mesh.
 *
 *  The ph_vertex information of a mesh object is stored in the VRAM.
 *  There must be a current ph_context to create a mesh object.
 *  a mesh object should be used only if the owning ph_context is current.
 *
 *  \tparam T the type of ph_vertex stored by the ph_mesh.
 */
template <typename T>
class mesh_t : public mesh
{
public:
  /** Type of the vertices stored in the mesh. */
  using vertex_type = T;

  /** Type used to represent the collection of vertices stored in the mesh. */
  using vertex_collection = std::vector<T>;

public:
  /** Creates a mesh with the given mesh_draw_mode, mesh_fill_mode, and vertices.
   *
   *  \param drawMode the mesh_draw_mode.
   *  \param fillMode the mesh_fill_mode.
   *  \param vertices the vertices.
   */
  mesh_t(mesh_draw_mode drawMode, mesh_fill_mode fillMode,
    const span<const T>& vertices);

  /** Move constructor.
   *
   *  \param other the other mesh_t object.
   */
  mesh_t(mesh_t&& other);

  /** Gets the vertices in the ph_mesh inside a vector.
   *
   *  \return a vector containing the vertices of the ph_mesh.
   */
  vertex_collection getVertices() const;

private:
  static_vertex_buffer<T> m_vbo;
};


/** Checks if two mesh objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are equal.
 */
template <typename T>
bool operator==(const mesh_t<T>& lhs, const mesh_t<T>& rhs);

/** Checks if two mesh_t objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are not equal.
 */
template <typename T>
bool operator!=(const mesh_t<T>& lhs, const mesh_t<T>& rhs);

/** Checks if two mesh_t objects are equal with the specified accuracy.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \param acc the accuracy.
 *  \return true if the two objects are equal.
 */
template <typename T>
bool close(const mesh_t<T>& lhs, const mesh_t<T>& rhs,
  typename T::comparison_type acc
  = std::numeric_limits<typename T::comparison_type>::epsilon());

/** Writes the object into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param m the mesh_t.
 *  \return a reference to os.
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const mesh_t<T>& m);

}  // namespace hou

#include "hou/gfx/mesh.inl"

#endif
