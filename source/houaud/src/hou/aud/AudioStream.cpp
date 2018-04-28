// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudioStream.hpp"



namespace hou
{

AudioStream::AudioStream()
  : BinaryStream()
  , mFormat(AudioBufferFormat::Mono8)
  , mSampleRate(0u)
{}



AudioStream::~AudioStream()
{}



AudioBufferFormat AudioStream::getFormat() const
{
  return mFormat;
}



uint AudioStream::getChannelCount() const
{
  return getAudioBufferFormatChannelCount(mFormat);
}



uint AudioStream::getBytesPerSample() const
{
  return getAudioBufferFormatBytesPerSample(mFormat);
}



uint AudioStream::getSampleRate() const
{
  return mSampleRate;
}



void AudioStream::setFormat(uint channels, uint bytesPerSample)
{
  mFormat = getAudioBufferFormatEnum(channels, bytesPerSample);
}



void AudioStream::setSampleRate(uint sampleRate)
{
  mSampleRate = sampleRate;
}

}  // namespace hou
