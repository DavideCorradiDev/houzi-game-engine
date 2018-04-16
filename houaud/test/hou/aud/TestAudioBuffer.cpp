// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/TestAudBase.hpp"
#include "hou/aud/TestData.hpp"

#include "hou/aud/AudioBuffer.hpp"
#include "hou/aud/WavFileIn.hpp"

using namespace hou;



namespace
{

class TestAudioBuffer : public TestAudBase
{
public:
  static const std::string wavStereo16FileName;
};



class TestAudioBufferDeathTest : public TestAudioBuffer
{};



const std::string TestAudioBuffer::wavStereo16FileName
  = getDataDir() + u8"TestWav-Stereo-16-44100.wav";

}  // namespace



TEST_F(TestAudioBuffer, DefaultConstructor)
{
  AudioBuffer ab;

  EXPECT_NE(0u, ab.getHandle().getName());
  EXPECT_EQ(2u, ab.getByteCount());
  EXPECT_EQ(1u, ab.getSampleCount());
  EXPECT_EQ(AudioBufferFormat::Mono16, ab.getFormat());
  EXPECT_EQ(1u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(1, ab.getSampleRate());
}



TEST_F(TestAudioBuffer, DataConstructor)
{
  std::vector<uint8_t> data{1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u};
  AudioBuffer ab(data, AudioBufferFormat::Stereo16, 345);

  EXPECT_NE(0u, ab.getHandle().getName());
  EXPECT_EQ(data.size(), ab.getByteCount());
  EXPECT_EQ(data.size()
      / (getAudioBufferFormatChannelCount(ab.getFormat())
          * getAudioBufferFormatBytesPerSample(ab.getFormat())),
    ab.getSampleCount());
  EXPECT_EQ(AudioBufferFormat::Stereo16, ab.getFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(345, ab.getSampleRate());
}



TEST_F(TestAudioBuffer, StreamConstructor)
{
  AudioBuffer ab(std::make_unique<WavFileIn>(wavStereo16FileName));

  EXPECT_NE(0u, ab.getHandle().getName());
  EXPECT_EQ(84924u, ab.getByteCount());
  EXPECT_EQ(21231u, ab.getSampleCount());
  EXPECT_EQ(AudioBufferFormat::Stereo16, ab.getFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(44100, ab.getSampleRate());
}



TEST_F(TestAudioBuffer, ExistingStreamConstructor)
{
  std::unique_ptr<WavFileIn> fi
    = std::make_unique<WavFileIn>(wavStereo16FileName);
  fi->setSamplePos(12u);
  AudioBuffer ab(std::move(fi));

  EXPECT_NE(0u, ab.getHandle().getName());
  EXPECT_EQ(84924u, ab.getByteCount());
  EXPECT_EQ(21231u, ab.getSampleCount());
  EXPECT_EQ(AudioBufferFormat::Stereo16, ab.getFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(44100, ab.getSampleRate());
}



TEST_F(TestAudioBuffer, MoveConstructor)
{
  std::vector<uint8_t> data{1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u};
  AudioBuffer abDummy(data, AudioBufferFormat::Stereo16, 345);
  ALuint nameRef = abDummy.getHandle().getName();
  AudioBuffer ab(std::move(abDummy));

  EXPECT_EQ(0u, abDummy.getHandle().getName());
  EXPECT_EQ(nameRef, ab.getHandle().getName());
  EXPECT_EQ(data.size(), ab.getByteCount());
  EXPECT_EQ(data.size()
      / (getAudioBufferFormatChannelCount(ab.getFormat())
          * getAudioBufferFormatBytesPerSample(ab.getFormat())),
    ab.getSampleCount());
  EXPECT_EQ(AudioBufferFormat::Stereo16, ab.getFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(345, ab.getSampleRate());
}



TEST_F(TestAudioBuffer, SetData)
{
  std::vector<uint8_t> dataRef1{1u, 2u, 3u, 4u};
  AudioBuffer ab(dataRef1, AudioBufferFormat::Stereo16, 114);

  EXPECT_EQ(dataRef1.size(), ab.getByteCount());
  EXPECT_EQ(dataRef1.size()
      / (getAudioBufferFormatChannelCount(ab.getFormat())
          * getAudioBufferFormatBytesPerSample(ab.getFormat())),
    ab.getSampleCount());
  EXPECT_EQ(AudioBufferFormat::Stereo16, ab.getFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(114, ab.getSampleRate());

  std::vector<uint8_t> dataRef2{1u, 2u, 3u, 4u, 5u, 6u};
  ab.setData(dataRef2, AudioBufferFormat::Mono16, 228);

  EXPECT_EQ(dataRef2.size(), ab.getByteCount());
  EXPECT_EQ(
    dataRef2.size() / getAudioBufferFormatBytesPerSample(ab.getFormat()),
    ab.getSampleCount());
  EXPECT_EQ(AudioBufferFormat::Mono16, ab.getFormat());
  EXPECT_EQ(1u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(228, ab.getSampleRate());
}



TEST_F(TestAudioBuffer, setDataFromStream)
{
  std::vector<uint8_t> dataRef1{1u, 2u, 3u, 4u};
  AudioBuffer ab(dataRef1, AudioBufferFormat::Stereo16, 114);

  EXPECT_EQ(dataRef1.size(), ab.getByteCount());
  EXPECT_EQ(dataRef1.size()
      / (getAudioBufferFormatChannelCount(ab.getFormat())
          * getAudioBufferFormatBytesPerSample(ab.getFormat())),
    ab.getSampleCount());
  EXPECT_EQ(AudioBufferFormat::Stereo16, ab.getFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(114, ab.getSampleRate());

  ab.setData(std::make_unique<WavFileIn>(wavStereo16FileName));

  EXPECT_EQ(84924u, ab.getByteCount());
  EXPECT_EQ(21231u, ab.getSampleCount());
  EXPECT_EQ(AudioBufferFormat::Stereo16, ab.getFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(44100, ab.getSampleRate());
}



TEST_F(TestAudioBuffer, GetMono8FormatMeasures)
{
  // Note: the implementation might convert the format to a different one.
  // Bits per sample might change from 8 to 16. Samples will then be padded and
  // the size of the buffer will increase.
  std::vector<uint8_t> data{1, 2, 3, 4};
  AudioBuffer b(data, AudioBufferFormat::Mono8, 144);
  EXPECT_EQ(b.getBytesPerSample() == 1u ? AudioBufferFormat::Mono8
                                        : AudioBufferFormat::Mono16,
    b.getFormat());
  EXPECT_EQ(1u, b.getChannelCount());
  EXPECT_TRUE(b.getBytesPerSample() == 1u || b.getBytesPerSample() == 2u);
  EXPECT_EQ(data.size() * b.getBytesPerSample(), b.getByteCount());
}



TEST_F(TestAudioBuffer, GetMono16FormatMeasures)
{
  std::vector<uint8_t> data{1, 2, 3, 4};
  AudioBuffer b(data, AudioBufferFormat::Mono16, 144);
  EXPECT_EQ(AudioBufferFormat::Mono16, b.getFormat());
  EXPECT_EQ(1u, b.getChannelCount());
  EXPECT_EQ(2u, b.getBytesPerSample());
  EXPECT_EQ(data.size(), b.getByteCount());
}



TEST_F(TestAudioBuffer, GetStereo8FormatMeasures)
{
  // Note: the implementation might convert the format to a different one.
  // Bits per sample might change from 8 to 16. Samples will then be padded and
  // the size of the buffer will increase.
  std::vector<uint8_t> data{1, 2, 3, 4};
  AudioBuffer b(data, AudioBufferFormat::Stereo8, 144);
  EXPECT_EQ(b.getBytesPerSample() == 1u ? AudioBufferFormat::Stereo8
                                        : AudioBufferFormat::Stereo16,
    b.getFormat());
  EXPECT_EQ(2u, b.getChannelCount());
  EXPECT_TRUE(b.getBytesPerSample() == 1u || b.getBytesPerSample() == 2u);
  EXPECT_EQ(data.size() * b.getBytesPerSample(), b.getByteCount());
}



TEST_F(TestAudioBuffer, GetStereo16FormatMeasures)
{
  std::vector<uint8_t> data{1, 2, 3, 4};
  AudioBuffer b(data, AudioBufferFormat::Stereo16, 144);
  EXPECT_EQ(AudioBufferFormat::Stereo16, b.getFormat());
  EXPECT_EQ(2u, b.getChannelCount());
  EXPECT_EQ(2u, b.getBytesPerSample());
  EXPECT_EQ(data.size(), b.getByteCount());
}
