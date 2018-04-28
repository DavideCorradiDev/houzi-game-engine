// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/Mesh.hpp"

#include "hou/gl/GlFunctions.hpp"



namespace hou
{

void Mesh::draw(const Mesh& mesh)
{
  VertexArray::bind(mesh.mVao);
  gl::setPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(mesh.mFillMode));
  gl::drawArrays(static_cast<GLenum>(mesh.mDrawMode), 0, mesh.mVertexCount);
}



Mesh::Mesh(MeshDrawMode drawMode, MeshFillMode fillMode, uint vertexCount)
  : non_copyable()
  , mDrawMode(drawMode)
  , mFillMode(fillMode)
  , mVertexCount(vertexCount)
  , mVao()
{}



Mesh::Mesh(Mesh&& other)
  : non_copyable()
  , mDrawMode(std::move(other.mDrawMode))
  , mFillMode(std::move(other.mFillMode))
  , mVertexCount(std::move(other.mVertexCount))
  , mVao(std::move(other.mVao))
{}



Mesh::~Mesh()
{}



MeshDrawMode Mesh::getDrawMode() const
{
  return mDrawMode;
}



MeshFillMode Mesh::getFillMode() const
{
  return mFillMode;
}



uint Mesh::getVertexCount() const
{
  return mVertexCount;
}

}  // namespace hou
