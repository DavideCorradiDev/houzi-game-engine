// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/sys/file.hpp"
#include "hou/sys/sys_error.hpp"

using namespace hou;



namespace
{

class test_file : public ::testing::Test
{
public:
  static const std::string filename;
  static const std::string file_content;

public:
  test_file();
  virtual ~test_file();
};



class test_file_death_test : public test_file
{
public:
  using test_file::test_file;
};



template <typename Container>
bool testFileContents(
  const std::string& filename, const Container& expected, file_type type);



const std::string test_file::filename
  = get_output_dir() + u8"test_file-\U00004f60\U0000597d-BinaryFile.txt";
const std::string test_file::file_content = u8"This is\na test file";



test_file::test_file()
{
  file f(filename, file_open_mode::write, file_type::binary);
  f.write(file_content);
}



test_file::~test_file()
{
  remove_dir(filename);
}



template <typename Container>
bool testFileContents(
  const std::string& filename, const Container& expected, file_type type)
{
  file f(filename, file_open_mode::read, type);
  Container buffer(f.get_byte_count(), 0);
  f.read(buffer);
  return expected == buffer;
}

}  // namespace



TEST_F(test_file, creation)
{
  file f(filename, file_open_mode::read, file_type::binary);
  EXPECT_FALSE(f.eof());
  EXPECT_FALSE(f.error());
  EXPECT_EQ(file_content.size(), f.get_byte_count());
  EXPECT_EQ(0, f.tell());
  std::string content(f.get_byte_count(), 0);
  f.read(content);
  EXPECT_EQ(file_content, content);
}



TEST_F(test_file_death_test, creation_error)
{
  HOU_EXPECT_ERROR(
    file f("NotAValidName.txt", file_open_mode::read, file_type::binary),
    std::runtime_error,
    format_string(get_text(sys_error::file_open), "NotAValidName.txt"));
}



TEST_F(test_file, move_constructor)
{
  file f_dummy(filename, file_open_mode::read, file_type::binary);
  file f(std::move(f_dummy));
  EXPECT_FALSE(f.eof());
  EXPECT_FALSE(f.error());
  EXPECT_EQ(file_content.size(), f.get_byte_count());
  EXPECT_EQ(0, f.tell());
  std::string content(f.get_byte_count(), 0);
  f.read(content);
  EXPECT_EQ(file_content, content);
}



TEST_F(test_file, cursor_positioning)
{
  file f(filename, file_open_mode::read, file_type::binary);

  EXPECT_EQ(0, f.tell());

  f.seek_set(5);
  EXPECT_EQ(5, f.tell());

  f.seek_offset(2);
  EXPECT_EQ(7, f.tell());

  f.seek_offset(-3);
  EXPECT_EQ(4, f.tell());
}



TEST_F(test_file_death_test, cursor_positioning_error)
{
  file f(filename, file_open_mode::read, file_type::binary);

  HOU_EXPECT_ERROR(
    f.seek_set(-1), std::runtime_error, get_text(sys_error::file_seek));

  HOU_EXPECT_ERROR(
    f.seek_offset(-2), std::runtime_error, get_text(sys_error::file_seek));

  // error flag is not set, only for read / write errors!
  EXPECT_FALSE(f.error());
}



TEST_F(test_file, file_size)
{
  file f(filename, file_open_mode::read, file_type::binary);
  EXPECT_EQ(19u, f.get_byte_count());
}



TEST_F(test_file, file_size_cursor_position)
{
  // Test if the size is correct if the cursor is not at the beginning, and if
  // requesting the file size does not change the cursor position.
  file f(filename, file_open_mode::read, file_type::binary);

  char c;
  f.getc(c);
  f.getc(c);
  long cur_pos = f.tell();
  size_t file_size = f.get_byte_count();

  EXPECT_EQ(cur_pos, f.tell());
  EXPECT_EQ(19u, file_size);
}



TEST_F(test_file, getc_binary)
{
  file f(filename, file_open_mode::read, file_type::binary);
  char c = 0;

  size_t i = 0;
  while(f.getc(c))
  {
    EXPECT_EQ(file_content[i], c);
    ++i;
  }
  EXPECT_TRUE(f.eof());
}



TEST_F(test_file, putc_binary)
{
  std::string to_write = u8"I have\nwritten this";
  {
    file f(filename, file_open_mode::write, file_type::binary);
    for(size_t i = 0; i < to_write.size(); ++i)
    {
      f.putc(to_write[i]);
    }
  }
  EXPECT_TRUE(testFileContents(filename, to_write, file_type::binary));
}



TEST_F(test_file, gets_binary)
{
  file f(filename, file_open_mode::read, file_type::binary);
  // Since a \0 is added, an extra character is needed
  std::string s(4u, 'a');

  // Gets stop reading at new lines, so we must be careful with that when
  // performing the comparisons inside the test.
  size_t cursor = 0;
  while(size_t count = f.gets(s))
  {
    EXPECT_EQ(file_content.substr(cursor, count), s.substr(0u, count));
    cursor += count;
  }
  EXPECT_TRUE(f.eof());
}



TEST_F(test_file, puts_binary)
{
  std::string to_write = u8"I have\nwritten this";
  {
    file f(filename, file_open_mode::write, file_type::binary);
    f.puts(to_write);
  }
  EXPECT_TRUE(testFileContents(filename, to_write, file_type::binary));
}



TEST_F(test_file, read_buffer_binary)
{
  file f(filename, file_open_mode::read, file_type::binary);
  std::vector<char> buf(3u, 0);

  size_t i = 0;
  while(f.read(buf.data(), buf.size()) == buf.size())
  {
    HOU_EXPECT_ARRAY_EQ(file_content.substr(i * buf.size(), buf.size()).data(),
      buf.data(), buf.size());
    ++i;
  }
  EXPECT_TRUE(f.eof());
}



