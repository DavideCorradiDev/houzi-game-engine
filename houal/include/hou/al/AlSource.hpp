// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_AL_AL_SOURCE_HPP
#define HOU_AL_AL_SOURCE_HPP

#include "hou/al/AlExport.hpp"
#include "hou/cor/NonCopyable.hpp"

#include "hou/al/AlSourceHandle.hpp"

#include <array>



namespace hou
{

namespace al
{

class Buffer;



class HOU_AL_API Source
  : public NonCopyable
{
public:
  Source();
  Source(Source&& other);

  const SourceHandle& getHandle() const;

  void setPitch(ALfloat value);
  ALfloat getPitch() const;

  void setGain(ALfloat value);
  ALfloat getGain() const;

  void setMaxGain(ALfloat value);
  ALfloat getMaxGain() const;

  void setMinGain(ALfloat value);
  ALfloat getMinGain() const;

  void setMaxDistance(ALfloat value);
  ALfloat getMaxDistance() const;

  void setRolloffFactor(ALfloat value);
  ALfloat getRolloffFactor() const;

  void setConeOuterGain(ALfloat value);
  ALfloat getConeOuterGain() const;

  void setConeInnerAngle(ALfloat value);
  ALfloat getConeInnerAngle() const;

  void setConeOuterAngle(ALfloat value);
  ALfloat getConeOuterAngle() const;

  void setReferenceDistance(ALfloat value);
  ALfloat getReferenceDistance() const;

  void setRelative(ALboolean value);
  ALboolean isRelative() const;

  void setLooping(ALboolean value);
  ALboolean isLooping() const;

  void setPosition(const std::array<ALfloat, 3u>& pos);
  std::array<ALfloat, 3u> getPosition() const;

  void setVelocity(const std::array<ALfloat, 3u>& vel);
  std::array<ALfloat, 3u> getVelocity() const;

  void setDirection(const std::array<ALfloat, 3u>& dir);
  std::array<ALfloat, 3u> getDirection() const;

  void setState(SourceState state);
  void play();
  void pause();
  void stop();
  void rewind();
  SourceState getState() const;

  void setBuffer(const Buffer& buffer);
  void resetBuffer();

  void queueBuffer(const Buffer& buffer);
  void unqueueBuffer();
  void unqueueBuffers(size_t number);
  uint getQueuedBuffers() const;
  uint getProcessedBuffers() const;

  void setSecOffset(ALfloat offset);
  ALfloat getSecOffset() const;
  void setSampleOffset(ALint offset);
  ALint getSampleOffset() const;
  void setByteOffset(ALint offset);
  ALint getByteOffset() const;

private:
  SourceHandle mHandle;
};

}

}

#endif

