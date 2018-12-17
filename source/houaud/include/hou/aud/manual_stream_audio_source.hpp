// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_MANUAL_STREAM_AUDIO_SOURCE_HPP
#define HOU_AUD_MANUAL_STREAM_AUDIO_SOURCE_HPP

#include "hou/aud/stream_audio_source.hpp"

#include "hou/aud/aud_config.hpp"



namespace hou
{

/**
 * A streaming audio source.
 *
 * This type of audio source streams audio data from an audio stream and stores
 * it internally in a buffer queue. The buffer queue must be periodically
 * updated manually by calling the update() function.
 */
class HOU_AUD_API manual_stream_audio_source final : public stream_audio_source
{
public:
  /**
   * Stream constructor.
   *
   * Creates a manual_stream_audio_source object with the given audio stream,
   * taking ownership of it.
   *
   * \param as the audio stream.
   */
  explicit manual_stream_audio_source(
    std::unique_ptr<audio_stream_in> as = nullptr);

  /**
   * Move constructor.
   *
   * \param other the object to be moved.
   */
  manual_stream_audio_source(manual_stream_audio_source&& other) = default;

  /**
   * Destructor.
   */
  ~manual_stream_audio_source();

  /**
   * Updates the internal audio buffer queue.
   *
   * This function should be called regularly to ensure that the audio buffer
   * queue is up to date and that new data is loaded from the audio stream as
   * soon as free buffers are available.
   */
  void update();

  // audio_source overrides.
  bool is_playing() const final;

  // stream_audio_source overrides.
  void set_stream(std::unique_ptr<audio_stream_in> as = nullptr) final;
  void set_buffer_count(size_t buffer_count) final;
  void set_buffer_sample_count(size_t buffer_sample_count) final;

protected:
  // audio_source overrides.
  void on_set_looping(bool looping) final;
  void on_set_sample_pos(sample_position pos) final;
  sample_position on_get_sample_pos() const final;
  void on_play() final;
  void on_pause() final;
};

}  // namespace hou

#endif

