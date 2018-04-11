// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

template <typename T, bool dynamicStorage>
RenderBufferT<T, dynamicStorage>::RenderBufferT(uint size)
  : RenderBuffer(size * sizeof(T), dynamicStorage)
{}



template <typename T, bool dynamicStorage>
RenderBufferT<T, dynamicStorage>::RenderBufferT(const Span<const T>& data)
  : RenderBuffer(data.size() * sizeof(T),
      reinterpret_cast<const void*>(data.data()), dynamicStorage)
{}



template <typename T, bool dynamicStorage>
RenderBufferT<T, dynamicStorage>::RenderBufferT(RenderBuffer&& other)
  : RenderBuffer(std::move(other))
{}



template <typename T, bool dynamicStorage>
uint RenderBufferT<T, dynamicStorage>::getSize() const
{
  HOU_EXPECT_DEV(getByteCount() % sizeof(T) == 0u);
  return getByteCount() / sizeof(T);
}



template <typename T, bool dynamicStorage>
typename RenderBufferT<T, dynamicStorage>::DataType
  RenderBufferT<T, dynamicStorage>::getData() const
{
  return getSubData(0u, getSize());
}



template <typename T, bool dynamicStorage>
template <bool ds, typename Enable>
void RenderBufferT<T, dynamicStorage>::setData(const Span<const T>& data)
{
  HOU_EXPECT(data.size() == getSize());
  setSubData(0u, data);
}



template <typename T, bool dynamicStorage>
typename RenderBufferT<T, dynamicStorage>::DataType
  RenderBufferT<T, dynamicStorage>::getSubData(uint offset, uint size) const
{
  HOU_EXPECT_DEV(getByteCount() % sizeof(T) == 0u);
  HOU_EXPECT(offset + size <= getSize());
  typename RenderBufferT<T, dynamicStorage>::DataType dataOut(size, T());
  gl::getBufferSubData(getHandle(), static_cast<GLintptr>(offset * sizeof(T)),
    static_cast<uint>(size * sizeof(T)),
    reinterpret_cast<GLvoid*>(dataOut.data()));
  return dataOut;
}



template <typename T, bool dynamicStorage>
template <bool ds, typename Enable>
void RenderBufferT<T, dynamicStorage>::setSubData(
  uint offset, const Span<const T>& data)
{
  HOU_EXPECT_DEV(getByteCount() % sizeof(T) == 0u);
  HOU_EXPECT(offset + data.size() <= getSize());
  gl::setBufferSubData(getHandle(), static_cast<GLintptr>(offset * sizeof(T)),
    static_cast<GLsizei>(data.size() * sizeof(T)),
    reinterpret_cast<const GLvoid*>(data.data()));
}

}  // namespace hou
