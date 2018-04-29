// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/al/TestAlBase.hpp"

#include "hou/al/al_listener.hpp"

#include "hou/cor/std_array.hpp"

using namespace hou;



namespace
{

class TestAlListener : public TestAlBase {};

}



TEST_F(TestAlListener, SetGain)
{
  EXPECT_FLOAT_EQ(1.f, al::get_listener_gain());
  al::set_listener_gain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, al::get_listener_gain());
}



TEST_F(TestAlListener, SetPosition)
{
  std::array<ALfloat, 3u> pos{9.f, 11.f, -7.f};
  std::array<ALfloat, 3u> posZero{0.f, 0.f, 0.f};
  std::array<ALfloat, 3u> posRef{2.f, 5.f, -3.f};

  al::get_listener_position(pos.data());
  HOU_EXPECT_FLOAT_CLOSE(posZero, pos);

  al::set_listener_position(posRef.data());
  al::get_listener_position(pos.data());
  HOU_EXPECT_FLOAT_CLOSE(posRef, pos);
}



TEST_F(TestAlListener, SetVelocity)
{
  std::array<ALfloat, 3u> vel{9.f, 11.f, -7.f};
  std::array<ALfloat, 3u> velZero{0.f, 0.f, 0.f};
  std::array<ALfloat, 3u> velRef{2.f, 5.f, -3.f};

  al::get_listener_velocity(vel.data());
  HOU_EXPECT_FLOAT_CLOSE(velZero, vel);

  al::set_listener_velocity(velRef.data());
  al::get_listener_velocity(vel.data());
  HOU_EXPECT_FLOAT_CLOSE(velRef, vel);
}



TEST_F(TestAlListener, SetOrientation)
{
  std::array<ALfloat, 6u> ori{9.f, 11.f, -7.f, 1.f, -4.f, 12.f};
  std::array<ALfloat, 6u> oriZero{0.f, 0.f, -1.f, 0.f, 1.f, 0.f};
  std::array<ALfloat, 6u> oriRef{2.f, 5.f, -3.f, -4.f, 7.f, 0.f};

  al::get_listener_orientation(ori.data());
  HOU_EXPECT_FLOAT_CLOSE(oriZero, ori);

  al::set_listener_orientation(oriRef.data());
  al::get_listener_orientation(ori.data());
  HOU_EXPECT_FLOAT_CLOSE(oriRef, ori);
}

