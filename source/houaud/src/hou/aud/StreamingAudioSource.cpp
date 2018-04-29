// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/StreamingAudioSource.hpp"

#include "hou/aud/AudioStreamIn.hpp"
#include "hou/aud/EmptyAudioStreamIn.hpp"

#include <functional>



namespace hou
{

namespace
{

constexpr size_t sDefaultBufferCount = 3u;
constexpr size_t sDefaultBufferByteCount = 44100u;

}  // namespace



StreamingAudioSource::StreamingAudioSource()
  : StreamingAudioSource(std::make_unique<EmptyAudioStreamIn>())
{}



StreamingAudioSource::StreamingAudioSource(
  not_null<std::unique_ptr<AudioStreamIn>> audioStream)
  : AudioSource()
  , mThread()
  , mThreadMutex()
  , mAudioStream(std::move(audioStream))
  , mBufferQueue(sDefaultBufferCount)
  , mStreamingThreadEndRequested(false)
  , mLooping(false)
  , mSamplePos(0u)
  , mBufferByteCount(sDefaultBufferByteCount)
{
  mAudioStream->setSamplePos(0u);
  mThread = std::thread(std::bind(&StreamingAudioSource::threadFunction, this));
}



StreamingAudioSource::~StreamingAudioSource()
{
  stop();
  mStreamingThreadEndRequested = true;
  mThread.join();
  freeBuffers();
}



void StreamingAudioSource::setStream(
  not_null<std::unique_ptr<AudioStreamIn>> audioStream)
{
  stop();
  std::lock_guard<std::mutex> lock(mThreadMutex);
  mAudioStream = std::move(audioStream);
  setSamplePosAndStreamCursor(0u);
}



void StreamingAudioSource::setBufferCount(size_t bufferCount)
{
  HOU_EXPECT(bufferCount > 0u);
  stop();
  std::lock_guard<std::mutex> lock(mThreadMutex);
  freeBuffers();
  mBufferQueue = BufferQueue(bufferCount);
}



size_t StreamingAudioSource::getBufferCount() const
{
  return mBufferQueue.getBufferCount();
}



void StreamingAudioSource::setBufferSampleCount(size_t bufferSampleCount)
{
  HOU_EXPECT(bufferSampleCount > 0u);
  stop();
  std::lock_guard<std::mutex> lock(mThreadMutex);
  mBufferByteCount = bufferSampleCount
    * (mAudioStream->getChannelCount() * mAudioStream->getBytesPerSample());
}



size_t StreamingAudioSource::getBufferSampleCount() const
{
  return mBufferByteCount
    / (mAudioStream->getChannelCount() * mAudioStream->getBytesPerSample());
}



AudioBufferFormat StreamingAudioSource::get_format() const
{
  return mAudioStream->get_format();
}



uint StreamingAudioSource::getChannelCount() const
{
  return mAudioStream->getChannelCount();
}



uint StreamingAudioSource::getBytesPerSample() const
{
  return mAudioStream->getBytesPerSample();
}



uint StreamingAudioSource::getSampleRate() const
{
  return mAudioStream->getSampleRate();
}



uint StreamingAudioSource::get_sample_count() const
{
  return mAudioStream->get_sample_count();
}



void StreamingAudioSource::setLooping(bool looping)
{
  mLooping = looping;
}



bool StreamingAudioSource::isLooping() const
{
  return mLooping;
}



void StreamingAudioSource::onSetSamplePos(uint value)
{
  std::lock_guard<std::mutex> lock(mThreadMutex);
  freeBuffers();
  setSamplePosAndStreamCursor(value);
  fillBuffers();
}



uint StreamingAudioSource::onGetSamplePos() const
{
  uint sampleCount = get_sample_count();
  return sampleCount == 0u
    ? 0u
    : (mSamplePos + AudioSource::onGetSamplePos()) % get_sample_count();
}



void StreamingAudioSource::threadFunction()
{
  while(!mStreamingThreadEndRequested)
  {
    std::lock_guard<std::mutex> lock(mThreadMutex);
    freeBuffers();
    if(getState() == AudioSourceState::Playing)
    {
      fillBuffers();
    }
  }
}



std::vector<uint8_t> StreamingAudioSource::readDataChunk(size_t chunkSize)
{
  std::vector<uint8_t> data(chunkSize);
  mAudioStream->read(data);
  data.resize(mAudioStream->get_read_byte_count());
  return data;
}



void StreamingAudioSource::freeBuffers()
{
  uint processedBuffers = al::getSourceProcessedBuffers(getHandle());
  std::vector<ALuint> bufferNames(processedBuffers, 0);
  al::sourceUnqueueBuffers(
    getHandle(), static_cast<ALsizei>(bufferNames.size()), bufferNames.data());
  uint processedBytes = mBufferQueue.freeBuffers(processedBuffers);
  setSamplePosVariable(mSamplePos
    + processedBytes
      / (mAudioStream->getChannelCount() * mAudioStream->getBytesPerSample()));
}



void StreamingAudioSource::fillBuffers()
{
  while(get_sample_count() > 0 && mBufferQueue.getFreeBufferCount() > 0)
  {
    std::vector<uint8_t> data = readDataChunk(mBufferByteCount);
    if(data.empty())
    {
      if(mLooping)
      {
        mAudioStream->setSamplePos(0u);
      }
      else
      {
        return;
      }
    }
    else
    {
      ALuint bufferName = mBufferQueue
                            .fillBuffer(data, mAudioStream->get_format(),
                              mAudioStream->getSampleRate())
                            .getHandle()
                            .get_name();
      al::sourceQueueBuffers(getHandle(), 1u, &bufferName);
    }
  }
}



void StreamingAudioSource::setSamplePosVariable(size_t pos)
{
  uint sampleCount = get_sample_count();
  mSamplePos = sampleCount == 0u ? 0u : pos % get_sample_count();
}



void StreamingAudioSource::setSamplePosAndStreamCursor(size_t pos)
{
  setSamplePosVariable(pos);
  mAudioStream->setSamplePos(pos);
}



StreamingAudioSource::BufferQueue::BufferQueue(size_t bufferCount)
  : mBuffers(bufferCount)
  , mBufferSampleCounts()
  , mFreeBufferCount(bufferCount)
  , mCurrentIndex(0u)
{}



size_t StreamingAudioSource::BufferQueue::freeBuffers(size_t count)
{
  mFreeBufferCount += count;
  HOU_ENSURE_DEV(mFreeBufferCount <= mBuffers.size());
  size_t freedBytes = 0u;
  for(uint i = 0; i < count; ++i)
  {
    freedBytes += mBufferSampleCounts.front();
    mBufferSampleCounts.pop();
  }
  return freedBytes;
}



const AudioBuffer& StreamingAudioSource::BufferQueue::fillBuffer(
  const std::vector<uint8_t>& data, AudioBufferFormat format, int sampleRate)
{
  HOU_EXPECT_DEV(mFreeBufferCount > 0);
  AudioBuffer& buffer = mBuffers[mCurrentIndex];
  buffer.setData(data, format, sampleRate);
  mCurrentIndex = (mCurrentIndex + 1) % mBuffers.size();
  --mFreeBufferCount;
  mBufferSampleCounts.push(data.size());
  return buffer;
}



size_t StreamingAudioSource::BufferQueue::getFreeBufferCount() const
{
  return mFreeBufferCount;
}



size_t StreamingAudioSource::BufferQueue::getUsedBufferCount() const
{
  return mBuffers.size() - mFreeBufferCount;
}



size_t StreamingAudioSource::BufferQueue::getBufferCount() const
{
  return mBuffers.size();
}

}  // namespace hou
