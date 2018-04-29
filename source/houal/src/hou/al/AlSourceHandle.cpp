// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/AlSourceHandle.hpp"

#include "hou/al/AlBufferHandle.hpp"
#include "hou/al/AlCheck.hpp"



namespace hou
{

namespace al
{

SourceHandle SourceHandle::generate()
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  ALuint name;
  alGenSources(1u, &name);
  HOU_AL_CHECK_ERROR();
  return SourceHandle(name);
}



SourceHandle::SourceHandle(SourceHandle&& other)
  : ContextOwnedObjectHandle(std::move(other))
{}



SourceHandle::~SourceHandle()
{
  if(get_name() != 0)
  {
    HOU_AL_CHECK_CONTEXT_EXISTENCE();
    HOU_AL_CHECK_CONTEXT_OWNERSHIP(*this);
    ALuint name = get_name();
    alDeleteSources(1u, &name);
    HOU_AL_CHECK_ERROR();
  }
}



SourceHandle::SourceHandle(ALuint name)
  : ContextOwnedObjectHandle(name)
{}



void setSourcePitch(const SourceHandle& s, ALfloat pitch)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_PITCH, pitch);
  HOU_AL_CHECK_ERROR();
}




ALfloat getSourcePitch(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_PITCH, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSourceGain(const SourceHandle& s, ALfloat gain)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_GAIN, gain);
  HOU_AL_CHECK_ERROR();
}




ALfloat getSourceGain(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_GAIN, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSourceMaxGain(const SourceHandle& s, ALfloat maxGain)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_MAX_GAIN, maxGain);
  HOU_AL_CHECK_ERROR();
}




ALfloat getSourceMaxGain(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_MAX_GAIN, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSourceMinGain(const SourceHandle& s, ALfloat minGain)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_MIN_GAIN, minGain);
  HOU_AL_CHECK_ERROR();
}




ALfloat getSourceMinGain(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_MIN_GAIN, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSourceMaxDistance(const SourceHandle& s, ALfloat distance)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_MAX_DISTANCE, distance);
  HOU_AL_CHECK_ERROR();
}




ALfloat getSourceMaxDistance(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_MAX_DISTANCE, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSourceRolloffFactor(const SourceHandle& s, ALfloat factor)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_ROLLOFF_FACTOR, factor);
  HOU_AL_CHECK_ERROR();
}




ALfloat getSourceRolloffFactor(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_ROLLOFF_FACTOR, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSourceConeOuterGain(const SourceHandle& s, ALfloat gain)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_CONE_OUTER_GAIN, gain);
  HOU_AL_CHECK_ERROR();
}




ALfloat getSourceConeOuterGain(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_CONE_OUTER_GAIN, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSourceConeInnerAngle(const SourceHandle& s, ALfloat angle)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_CONE_INNER_ANGLE, angle);
  HOU_AL_CHECK_ERROR();
}




ALfloat getSourceConeInnerAngle(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_CONE_INNER_ANGLE, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSourceConeOuterAngle(const SourceHandle& s, ALfloat angle)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_CONE_OUTER_ANGLE, angle);
  HOU_AL_CHECK_ERROR();
}




ALfloat getSourceConeOuterAngle(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_CONE_OUTER_ANGLE, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSourceReferenceDistance(const SourceHandle& s, ALfloat dist)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_REFERENCE_DISTANCE, dist);
  HOU_AL_CHECK_ERROR();
}




ALfloat getSourceReferenceDistance(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_REFERENCE_DISTANCE, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSourcePosition(const SourceHandle& s, const ALfloat* pos)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcefv(s.get_name(), AL_POSITION, const_cast<ALfloat*>(pos));
  HOU_AL_CHECK_ERROR();
}




void getSourcePosition(const SourceHandle& s, ALfloat* pos)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alGetSourcefv(s.get_name(), AL_POSITION, pos);
  HOU_AL_CHECK_ERROR();
}



