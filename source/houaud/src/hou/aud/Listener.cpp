// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/Listener.hpp"

#include "hou/al/AlListener.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/rotation3.hpp"



namespace hou
{

namespace Listener
{

float getGain()
{
  return static_cast<float>(al::getListenerGain());
}



void setGain(float gain)
{
  HOU_EXPECT(gain >= 0.f);
  al::setListenerGain(static_cast<ALfloat>(gain));
}



vec3f get_position()
{
  ALfloat pos[3];
  al::getListenerPosition(pos);
  return vec3f(pos[0], pos[1], pos[2]);
}



void set_position(const vec3f& pos)
{
  al::setListenerPosition(reinterpret_cast<const ALfloat*>(pos.data()));
}



vec3f getVelocity()
{
  ALfloat vel[3];
  al::getListenerVelocity(vel);
  return vec3f(vel[0], vel[1], vel[2]);
}



void setVelocity(const vec3f& vel)
{
  al::setListenerVelocity(reinterpret_cast<const ALfloat*>(vel.data()));
}



Rot3f getOrientation()
{
  ALfloat ori[6];
  al::getListenerOrientation(ori);

  vec3f z(-ori[0], -ori[1], -ori[2]);
  vec3f y(ori[3], ori[4], ori[5]);
  vec3f x = cross(y, z);

  mat3x3f rotMat = mat3x3f::zero();
  rotMat(0, 0) = x(0);
  rotMat(1, 0) = x(1);
  rotMat(2, 0) = x(2);
  rotMat(0, 1) = y(0);
  rotMat(1, 1) = y(1);
  rotMat(2, 1) = y(2);
  rotMat(0, 2) = z(0);
  rotMat(1, 2) = z(1);
  rotMat(2, 2) = z(2);

  return Rot3f(rotMat);
}



void setOrientation(const Rot3f& ori)
{
  mat3x3f rotMat = ori.get_matrix();
  ALfloat value[6] = {-rotMat(0, 2), -rotMat(1, 2), -rotMat(2, 2), rotMat(0, 1),
    rotMat(1, 1), rotMat(2, 1)};
  al::setListenerOrientation(reinterpret_cast<const ALfloat*>(value));
}

}  // namespace Listener

}  // namespace hou
