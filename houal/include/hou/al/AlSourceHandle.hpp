// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_SOURCE_HANDLE_HPP
#define HOU_AL_AL_SOURCE_HANDLE_HPP

#include "hou/al/AlExport.hpp"
#include "hou/al/AlObjectHandle.hpp"



namespace hou
{

namespace al
{

class BufferHandle;



class HOU_AL_API SourceHandle
  : public ContextOwnedObjectHandle
{
public:
  static SourceHandle generate();

  SourceHandle(SourceHandle&& other);
  virtual ~SourceHandle();

private:
  SourceHandle(ALuint name);
};



HOU_AL_API void setSourcePitch(const SourceHandle& s, ALfloat pitch);
HOU_AL_API ALfloat getSourcePitch(const SourceHandle& s);
HOU_AL_API void setSourceGain(const SourceHandle& s, ALfloat gain);
HOU_AL_API ALfloat getSourceGain(const SourceHandle& s);
HOU_AL_API void setSourceMaxGain(const SourceHandle& s, ALfloat maxGain);
HOU_AL_API ALfloat getSourceMaxGain(const SourceHandle& s);
HOU_AL_API void setSourceMinGain(const SourceHandle& s, ALfloat minGain);
HOU_AL_API ALfloat getSourceMinGain(const SourceHandle& s);
HOU_AL_API void setSourceMaxDistance(const SourceHandle& s, ALfloat distance);
HOU_AL_API ALfloat getSourceMaxDistance(const SourceHandle& s);
HOU_AL_API void setSourceRolloffFactor(const SourceHandle& s, ALfloat factor);
HOU_AL_API ALfloat getSourceRolloffFactor(const SourceHandle& s);
HOU_AL_API void setSourceConeOuterGain(const SourceHandle& s, ALfloat gain);
HOU_AL_API ALfloat getSourceConeOuterGain(const SourceHandle& s);
HOU_AL_API void setSourceConeInnerAngle(const SourceHandle& s, ALfloat angle);
HOU_AL_API ALfloat getSourceConeInnerAngle(const SourceHandle& s);
HOU_AL_API void setSourceConeOuterAngle(const SourceHandle& s, ALfloat angle);
HOU_AL_API ALfloat getSourceConeOuterAngle(const SourceHandle& s);
HOU_AL_API void setSourceReferenceDistance(const SourceHandle& s, ALfloat dist);
HOU_AL_API ALfloat getSourceReferenceDistance(const SourceHandle& s);
HOU_AL_API void setSourcePosition(const SourceHandle& s, const ALfloat* pos);
HOU_AL_API void getSourcePosition(const SourceHandle& s, ALfloat* pos);
HOU_AL_API void setSourceVelocity(const SourceHandle& s, const ALfloat* vel);
HOU_AL_API void getSourceVelocity(const SourceHandle& s, ALfloat* vel);
HOU_AL_API void setSourceDirection(const SourceHandle& s, const ALfloat* dir);
HOU_AL_API void getSourceDirection(const SourceHandle& s, ALfloat* dir);
HOU_AL_API void setSourceRelative(const SourceHandle& s, ALboolean relative);
HOU_AL_API ALboolean getSourceRelative(const SourceHandle& s);
HOU_AL_API void setSourceLooping(const SourceHandle& s, ALboolean looping);
HOU_AL_API ALboolean getSourceLooping(const SourceHandle& s);

HOU_AL_API void setSourceState(const SourceHandle& s, ALenum state);
HOU_AL_API ALenum getSourceState(const SourceHandle& s);
HOU_AL_API void playSource(const SourceHandle& s);
HOU_AL_API void pauseSource(const SourceHandle& s);
HOU_AL_API void stopSource(const SourceHandle& s);
HOU_AL_API void rewindSource(const SourceHandle& s);

HOU_AL_API void setSourceBuffer(const SourceHandle& s, ALuint buffer);
HOU_AL_API ALuint getSourceBuffer(const SourceHandle& s);
HOU_AL_API void sourceQueueBuffers(const SourceHandle& s, ALsizei n
  , ALuint* buffers);
HOU_AL_API void sourceUnqueueBuffers(const SourceHandle& s, ALsizei n
  , ALuint* buffers);
HOU_AL_API ALint getSourceQueuedBuffers(const SourceHandle& s);
HOU_AL_API ALint getSourceProcessedBuffers(const SourceHandle& s);

HOU_AL_API void setSourceSecOffset(const SourceHandle& s, ALfloat offset);
HOU_AL_API ALfloat getSourceSecOffset(const SourceHandle& s);
HOU_AL_API void setSourceSampleOffset(const SourceHandle& s, ALint offset);
HOU_AL_API ALint getSourceSampleOffset(const SourceHandle& s);
HOU_AL_API void setSourceByteOffset(const SourceHandle& s, ALint offset);
HOU_AL_API ALint getSourceByteOffset(const SourceHandle& s);

}

}

#endif

