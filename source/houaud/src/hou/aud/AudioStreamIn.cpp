// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudioStreamIn.hpp"

#include "hou/aud/AudError.hpp"
#include "hou/aud/OggFileIn.hpp"
#include "hou/aud/WavFileIn.hpp"

#include "hou/cor/cor_error.hpp"
#include "hou/cor/error.hpp"



namespace hou
{

AudioStreamIn::~AudioStreamIn()
{}




size_t AudioStreamIn::getReadSampleCount() const
{
  return getReadByteCount() / (getChannelCount() * getBytesPerSample());
}

}

