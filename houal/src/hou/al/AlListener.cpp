// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/AlListener.hpp"

#include "hou/al/AlCheck.hpp"



namespace hou
{

namespace al
{

void setListenerGain(ALfloat value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alListenerf(AL_GAIN, value);
  HOU_AL_CHECK_ERROR();
}



ALfloat getListenerGain()
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  ALfloat value;
  alGetListenerf(AL_GAIN, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setListenerPosition(const ALfloat* value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alListenerfv(AL_POSITION, const_cast<ALfloat*>(value));
  HOU_AL_CHECK_ERROR();
}



void getListenerPosition(ALfloat* value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alGetListenerfv(AL_POSITION, value);
  HOU_AL_CHECK_ERROR();
}



void setListenerVelocity(const ALfloat* value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alListenerfv(AL_VELOCITY, const_cast<ALfloat*>(value));
  HOU_AL_CHECK_ERROR();
}



void getListenerVelocity(ALfloat* value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alGetListenerfv(AL_VELOCITY, value);
  HOU_AL_CHECK_ERROR();
}



void setListenerOrientation(const ALfloat* value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alListenerfv(AL_ORIENTATION, const_cast<ALfloat*>(value));
  HOU_AL_CHECK_ERROR();
}



void getListenerOrientation(ALfloat* value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alGetListenerfv(AL_ORIENTATION, value);
  HOU_AL_CHECK_ERROR();
}



}

}

