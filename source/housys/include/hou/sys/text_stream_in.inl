// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <typename T>
std::enable_if_t<is_contiguous_container<T>::value, T> text_stream_in::read_all()
{
  T data(get_byte_count());
  set_text_pos(text_stream::text_position::start);
  read(data);
  DEPRECATED_HOU_ENSURE(data.size() == get_read_byte_count());
  return data;
}

}  // namespace hou
