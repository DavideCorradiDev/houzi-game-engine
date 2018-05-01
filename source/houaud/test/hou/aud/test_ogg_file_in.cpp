// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/test_data.hpp"

#include "hou/aud/aud_error.hpp"
#include "hou/aud/ogg_file_in.hpp"

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



const std::string TestOggFileIn::mono16UnicodeFileName = get_data_dir()
  + u8"TestOgg\U00004f60\U0000597d.ogg";
const std::string TestOggFileIn::mono16FileName = get_data_dir()
  + u8"TestOgg-Mono-16-44100.ogg";
const std::string TestOggFileIn::stereo16FileName = get_data_dir()
  + u8"TestOgg-Stereo-16-44100.ogg";
const std::string TestOggFileIn::lowSampleRateFileName = get_data_dir()
  + u8"TestOgg-Mono-16-22050.ogg";
const std::string TestOggFileIn::wavFileName = get_data_dir()
  + u8"TestWav-Mono-16-44100.wav";

}



TEST_F(TestOggFileIn, CheckSuccess)
{
  EXPECT_TRUE(ogg_file_in::check(mono16UnicodeFileName));
}



TEST_F(TestOggFileIn, CheckFailureInvalidFormat)
{
  EXPECT_FALSE(ogg_file_in::check(wavFileName));
}



TEST_F(TestOggFileInDeathTest, CheckFailureInvalidFile)
{
  std::string invalid_filename = u8"Invalidfile";
  HOU_EXPECT_ERROR(ogg_file_in::check(invalid_filename), std::runtime_error
    , format_string(get_text(sys_error::file_open), invalid_filename.c_str()));
}



