// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_AL_AL_BUFFER_HPP
#define HOU_AL_AL_BUFFER_HPP

#include "hou/al/AlExport.hpp"
#include "hou/cor/NonCopyable.hpp"

#include "hou/al/AlBufferHandle.hpp"

#include <vector>



namespace hou
{

namespace al
{

class HOU_AL_API Buffer
  : public NonCopyable
{
public:
  Buffer();
  template <typename T>
    Buffer(const std::vector<T>& data, BufferFormat format, ALsizei freq);
  Buffer(Buffer&& other);

  const BufferHandle& getHandle() const;

  ALint getFrequency() const;
  al::BufferFormat getFormat() const;
  ALint getBits() const;
  ALint getChannels() const;
  ALint getSize() const;
  template <typename T>
    void setData(const std::vector<T>& data, BufferFormat format, ALsizei freq);

private:
  BufferHandle mHandle;
};

}

}



#include "hou/al/AlBuffer.inl"

#endif

