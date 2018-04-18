// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/Listener.hpp"

#include "hou/al/AlListener.hpp"

#include "hou/mth/Matrix.hpp"
#include "hou/mth/Rotation3.hpp"



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



Vec3f getPosition()
{
  ALfloat pos[3];
  al::getListenerPosition(pos);
  return Vec3f(pos[0], pos[1], pos[2]);
}



void setPosition(const Vec3f& pos)
{
  al::setListenerPosition(reinterpret_cast<const ALfloat*>(pos.data()));
}



Vec3f getVelocity()
{
  ALfloat vel[3];
  al::getListenerVelocity(vel);
  return Vec3f(vel[0], vel[1], vel[2]);
}



void setVelocity(const Vec3f& vel)
{
  al::setListenerVelocity(reinterpret_cast<const ALfloat*>(vel.data()));
}



Rot3f getOrientation()
{
  ALfloat ori[6];
  al::getListenerOrientation(ori);

  Vec3f z(-ori[0], -ori[1], -ori[2]);
  Vec3f y(ori[3], ori[4], ori[5]);
  Vec3f x = cross(y, z);

  Mat3x3f rotMat = Mat3x3f::zero();
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
  Mat3x3f rotMat = ori.getMatrix();
  ALfloat value[6] = {-rotMat(0, 2), -rotMat(1, 2), -rotMat(2, 2), rotMat(0, 1),
    rotMat(1, 1), rotMat(2, 1)};
  al::setListenerOrientation(reinterpret_cast<const ALfloat*>(value));
}

}  // namespace Listener

}  // namespace hou
