// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/TestData.hpp"

#include "hou/aud/AudError.hpp"
#include "hou/aud/OggFileIn.hpp"

#include "hou/sys/file.hpp"
#include "hou/sys/sys_error.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestOggFileIn
  : public Test
{
public:
  // Note: OGG files are always read with 16 bits per sample in the Houzi library.
  // For this reason there are no tests involving buffers with 8 bits per sample.
  static const std::string mono16UnicodeFileName;
  static const std::string mono16FileName;
  static const std::string stereo16FileName;
  static const std::string lowSampleRateFileName;
  static const std::string wavFileName;
};



class TestOggFileInDeathTest : public TestOggFileIn {};



const std::string TestOggFileIn::mono16UnicodeFileName = getDataDir()
  + u8"TestOgg\U00004f60\U0000597d.ogg";
const std::string TestOggFileIn::mono16FileName = getDataDir()
  + u8"TestOgg-Mono-16-44100.ogg";
const std::string TestOggFileIn::stereo16FileName = getDataDir()
  + u8"TestOgg-Stereo-16-44100.ogg";
const std::string TestOggFileIn::lowSampleRateFileName = getDataDir()
  + u8"TestOgg-Mono-16-22050.ogg";
const std::string TestOggFileIn::wavFileName = getDataDir()
  + u8"TestWav-Mono-16-44100.wav";

}



TEST_F(TestOggFileIn, CheckSuccess)
{
  EXPECT_TRUE(OggFileIn::check(mono16UnicodeFileName));
}



TEST_F(TestOggFileIn, CheckFailureInvalidFormat)
{
  EXPECT_FALSE(OggFileIn::check(wavFileName));
}



TEST_F(TestOggFileInDeathTest, CheckFailureInvalidFile)
{
  std::string invalidFileName = u8"Invalidfile";
  HOU_EXPECT_ERROR(OggFileIn::check(invalidFileName), std::runtime_error
    , format_string(get_text(sys_error::file_open), invalidFileName.c_str()));
}



