// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudioSource.hpp"

#include "hou/cor/cor_error.hpp"
#include "hou/cor/error.hpp"

#include "hou/mth/math_functions.hpp"



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
  , m_handle(al::SourceHandle::generate())
  , mRequestedSamplePos(0u)
{}



AudioSource::AudioSource(AudioSource&& other)
  : m_handle(std::move(other.m_handle))
  , mRequestedSamplePos(std::move(other.mRequestedSamplePos))
{}



AudioSource::~AudioSource()
{}



const al::SourceHandle& AudioSource::get_handle() const
{
  return m_handle;
}



void AudioSource::play()
{
  if(getState() != AudioSourceState::Playing)
  {
    al::stopSource(m_handle);
    onSetSamplePos(mRequestedSamplePos);
    al::playSource(m_handle);
    // The requested pos has to be set to 0 in case playback ends on its own.
    mRequestedSamplePos = 0u;
  }
}



void AudioSource::pause()
{
  if(getState() != AudioSourceState::Paused)
  {
    al::pauseSource(m_handle);
    // The requested pos is updated. Another call to play will resume from
    // the current pos.
    mRequestedSamplePos = onGetSamplePos();
  }
}



void AudioSource::stop()
{
  if(getState() != AudioSourceState::Stopped)
  {
    al::stopSource(m_handle);
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
  return alSourceStateToAudioSourceState(al::getSourceState(m_handle));
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
  return std::chrono::nanoseconds(static_cast<int64_t>(get_sample_count())
    * 1000000000 / static_cast<int64_t>(getSampleRate()));
}



void AudioSource::setSamplePos(uint pos)
{
  if(getState() == AudioSourceState::Playing)
  {
    onSetSamplePos(normalize(pos, get_sample_count()));
  }
  else
  {
    mRequestedSamplePos = normalize(pos, get_sample_count());
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
  al::setSourceLooping(m_handle, static_cast<ALboolean>(looping));
}



bool AudioSource::isLooping() const
{
  return static_cast<bool>(al::getSourceLooping(m_handle));
}



void AudioSource::setPitch(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourcePitch(m_handle, static_cast<ALfloat>(value));
}



float AudioSource::getPitch() const
{
  return static_cast<float>(al::getSourcePitch(m_handle));
}



void AudioSource::setGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceGain(m_handle, static_cast<ALfloat>(value));
}



float AudioSource::getGain() const
{
  return static_cast<float>(al::getSourceGain(m_handle));
}



void AudioSource::setMaxGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceMaxGain(m_handle, static_cast<ALfloat>(value));
}



float AudioSource::getMaxGain() const
{
  return static_cast<float>(al::getSourceMaxGain(m_handle));
}



void AudioSource::setMinGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceMinGain(m_handle, static_cast<ALfloat>(value));
}



float AudioSource::getMinGain() const
{
  return static_cast<float>(al::getSourceMinGain(m_handle));
}



void AudioSource::setMaxDistance(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceMaxDistance(m_handle, static_cast<ALfloat>(value));
}



float AudioSource::getMaxDistance() const
{
  return static_cast<float>(al::getSourceMaxDistance(m_handle));
}



void AudioSource::setRolloffFactor(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceRolloffFactor(m_handle, static_cast<ALfloat>(value));
}



float AudioSource::getRolloffFactor() const
{
  return static_cast<float>(al::getSourceRolloffFactor(m_handle));
}



void AudioSource::setReferenceDistance(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceReferenceDistance(m_handle, static_cast<ALfloat>(value));
}



float AudioSource::getReferenceDistance() const
{
  return static_cast<float>(al::getSourceReferenceDistance(m_handle));
}



void AudioSource::setRelative(bool value)
{
  al::setSourceRelative(m_handle, static_cast<ALfloat>(value));
}



bool AudioSource::isRelative() const
{
  return static_cast<bool>(al::getSourceRelative(m_handle));
}



void AudioSource::setConeOuterGain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::setSourceConeOuterGain(m_handle, static_cast<ALfloat>(value));
}



float AudioSource::getConeOuterGain() const
{
  return static_cast<float>(al::getSourceConeOuterGain(m_handle));
}



void AudioSource::setConeInnerAngle(float value)
{
  HOU_EXPECT(value >= 0.f && value <= 2.f * pi_f);
  al::setSourceConeInnerAngle(m_handle, static_cast<ALfloat>(rad_to_deg(value)));
}



float AudioSource::getConeInnerAngle() const
{
  return deg_to_rad(static_cast<float>(al::getSourceConeInnerAngle(m_handle)));
}



void AudioSource::setConeOuterAngle(float value)
{
  HOU_EXPECT(value >= 0.f && value <= 2.f * pi_f);
  al::setSourceConeOuterAngle(m_handle, static_cast<ALfloat>(rad_to_deg(value)));
}



float AudioSource::getConeOuterAngle() const
{
  return deg_to_rad(static_cast<float>(al::getSourceConeOuterAngle(m_handle)));
}



void AudioSource::set_position(const vec3f& pos)
{
  al::setSourcePosition(m_handle, static_cast<const ALfloat*>(pos.data()));
}



vec3f AudioSource::get_position() const
{
  vec3f retval;
  al::getSourcePosition(
    m_handle, static_cast<ALfloat*>(const_cast<float*>(retval.data())));
  return retval;
}



void AudioSource::setVelocity(const vec3f& vel)
{
  al::setSourceVelocity(m_handle, static_cast<const ALfloat*>(vel.data()));
}



vec3f AudioSource::getVelocity() const
{
  vec3f retval;
  al::getSourceVelocity(
    m_handle, static_cast<ALfloat*>(const_cast<float*>(retval.data())));
  return retval;
}



void AudioSource::setDirection(const vec3f& dir)
{
  al::setSourceDirection(m_handle, static_cast<const ALfloat*>(dir.data()));
}



vec3f AudioSource::getDirection() const
{
  vec3f retval;
  al::getSourceDirection(
    m_handle, static_cast<ALfloat*>(const_cast<float*>(retval.data())));
  return retval;
}



void AudioSource::onSetSamplePos(uint pos)
{
  al::setSourceSampleOffset(m_handle, static_cast<ALint>(pos));
}



uint AudioSource::onGetSamplePos() const
{
  return static_cast<uint>(al::getSourceSampleOffset(m_handle));
}

}  // namespace hou
