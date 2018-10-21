// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_THREADED_AUDIO_SOURCE_HPP
#define HOU_AUD_THREADED_AUDIO_SOURCE_HPP

#include "hou/aud/streaming_audio_source_base.hpp"

#include "hou/aud/aud_config.hpp"

#include <atomic>
#include <mutex>
#include <thread>



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
 * Each threaded_audio_source object spawns a thread that takes care of
 * loading part of the audio into a queue of memory buffers.
 * The thread is destroyed when the threaded_audio_source is destroyed.
 *
 * A threaded_audio_source must be given an audio_stream to play a sound.
 * The threaded_audio_source will retain unique ownership of the audio_stream
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
class HOU_AUD_API threaded_audio_source final
  : public streaming_audio_source_base
{
public:
  /**
   * Stream constructor.
   *
   * Creates a threaded_audio_source object with the given audio stream,
   * taking ownership of it.
   *
   * \param as the audio stream.
   */
  explicit threaded_audio_source(std::unique_ptr<audio_stream_in> as = nullptr);

  // It is not trivial to move the object because it internally spawns a thread
  // which uses a pointer to this object. Moving the object would invalidate
  // this pointer.
  threaded_audio_source(threaded_audio_source&&) = delete;

  /**
   * Destructor.
   */
  ~threaded_audio_source();

  // streaming_audio_source_base overrides.
  void set_stream(std::unique_ptr<audio_stream_in> as = nullptr) final;
  void set_buffer_count(size_t buffer_count) final;
  void set_buffer_sample_count(size_t buffer_sample_count) final;

private:
  void thread_function();

  // audio_source overrides.
  void on_set_sample_pos(uint pos) final;

private:
  std::thread m_thread;
  std::mutex m_thread_mutex;
  std::atomic<bool> m_streaming_thread_end_requested;
};

}  // namespace hou

#endif