TEST_F(TestOggFileIn, PathConstructor)
{
  OggFileIn fi(mono16UnicodeFileName);
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(42206u, fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(AudioBufferFormat::Mono16, fi.get_format());
  EXPECT_EQ(1u, fi.getChannelCount());
  EXPECT_EQ(2u, fi.getBytesPerSample());
  EXPECT_EQ(44100u, fi.getSampleRate());
  EXPECT_EQ(21103u, fi.get_sample_count());
  EXPECT_EQ(0, fi.getSamplePos());
}



TEST_F(TestOggFileInDeathTest, PathConstructorFailureFileNotExisting)
{
  std::string invalidFileName = u8"InvalidFileName";
  HOU_EXPECT_ERROR(OggFileIn fi(invalidFileName), std::runtime_error
    , format_string(get_text(sys_error::file_open), invalidFileName.c_str()));
}



TEST_F(TestOggFileInDeathTest, PathConstructorFailureInvalidOggFile)
{
  static constexpr size_t stringSize = 4u;
  struct OggMetadata
  {
    char id[stringSize];
    uint32_t chunkSize;
    char form[stringSize];
    char sc1Id[stringSize];
    uint32_t sc1Size;
    uint16_t format;
    uint16_t channels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char sc2Id[stringSize];
    uint32_t sc2Size;
  };

  std::string dummyOggFileName = getOutputDir() + u8"dummyOggFile.wav";

  {
    file dummyOggFile(dummyOggFileName, file_open_mode::write, file_type::binary);
    OggMetadata data;
    data.id[0] = 'F';
    data.id[1] = 'a';
    data.id[2] = 'K';
    data.id[3] = 'E';
    dummyOggFile.write(&data, 1u);
  }

  HOU_EXPECT_ERROR(OggFileIn fi(dummyOggFileName), std::runtime_error
    , format_string(get_text(AudError::OggInvalidHeader)
    , dummyOggFileName.c_str()));

  remove_dir(dummyOggFileName);
}



TEST_F(TestOggFileInDeathTest, PathConstructorFailureNoOggHeader)
{
  std::string dummyOggFileName = getOutputDir() + u8"dummyOggFile.wav";

  {
    file dummyOggFile(dummyOggFileName, file_open_mode::write, file_type::binary);
  }

  HOU_EXPECT_ERROR(OggFileIn fi(dummyOggFileName), std::runtime_error
    , format_string(get_text(AudError::OggInvalidHeader)
    , dummyOggFileName.c_str()));

  remove_dir(dummyOggFileName);
}



TEST_F(TestOggFileIn, MoveConstructor)
{
  OggFileIn fiDummy(mono16UnicodeFileName);
  OggFileIn fi(std::move(fiDummy));
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(42206u, fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(AudioBufferFormat::Mono16, fi.get_format());
  EXPECT_EQ(1u, fi.getChannelCount());
  EXPECT_EQ(2u, fi.getBytesPerSample());
  EXPECT_EQ(44100u, fi.getSampleRate());
  EXPECT_EQ(21103u, fi.get_sample_count());
  EXPECT_EQ(0, fi.getSamplePos());
}



TEST_F(TestOggFileIn, AudioBufferFormatAttributes)
{
  OggFileIn fiMono16(mono16FileName);
  OggFileIn fiStereo16(stereo16FileName);

  EXPECT_EQ(AudioBufferFormat::Mono16, fiMono16.get_format());
  EXPECT_EQ(1u, fiMono16.getChannelCount());
  EXPECT_EQ(2u, fiMono16.getBytesPerSample());
  EXPECT_EQ(AudioBufferFormat::Stereo16, fiStereo16.get_format());
  EXPECT_EQ(2u, fiStereo16.getChannelCount());
  EXPECT_EQ(2u, fiStereo16.getBytesPerSample());
}



TEST_F(TestOggFileIn, SampleRateAttributes)
{
  OggFileIn fiNormalRate(mono16FileName);
  OggFileIn fiLowRate(lowSampleRateFileName);

  EXPECT_EQ(44100u, fiNormalRate.getSampleRate());
  EXPECT_EQ(22050u, fiLowRate.getSampleRate());
}



TEST_F(TestOggFileIn, GetSampleCount)
{
  OggFileIn fiMono16(mono16FileName);
  OggFileIn fiStereo16(stereo16FileName);

  EXPECT_EQ(21231u, fiMono16.get_sample_count());
  EXPECT_EQ(21231u, fiStereo16.get_sample_count());

  EXPECT_EQ(42462u, fiMono16.get_byte_count());
  EXPECT_EQ(84924u, fiStereo16.get_byte_count());
}



TEST_F(TestOggFileIn, SetBytePos)
{
  OggFileIn fi(mono16FileName);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(6);
  EXPECT_EQ(6, fi.get_byte_pos());
  fi.set_byte_pos(0);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(fi.get_byte_count());
  EXPECT_EQ(static_cast<OggFileIn::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
}



TEST_F(TestOggFileInDeathTest, SetBytePosErrorPositionInSample)
{
  OggFileIn fi(mono16FileName);
  HOU_EXPECT_ERROR(fi.set_byte_pos(3), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(fi.set_byte_pos(fi.get_byte_count() + 3), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestOggFileInDeathTest, SetBytePosErrorInvalidPosition)
{
  OggFileIn fi(mono16FileName);
  HOU_EXPECT_ERROR(fi.set_byte_pos(-2), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(fi.set_byte_pos(fi.get_byte_count() + 2), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestOggFileIn, MoveBytePos)
{
  OggFileIn fi(mono16FileName);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(6);
  EXPECT_EQ(6, fi.get_byte_pos());
  fi.move_byte_pos(-2);
  EXPECT_EQ(4, fi.get_byte_pos());
  fi.move_byte_pos(-4);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(fi.get_byte_count());
  EXPECT_EQ(static_cast<OggFileIn::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
}



TEST_F(TestOggFileInDeathTest, MoveBytePosErrorPositionInSample)
{
  OggFileIn fi(mono16FileName);
  fi.move_byte_pos(4);
  HOU_EXPECT_ERROR(fi.move_byte_pos(3), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(fi.move_byte_pos(fi.get_byte_count() + 3), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestOggFileInDeathTest, MoveBytePosErrorInvalidPosition)
{
  OggFileIn fi(mono16FileName);
  fi.move_byte_pos(4);
  HOU_EXPECT_ERROR(fi.move_byte_pos(-6), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(fi.move_byte_pos(fi.get_byte_count() - 2), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestOggFileIn, SetSamplePosMono16)
{
  OggFileIn fi(mono16FileName);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.getSamplePos());
  fi.setSamplePos(3);
  EXPECT_EQ(6, fi.get_byte_pos());
  EXPECT_EQ(3, fi.getSamplePos());
  fi.setSamplePos(fi.get_sample_count());
  EXPECT_EQ(static_cast<OggFileIn::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
  EXPECT_EQ(static_cast<OggFileIn::SamplePosition>(fi.get_sample_count())
    , fi.getSamplePos());
}



TEST_F(TestOggFileIn, SetSamplePosStereo16)
{
  OggFileIn fi(stereo16FileName);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.getSamplePos());
  fi.setSamplePos(3);
  EXPECT_EQ(12, fi.get_byte_pos());
  EXPECT_EQ(3, fi.getSamplePos());
  fi.setSamplePos(fi.get_sample_count());
  EXPECT_EQ(static_cast<OggFileIn::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
  EXPECT_EQ(static_cast<OggFileIn::SamplePosition>(fi.get_sample_count())
    , fi.getSamplePos());
}



TEST_F(TestOggFileInDeathTest, SetSamplePosErrorInvalidPosition)
{
  OggFileIn fi(mono16FileName);
  HOU_EXPECT_ERROR(fi.setSamplePos(-1), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(fi.setSamplePos(fi.get_sample_count() + 1), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestOggFileIn, MoveSamplePosMono16)
{
  OggFileIn fi(mono16FileName);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.getSamplePos());
  fi.moveSamplePos(3);
  EXPECT_EQ(6, fi.get_byte_pos());
  EXPECT_EQ(3, fi.getSamplePos());
  fi.moveSamplePos(-1);
  EXPECT_EQ(4, fi.get_byte_pos());
  EXPECT_EQ(2, fi.getSamplePos());
  fi.moveSamplePos(-2);
  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.getSamplePos());
  fi.moveSamplePos(fi.get_sample_count());
  EXPECT_EQ(static_cast<OggFileIn::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
  EXPECT_EQ(static_cast<OggFileIn::SamplePosition>(fi.get_sample_count())
    , fi.getSamplePos());
}



TEST_F(TestOggFileIn, MoveSamplePosStereo16)
{
  OggFileIn fi(stereo16FileName);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.getSamplePos());
  fi.moveSamplePos(3);
  EXPECT_EQ(12, fi.get_byte_pos());
  EXPECT_EQ(3, fi.getSamplePos());
  fi.moveSamplePos(-1);
  EXPECT_EQ(8, fi.get_byte_pos());
  EXPECT_EQ(2, fi.getSamplePos());
  fi.moveSamplePos(-2);
  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.getSamplePos());
  fi.moveSamplePos(fi.get_sample_count());
  EXPECT_EQ(static_cast<OggFileIn::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
  EXPECT_EQ(static_cast<OggFileIn::SamplePosition>(fi.get_sample_count())
    , fi.getSamplePos());
}



TEST_F(TestOggFileInDeathTest, MoveSamplePosErrorInvalidPosition)
{
  OggFileIn fi(mono16FileName);
  fi.moveSamplePos(2);
  HOU_EXPECT_ERROR(fi.moveSamplePos(-3), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(fi.moveSamplePos(fi.get_sample_count() + 1), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestOggFileIn, ReadToVariable)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 1u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  OggFileIn fi(mono16UnicodeFileName);
  BufferType buffer;

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  EXPECT_EQ(10124u, buffer);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  EXPECT_EQ(11584u, buffer);
}



TEST_F(TestOggFileIn, ReadToBasicArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  OggFileIn fi(mono16UnicodeFileName);
  BufferType buffer[bufferSize];

  fi.read(buffer, bufferSize);
  BufferType bufferRef1[bufferSize] = {10124u, 11584u, 9754u};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  HOU_EXPECT_ARRAY_EQ(bufferRef1, buffer, bufferSize);

  fi.read(buffer, bufferSize);
  BufferType bufferRef2[bufferSize] = {11404u, 10203u, 11732u};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  HOU_EXPECT_ARRAY_EQ(bufferRef2, buffer, bufferSize);
}



TEST_F(TestOggFileIn, ReadToArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  OggFileIn fi(mono16UnicodeFileName);
  std::array<BufferType, bufferSize> buffer = {0, 0, 0};

  fi.read(buffer);
  std::array<BufferType, bufferSize> bufferRef1 = {10124u, 11584u, 9754u};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  EXPECT_EQ(bufferRef1, buffer);

  fi.read(buffer);
  std::array<BufferType, bufferSize> bufferRef2 = {11404u, 10203u, 11732u};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  EXPECT_EQ(bufferRef2, buffer);
}



TEST_F(TestOggFileIn, ReadToVector)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  OggFileIn fi(mono16UnicodeFileName);
  std::vector<BufferType> buffer(bufferSize, 0u);

  fi.read(buffer);
  std::vector<BufferType> bufferRef1 = {10124u, 11584u, 9754u};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  EXPECT_EQ(bufferRef1, buffer);

  fi.read(buffer);
  std::vector<BufferType> bufferRef2 = {11404u, 10203u, 11732u};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  EXPECT_EQ(bufferRef2, buffer);
}



TEST_F(TestOggFileIn, ReadToString)
{
  using BufferType = std::string::value_type;
  static constexpr size_t bufferSize = 4u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  OggFileIn fi(mono16UnicodeFileName);
  std::string buffer(bufferSize, 0);

  fi.read(buffer);
  std::string bufferRef1 = {-116, 39, 64, 45};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize / 2, fi.getReadSampleCount());
  EXPECT_EQ(bufferRef1, buffer);

  fi.read(buffer);
  std::string bufferRef2 = {26, 38, -116, 44};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize / 2, fi.getReadSampleCount());
  EXPECT_EQ(bufferRef2, buffer);
}



TEST_F(TestOggFileInDeathTest, ReadToInvalidSizeBuffer)
{
  using BufferType = uint8_t;
  static constexpr size_t bufferSize = 3u;
  std::vector<BufferType> buffer(bufferSize, 0u);

  OggFileIn fi(mono16FileName);
  EXPECT_EQ(AudioBufferFormat::Mono16, fi.get_format());

  HOU_EXPECT_ERROR(fi.read(buffer), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestOggFileIn, ReadAllToVector)
{
  OggFileIn fi(mono16FileName);
  std::vector<uint8_t> fileContent(fi.get_byte_count());
  fi.read(fileContent);
  fi.set_byte_pos(0u);

  auto fiContent = fi.read_all<std::vector<uint8_t>>();
  EXPECT_EQ(fileContent, fiContent);
  EXPECT_EQ(fileContent.size(), fi.get_read_byte_count());
  EXPECT_EQ(fileContent.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(TestOggFileIn, ReadAllToVectorNotFromStart)
{
  OggFileIn fi(mono16FileName);
  std::vector<uint8_t> fileContent(fi.get_byte_count());
  fi.read(fileContent);
  fi.set_byte_pos(2u);

  auto fiContent = fi.read_all<std::vector<uint8_t>>();
  EXPECT_EQ(fileContent, fiContent);
  EXPECT_EQ(fileContent.size(), fi.get_read_byte_count());
  EXPECT_EQ(fileContent.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(TestOggFileIn, Eof)
{
  OggFileIn fi(mono16FileName);
  std::vector<uint8_t> buffer(fi.get_byte_count() + 2u, 0u);

  fi.read(buffer);
  EXPECT_TRUE(fi.eof());

  EXPECT_EQ(fi.get_byte_count(), fi.get_read_byte_count());
  EXPECT_TRUE(fi.eof());

  fi.get_byte_pos();
  EXPECT_TRUE(fi.eof());

  fi.set_byte_pos(0u);
  EXPECT_FALSE(fi.eof());

  EXPECT_FALSE(fi.error());
}

