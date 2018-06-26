// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"
#include "hou/aud/test_data.hpp"

#include "hou/aud/aud_exceptions.hpp"
#include "hou/aud/wav_file_in.hpp"

#include "hou/sys/sys_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_wav_file_in : public Test
{
public:
  static const std::string mono16_unicode_filename;
  static const std::string mono8_filename;
  static const std::string mono16_filename;
  static const std::string stereo8_filename;
  static const std::string stereo16_filename;
  static const std::string low_sample_rate_filename;
  static const std::string ogg_filename;
};

class test_wav_file_in_death_test : public test_wav_file_in
{};



const std::string test_wav_file_in::mono16_unicode_filename
  = get_data_dir() + u8"TestWav\U00004f60\U0000597d.wav";
const std::string test_wav_file_in::mono8_filename
  = get_data_dir() + u8"TestWav-mono-8-44100.wav";
const std::string test_wav_file_in::mono16_filename
  = get_data_dir() + u8"TestWav-mono-16-44100.wav";
const std::string test_wav_file_in::stereo8_filename
  = get_data_dir() + u8"TestWav-stereo-8-44100.wav";
const std::string test_wav_file_in::stereo16_filename
  = get_data_dir() + u8"TestWav-stereo-16-44100.wav";
const std::string test_wav_file_in::low_sample_rate_filename
  = get_data_dir() + u8"TestWav-mono-16-22050.wav";
const std::string test_wav_file_in::ogg_filename
  = get_data_dir() + u8"TestOgg\U00004f60\U0000597d.ogg";

}  // namespace



TEST_F(test_wav_file_in, check_success)
{
  EXPECT_TRUE(wav_file_in::check(mono16_unicode_filename));
}



TEST_F(test_wav_file_in, check_failure_invalid_format)
{
  EXPECT_FALSE(wav_file_in::check(ogg_filename));
}



TEST_F(test_wav_file_in_death_test, check_failure_invalid_file)
{
  std::string invalid_filename = u8"Invalidfile";
  EXPECT_ERROR_N(
    wav_file_in::check(invalid_filename), file_open_error, invalid_filename);
}



