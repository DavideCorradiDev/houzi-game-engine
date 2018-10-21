// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_STREAMING_AUDIO_SOURCE_HPP
#define HOU_AUD_STREAMING_AUDIO_SOURCE_HPP

#include "hou/aud/streaming_audio_source_base.hpp"

#include "hou/aud/aud_config.hpp"



namespace hou
{

/**
 * Represents an audio source constantly streaming a buffer.
 *
 * This class is suited to play long audio buffers, as the buffer must not be
 * completely loaded in memory but is rather streamed concurrently in smaller
 * chunks.
 * For short audio files, it is suggested to use an memory_audio_source and an
 * audio_buffer, as performance is better and as the audio_buffer can be shared
 * by multiple memory_audio_source objects.
 *
 * Each streaming_audio_source object spawns a thread that takes care of
 * loading part of the audio into a queue of memory buffers.
 * The thread is destroyed when the streaming_audio_source is destroyed.
 *
 * A streaming_audio_source must be given an audio_stream to play a sound.
 * The streaming_audio_source will retain unique ownership of the audio_stream
 * and will automatically destroy it.
 *
 * The buffer queue is defined by the number of buffers and the size of
 * each buffer.
 * The default values are 3 buffers, each composed of 44100 bytes.
 * This configuration should work well for most applications.
 * If necessary it is possible to modify these values with the associated
 * methods.
 * Higher number of buffers and higher buffer size will result in higher
 * memory consumption, but potentially better sound quality.
 */
class HOU_AUD_API streaming_audio_source final
  : public streaming_audio_source_base
{
public:
  /**
   * Stream constructor.
   *
   * Creates a streaming_audio_source object with the given audio stream,
   * taking ownership of it.
   *
   * \param as the audio stream.
   */
  explicit streaming_audio_source(
    std::unique_ptr<audio_stream_in> as = nullptr);

  /**
   * Move constructor.
   *
   * \param other the object to be moved.
   */
  streaming_audio_source(streaming_audio_source&& other) = default;

  /**
   * Destructor.
   */
  ~streaming_audio_source();

  /**
   * Updates the internal audio buffer queue.
   *
   * This function should be called regularly to ensure that the audio buffer
   * queue is up to date and that new data is loaded from the audio stream as
   * soon as free buffers are available.
   */
  void update();

  // streaming_audio_source_base overrides.
  void set_stream(std::unique_ptr<audio_stream_in> as = nullptr) final;
  void set_buffer_count(size_t buffer_count) final;
  void set_buffer_sample_count(size_t buffer_sample_count) final;

private:
  // audio_source overrides.
  void on_set_sample_pos(uint pos) final;
};

}  // namespace hou

#endif

