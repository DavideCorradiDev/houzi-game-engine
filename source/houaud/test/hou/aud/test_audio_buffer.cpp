// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"
#include "hou/aud/test_aud_base.hpp"
#include "hou/aud/test_data.hpp"

#include "hou/aud/audio_buffer.hpp"
#include "hou/aud/wav_file_in.hpp"

using namespace hou;



namespace
{

class test_audio_buffer : public test_aud_base
{
public:
  static const std::string wav_stereo16_filename;
};



class test_audio_buffer_death_test : public test_audio_buffer
{};



const std::string test_audio_buffer::wav_stereo16_filename
  = get_data_dir() + u8"TestWav-stereo-16-44100.wav";

}  // namespace



TEST_F(test_audio_buffer, default_constructor)
{
  audio_buffer ab;

  EXPECT_NE(0u, ab.get_handle().get_name());
  EXPECT_EQ(2u, ab.get_byte_count());
  EXPECT_EQ(1u, ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::mono16, ab.get_format());
  EXPECT_EQ(1u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(1, ab.get_sample_rate());
}



TEST_F(test_audio_buffer, data_constructor)
{
  std::vector<uint8_t> data{1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u};
  audio_buffer ab(data, audio_buffer_format::stereo16, 345);

  EXPECT_NE(0u, ab.get_handle().get_name());
  EXPECT_EQ(data.size(), ab.get_byte_count());
  EXPECT_EQ(data.size()
      / (get_audio_buffer_format_channel_count(ab.get_format())
          * get_audio_buffer_format_bytes_per_sample(ab.get_format())),
    ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::stereo16, ab.get_format());
  EXPECT_EQ(2u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(345, ab.get_sample_rate());
}



TEST_F(test_audio_buffer, data_move_constructor)
{
  std::vector<uint8_t> data{1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u};
  audio_buffer ab(
    {1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u}, audio_buffer_format::stereo16, 345);

  EXPECT_NE(0u, ab.get_handle().get_name());
  EXPECT_EQ(data.size(), ab.get_byte_count());
  EXPECT_EQ(data.size()
      / (get_audio_buffer_format_channel_count(ab.get_format())
          * get_audio_buffer_format_bytes_per_sample(ab.get_format())),
    ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::stereo16, ab.get_format());
  EXPECT_EQ(2u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(345, ab.get_sample_rate());
}



TEST_F(test_audio_buffer, stream_constructor)
{
  wav_file_in fi(wav_stereo16_filename);
  fi.set_sample_pos(12u);
  audio_buffer ab(fi);

  EXPECT_NE(0u, ab.get_handle().get_name());
  EXPECT_EQ(84924u, ab.get_byte_count());
  EXPECT_EQ(21231u, ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::stereo16, ab.get_format());
  EXPECT_EQ(2u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(44100, ab.get_sample_rate());
  EXPECT_EQ(fi.get_byte_count(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(test_audio_buffer, stream_move_constructor)
{
  audio_buffer ab = audio_buffer(wav_file_in(wav_stereo16_filename));

  EXPECT_NE(0u, ab.get_handle().get_name());
  EXPECT_EQ(84924u, ab.get_byte_count());
  EXPECT_EQ(21231u, ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::stereo16, ab.get_format());
  EXPECT_EQ(2u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(44100, ab.get_sample_rate());
}



TEST_F(test_audio_buffer, move_constructor)
{
  std::vector<uint8_t> data{1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u};
  audio_buffer ab_dummy(data, audio_buffer_format::stereo16, 345);
  ALuint name_ref = ab_dummy.get_handle().get_name();
  audio_buffer ab(std::move(ab_dummy));

  EXPECT_EQ(0u, ab_dummy.get_handle().get_name());
  EXPECT_EQ(name_ref, ab.get_handle().get_name());
  EXPECT_EQ(data.size(), ab.get_byte_count());
  EXPECT_EQ(data.size()
      / (get_audio_buffer_format_channel_count(ab.get_format())
          * get_audio_buffer_format_bytes_per_sample(ab.get_format())),
    ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::stereo16, ab.get_format());
  EXPECT_EQ(2u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(345, ab.get_sample_rate());
}



TEST_F(test_audio_buffer, set_data)
{
  std::vector<uint8_t> data_ref1{1u, 2u, 3u, 4u};
  audio_buffer ab(data_ref1, audio_buffer_format::stereo16, 114);

  EXPECT_EQ(data_ref1.size(), ab.get_byte_count());
  EXPECT_EQ(data_ref1.size()
      / (get_audio_buffer_format_channel_count(ab.get_format())
          * get_audio_buffer_format_bytes_per_sample(ab.get_format())),
    ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::stereo16, ab.get_format());
  EXPECT_EQ(2u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(114, ab.get_sample_rate());

  std::vector<uint8_t> data_ref2{1u, 2u, 3u, 4u, 5u, 6u};
  ab.set_data(data_ref2, audio_buffer_format::mono16, 228);

  EXPECT_EQ(data_ref2.size(), ab.get_byte_count());
  EXPECT_EQ(data_ref2.size()
      / get_audio_buffer_format_bytes_per_sample(ab.get_format()),
    ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::mono16, ab.get_format());
  EXPECT_EQ(1u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(228, ab.get_sample_rate());
}



TEST_F(test_audio_buffer, set_data_with_move)
{
  std::vector<uint8_t> data_ref1{1u, 2u, 3u, 4u};
  audio_buffer ab({1u, 2u, 3u, 4u}, audio_buffer_format::stereo16, 114);

  EXPECT_EQ(data_ref1.size(), ab.get_byte_count());
  EXPECT_EQ(data_ref1.size()
      / (get_audio_buffer_format_channel_count(ab.get_format())
          * get_audio_buffer_format_bytes_per_sample(ab.get_format())),
    ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::stereo16, ab.get_format());
  EXPECT_EQ(2u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(114, ab.get_sample_rate());

  std::vector<uint8_t> data_ref2{1u, 2u, 3u, 4u, 5u, 6u};
  ab.set_data({1u, 2u, 3u, 4u, 5u, 6u}, audio_buffer_format::mono16, 228);

  EXPECT_EQ(data_ref2.size(), ab.get_byte_count());
  EXPECT_EQ(data_ref2.size()
      / get_audio_buffer_format_bytes_per_sample(ab.get_format()),
    ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::mono16, ab.get_format());
  EXPECT_EQ(1u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(228, ab.get_sample_rate());
}



TEST_F(test_audio_buffer, set_data_from_stream)
{
  std::vector<uint8_t> data_ref1{1u, 2u, 3u, 4u};
  audio_buffer ab(data_ref1, audio_buffer_format::stereo16, 114);

  EXPECT_EQ(data_ref1.size(), ab.get_byte_count());
  EXPECT_EQ(data_ref1.size()
      / (get_audio_buffer_format_channel_count(ab.get_format())
          * get_audio_buffer_format_bytes_per_sample(ab.get_format())),
    ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::stereo16, ab.get_format());
  EXPECT_EQ(2u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(114, ab.get_sample_rate());

  wav_file_in fi(wav_stereo16_filename);
  fi.set_sample_pos(4u);
  ab.set_data(fi);

  EXPECT_EQ(84924u, ab.get_byte_count());
  EXPECT_EQ(21231u, ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::stereo16, ab.get_format());
  EXPECT_EQ(2u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(44100, ab.get_sample_rate());
}



TEST_F(test_audio_buffer, set_data_from_stream_with_move)
{
  std::vector<uint8_t> data_ref1{1u, 2u, 3u, 4u};
  audio_buffer ab(data_ref1, audio_buffer_format::stereo16, 114);

  EXPECT_EQ(data_ref1.size(), ab.get_byte_count());
  EXPECT_EQ(data_ref1.size()
      / (get_audio_buffer_format_channel_count(ab.get_format())
          * get_audio_buffer_format_bytes_per_sample(ab.get_format())),
    ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::stereo16, ab.get_format());
  EXPECT_EQ(2u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(114, ab.get_sample_rate());

  ab.set_data(wav_file_in(wav_stereo16_filename));

  EXPECT_EQ(84924u, ab.get_byte_count());
  EXPECT_EQ(21231u, ab.get_sample_count());
  EXPECT_EQ(audio_buffer_format::stereo16, ab.get_format());
  EXPECT_EQ(2u, ab.get_channel_count());
  EXPECT_EQ(2u, ab.get_bytes_per_sample());
  EXPECT_EQ(44100, ab.get_sample_rate());
}



TEST_F(test_audio_buffer, get_mono8_format_measures)
{
  // Note: the implementation might convert the format to a different one.
  // Bits per sample might change from 8 to 16. Samples will then be padded and
  // the size of the buffer will increase.
  std::vector<uint8_t> data{1, 2, 3, 4};
  audio_buffer b(data, audio_buffer_format::mono8, 144);
  EXPECT_EQ(b.get_bytes_per_sample() == 1u ? audio_buffer_format::mono8
                                           : audio_buffer_format::mono16,
    b.get_format());
  EXPECT_EQ(1u, b.get_channel_count());
  EXPECT_TRUE(b.get_bytes_per_sample() == 1u || b.get_bytes_per_sample() == 2u);
  EXPECT_EQ(data.size() * b.get_bytes_per_sample(), b.get_byte_count());
}



TEST_F(test_audio_buffer, get_mono16_format_measures)
{
  std::vector<uint8_t> data{1, 2, 3, 4};
  audio_buffer b(data, audio_buffer_format::mono16, 144);
  EXPECT_EQ(audio_buffer_format::mono16, b.get_format());
  EXPECT_EQ(1u, b.get_channel_count());
  EXPECT_EQ(2u, b.get_bytes_per_sample());
  EXPECT_EQ(data.size(), b.get_byte_count());
}



TEST_F(test_audio_buffer, get_stereo8_format_measures)
{
  // Note: the implementation might convert the format to a different one.
  // Bits per sample might change from 8 to 16. Samples will then be padded and
  // the size of the buffer will increase.
  std::vector<uint8_t> data{1, 2, 3, 4};
  audio_buffer b(data, audio_buffer_format::stereo8, 144);
  EXPECT_EQ(b.get_bytes_per_sample() == 1u ? audio_buffer_format::stereo8
                                           : audio_buffer_format::stereo16,
    b.get_format());
  EXPECT_EQ(2u, b.get_channel_count());
  EXPECT_TRUE(b.get_bytes_per_sample() == 1u || b.get_bytes_per_sample() == 2u);
  EXPECT_EQ(data.size() * b.get_bytes_per_sample(), b.get_byte_count());
}



TEST_F(test_audio_buffer, get_stereo16_format_measures)
{
  std::vector<uint8_t> data{1, 2, 3, 4};
  audio_buffer b(data, audio_buffer_format::stereo16, 144);
  EXPECT_EQ(audio_buffer_format::stereo16, b.get_format());
  EXPECT_EQ(2u, b.get_channel_count());
  EXPECT_EQ(2u, b.get_bytes_per_sample());
  EXPECT_EQ(data.size(), b.get_byte_count());
}