void setSourceVelocity(const SourceHandle& s, const ALfloat* vel)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcefv(s.get_name(), AL_VELOCITY, const_cast<ALfloat*>(vel));
  HOU_AL_CHECK_ERROR();
}




void getSourceVelocity(const SourceHandle& s, ALfloat* vel)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alGetSourcefv(s.get_name(), AL_VELOCITY, vel);
  HOU_AL_CHECK_ERROR();
}



void setSourceDirection(const SourceHandle& s, const ALfloat* dir)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcefv(s.get_name(), AL_DIRECTION, const_cast<ALfloat*>(dir));
  HOU_AL_CHECK_ERROR();
}



void getSourceDirection(const SourceHandle& s, ALfloat* dir)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alGetSourcefv(s.get_name(), AL_DIRECTION, dir);
  HOU_AL_CHECK_ERROR();
}




void setSourceRelative(const SourceHandle& s, ALboolean relative)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcei(s.get_name(), AL_SOURCE_RELATIVE, static_cast<ALint>(relative));
  HOU_AL_CHECK_ERROR();
}




ALboolean getSourceRelative(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_SOURCE_RELATIVE, &value);
  HOU_AL_CHECK_ERROR();
  return static_cast<ALboolean>(value);
}



void setSourceLooping(const SourceHandle& s, ALboolean looping)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcei(s.get_name(), AL_LOOPING, static_cast<ALint>(looping));
  HOU_AL_CHECK_ERROR();
}



ALboolean getSourceLooping(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_LOOPING, &value);
  HOU_AL_CHECK_ERROR();
  return static_cast<ALboolean>(value);
}



void setSourceState(const SourceHandle& s, ALenum state)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcei(s.get_name(), AL_SOURCE_STATE, state);
  HOU_AL_CHECK_ERROR();
}



ALenum getSourceState(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_SOURCE_STATE, &value);
  HOU_AL_CHECK_ERROR();
  return static_cast<ALenum>(value);
}



void playSource(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcePlay(s.get_name());
  HOU_AL_CHECK_ERROR();
}



void pauseSource(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcePause(s.get_name());
  HOU_AL_CHECK_ERROR();
}



void stopSource(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourceStop(s.get_name());
  HOU_AL_CHECK_ERROR();
}



void rewindSource(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourceRewind(s.get_name());
  HOU_AL_CHECK_ERROR();
}




void setSourceBuffer(const SourceHandle& s, ALuint buffer)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcei(s.get_name(), AL_BUFFER, static_cast<ALint>(buffer));
  HOU_AL_CHECK_ERROR();
}



ALuint getSourceBuffer(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_BUFFER, &value);
  HOU_AL_CHECK_ERROR();
  return static_cast<ALuint>(value);
}



void sourceQueueBuffers(const SourceHandle& s, ALsizei n, ALuint* buffers)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourceQueueBuffers(s.get_name(), n, buffers);
  HOU_AL_CHECK_ERROR();
}



void sourceUnqueueBuffers(const SourceHandle& s, ALsizei n, ALuint* buffers)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourceUnqueueBuffers(s.get_name(), n, buffers);
  HOU_AL_CHECK_ERROR();
}



ALint getSourceQueuedBuffers(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_BUFFERS_QUEUED, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



ALint getSourceProcessedBuffers(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_BUFFERS_PROCESSED, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSourceSecOffset(const SourceHandle& s, ALfloat offset)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_SEC_OFFSET, offset);
  HOU_AL_CHECK_ERROR();
}



ALfloat getSourceSecOffset(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_SEC_OFFSET, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



ALint getSourceSampleOffset(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_SAMPLE_OFFSET, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSourceSampleOffset(const SourceHandle& s, ALint offset)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcei(s.get_name(), AL_SAMPLE_OFFSET, offset);
  HOU_AL_CHECK_ERROR();
}



ALint getSourceByteOffset(const SourceHandle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_BYTE_OFFSET, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSourceByteOffset(const SourceHandle& s, ALint offset)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcei(s.get_name(), AL_BYTE_OFFSET, offset);
  HOU_AL_CHECK_ERROR();
}

}

}

