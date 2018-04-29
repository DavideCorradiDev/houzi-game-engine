// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/MemoryAudioSource.hpp"

#include "hou/aud/AudioBuffer.hpp"



namespace hou
{

MemoryAudioSource::MemoryAudioSource(const AudioBuffer* buffer)
  : AudioSource()
  , mBufferRef(nullptr)
{
  setBuffer(buffer);
}



MemoryAudioSource::MemoryAudioSource(MemoryAudioSource&& other)
  : AudioSource(std::move(other))
  , mBufferRef(std::move(other.mBufferRef))
{}



MemoryAudioSource::~MemoryAudioSource()
{}



void MemoryAudioSource::setBuffer(const AudioBuffer* buffer)
{
  stop();
  mBufferRef = buffer;
  if(buffer != nullptr)
  {
    al::setSourceBuffer(get_handle(), buffer->get_handle().get_name());
  }
  else
  {
    al::setSourceBuffer(get_handle(), 0);
  }
}



const AudioBuffer* MemoryAudioSource::getBuffer() const
{
  return mBufferRef;
}



AudioBufferFormat MemoryAudioSource::get_format() const
{
  return mBufferRef == nullptr ? AudioBufferFormat::Mono8
                               : mBufferRef->get_format();
}



uint MemoryAudioSource::getChannelCount() const
{
  return mBufferRef == nullptr ? 1u : mBufferRef->getChannelCount();
}



uint MemoryAudioSource::getBytesPerSample() const
{
  return mBufferRef == nullptr ? 1u : mBufferRef->getChannelCount();
}



uint MemoryAudioSource::getSampleRate() const
{
  return mBufferRef == nullptr ? 1u : mBufferRef->getSampleRate();
}



uint MemoryAudioSource::get_sample_count() const
{
  return mBufferRef == nullptr ? 0u : mBufferRef->get_sample_count();
}



void MemoryAudioSource::setLooping(bool looping)
{
  AudioSource::setLooping(looping);
}



bool MemoryAudioSource::isLooping() const
{
  return AudioSource::isLooping();
}



void MemoryAudioSource::onSetSamplePos(uint pos)
{
  AudioSource::onSetSamplePos(pos);
}



uint MemoryAudioSource::onGetSamplePos() const
{
  return AudioSource::onGetSamplePos();
}

}  // namespace hou
