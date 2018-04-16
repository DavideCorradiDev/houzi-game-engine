// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/TestAudBase.hpp"

#include "hou/aud/AudioSourceBase.hpp"

#include "hou/al/AlBuffer.hpp"

#include "hou/cor/CorError.hpp"

#include "hou/mth/MthUtils.hpp"

using namespace hou;



namespace
{

class TestAudioSourceBase
  : public TestAudBase
{
public:
  TestAudioSourceBase();

public:
  al::Buffer mBuffer;
};



class TestAudioSourceBaseDeathTest : public TestAudioSourceBase {};



class ConcreteAudioSource
  : public AudioSourceBase
{
public:
  ConcreteAudioSource(const al::Buffer& buffer);
  ConcreteAudioSource(ConcreteAudioSource&& other);
  virtual ~ConcreteAudioSource();

  AudioFormat getAudioFormat() const final;
  uint getChannelCount() const final;
  uint getBytesPerSample() const final;
  uint getSampleRate() const final;
  uint getSampleCount() const final;

  void setLooping(bool looping) final;
  bool isLooping() const final;

private:
  void onSetSamplePos(uint value) final;
  uint onGetSamplePos() const final;

private:
  uint mSampleCount;
  AudioFormat mAudioFormat;
  int mSampleRate;
};



TestAudioSourceBase::TestAudioSourceBase()
  : TestAudBase()
  , mBuffer(std::vector<uint8_t>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    , al::BufferFormat::Stereo16, 2)
{}



ConcreteAudioSource::ConcreteAudioSource(const al::Buffer& buffer)
  : AudioSourceBase()
  , mSampleCount(buffer.getSize()
    / (al::getBufferFormatChannels(buffer.getFormat())
    * al::getBufferFormatBytesPerSample(buffer.getFormat())))
  , mAudioFormat(alBufferFormatToAudioFormat(buffer.getFormat()))
  , mSampleRate(buffer.getFrequency())
{
  al::setSourceBuffer(getHandle(), buffer.getHandle().getName());
}



ConcreteAudioSource::ConcreteAudioSource(ConcreteAudioSource&& other)
  : AudioSourceBase(std::move(other))
  , mSampleCount(std::move(other.mSampleCount))
  , mAudioFormat(std::move(other.mAudioFormat))
  , mSampleRate(std::move(other.mSampleRate))
{}



ConcreteAudioSource::~ConcreteAudioSource()
{}



AudioFormat ConcreteAudioSource::getAudioFormat() const
{
  return mAudioFormat;
}



uint ConcreteAudioSource::getChannelCount() const
{
  return getAudioFormatChannelCount(mAudioFormat);
}



uint ConcreteAudioSource::getBytesPerSample() const
{
  return getAudioFormatBytesPerSample(mAudioFormat);
}



uint ConcreteAudioSource::getSampleRate() const
{
  return mSampleRate;
}



uint ConcreteAudioSource::getSampleCount() const
{
  return mSampleCount;
}



void ConcreteAudioSource::setLooping(bool looping)
{
  AudioSourceBase::setLooping(looping);
}



bool ConcreteAudioSource::isLooping() const
{
  return AudioSourceBase::isLooping();
}



void ConcreteAudioSource::onSetSamplePos(uint value)
{
  AudioSourceBase::onSetSamplePos(value);
}



uint ConcreteAudioSource::onGetSamplePos() const
{
  return AudioSourceBase::onGetSamplePos();
}

}



TEST_F(TestAudioSourceBase, DefaultConstructor)
{
  ConcreteAudioSource as(mBuffer);
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



TEST_F(TestAudioSourceBase, MoveConstructor)
{
  ConcreteAudioSource asDummy(mBuffer);
  ConcreteAudioSource as(std::move(asDummy));
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
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



TEST_F(TestAudioSourceBase, SetTimePosWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.setSamplePos(3u);
  EXPECT_EQ(3u, as.getSamplePos());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestAudioSourceBase, SetTimePosWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.setSamplePos(3u);
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSourceBase, SetTimePosWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.setSamplePos(3u);
  EXPECT_EQ(3u, as.getSamplePos());
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestAudioSourceBase, SetTimePosOverflow)
{
  ConcreteAudioSource as(mBuffer);
  as.setSamplePos(6u);
  EXPECT_EQ(2u, as.getSamplePos());
}



TEST_F(TestAudioSourceBase, SetTimePosMicroseconds)
{
  ConcreteAudioSource as(mBuffer);
  EXPECT_EQ(std::chrono::microseconds(0), as.getTimePos());
  EXPECT_EQ(0u, as.getSamplePos());
  as.setTimePos(std::chrono::microseconds(1500000));
  EXPECT_EQ(std::chrono::microseconds(1500000), as.getTimePos());
  EXPECT_EQ(3u, as.getSamplePos());
  as.setSamplePos(1u);
  EXPECT_EQ(std::chrono::microseconds(500000), as.getTimePos());
  EXPECT_EQ(1u, as.getSamplePos());
}



TEST_F(TestAudioSourceBase, PosSeconds)
{
  ConcreteAudioSource as(mBuffer);
  as.setTimePos(std::chrono::duration<double>(1.5f));
  EXPECT_EQ(std::chrono::duration<double>(1.5f), as.getTimePos());
  EXPECT_EQ(3u, as.getSamplePos());
}



TEST_F(TestAudioSourceBase, Looping)
{
  ConcreteAudioSource as(mBuffer);
  EXPECT_FALSE(as.isLooping());
  as.setLooping(true);
  EXPECT_TRUE(as.isLooping());
  as.setLooping(false);
  EXPECT_FALSE(as.isLooping());
}



TEST_F(TestAudioSourceBase, StopWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestAudioSourceBase, StopWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.play();
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestAudioSourceBase, StopWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.play();
  as.pause();
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestAudioSourceBase, PlayWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSourceBase, PlayWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSourceBase, PlayWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSourceBase, PauseWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.pause();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestAudioSourceBase, PauseWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestAudioSourceBase, PauseWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.pause();
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestAudioSourceBase, ReplayWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSourceBase, ReplayWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSourceBase, ReplayWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSourceBase, Pitch)
{
  ConcreteAudioSource as(mBuffer);
  as.setPitch(3.f);
  EXPECT_FLOAT_EQ(3.f, as.getPitch());
}



TEST_F(TestAudioSourceBase, Gain)
{
  ConcreteAudioSource as(mBuffer);
  as.setGain(3.f);
  EXPECT_FLOAT_EQ(3.f, as.getGain());
}



TEST_F(TestAudioSourceBaseDeathTest, InvalidGain)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setGain(-3.f), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestAudioSourceBase, MaxGain)
{
  ConcreteAudioSource as(mBuffer);
  as.setMaxGain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, as.getMaxGain());
}