TEST_F(test_wav_file_in, path_constructor)
{
  wav_file_in fi(mono16_unicode_filename);
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



TEST_F(test_wav_file_in_death_test, path_constructor_failure_file_not_existing)
{
  std::string invalid_filename = u8"InvalidFileName";
  EXPECT_ERROR_N(
    wav_file_in fi(invalid_filename), file_open_error, invalid_filename);
}



TEST_F(test_wav_file_in_death_test, path_constructor_failure_invalid_wav_file)
{
  static constexpr size_t string_size = 4u;

  struct wav_metadata
  {
    char id[string_size];
    uint32_t chunk_size;
    char form[string_size];
    char sc1Id[string_size];
    uint32_t sc1Size;
    uint16_t format;
    uint16_t channels;
    uint32_t sample_rate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char sc2Id[string_size];
    uint32_t sc2Size;
  };

  std::string dummy_wav_filename = get_output_dir() + u8"dummy_wav_file.wav";

  {
    file dummy_wav_file(
      dummy_wav_filename, file_open_mode::write, file_type::binary);
    wav_metadata data;
    data.id[0] = 'F';
    data.id[1] = 'a';
    data.id[2] = 'K';
    data.id[3] = 'E';
    dummy_wav_file.write(&data, 1u);
  }

  EXPECT_ERROR_0(wav_file_in fi(dummy_wav_filename), invalid_audio_data);

  remove_dir(dummy_wav_filename);
}



TEST_F(test_wav_file_in_death_test, path_constructor_failure_no_wav_header)
{
  std::string dummy_wav_filename = get_output_dir() + u8"dummy_wav_file.wav";

  {
    file dummy_wav_file(
      dummy_wav_filename, file_open_mode::write, file_type::binary);
  }

  EXPECT_ERROR_0(wav_file_in fi(dummy_wav_filename), invalid_audio_data);

  remove_dir(dummy_wav_filename);
}



TEST_F(test_wav_file_in, move_constructor)
{
  wav_file_in fi_dummy(mono16_unicode_filename);
  wav_file_in fi(std::move(fi_dummy));
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



TEST_F(test_wav_file_in, audio_buffer_format_attributes)
{
  wav_file_in fi_mono8(mono8_filename);
  wav_file_in fi_mono16(mono16_filename);
  wav_file_in fi_stereo8(stereo8_filename);
  wav_file_in fi_stereo16(stereo16_filename);

  EXPECT_EQ(audio_buffer_format::mono8, fi_mono8.get_format());
  EXPECT_EQ(1u, fi_mono8.get_channel_count());
  EXPECT_EQ(1u, fi_mono8.get_bytes_per_sample());
  EXPECT_EQ(audio_buffer_format::mono16, fi_mono16.get_format());
  EXPECT_EQ(1u, fi_mono16.get_channel_count());
  EXPECT_EQ(2u, fi_mono16.get_bytes_per_sample());
  EXPECT_EQ(audio_buffer_format::stereo8, fi_stereo8.get_format());
  EXPECT_EQ(2u, fi_stereo8.get_channel_count());
  EXPECT_EQ(1u, fi_stereo8.get_bytes_per_sample());
  EXPECT_EQ(audio_buffer_format::stereo16, fi_stereo16.get_format());
  EXPECT_EQ(2u, fi_stereo16.get_channel_count());
  EXPECT_EQ(2u, fi_stereo16.get_bytes_per_sample());
}



TEST_F(test_wav_file_in, sample_rate_attributes)
{
  wav_file_in fi_normal_rate(mono16_filename);
  wav_file_in fi_low_rate(low_sample_rate_filename);

  EXPECT_EQ(44100u, fi_normal_rate.get_sample_rate());
  EXPECT_EQ(22050u, fi_low_rate.get_sample_rate());
}



TEST_F(test_wav_file_in, get_sample_count)
{
  wav_file_in fi_mono8(mono8_filename);
  wav_file_in fi_mono16(mono16_filename);
  wav_file_in fi_stereo8(stereo8_filename);
  wav_file_in fi_stereo16(stereo16_filename);

  EXPECT_EQ(21231u, fi_mono8.get_sample_count());
  EXPECT_EQ(21231u, fi_mono16.get_sample_count());
  EXPECT_EQ(21231u, fi_stereo8.get_sample_count());
  EXPECT_EQ(21231u, fi_stereo16.get_sample_count());

  EXPECT_EQ(21231u, fi_mono8.get_byte_count());
  EXPECT_EQ(42462u, fi_mono16.get_byte_count());
  EXPECT_EQ(42462u, fi_stereo8.get_byte_count());
  EXPECT_EQ(84924u, fi_stereo16.get_byte_count());
}



TEST_F(test_wav_file_in, set_byte_pos)
{
  wav_file_in fi(mono16_filename);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(6);
  EXPECT_EQ(6, fi.get_byte_pos());
  fi.set_byte_pos(0);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(static_cast<wav_file_in::byte_position>(fi.get_byte_count()));
  EXPECT_EQ(static_cast<wav_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
}



TEST_F(test_wav_file_in_death_test, set_byte_pos_error_position_in_sample)
{
  wav_file_in fi(mono16_filename);
  EXPECT_PRECOND_ERROR(fi.set_byte_pos(3));
  EXPECT_PRECOND_ERROR(fi.set_byte_pos(
    static_cast<wav_file_in::byte_position>(fi.get_byte_count() + 3)));
}



TEST_F(test_wav_file_in_death_test, set_byte_pos_error_invalid_position)
{
  wav_file_in fi(mono16_filename);
  EXPECT_ERROR_0(fi.set_byte_pos(-2), cursor_error);
  EXPECT_ERROR_0(fi.set_byte_pos(static_cast<wav_file_in::byte_position>(
                   fi.get_byte_count() + 2)),
    cursor_error);
}



TEST_F(test_wav_file_in, move_byte_pos)
{
  wav_file_in fi(mono16_filename);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(6);
  EXPECT_EQ(6, fi.get_byte_pos());
  fi.move_byte_pos(-2);
  EXPECT_EQ(4, fi.get_byte_pos());
  fi.move_byte_pos(-4);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(
    static_cast<wav_file_in::byte_position>(fi.get_byte_count()));
  EXPECT_EQ(static_cast<wav_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
}



TEST_F(test_wav_file_in_death_test, move_byte_pos_error_position_in_sample)
{
  wav_file_in fi(mono16_filename);
  fi.move_byte_pos(4);
  EXPECT_PRECOND_ERROR(fi.move_byte_pos(3));
  EXPECT_PRECOND_ERROR(fi.move_byte_pos(
    static_cast<wav_file_in::byte_position>(fi.get_byte_count() + 3)));
}



TEST_F(test_wav_file_in_death_test, move_byte_pos_error_invalid_position)
{
  wav_file_in fi(mono16_filename);
  fi.move_byte_pos(4);
  EXPECT_ERROR_0(fi.move_byte_pos(-6), cursor_error);
  EXPECT_ERROR_0(fi.move_byte_pos(static_cast<wav_file_in::byte_position>(
                   fi.get_byte_count() - 2)),
    cursor_error);
}



TEST_F(test_wav_file_in, set_sample_pos_mono8)
{
  wav_file_in fi(mono8_filename);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.set_sample_pos(3);
  EXPECT_EQ(3, fi.get_byte_pos());
  EXPECT_EQ(3, fi.get_sample_pos());
  fi.set_sample_pos(
    static_cast<wav_file_in::byte_position>(fi.get_sample_count()));
  EXPECT_EQ(static_cast<wav_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  EXPECT_EQ(static_cast<wav_file_in::sample_position>(fi.get_sample_count()),
    fi.get_sample_pos());
}



TEST_F(test_wav_file_in, set_sample_pos_mono16)
{
  wav_file_in fi(mono16_filename);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.set_sample_pos(3);
  EXPECT_EQ(6, fi.get_byte_pos());
  EXPECT_EQ(3, fi.get_sample_pos());
  fi.set_sample_pos(
    static_cast<wav_file_in::byte_position>(fi.get_sample_count()));
  EXPECT_EQ(static_cast<wav_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  EXPECT_EQ(static_cast<wav_file_in::sample_position>(fi.get_sample_count()),
    fi.get_sample_pos());
}



TEST_F(test_wav_file_in, set_sample_pos_stereo8)
{
  wav_file_in fi(stereo8_filename);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.set_sample_pos(3);
  EXPECT_EQ(6, fi.get_byte_pos());
  EXPECT_EQ(3, fi.get_sample_pos());
  fi.set_sample_pos(
    static_cast<wav_file_in::byte_position>(fi.get_sample_count()));
  EXPECT_EQ(static_cast<wav_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  EXPECT_EQ(static_cast<wav_file_in::sample_position>(fi.get_sample_count()),
    fi.get_sample_pos());
}



TEST_F(test_wav_file_in, set_sample_pos_stereo16)
{
  wav_file_in fi(stereo16_filename);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.set_sample_pos(3);
  EXPECT_EQ(12, fi.get_byte_pos());
  EXPECT_EQ(3, fi.get_sample_pos());
  fi.set_sample_pos(
    static_cast<wav_file_in::byte_position>(fi.get_sample_count()));
  EXPECT_EQ(static_cast<wav_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  EXPECT_EQ(static_cast<wav_file_in::sample_position>(fi.get_sample_count()),
    fi.get_sample_pos());
}



TEST_F(test_wav_file_in_death_test, set_sample_pos_error_invalid_position)
{
  wav_file_in fi(mono16_filename);
  EXPECT_ERROR_0(fi.set_sample_pos(-1), cursor_error);
  EXPECT_ERROR_0(fi.set_sample_pos(static_cast<wav_file_in::byte_position>(
                   fi.get_sample_count() + 1)),
    cursor_error);
}



TEST_F(test_wav_file_in, move_sample_pos_mono8)
{
  wav_file_in fi(mono8_filename);

  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.move_sample_pos(3);
  EXPECT_EQ(3, fi.get_byte_pos());
  EXPECT_EQ(3, fi.get_sample_pos());
  fi.move_sample_pos(-1);
  EXPECT_EQ(2, fi.get_byte_pos());
  EXPECT_EQ(2, fi.get_sample_pos());
  fi.move_sample_pos(-2);
  EXPECT_EQ(0, fi.get_byte_pos());
  EXPECT_EQ(0, fi.get_sample_pos());
  fi.move_sample_pos(
    static_cast<wav_file_in::byte_position>(fi.get_sample_count()));
  EXPECT_EQ(static_cast<wav_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  EXPECT_EQ(static_cast<wav_file_in::sample_position>(fi.get_sample_count()),
    fi.get_sample_pos());
}



TEST_F(test_wav_file_in, move_sample_pos_mono16)
{
  wav_file_in fi(mono16_filename);

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
  fi.move_sample_pos(
    static_cast<wav_file_in::byte_position>(fi.get_sample_count()));
  EXPECT_EQ(static_cast<wav_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  EXPECT_EQ(static_cast<wav_file_in::sample_position>(fi.get_sample_count()),
    fi.get_sample_pos());
}



TEST_F(test_wav_file_in, move_sample_pos_stereo8)
{
  wav_file_in fi(stereo8_filename);

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
  fi.move_sample_pos(
    static_cast<wav_file_in::byte_position>(fi.get_sample_count()));
  EXPECT_EQ(static_cast<wav_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  EXPECT_EQ(static_cast<wav_file_in::sample_position>(fi.get_sample_count()),
    fi.get_sample_pos());
}



TEST_F(test_wav_file_in, move_sample_pos_stereo16)
{
  wav_file_in fi(stereo16_filename);

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
  fi.move_sample_pos(
    static_cast<wav_file_in::byte_position>(fi.get_sample_count()));
  EXPECT_EQ(static_cast<wav_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  EXPECT_EQ(static_cast<wav_file_in::sample_position>(fi.get_sample_count()),
    fi.get_sample_pos());
}



TEST_F(test_wav_file_in_death_test, move_sample_pos_error_invalid_position)
{
  wav_file_in fi(mono16_filename);
  fi.move_sample_pos(2);
  EXPECT_ERROR_0(fi.move_sample_pos(-3), cursor_error);
  EXPECT_ERROR_0(fi.move_sample_pos(static_cast<wav_file_in::byte_position>(
                   fi.get_sample_count() - 1)),
    cursor_error);
}



TEST_F(test_wav_file_in, read_to_variable)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 1u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  wav_file_in fi(mono16_unicode_filename);
  buffer_type buffer;

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(12480u, buffer);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(12460, buffer);
}



TEST_F(test_wav_file_in, read_to_basic_array)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  wav_file_in fi(mono16_unicode_filename);
  buffer_type buffer[buffer_size];

  fi.read(buffer, buffer_size);
  buffer_type buffer_ref1[buffer_size] = {12480u, 12460u, 12440u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_ARRAY_EQ(buffer_ref1, buffer, buffer_size);

  fi.read(buffer, buffer_size);
  buffer_type buffer_ref2[buffer_size] = {12420u, 12400u, 12380u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_ARRAY_EQ(buffer_ref2, buffer, buffer_size);
}



TEST_F(test_wav_file_in, read_to_array)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  wav_file_in fi(mono16_unicode_filename);
  std::array<buffer_type, buffer_size> buffer = {0, 0, 0};

  fi.read(buffer);
  std::array<buffer_type, buffer_size> buffer_ref1 = {12480u, 12460u, 12440u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(buffer_ref1, buffer);

  fi.read(buffer);
  std::array<buffer_type, buffer_size> buffer_ref2 = {12420u, 12400u, 12380u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(buffer_ref2, buffer);
}



TEST_F(test_wav_file_in, read_to_vector)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  wav_file_in fi(mono16_unicode_filename);
  std::vector<buffer_type> buffer(buffer_size, 0u);

  fi.read(buffer);
  std::vector<buffer_type> buffer_ref1 = {12480u, 12460u, 12440u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(buffer_ref1, buffer);

  fi.read(buffer);
  std::vector<buffer_type> buffer_ref2 = {12420u, 12400u, 12380u};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size, fi.get_read_sample_count());
  EXPECT_EQ(buffer_ref2, buffer);
}



TEST_F(test_wav_file_in, read_to_string)
{
  using buffer_type = std::string::value_type;
  static constexpr size_t buffer_size = 4u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  wav_file_in fi(mono16_unicode_filename);
  std::string buffer(buffer_size, 0);

  fi.read(buffer);
  std::string buffer_ref1 = {-64, 48, -84, 48};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size / 2, fi.get_read_sample_count());
  EXPECT_EQ(buffer_ref1, buffer);

  fi.read(buffer);
  std::string buffer_ref2 = {-104, 48, -124, 48};
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_EQ(buffer_size / 2, fi.get_read_sample_count());
  EXPECT_EQ(buffer_ref2, buffer);
}



TEST_F(test_wav_file_in_death_test, read_to_invalid_size_buffer)
{
  using buffer_type = uint8_t;
  static constexpr size_t buffer_size = 3u;
  std::vector<buffer_type> buffer(buffer_size, 0u);

  wav_file_in fi(mono16_filename);
  EXPECT_EQ(audio_buffer_format::mono16, fi.get_format());

  EXPECT_PRECOND_ERROR(fi.read(buffer));
}



TEST_F(test_wav_file_in, read_all_to_vector)
{
  wav_file_in fi(mono8_filename);
  std::vector<uint8_t> file_content(fi.get_byte_count());
  fi.read(file_content);
  fi.set_byte_pos(0u);

  auto fi_content = fi.read_all<std::vector<uint8_t>>();
  EXPECT_EQ(file_content, fi_content);
  EXPECT_EQ(file_content.size(), fi.get_read_byte_count());
  EXPECT_EQ(file_content.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(test_wav_file_in, read_all_to_vector_not_from_start)
{
  wav_file_in fi(mono8_filename);
  std::vector<uint8_t> file_content(fi.get_byte_count());
  fi.read(file_content);
  fi.set_byte_pos(2u);

  auto fi_content = fi.read_all<std::vector<uint8_t>>();
  EXPECT_EQ(file_content, fi_content);
  EXPECT_EQ(file_content.size(), fi.get_read_byte_count());
  EXPECT_EQ(file_content.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(test_wav_file_in, eof)
{
  wav_file_in fi(mono16_filename);
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
