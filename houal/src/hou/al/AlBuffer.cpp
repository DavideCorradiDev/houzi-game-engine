// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/al/AlBuffer.hpp"

#include "hou/cor/Error.hpp"



namespace hou
{

namespace al
{

Buffer::Buffer()
  : NonCopyable()
  , mHandle(al::BufferHandle::generate())
{}



Buffer::Buffer(Buffer&& other)
  : mHandle(std::move(other.mHandle))
{}



const BufferHandle& Buffer::getHandle() const
{
  return mHandle;
}



ALint Buffer::getFrequency() const
{
  return getBufferFrequency(mHandle);
}



al::BufferFormat Buffer::getFormat() const
{
  return getBufferFormatEnum(getChannels(), getBits() / 8u);
}



ALint Buffer::getBits() const
{
  return getBufferBits(mHandle);
}



ALint Buffer::getChannels() const
{
  return getBufferChannels(mHandle);
}



ALint Buffer::getSize() const
{
  return getBufferSize(mHandle);
}

}

}

