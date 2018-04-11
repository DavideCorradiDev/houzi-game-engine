// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_MESH_HPP
#define HOU_GFX_MESH_HPP

#include "hou/cor/NonCopyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/gfx/MeshDrawMode.hpp"
#include "hou/gfx/MeshFillMode.hpp"
#include "hou/gfx/VertexArray.hpp"
#include "hou/gfx/RenderBuffer.hpp"

#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/Span.hpp"
#include "hou/cor/StdVector.hpp"

#include "hou/gl/GlUtils.hpp"

#include <iostream>



namespace hou
{

/** Represents a mesh.
 *
 *  The vertex information of a Mesh object is stored in the VRAM.
 *  There must be a current context to create a Mesh object.
 *  A Mesh object should be used only if the owning context is current.
 */
template <typename VertexType>
class HOU_GFX_API Mesh : public NonCopyable
{
public:
  /** Binds the mesh to the current RenderContext.
   *
   *  \param mesh the Mesh to be bound.
   */
  static void bind(const Mesh& mesh);

  /** Draws a Mesh object with the current shader and texture.
   *
   *  The draw operation automatically binds the mesh to the current
   * RenderContext.
   *
   *  \param mesh the Mesh to be drawn.
   */
  static void draw(const Mesh& mesh);

public:
  /** Creates a Mesh with the given MeshDrawMode, MeshFillMode, and vertices.
   *
   *  \param drawMode the MeshDrawMode.
   *  \param fillMode the MeshFillMode.
   *  \param vertices the vertices.
   */
  Mesh(MeshDrawMode drawMode, MeshFillMode fillMode,
    const Span<const VertexType>& vertices);

  /** Move constructor.
   *
   *  \param other the other Mesh object.
   */
  Mesh(Mesh&& other);

  /** Gets the MeshDrawMode.
   *
   *  \return the MeshDrawMode.
   */
  MeshDrawMode getDrawMode() const;

  /** Gets the MeshFillMode.
   *
   *  \return the MeshFillMode.
   */
  MeshFillMode getFillMode() const;

  /** Gets the number of vertices in the mesh.
   *
   *  \return the number of vertices in the mesh.
   */
  uint getVertexCount() const;

  /** Gets the vertices in the mesh inside a vector.
   *
   *  \return a vector containing the vertices of the mesh.
   */
  std::vector<VertexType> getVertices() const;

  /** Checks if this Mesh is bound to the current RenderContext.
   *
   *  \return true if this Mesh is bound to the current RenderContext.
   */
  bool isBound() const;

private:
  MeshDrawMode mDrawMode;
  MeshFillMode mFillMode;
  uint mVertexCount;
  StaticRenderBuffer<VertexType> mVbo;
  VertexArray mVao;
};


/** Checks if two Mesh objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are equal.
 */
template <typename VertexType>
bool operator==(const Mesh<VertexType>& lhs, const Mesh<VertexType>& rhs);

/** Checks if two Mesh objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are not equal.
 */
template <typename VertexType>
bool operator!=(const Mesh<VertexType>& lhs, const Mesh<VertexType>& rhs);

/** Checks if two Mesh objects are equal with the specified accuracy.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \param acc the accuracy.
 *  \return true if the two objects are equal.
 */
template <typename VertexType>
bool close(const Mesh<VertexType>& lhs, const Mesh<VertexType>& rhs,
  typename VertexType::value_type acc = std::numeric_limits<float>::epsilon());

/** Writes the object into a stream.
 *
 *  \param os the stream.
 *  \param v the Mesh.
 *  \return a reference to os.
 */
template <typename VertexType>
std::ostream& operator<<(std::ostream& os, const Mesh<VertexType>& m);

}  // namespace hou

#include "hou/gfx/Mesh.inl"

#endif
