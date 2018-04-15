// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudioBuffer.hpp"

#include "hou/aud/AudioStreamIn.hpp"

#include "hou/al/AlBufferFormat.hpp"



namespace hou
{

AudioBuffer::AudioBuffer(const std::vector<uint8_t>& data, AudioFormat format
  , int smlRate)
  : NonCopyable()
  , mAlBuffer(data, audioBufferFormatToAlBufferFormat(format), smlRate)
{}



AudioBuffer::AudioBuffer(NotNull<std::unique_ptr<AudioStreamIn>> audioStream)
  : NonCopyable()
  , mAlBuffer()
{
  setData(std::move(audioStream));
}



AudioBuffer::AudioBuffer(AudioBuffer&& other)
  : mAlBuffer(std::move(other.mAlBuffer))
{}



AudioFormat AudioBuffer::getAudioFormat() const
{
  return alBufferFormatToAudioFormat(mAlBuffer.getFormat());
}



uint AudioBuffer::getBytesPerSample() const
{
  return static_cast<uint>(mAlBuffer.getBits() / 8u);
}



uint AudioBuffer::getChannelCount() const
{
  return static_cast<uint>(mAlBuffer.getChannels());
}



int AudioBuffer::getSampleRate() const
{
  return static_cast<int>(mAlBuffer.getFrequency());
}



void AudioBuffer::setData(const std::vector<uint8_t>& data, AudioFormat format
  , int smlRate)
{
  mAlBuffer.setData(data, audioBufferFormatToAlBufferFormat(format), smlRate);
}



size_t AudioBuffer::getByteCount() const
{
  return static_cast<size_t>(mAlBuffer.getSize());
}



size_t AudioBuffer::getSampleCount() const
{
  HOU_EXPECT(getBytesPerSample() != 0u);
  HOU_EXPECT_DEV(getByteCount() % (getChannelCount() * getBytesPerSample()) == 0);
  return getByteCount() / (getChannelCount() * getBytesPerSample());
}



void AudioBuffer::setData(NotNull<std::unique_ptr<AudioStreamIn>> audioStream)
{
  audioStream->setBytePos(0u);
  std::vector<uint8_t> data;
  data.resize(audioStream->getByteCount());
  audioStream->read(data);
  HOU_ENSURE(data.size() == audioStream->getReadByteCount());
  setData(data, audioStream->getAudioFormat(), audioStream->getSampleRate());
}

}

