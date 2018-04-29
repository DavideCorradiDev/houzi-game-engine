// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T, bool dynamicStorage>
vertex_buffer_t<T, dynamicStorage>::vertex_buffer_t(uint size)
  : vertex_buffer(size * sizeof(T), dynamicStorage)
{}



template <typename T, bool dynamicStorage>
vertex_buffer_t<T, dynamicStorage>::vertex_buffer_t(const span<const T>& data)
  : vertex_buffer(data.size() * sizeof(T),
      reinterpret_cast<const void*>(data.data()), dynamicStorage)
{}



template <typename T, bool dynamicStorage>
vertex_buffer_t<T, dynamicStorage>::vertex_buffer_t(vertex_buffer&& other)
  : vertex_buffer(std::move(other))
{}



template <typename T, bool dynamicStorage>
uint vertex_buffer_t<T, dynamicStorage>::get_size() const
{
  HOU_EXPECT_DEV(get_byte_count() % sizeof(T) == 0u);
  return get_byte_count() / sizeof(T);
}



template <typename T, bool dynamicStorage>
typename vertex_buffer_t<T, dynamicStorage>::DataType
  vertex_buffer_t<T, dynamicStorage>::get_data() const
{
  return get_sub_data(0u, get_size());
}



template <typename T, bool dynamicStorage>
typename vertex_buffer_t<T, dynamicStorage>::DataType
  vertex_buffer_t<T, dynamicStorage>::get_sub_data(
    uint offset, uint elementCount) const
{
  HOU_EXPECT_DEV(get_byte_count() % sizeof(T) == 0u);
  HOU_EXPECT(offset + elementCount <= get_size());
  typename vertex_buffer_t<T, dynamicStorage>::DataType dataOut(
    elementCount, T());
  gl::get_buffer_sub_data(get_handle(), static_cast<GLintptr>(offset * sizeof(T)),
    static_cast<uint>(elementCount * sizeof(T)),
    reinterpret_cast<GLvoid*>(dataOut.data()));
  return dataOut;
}



template <typename T, bool dynamicStorage>
template <bool ds, typename Enable>
void vertex_buffer_t<T, dynamicStorage>::set_data(const span<const T>& data)
{
  HOU_EXPECT(data.size() == get_size());
  set_sub_data(0u, data);
}



template <typename T, bool dynamicStorage>
template <bool ds, typename Enable>
void vertex_buffer_t<T, dynamicStorage>::set_sub_data(
  uint offset, const span<const T>& data)
{
  HOU_EXPECT_DEV(get_byte_count() % sizeof(T) == 0u);
  HOU_EXPECT(offset + data.size() <= get_size());
  gl::set_buffer_sub_data(get_handle(), static_cast<GLintptr>(offset * sizeof(T)),
    static_cast<GLsizei>(data.size() * sizeof(T)),
    reinterpret_cast<const GLvoid*>(data.data()));
}

}  // namespace hou
