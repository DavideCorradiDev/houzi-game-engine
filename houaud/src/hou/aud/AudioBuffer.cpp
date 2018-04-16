// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudioBuffer.hpp"

#include "hou/aud/AudioStreamIn.hpp"

#include "hou/al/AlBufferFormat.hpp"



namespace hou
{

namespace
{
static constexpr uint bitsPerByte = 8u;
}



AudioBuffer::AudioBuffer()
  : AudioBuffer(std::vector<uint8_t>(2u, 0u), AudioFormat::Mono16, 1u)
{}



AudioBuffer::AudioBuffer(
  const std::vector<uint8_t>& data, AudioFormat format, int smlRate)
  : NonCopyable()
  , mHandle(al::BufferHandle::generate())
{
  setData(data, format, smlRate);
}



AudioBuffer::AudioBuffer(NotNull<std::unique_ptr<AudioStreamIn>> audioStream)
  : NonCopyable()
  , mHandle(al::BufferHandle::generate())
{
  setData(std::move(audioStream));
}



AudioBuffer::AudioBuffer(AudioBuffer&& other)
  : mHandle(std::move(other.mHandle))
{}



const al::BufferHandle& AudioBuffer::getHandle() const
{
  return mHandle;
}



AudioFormat AudioBuffer::getAudioFormat() const
{
  return alBufferFormatToAudioFormat(
    al::getBufferFormatEnum(getChannelCount(), getBytesPerSample()));
}



uint AudioBuffer::getBytesPerSample() const
{
  return static_cast<uint>(al::getBufferBits(mHandle) / bitsPerByte);
}



uint AudioBuffer::getChannelCount() const
{
  return static_cast<uint>(al::getBufferChannels(mHandle));
}



int AudioBuffer::getSampleRate() const
{
  return static_cast<int>(al::getBufferFrequency(mHandle));
}



uint AudioBuffer::getByteCount() const
{
  return static_cast<uint>(al::getBufferSize(mHandle));
}



uint AudioBuffer::getSampleCount() const
{
  HOU_EXPECT_DEV(getBytesPerSample() != 0u);
  HOU_EXPECT_DEV(
    getByteCount() % (getChannelCount() * getBytesPerSample()) == 0);
  return getByteCount() / (getChannelCount() * getBytesPerSample());
}



void AudioBuffer::setData(
  const std::vector<uint8_t>& data, AudioFormat format, int smlRate)
{
  HOU_EXPECT_DEV(sizeof(uint8_t) == 1u);
  al::setBufferData(mHandle, audioBufferFormatToAlBufferFormat(format),
    reinterpret_cast<ALvoid*>(const_cast<uint8_t*>(data.data())),
    static_cast<ALsizei>(data.size()), static_cast<ALsizei>(smlRate));
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

}  // namespace hou
