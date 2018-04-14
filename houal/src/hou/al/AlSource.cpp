// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/AlSource.hpp"

#include "hou/al/AlBuffer.hpp"

#include "hou/cor/Error.hpp"

#include <iostream>



namespace hou
{

namespace al
{

Source::Source()
  : NonCopyable()
  , mHandle(al::SourceHandle::generate())
{}



Source::Source(Source&& other)
  : mHandle(std::move(other.mHandle))
{}



const SourceHandle& Source::getHandle() const
{
  return mHandle;
}



void Source::setPitch(ALfloat value)
{
  setSourcePitch(mHandle, value);
}



ALfloat Source::getPitch() const
{
  return getSourcePitch(mHandle);
}



void Source::setGain(ALfloat value)
{
  setSourceGain(mHandle, value);
}



ALfloat Source::getGain() const
{
  return getSourceGain(mHandle);
}



void Source::setMaxGain(ALfloat value)
{
  setSourceMaxGain(mHandle, value);
}



ALfloat Source::getMaxGain() const
{
  return getSourceMaxGain(mHandle);
}



void Source::setMinGain(ALfloat value)
{
  setSourceMinGain(mHandle, value);
}



ALfloat Source::getMinGain() const
{
  return getSourceMinGain(mHandle);
}



void Source::setMaxDistance(ALfloat value)
{
  setSourceMaxDistance(mHandle, value);
}



ALfloat Source::getMaxDistance() const
{
  return getSourceMaxDistance(mHandle);
}



void Source::setRolloffFactor(ALfloat value)
{
  setSourceRolloffFactor(mHandle, value);
}



ALfloat Source::getRolloffFactor() const
{
  return getSourceRolloffFactor(mHandle);
}



void Source::setConeOuterGain(ALfloat value)
{
  setSourceConeOuterGain(mHandle, value);
}



ALfloat Source::getConeOuterGain() const
{
  return getSourceConeOuterGain(mHandle);
}



void Source::setConeInnerAngle(ALfloat value)
{
  setSourceConeInnerAngle(mHandle, value);
}



ALfloat Source::getConeInnerAngle() const
{
  return getSourceConeInnerAngle(mHandle);
}



void Source::setConeOuterAngle(ALfloat value)
{
  setSourceConeOuterAngle(mHandle, value);
}



ALfloat Source::getConeOuterAngle() const
{
  return getSourceConeOuterAngle(mHandle);
}



void Source::setReferenceDistance(ALfloat value)
{
  setSourceReferenceDistance(mHandle, value);
}



ALfloat Source::getReferenceDistance() const
{
  return getSourceReferenceDistance(mHandle);
}



void Source::setRelative(ALboolean value)
{
  setSourceRelative(mHandle, value);
}



ALboolean Source::isRelative() const
{
  return getSourceRelative(mHandle);
}



void Source::setLooping(ALboolean value)
{
  setSourceLooping(mHandle, value);
}



ALboolean Source::isLooping() const
{
  return getSourceLooping(mHandle);
}



void Source::setState(SourceState state)
{
  setSourceState(mHandle, state);
}



void Source::play()
{
  playSource(mHandle);
}



void Source::pause()
{
  pauseSource(mHandle);
}



void Source::stop()
{
  stopSource(mHandle);
}



void Source::rewind()
{
  rewindSource(mHandle);
}



void Source::setPosition(const std::array<ALfloat, 3u>& pos)
{
  setSourcePosition(mHandle, pos.data());
}



std::array<ALfloat, 3u> Source::getPosition() const
{
  std::array<ALfloat, 3u> pos;
  getSourcePosition(mHandle, pos.data());
  return pos;
}



void Source::setVelocity(const std::array<ALfloat, 3u>& vel)
{
  setSourceVelocity(mHandle, vel.data());
}



std::array<ALfloat, 3u> Source::getVelocity() const
{
  std::array<ALfloat, 3u> vel;
  getSourceVelocity(mHandle, vel.data());
  return vel;
}



void Source::setDirection(const std::array<ALfloat, 3u>& dir)
{
  setSourceDirection(mHandle, dir.data());
}



std::array<ALfloat, 3u> Source::getDirection() const
{
  std::array<ALfloat, 3u> dir;
  getSourceDirection(mHandle, dir.data());
  return dir;
}



SourceState Source::getState() const
{
  return getSourceState(mHandle);
}



void Source::setBuffer(const Buffer& buffer)
{
  setSourceBuffer(mHandle, buffer.getHandle().getName());
}



void Source::resetBuffer()
{
  setSourceBuffer(mHandle, 0u);
}



void Source::queueBuffer(const Buffer& buffer)
{
  ALuint bufferName = buffer.getHandle().getName();
  sourceQueueBuffers(mHandle, 1u, &bufferName);
}



void Source::unqueueBuffer()
{
  ALuint bufferName;
  sourceUnqueueBuffers(mHandle, 1u, &bufferName);
}



void Source::unqueueBuffers(size_t number)
{
  std::vector<ALuint> bufferNames(number, 0);
  sourceUnqueueBuffers(mHandle, number, bufferNames.data());
}



uint Source::getQueuedBuffers() const
{
  return getSourceQueuedBuffers(mHandle);
}



uint Source::getProcessedBuffers() const
{
  return getSourceProcessedBuffers(mHandle);
}



void Source::setSecOffset(ALfloat offset)
{
  setSourceSecOffset(mHandle, offset);
}



ALfloat Source::getSecOffset() const
{
  return getSourceSecOffset(mHandle);
}



void Source::setSampleOffset(ALint offset)
{
  setSourceSampleOffset(mHandle, offset);
}



ALint Source::getSampleOffset() const
{
  return getSourceSampleOffset(mHandle);
}



void Source::setByteOffset(ALint offset)
{
  setSourceByteOffset(mHandle, offset);
}



ALint Source::getByteOffset() const
{
  return getSourceByteOffset(mHandle);
}

}

}

