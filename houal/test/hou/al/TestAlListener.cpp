// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/al/TestAlBase.hpp"

#include "hou/al/AlListener.hpp"

#include "hou/cor/StdArray.hpp"

using namespace hou;



namespace
{

class TestAlListener : public TestAlBase {};

}



TEST_F(TestAlListener, SetGain)
{
  EXPECT_FLOAT_EQ(1.f, al::getListenerGain());
  al::setListenerGain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, al::getListenerGain());
}



TEST_F(TestAlListener, SetPosition)
{
  std::array<ALfloat, 3u> pos{9.f, 11.f, -7.f};
  std::array<ALfloat, 3u> posZero{0.f, 0.f, 0.f};
  std::array<ALfloat, 3u> posRef{2.f, 5.f, -3.f};

  al::getListenerPosition(pos.data());
  HOU_EXPECT_FLOAT_CLOSE(posZero, pos);

  al::setListenerPosition(posRef.data());
  al::getListenerPosition(pos.data());
  HOU_EXPECT_FLOAT_CLOSE(posRef, pos);
}



TEST_F(TestAlListener, SetVelocity)
{
  std::array<ALfloat, 3u> vel{9.f, 11.f, -7.f};
  std::array<ALfloat, 3u> velZero{0.f, 0.f, 0.f};
  std::array<ALfloat, 3u> velRef{2.f, 5.f, -3.f};

  al::getListenerVelocity(vel.data());
  HOU_EXPECT_FLOAT_CLOSE(velZero, vel);

  al::setListenerVelocity(velRef.data());
  al::getListenerVelocity(vel.data());
  HOU_EXPECT_FLOAT_CLOSE(velRef, vel);
}



TEST_F(TestAlListener, SetOrientation)
{
  std::array<ALfloat, 6u> ori{9.f, 11.f, -7.f, 1.f, -4.f, 12.f};
  std::array<ALfloat, 6u> oriZero{0.f, 0.f, -1.f, 0.f, 1.f, 0.f};
  std::array<ALfloat, 6u> oriRef{2.f, 5.f, -3.f, -4.f, 7.f, 0.f};

  al::getListenerOrientation(ori.data());
  HOU_EXPECT_FLOAT_CLOSE(oriZero, ori);

  al::setListenerOrientation(oriRef.data());
  al::getListenerOrientation(ori.data());
  HOU_EXPECT_FLOAT_CLOSE(oriRef, ori);
}

