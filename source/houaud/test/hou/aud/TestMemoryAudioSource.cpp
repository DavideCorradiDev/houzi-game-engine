// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/TestAudBase.hpp"

#include "hou/aud/AudioBuffer.hpp"
#include "hou/aud/MemoryAudioSource.hpp"

#include "hou/mth/math_functions.hpp"

using namespace hou;



namespace
{

class TestMemoryAudioSource
  : public TestAudBase
{
public:
  TestMemoryAudioSource();

public:
  AudioBuffer mBuffer;
};



TestMemoryAudioSource::TestMemoryAudioSource()
  : TestAudBase()
  , mBuffer(std::vector<uint8_t>{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    , AudioBufferFormat::Stereo16, 2)
{}

}



TEST_F(TestMemoryAudioSource, DefaultConstructor)
{
  MemoryAudioSource as;
  EXPECT_EQ(nullptr, as.getBuffer());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(AudioBufferFormat::Mono8, as.get_format());
  EXPECT_EQ(1u, as.getChannelCount());
  EXPECT_EQ(1u, as.getBytesPerSample());
  EXPECT_EQ(1u, as.getSampleRate());
  EXPECT_EQ(0u, as.getSampleCount());
  EXPECT_EQ(0u, as.getSamplePos());
  EXPECT_EQ(std::chrono::microseconds(0), as.getTimePos());
  EXPECT_EQ(std::chrono::microseconds(0), as.getDuration());
  EXPECT_FALSE(as.isLooping());
  EXPECT_FLOAT_EQ(1.f, as.getPitch());
  EXPECT_FLOAT_EQ(1.f, as.getGain());
  EXPECT_FLOAT_EQ(1.f, as.getMaxGain());
  EXPECT_FLOAT_EQ(0.f, as.getMinGain());
  EXPECT_FLOAT_EQ(std::numeric_limits<float>::max(), as.getMaxDistance());
  EXPECT_FLOAT_EQ(1.f, as.getRolloffFactor());
  EXPECT_FLOAT_EQ(1.f, as.getReferenceDistance());
  EXPECT_FALSE(as.isRelative());
  EXPECT_FLOAT_EQ(0.f, as.getConeOuterGain());
  EXPECT_FLOAT_EQ(2 * pi_f, as.getConeInnerAngle());
  EXPECT_FLOAT_EQ(2 * pi_f, as.getConeOuterAngle());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_position());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.getVelocity());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.getDirection());
}



TEST_F(TestMemoryAudioSource, BufferConstructor)
{
  MemoryAudioSource as(&mBuffer);
  EXPECT_EQ(&mBuffer, as.getBuffer());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(AudioBufferFormat::Stereo16, as.get_format());
  EXPECT_EQ(2u, as.getChannelCount());
  EXPECT_EQ(2u, as.getBytesPerSample());
  EXPECT_EQ(2u, as.getSampleRate());
  EXPECT_EQ(4u, as.getSampleCount());
  EXPECT_EQ(0u, as.getSamplePos());
  EXPECT_EQ(std::chrono::microseconds(0), as.getTimePos());
  EXPECT_EQ(std::chrono::microseconds(2000000), as.getDuration());
  EXPECT_FALSE(as.isLooping());
  EXPECT_FLOAT_EQ(1.f, as.getPitch());
  EXPECT_FLOAT_EQ(1.f, as.getGain());
  EXPECT_FLOAT_EQ(1.f, as.getMaxGain());
  EXPECT_FLOAT_EQ(0.f, as.getMinGain());
  EXPECT_FLOAT_EQ(std::numeric_limits<float>::max(), as.getMaxDistance());
  EXPECT_FLOAT_EQ(1.f, as.getRolloffFactor());
  EXPECT_FLOAT_EQ(1.f, as.getReferenceDistance());
  EXPECT_FALSE(as.isRelative());
  EXPECT_FLOAT_EQ(0.f, as.getConeOuterGain());
  EXPECT_FLOAT_EQ(2 * pi_f, as.getConeInnerAngle());
  EXPECT_FLOAT_EQ(2 * pi_f, as.getConeOuterAngle());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_position());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.getVelocity());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.getDirection());
}



