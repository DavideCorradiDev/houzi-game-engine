// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_STREAMING_AUDIO_SOURCE_HPP
#define HOU_AUD_STREAMING_AUDIO_SOURCE_HPP

#include "hou/aud/AudExport.hpp"
#include "hou/aud/AudioSourceBase.hpp"

#include "hou/aud/AudioBuffer.hpp"

#include "hou/cor/NotNull.hpp"

#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>



namespace hou
{

/** Represents an audio source constantly streaming a buffer.
 *
 *  This class is suited to play long audio buffers, as the buffer must not be
 *  completely loaded in memory but is rather streamed concurrently in smaller
 *  chunks.
 *  For short audio files, it is suggested to use an AudioSource and an
 *  AudioBuffer, as performance is better and as the AudioBuffer can be shared
 *  by multiple AudioSources.
 *  Each StreamingAudioSource object spawns a thread that takes care of loading
 *  part of the audio into a queue of memory buffers.
 *  The thread is destroyed when the StreamingAudioSource is destroyed.
 *  A StreamingAudioSource must be given an AudioStream to play a sound.
 *  The StreamingAudioSource will retain unique ownership of the AudioStream and
 *  will automatically destroy it when necessary.
 *
 *  The buffer queue is defined by the number of buffers and the size of
 *  each buffer.
 *  The default values are 3 buffers, each composed of 44100 bytes.
 *  If necessary it is possible to modify these values with the associated
 *  methods.
 *  Higher number of buffers and higher buffer size will result in higher
 *  memory consumption, but better sound quality.
 */
class HOU_AUD_API StreamingAudioSource : public AudioSourceBase
{
public:
  /** Default constructor.
   *
   *  Creates a StreamingAudioSource object with an EmptyStream.
   */
  StreamingAudioSource();

  /** Stream constructor.
   *
   *  Creates a StreamingAudioSource object with the given audio stream, taking
   *  ownership of it.
   *
   *  \param audioStream the audio stream.
   */
  explicit StreamingAudioSource(
    NotNull<std::unique_ptr<AudioStreamIn>> audioStream);

  /** Destructor.
   */
  virtual ~StreamingAudioSource();
  // Note: no move constructor is implemented at the moment because of
  // difficulty with the streaming thread. The thread should be stopped before
  // copying data around.

  /** Sets the stream and transfers ownership to this object.
   *
   *  \param audioStream the stream.
   */
  void setStream(NotNull<std::unique_ptr<AudioStreamIn>> audioStream);

  /** Sets the number of buffers in the buffer queue.
   *
   *  Throws if passed zero.
   *
   *  \param bufferCount the number of buffers.
   */
  void setBufferCount(size_t bufferCount);

  /** Gets the number of buffers in the buffer queue.
   *
   *  \return the number of buffers.
   */
  size_t getBufferCount() const;

  /** Sets the size in samples of each buffer in the buffer queue.
   *
   *  \param bufferSampleCount the size in samples of each buffer.
   */
  void setBufferSampleCount(size_t bufferSampleCount);

  /** Gets the size in samples of each buffer in the buffer queue.
   *
   *  \return the size in samples of each buffer.
   */
  size_t getBufferSampleCount() const;

  // AudioSourceBase overrides.
  AudioBufferFormat getFormat() const final;
  uint getChannelCount() const final;
  uint getBytesPerSample() const final;
  uint getSampleRate() const final;
  uint getSampleCount() const final;
  void setLooping(bool looping) final;
  bool isLooping() const final;

private:
  class BufferQueue
  {
  public:
    BufferQueue(size_t bufferCount);
    size_t freeBuffers(size_t count);
    const AudioBuffer& fillBuffer(const std::vector<uint8_t>& data,
      AudioBufferFormat format, int sampleRate);
    size_t getFreeBufferCount() const;
    size_t getUsedBufferCount() const;
    size_t getBufferCount() const;

  private:
    std::vector<AudioBuffer> mBuffers;
    std::queue<size_t> mBufferSampleCounts;
    size_t mFreeBufferCount;
    size_t mCurrentIndex;
  };

private:
  void onSetSamplePos(uint pos) final;
  uint onGetSamplePos() const final;

  void threadFunction();
  std::vector<uint8_t> readDataChunk(size_t chunkSize);
  void freeBuffers();
  void fillBuffers();
  void setSamplePosVariable(size_t pos);
  void setSamplePosAndStreamCursor(size_t pos);

private:
  std::thread mThread;
  std::mutex mThreadMutex;
  NotNull<std::unique_ptr<AudioStreamIn>> mAudioStream;
  BufferQueue mBufferQueue;
  std::atomic<bool> mStreamingThreadEndRequested;
  std::atomic<bool> mLooping;
  std::atomic<uint> mSamplePos;
  size_t mBufferByteCount;
};

}  // namespace hou

#endif
