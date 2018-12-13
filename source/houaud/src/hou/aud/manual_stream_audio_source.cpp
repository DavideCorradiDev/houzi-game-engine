// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/manual_stream_audio_source.hpp"

#include <functional>



namespace hou
{

manual_stream_audio_source::manual_stream_audio_source(
  std::unique_ptr<audio_stream_in> as)
  : stream_audio_source(std::move(as))
{}



manual_stream_audio_source::~manual_stream_audio_source()
{}



void manual_stream_audio_source::update()
{
  update_buffer_queue();
}



audio_source_state manual_stream_audio_source::get_state() const
{
  return stream_audio_source::get_state();
}



void manual_stream_audio_source::set_stream(std::unique_ptr<audio_stream_in> as)
{
  stream_audio_source::set_stream(std::move(as));
}



void manual_stream_audio_source::set_buffer_count(size_t buffer_count)
{
  stream_audio_source::set_buffer_count(buffer_count);
}



void manual_stream_audio_source::set_buffer_sample_count(
  size_t buffer_sample_count)
{
  stream_audio_source::set_buffer_sample_count(buffer_sample_count);
}



void manual_stream_audio_source::on_set_looping(bool looping)
{
  stream_audio_source::on_set_looping(looping);
}



void manual_stream_audio_source::on_set_sample_pos(uint value)
{
  stream_audio_source::on_set_sample_pos(value);
}



uint manual_stream_audio_source::on_get_sample_pos() const
{
  return stream_audio_source::on_get_sample_pos();
}



void manual_stream_audio_source::on_play()
{
  stream_audio_source::on_play();
}



void manual_stream_audio_source::on_pause()
{
  stream_audio_source::on_pause();
}

}  // namespace hou

