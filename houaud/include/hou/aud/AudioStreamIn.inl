// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <typename T>
std::enable_if_t<isContiguousContainer<T>::value, T> AudioStreamIn::readAll()
{
  T data(getByteCount());
  setBytePos(0u);
  read(data);
  HOU_ENSURE(data.size() == getReadByteCount());
  return data;
}

}  // namespace hou

