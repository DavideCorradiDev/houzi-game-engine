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

class TestAudioBuffer
  : public TestAudBase
{
public:
  static const std::string wavStereo16FileName;
};



class TestAudioBufferDeathTest : public TestAudioBuffer {};



const std::string TestAudioBuffer::wavStereo16FileName = getDataDir()
  + u8"TestWav-Stereo-16-44100.wav";

}



TEST_F(TestAudioBuffer, Creation)
{
  std::vector<uint8_t> data{1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u};
  AudioBuffer ab(data, AudioFormat::Stereo16, 345);

  EXPECT_EQ(data.size(), ab.getByteCount());
  EXPECT_EQ(data.size()
    / (getAudioFormatChannelCount(ab.getAudioFormat())
    * getAudioFormatBytesPerSample(ab.getAudioFormat()))
    , ab.getSampleCount());
  EXPECT_EQ(AudioFormat::Stereo16, ab.getAudioFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(345, ab.getSampleRate());
}



TEST_F(TestAudioBuffer, CreationFromStream)
{
  AudioBuffer ab(std::make_unique<WavFileIn>(wavStereo16FileName));
  EXPECT_EQ(84924u, ab.getByteCount());
  EXPECT_EQ(21231u, ab.getSampleCount());
  EXPECT_EQ(AudioFormat::Stereo16, ab.getAudioFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(44100, ab.getSampleRate());
}



TEST_F(TestAudioBuffer, CreationFromExistingStream)
{
  std::unique_ptr<WavFileIn> fi
    = std::make_unique<WavFileIn>(wavStereo16FileName);
  fi->setSamplePos(12u);
  AudioBuffer ab(std::move(fi));
  EXPECT_EQ(84924u, ab.getByteCount());
  EXPECT_EQ(21231u, ab.getSampleCount());
  EXPECT_EQ(AudioFormat::Stereo16, ab.getAudioFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(44100, ab.getSampleRate());
}



TEST_F(TestAudioBuffer, MoveConstructor)
{
  std::vector<uint8_t> data{1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u};
  AudioBuffer abDummy(data, AudioFormat::Stereo16, 345);
  AudioBuffer ab(std::move(abDummy));

  EXPECT_EQ(data.size(), ab.getByteCount());
  EXPECT_EQ(data.size()
    / (getAudioFormatChannelCount(ab.getAudioFormat())
    * getAudioFormatBytesPerSample(ab.getAudioFormat()))
    , ab.getSampleCount());
  EXPECT_EQ(AudioFormat::Stereo16, ab.getAudioFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(345, ab.getSampleRate());
}



TEST_F(TestAudioBuffer, SetData)
{
  std::vector<uint8_t> dataRef1{1u, 2u, 3u, 4u};
  AudioBuffer ab(dataRef1, AudioFormat::Stereo16, 114);

  EXPECT_EQ(dataRef1.size(), ab.getByteCount());
  EXPECT_EQ(dataRef1.size()
    / (getAudioFormatChannelCount(ab.getAudioFormat())
    * getAudioFormatBytesPerSample(ab.getAudioFormat()))
    , ab.getSampleCount());
  EXPECT_EQ(AudioFormat::Stereo16, ab.getAudioFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(114, ab.getSampleRate());

  std::vector<uint8_t> dataRef2{1u, 2u, 3u, 4u, 5u, 6u};
  ab.setData(dataRef2, AudioFormat::Mono16, 228);

  EXPECT_EQ(dataRef2.size(), ab.getByteCount());
  EXPECT_EQ(dataRef2.size() / getAudioFormatBytesPerSample(ab.getAudioFormat())
    , ab.getSampleCount());
  EXPECT_EQ(AudioFormat::Mono16, ab.getAudioFormat());
  EXPECT_EQ(1u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(228, ab.getSampleRate());
}



TEST_F(TestAudioBuffer, setDataFromStream)
{
  std::vector<uint8_t> dataRef1{1u, 2u, 3u, 4u};
  AudioBuffer ab(dataRef1, AudioFormat::Stereo16, 114);

  EXPECT_EQ(dataRef1.size(), ab.getByteCount());
  EXPECT_EQ(dataRef1.size()
    / (getAudioFormatChannelCount(ab.getAudioFormat())
    * getAudioFormatBytesPerSample(ab.getAudioFormat()))
    , ab.getSampleCount());
  EXPECT_EQ(AudioFormat::Stereo16, ab.getAudioFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(114, ab.getSampleRate());

  ab.setData(std::make_unique<WavFileIn>(wavStereo16FileName));

  EXPECT_EQ(84924u, ab.getByteCount());
  EXPECT_EQ(21231u, ab.getSampleCount());
  EXPECT_EQ(AudioFormat::Stereo16, ab.getAudioFormat());
  EXPECT_EQ(2u, ab.getChannelCount());
  EXPECT_EQ(2u, ab.getBytesPerSample());
  EXPECT_EQ(44100, ab.getSampleRate());
}

