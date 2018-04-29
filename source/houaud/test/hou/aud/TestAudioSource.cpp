// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/TestAudBase.hpp"

#include "hou/aud/AudioBuffer.hpp"
#include "hou/aud/AudioSource.hpp"

#include "hou/cor/cor_error.hpp"

#include "hou/mth/math_functions.hpp"

using namespace hou;



namespace
{

class TestAudioSource : public TestAudBase
{
public:
  TestAudioSource();

public:
  AudioBuffer mBuffer;
};



class TestAudioSourceDeathTest : public TestAudioSource
{};



class ConcreteAudioSource : public AudioSource
{
public:
  ConcreteAudioSource(const AudioBuffer& buffer);
  ConcreteAudioSource(ConcreteAudioSource&& other);
  virtual ~ConcreteAudioSource();

  AudioBufferFormat get_format() const final;
  uint getChannelCount() const final;
  uint getBytesPerSample() const final;
  uint getSampleRate() const final;
  uint get_sample_count() const final;

  void setLooping(bool looping) final;
  bool isLooping() const final;

private:
  void onSetSamplePos(uint value) final;
  uint onGetSamplePos() const final;

private:
  uint m_sample_count;
  AudioBufferFormat mAudioBufferFormat;
  int mSampleRate;
};



TestAudioSource::TestAudioSource()
  : TestAudBase()
  , mBuffer(
      std::vector<uint8_t>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      AudioBufferFormat::Stereo16, 2)
{}



ConcreteAudioSource::ConcreteAudioSource(const AudioBuffer& buffer)
  : AudioSource()
  , m_sample_count(buffer.get_sample_count())
  , mAudioBufferFormat(buffer.get_format())
  , mSampleRate(buffer.getSampleRate())
{
  al::setSourceBuffer(getHandle(), buffer.getHandle().get_name());
}



ConcreteAudioSource::ConcreteAudioSource(ConcreteAudioSource&& other)
  : AudioSource(std::move(other))
  , m_sample_count(std::move(other.m_sample_count))
  , mAudioBufferFormat(std::move(other.mAudioBufferFormat))
  , mSampleRate(std::move(other.mSampleRate))
{}



ConcreteAudioSource::~ConcreteAudioSource()
{}



AudioBufferFormat ConcreteAudioSource::get_format() const
{
  return mAudioBufferFormat;
}



uint ConcreteAudioSource::getChannelCount() const
{
  return getAudioBufferFormatChannelCount(mAudioBufferFormat);
}



uint ConcreteAudioSource::getBytesPerSample() const
{
  return getAudioBufferFormatBytesPerSample(mAudioBufferFormat);
}



uint ConcreteAudioSource::getSampleRate() const
{
  return mSampleRate;
}



uint ConcreteAudioSource::get_sample_count() const
{
  return m_sample_count;
}



void ConcreteAudioSource::setLooping(bool looping)
{
  AudioSource::setLooping(looping);
}



bool ConcreteAudioSource::isLooping() const
{
  return AudioSource::isLooping();
}



void ConcreteAudioSource::onSetSamplePos(uint value)
{
  AudioSource::onSetSamplePos(value);
}



uint ConcreteAudioSource::onGetSamplePos() const
{
  return AudioSource::onGetSamplePos();
}

}  // namespace



TEST_F(TestAudioSource, DefaultConstructor)
{
  ConcreteAudioSource as(mBuffer);
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(AudioBufferFormat::Stereo16, as.get_format());
  EXPECT_EQ(2u, as.getChannelCount());
  EXPECT_EQ(2u, as.getBytesPerSample());
  EXPECT_EQ(2u, as.getSampleRate());
  EXPECT_EQ(4u, as.get_sample_count());
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



TEST_F(TestAudioSource, MoveConstructor)
{
  ConcreteAudioSource asDummy(mBuffer);
  ConcreteAudioSource as(std::move(asDummy));
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(2u, as.getChannelCount());
  EXPECT_EQ(2u, as.getBytesPerSample());
  EXPECT_EQ(2u, as.getSampleRate());
  EXPECT_EQ(4u, as.get_sample_count());
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



TEST_F(TestAudioSource, SetTimePosWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.setSamplePos(3u);
  EXPECT_EQ(3u, as.getSamplePos());
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
}



TEST_F(TestAudioSource, SetTimePosWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.setSamplePos(3u);
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, SetTimePosWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.setSamplePos(3u);
  EXPECT_EQ(3u, as.getSamplePos());
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestAudioSource, SetTimePosOverflow)
{
  ConcreteAudioSource as(mBuffer);
  as.setSamplePos(6u);
  EXPECT_EQ(2u, as.getSamplePos());
}



TEST_F(TestAudioSource, SetTimePosMicroseconds)
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



TEST_F(TestAudioSource, PosSeconds)
{
  ConcreteAudioSource as(mBuffer);
  as.setTimePos(std::chrono::duration<double>(1.5f));
  EXPECT_EQ(std::chrono::duration<double>(1.5f), as.getTimePos());
  EXPECT_EQ(3u, as.getSamplePos());
}



TEST_F(TestAudioSource, Looping)
{
  ConcreteAudioSource as(mBuffer);
  EXPECT_FALSE(as.isLooping());
  as.setLooping(true);
  EXPECT_TRUE(as.isLooping());
  as.setLooping(false);
  EXPECT_FALSE(as.isLooping());
}



TEST_F(TestAudioSource, StopWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestAudioSource, StopWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.play();
  as.stop();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestAudioSource, StopWhilePaused)
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



TEST_F(TestAudioSource, PlayWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, PlayWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, PlayWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.play();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, PauseWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.setSamplePos(3u);
  as.pause();
  EXPECT_EQ(AudioSourceState::Stopped, as.getState());
  EXPECT_EQ(0u, as.getSamplePos());
}



TEST_F(TestAudioSource, PauseWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestAudioSource, PauseWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.pause();
  EXPECT_EQ(AudioSourceState::Paused, as.getState());
}



TEST_F(TestAudioSource, ReplayWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, ReplayWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, ReplayWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.setLooping(true);
  as.play();
  as.pause();
  as.replay();
  EXPECT_EQ(AudioSourceState::Playing, as.getState());
}



TEST_F(TestAudioSource, Pitch)
{
  ConcreteAudioSource as(mBuffer);
  as.setPitch(3.f);
  EXPECT_FLOAT_EQ(3.f, as.getPitch());
}



TEST_F(TestAudioSource, Gain)
{
  ConcreteAudioSource as(mBuffer);
  as.setGain(3.f);
  EXPECT_FLOAT_EQ(3.f, as.getGain());
}



TEST_F(TestAudioSourceDeathTest, InvalidGain)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(
    as.setGain(-3.f), std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, MaxGain)
{
  ConcreteAudioSource as(mBuffer);
  as.setMaxGain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, as.getMaxGain());
}



TEST_F(TestAudioSourceDeathTest, InvalidMaxGain)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(
    as.setMaxGain(-3.f), std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, MinGain)
{
  ConcreteAudioSource as(mBuffer);
  as.setMinGain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, as.getMinGain());
}



