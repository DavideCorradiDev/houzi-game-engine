// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/TestAudBaseTestSpecificContext.hpp"

#include "hou/aud/Listener.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/math_functions.hpp"
#include "hou/mth/rotation3.hpp"

using namespace hou;



namespace
{

class TestListener : public TestAudBaseTestSpecificContext
{};

class TestListenerDeathTest : public TestListener
{};

}  // namespace



TEST_F(TestListener, Gain)
{
  EXPECT_FLOAT_EQ(1.f, Listener::getGain());
  Listener::setGain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, Listener::getGain());
}



TEST_F(TestListenerDeathTest, InvalidGain)
{
  HOU_EXPECT_PRECONDITION(Listener::setGain(-1.f));
}



TEST_F(TestListener, Position)
{
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), Listener::get_position());
  Listener::set_position(vec3f(1.f, 2.f, 3.f));
  HOU_EXPECT_FLOAT_CLOSE(vec3f(1.f, 2.f, 3.f), Listener::get_position());
}



TEST_F(TestListener, Velocity)
{
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), Listener::getVelocity());
  Listener::setVelocity(vec3f(1.f, 2.f, 3.f));
  HOU_EXPECT_FLOAT_CLOSE(vec3f(1.f, 2.f, 3.f), Listener::getVelocity());
}



TEST_F(TestListener, Orientation)
{
  HOU_EXPECT_FLOAT_CLOSE(Rot3f::identity(), Listener::getOrientation());

  Rot3f orRef
    = Rot3f::x(pi_f / 3.f) * Rot3f::z(pi_f / 4.f) * Rot3f::y(pi_f / 2.f);
  Listener::setOrientation(orRef);
  HOU_EXPECT_FLOAT_CLOSE(orRef, Listener::getOrientation());
}
