// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudioSource.hpp"

#include "hou/aud/AudioBuffer.hpp"



namespace hou
{

AudioSource::AudioSource(const AudioBuffer* buffer)
  : AudioSourceBase()
  , mBufferRef(nullptr)
{
  setBuffer(buffer);
}



AudioSource::AudioSource(AudioSource&& other)
  : AudioSourceBase(std::move(other))
  , mBufferRef(std::move(other.mBufferRef))
{}



AudioSource::~AudioSource()
{}



void AudioSource::setBuffer(const AudioBuffer* buffer)
{
  stop();
  mBufferRef = buffer;
  if(buffer != nullptr)
  {
    al::setSourceBuffer(getHandle(), buffer->getHandle().getName());
  }
  else
  {
    al::setSourceBuffer(getHandle(), 0);
  }
}



const AudioBuffer* AudioSource::getBuffer() const
{
  return mBufferRef;
}



AudioBufferFormat AudioSource::getFormat() const
{
  return mBufferRef == nullptr ? AudioBufferFormat::Mono8
                               : mBufferRef->getFormat();
}



uint AudioSource::getChannelCount() const
{
  return mBufferRef == nullptr ? 1u : mBufferRef->getChannelCount();
}



uint AudioSource::getBytesPerSample() const
{
  return mBufferRef == nullptr ? 1u : mBufferRef->getChannelCount();
}



uint AudioSource::getSampleRate() const
{
  return mBufferRef == nullptr ? 1u : mBufferRef->getSampleRate();
}



uint AudioSource::getSampleCount() const
{
  return mBufferRef == nullptr ? 0u : mBufferRef->getSampleCount();
}



void AudioSource::setLooping(bool looping)
{
  AudioSourceBase::setLooping(looping);
}



bool AudioSource::isLooping() const
{
  return AudioSourceBase::isLooping();
}



void AudioSource::onSetSamplePos(uint pos)
{
  AudioSourceBase::onSetSamplePos(pos);
}



uint AudioSource::onGetSamplePos() const
{
  return AudioSourceBase::onGetSamplePos();
}

}  // namespace hou
