// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/al/AlDevice.hpp"
#include "hou/al/AlError.hpp"

using namespace hou;



TEST(TestAlDevice, DefaultDeviceCreation)
{
  al::Device d;
  EXPECT_NE(nullptr, d.getHandle());
  EXPECT_NE(0u, d.getUid());
}



TEST(TestAlDevice, Creation)
{
  std::vector<std::string> deviceNames = al::Device::getDeviceNames();
  for(const auto& deviceName : deviceNames)
  {
    al::Device d(deviceName);
    EXPECT_NE(nullptr, d.getHandle());
    EXPECT_NE(0u, d.getUid());
  }
}



TEST(TestAlDeviceDeathTest, CreationFailure)
{
  std::string invalidDeviceName = u8"Invalid device name";
  HOU_EXPECT_ERROR(al::Device d(invalidDeviceName), std::runtime_error
    , formatString(getText(AlError::DeviceOpen), invalidDeviceName.c_str()));
}



TEST(TestAlDevice, MoveConstructor)
{
  al::Device dDummy;
  ALCdevice* handleRef = dDummy.getHandle();
  uint32_t uidRef = dDummy.getUid();
  al::Device d(std::move(dDummy));

  EXPECT_EQ(handleRef, d.getHandle());
  EXPECT_EQ(uidRef, d.getUid());
  EXPECT_EQ(nullptr, dDummy.getHandle());
}

