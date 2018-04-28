// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <typename T>
std::enable_if_t<is_contiguous_container<T>::value, T> TextStreamIn::readAll()
{
  T data(getByteCount());
  setTextPos(TextStream::TextPosition::Start);
  read(data);
  HOU_ENSURE(data.size() == getReadByteCount());
  return data;
}

}  // namespace hou
