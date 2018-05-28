// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/sys/file_handle.hpp"
#include "hou/sys/sys_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_file_handle : public Test
{
public:
  static const std::string filename;
  static const std::string file_content;

public:
  test_file_handle();
  virtual ~test_file_handle();
};



class test_file_handle_death_test : public test_file_handle
{
public:
  using test_file_handle::test_file_handle;
};



const std::string test_file_handle::filename
  = get_output_dir() + u8"test_file_handle-\U00004f60\U0000597d.txt";
const std::string test_file_handle::file_content = u8"This is\na test file";



test_file_handle::test_file_handle()
{
  file_handle f(filename, file_open_mode::write, file_type::binary);
  fwrite(file_content.data(), sizeof(char), file_content.size(), f);
}



test_file_handle::~test_file_handle()
{
  if(check_dir(filename))
  {
    remove_dir(filename);
  }
}

}  // namespace



TEST_F(test_file_handle, path_constructor)
{
  file_handle f(filename, file_open_mode::read, file_type::binary);
  EXPECT_NE(nullptr, static_cast<FILE*>(f));
}



TEST_F(test_file_handle_death_test, path_constructor_error)
{
  std::string invalid_filename = u8"InvalidFileName.txt";
  EXPECT_ERROR_N(
    file_handle f(invalid_filename, file_open_mode::read, file_type::binary),
    file_open_error, invalid_filename);
}



TEST_F(test_file_handle, move_constructor)
{
  file_handle f_dummy(filename, file_open_mode::read, file_type::binary);
  FILE* file_ref = static_cast<FILE*>(f_dummy);
  file_handle f(std::move(f_dummy));
  EXPECT_EQ(file_ref, static_cast<FILE*>(f));
  EXPECT_EQ(nullptr, static_cast<FILE*>(f_dummy));
}



TEST_F(test_file_handle, close)
{
  file_handle f(filename, file_open_mode::read, file_type::binary);
  EXPECT_NE(nullptr, static_cast<FILE*>(f));
  f.close();
  EXPECT_EQ(nullptr, static_cast<FILE*>(f));
}



TEST_F(test_file_handle_death_test, close_error)
{
  file_handle f(filename, file_open_mode::read, file_type::binary);
  EXPECT_NE(nullptr, static_cast<FILE*>(f));
  f.close();
  EXPECT_EQ(nullptr, static_cast<FILE*>(f));
  EXPECT_ERROR_0(f.close(), file_close_error);
}



TEST_F(test_file_handle, get_file_mode_string)
{
  EXPECT_EQ("r", get_file_mode_string(file_open_mode::read, file_type::text));
  EXPECT_EQ("w", get_file_mode_string(file_open_mode::write, file_type::text));
  EXPECT_EQ("a", get_file_mode_string(file_open_mode::append, file_type::text));
  EXPECT_EQ(
    "rb", get_file_mode_string(file_open_mode::read, file_type::binary));
  EXPECT_EQ(
    "wb", get_file_mode_string(file_open_mode::write, file_type::binary));
  EXPECT_EQ(
    "ab", get_file_mode_string(file_open_mode::append, file_type::binary));
}



TEST_F(test_file_handle, open_close_file)
{
  FILE* f = open_file(filename, "rb");
  EXPECT_NE(nullptr, f);
  EXPECT_TRUE(close_file(f));
}



TEST_F(test_file_handle, open_file_failure)
{
  FILE* f = open_file("dummy", "rb");
  EXPECT_EQ(nullptr, f);
}



TEST_F(test_file_handle, close_file_failure)
{
  FILE* f = open_file("dummy", "rb");
  close_file(f);
  EXPECT_FALSE(close_file(f));
}



TEST_F(test_file_handle, check_dir)
{
  EXPECT_TRUE(check_dir(filename));
  EXPECT_TRUE(check_dir(get_output_dir()));
  EXPECT_FALSE(check_dir(u8"DummyName"));
  EXPECT_FALSE(check_dir(u8"./DummyDir/"));
}



