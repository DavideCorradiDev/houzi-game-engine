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
  const span<const uint8_t>& data, AudioBufferFormat format, int smlRate)
  : non_copyable()
  , m_handle(al::buffer_handle::generate())
{
  setData(data, format, smlRate);
}



AudioBuffer::AudioBuffer(
  std::vector<uint8_t>&& data, AudioBufferFormat format, int smpRate)
  : AudioBuffer(span<const uint8_t>(data), format, smpRate)
{}



AudioBuffer::AudioBuffer(AudioStreamIn& audioStream)
  : non_copyable()
  , m_handle(al::buffer_handle::generate())
{
  setData(audioStream);
}



AudioBuffer::AudioBuffer(AudioStreamIn&& audioStream)
  : non_copyable()
  , m_handle(al::buffer_handle::generate())
{
  setData(audioStream);
}



AudioBuffer::AudioBuffer(AudioBuffer&& other)
  : m_handle(std::move(other.m_handle))
{}



const al::buffer_handle& AudioBuffer::getHandle() const
{
  return m_handle;
}



AudioBufferFormat AudioBuffer::get_format() const
{
  return getAudioBufferFormatEnum(getChannelCount(), getBytesPerSample());
}



uint AudioBuffer::getBytesPerSample() const
{
  return static_cast<uint>(al::getBufferBits(m_handle) / bitsPerByte);
}



uint AudioBuffer::getChannelCount() const
{
  return static_cast<uint>(al::getBufferChannels(m_handle));
}



int AudioBuffer::getSampleRate() const
{
  return static_cast<int>(al::getBufferFrequency(m_handle));
}



uint AudioBuffer::get_byte_count() const
{
  return static_cast<uint>(al::getBufferSize(m_handle));
}



uint AudioBuffer::get_sample_count() const
{
  HOU_EXPECT_DEV(getBytesPerSample() != 0u);
  HOU_EXPECT_DEV(
    get_byte_count() % (getChannelCount() * getBytesPerSample()) == 0);
  return get_byte_count() / (getChannelCount() * getBytesPerSample());
}



void AudioBuffer::setData(
  const span<const uint8_t>& data, AudioBufferFormat format, int smlRate)
{
  HOU_EXPECT_DEV(sizeof(uint8_t) == 1u);
  al::setBufferData(m_handle, static_cast<ALenum>(format),
    reinterpret_cast<ALvoid*>(const_cast<uint8_t*>(data.data())),
    static_cast<ALsizei>(data.size()), static_cast<ALsizei>(smlRate));
}



void AudioBuffer::setData(
  std::vector<uint8_t>&& data, AudioBufferFormat format, int smlRate)
{
  setData(span<const uint8_t>(data), format, smlRate);
}



void AudioBuffer::setData(AudioStreamIn& audioStream)
{
  setData(audioStream.read_all<std::vector<uint8_t>>(), audioStream.get_format(),
    audioStream.getSampleRate());
}



void AudioBuffer::setData(AudioStreamIn&& audioStream)
{
  setData(audioStream.read_all<std::vector<uint8_t>>(), audioStream.get_format(),
    audioStream.getSampleRate());
}

}  // namespace hou
