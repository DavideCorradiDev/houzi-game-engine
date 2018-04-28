// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudioSource.hpp"

#include "hou/cor/cor_error.hpp"
#include "hou/cor/error.hpp"

#include "hou/mth/MathFunctions.hpp"



namespace hou
{

namespace
{

AudioSourceState alSourceStateToAudioSourceState(ALenum state);
uint normalize(uint value, uint max);

AudioSourceState alSourceStateToAudioSourceState(ALenum state)
{
  switch(state)
  {
  case AL_PLAYING:
    return AudioSourceState::Playing;
  case AL_PAUSED:
    return AudioSourceState::Paused;
  case AL_INITIAL:
  case AL_STOPPED:
    return AudioSourceState::Stopped;
  default:
    HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<int>(state));
    return AudioSourceState::Stopped;
  }
}



uint normalize(uint value, uint max)
{
  return max == 0u ? 0u : value % max;
}

}  // namespace



AudioSource::AudioSource()
  : non_copyable()
  , mHandle(al::SourceHandle::generate())
  , mRequestedSamplePos(0u)
{}



AudioSource::AudioSource(AudioSource&& other)
  : mHandle(std::move(other.mHandle))
  , mRequestedSamplePos(std::move(other.mRequestedSamplePos))
{}



AudioSource::~AudioSource()
{}



const al::SourceHandle& AudioSource::getHandle() const
{
  return mHandle;
}



void AudioSource::play()
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



void AudioSource::pause()
{
  if(getState() != AudioSourceState::Paused)
  {
    al::pauseSource(mHandle);
    // The requested pos is updated. Another call to play will resume from
    // the current pos.
    mRequestedSamplePos = onGetSamplePos();
  }
}



void AudioSource::stop()
{
  if(getState() != AudioSourceState::Stopped)
  {
    al::stopSource(mHandle);
  }
  // Stopping resets the pos to 0.
  mRequestedSamplePos = 0u;
}



void AudioSource::replay()
{
  stop();
  play();
}



AudioSourceState AudioSource::getState() const
{
  return alSourceStateToAudioSourceState(al::getSourceState(mHandle));
}



void AudioSource::setTimePos(std::chrono::nanoseconds nsPos)
{
  setSamplePos(static_cast<int64_t>(nsPos.count())
    * static_cast<int64_t>(getSampleRate()) / 1000000000);
}



std::chrono::nanoseconds AudioSource::getTimePos() const
{
  return std::chrono::nanoseconds(static_cast<int64_t>(getSamplePos())
    * 1000000000 / static_cast<int64_t>(getSampleRate()));
}



std::chrono::nanoseconds AudioSource::getDuration() const
{
  return std::chrono::nanoseconds(static_cast<int64_t>(getSampleCount())
    * 1000000000 / static_cast<int64_t>(getSampleRate()));
}



void AudioSource::setSamplePos(uint pos)
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



uint AudioSource::getSamplePos() const
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



void AudioSource::setLooping(bool looping)
{
  al::setSourceLooping(mHandle, static_cast<ALboolean>(looping));
}



bool AudioSource::isLooping() const
{
  return static_cast<bool>(al::getSourceLooping(mHandle));
}



void AudioSource::setPitch(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourcePitch(mHandle, static_cast<ALfloat>(value));
}



float AudioSource::getPitch() const
{
  return static_cast<float>(al::getSourcePitch(mHandle));
}



void AudioSource::setGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceGain(mHandle, static_cast<ALfloat>(value));
}



float AudioSource::getGain() const
{
  return static_cast<float>(al::getSourceGain(mHandle));
}



void AudioSource::setMaxGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceMaxGain(mHandle, static_cast<ALfloat>(value));
}



float AudioSource::getMaxGain() const
{
  return static_cast<float>(al::getSourceMaxGain(mHandle));
}



void AudioSource::setMinGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceMinGain(mHandle, static_cast<ALfloat>(value));
}



float AudioSource::getMinGain() const
{
  return static_cast<float>(al::getSourceMinGain(mHandle));
}



void AudioSource::setMaxDistance(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceMaxDistance(mHandle, static_cast<ALfloat>(value));
}



float AudioSource::getMaxDistance() const
{
  return static_cast<float>(al::getSourceMaxDistance(mHandle));
}



void AudioSource::setRolloffFactor(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceRolloffFactor(mHandle, static_cast<ALfloat>(value));
}



float AudioSource::getRolloffFactor() const
{
  return static_cast<float>(al::getSourceRolloffFactor(mHandle));
}



void AudioSource::setReferenceDistance(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceReferenceDistance(mHandle, static_cast<ALfloat>(value));
}



float AudioSource::getReferenceDistance() const
{
  return static_cast<float>(al::getSourceReferenceDistance(mHandle));
}



void AudioSource::setRelative(bool value)
{
  al::setSourceRelative(mHandle, static_cast<ALfloat>(value));
}



bool AudioSource::isRelative() const
{
  return static_cast<bool>(al::getSourceRelative(mHandle));
}



void AudioSource::setConeOuterGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceConeOuterGain(mHandle, static_cast<ALfloat>(value));
}



float AudioSource::getConeOuterGain() const
{
  return static_cast<float>(al::getSourceConeOuterGain(mHandle));
}



void AudioSource::setConeInnerAngle(float value)
{
  HOU_EXPECT(value >= 0.f && value <= 2.f * PI_F);
  al::setSourceConeInnerAngle(mHandle, static_cast<ALfloat>(radToDeg(value)));
}



float AudioSource::getConeInnerAngle() const
{
  return degToRad(static_cast<float>(al::getSourceConeInnerAngle(mHandle)));
}



void AudioSource::setConeOuterAngle(float value)
{
  HOU_EXPECT(value >= 0.f && value <= 2.f * PI_F);
  al::setSourceConeOuterAngle(mHandle, static_cast<ALfloat>(radToDeg(value)));
}



float AudioSource::getConeOuterAngle() const
{
  return degToRad(static_cast<float>(al::getSourceConeOuterAngle(mHandle)));
}



void AudioSource::setPosition(const Vec3f& pos)
{
  al::setSourcePosition(mHandle, static_cast<const ALfloat*>(pos.data()));
}



Vec3f AudioSource::getPosition() const
{
  Vec3f retval;
  al::getSourcePosition(
    mHandle, static_cast<ALfloat*>(const_cast<float*>(retval.data())));
  return retval;
}



void AudioSource::setVelocity(const Vec3f& vel)
{
  al::setSourceVelocity(mHandle, static_cast<const ALfloat*>(vel.data()));
}



Vec3f AudioSource::getVelocity() const
{
  Vec3f retval;
  al::getSourceVelocity(
    mHandle, static_cast<ALfloat*>(const_cast<float*>(retval.data())));
  return retval;
}



void AudioSource::setDirection(const Vec3f& dir)
{
  al::setSourceDirection(mHandle, static_cast<const ALfloat*>(dir.data()));
}



Vec3f AudioSource::getDirection() const
{
  Vec3f retval;
  al::getSourceDirection(
    mHandle, static_cast<ALfloat*>(const_cast<float*>(retval.data())));
  return retval;
}



void AudioSource::onSetSamplePos(uint pos)
{
  al::setSourceSampleOffset(mHandle, static_cast<ALint>(pos));
}



uint AudioSource::onGetSamplePos() const
{
  return static_cast<uint>(al::getSourceSampleOffset(mHandle));
}

}  // namespace hou
