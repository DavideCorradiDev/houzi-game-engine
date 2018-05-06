// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/test_data.hpp"

#include "hou/aud/aud_exceptions.hpp"
#include "hou/aud/ogg_file_in.hpp"

#include "hou/sys/file.hpp"
#include "hou/sys/sys_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_ogg_file_in : public Test
{
public:
  // Note: OGG files are always read with 16 bits per sample in the Houzi
  // library. For this reason there are no tests involving buffers with 8 bits
  // per sample.
  static const std::string mono16_unicode_filename;
  static const std::string mono16_filename;
  static const std::string stereo16_filename;
  static const std::string low_sample_rate_filename;
  static const std::string wav_filename;
};



class TestOggFileInDeathTest : public test_ogg_file_in
{};



const std::string test_ogg_file_in::mono16_unicode_filename
  = get_data_dir() + u8"TestOgg\U00004f60\U0000597d.ogg";
const std::string test_ogg_file_in::mono16_filename
  = get_data_dir() + u8"TestOgg-Mono-16-44100.ogg";
const std::string test_ogg_file_in::stereo16_filename
  = get_data_dir() + u8"TestOgg-Stereo-16-44100.ogg";
const std::string test_ogg_file_in::low_sample_rate_filename
  = get_data_dir() + u8"TestOgg-Mono-16-22050.ogg";
const std::string test_ogg_file_in::wav_filename
  = get_data_dir() + u8"TestWav-Mono-16-44100.wav";

}  // namespace



TEST_F(test_ogg_file_in, check_success)
{
  EXPECT_TRUE(ogg_file_in::check(mono16_unicode_filename));
}



TEST_F(test_ogg_file_in, check_failure_invalid_format)
{
  EXPECT_FALSE(ogg_file_in::check(wav_filename));
}



TEST_F(TestOggFileInDeathTest, check_failure_invalid_file)
{
  std::string invalid_filename = u8"Invalidfile";
  EXPECT_ERROR_N(
    ogg_file_in::check(invalid_filename), file_open_error, invalid_filename);
}



TEST_F(test_ogg_file_in, path_constructor)
{
  ogg_file_in fi(mono16_unicode_filename);
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



TEST_F(TestOggFileInDeathTest, path_constructor_failure_file_not_existing)
{
  std::string invalid_filename = u8"InvalidFileName";
  EXPECT_ERROR_N(
    ogg_file_in fi(invalid_filename), file_open_error, invalid_filename);
}



TEST_F(TestOggFileInDeathTest, path_constructor_failure_invalid_ogg_file)
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

  std::string invalid_filename = get_output_dir() + u8"dummyOggFile.wav";

  {
    file dummyOggFile(
      invalid_filename, file_open_mode::write, file_type::binary);
    OggMetadata data;
    data.id[0] = 'F';
    data.id[1] = 'a';
    data.id[2] = 'K';
    data.id[3] = 'E';
    dummyOggFile.write(&data, 1u);
  }

  EXPECT_ERROR_N(
    ogg_file_in fi(invalid_filename), audio_read_error, invalid_filename);

  remove_dir(invalid_filename);
}



TEST_F(TestOggFileInDeathTest, path_constructor_failure_no_ogg_header)
{
  std::string invalid_filename = get_output_dir() + u8"dummyOggFile.wav";

  {
    file dummyOggFile(
      invalid_filename, file_open_mode::write, file_type::binary);
  }

  EXPECT_ERROR_N(
    ogg_file_in fi(invalid_filename), audio_read_error, invalid_filename);

  remove_dir(invalid_filename);
}



