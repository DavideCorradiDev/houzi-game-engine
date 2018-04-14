// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/TestAudBase.hpp"

#include "hou/aud/Listener.hpp"

#include "hou/cor/CorError.hpp"

#include "hou/mth/Matrix.hpp"
#include "hou/mth/MthUtils.hpp"
#include "hou/mth/Rotation3.hpp"

using namespace hou;



namespace
{

class TestListener : public TestAudBase {};
class TestListenerDeathTest : public TestListener {};

}



TEST_F(TestListener, Gain)
{
  EXPECT_FLOAT_EQ(1.f, Listener::getGain());
  Listener::setGain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, Listener::getGain());
}



TEST_F(TestListener, InvalidGain)
{
  HOU_EXPECT_ERROR(Listener::setGain(-1.f), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestListener, Position)
{
  HOU_EXPECT_FLOAT_CLOSE(Vec3f::zero(), Listener::getPosition());
  Listener::setPosition(Vec3f(1.f, 2.f, 3.f));
  HOU_EXPECT_FLOAT_CLOSE(Vec3f(1.f, 2.f, 3.f), Listener::getPosition());
}



TEST_F(TestListener, Velocity)
{
  HOU_EXPECT_FLOAT_CLOSE(Vec3f::zero(), Listener::getVelocity());
  Listener::setVelocity(Vec3f(1.f, 2.f, 3.f));
  HOU_EXPECT_FLOAT_CLOSE(Vec3f(1.f, 2.f, 3.f), Listener::getVelocity());
}



TEST_F(TestListener, Orientation)
{
  HOU_EXPECT_FLOAT_CLOSE(Rot3f::identity(), Listener::getOrientation());

  Rot3f orRef = Rot3f::x(PI_F / 3.f) * Rot3f::z(PI_F / 4.f) * Rot3f::y(PI_F / 2.f);
  Listener::setOrientation(orRef);
  HOU_EXPECT_FLOAT_CLOSE(orRef, Listener::getOrientation());

  /// Vec3f at;
  /// Vec3f up;

  /// Vec3f atRef(0.f, 0.f, -1.f);
  /// Vec3f upRef(0.f, 1.f, 0.f);
  /// std::tie(at, up) = Listener::getOrientation();
  /// HOU_EXPECT_FLOAT_CLOSE(atRef, at);
  /// HOU_EXPECT_FLOAT_CLOSE(upRef, up);

  /// atRef = Vec3f(1.f, 2.f, 3.f);
  /// upRef = Vec3f(4.f, 5.f, 6.f);
  /// Listener::setOrientation(atRef, upRef);
  /// std::tie(at, up) = Listener::getOrientation();
  /// HOU_EXPECT_FLOAT_CLOSE(atRef, at);
  /// HOU_EXPECT_FLOAT_CLOSE(upRef, up);
}

