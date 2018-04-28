// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/sys/sys_error.hpp"
#include "hou/sys/file.hpp"

using namespace hou;



namespace
{

class TestFile
  : public ::testing::Test
{
public:
  static const std::string fileName;
  static const std::string fileContent;

public:
  TestFile();
  virtual ~TestFile();
};



class TestFileDeathTest
  : public TestFile
{
public:
  using TestFile::TestFile;
};



template <typename Container>
  bool testFileContents(const std::string& filename, const Container& expected
  , file_type type);



const std::string TestFile::fileName = getOutputDir()
  + u8"TestFile-\U00004f60\U0000597d-BinaryFile.txt";
const std::string TestFile::fileContent = u8"This is\na test file";



TestFile::TestFile()
{
  file f(fileName, file_open_mode::write, file_type::binary);
  f.write(fileContent);
}



TestFile::~TestFile()
{
  remove_dir(fileName);
}



template <typename Container>
  bool testFileContents(const std::string& filename, const Container& expected
  , file_type type)
{
  file f(filename, file_open_mode::read, type);
  Container buffer(f.get_byte_count(), 0);
  f.read(buffer);
  return expected == buffer;
}

}



TEST_F(TestFile, Creation)
{
  file f(fileName, file_open_mode::read, file_type::binary);
  EXPECT_FALSE(f.eof());
  EXPECT_FALSE(f.error());
  EXPECT_EQ(fileContent.size(), f.get_byte_count());
  EXPECT_EQ(0, f.tell());
  std::string content(f.get_byte_count(), 0);
  f.read(content);
  EXPECT_EQ(fileContent, content);
}



TEST_F(TestFileDeathTest, CreationError)
{
  HOU_EXPECT_ERROR(file f("NotAValidName.txt", file_open_mode::read
    , file_type::binary), std::runtime_error
    , format_string(get_text(sys_error::file_open), "NotAValidName.txt"));
}



TEST_F(TestFile, MoveConstructor)
{
  file fDummy(fileName, file_open_mode::read, file_type::binary);
  file f(std::move(fDummy));
  EXPECT_FALSE(f.eof());
  EXPECT_FALSE(f.error());
  EXPECT_EQ(fileContent.size(), f.get_byte_count());
  EXPECT_EQ(0, f.tell());
  std::string content(f.get_byte_count(), 0);
  f.read(content);
  EXPECT_EQ(fileContent, content);
}



TEST_F(TestFile, CursorPositioning)
{
  file f(fileName, file_open_mode::read, file_type::binary);

  EXPECT_EQ(0, f.tell());

  f.seek_set(5);
  EXPECT_EQ(5, f.tell());

  f.seek_offset(2);
  EXPECT_EQ(7, f.tell());

  f.seek_offset(-3);
  EXPECT_EQ(4, f.tell());
}



TEST_F(TestFileDeathTest, CursorPositioningError)
{
  file f(fileName, file_open_mode::read, file_type::binary);

  HOU_EXPECT_ERROR(f.seek_set(-1), std::runtime_error
    , get_text(sys_error::file_seek));

  HOU_EXPECT_ERROR(f.seek_offset(-2), std::runtime_error
    , get_text(sys_error::file_seek));

  // error flag is not set, only for read / write errors!
  EXPECT_FALSE(f.error());
}



TEST_F(TestFile, FileSize)
{
  file f(fileName, file_open_mode::read, file_type::binary);
  EXPECT_EQ(19u, f.get_byte_count());
}



TEST_F(TestFile, FileSizeCursorPosition)
{
  // Test if the size is correct if the cursor is not at the beginning, and if
  // requesting the ph_file size does not change the cursor position.
  file f(fileName, file_open_mode::read, file_type::binary);

  char c;
  f.getc(c);
  f.getc(c);
  long curPos = f.tell();
  size_t fileSize = f.get_byte_count();

  EXPECT_EQ(curPos, f.tell());
  EXPECT_EQ(19u, fileSize);
}




