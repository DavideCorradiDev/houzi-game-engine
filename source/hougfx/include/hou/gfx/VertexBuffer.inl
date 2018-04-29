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
VertexBufferT<T, dynamicStorage>::VertexBufferT(const span<const T>& data)
  : VertexBuffer(data.size() * sizeof(T),
      reinterpret_cast<const void*>(data.data()), dynamicStorage)
{}



template <typename T, bool dynamicStorage>
VertexBufferT<T, dynamicStorage>::VertexBufferT(VertexBuffer&& other)
  : VertexBuffer(std::move(other))
{}



template <typename T, bool dynamicStorage>
uint VertexBufferT<T, dynamicStorage>::get_size() const
{
  HOU_EXPECT_DEV(get_byte_count() % sizeof(T) == 0u);
  return get_byte_count() / sizeof(T);
}



template <typename T, bool dynamicStorage>
typename VertexBufferT<T, dynamicStorage>::DataType
  VertexBufferT<T, dynamicStorage>::getData() const
{
  return getSubData(0u, get_size());
}



template <typename T, bool dynamicStorage>
typename VertexBufferT<T, dynamicStorage>::DataType
  VertexBufferT<T, dynamicStorage>::getSubData(
    uint offset, uint elementCount) const
{
  HOU_EXPECT_DEV(get_byte_count() % sizeof(T) == 0u);
  HOU_EXPECT(offset + elementCount <= get_size());
  typename VertexBufferT<T, dynamicStorage>::DataType dataOut(
    elementCount, T());
  gl::get_buffer_sub_data(get_handle(), static_cast<GLintptr>(offset * sizeof(T)),
    static_cast<uint>(elementCount * sizeof(T)),
    reinterpret_cast<GLvoid*>(dataOut.data()));
  return dataOut;
}



template <typename T, bool dynamicStorage>
template <bool ds, typename Enable>
void VertexBufferT<T, dynamicStorage>::setData(const span<const T>& data)
{
  HOU_EXPECT(data.size() == get_size());
  setSubData(0u, data);
}



template <typename T, bool dynamicStorage>
template <bool ds, typename Enable>
void VertexBufferT<T, dynamicStorage>::setSubData(
  uint offset, const span<const T>& data)
{
  HOU_EXPECT_DEV(get_byte_count() % sizeof(T) == 0u);
  HOU_EXPECT(offset + data.size() <= get_size());
  gl::set_buffer_sub_data(get_handle(), static_cast<GLintptr>(offset * sizeof(T)),
    static_cast<GLsizei>(data.size() * sizeof(T)),
    reinterpret_cast<const GLvoid*>(data.data()));
}

}  // namespace hou
