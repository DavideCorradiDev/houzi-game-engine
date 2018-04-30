// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <typename T>
std::enable_if_t<is_contiguous_container<T>::value, T>
  binary_stream_in::read_all()
{
  T data(get_byte_count());
  set_byte_pos(0u);
  read(data);
  HOU_ENSURE(data.size() == get_read_byte_count());
  return data;
}

}  // namespace hou