TEST_F(TestOggFileIn, PathConstructor)
{
  ogg_file_in fi(mono16UnicodeFileName);
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(42206u, fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(audio_buffer_format::mono16, fi.get_format());
  EXPECT_EQ(1u, fi.get_channel_count());
  EXPECT_EQ(2u, fi.get_bytes_per_sample());
  EXPECT_EQ(44100u, fi.get_sample_rate());
  EXPECT_EQ(21103u, fi.get_sample_count());
  EXPECT_EQ(0, fi.get_sample_pos());
}



TEST_F(TestOggFileInDeathTest, PathConstructorFailureFileNotExisting)
{
  std::string invalid_filename = u8"InvalidFileName";
  HOU_EXPECT_ERROR(ogg_file_in fi(invalid_filename), std::runtime_error
    , format_string(get_text(sys_error::file_open), invalid_filename.c_str()));
}



TEST_F(TestOggFileInDeathTest, PathConstructorFailureInvalidOggFile)
{
  static constexpr size_t stringSize = 4u;
  struct OggMetadata
  {
    char id[stringSize];
    uint32_t chunk_size;
    char form[stringSize];
    char sc1Id[stringSize];
    uint32_t sc1Size;
    uint16_t format;
    uint16_t channels;
    uint32_t sample_rate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char sc2Id[stringSize];
    uint32_t sc2Size;
  };

  std::string dummyOggFileName = get_output_dir() + u8"dummyOggFile.wav";

  {
    file dummyOggFile(dummyOggFileName, file_open_mode::write, file_type::binary);
    OggMetadata data;
    data.id[0] = 'F';
    data.id[1] = 'a';
    data.id[2] = 'K';
    data.id[3] = 'E';
    dummyOggFile.write(&data, 1u);
  }

  HOU_EXPECT_ERROR(ogg_file_in fi(dummyOggFileName), std::runtime_error
    , format_string(get_text(aud_error::ogg_invalid_header)
    , dummyOggFileName.c_str()));

  remove_dir(dummyOggFileName);
}



TEST_F(TestOggFileInDeathTest, PathConstructorFailureNoOggHeader)
{
  std::string dummyOggFileName = get_output_dir() + u8"dummyOggFile.wav";

  {
    file dummyOggFile(dummyOggFileName, file_open_mode::write, file_type::binary);
  }

  HOU_EXPECT_ERROR(ogg_file_in fi(dummyOggFileName), std::runtime_error
    , format_string(get_text(aud_error::ogg_invalid_header)
    , dummyOggFileName.c_str()));

  remove_dir(dummyOggFileName);
}



TEST_F(TestOggFileIn, MoveConstructor)
{
  ogg_file_in fi_dummy(mono16UnicodeFileName);
  ogg_file_in fi(std::move(fi_dummy));
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(42206u, fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(audio_buffer_format::mono16, fi.get_format());
  EXPECT_EQ(1u, fi.get_channel_count());
  EXPECT_EQ(2u, fi.get_bytes_per_sample());
  EXPECT_EQ(44100u, fi.get_sample_rate());
  EXPECT_EQ(21103u, fi.get_sample_count());
  EXPECT_EQ(0, fi.get_sample_pos());
}



TEST_F(TestOggFileIn, AudioBufferFormatAttributes)
{
  ogg_file_in fiMono16(mono16FileName);
  ogg_file_in fiStereo16(stereo16FileName);

  EXPECT_EQ(audio_buffer_format::mono16, fiMono16.get_format());
  EXPECT_EQ(1u, fiMono16.get_channel_count());
  EXPECT_EQ(2u, fiMono16.get_bytes_per_sample());
  EXPECT_EQ(audio_buffer_format::stereo16, fiStereo16.get_format());
  EXPECT_EQ(2u, fiStereo16.get_channel_count());
  EXPECT_EQ(2u, fiStereo16.get_bytes_per_sample());
}



TEST_F(TestOggFileIn, SampleRateAttributes)
{
  ogg_file_in fiNormalRate(mono16FileName);
  ogg_file_in fiLowRate(lowSampleRateFileName);

  EXPECT_EQ(44100u, fiNormalRate.get_sample_rate());
  EXPECT_EQ(22050u, fiLowRate.get_sample_rate());
}



TEST_F(TestOggFileIn, GetSampleCount)
{
  ogg_file_in fiMono16(mono16FileName);
  ogg_file_in fiStereo16(stereo16FileName);

  EXPECT_EQ(21231u, fiMono16.get_sample_count());
  EXPECT_EQ(21231u, fiStereo16.get_sample_count());

  EXPECT_EQ(42462u, fiMono16.get_byte_count());
  EXPECT_EQ(84924u, fiStereo16.get_byte_count());
}



TEST_F(TestOggFileIn, SetBytePos)
{
  ogg_file_in fi(mono16FileName);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(6);
  EXPECT_EQ(6, fi.get_byte_pos());
  fi.set_byte_pos(0);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(fi.get_byte_count());
  EXPECT_EQ(static_cast<ogg_file_in::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
}



TEST_F(TestOggFileInDeathTest, SetBytePosErrorPositionInSample)
{
  ogg_file_in fi(mono16FileName);
  HOU_EXPECT_ERROR(fi.set_byte_pos(3), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(fi.set_byte_pos(fi.get_byte_count() + 3), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestOggFileInDeathTest, SetBytePosErrorInvalidPosition)
{
  ogg_file_in fi(mono16FileName);
  HOU_EXPECT_ERROR(fi.set_byte_pos(-2), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(fi.set_byte_pos(fi.get_byte_count() + 2), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestOggFileIn, MoveBytePos)
{
  ogg_file_in fi(mono16FileName);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(6);
  EXPECT_EQ(6, fi.get_byte_pos());
  fi.move_byte_pos(-2);
  EXPECT_EQ(4, fi.get_byte_pos());
  fi.move_byte_pos(-4);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(fi.get_byte_count());
  EXPECT_EQ(static_cast<ogg_file_in::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
}



TEST_F(TestOggFileInDeathTest, MoveBytePosErrorPositionInSample)
{
  ogg_file_in fi(mono16FileName);
  fi.move_byte_pos(4);
  HOU_EXPECT_ERROR(fi.move_byte_pos(3), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(fi.move_byte_pos(fi.get_byte_count() + 3), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestOggFileInDeathTest, MoveBytePosErrorInvalidPosition)
{
  ogg_file_in fi(mono16FileName);
  fi.move_byte_pos(4);
  HOU_EXPECT_ERROR(fi.move_byte_pos(-6), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(fi.move_byte_pos(fi.get_byte_count() - 2), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestOggFileIn, SetSamplePosMono16)
{
  ogg_file_in fi(mono16FileName);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.set_sample_pos(3);
  EXPECT_EQ(6, fi.get_byte_pos());
  EXPECT_EQ(3, fi.get_sample_pos());
  fi.set_sample_pos(fi.get_sample_count());
  EXPECT_EQ(static_cast<ogg_file_in::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
  EXPECT_EQ(static_cast<ogg_file_in::sample_position>(fi.get_sample_count())
    , fi.get_sample_pos());
}



TEST_F(TestOggFileIn, SetSamplePosStereo16)
{
  ogg_file_in fi(stereo16FileName);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.set_sample_pos(3);
  EXPECT_EQ(12, fi.get_byte_pos());
  EXPECT_EQ(3, fi.get_sample_pos());
  fi.set_sample_pos(fi.get_sample_count());
  EXPECT_EQ(static_cast<ogg_file_in::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
  EXPECT_EQ(static_cast<ogg_file_in::sample_position>(fi.get_sample_count())
    , fi.get_sample_pos());
}



TEST_F(TestOggFileInDeathTest, SetSamplePosErrorInvalidPosition)
{
  ogg_file_in fi(mono16FileName);
  HOU_EXPECT_ERROR(fi.set_sample_pos(-1), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(fi.set_sample_pos(fi.get_sample_count() + 1), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestOggFileIn, MoveSamplePosMono16)
{
  ogg_file_in fi(mono16FileName);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.move_sample_pos(3);
  EXPECT_EQ(6, fi.get_byte_pos());
  EXPECT_EQ(3, fi.get_sample_pos());
  fi.move_sample_pos(-1);
  EXPECT_EQ(4, fi.get_byte_pos());
  EXPECT_EQ(2, fi.get_sample_pos());
  fi.move_sample_pos(-2);
  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.move_sample_pos(fi.get_sample_count());
  EXPECT_EQ(static_cast<ogg_file_in::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
  EXPECT_EQ(static_cast<ogg_file_in::sample_position>(fi.get_sample_count())
    , fi.get_sample_pos());
}



TEST_F(TestOggFileIn, MoveSamplePosStereo16)
{
  ogg_file_in fi(stereo16FileName);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.move_sample_pos(3);
  EXPECT_EQ(12, fi.get_byte_pos());
  EXPECT_EQ(3, fi.get_sample_pos());
  fi.move_sample_pos(-1);
  EXPECT_EQ(8, fi.get_byte_pos());
  EXPECT_EQ(2, fi.get_sample_pos());
  fi.move_sample_pos(-2);
  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.move_sample_pos(fi.get_sample_count());
  EXPECT_EQ(static_cast<ogg_file_in::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
  EXPECT_EQ(static_cast<ogg_file_in::sample_position>(fi.get_sample_count())
    , fi.get_sample_pos());
}



TEST_F(TestOggFileInDeathTest, MoveSamplePosErrorInvalidPosition)
{
  ogg_file_in fi(mono16FileName);
  fi.move_sample_pos(2);
  HOU_EXPECT_ERROR(fi.move_sample_pos(-3), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(fi.move_sample_pos(fi.get_sample_count() + 1), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestOggFileIn, ReadToVariable)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 1u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  ogg_file_in fi(mono16UnicodeFileName);
  buffer_type buffer;

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(10124u, buffer);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(11584u, buffer);
}



TEST_F(TestOggFileIn, ReadToBasicArray)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  ogg_file_in fi(mono16UnicodeFileName);
  buffer_type buffer[buffer_size];

  fi.read(buffer, buffer_size);
  buffer_type bufferRef1[buffer_size] = {10124u, 11584u, 9754u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  HOU_EXPECT_ARRAY_EQ(bufferRef1, buffer, buffer_size);

  fi.read(buffer, buffer_size);
  buffer_type bufferRef2[buffer_size] = {11404u, 10203u, 11732u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  HOU_EXPECT_ARRAY_EQ(bufferRef2, buffer, buffer_size);
}



TEST_F(TestOggFileIn, ReadToArray)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  ogg_file_in fi(mono16UnicodeFileName);
  std::array<buffer_type, buffer_size> buffer = {0, 0, 0};

  fi.read(buffer);
  std::array<buffer_type, buffer_size> bufferRef1 = {10124u, 11584u, 9754u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(bufferRef1, buffer);

  fi.read(buffer);
  std::array<buffer_type, buffer_size> bufferRef2 = {11404u, 10203u, 11732u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(bufferRef2, buffer);
}



TEST_F(TestOggFileIn, ReadToVector)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  ogg_file_in fi(mono16UnicodeFileName);
  std::vector<buffer_type> buffer(buffer_size, 0u);

  fi.read(buffer);
  std::vector<buffer_type> bufferRef1 = {10124u, 11584u, 9754u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(bufferRef1, buffer);

  fi.read(buffer);
  std::vector<buffer_type> bufferRef2 = {11404u, 10203u, 11732u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(bufferRef2, buffer);
}



TEST_F(TestOggFileIn, ReadToString)
{
  using buffer_type = std::string::value_type;
  static constexpr size_t buffer_size = 4u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  ogg_file_in fi(mono16UnicodeFileName);
  std::string buffer(buffer_size, 0);

  fi.read(buffer);
  std::string bufferRef1 = {-116, 39, 64, 45};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size / 2, fi.get_read_sample_count());
  EXPECT_EQ(bufferRef1, buffer);

  fi.read(buffer);
  std::string bufferRef2 = {26, 38, -116, 44};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size / 2, fi.get_read_sample_count());
  EXPECT_EQ(bufferRef2, buffer);
}



TEST_F(TestOggFileInDeathTest, ReadToInvalidSizeBuffer)
{
  using buffer_type = uint8_t;
  static constexpr size_t buffer_size = 3u;
  std::vector<buffer_type> buffer(buffer_size, 0u);

  ogg_file_in fi(mono16FileName);
  EXPECT_EQ(audio_buffer_format::mono16, fi.get_format());

  HOU_EXPECT_ERROR(fi.read(buffer), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestOggFileIn, ReadAllToVector)
{
  ogg_file_in fi(mono16FileName);
  std::vector<uint8_t> file_content(fi.get_byte_count());
  fi.read(file_content);
  fi.set_byte_pos(0u);

  auto fi_content = fi.read_all<std::vector<uint8_t>>();
  EXPECT_EQ(file_content, fi_content);
  EXPECT_EQ(file_content.size(), fi.get_read_byte_count());
  EXPECT_EQ(file_content.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(TestOggFileIn, ReadAllToVectorNotFromStart)
{
  ogg_file_in fi(mono16FileName);
  std::vector<uint8_t> file_content(fi.get_byte_count());
  fi.read(file_content);
  fi.set_byte_pos(2u);

  auto fi_content = fi.read_all<std::vector<uint8_t>>();
  EXPECT_EQ(file_content, fi_content);
  EXPECT_EQ(file_content.size(), fi.get_read_byte_count());
  EXPECT_EQ(file_content.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(TestOggFileIn, Eof)
{
  ogg_file_in fi(mono16FileName);
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

