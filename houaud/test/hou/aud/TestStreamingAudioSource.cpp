// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/TestAudBase.hpp"
#include "hou/aud/TestData.hpp"

#include "hou/aud/EmptyAudioStreamIn.hpp"
#include "hou/aud/Listener.hpp"
#include "hou/aud/OggFileIn.hpp"
#include "hou/aud/StreamingAudioSource.hpp"

#include "hou/cor/CorError.hpp"

#include "hou/mth/MthUtils.hpp"

using namespace hou;



namespace
{

class TestStreamingAudioSource
  : public TestAudBase
{
public:
  static void SetUpTestCase();

public:
  static const std::string audioFileName;
};



class TestStreamingAudioSourceDeathTest : public TestStreamingAudioSource {};



void TestStreamingAudioSource::SetUpTestCase()
{
  TestAudBase::SetUpTestCase();
  Listener::setGain(0.f);
}




const std::string TestStreamingAudioSource::audioFileName = getDataDir()
  + u8"TestOgg-Stereo-16-44100.ogg";

}



TEST_F(TestStreamingAudioSource, DefaultConstructor)
{
  StreamingAudioSource as;
  EXPECT_EQ(3u, as.getBufferCount());
  EXPECT_EQ(44100u, as.getBufferSampleCount());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(AudioFormat::Mono8, as.getAudioFormat());
  EXPECT_EQ(1u, as.getChannelCount());
  EXPECT_EQ(1u, as.getBytesPerSample());
  EXPECT_EQ(1u, as.getSampleRate());
  EXPECT_EQ(0u, as.getSampleCount());
  EXPECT_EQ(0u, as.getSamplePos());
  EXPECT_EQ(std::chrono::nanoseconds(0), as.getTimePos());
  EXPECT_EQ(std::chrono::nanoseconds(0), as.getDuration());
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



TEST_F(TestStreamingAudioSource, StreamConstructor)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  EXPECT_EQ(3u, as.getBufferCount());
  EXPECT_EQ(44100u / 4u, as.getBufferSampleCount());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(AudioFormat::Stereo16, as.getAudioFormat());
  EXPECT_EQ(2u, as.getChannelCount());
  EXPECT_EQ(2u, as.getBytesPerSample());
  EXPECT_EQ(44100u, as.getSampleRate());
  EXPECT_EQ(21231u, as.getSampleCount());
  EXPECT_EQ(0u, as.getSamplePos());
  EXPECT_EQ(std::chrono::nanoseconds(0), as.getTimePos());
  EXPECT_EQ(std::chrono::nanoseconds(481428571), as.getDuration());
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



TEST_F(TestStreamingAudioSource, SetStreamWhileStopped)
{
  StreamingAudioSource as;
  as.setStream(std::make_unique<OggFileIn>(audioFileName));
  EXPECT_EQ(21231u, as.getSampleCount());
}



TEST_F(TestStreamingAudioSource, SetStreamWhilePlaying)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.setStream(std::make_unique<EmptyAudioStreamIn>());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestStreamingAudioSource, SetStreamWhilePaused)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.pause();
  as.setStream(std::make_unique<EmptyAudioStreamIn>());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestStreamingAudioSource, SetTimePosWhileStopped)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setSamplePos(3u);
  EXPECT_EQ(3u, as.getSamplePos());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestStreamingAudioSource, SetTimePosWhilePlaying)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.setSamplePos(3u);
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestStreamingAudioSource, SetTimePosWhilePaused)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.pause();
  as.setSamplePos(3u);
  EXPECT_EQ(3u, as.getSamplePos());
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestStreamingAudioSource, SetTimePosOverflow)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setSamplePos(21432u);
  EXPECT_EQ(201u, as.getSamplePos());
}



TEST_F(TestStreamingAudioSource, SetLooping)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  EXPECT_TRUE(as.isLooping());
  as.setLooping(false);
  EXPECT_FALSE(as.isLooping());
}



TEST_F(TestStreamingAudioSource, SetTimePosMicroseconds)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  OggFileIn fi(audioFileName);
  EXPECT_EQ(std::chrono::microseconds(0), as.getTimePos());
  EXPECT_EQ(0u, as.getSamplePos());
  as.setTimePos(std::chrono::microseconds(30000));
  EXPECT_EQ(std::chrono::microseconds(30000), as.getTimePos());
  EXPECT_EQ(1323u, as.getSamplePos());
  as.setSamplePos(11025u);
  EXPECT_EQ(std::chrono::microseconds(250000), as.getTimePos());
  EXPECT_EQ(11025u, as.getSamplePos());
}



TEST_F(TestStreamingAudioSource, StopWhileStopped)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.setSamplePos(3u);
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestStreamingAudioSource, StopWhilePlaying)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.setSamplePos(3u);
  as.play();
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestStreamingAudioSource, StopWhilePaused)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.setSamplePos(3u);
  as.play();
  as.pause();
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestStreamingAudioSource, PlayWhileStopped)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestStreamingAudioSource, PlayWhilePlaying)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestStreamingAudioSource, PlayWhilePaused)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.pause();
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestStreamingAudioSource, PauseWhileStopped)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.setSamplePos(3u);
  as.pause();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestStreamingAudioSource, PauseWhilePlaying)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.pause();
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestStreamingAudioSource, PauseWhilePaused)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.pause();
  as.pause();
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestStreamingAudioSource, ReplayWhileStopped)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestStreamingAudioSource, ReplayWhilePlaying)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestStreamingAudioSource, ReplayWhilePaused)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.pause();
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestStreamingAudioSource, PlayWithoutStream)
{
  StreamingAudioSource as;
  as.setLooping(true);
  as.play();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestStreamingAudioSource, SetBufferCount)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  EXPECT_EQ(3u, as.getBufferCount());
  as.setBufferCount(5u);
  EXPECT_EQ(5u, as.getBufferCount());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestStreamingAudioSource, SetBufferCountWhilePlaying)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.setBufferCount(5u);
  EXPECT_EQ(5u, as.getBufferCount());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestStreamingAudioSource, SetBufferCountWhilePaused)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.pause();
  as.setBufferCount(5u);
  EXPECT_EQ(5u, as.getBufferCount());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestStreamingAudioSourceDeathTest, SetBufferCountError)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  HOU_EXPECT_ERROR(as.setBufferCount(0u), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestStreamingAudioSource, SetBufferSampleCount)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setBufferSampleCount(500u);
  EXPECT_EQ(500u, as.getBufferSampleCount());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestStreamingAudioSource, SetBufferSampleCountWhilePlaying)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.setBufferSampleCount(500u);
  EXPECT_EQ(500u, as.getBufferSampleCount());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestStreamingAudioSource, SetBufferSampleCountWhilePaused)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  as.setLooping(true);
  as.play();
  as.pause();
  as.setBufferSampleCount(500u);
  EXPECT_EQ(500u, as.getBufferSampleCount());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestStreamingAudioSourceDeathTest, SetBufferSampleCountError)
{
  StreamingAudioSource as(std::make_unique<OggFileIn>(audioFileName));
  HOU_EXPECT_ERROR(as.setBufferSampleCount(0u), std::logic_error
    , getText(CorError::Precondition));
}