TEST_F(TestMemoryAudioSource, MoveConstructor)
{
  MemoryAudioSource asDummy(&mBuffer);
  MemoryAudioSource as(std::move(asDummy));
  EXPECT_EQ(&mBuffer, as.getBuffer());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(AudioBufferFormat::Stereo16, as.get_format());
  EXPECT_EQ(2u, as.getChannelCount());
  EXPECT_EQ(2u, as.getBytesPerSample());
  EXPECT_EQ(2u, as.getSampleRate());
  EXPECT_EQ(0u, as.getSamplePos());
  EXPECT_EQ(4u, as.getSampleCount());
  EXPECT_EQ(std::chrono::microseconds(0), as.getTimePos());
  EXPECT_EQ(std::chrono::microseconds(2000000), as.getDuration());
  EXPECT_FALSE(as.isLooping());
  EXPECT_FLOAT_EQ(1.f, as.getPitch());
  EXPECT_FLOAT_EQ(1.f, as.getGain());
  EXPECT_FLOAT_EQ(1.f, as.getMaxGain());
  EXPECT_FLOAT_EQ(0.f, as.getMinGain());
  EXPECT_FLOAT_EQ(std::numeric_limits<float>::max(), as.getMaxDistance());
  EXPECT_FLOAT_EQ(1.f, as.getRolloffFactor());
  EXPECT_FLOAT_EQ(1.f, as.getReferenceDistance());
  EXPECT_FALSE(as.isRelative());
  EXPECT_FLOAT_EQ(0.f, as.getConeOuterGain());
  EXPECT_FLOAT_EQ(2 * pi_f, as.getConeInnerAngle());
  EXPECT_FLOAT_EQ(2 * pi_f, as.getConeOuterAngle());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_position());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.getVelocity());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.getDirection());
}



TEST_F(TestMemoryAudioSource, SetBufferWhileStopped)
{
  MemoryAudioSource as;
  as.setBuffer(&mBuffer);
  EXPECT_EQ(&mBuffer, as.getBuffer());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestMemoryAudioSource, SetBufferWhilePlaying)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.setBuffer(nullptr);
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestMemoryAudioSource, SetBufferWhilePaused)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.setBuffer(nullptr);
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestMemoryAudioSource, SetTimePosWhileStopped)
{
  MemoryAudioSource as(&mBuffer);
  as.setSamplePos(3u);
  EXPECT_EQ(3u, as.getSamplePos());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestMemoryAudioSource, SetTimePosWhilePlaying)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.setSamplePos(3u);
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestMemoryAudioSource, SetTimePosWhilePaused)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.setSamplePos(3u);
  EXPECT_EQ(3u, as.getSamplePos());
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestMemoryAudioSource, SetTimePosOverflow)
{
  MemoryAudioSource as(&mBuffer);
  as.setSamplePos(6u);
  EXPECT_EQ(2u, as.getSamplePos());
}



TEST_F(TestMemoryAudioSource, SetTimePosMicroseconds)
{
  MemoryAudioSource as(&mBuffer);
  EXPECT_EQ(std::chrono::microseconds(0), as.getTimePos());
  EXPECT_EQ(0u, as.getSamplePos());
  as.setTimePos(std::chrono::microseconds(1500000));
  EXPECT_EQ(std::chrono::microseconds(1500000), as.getTimePos());
  EXPECT_EQ(3u, as.getSamplePos());
  as.setSamplePos(1u);
  EXPECT_EQ(std::chrono::microseconds(500000), as.getTimePos());
  EXPECT_EQ(1u, as.getSamplePos());
}



TEST_F(TestMemoryAudioSource, SetLooping)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  EXPECT_TRUE(as.isLooping());
  as.setLooping(false);
  EXPECT_FALSE(as.isLooping());
}



TEST_F(TestMemoryAudioSource, StopWhileStopped)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestMemoryAudioSource, StopWhilePlaying)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.play();
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestMemoryAudioSource, StopWhilePaused)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.play();
  as.pause();
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestMemoryAudioSource, PlayWhileStopped)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestMemoryAudioSource, PlayWhilePlaying)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestMemoryAudioSource, PlayWhilePaused)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestMemoryAudioSource, PauseWhileStopped)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.pause();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestMemoryAudioSource, PauseWhilePlaying)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestMemoryAudioSource, PauseWhilePaused)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.pause();
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestMemoryAudioSource, ReplayWhileStopped)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestMemoryAudioSource, ReplayWhilePlaying)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestMemoryAudioSource, ReplayWhilePaused)
{
  MemoryAudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestMemoryAudioSource, PlayWithoutBuffer)
{
  MemoryAudioSource as;
  as.setLooping(true);
  as.play();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}

