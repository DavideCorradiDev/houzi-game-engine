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
 * A streaming audio source.
 *
 * This type of audio source streams audio data from an audio stream and stores
 * it internally in a buffer queue. Each instance of this class spawns a thread
 * that automatically takes care of loading the audio data in the background.
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

  // audio_source overrides.
  audio_source_state get_state() const final;

  // streaming_audio_source_base overrides.
  void set_stream(std::unique_ptr<audio_stream_in> as = nullptr) final;
  void set_buffer_count(size_t buffer_count) final;
  void set_buffer_sample_count(size_t buffer_sample_count) final;

protected:
  // audio_source overrides.
  void on_set_looping(bool looping) final;
  void on_set_sample_pos(uint pos) final;
  uint on_get_sample_pos() const final;
  void on_play() final;
  void on_pause() final;

private:
  void thread_function();

private:
  std::thread m_thread;
  std::atomic<bool> m_streaming_thread_end_requested;
  // This mutex controls access to the stream variables (the audio stream,
  // sample position, buffer queue).
  mutable std::mutex m_stream_mutex;
  // This mutex controls acces to the flag to activate buffer processing.
  mutable std::mutex m_processing_buffer_flag_mutex;
  // Two mutexes are required to avoid deadlocks due to recursive locking, since
  // stop() is called in many places.
};

}  // namespace hou

#endif
