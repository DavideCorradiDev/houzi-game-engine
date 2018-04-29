// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/TestData.hpp"

#include "hou/aud/AudError.hpp"
#include "hou/aud/WavFileIn.hpp"

#include "hou/sys/sys_error.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestWavFileIn : public Test
{
public:
  static const std::string mono16UnicodeFileName;
  static const std::string mono8FileName;
  static const std::string mono16FileName;
  static const std::string stereo8FileName;
  static const std::string stereo16FileName;
  static const std::string lowSampleRateFileName;
  static const std::string oggFileName;
};

class TestWavFileInDeathTest : public TestWavFileIn
{};



const std::string TestWavFileIn::mono16UnicodeFileName
  = getDataDir() + u8"TestWav\U00004f60\U0000597d.wav";
const std::string TestWavFileIn::mono8FileName
  = getDataDir() + u8"TestWav-Mono-8-44100.wav";
const std::string TestWavFileIn::mono16FileName
  = getDataDir() + u8"TestWav-Mono-16-44100.wav";
const std::string TestWavFileIn::stereo8FileName
  = getDataDir() + u8"TestWav-Stereo-8-44100.wav";
const std::string TestWavFileIn::stereo16FileName
  = getDataDir() + u8"TestWav-Stereo-16-44100.wav";
const std::string TestWavFileIn::lowSampleRateFileName
  = getDataDir() + u8"TestWav-Mono-16-22050.wav";
const std::string TestWavFileIn::oggFileName
  = getDataDir() + u8"TestOgg\U00004f60\U0000597d.ogg";

}  // namespace



TEST_F(TestWavFileIn, CheckSuccess)
{
  EXPECT_TRUE(WavFileIn::check(mono16UnicodeFileName));
}



TEST_F(TestWavFileIn, CheckFailureInvalidFormat)
{
  EXPECT_FALSE(WavFileIn::check(oggFileName));
}



TEST_F(TestWavFileInDeathTest, CheckFailureInvalidFile)
{
  std::string invalidFileName = u8"Invalidfile";
  HOU_EXPECT_ERROR(WavFileIn::check(invalidFileName), std::runtime_error,
    format_string(get_text(sys_error::file_open), invalidFileName.c_str()));
}



