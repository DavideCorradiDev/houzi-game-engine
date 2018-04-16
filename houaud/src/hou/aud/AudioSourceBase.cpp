// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

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

}  // namespace



AudioSourceBase::AudioSourceBase()
  : NonCopyable()
  , mHandle(al::SourceHandle::generate())
  , mRequestedSamplePos(0u)
{}



AudioSourceBase::AudioSourceBase(AudioSourceBase&& other)
  : mHandle(std::move(other.mHandle))
  , mRequestedSamplePos(std::move(other.mRequestedSamplePos))
{}



AudioSourceBase::~AudioSourceBase()
{}



const al::SourceHandle& AudioSourceBase::getHandle() const
{
  return mHandle;
}



void AudioSourceBase::play()
{
  if(getState() != AudioSourceState::Playing)
  {
    al::stopSource(mHandle);
    onSetSamplePos(mRequestedSamplePos);
    al::playSource(mHandle);
    // The requested pos has to be set to 0 in case playback ends on its own.
    mRequestedSamplePos = 0u;
  }
}



void AudioSourceBase::pause()
{
  if(getState() != AudioSourceState::Paused)
  {
    al::pauseSource(mHandle);
    // The requested pos is updated. Another call to play will resume from
    // the current pos.
    mRequestedSamplePos = onGetSamplePos();
  }
}



void AudioSourceBase::stop()
{
  if(getState() != AudioSourceState::Stopped)
  {
    al::stopSource(mHandle);
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
  return alSourceStateToAudioSourceState(al::getSourceState(mHandle));
}



void AudioSourceBase::setTimePos(std::chrono::nanoseconds nsPos)
{
  setSamplePos(static_cast<int64_t>(nsPos.count())
    * static_cast<int64_t>(getSampleRate()) / 1000000000);
}



std::chrono::nanoseconds AudioSourceBase::getTimePos() const
{
  return std::chrono::nanoseconds(static_cast<int64_t>(getSamplePos())
    * 1000000000 / static_cast<int64_t>(getSampleRate()));
}



std::chrono::nanoseconds AudioSourceBase::getDuration() const
{
  return std::chrono::nanoseconds(static_cast<int64_t>(getSampleCount())
    * 1000000000 / static_cast<int64_t>(getSampleRate()));
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
  al::setSourceLooping(mHandle, static_cast<ALboolean>(looping));
}



bool AudioSourceBase::isLooping() const
{
  return static_cast<bool>(al::getSourceLooping(mHandle));
}



void AudioSourceBase::setPitch(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourcePitch(mHandle, static_cast<ALfloat>(value));
}



float AudioSourceBase::getPitch() const
{
  return static_cast<float>(al::getSourcePitch(mHandle));
}



void AudioSourceBase::setGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceGain(mHandle, static_cast<ALfloat>(value));
}



float AudioSourceBase::getGain() const
{
  return static_cast<float>(al::getSourceGain(mHandle));
}



void AudioSourceBase::setMaxGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceMaxGain(mHandle, static_cast<ALfloat>(value));
}



float AudioSourceBase::getMaxGain() const
{
  return static_cast<float>(al::getSourceMaxGain(mHandle));
}



void AudioSourceBase::setMinGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceMinGain(mHandle, static_cast<ALfloat>(value));
}



float AudioSourceBase::getMinGain() const
{
  return static_cast<float>(al::getSourceMinGain(mHandle));
}



void AudioSourceBase::setMaxDistance(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceMaxDistance(mHandle, static_cast<ALfloat>(value));
}



float AudioSourceBase::getMaxDistance() const
{
  return static_cast<float>(al::getSourceMaxDistance(mHandle));
}



void AudioSourceBase::setRolloffFactor(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceRolloffFactor(mHandle, static_cast<ALfloat>(value));
}



float AudioSourceBase::getRolloffFactor() const
{
  return static_cast<float>(al::getSourceRolloffFactor(mHandle));
}



void AudioSourceBase::setReferenceDistance(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceReferenceDistance(mHandle, static_cast<ALfloat>(value));
}



float AudioSourceBase::getReferenceDistance() const
{
  return static_cast<float>(al::getSourceReferenceDistance(mHandle));
}



void AudioSourceBase::setRelative(bool value)
{
  al::setSourceRelative(mHandle, static_cast<ALfloat>(value));
}



bool AudioSourceBase::isRelative() const
{
  return static_cast<bool>(al::getSourceRelative(mHandle));
}



void AudioSourceBase::setConeOuterGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceConeOuterGain(mHandle, static_cast<ALfloat>(value));
}



float AudioSourceBase::getConeOuterGain() const
{
  return static_cast<float>(al::getSourceConeOuterGain(mHandle));
}



void AudioSourceBase::setConeInnerAngle(float value)
{
  HOU_EXPECT(value >= 0.f && value <= 2.f * PI_F);
  al::setSourceConeInnerAngle(mHandle, static_cast<ALfloat>(radToDeg(value)));
}



float AudioSourceBase::getConeInnerAngle() const
{
  return degToRad(static_cast<float>(al::getSourceConeInnerAngle(mHandle)));
}



void AudioSourceBase::setConeOuterAngle(float value)
{
  HOU_EXPECT(value >= 0.f && value <= 2.f * PI_F);
  al::setSourceConeOuterAngle(mHandle, static_cast<ALfloat>(radToDeg(value)));
}



float AudioSourceBase::getConeOuterAngle() const
{
  return degToRad(static_cast<float>(al::getSourceConeOuterAngle(mHandle)));
}



void AudioSourceBase::setPosition(const Vec3f& pos)
{
  al::setSourcePosition(mHandle, static_cast<const ALfloat*>(pos.data()));
}



Vec3f AudioSourceBase::getPosition() const
{
  Vec3f retval;
  al::getSourcePosition(
    mHandle, static_cast<ALfloat*>(const_cast<float*>(retval.data())));
  return retval;
}



void AudioSourceBase::setVelocity(const Vec3f& vel)
{
  al::setSourceVelocity(mHandle, static_cast<const ALfloat*>(vel.data()));
}



Vec3f AudioSourceBase::getVelocity() const
{
  Vec3f retval;
  al::getSourceVelocity(
    mHandle, static_cast<ALfloat*>(const_cast<float*>(retval.data())));
  return retval;
}



void AudioSourceBase::setDirection(const Vec3f& dir)
{
  al::setSourceDirection(mHandle, static_cast<const ALfloat*>(dir.data()));
}



Vec3f AudioSourceBase::getDirection() const
{
  Vec3f retval;
  al::getSourceDirection(
    mHandle, static_cast<ALfloat*>(const_cast<float*>(retval.data())));
  return retval;
}



void AudioSourceBase::onSetSamplePos(uint pos)
{
  al::setSourceSampleOffset(mHandle, static_cast<ALint>(pos));
}



uint AudioSourceBase::onGetSamplePos() const
{
  return static_cast<uint>(al::getSourceSampleOffset(mHandle));
}

}  // namespace hou
