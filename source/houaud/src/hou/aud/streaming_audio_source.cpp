// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/streaming_audio_source.hpp"

#include <functional>



namespace hou
{

streaming_audio_source::streaming_audio_source(
  std::unique_ptr<audio_stream_in> as)
  : streaming_audio_source_base(std::move(as))
{}



streaming_audio_source::~streaming_audio_source()
{}



void streaming_audio_source::update()
{
  update_buffer_queue();
}



void streaming_audio_source::set_stream(std::unique_ptr<audio_stream_in> as)
{
  streaming_audio_source_base::set_stream(std::move(as));
}



void streaming_audio_source::set_buffer_count(size_t buffer_count)
{
  streaming_audio_source_base::set_buffer_count(buffer_count);
}



void streaming_audio_source::set_buffer_sample_count(size_t buffer_sample_count)
{
  streaming_audio_source_base::set_buffer_sample_count(buffer_sample_count);
}



void streaming_audio_source::on_set_sample_pos(uint value)
{
  streaming_audio_source_base::on_set_sample_pos(value);
}

}  // namespace hou