TEST_F(TestWavFileIn, PathConstructor)
{
  WavFileIn fi(mono16UnicodeFileName);
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



TEST_F(TestWavFileInDeathTest, PathConstructorFailureFileNotExisting)
{
  std::string invalidFileName = u8"InvalidFileName";
  HOU_EXPECT_ERROR(WavFileIn fi(invalidFileName), std::runtime_error,
    format_string(get_text(sys_error::file_open), invalidFileName.c_str()));
}



TEST_F(TestWavFileInDeathTest, PathConstructorFailureInvalidWavFile)
{
  static constexpr size_t stringSize = 4u;
  struct WavMetadata
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

  std::string dummyWavFileName = getOutputDir() + u8"dummyWavFile.wav";

  {
    file dummyWavFile(dummyWavFileName, file_open_mode::write, file_type::binary);
    WavMetadata data;
    data.id[0] = 'F';
    data.id[1] = 'a';
    data.id[2] = 'K';
    data.id[3] = 'E';
    dummyWavFile.write(&data, 1u);
  }

  HOU_EXPECT_ERROR(WavFileIn fi(dummyWavFileName), std::runtime_error,
    format_string(
      get_text(AudError::WavInvalidHeader), dummyWavFileName.c_str()));

  remove_dir(dummyWavFileName);
}



TEST_F(TestWavFileInDeathTest, PathConstructorFailureNoWavHeader)
{
  std::string dummyWavFileName = getOutputDir() + u8"dummyWavFile.wav";

  {
    file dummyWavFile(dummyWavFileName, file_open_mode::write, file_type::binary);
  }

  HOU_EXPECT_ERROR(WavFileIn fi(dummyWavFileName), std::runtime_error,
    format_string(
      get_text(AudError::WavInvalidHeader), dummyWavFileName.c_str()));

  remove_dir(dummyWavFileName);
}



TEST_F(TestWavFileIn, MoveConstructor)
{
  WavFileIn fiDummy(mono16UnicodeFileName);
  WavFileIn fi(std::move(fiDummy));
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



TEST_F(TestWavFileIn, AudioBufferFormatAttributes)
{
  WavFileIn fiMono8(mono8FileName);
  WavFileIn fiMono16(mono16FileName);
  WavFileIn fiStereo8(stereo8FileName);
  WavFileIn fiStereo16(stereo16FileName);

  EXPECT_EQ(AudioBufferFormat::Mono8, fiMono8.get_format());
  EXPECT_EQ(1u, fiMono8.getChannelCount());
  EXPECT_EQ(1u, fiMono8.getBytesPerSample());
  EXPECT_EQ(AudioBufferFormat::Mono16, fiMono16.get_format());
  EXPECT_EQ(1u, fiMono16.getChannelCount());
  EXPECT_EQ(2u, fiMono16.getBytesPerSample());
  EXPECT_EQ(AudioBufferFormat::Stereo8, fiStereo8.get_format());
  EXPECT_EQ(2u, fiStereo8.getChannelCount());
  EXPECT_EQ(1u, fiStereo8.getBytesPerSample());
  EXPECT_EQ(AudioBufferFormat::Stereo16, fiStereo16.get_format());
  EXPECT_EQ(2u, fiStereo16.getChannelCount());
  EXPECT_EQ(2u, fiStereo16.getBytesPerSample());
}



TEST_F(TestWavFileIn, SampleRateAttributes)
{
  WavFileIn fiNormalRate(mono16FileName);
  WavFileIn fiLowRate(lowSampleRateFileName);

  EXPECT_EQ(44100u, fiNormalRate.getSampleRate());
  EXPECT_EQ(22050u, fiLowRate.getSampleRate());
}



TEST_F(TestWavFileIn, GetSampleCount)
{
  WavFileIn fiMono8(mono8FileName);
  WavFileIn fiMono16(mono16FileName);
  WavFileIn fiStereo8(stereo8FileName);
  WavFileIn fiStereo16(stereo16FileName);

  EXPECT_EQ(21231u, fiMono8.get_sample_count());
  EXPECT_EQ(21231u, fiMono16.get_sample_count());
  EXPECT_EQ(21231u, fiStereo8.get_sample_count());
  EXPECT_EQ(21231u, fiStereo16.get_sample_count());

  EXPECT_EQ(21231u, fiMono8.get_byte_count());
  EXPECT_EQ(42462u, fiMono16.get_byte_count());
  EXPECT_EQ(42462u, fiStereo8.get_byte_count());
  EXPECT_EQ(84924u, fiStereo16.get_byte_count());
}



TEST_F(TestWavFileIn, SetBytePos)
{
  WavFileIn fi(mono16FileName);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(6);
  EXPECT_EQ(6, fi.get_byte_pos());
  fi.set_byte_pos(0);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(fi.get_byte_count());
  EXPECT_EQ(
    static_cast<WavFileIn::byte_position>(fi.get_byte_count()), fi.get_byte_pos());
}



TEST_F(TestWavFileInDeathTest, SetBytePosErrorPositionInSample)
{
  WavFileIn fi(mono16FileName);
  HOU_EXPECT_ERROR(
    fi.set_byte_pos(3), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(fi.set_byte_pos(fi.get_byte_count() + 3), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(TestWavFileInDeathTest, SetBytePosErrorInvalidPosition)
{
  WavFileIn fi(mono16FileName);
  HOU_EXPECT_ERROR(
    fi.set_byte_pos(-2), std::runtime_error, get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(fi.set_byte_pos(fi.get_byte_count() + 2), std::runtime_error,
    get_text(sys_error::file_seek));
}



TEST_F(TestWavFileIn, MoveBytePos)
{
  WavFileIn fi(mono16FileName);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(6);
  EXPECT_EQ(6, fi.get_byte_pos());
  fi.move_byte_pos(-2);
  EXPECT_EQ(4, fi.get_byte_pos());
  fi.move_byte_pos(-4);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(fi.get_byte_count());
  EXPECT_EQ(
    static_cast<WavFileIn::byte_position>(fi.get_byte_count()), fi.get_byte_pos());
}



TEST_F(TestWavFileInDeathTest, MoveBytePosErrorPositionInSample)
{
  WavFileIn fi(mono16FileName);
  fi.move_byte_pos(4);
  HOU_EXPECT_ERROR(
    fi.move_byte_pos(3), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(fi.move_byte_pos(fi.get_byte_count() + 3), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(TestWavFileInDeathTest, MoveBytePosErrorInvalidPosition)
{
  WavFileIn fi(mono16FileName);
  fi.move_byte_pos(4);
  HOU_EXPECT_ERROR(
    fi.move_byte_pos(-6), std::runtime_error, get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(fi.move_byte_pos(fi.get_byte_count() - 2), std::runtime_error,
    get_text(sys_error::file_seek));
}



TEST_F(TestWavFileIn, SetSamplePosMono8)
{
  WavFileIn fi(mono8FileName);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.getSamplePos());
  fi.setSamplePos(3);
  EXPECT_EQ(3, fi.get_byte_pos());
  EXPECT_EQ(3, fi.getSamplePos());
  fi.setSamplePos(fi.get_sample_count());
  EXPECT_EQ(
    static_cast<WavFileIn::byte_position>(fi.get_byte_count()), fi.get_byte_pos());
  EXPECT_EQ(static_cast<WavFileIn::SamplePosition>(fi.get_sample_count()),
    fi.getSamplePos());
}



TEST_F(TestWavFileIn, SetSamplePosMono16)
{
  WavFileIn fi(mono16FileName);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.getSamplePos());
  fi.setSamplePos(3);
  EXPECT_EQ(6, fi.get_byte_pos());
  EXPECT_EQ(3, fi.getSamplePos());
  fi.setSamplePos(fi.get_sample_count());
  EXPECT_EQ(
    static_cast<WavFileIn::byte_position>(fi.get_byte_count()), fi.get_byte_pos());
  EXPECT_EQ(static_cast<WavFileIn::SamplePosition>(fi.get_sample_count()),
    fi.getSamplePos());
}



TEST_F(TestWavFileIn, SetSamplePosStereo8)
{
  WavFileIn fi(stereo8FileName);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.getSamplePos());
  fi.setSamplePos(3);
  EXPECT_EQ(6, fi.get_byte_pos());
  EXPECT_EQ(3, fi.getSamplePos());
  fi.setSamplePos(fi.get_sample_count());
  EXPECT_EQ(
    static_cast<WavFileIn::byte_position>(fi.get_byte_count()), fi.get_byte_pos());
  EXPECT_EQ(static_cast<WavFileIn::SamplePosition>(fi.get_sample_count()),
    fi.getSamplePos());
}



TEST_F(TestWavFileIn, SetSamplePosStereo16)
{
  WavFileIn fi(stereo16FileName);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.getSamplePos());
  fi.setSamplePos(3);
  EXPECT_EQ(12, fi.get_byte_pos());
  EXPECT_EQ(3, fi.getSamplePos());
  fi.setSamplePos(fi.get_sample_count());
  EXPECT_EQ(
    static_cast<WavFileIn::byte_position>(fi.get_byte_count()), fi.get_byte_pos());
  EXPECT_EQ(static_cast<WavFileIn::SamplePosition>(fi.get_sample_count()),
    fi.getSamplePos());
}



TEST_F(TestWavFileInDeathTest, SetSamplePosErrorInvalidPosition)
{
  WavFileIn fi(mono16FileName);
  HOU_EXPECT_ERROR(
    fi.setSamplePos(-1), std::runtime_error, get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(fi.setSamplePos(fi.get_sample_count() + 1), std::runtime_error,
    get_text(sys_error::file_seek));
}



TEST_F(TestWavFileIn, MoveSamplePosMono8)
{
  WavFileIn fi(mono8FileName);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.getSamplePos());
  fi.moveSamplePos(3);
  EXPECT_EQ(3, fi.get_byte_pos());
  EXPECT_EQ(3, fi.getSamplePos());
  fi.moveSamplePos(-1);
  EXPECT_EQ(2, fi.get_byte_pos());
  EXPECT_EQ(2, fi.getSamplePos());
  fi.moveSamplePos(-2);
  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.getSamplePos());
  fi.moveSamplePos(fi.get_sample_count());
  EXPECT_EQ(
    static_cast<WavFileIn::byte_position>(fi.get_byte_count()), fi.get_byte_pos());
  EXPECT_EQ(static_cast<WavFileIn::SamplePosition>(fi.get_sample_count()),
    fi.getSamplePos());
}



TEST_F(TestWavFileIn, MoveSamplePosMono16)
{
  WavFileIn fi(mono16FileName);

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
  EXPECT_EQ(
    static_cast<WavFileIn::byte_position>(fi.get_byte_count()), fi.get_byte_pos());
  EXPECT_EQ(static_cast<WavFileIn::SamplePosition>(fi.get_sample_count()),
    fi.getSamplePos());
}



TEST_F(TestWavFileIn, MoveSamplePosStereo8)
{
  WavFileIn fi(stereo8FileName);

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
  EXPECT_EQ(
    static_cast<WavFileIn::byte_position>(fi.get_byte_count()), fi.get_byte_pos());
  EXPECT_EQ(static_cast<WavFileIn::SamplePosition>(fi.get_sample_count()),
    fi.getSamplePos());
}



TEST_F(TestWavFileIn, MoveSamplePosStereo16)
{
  WavFileIn fi(stereo16FileName);

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
  EXPECT_EQ(
    static_cast<WavFileIn::byte_position>(fi.get_byte_count()), fi.get_byte_pos());
  EXPECT_EQ(static_cast<WavFileIn::SamplePosition>(fi.get_sample_count()),
    fi.getSamplePos());
}



TEST_F(TestWavFileInDeathTest, MoveSamplePosErrorInvalidPosition)
{
  WavFileIn fi(mono16FileName);
  fi.moveSamplePos(2);
  HOU_EXPECT_ERROR(
    fi.moveSamplePos(-3), std::runtime_error, get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(fi.moveSamplePos(fi.get_sample_count() - 1),
    std::runtime_error, get_text(sys_error::file_seek));
}



TEST_F(TestWavFileIn, ReadToVariable)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 1u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  WavFileIn fi(mono16UnicodeFileName);
  BufferType buffer;

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  EXPECT_EQ(12480u, buffer);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  EXPECT_EQ(12460, buffer);
}



TEST_F(TestWavFileIn, ReadToBasicArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  WavFileIn fi(mono16UnicodeFileName);
  BufferType buffer[bufferSize];

  fi.read(buffer, bufferSize);
  BufferType bufferRef1[bufferSize] = {12480u, 12460u, 12440u};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  HOU_EXPECT_ARRAY_EQ(bufferRef1, buffer, bufferSize);

  fi.read(buffer, bufferSize);
  BufferType bufferRef2[bufferSize] = {12420u, 12400u, 12380u};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  HOU_EXPECT_ARRAY_EQ(bufferRef2, buffer, bufferSize);
}



TEST_F(TestWavFileIn, ReadToArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  WavFileIn fi(mono16UnicodeFileName);
  std::array<BufferType, bufferSize> buffer = {0, 0, 0};

  fi.read(buffer);
  std::array<BufferType, bufferSize> bufferRef1 = {12480u, 12460u, 12440u};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  EXPECT_EQ(bufferRef1, buffer);

  fi.read(buffer);
  std::array<BufferType, bufferSize> bufferRef2 = {12420u, 12400u, 12380u};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  EXPECT_EQ(bufferRef2, buffer);
}



TEST_F(TestWavFileIn, ReadToVector)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  WavFileIn fi(mono16UnicodeFileName);
  std::vector<BufferType> buffer(bufferSize, 0u);

  fi.read(buffer);
  std::vector<BufferType> bufferRef1 = {12480u, 12460u, 12440u};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  EXPECT_EQ(bufferRef1, buffer);

  fi.read(buffer);
  std::vector<BufferType> bufferRef2 = {12420u, 12400u, 12380u};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize, fi.getReadSampleCount());
  EXPECT_EQ(bufferRef2, buffer);
}



TEST_F(TestWavFileIn, ReadToString)
{
  using BufferType = std::string::value_type;
  static constexpr size_t bufferSize = 4u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  WavFileIn fi(mono16UnicodeFileName);
  std::string buffer(bufferSize, 0);

  fi.read(buffer);
  std::string bufferRef1 = {-64, 48, -84, 48};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize / 2, fi.getReadSampleCount());
  EXPECT_EQ(bufferRef1, buffer);

  fi.read(buffer);
  std::string bufferRef2 = {-104, 48, -124, 48};
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  EXPECT_EQ(bufferSize / 2, fi.getReadSampleCount());
  EXPECT_EQ(bufferRef2, buffer);
}



TEST_F(TestWavFileInDeathTest, ReadToInvalidSizeBuffer)
{
  using BufferType = uint8_t;
  static constexpr size_t bufferSize = 3u;
  std::vector<BufferType> buffer(bufferSize, 0u);

  WavFileIn fi(mono16FileName);
  EXPECT_EQ(AudioBufferFormat::Mono16, fi.get_format());

  HOU_EXPECT_ERROR(
    fi.read(buffer), std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(TestWavFileIn, ReadAllToVector)
{
  WavFileIn fi(mono8FileName);
  std::vector<uint8_t> fileContent(fi.get_byte_count());
  fi.read(fileContent);
  fi.set_byte_pos(0u);

  auto fiContent = fi.read_all<std::vector<uint8_t>>();
  EXPECT_EQ(fileContent, fiContent);
  EXPECT_EQ(fileContent.size(), fi.get_read_byte_count());
  EXPECT_EQ(fileContent.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(TestWavFileIn, ReadAllToVectorNotFromStart)
{
  WavFileIn fi(mono8FileName);
  std::vector<uint8_t> fileContent(fi.get_byte_count());
  fi.read(fileContent);
  fi.set_byte_pos(2u);

  auto fiContent = fi.read_all<std::vector<uint8_t>>();
  EXPECT_EQ(fileContent, fiContent);
  EXPECT_EQ(fileContent.size(), fi.get_read_byte_count());
  EXPECT_EQ(fileContent.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(TestWavFileIn, Eof)
{
  WavFileIn fi(mono16FileName);
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
