// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/listener.hpp"

#include "hou/al/al_listener.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/rotation3.hpp"



namespace hou
{

namespace listener
{

float get_gain()
{
  return static_cast<float>(al::get_listener_gain());
}



void set_gain(float gain)
{
  DEPRECATED_HOU_EXPECT(gain >= 0.f);
  al::set_listener_gain(static_cast<ALfloat>(gain));
}



vec3f get_position()
{
  ALfloat pos[3];
  al::get_listener_position(pos);
  return vec3f(pos[0], pos[1], pos[2]);
}



void set_position(const vec3f& pos)
{
  al::set_listener_position(reinterpret_cast<const ALfloat*>(pos.data()));
}



vec3f get_velocity()
{
  ALfloat vel[3];
  al::get_listener_velocity(vel);
  return vec3f(vel[0], vel[1], vel[2]);
}



void set_velocity(const vec3f& vel)
{
  al::set_listener_velocity(reinterpret_cast<const ALfloat*>(vel.data()));
}



rot3f get_orientation()
{
  ALfloat ori[6];
  al::get_listener_orientation(ori);

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

  return rot3f(rotMat);
}



void set_orientation(const rot3f& ori)
{
  mat3x3f rotMat = ori.get_matrix();
  ALfloat value[6] = {-rotMat(0, 2), -rotMat(1, 2), -rotMat(2, 2), rotMat(0, 1),
    rotMat(1, 1), rotMat(2, 1)};
  al::set_listener_orientation(reinterpret_cast<const ALfloat*>(value));
}

}  // namespace listener

}  // namespace hou
