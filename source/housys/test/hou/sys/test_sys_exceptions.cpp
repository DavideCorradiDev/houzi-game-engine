// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/test_sys_base.hpp"

#include "hou/sys/sys_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_sys_exceptions : public test_sys_base
{};

}  // namespace



TEST_F(test_sys_exceptions, file_open_error)
{
  file_open_error ex("source.cpp", 33u, "path/to/the_file_name.txt");
  EXPECT_STREQ(
    "source.cpp:33 - Failed to open file 'path/to/the_file_name.txt'.",
    ex.what());
}



TEST_F(test_sys_exceptions, file_close_error)
{
  file_close_error ex("source.cpp", 33u);
  EXPECT_STREQ("source.cpp:33 - Failed to close the file.", ex.what());
}



TEST_F(test_sys_exceptions, read_error)
{
  read_error ex("source.cpp", 33u);
  EXPECT_STREQ("source.cpp:33 - Failed to read data.", ex.what());
}



TEST_F(test_sys_exceptions, write_error)
{
  write_error ex("source.cpp", 33u);
  EXPECT_STREQ("source.cpp:33 - Failed to write data.", ex.what());
}



TEST_F(test_sys_exceptions, cursor_error)
{
  cursor_error ex("source.cpp", 33u);
  EXPECT_STREQ("source.cpp:33 - Failed to set or get the file cursor position.",
    ex.what());
}



TEST_F(test_sys_exceptions, invalid_image_data)
{
  invalid_image_data ex("source.cpp", 33u);
  EXPECT_STREQ("source.cpp:33 - Invalid or corrupted image data.", ex.what());
}



TEST_F(test_sys_exceptions, platform_error)
{
  platform_error ex("plat.cpp", 24u, "Something wrong.");
  EXPECT_STREQ(
    "plat.cpp:24 - A platform-specific error occurred:\nSomething wrong.",
    ex.what());
}



TEST_F(test_sys_exceptions, invalid_monitor_id)
{
  invalid_monitor_id ex("mon.cpp", 333u, 8u);
  EXPECT_STREQ("mon.cpp:333 - Invalid monitor id: 8.", ex.what());
}
