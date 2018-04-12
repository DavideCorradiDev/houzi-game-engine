// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_MESH_HPP
#define HOU_GFX_MESH_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/NonCopyable.hpp"

#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/Span.hpp"
#include "hou/cor/StdVector.hpp"

#include "hou/gfx/MeshDrawMode.hpp"
#include "hou/gfx/MeshFillMode.hpp"
#include "hou/gfx/RenderBuffer.hpp"
#include "hou/gfx/VertexArray.hpp"

#include <iostream>



namespace hou
{

/** Represents a mesh.
 *
 *  The vertex information of a Mesh object is stored in the VRAM.
 *  There must be a current context to create a Mesh object.
 *  A Mesh object should be used only if the owning context is current.
 *
 *  \tparam T the type of vertex stored by the mesh.
 */
class HOU_GFX_API Mesh : public NonCopyable
{
public:
  /** Draws a Mesh object with the current shader and texture.
   *
   *  The draw operation automatically binds the mesh to the current
   * RenderContext.
   *
   *  \param mesh the Mesh to be drawn.
   */
  static void draw(const Mesh& mesh);

public:
  /** Destructor.
   */
  virtual ~Mesh() = 0;

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

protected:
  /** Generic constructor.
   *
   *  To be used by derived classes.
   *
   *  \param drawMode the MeshDrawMode.
   *  \param fillMode the MeshFillMode.
   *  \param vertexCount the number of vertices.
   */
  Mesh(MeshDrawMode drawMode, MeshFillMode fillMode, uint vertexCount);

  /** Move constructor.
   *
   *  \param other the other MeshT object.
   */
  Mesh(Mesh&& other);

protected:
  MeshDrawMode mDrawMode;
  MeshFillMode mFillMode;
  uint mVertexCount;
  VertexArray mVao;
};

/** Represents a mesh.
 *
 *  The vertex information of a Mesh object is stored in the VRAM.
 *  There must be a current context to create a Mesh object.
 *  A Mesh object should be used only if the owning context is current.
 *
 *  \tparam T the type of vertex stored by the mesh.
 */
template <typename T>
class MeshT : public Mesh
{
public:
  /** Type of the vertices stored in the Mesh. */
  using VertexType = T;

  /** Type used to represent the collection of vertices stored in the Mesh. */
  using VertexCollectionType = std::vector<T>;

public:
  /** Creates a Mesh with the given MeshDrawMode, MeshFillMode, and vertices.
   *
   *  \param drawMode the MeshDrawMode.
   *  \param fillMode the MeshFillMode.
   *  \param vertices the vertices.
   */
  MeshT(MeshDrawMode drawMode, MeshFillMode fillMode,
    const Span<const T>& vertices);

  /** Move constructor.
   *
   *  \param other the other MeshT object.
   */
  MeshT(MeshT&& other);

  /** Gets the vertices in the mesh inside a vector.
   *
   *  \return a vector containing the vertices of the mesh.
   */
  VertexCollectionType getVertices() const;

private:
  StaticRenderBuffer<T> mVbo;
};


/** Checks if two Mesh objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are equal.
 */
template <typename T>
bool operator==(const MeshT<T>& lhs, const MeshT<T>& rhs);

/** Checks if two MeshT objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are not equal.
 */
template <typename T>
bool operator!=(const MeshT<T>& lhs, const MeshT<T>& rhs);

/** Checks if two MeshT objects are equal with the specified accuracy.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \param acc the accuracy.
 *  \return true if the two objects are equal.
 */
template <typename T>
bool close(const MeshT<T>& lhs, const MeshT<T>& rhs,
  typename T::ComparisonType acc
  = std::numeric_limits<typename T::ComparisonType>::epsilon());

/** Writes the object into a stream.
 *
 *  \param os the stream.
 *  \param v the MeshT.
 *  \return a reference to os.
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const MeshT<T>& m);

}  // namespace hou

#include "hou/gfx/Mesh.inl"

#endif