TEST_F(test_ogg_file_in, move_constructor)
{
  ogg_file_in fi_dummy(mono16_unicode_filename);
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



TEST_F(test_ogg_file_in, audio_buffer_format_attributes)
{
  ogg_file_in fi_mono16(mono16_filename);
  ogg_file_in fi_stereo16(stereo16_filename);

  EXPECT_EQ(audio_buffer_format::mono16, fi_mono16.get_format());
  EXPECT_EQ(1u, fi_mono16.get_channel_count());
  EXPECT_EQ(2u, fi_mono16.get_bytes_per_sample());
  EXPECT_EQ(audio_buffer_format::stereo16, fi_stereo16.get_format());
  EXPECT_EQ(2u, fi_stereo16.get_channel_count());
  EXPECT_EQ(2u, fi_stereo16.get_bytes_per_sample());
}



TEST_F(test_ogg_file_in, sample_rate_attributes)
{
  ogg_file_in fi_normal_rate(mono16_filename);
  ogg_file_in fi_low_rate(low_sample_rate_filename);

  EXPECT_EQ(44100u, fi_normal_rate.get_sample_rate());
  EXPECT_EQ(22050u, fi_low_rate.get_sample_rate());
}



TEST_F(test_ogg_file_in, get_sample_count)
{
  ogg_file_in fi_mono16(mono16_filename);
  ogg_file_in fi_stereo16(stereo16_filename);

  EXPECT_EQ(21231u, fi_mono16.get_sample_count());
  EXPECT_EQ(21231u, fi_stereo16.get_sample_count());

  EXPECT_EQ(42462u, fi_mono16.get_byte_count());
  EXPECT_EQ(84924u, fi_stereo16.get_byte_count());
}



TEST_F(test_ogg_file_in, set_byte_pos)
{
  ogg_file_in fi(mono16_filename);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(6);
  EXPECT_EQ(6, fi.get_byte_pos());
  fi.set_byte_pos(0);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(fi.get_byte_count());
  EXPECT_EQ(static_cast<ogg_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
}



TEST_F(TestOggFileInDeathTest, set_byte_pos_error_position_in_sample)
{
  ogg_file_in fi(mono16_filename);
  EXPECT_PRECOND_ERROR(fi.set_byte_pos(3));
  EXPECT_PRECOND_ERROR(fi.set_byte_pos(fi.get_byte_count() + 3));
}



TEST_F(TestOggFileInDeathTest, set_byte_pos_error_invalid_position)
{
  ogg_file_in fi(mono16_filename);
  EXPECT_ERROR_0(fi.set_byte_pos(-2), file_cursor_error);
  EXPECT_ERROR_0(fi.set_byte_pos(fi.get_byte_count() + 2), file_cursor_error);
}



TEST_F(test_ogg_file_in, move_byte_pos)
{
  ogg_file_in fi(mono16_filename);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(6);
  EXPECT_EQ(6, fi.get_byte_pos());
  fi.move_byte_pos(-2);
  EXPECT_EQ(4, fi.get_byte_pos());
  fi.move_byte_pos(-4);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(fi.get_byte_count());
  EXPECT_EQ(static_cast<ogg_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
}



TEST_F(TestOggFileInDeathTest, move_byte_pos_error_position_in_sample)
{
  ogg_file_in fi(mono16_filename);
  fi.move_byte_pos(4);
  EXPECT_PRECOND_ERROR(fi.move_byte_pos(3));
  EXPECT_PRECOND_ERROR(fi.move_byte_pos(fi.get_byte_count() + 3));
}



TEST_F(TestOggFileInDeathTest, move_byte_pos_error_invalid_position)
{
  ogg_file_in fi(mono16_filename);
  fi.move_byte_pos(4);
  EXPECT_ERROR_0(fi.move_byte_pos(-6), file_cursor_error);
  EXPECT_ERROR_0(fi.move_byte_pos(fi.get_byte_count() - 2), file_cursor_error);
}



TEST_F(test_ogg_file_in, set_sample_pos_mono16)
{
  ogg_file_in fi(mono16_filename);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.set_sample_pos(3);
  EXPECT_EQ(6, fi.get_byte_pos());
  EXPECT_EQ(3, fi.get_sample_pos());
  fi.set_sample_pos(fi.get_sample_count());
  EXPECT_EQ(static_cast<ogg_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  EXPECT_EQ(static_cast<ogg_file_in::sample_position>(fi.get_sample_count()),
    fi.get_sample_pos());
}



TEST_F(test_ogg_file_in, set_sample_pos_stereo16)
{
  ogg_file_in fi(stereo16_filename);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.set_sample_pos(3);
  EXPECT_EQ(12, fi.get_byte_pos());
  EXPECT_EQ(3, fi.get_sample_pos());
  fi.set_sample_pos(fi.get_sample_count());
  EXPECT_EQ(static_cast<ogg_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  EXPECT_EQ(static_cast<ogg_file_in::sample_position>(fi.get_sample_count()),
    fi.get_sample_pos());
}



TEST_F(TestOggFileInDeathTest, set_sample_pos_error_invalid_position)
{
  ogg_file_in fi(mono16_filename);
  EXPECT_ERROR_0(fi.set_sample_pos(-1), file_cursor_error);
  EXPECT_ERROR_0(
    fi.set_sample_pos(fi.get_sample_count() + 1), file_cursor_error);
}



TEST_F(test_ogg_file_in, move_sample_pos_mono16)
{
  ogg_file_in fi(mono16_filename);

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
  EXPECT_EQ(static_cast<ogg_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  EXPECT_EQ(static_cast<ogg_file_in::sample_position>(fi.get_sample_count()),
    fi.get_sample_pos());
}



TEST_F(test_ogg_file_in, move_sample_pos_stereo16)
{
  ogg_file_in fi(stereo16_filename);

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
  EXPECT_EQ(static_cast<ogg_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  EXPECT_EQ(static_cast<ogg_file_in::sample_position>(fi.get_sample_count()),
    fi.get_sample_pos());
}



TEST_F(TestOggFileInDeathTest, move_sample_pos_error_invalid_position)
{
  ogg_file_in fi(mono16_filename);
  fi.move_sample_pos(2);
  EXPECT_ERROR_0(fi.move_sample_pos(-3), file_cursor_error);
  EXPECT_ERROR_0(
    fi.move_sample_pos(fi.get_sample_count() + 1), file_cursor_error);
}



TEST_F(test_ogg_file_in, read_to_variable)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 1u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  ogg_file_in fi(mono16_unicode_filename);
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



TEST_F(test_ogg_file_in, read_to_basic_array)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  ogg_file_in fi(mono16_unicode_filename);
  buffer_type buffer[buffer_size];

  fi.read(buffer, buffer_size);
  buffer_type buffer_ref1[buffer_size] = {10124u, 11584u, 9754u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  HOU_EXPECT_ARRAY_EQ(buffer_ref1, buffer, buffer_size);

  fi.read(buffer, buffer_size);
  buffer_type buffer_ref2[buffer_size] = {11404u, 10203u, 11732u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  HOU_EXPECT_ARRAY_EQ(buffer_ref2, buffer, buffer_size);
}



TEST_F(test_ogg_file_in, read_to_array)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  ogg_file_in fi(mono16_unicode_filename);
  std::array<buffer_type, buffer_size> buffer = {0, 0, 0};

  fi.read(buffer);
  std::array<buffer_type, buffer_size> buffer_ref1 = {10124u, 11584u, 9754u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(buffer_ref1, buffer);

  fi.read(buffer);
  std::array<buffer_type, buffer_size> buffer_ref2 = {11404u, 10203u, 11732u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(buffer_ref2, buffer);
}



TEST_F(test_ogg_file_in, read_to_vector)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  ogg_file_in fi(mono16_unicode_filename);
  std::vector<buffer_type> buffer(buffer_size, 0u);

  fi.read(buffer);
  std::vector<buffer_type> buffer_ref1 = {10124u, 11584u, 9754u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(buffer_ref1, buffer);

  fi.read(buffer);
  std::vector<buffer_type> buffer_ref2 = {11404u, 10203u, 11732u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(buffer_ref2, buffer);
}



TEST_F(test_ogg_file_in, read_to_string)
{
  using buffer_type = std::string::value_type;
  static constexpr size_t buffer_size = 4u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  ogg_file_in fi(mono16_unicode_filename);
  std::string buffer(buffer_size, 0);

  fi.read(buffer);
  std::string buffer_ref1 = {-116, 39, 64, 45};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size / 2, fi.get_read_sample_count());
  EXPECT_EQ(buffer_ref1, buffer);

  fi.read(buffer);
  std::string buffer_ref2 = {26, 38, -116, 44};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size / 2, fi.get_read_sample_count());
  EXPECT_EQ(buffer_ref2, buffer);
}



TEST_F(TestOggFileInDeathTest, read_to_invalid_size_buffer)
{
  using buffer_type = uint8_t;
  static constexpr size_t buffer_size = 3u;
  std::vector<buffer_type> buffer(buffer_size, 0u);

  ogg_file_in fi(mono16_filename);
  EXPECT_EQ(audio_buffer_format::mono16, fi.get_format());

  EXPECT_PRECOND_ERROR(fi.read(buffer));
}



TEST_F(test_ogg_file_in, read_all_to_vector)
{
  ogg_file_in fi(mono16_filename);
  std::vector<uint8_t> file_content(fi.get_byte_count());
  fi.read(file_content);
  fi.set_byte_pos(0u);

  auto fi_content = fi.read_all<std::vector<uint8_t>>();
  EXPECT_EQ(file_content, fi_content);
  EXPECT_EQ(file_content.size(), fi.get_read_byte_count());
  EXPECT_EQ(file_content.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(test_ogg_file_in, read_all_to_vector_not_from_start)
{
  ogg_file_in fi(mono16_filename);
  std::vector<uint8_t> file_content(fi.get_byte_count());
  fi.read(file_content);
  fi.set_byte_pos(2u);

  auto fi_content = fi.read_all<std::vector<uint8_t>>();
  EXPECT_EQ(file_content, fi_content);
  EXPECT_EQ(file_content.size(), fi.get_read_byte_count());
  EXPECT_EQ(file_content.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(test_ogg_file_in, eof)
{
  ogg_file_in fi(mono16_filename);
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
