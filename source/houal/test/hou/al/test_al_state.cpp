// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/al/test_al_base.hpp"

#include "hou/al/al_state.hpp"

using namespace hou;



namespace
{

class TestAlState : public test_al_base {};

}



TEST_F(TestAlState, SetDistanceModel)
{
  EXPECT_EQ(AL_INVERSE_DISTANCE_CLAMPED, al::get_distance_model());
  al::set_distance_model(AL_INVERSE_DISTANCE);
  EXPECT_EQ(AL_INVERSE_DISTANCE, al::get_distance_model());
}



TEST_F(TestAlState, SetDopplerFactor)
{
  EXPECT_FLOAT_EQ(1.f, al::get_doppler_factor());
  al::set_doppler_factor(0.5f);
  EXPECT_FLOAT_EQ(0.5f, al::get_doppler_factor());
}



TEST_F(TestAlState, SetSpeedOfSound)
{
  EXPECT_FLOAT_EQ(343.3f, al::get_speed_of_sound());
  al::set_speed_of_sound(0.5f);
  EXPECT_FLOAT_EQ(0.5f, al::get_speed_of_sound());
}

