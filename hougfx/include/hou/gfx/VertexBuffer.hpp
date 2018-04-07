// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_VERTEX_BUFFER_HPP
#define HOU_GFX_VERTEX_BUFFER_HPP

#include "hou/cor/NonCopyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/Error.hpp"
#include "hou/cor/TemplateUtils.hpp"

#include "hou/gfx/VertexBufferAttributes.hpp"
#include "hou/gfx/VertexBufferTarget.hpp"

#include "hou/gl/GlBufferHandle.hpp"

#include <vector>



namespace hou
{

class HOU_GFX_API VertexBuffer : public NonCopyable
{
public:
  static void bind(const VertexBuffer& buffer, VertexBufferTarget target);
  static void unbind(VertexBufferTarget target);

public:
  VertexBuffer(uint byteCount, VertexBufferAttributes attributes);
  template <typename Container,
    typename Enable = std::enable_if_t<isContiguousContainer<Container>::value>>
  VertexBuffer(const Container& data, VertexBufferAttributes attributes);
  VertexBuffer(VertexBuffer&& other);

  const gl::BufferHandle& getHandle() const;
  bool isBound(VertexBufferTarget target) const;
  uint getByteCount() const;
  template <typename Container,
    typename Enable = std::enable_if_t<isContiguousContainer<Container>::value>>
  void setData(const Container& data);
  template <typename Container,
    typename Enable = std::enable_if_t<isContiguousContainer<Container>::value>>
  void setSubData(uint offset, const Container& data);
  template <typename DataType>
  std::vector<DataType> getData() const;
  template <typename DataType>
  std::vector<DataType> getSubData(uint offset, uint size) const;

private:
  VertexBuffer(
    uint byteCount, const void* data, VertexBufferAttributes attributes);

private:
  gl::BufferHandle mHandle;
  uint mByteCount;
};

}  // namespace hou

#include "hou/gfx/VertexBuffer.inl"

#endif
