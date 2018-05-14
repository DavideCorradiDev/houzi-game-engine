// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/al/al_device.hpp"
#include "hou/al/al_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_al_device : public Test
{};

class test_al_device_death_test : public test_al_device
{};
}  // namespace



TEST_F(test_al_device, default_device_creation)
{
  al::device d;
  EXPECT_NE(nullptr, d.get_handle());
  EXPECT_NE(0u, d.get_uid());
}



TEST_F(test_al_device, creation)
{
  std::vector<std::string> device_names = al::device::get_device_names();
  for(const auto& dev_name : device_names)
  {
    al::device d(dev_name);
    EXPECT_NE(nullptr, d.get_handle());
    EXPECT_NE(0u, d.get_uid());
  }
}



TEST_F(test_al_device_death_test, creation_failure)
{
  std::string invalid_device_name = u8"Invalid device name";
  EXPECT_ERROR_N(al::device d(invalid_device_name), al::device_open_error,
    invalid_device_name);
}



TEST_F(test_al_device, move_constructor)
{
  al::device d_dummy;
  ALCdevice* handle_ref = d_dummy.get_handle();
  uint32_t uid_ref = d_dummy.get_uid();
  al::device d(std::move(d_dummy));

  EXPECT_EQ(handle_ref, d.get_handle());
  EXPECT_EQ(uid_ref, d.get_uid());
  EXPECT_EQ(nullptr, d_dummy.get_handle());
}
