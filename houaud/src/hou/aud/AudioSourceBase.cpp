// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/aud/AudioSourceBase.hpp"

#include "hou/cor/CorError.hpp"
#include "hou/cor/Error.hpp"

#include "hou/mth/MthUtils.hpp"



namespace hou
{

namespace
{

AudioSourceState alSourceStateToAudioSourceState(al::SourceState state);
uint normalize(uint value, uint max);

AudioSourceState alSourceStateToAudioSourceState(al::SourceState state)
{
  switch(state)
  {
    case al::SourceState::Playing:
      return AudioSourceState::Playing;
    case al::SourceState::Paused:
      return AudioSourceState::Paused;
    case al::SourceState::Stopped:
    case al::SourceState::Initial:
      return AudioSourceState::Stopped;
    default:
      HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), static_cast<int>(state));
      return AudioSourceState::Stopped;
  }
}



uint normalize(uint value, uint max)
{
  return max == 0u ? 0u : value % max;
}

}



AudioSourceBase::AudioSourceBase()
  : NonCopyable()
  , mAlSource()
  , mRequestedSamplePos(0u)
{}



AudioSourceBase::AudioSourceBase(AudioSourceBase&& other)
  : mAlSource(std::move(other.mAlSource))
  , mRequestedSamplePos(std::move(other.mRequestedSamplePos))
{}



AudioSourceBase::~AudioSourceBase()
{}



void AudioSourceBase::play()
{
  if(getState() != AudioSourceState::Playing)
  {
    mAlSource.stop();
    onSetSamplePos(mRequestedSamplePos);
    mAlSource.play();
    // The requested pos has to be set to 0 in case playback ends on its own.
    mRequestedSamplePos = 0u;
  }
}



void AudioSourceBase::pause()
{
  if(getState() != AudioSourceState::Paused)
  {
    mAlSource.pause();
    // The requested pos is updated. Another call to play will resume from
    // the current pos.
    mRequestedSamplePos = onGetSamplePos();
  }
}



void AudioSourceBase::stop()
{
  if(getState() != AudioSourceState::Stopped)
  {
    mAlSource.stop();
  }
  // Stopping resets the pos to 0.
  mRequestedSamplePos = 0u;
}



void AudioSourceBase::replay()
{
  stop();
  play();
}



AudioSourceState AudioSourceBase::getState() const
{
  return alSourceStateToAudioSourceState(mAlSource.getState());
}



void AudioSourceBase::setTimePos(std::chrono::nanoseconds nsPos)
{
  setSamplePos
    ( static_cast<int64_t>(nsPos.count())
    * static_cast<int64_t>(getSampleRate())
    / 1000000000);
}



std::chrono::nanoseconds AudioSourceBase::getTimePos() const
{
  return std::chrono::nanoseconds(static_cast<int64_t>(getSamplePos()) * 1000000000
    / static_cast<int64_t>(getSampleRate()));
}



std::chrono::nanoseconds AudioSourceBase::getDuration() const
{
  return std::chrono::nanoseconds(static_cast<int64_t>(getSampleCount()) * 1000000000
    / static_cast<int64_t>(getSampleRate()));
}



void AudioSourceBase::setSamplePos(uint pos)
{
  if(getState() == AudioSourceState::Playing)
  {
    onSetSamplePos(normalize(pos, getSampleCount()));
  }
  else
  {
    mRequestedSamplePos = normalize(pos, getSampleCount());
  }
}



uint AudioSourceBase::getSamplePos() const
{
  if(getState() == AudioSourceState::Playing)
  {
    return onGetSamplePos();
  }
  else
  {
    return mRequestedSamplePos;
  }
}



void AudioSourceBase::setLooping(bool looping)
{
  mAlSource.setLooping(static_cast<ALboolean>(looping));
}



bool AudioSourceBase::isLooping() const
{
  return static_cast<bool>(mAlSource.isLooping());
}



void AudioSourceBase::setPitch(float value)
{
  HOU_EXPECT(value >= 0.f);
  mAlSource.setPitch(static_cast<ALfloat>(value));
}



float AudioSourceBase::getPitch() const
{
  return mAlSource.getPitch();
}



