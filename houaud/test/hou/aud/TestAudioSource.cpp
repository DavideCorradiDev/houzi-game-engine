// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/TestAudBase.hpp"

#include "hou/aud/AudioBuffer.hpp"
#include "hou/aud/AudioSource.hpp"

#include "hou/mth/MthUtils.hpp"

using namespace hou;



namespace
{

class TestAudioSource
  : public TestAudBase
{
public:
  TestAudioSource();

public:
  AudioBuffer mBuffer;
};



TestAudioSource::TestAudioSource()
  : TestAudBase()
  , mBuffer(std::vector<uint8_t>{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    , AudioFormat::Stereo16, 2)
{}

}



TEST_F(TestAudioSource, DefaultConstructor)
{
  AudioSource as;
  EXPECT_EQ(nullptr, as.getBuffer());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(AudioFormat::Mono8, as.getAudioFormat());
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
  EXPECT_FLOAT_EQ(2 * PI_F, as.getConeInnerAngle());
  EXPECT_FLOAT_EQ(2 * PI_F, as.getConeOuterAngle());
  HOU_EXPECT_FLOAT_CLOSE(Vec3f::zero(), as.getPosition());
  HOU_EXPECT_FLOAT_CLOSE(Vec3f::zero(), as.getVelocity());
  HOU_EXPECT_FLOAT_CLOSE(Vec3f::zero(), as.getDirection());
}



TEST_F(TestAudioSource, BufferConstructor)
{
  AudioSource as(&mBuffer);
  EXPECT_EQ(&mBuffer, as.getBuffer());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(AudioFormat::Stereo16, as.getAudioFormat());
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
  EXPECT_FLOAT_EQ(2 * PI_F, as.getConeInnerAngle());
  EXPECT_FLOAT_EQ(2 * PI_F, as.getConeOuterAngle());
  HOU_EXPECT_FLOAT_CLOSE(Vec3f::zero(), as.getPosition());
  HOU_EXPECT_FLOAT_CLOSE(Vec3f::zero(), as.getVelocity());
  HOU_EXPECT_FLOAT_CLOSE(Vec3f::zero(), as.getDirection());
}



TEST_F(TestAudioSource, MoveConstructor)
{
  AudioSource asDummy(&mBuffer);
  AudioSource as(std::move(asDummy));
  EXPECT_EQ(&mBuffer, as.getBuffer());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(AudioFormat::Stereo16, as.getAudioFormat());
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
  EXPECT_FLOAT_EQ(2 * PI_F, as.getConeInnerAngle());
  EXPECT_FLOAT_EQ(2 * PI_F, as.getConeOuterAngle());
  HOU_EXPECT_FLOAT_CLOSE(Vec3f::zero(), as.getPosition());
  HOU_EXPECT_FLOAT_CLOSE(Vec3f::zero(), as.getVelocity());
  HOU_EXPECT_FLOAT_CLOSE(Vec3f::zero(), as.getDirection());
}



TEST_F(TestAudioSource, SetBufferWhileStopped)
{
  AudioSource as;
  as.setBuffer(&mBuffer);
  EXPECT_EQ(&mBuffer, as.getBuffer());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestAudioSource, SetBufferWhilePlaying)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.setBuffer(nullptr);
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestAudioSource, SetBufferWhilePaused)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.setBuffer(nullptr);
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestAudioSource, SetTimePosWhileStopped)
{
  AudioSource as(&mBuffer);
  as.setSamplePos(3u);
  EXPECT_EQ(3u, as.getSamplePos());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestAudioSource, SetTimePosWhilePlaying)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.setSamplePos(3u);
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, SetTimePosWhilePaused)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.setSamplePos(3u);
  EXPECT_EQ(3u, as.getSamplePos());
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestAudioSource, SetTimePosOverflow)
{
  AudioSource as(&mBuffer);
  as.setSamplePos(6u);
  EXPECT_EQ(2u, as.getSamplePos());
}



TEST_F(TestAudioSource, SetTimePosMicroseconds)
{
  AudioSource as(&mBuffer);
  EXPECT_EQ(std::chrono::microseconds(0), as.getTimePos());
  EXPECT_EQ(0u, as.getSamplePos());
  as.setTimePos(std::chrono::microseconds(1500000));
  EXPECT_EQ(std::chrono::microseconds(1500000), as.getTimePos());
  EXPECT_EQ(3u, as.getSamplePos());
  as.setSamplePos(1u);
  EXPECT_EQ(std::chrono::microseconds(500000), as.getTimePos());
  EXPECT_EQ(1u, as.getSamplePos());
}



TEST_F(TestAudioSource, SetLooping)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  EXPECT_TRUE(as.isLooping());
  as.setLooping(false);
  EXPECT_FALSE(as.isLooping());
}



TEST_F(TestAudioSource, StopWhileStopped)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestAudioSource, StopWhilePlaying)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.play();
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestAudioSource, StopWhilePaused)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.play();
  as.pause();
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestAudioSource, PlayWhileStopped)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, PlayWhilePlaying)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, PlayWhilePaused)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, PauseWhileStopped)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.pause();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestAudioSource, PauseWhilePlaying)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestAudioSource, PauseWhilePaused)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.pause();
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestAudioSource, ReplayWhileStopped)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, ReplayWhilePlaying)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, ReplayWhilePaused)
{
  AudioSource as(&mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, PlayWithoutBuffer)
{
  AudioSource as;
  as.setLooping(true);
  as.play();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}

