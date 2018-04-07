// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_VERTEX_ARRAY_HPP
#define HOU_GFX_VERTEX_ARRAY_HPP

#include "hou/cor/NonCopyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"

#include "hou/gl/GlVertexArrayHandle.hpp"



namespace hou
{

class VertexBuffer;
class VertexFormat;

class HOU_GFX_API VertexArray : public NonCopyable
{
public:
  static void bind(const VertexArray& vertexArray);
  static void unbind();

  static uint getMaxBindingIndex();

public:
  VertexArray();
  VertexArray(VertexArray&& other);

  const gl::VertexArrayHandle& getHandle() const;
  bool isBound() const;
  void setVertexData(
    const VertexBuffer& vb, uint bindingIndex, const VertexFormat& vf);
  void setElementData(const VertexBuffer& eb);

private:
  gl::VertexArrayHandle mHandle;
};

}  // namespace hou

#endif
