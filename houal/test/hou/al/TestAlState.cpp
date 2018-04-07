// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/al/TestAlBase.hpp"

#include "hou/al/AlState.hpp"

using namespace hou;



namespace
{

class TestAlState : public TestAlBase {};

}



TEST_F(TestAlState, SetDistanceModel)
{
  EXPECT_EQ(al::DistanceModel::InverseDistanceClamped, al::getDistanceModel());
  al::setDistanceModel(al::DistanceModel::InverseDistance);
  EXPECT_EQ(al::DistanceModel::InverseDistance, al::getDistanceModel());
}



TEST_F(TestAlState, SetDopplerFactor)
{
  EXPECT_FLOAT_EQ(1.f, al::getDopplerFactor());
  al::setDopplerFactor(0.5f);
  EXPECT_FLOAT_EQ(0.5f, al::getDopplerFactor());
}



TEST_F(TestAlState, SetSpeedOfSound)
{
  EXPECT_FLOAT_EQ(343.3f, al::getSpeedOfSound());
  al::setSpeedOfSound(0.5f);
  EXPECT_FLOAT_EQ(0.5f, al::getSpeedOfSound());
}