TEST_F(TestAudioSourceBaseDeathTest, InvalidMaxGain)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setMaxGain(-3.f), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestAudioSourceBase, MinGain)
{
  ConcreteAudioSource as(mBuffer);
  as.setMinGain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, as.getMinGain());
}



TEST_F(TestAudioSourceBaseDeathTest, InvalidMinGain)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setMinGain(-3.f), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestAudioSourceBase, MaxDistance)
{
  ConcreteAudioSource as(mBuffer);
  as.setMaxDistance(3.f);
  EXPECT_FLOAT_EQ(3.f, as.getMaxDistance());
}



TEST_F(TestAudioSourceBaseDeathTest, InvalidMaxDistance)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setMaxDistance(-3.f), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestAudioSourceBase, RolloffFactor)
{
  ConcreteAudioSource as(mBuffer);
  as.setRolloffFactor(3.f);
  EXPECT_FLOAT_EQ(3.f, as.getRolloffFactor());
}



TEST_F(TestAudioSourceBaseDeathTest, InvalidRolloffFactor)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setRolloffFactor(-3.f), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestAudioSourceBase, ReferenceDistance)
{
  ConcreteAudioSource as(mBuffer);
  as.setReferenceDistance(3.f);
  EXPECT_FLOAT_EQ(3.f, as.getReferenceDistance());
}



TEST_F(TestAudioSourceBaseDeathTest, InvalidReferenceDistance)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setReferenceDistance(-3.f), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestAudioSourceBase, Relative)
{
  ConcreteAudioSource as(mBuffer);
  as.setRelative(true);
  EXPECT_TRUE(as.isRelative());
}



TEST_F(TestAudioSourceBase, ConeOuterGain)
{
  ConcreteAudioSource as(mBuffer);
  as.setConeOuterGain(1.f);
  EXPECT_FLOAT_EQ(1.f, as.getConeOuterGain());
}



TEST_F(TestAudioSourceBaseDeathTest, InvalidConeOuterGain)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setConeOuterGain(-3.f), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestAudioSourceBase, ConeInnerAngle)
{
  ConcreteAudioSource as(mBuffer);
  as.setConeInnerAngle(0.f);
  EXPECT_FLOAT_EQ(0.f, as.getConeInnerAngle());
  as.setConeInnerAngle(PI_F);
  EXPECT_FLOAT_EQ(PI_F, as.getConeInnerAngle());
  as.setConeInnerAngle(2 * PI_F);
  EXPECT_FLOAT_EQ(2 * PI_F, as.getConeInnerAngle());
}



TEST_F(TestAudioSourceBaseDeathTest, InvalidConeInnerAngle)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setConeInnerAngle(-PI_F), std::logic_error
    , getText(CorError::Precondition));
  HOU_EXPECT_ERROR(as.setConeInnerAngle(3 * PI_F), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestAudioSourceBase, ConeOuterAngle)
{
  ConcreteAudioSource as(mBuffer);
  as.setConeOuterAngle(0.f);
  EXPECT_FLOAT_EQ(0.f, as.getConeOuterAngle());
  as.setConeOuterAngle(PI_F);
  EXPECT_FLOAT_EQ(PI_F, as.getConeOuterAngle());
  as.setConeOuterAngle(2 * PI_F);
  EXPECT_FLOAT_EQ(2 * PI_F, as.getConeOuterAngle());
}



TEST_F(TestAudioSourceBaseDeathTest, InvalidConeOuterAngle)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setConeOuterAngle(-PI_F), std::logic_error
    , getText(CorError::Precondition));
  HOU_EXPECT_ERROR(as.setConeOuterAngle(3 * PI_F), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestAudioSourceBase, Position)
{
  ConcreteAudioSource as(mBuffer);
  Vec3f posRef(1.f, -2.f, 3.f);
  as.setPosition(posRef);
  HOU_EXPECT_FLOAT_CLOSE(posRef, as.getPosition());
}



TEST_F(TestAudioSourceBase, Velocity)
{
  ConcreteAudioSource as(mBuffer);
  Vec3f velRef(1.f, -2.f, 3.f);
  as.setVelocity(velRef);
  HOU_EXPECT_FLOAT_CLOSE(velRef, as.getVelocity());
}



TEST_F(TestAudioSourceBase, Direction)
{
  ConcreteAudioSource as(mBuffer);
  Vec3f dirRef(1.f, -2.f, 3.f);
  as.setDirection(dirRef);
  HOU_EXPECT_FLOAT_CLOSE(dirRef, as.getDirection());
}

