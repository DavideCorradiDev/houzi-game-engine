// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/audio_stream_in.hpp"

#include "hou/aud/ogg_file_in.hpp"
#include "hou/aud/wav_file_in.hpp"



namespace hou
{

size_t audio_stream_in::get_read_sample_count() const noexcept
{
  return get_read_byte_count() / (get_channel_count() * get_bytes_per_sample());
}

}  // namespace hou