TEST_F(TestFile, GetcBinary)
{
  file f(fileName, file_open_mode::read, file_type::binary);
  char c = 0;

  size_t i = 0;
  while(f.getc(c))
  {
    EXPECT_EQ(fileContent[i], c);
    ++i;
  }
  EXPECT_TRUE(f.eof());
}



TEST_F(TestFile, PutcBinary)
{
  std::string toWrite = u8"I have\nwritten this";
  {
    file f(fileName, file_open_mode::write, file_type::binary);
    for(size_t i = 0; i < toWrite.size(); ++i)
    {
      f.putc(toWrite[i]);
    }
  }
  EXPECT_TRUE(testFileContents(fileName, toWrite, file_type::binary));
}



TEST_F(TestFile, GetsBinary)
{
  file f(fileName, file_open_mode::read, file_type::binary);
  // Since a \0 is added, an extra character is needed
  std::string s(4u, 'a');

  // Gets stop reading at new lines, so we must be careful with that when
  // performing the comparisons inside the test.
  size_t cursor = 0;
  while(size_t count = f.gets(s))
  {
    EXPECT_EQ(fileContent.substr(cursor, count), s.substr(0u, count));
    cursor += count;
  }
  EXPECT_TRUE(f.eof());
}



TEST_F(TestFile, PutsBinary)
{
  std::string toWrite = u8"I have\nwritten this";
  {
    file f(fileName, file_open_mode::write, file_type::binary);
    f.puts(toWrite);
  }
  EXPECT_TRUE(testFileContents(fileName, toWrite, file_type::binary));
}



TEST_F(TestFile, ReadBufferBinary)
{
  file f(fileName, file_open_mode::read, file_type::binary);
  std::vector<char> buf(3u, 0);

  size_t i = 0;
  while(f.read(buf.data(), buf.size()) == buf.size())
  {
    HOU_EXPECT_ARRAY_EQ(fileContent.substr(i * buf.size(), buf.size()).data()
      , buf.data(), buf.size());
    ++i;
  }
  EXPECT_TRUE(f.eof());
}



TEST_F(TestFile, WriteBufferBinary)
{
  std::vector<char> toWrite{23, 12, 15, 0, 14, 1};
  {
    file f(fileName, file_open_mode::write, file_type::binary);
    f.write(toWrite.data(), toWrite.size());
  }
  EXPECT_TRUE(testFileContents(fileName, toWrite, file_type::binary));
}



TEST_F(TestFile, ReadStringBinary)
{
  file f(fileName, file_open_mode::read, file_type::binary);
  std::string buf(3u, 0);

  size_t i = 0;
  while(f.read(buf) == buf.size())
  {
    HOU_EXPECT_ARRAY_EQ(fileContent.substr(i * buf.size(), buf.size()).data()
      , buf.data(), buf.size());
    ++i;
  }
  EXPECT_TRUE(f.eof());
}



TEST_F(TestFile, WriteStringBinary)
{
  std::string toWrite = u8"I have\nwritten this";
  {
    file f(fileName, file_open_mode::write, file_type::binary);
    f.write(toWrite);
  }
  EXPECT_TRUE(testFileContents(fileName, toWrite, file_type::binary));
}



TEST_F(TestFile, ReadContainerBinary)
{
  file f(fileName, file_open_mode::read, file_type::binary);
  std::vector<char> buf(3u, 0);

  size_t i = 0;
  while(f.read(buf) == buf.size())
  {
    HOU_EXPECT_ARRAY_EQ(fileContent.substr(i * buf.size(), buf.size()).data()
      , buf.data(), buf.size());
    ++i;
  }
  EXPECT_TRUE(f.eof());
}



TEST_F(TestFile, WriteContainerBinary)
{
  std::vector<char> toWrite{23, 12, 15, 0, 14, 1};
  {
    file f(fileName, file_open_mode::write, file_type::binary);
    f.write(toWrite);
  }
  EXPECT_TRUE(testFileContents(fileName, toWrite, file_type::binary));
}



