// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

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

}



StreamingAudioSource::StreamingAudioSource()
  : StreamingAudioSource(std::make_unique<EmptyAudioStreamIn>())
{}



StreamingAudioSource::StreamingAudioSource
  (NotNull<std::unique_ptr<AudioStreamIn>> audioStream)
  : AudioSourceBase()
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



void StreamingAudioSource::setStream
  (NotNull<std::unique_ptr<AudioStreamIn>> audioStream)
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
  mBufferByteCount = bufferSampleCount * (mAudioStream->getChannelCount()
    * mAudioStream->getBytesPerSample());
}



size_t StreamingAudioSource::getBufferSampleCount() const
{
  return mBufferByteCount / (mAudioStream->getChannelCount()
    * mAudioStream->getBytesPerSample());
}



AudioFormat StreamingAudioSource::getAudioFormat() const
{
  return mAudioStream->getAudioFormat();
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



uint StreamingAudioSource::getSampleCount() const
{
  return mAudioStream->getSampleCount();
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
  uint sampleCount = getSampleCount();
  return sampleCount == 0u ? 0u
    : (mSamplePos + mAlSource.getSampleOffset()) % getSampleCount();
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
  data.resize(mAudioStream->getReadByteCount());
  return data;
}



void StreamingAudioSource::freeBuffers()
{
  size_t processedBuffers = mAlSource.getProcessedBuffers();
  mAlSource.unqueueBuffers(processedBuffers);
  size_t processedBytes = mBufferQueue.freeBuffers(processedBuffers);
  setSamplePosVariable(mSamplePos + processedBytes
    / (mAudioStream->getChannelCount()
    * mAudioStream->getBytesPerSample()));
}



void StreamingAudioSource::fillBuffers()
{
  while(getSampleCount() > 0 && mBufferQueue.getFreeBufferCount() > 0)
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
      mAlSource.queueBuffer(mBufferQueue.fillBuffer(data
        , mAudioStream->getAudioFormat(), mAudioStream->getSampleRate()));
    }
  }
}



void StreamingAudioSource::setSamplePosVariable(size_t pos)
{
  uint sampleCount = getSampleCount();
  mSamplePos = sampleCount == 0u ? 0u : pos % getSampleCount();
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



const al::Buffer& StreamingAudioSource::BufferQueue::fillBuffer
  (const std::vector<uint8_t>& data, AudioFormat format, int sampleRate)
{
  HOU_EXPECT_DEV(mFreeBufferCount > 0);
  al::Buffer& buffer = mBuffers[mCurrentIndex];
  buffer.setData(data, audioBufferFormatToAlBufferFormat(format), sampleRate);
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

}

