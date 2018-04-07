// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/al/TestAlBase.hpp"

#include "hou/al/AlBuffer.hpp"
#include "hou/al/AlSource.hpp"

#include "hou/cor/StdArray.hpp"

using namespace hou;



namespace
{

class TestAlSource : public TestAlBase {};

}



TEST_F(TestAlSource, Creation)
{
  al::Source s;
  std::array<ALfloat, 3u> zeroVec{0.f, 0.f, 0.f};
  EXPECT_NE(0u, s.getHandle().getName());
  EXPECT_FLOAT_EQ(1.f, s.getPitch());
  EXPECT_FLOAT_EQ(1.f, s.getGain());
  EXPECT_FLOAT_EQ(1.f, s.getMaxGain());
  EXPECT_FLOAT_EQ(0.f, s.getMinGain());
  EXPECT_FLOAT_EQ(std::numeric_limits<float>::max(), s.getMaxDistance());
  EXPECT_FLOAT_EQ(1.f, s.getRolloffFactor());
  EXPECT_FLOAT_EQ(0.f, s.getConeOuterGain());
  EXPECT_FLOAT_EQ(360.f, s.getConeInnerAngle());
  EXPECT_FLOAT_EQ(360.f, s.getConeOuterAngle());
  EXPECT_FLOAT_EQ(1.f, s.getReferenceDistance());
  EXPECT_EQ(AL_FALSE, s.isRelative());
  EXPECT_EQ(AL_FALSE, s.isLooping());
  HOU_EXPECT_FLOAT_CLOSE(zeroVec, s.getPosition());
  HOU_EXPECT_FLOAT_CLOSE(zeroVec, s.getVelocity());
  HOU_EXPECT_FLOAT_CLOSE(zeroVec, s.getDirection());
  EXPECT_EQ(al::SourceState::Initial, s.getState());
  EXPECT_FLOAT_EQ(0.f, s.getSecOffset());
  EXPECT_EQ(0, s.getSampleOffset());
  EXPECT_EQ(0, s.getByteOffset());
}



TEST_F(TestAlSource, MoveConstructor)
{
  al::Source sDummy;
  ALuint nameRef = sDummy.getHandle().getName();
  al::Source s(std::move(sDummy));
  std::array<ALfloat, 3u> zeroVec{0.f, 0.f, 0.f};
  EXPECT_EQ(nameRef, s.getHandle().getName());
  EXPECT_FLOAT_EQ(1.f, s.getPitch());
  EXPECT_FLOAT_EQ(1.f, s.getGain());
  EXPECT_FLOAT_EQ(1.f, s.getMaxGain());
  EXPECT_FLOAT_EQ(0.f, s.getMinGain());
  EXPECT_FLOAT_EQ(std::numeric_limits<float>::max(), s.getMaxDistance());
  EXPECT_FLOAT_EQ(1.f, s.getRolloffFactor());
  EXPECT_FLOAT_EQ(0.f, s.getConeOuterGain());
  EXPECT_FLOAT_EQ(360.f, s.getConeInnerAngle());
  EXPECT_FLOAT_EQ(360.f, s.getConeOuterAngle());
  EXPECT_FLOAT_EQ(1.f, s.getReferenceDistance());
  EXPECT_EQ(AL_FALSE, s.isRelative());
  EXPECT_EQ(AL_FALSE, s.isLooping());
  HOU_EXPECT_FLOAT_CLOSE(zeroVec, s.getPosition());
  HOU_EXPECT_FLOAT_CLOSE(zeroVec, s.getVelocity());
  HOU_EXPECT_FLOAT_CLOSE(zeroVec, s.getDirection());
  EXPECT_EQ(al::SourceState::Initial, s.getState());
  EXPECT_FLOAT_EQ(0.f, s.getSecOffset());
  EXPECT_EQ(0, s.getSampleOffset());
  EXPECT_EQ(0, s.getByteOffset());
}



TEST_F(TestAlSource, SetPitch)
{
  al::Source s;
  s.setPitch(0.5f);
  EXPECT_FLOAT_EQ(0.5f, s.getPitch());
}



TEST_F(TestAlSource, SetGain)
{
  al::Source s;
  s.setGain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, s.getGain());
}



TEST_F(TestAlSource, SetMaxGain)
{
  al::Source s;
  s.setMaxGain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, s.getMaxGain());
}



TEST_F(TestAlSource, SetMinGain)
{
  al::Source s;
  s.setMinGain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, s.getMinGain());
}