void AudioSourceBase::setGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  mAlSource.setGain(static_cast<ALfloat>(value));
}



float AudioSourceBase::getGain() const
{
  return mAlSource.getGain();
}



void AudioSourceBase::setMaxGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  mAlSource.setMaxGain(static_cast<ALfloat>(value));
}



float AudioSourceBase::getMaxGain() const
{
  return mAlSource.getMaxGain();
}



void AudioSourceBase::setMinGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  mAlSource.setMinGain(static_cast<ALfloat>(value));
}



float AudioSourceBase::getMinGain() const
{
  return mAlSource.getMinGain();
}



void AudioSourceBase::setMaxDistance(float value)
{
  HOU_EXPECT(value >= 0.f);
  mAlSource.setMaxDistance(static_cast<ALfloat>(value));
}



float AudioSourceBase::getMaxDistance() const
{
  return mAlSource.getMaxDistance();
}



void AudioSourceBase::setRolloffFactor(float value)
{
  HOU_EXPECT(value >= 0.f);
  mAlSource.setRolloffFactor(static_cast<ALfloat>(value));
}



float AudioSourceBase::getRolloffFactor() const
{
  return mAlSource.getRolloffFactor();
}



void AudioSourceBase::setReferenceDistance(float value)
{
  HOU_EXPECT(value >= 0.f);
  mAlSource.setReferenceDistance(static_cast<ALfloat>(value));
}



float AudioSourceBase::getReferenceDistance() const
{
  return mAlSource.getReferenceDistance();
}



void AudioSourceBase::setRelative(bool value)
{
  mAlSource.setRelative(static_cast<ALfloat>(value));
}



bool AudioSourceBase::isRelative() const
{
  return static_cast<bool>(mAlSource.isRelative());
}



void AudioSourceBase::setConeOuterGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  mAlSource.setConeOuterGain(static_cast<ALfloat>(value));
}



float AudioSourceBase::getConeOuterGain() const
{
  return mAlSource.getConeOuterGain();
}



void AudioSourceBase::setConeInnerAngle(float value)
{
  HOU_EXPECT(value >= 0.f && value <= 2.f * PI_F);
  mAlSource.setConeInnerAngle(radToDeg(value));
}



float AudioSourceBase::getConeInnerAngle() const
{
  return degToRad(mAlSource.getConeInnerAngle());
}



void AudioSourceBase::setConeOuterAngle(float value)
{
  HOU_EXPECT(value >= 0.f && value <= 2.f * PI_F);
  mAlSource.setConeOuterAngle(radToDeg(value));
}



float AudioSourceBase::getConeOuterAngle() const
{
  return degToRad(mAlSource.getConeOuterAngle());
}



void AudioSourceBase::setPosition(const Vec3f& pos)
{
  mAlSource.setPosition(std::array<ALfloat, 3u>{pos.x(), pos.y(), pos.z()});
}



Vec3f AudioSourceBase::getPosition() const
{
  std::array<ALfloat, 3u> pos = mAlSource.getPosition();
  return Vec3f(pos[0], pos[1], pos[2]);
}



void AudioSourceBase::setVelocity(const Vec3f& vel)
{
  mAlSource.setVelocity(std::array<ALfloat, 3u>{vel.x(), vel.y(), vel.z()});
}



Vec3f AudioSourceBase::getVelocity() const
{
  std::array<ALfloat, 3u> vel = mAlSource.getVelocity();
  return Vec3f(vel[0], vel[1], vel[2]);
}



void AudioSourceBase::setDirection(const Vec3f& dir)
{
  mAlSource.setDirection(std::array<ALfloat, 3u>{dir.x(), dir.y(), dir.z()});
}



Vec3f AudioSourceBase::getDirection() const
{
  std::array<ALfloat, 3u> dir = mAlSource.getDirection();
  return Vec3f(dir[0], dir[1], dir[2]);
}



void AudioSourceBase::onSetSamplePos(uint pos)
{
  mAlSource.setSampleOffset(static_cast<ALint>(pos));
}



uint AudioSourceBase::onGetSamplePos() const
{
  return static_cast<uint>(mAlSource.getSampleOffset());
}

}

