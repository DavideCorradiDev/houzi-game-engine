// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/al/test_al_base.hpp"

#include "hou/al/al_listener.hpp"

#include "hou/cor/std_array.hpp"

using namespace hou;



namespace
{

class test_al_listener : public test_al_base
{};

}  // namespace



TEST_F(test_al_listener, set_gain)
{
  EXPECT_FLOAT_EQ(1.f, al::get_listener_gain());
  al::set_listener_gain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, al::get_listener_gain());
}



TEST_F(test_al_listener, set_position)
{
  std::array<ALfloat, 3u> pos{9.f, 11.f, -7.f};
  std::array<ALfloat, 3u> pos_zero{0.f, 0.f, 0.f};
  std::array<ALfloat, 3u> pos_ref{2.f, 5.f, -3.f};

  al::get_listener_position(pos.data());
  HOU_EXPECT_FLOAT_CLOSE(pos_zero, pos);

  al::set_listener_position(pos_ref.data());
  al::get_listener_position(pos.data());
  HOU_EXPECT_FLOAT_CLOSE(pos_ref, pos);
}



TEST_F(test_al_listener, set_velocity)
{
  std::array<ALfloat, 3u> vel{9.f, 11.f, -7.f};
  std::array<ALfloat, 3u> vel_zero{0.f, 0.f, 0.f};
  std::array<ALfloat, 3u> vel_ref{2.f, 5.f, -3.f};

  al::get_listener_velocity(vel.data());
  HOU_EXPECT_FLOAT_CLOSE(vel_zero, vel);

  al::set_listener_velocity(vel_ref.data());
  al::get_listener_velocity(vel.data());
  HOU_EXPECT_FLOAT_CLOSE(vel_ref, vel);
}



TEST_F(test_al_listener, set_orientation)
{
  std::array<ALfloat, 6u> ori{9.f, 11.f, -7.f, 1.f, -4.f, 12.f};
  std::array<ALfloat, 6u> ori_zero{0.f, 0.f, -1.f, 0.f, 1.f, 0.f};
  std::array<ALfloat, 6u> ori_ref{2.f, 5.f, -3.f, -4.f, 7.f, 0.f};

  al::get_listener_orientation(ori.data());
  HOU_EXPECT_FLOAT_CLOSE(ori_zero, ori);

  al::set_listener_orientation(ori_ref.data());
  al::get_listener_orientation(ori.data());
  HOU_EXPECT_FLOAT_CLOSE(ori_ref, ori);
}