TEST_F(test_file_handle, rename_dir)
{
  const std::string new_name
    = get_output_dir() + u8"test_file_handle-\U00004f61\U0000597e-2.txt";

  EXPECT_TRUE(check_dir(filename));
  EXPECT_FALSE(check_dir(new_name));

  EXPECT_TRUE(rename_dir(filename, new_name));
  EXPECT_FALSE(check_dir(filename));
  EXPECT_TRUE(check_dir(new_name));

  EXPECT_TRUE(rename_dir(new_name, filename));
  EXPECT_TRUE(check_dir(filename));
  EXPECT_FALSE(check_dir(new_name));

  // Just for safety reason... If the test fails and the file does not get
  // renamed back, it will not be cleaned up at the end of the test.
  if(check_dir(new_name))
  {
    remove_dir(new_name);
  }
}



TEST_F(test_file_handle, rename_invalid_dir)
{
  EXPECT_FALSE(rename_dir(u8"notaValidFile.txt", u8"someOtherFile.txt"));
}



TEST_F(test_file_handle, remove_dir)
{
  const std::string new_name
    = get_output_dir() + u8"test_file_handle-\U00004f61\U0000597e-2.txt";
  const std::string to_write = u8"I have\nwritten this";

  EXPECT_FALSE(check_dir(new_name));

  {
    file_handle f(new_name, file_open_mode::write, file_type::binary);
    fwrite(to_write.data(), sizeof(char), to_write.size(), f);
  }

  {
    file_handle f(new_name, file_open_mode::read, file_type::binary);
    EXPECT_NE(nullptr, static_cast<FILE*>(f));
  }

  EXPECT_TRUE(check_dir(new_name));
  EXPECT_TRUE(remove_dir(new_name));
  EXPECT_FALSE(check_dir(new_name));
}



TEST_F(test_file_handle, remove_invalid_dir)
{
  EXPECT_FALSE(remove_dir("notaValidFile.txt"));
}



TEST_F(test_file_handle, get_dir_byte_size)
{
  EXPECT_EQ(file_content.size(), get_dir_byte_size(filename));
}



TEST_F(test_file_handle, get_invalid_dir_byte_size)
{
  EXPECT_EQ(
    std::numeric_limits<size_t>::max(), get_dir_byte_size("invalid.txt"));
}



TEST_F(test_file_handle, get_filename_extension)
{
  EXPECT_EQ(u8"", get_filename_extension(u8""));
  EXPECT_EQ(u8"", get_filename_extension(u8"fileWithoutExtension"));
  EXPECT_EQ(u8"txt", get_filename_extension(u8"fileWithExtension.txt"));
  EXPECT_EQ(u8"txt2", get_filename_extension(u8"filename.with.points.txt2"));
  EXPECT_EQ(u8"txt", get_filename_extension(u8".hiddenFile.txt"));
}



TEST_F(test_file_handle, get_file_descriptor)
{
  file_handle fh(filename, file_open_mode::read, file_type::binary);
  EXPECT_GE(get_file_descriptor(fh), 0);
}



TEST_F(test_file_handle, get_file_descriptor_error)
{
  EXPECT_EQ(-1, get_file_descriptor(nullptr));
}



TEST_F(test_file_handle, get_file_byte_size)
{
  file_handle fh(filename, file_open_mode::read, file_type::binary);
  EXPECT_EQ(file_content.size(), get_file_byte_size(get_file_descriptor(fh)));
}



// MSVC will trigger an assertion making this untestable.
#ifdef HOU_COMPILER_MSVC
TEST_F(test_file_handle, DISABLED_get_invalid_file_byte_size)
#else
TEST_F(test_file_handle, get_invalid_file_byte_size)
#endif
{
  EXPECT_EQ(std::numeric_limits<size_t>::max(), get_file_byte_size(-1));
}