TEST_F(test_file, write_buffer_binary)
{
  std::vector<char> to_write{23, 12, 15, 0, 14, 1};
  {
    file f(filename, file_open_mode::write, file_type::binary);
    f.write(to_write.data(), to_write.size());
  }
  EXPECT_TRUE(testFileContents(filename, to_write, file_type::binary));
}



TEST_F(test_file, read_string_binary)
{
  file f(filename, file_open_mode::read, file_type::binary);
  std::string buf(3u, 0);

  size_t i = 0;
  while(f.read(buf) == buf.size())
  {
    HOU_EXPECT_ARRAY_EQ(file_content.substr(i * buf.size(), buf.size()).data(),
      buf.data(), buf.size());
    ++i;
  }
  EXPECT_TRUE(f.eof());
}



TEST_F(test_file, write_string_binary)
{
  std::string to_write = u8"I have\nwritten this";
  {
    file f(filename, file_open_mode::write, file_type::binary);
    f.write(to_write);
  }
  EXPECT_TRUE(testFileContents(filename, to_write, file_type::binary));
}



TEST_F(test_file, read_container_binary)
{
  file f(filename, file_open_mode::read, file_type::binary);
  std::vector<char> buf(3u, 0);

  size_t i = 0;
  while(f.read(buf) == buf.size())
  {
    HOU_EXPECT_ARRAY_EQ(file_content.substr(i * buf.size(), buf.size()).data(),
      buf.data(), buf.size());
    ++i;
  }
  EXPECT_TRUE(f.eof());
}



TEST_F(test_file, write_container_binary)
{
  std::vector<char> to_write{23, 12, 15, 0, 14, 1};
  {
    file f(filename, file_open_mode::write, file_type::binary);
    f.write(to_write);
  }
  EXPECT_TRUE(testFileContents(filename, to_write, file_type::binary));
}



TEST_F(test_file, append_binary)
{
  std::string to_write = u8"I have\nwritten this";
  {
    file f(filename, file_open_mode::append, file_type::binary);
    f.write(to_write);
  }
  EXPECT_TRUE(
    testFileContents(filename, file_content + to_write, file_type::binary));
}



TEST_F(test_file_death_test, read_from_write_only_file)
{
  file f(filename, file_open_mode::write, file_type::binary);

  char c;
  HOU_EXPECT_ERROR(
    f.getc(c), std::runtime_error, get_text(sys_error::file_read));

  std::string buffer(3u, 0);
  HOU_EXPECT_ERROR(
    f.read(buffer), std::runtime_error, get_text(sys_error::file_read));

#if defined(HOU_USE_EXCEPTIONS)
  // With no exceptions handling, the HOU_EXPECT_ERROR macro does some magic,
  // so that in the end the error flag is not set for f.
  EXPECT_TRUE(f.error());
#endif
}



TEST_F(test_file_death_test, write_to_read_only_file)
{
  file f(filename, file_open_mode::read, file_type::binary);

  HOU_EXPECT_ERROR(
    f.putc('a'), std::runtime_error, get_text(sys_error::file_write));

  std::string to_write = u8"I have\nwritten this";
  HOU_EXPECT_ERROR(
    f.write(to_write), std::runtime_error, get_text(sys_error::file_write));

#ifndef HOU_DISABLE_EXCEPTIONS
  // With no exceptions handling, the HOU_EXPECT_ERROR macro does some magic,
  // so that in the end the error flag is not set for f.
  EXPECT_TRUE(f.error());
#endif
}



TEST_F(test_file, eof)
{
  file f(filename, file_open_mode::read, file_type::binary);
  char c = 0;
  while(f.getc(c))
  {
  }
  EXPECT_TRUE(f.eof());
}



TEST_F(test_file, get_size_after_putc)
{
  // Note: on some filesystems the size is not immediately updated.
  // For this reason it is necessary to open the file again to check the size.
  {
    file f(filename, file_open_mode::append, file_type::binary);
    EXPECT_EQ(file_content.size(), f.get_byte_count());
    f.putc('a');
  }
  {
    file f(filename, file_open_mode::read, file_type::binary);
    EXPECT_EQ(file_content.size() + 1u, f.get_byte_count());
  }
}



TEST_F(test_file, get_size_after_puts)
{
  // Note: on some filesystems the size is not immediately updated.
  // For this reason it is necessary to open the file again to check the size.
  std::string to_write = u8"New stuff!";
  {
    file f(filename, file_open_mode::append, file_type::binary);
    EXPECT_EQ(file_content.size(), f.get_byte_count());
    f.puts(to_write);
  }
  {
    file f(filename, file_open_mode::read, file_type::binary);
    EXPECT_EQ(file_content.size() + to_write.size(), f.get_byte_count());
  }
}



TEST_F(test_file, get_size_after_write)
{
  // Note: on some filesystems the size is not immediately updated.
  // For this reason it is necessary to open the file again to check the size.
  std::vector<uint16_t> to_write{23, 12, 15, 0, 14, 1};
  {
    file f(filename, file_open_mode::append, file_type::binary);
    EXPECT_EQ(file_content.size(), f.get_byte_count());
    f.write(to_write);
  }
  {
    file f(filename, file_open_mode::read, file_type::binary);
    EXPECT_EQ(file_content.size() + to_write.size() * sizeof(uint16_t),
      f.get_byte_count());
  }
}

// Test flush.
// Test flush error.
// Test close error.
// Test tell error.
// Tests for text files.
