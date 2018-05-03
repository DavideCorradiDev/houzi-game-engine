// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T, bool DynamicStorage>
vertex_buffer_t<T, DynamicStorage>::vertex_buffer_t(uint size)
  : vertex_buffer(size * sizeof(T), DynamicStorage)
{}



template <typename T, bool DynamicStorage>
vertex_buffer_t<T, DynamicStorage>::vertex_buffer_t(const span<const T>& data)
  : vertex_buffer(data.size() * sizeof(T),
      reinterpret_cast<const void*>(data.data()), DynamicStorage)
{}



template <typename T, bool DynamicStorage>
vertex_buffer_t<T, DynamicStorage>::vertex_buffer_t(vertex_buffer&& other)
  : vertex_buffer(std::move(other))
{}



template <typename T, bool DynamicStorage>
uint vertex_buffer_t<T, DynamicStorage>::get_size() const
{
  DEPRECATED_HOU_EXPECT_DEV(get_byte_count() % sizeof(T) == 0u);
  return get_byte_count() / sizeof(T);
}



template <typename T, bool DynamicStorage>
typename vertex_buffer_t<T, DynamicStorage>::data_type
  vertex_buffer_t<T, DynamicStorage>::get_data() const
{
  return get_sub_data(0u, get_size());
}



template <typename T, bool DynamicStorage>
typename vertex_buffer_t<T, DynamicStorage>::data_type
  vertex_buffer_t<T, DynamicStorage>::get_sub_data(
    uint offset, uint element_count) const
{
  DEPRECATED_HOU_EXPECT_DEV(get_byte_count() % sizeof(T) == 0u);
  DEPRECATED_HOU_EXPECT(offset + element_count <= get_size());
  typename vertex_buffer_t<T, DynamicStorage>::data_type dataOut(
    element_count, T());
  gl::get_buffer_sub_data(get_handle(),
    static_cast<GLintptr>(offset * sizeof(T)),
    static_cast<uint>(element_count * sizeof(T)),
    reinterpret_cast<GLvoid*>(dataOut.data()));
  return dataOut;
}



template <typename T, bool DynamicStorage>
template <bool DS, typename Enable>
void vertex_buffer_t<T, DynamicStorage>::set_data(const span<const T>& data)
{
  DEPRECATED_HOU_EXPECT(data.size() == get_size());
  set_sub_data(0u, data);
}



template <typename T, bool DynamicStorage>
template <bool DS, typename Enable>
void vertex_buffer_t<T, DynamicStorage>::set_sub_data(
  uint offset, const span<const T>& data)
{
  DEPRECATED_HOU_EXPECT_DEV(get_byte_count() % sizeof(T) == 0u);
  DEPRECATED_HOU_EXPECT(offset + data.size() <= get_size());
  gl::set_buffer_sub_data(get_handle(),
    static_cast<GLintptr>(offset * sizeof(T)),
    static_cast<GLsizei>(data.size() * sizeof(T)),
    reinterpret_cast<const GLvoid*>(data.data()));
}

}  // namespace hou
