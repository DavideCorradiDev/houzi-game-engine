// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_RENDER_BUFFER_HPP
#define HOU_GFX_RENDER_BUFFER_HPP

#include "hou/cor/NonCopyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/Error.hpp"
#include "hou/cor/Span.hpp"
#include "hou/cor/TemplateUtils.hpp"

#include "hou/gfx/RenderBufferFwd.hpp"
#include "hou/gfx/RenderBufferTarget.hpp"

#include "hou/gl/GlBufferHandle.hpp"

#include <vector>



namespace hou
{

class HOU_GFX_API RenderBuffer : public NonCopyable
{
public:
  static void bind(const RenderBuffer& buffer, RenderBufferTarget target);
  static void unbind(RenderBufferTarget target);

public:
  const gl::BufferHandle& getHandle() const;
  bool isBound(RenderBufferTarget target) const;
  uint getByteCount() const;

protected:
  RenderBuffer(uint size, bool dynamicStorage);
  RenderBuffer(uint byteCount, const void* data, bool dynamicStorage);
  RenderBuffer(RenderBuffer&& other);

private:
  gl::BufferHandle mHandle;
  uint mByteCount;
};

template <typename T, bool dynamicStorage = false>
class RenderBufferT : public RenderBuffer
{
public:
  using ValueType = T;
  using DataType = std::vector<T>;

public:
  RenderBufferT(uint size);
  RenderBufferT(const Span<const T>& data);
  RenderBufferT(RenderBuffer&& other);

  uint getSize() const;

  DataType getData() const;
  template <bool ds = dynamicStorage, typename Enable = std::enable_if_t<ds>>
  void setData(const Span<const T>& data);

  DataType getSubData(uint offset, uint size) const;
  template <bool ds = dynamicStorage, typename Enable = std::enable_if_t<ds>>
  void setSubData(uint offset, const Span<const T>& data);
};

}  // namespace hou

#include "hou/gfx/RenderBuffer.inl"

#endif
