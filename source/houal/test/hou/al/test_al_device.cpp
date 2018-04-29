// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/al/al_device.hpp"
#include "hou/al/al_error.hpp"

using namespace hou;



TEST(TestAlDevice, DefaultDeviceCreation)
{
  al::device d;
  EXPECT_NE(nullptr, d.get_handle());
  EXPECT_NE(0u, d.get_uid());
}



TEST(TestAlDevice, Creation)
{
  std::vector<std::string> deviceNames = al::device::get_device_names();
  for(const auto& deviceName : deviceNames)
  {
    al::device d(deviceName);
    EXPECT_NE(nullptr, d.get_handle());
    EXPECT_NE(0u, d.get_uid());
  }
}



TEST(TestAlDeviceDeathTest, CreationFailure)
{
  std::string invalidDeviceName = u8"Invalid ph_device name";
  HOU_EXPECT_ERROR(al::device d(invalidDeviceName), std::runtime_error
    , format_string(get_text(al_error::device_open), invalidDeviceName.c_str()));
}



TEST(TestAlDevice, MoveConstructor)
{
  al::device dDummy;
  ALCdevice* handleRef = dDummy.get_handle();
  uint32_t uidRef = dDummy.get_uid();
  al::device d(std::move(dDummy));

  EXPECT_EQ(handleRef, d.get_handle());
  EXPECT_EQ(uidRef, d.get_uid());
  EXPECT_EQ(nullptr, dDummy.get_handle());
}

