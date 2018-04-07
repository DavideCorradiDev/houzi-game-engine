// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/aud/AudioStream.hpp"



namespace hou
{

AudioStream::AudioStream()
  : BinaryStream()
  , mFormat(AudioFormat::Mono8)
  , mSampleRate(0u)
{}



AudioStream::~AudioStream()
{}



AudioFormat AudioStream::getAudioFormat() const
{
  return mFormat;
}



uint AudioStream::getChannelCount() const
{
  return getAudioFormatChannelCount(mFormat);
}



uint AudioStream::getBytesPerSample() const
{
  return getAudioFormatBytesPerSample(mFormat);
}



uint AudioStream::getSampleRate() const
{
  return mSampleRate;
}



void AudioStream::setAudioFormat(uint channels, uint bytesPerSample)
{
  mFormat = getAudioFormatEnum(channels, bytesPerSample);
}



void AudioStream::setSampleRate(uint sampleRate)
{
  mSampleRate = sampleRate;
}

}

