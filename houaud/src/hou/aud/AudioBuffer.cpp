// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudioBuffer.hpp"

#include "hou/aud/AudioStreamIn.hpp"



namespace hou
{

namespace
{
static constexpr uint bitsPerByte = 8u;
}



AudioBuffer::AudioBuffer()
  : AudioBuffer(std::vector<uint8_t>(2u, 0u), AudioBufferFormat::Mono16, 1u)
{}



AudioBuffer::AudioBuffer(
  const Span<const uint8_t>& data, AudioBufferFormat format, int smlRate)
  : NonCopyable()
  , mHandle(al::BufferHandle::generate())
{
  setData(data, format, smlRate);
}



AudioBuffer::AudioBuffer(
  std::vector<uint8_t>&& data, AudioBufferFormat format, int smpRate)
  : AudioBuffer(Span<const uint8_t>(data), format, smpRate)
{}



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



AudioBufferFormat AudioBuffer::getFormat() const
{
  return getAudioBufferFormatEnum(getChannelCount(), getBytesPerSample());
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
  const Span<const uint8_t>& data, AudioBufferFormat format, int smlRate)
{
  HOU_EXPECT_DEV(sizeof(uint8_t) == 1u);
  al::setBufferData(mHandle, static_cast<ALenum>(format),
    reinterpret_cast<ALvoid*>(const_cast<uint8_t*>(data.data())),
    static_cast<ALsizei>(data.size()), static_cast<ALsizei>(smlRate));
}



void AudioBuffer::setData(
  std::vector<uint8_t>&& data, AudioBufferFormat format, int smlRate)
{
  setData(Span<const uint8_t>(data), format, smlRate);
}



void AudioBuffer::setData(NotNull<std::unique_ptr<AudioStreamIn>> audioStream)
{
  setData(audioStream->readAll<std::vector<uint8_t>>(),
    audioStream->getFormat(), audioStream->getSampleRate());
}

}  // namespace hou
