// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/sys_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_sys_exceptions : public Test
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



TEST_F(test_sys_exceptions, file_cursor_error)
{
  file_cursor_error ex("source.cpp", 33u);
  EXPECT_STREQ("source.cpp:33 - Failed to set or get the file cursor position.",
    ex.what());
}



TEST_F(test_sys_exceptions, image_read_error)
{
  image_read_error ex("source.cpp", 33u, "path/to/the_file_name.txt");
  EXPECT_STREQ(
    "source.cpp:33 - Failed to read the image from file "
    "'path/to/the_file_name.txt'.",
    ex.what());
}



TEST_F(test_sys_exceptions, image_write_error)
{
  image_write_error ex("source.cpp", 33u, "path/to/the_file_name.txt");
  EXPECT_STREQ(
    "source.cpp:33 - Failed to write the image to file "
    "'path/to/the_file_name.txt'.",
    ex.what());
}
