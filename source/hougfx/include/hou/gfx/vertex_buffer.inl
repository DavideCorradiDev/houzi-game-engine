// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T, bool DynamicStorage>
vertex_buffer_t<T, DynamicStorage>::vertex_buffer_t(size_t size)
  : vertex_buffer(size * sizeof(T), DynamicStorage)
{}



template <typename T, bool DynamicStorage>
vertex_buffer_t<T, DynamicStorage>::vertex_buffer_t(const span<const T>& data)
  : vertex_buffer(data.size() * sizeof(T),
      reinterpret_cast<const void*>(data.data()), DynamicStorage)
{}



template <typename T, bool DynamicStorage>
size_t vertex_buffer_t<T, DynamicStorage>::get_size() const
{
  HOU_DEV_ASSERT(get_byte_count() % sizeof(T) == 0u);
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
    size_t offset, size_t element_count) const
{
  HOU_DEV_ASSERT(get_byte_count() % sizeof(T) == 0u);
  HOU_PRECOND(offset + element_count <= get_size());
  typename vertex_buffer_t<T, DynamicStorage>::data_type data_out(
    element_count, T());
  gl::get_buffer_sub_data(get_handle(),
    narrow_cast<GLintptr>(offset * sizeof(T)),
    narrow_cast<uint>(element_count * sizeof(T)),
    reinterpret_cast<GLvoid*>(data_out.data()));
  return data_out;
}



template <typename T, bool DynamicStorage>
template <bool DS, typename Enable>
void vertex_buffer_t<T, DynamicStorage>::set_data(const span<const T>& data)
{
  HOU_PRECOND(data.size() == get_size());
  set_sub_data(0u, data);
}



template <typename T, bool DynamicStorage>
template <bool DS, typename Enable>
void vertex_buffer_t<T, DynamicStorage>::set_sub_data(
  size_t offset, const span<const T>& data)
{
  HOU_DEV_ASSERT(get_byte_count() % sizeof(T) == 0u);
  HOU_PRECOND(offset + data.size() <= get_size());
  gl::set_buffer_sub_data(get_handle(),
    narrow_cast<GLintptr>(offset * sizeof(T)),
    narrow_cast<GLsizei>(data.size() * sizeof(T)),
    reinterpret_cast<const GLvoid*>(data.data()));
}

}  // namespace hou
