// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/audio_stream_in.hpp"

#include "hou/aud/aud_error.hpp"
#include "hou/aud/ogg_file_in.hpp"
#include "hou/aud/wav_file_in.hpp"

#include "hou/cor/cor_error.hpp"
#include "hou/cor/assertions.hpp"



namespace hou
{

audio_stream_in::~audio_stream_in()
{}



size_t audio_stream_in::get_read_sample_count() const
{
  return get_read_byte_count() / (get_channel_count() * get_bytes_per_sample());
}

}  // namespace hou
