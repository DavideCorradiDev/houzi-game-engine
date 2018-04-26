// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T, bool dynamicStorage>
VertexBufferT<T, dynamicStorage>::VertexBufferT(uint size)
  : VertexBuffer(size * sizeof(T), dynamicStorage)
{}



template <typename T, bool dynamicStorage>
VertexBufferT<T, dynamicStorage>::VertexBufferT(const Span<const T>& data)
  : VertexBuffer(data.size() * sizeof(T),
      reinterpret_cast<const void*>(data.data()), dynamicStorage)
{}



template <typename T, bool dynamicStorage>
VertexBufferT<T, dynamicStorage>::VertexBufferT(VertexBuffer&& other)
  : VertexBuffer(std::move(other))
{}



template <typename T, bool dynamicStorage>
uint VertexBufferT<T, dynamicStorage>::getSize() const
{
  HOU_EXPECT_DEV(getByteCount() % sizeof(T) == 0u);
  return getByteCount() / sizeof(T);
}



template <typename T, bool dynamicStorage>
typename VertexBufferT<T, dynamicStorage>::DataType
  VertexBufferT<T, dynamicStorage>::getData() const
{
  return getSubData(0u, getSize());
}



template <typename T, bool dynamicStorage>
typename VertexBufferT<T, dynamicStorage>::DataType
  VertexBufferT<T, dynamicStorage>::getSubData(
    uint offset, uint elementCount) const
{
  HOU_EXPECT_DEV(getByteCount() % sizeof(T) == 0u);
  HOU_EXPECT(offset + elementCount <= getSize());
  typename VertexBufferT<T, dynamicStorage>::DataType dataOut(
    elementCount, T());
  gl::getBufferSubData(getHandle(), static_cast<GLintptr>(offset * sizeof(T)),
    static_cast<uint>(elementCount * sizeof(T)),
    reinterpret_cast<GLvoid*>(dataOut.data()));
  return dataOut;
}



template <typename T, bool dynamicStorage>
template <bool ds, typename Enable>
void VertexBufferT<T, dynamicStorage>::setData(const Span<const T>& data)
{
  HOU_EXPECT(data.size() == getSize());
  setSubData(0u, data);
}



template <typename T, bool dynamicStorage>
template <bool ds, typename Enable>
void VertexBufferT<T, dynamicStorage>::setSubData(
  uint offset, const Span<const T>& data)
{
  HOU_EXPECT_DEV(getByteCount() % sizeof(T) == 0u);
  HOU_EXPECT(offset + data.size() <= getSize());
  gl::setBufferSubData(getHandle(), static_cast<GLintptr>(offset * sizeof(T)),
    static_cast<GLsizei>(data.size() * sizeof(T)),
    reinterpret_cast<const GLvoid*>(data.data()));
}

}  // namespace hou
