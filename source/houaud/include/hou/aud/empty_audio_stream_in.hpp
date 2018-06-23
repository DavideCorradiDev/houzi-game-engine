// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_EMPTY_AUDIO_STREAM_IN_HPP
#define HOU_AUD_EMPTY_AUDIO_STREAM_IN_HPP

#include "hou/aud/audio_stream_in.hpp"

#include "hou/aud/aud_config.hpp"



namespace hou
{

/**
 * Class representing a dummy empty input audio stream.
 */
class HOU_AUD_API empty_audio_stream_in : public audio_stream_in
{
public:
  /**
   * default constructor.
   */
  empty_audio_stream_in();

  // stream overrides.
  bool eof() const noexcept final;
  bool error() const noexcept final;
  size_t get_byte_count() const noexcept final;

  // stream_in overrides.
  size_t get_read_byte_count() const noexcept final;
  size_t get_read_element_count() const noexcept final;

  // binary_stream overrides.
  byte_position get_byte_pos() const final;
  binary_stream& set_byte_pos(byte_position pos) final;
  binary_stream& move_byte_pos(byte_offset offset) final;

  // audio_stream overrides.
  size_t get_sample_count() const noexcept final;
  sample_position get_sample_pos() const final;
  audio_stream_in& set_sample_pos(sample_position pos) final;
  audio_stream_in& move_sample_pos(sample_offset offset) final;

private:
  void on_read(void* buf, size_t element_size, size_t buf_size) final;
};

}  // namespace hou

#endif
