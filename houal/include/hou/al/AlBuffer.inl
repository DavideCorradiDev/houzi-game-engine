// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

namespace al
{
template <typename T>
  Buffer::Buffer(const std::vector<T>& data, BufferFormat format, ALsizei freq)
  : Buffer()
{
  setData(data, format, freq);
}



template <typename T>
  void Buffer::setData(const std::vector<T>& data, BufferFormat format
  , ALsizei freq)
{
  ALsizei dataSizeBytes = data.size() * sizeof(T);
  setBufferData(mHandle, format
    , reinterpret_cast<ALvoid*>(const_cast<T*>(data.data())), dataSizeBytes
    , freq);
}

}

}