TEST_F(TestAlSource, SetMaxDistance)
{
  al::Source s;
  s.setMaxDistance(0.5f);
  EXPECT_FLOAT_EQ(0.5f, s.getMaxDistance());
}



TEST_F(TestAlSource, SetRolloffFactor)
{
  al::Source s;
  s.setRolloffFactor(0.5f);
  EXPECT_FLOAT_EQ(0.5f, s.getRolloffFactor());
}



TEST_F(TestAlSource, SetConeOuterGain)
{
  al::Source s;
  s.setConeOuterGain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, s.getConeOuterGain());
}



TEST_F(TestAlSource, SetConeInnerAngle)
{
  al::Source s;
  s.setConeInnerAngle(0.5f);
  EXPECT_FLOAT_EQ(0.5f, s.getConeInnerAngle());
}



TEST_F(TestAlSource, SetConeOuterAngle)
{
  al::Source s;
  s.setConeOuterAngle(0.5f);
  EXPECT_FLOAT_EQ(0.5f, s.getConeOuterAngle());
}



TEST_F(TestAlSource, SetReferenceDistance)
{
  al::Source s;
  s.setReferenceDistance(0.5f);
  EXPECT_FLOAT_EQ(0.5f, s.getReferenceDistance());
}



TEST_F(TestAlSource, SetRelative)
{
  al::Source s;
  s.setRelative(AL_TRUE);
  EXPECT_EQ(AL_TRUE, s.isRelative());
}



TEST_F(TestAlSource, SetLooping)
{
  al::Source s;
  s.setLooping(AL_TRUE);
  EXPECT_EQ(AL_TRUE, s.isLooping());
}



TEST_F(TestAlSource, SetPosition)
{
  al::Source s;
  std::array<ALfloat, 3u> posRef{2.f, 5.f, -3.f};
  s.setPosition(posRef);
  HOU_EXPECT_FLOAT_CLOSE(posRef, s.getPosition());
}



TEST_F(TestAlSource, SetState)
{
  al::Buffer buf
    ( std::vector<uint8_t>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    , al::BufferFormat::Stereo16, 2);
  {
    al::Source s;
    s.setBuffer(buf);
    s.setLooping(true);

    EXPECT_EQ(al::SourceState::Initial, s.getState());
    s.play();
    EXPECT_EQ(al::SourceState::Playing, s.getState());
    s.stop();
    EXPECT_EQ(al::SourceState::Stopped, s.getState());
    s.rewind();
    EXPECT_EQ(al::SourceState::Initial, s.getState());
    s.play();
    EXPECT_EQ(al::SourceState::Playing, s.getState());
    s.pause();
    EXPECT_EQ(al::SourceState::Paused, s.getState());
    s.play();
    EXPECT_EQ(al::SourceState::Playing, s.getState());
    s.pause();
    EXPECT_EQ(al::SourceState::Paused, s.getState());
    s.stop();
    EXPECT_EQ(al::SourceState::Stopped, s.getState());
    s.play();
    EXPECT_EQ(al::SourceState::Playing, s.getState());
    s.rewind();
    EXPECT_EQ(al::SourceState::Initial, s.getState());
    s.play();
    EXPECT_EQ(al::SourceState::Playing, s.getState());
    s.pause();
    EXPECT_EQ(al::SourceState::Paused, s.getState());
    s.rewind();
    EXPECT_EQ(al::SourceState::Initial, s.getState());
  }
}



TEST_F(TestAlSource, SetOffset)
{
  al::Buffer buf
    ( std::vector<uint8_t>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    , al::BufferFormat::Stereo16, 2);
  {
    al::Source s;
    s.setBuffer(buf);

    // Note: a source in the stopped state does not change offset even if
    // requested. For this reason the source is preventively started and paused.
    s.setLooping(true);
    s.play();
    s.pause();

    s.setSecOffset(1.5f);
    EXPECT_FLOAT_EQ(1.5f, s.getSecOffset());
    EXPECT_EQ(3, s.getSampleOffset());
    EXPECT_EQ(12, s.getByteOffset());

    s.setSampleOffset(2);
    EXPECT_FLOAT_EQ(1.f, s.getSecOffset());
    EXPECT_EQ(2, s.getSampleOffset());
    EXPECT_EQ(8, s.getByteOffset());

    // Note: the value gets rounded to the lower multiple of sample size.
    s.setByteOffset(15);
    EXPECT_FLOAT_EQ(1.5f, s.getSecOffset());
    EXPECT_EQ(3, s.getSampleOffset());
    EXPECT_EQ(12, s.getByteOffset());
  }
}