TEST_F(TestAudioSourceDeathTest, InvalidMinGain)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(
    as.setMinGain(-3.f), std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, MaxDistance)
{
  ConcreteAudioSource as(mBuffer);
  as.setMaxDistance(3.f);
  EXPECT_FLOAT_EQ(3.f, as.getMaxDistance());
}



TEST_F(TestAudioSourceDeathTest, InvalidMaxDistance)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(
    as.setMaxDistance(-3.f), std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, RolloffFactor)
{
  ConcreteAudioSource as(mBuffer);
  as.setRolloffFactor(3.f);
  EXPECT_FLOAT_EQ(3.f, as.getRolloffFactor());
}



TEST_F(TestAudioSourceDeathTest, InvalidRolloffFactor)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setRolloffFactor(-3.f), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, ReferenceDistance)
{
  ConcreteAudioSource as(mBuffer);
  as.setReferenceDistance(3.f);
  EXPECT_FLOAT_EQ(3.f, as.getReferenceDistance());
}



TEST_F(TestAudioSourceDeathTest, InvalidReferenceDistance)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setReferenceDistance(-3.f), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, Relative)
{
  ConcreteAudioSource as(mBuffer);
  as.setRelative(true);
  EXPECT_TRUE(as.isRelative());
}



TEST_F(TestAudioSource, ConeOuterGain)
{
  ConcreteAudioSource as(mBuffer);
  as.setConeOuterGain(1.f);
  EXPECT_FLOAT_EQ(1.f, as.getConeOuterGain());
}



TEST_F(TestAudioSourceDeathTest, InvalidConeOuterGain)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setConeOuterGain(-3.f), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, ConeInnerAngle)
{
  ConcreteAudioSource as(mBuffer);
  as.setConeInnerAngle(0.f);
  EXPECT_FLOAT_EQ(0.f, as.getConeInnerAngle());
  as.setConeInnerAngle(pi_f);
  EXPECT_FLOAT_EQ(pi_f, as.getConeInnerAngle());
  as.setConeInnerAngle(2 * pi_f);
  EXPECT_FLOAT_EQ(2 * pi_f, as.getConeInnerAngle());
}



TEST_F(TestAudioSourceDeathTest, InvalidConeInnerAngle)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setConeInnerAngle(-pi_f), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(as.setConeInnerAngle(3 * pi_f), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, ConeOuterAngle)
{
  ConcreteAudioSource as(mBuffer);
  as.setConeOuterAngle(0.f);
  EXPECT_FLOAT_EQ(0.f, as.getConeOuterAngle());
  as.setConeOuterAngle(pi_f);
  EXPECT_FLOAT_EQ(pi_f, as.getConeOuterAngle());
  as.setConeOuterAngle(2 * pi_f);
  EXPECT_FLOAT_EQ(2 * pi_f, as.getConeOuterAngle());
}



TEST_F(TestAudioSourceDeathTest, InvalidConeOuterAngle)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.setConeOuterAngle(-pi_f), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(as.setConeOuterAngle(3 * pi_f), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, Position)
{
  ConcreteAudioSource as(mBuffer);
  vec3f posRef(1.f, -2.f, 3.f);
  as.set_position(posRef);
  HOU_EXPECT_FLOAT_CLOSE(posRef, as.get_position());
}



TEST_F(TestAudioSource, Velocity)
{
  ConcreteAudioSource as(mBuffer);
  vec3f velRef(1.f, -2.f, 3.f);
  as.setVelocity(velRef);
  HOU_EXPECT_FLOAT_CLOSE(velRef, as.getVelocity());
}



TEST_F(TestAudioSource, Direction)
{
  ConcreteAudioSource as(mBuffer);
  vec3f dirRef(1.f, -2.f, 3.f);
  as.setDirection(dirRef);
  HOU_EXPECT_FLOAT_CLOSE(dirRef, as.getDirection());
}
