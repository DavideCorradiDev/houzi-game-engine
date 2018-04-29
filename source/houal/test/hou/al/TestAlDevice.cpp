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
  EXPECT_NE(nullptr, d.get_handle());
  EXPECT_NE(0u, d.get_uid());
}



TEST(TestAlDevice, Creation)
{
  std::vector<std::string> deviceNames = al::Device::getDeviceNames();
  for(const auto& deviceName : deviceNames)
  {
    al::Device d(deviceName);
    EXPECT_NE(nullptr, d.get_handle());
    EXPECT_NE(0u, d.get_uid());
  }
}



TEST(TestAlDeviceDeathTest, CreationFailure)
{
  std::string invalidDeviceName = u8"Invalid device name";
  HOU_EXPECT_ERROR(al::Device d(invalidDeviceName), std::runtime_error
    , format_string(get_text(AlError::DeviceOpen), invalidDeviceName.c_str()));
}



TEST(TestAlDevice, MoveConstructor)
{
  al::Device dDummy;
  ALCdevice* handleRef = dDummy.get_handle();
  uint32_t uidRef = dDummy.get_uid();
  al::Device d(std::move(dDummy));

  EXPECT_EQ(handleRef, d.get_handle());
  EXPECT_EQ(uidRef, d.get_uid());
  EXPECT_EQ(nullptr, dDummy.get_handle());
}