TEST_F(TestFile, AppendBinary)
{
  std::string toWrite = u8"I have\nwritten this";
  {
    file f(fileName, file_open_mode::append, file_type::binary);
    f.write(toWrite);
  }
  EXPECT_TRUE(testFileContents(fileName, fileContent + toWrite
    , file_type::binary));
}



TEST_F(TestFileDeathTest, ReadFromWriteOnlyFile)
{
  file f(fileName, file_open_mode::write, file_type::binary);

  char c;
  HOU_EXPECT_ERROR(f.getc(c), std::runtime_error
    , get_text(sys_error::file_read));

  std::string buffer(3u, 0);
  HOU_EXPECT_ERROR(f.read(buffer), std::runtime_error
    , get_text(sys_error::file_read));

#if defined(HOU_USE_EXCEPTIONS)
  // With no exceptions handling, the HOU_EXPECT_ERROR macro does some magic,
  // so that in the end the error flag is not set for f.
  EXPECT_TRUE(f.error());
#endif
}



TEST_F(TestFileDeathTest, WriteToReadOnlyFile)
{
  file f(fileName, file_open_mode::read, file_type::binary);

  HOU_EXPECT_ERROR(f.putc('a'), std::runtime_error
    , get_text(sys_error::file_write));

  std::string toWrite = u8"I have\nwritten this";
  HOU_EXPECT_ERROR(f.write(toWrite), std::runtime_error
    , get_text(sys_error::file_write));

#ifndef HOU_DISABLE_EXCEPTIONS
  // With no exceptions handling, the HOU_EXPECT_ERROR macro does some magic,
  // so that in the end the error flag is not set for f.
  EXPECT_TRUE(f.error());
#endif
}



TEST_F(TestFile, Eof)
{
  file f(fileName, file_open_mode::read, file_type::binary);
  char c = 0;
  while(f.getc(c)) {}
  EXPECT_TRUE(f.eof());
}



TEST_F(TestFile, GetSizeAfterPutc)
{
  // Note: on some filesystems the size is not immediately updated.
  // For this reason it is necessary to open the ph_file again to check the size.
  {
    file f(fileName, file_open_mode::append, file_type::binary);
    EXPECT_EQ(fileContent.size(), f.get_byte_count());
    f.putc('a');
  }
  {
    file f(fileName, file_open_mode::read, file_type::binary);
    EXPECT_EQ(fileContent.size() + 1u, f.get_byte_count());
  }
}



TEST_F(TestFile, GetSizeAfterPuts)
{
  // Note: on some filesystems the size is not immediately updated.
  // For this reason it is necessary to open the ph_file again to check the size.
  std::string toWrite = u8"New stuff!";
  {
    file f(fileName, file_open_mode::append, file_type::binary);
    EXPECT_EQ(fileContent.size(), f.get_byte_count());
    f.puts(toWrite);
  }
  {
    file f(fileName, file_open_mode::read, file_type::binary);
    EXPECT_EQ(fileContent.size() + toWrite.size(), f.get_byte_count());
  }
}



TEST_F(TestFile, GetSizeAfterWrite)
{
  // Note: on some filesystems the size is not immediately updated.
  // For this reason it is necessary to open the ph_file again to check the size.
  std::vector<uint16_t> toWrite{23, 12, 15, 0, 14, 1};
  {
    file f(fileName, file_open_mode::append, file_type::binary);
    EXPECT_EQ(fileContent.size(), f.get_byte_count());
    f.write(toWrite);
  }
  {
    file f(fileName, file_open_mode::read, file_type::binary);
    EXPECT_EQ(fileContent.size() + toWrite.size() * sizeof(uint16_t)
      , f.get_byte_count());
  }
}

// Test flush.
// Test flush error.
// Test close error.
// Test tell error.
// Tests for text files.

