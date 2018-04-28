// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/TestData.hpp"

#include "hou/sys/SysError.hpp"
#include "hou/sys/File.hpp"

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
  , FileType type);



const std::string TestFile::fileName = getOutputDir()
  + u8"TestFile-\U00004f60\U0000597d-BinaryFile.txt";
const std::string TestFile::fileContent = u8"This is\na test file";



TestFile::TestFile()
{
  File f(fileName, FileOpenMode::Write, FileType::Binary);
  f.write(fileContent);
}



TestFile::~TestFile()
{
  removeDir(fileName);
}



template <typename Container>
  bool testFileContents(const std::string& filename, const Container& expected
  , FileType type)
{
  File f(filename, FileOpenMode::Read, type);
  Container buffer(f.getByteCount(), 0);
  f.read(buffer);
  return expected == buffer;
}

}



TEST_F(TestFile, Creation)
{
  File f(fileName, FileOpenMode::Read, FileType::Binary);
  EXPECT_FALSE(f.eof());
  EXPECT_FALSE(f.error());
  EXPECT_EQ(fileContent.size(), f.getByteCount());
  EXPECT_EQ(0, f.tell());
  std::string content(f.getByteCount(), 0);
  f.read(content);
  EXPECT_EQ(fileContent, content);
}



TEST_F(TestFileDeathTest, CreationError)
{
  HOU_EXPECT_ERROR(File f("NotAValidName.txt", FileOpenMode::Read
    , FileType::Binary), std::runtime_error
    , format_string(get_text(SysError::FileOpen), "NotAValidName.txt"));
}



TEST_F(TestFile, MoveConstructor)
{
  File fDummy(fileName, FileOpenMode::Read, FileType::Binary);
  File f(std::move(fDummy));
  EXPECT_FALSE(f.eof());
  EXPECT_FALSE(f.error());
  EXPECT_EQ(fileContent.size(), f.getByteCount());
  EXPECT_EQ(0, f.tell());
  std::string content(f.getByteCount(), 0);
  f.read(content);
  EXPECT_EQ(fileContent, content);
}



TEST_F(TestFile, CursorPositioning)
{
  File f(fileName, FileOpenMode::Read, FileType::Binary);

  EXPECT_EQ(0, f.tell());

  f.seekSet(5);
  EXPECT_EQ(5, f.tell());

  f.seekOffset(2);
  EXPECT_EQ(7, f.tell());

  f.seekOffset(-3);
  EXPECT_EQ(4, f.tell());
}



TEST_F(TestFileDeathTest, CursorPositioningError)
{
  File f(fileName, FileOpenMode::Read, FileType::Binary);

  HOU_EXPECT_ERROR(f.seekSet(-1), std::runtime_error
    , get_text(SysError::FileSeek));

  HOU_EXPECT_ERROR(f.seekOffset(-2), std::runtime_error
    , get_text(SysError::FileSeek));

  // error flag is not set, only for read / write errors!
  EXPECT_FALSE(f.error());
}



TEST_F(TestFile, FileSize)
{
  File f(fileName, FileOpenMode::Read, FileType::Binary);
  EXPECT_EQ(19u, f.getByteCount());
}



TEST_F(TestFile, FileSizeCursorPosition)
{
  // Test if the size is correct if the cursor is not at the beginning, and if
  // requesting the file size does not change the cursor position.
  File f(fileName, FileOpenMode::Read, FileType::Binary);

  char c;
  f.getc(c);
  f.getc(c);
  long curPos = f.tell();
  size_t fileSize = f.getByteCount();

  EXPECT_EQ(curPos, f.tell());
  EXPECT_EQ(19u, fileSize);
}




TEST_F(TestFile, GetcBinary)
{
  File f(fileName, FileOpenMode::Read, FileType::Binary);
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
    File f(fileName, FileOpenMode::Write, FileType::Binary);
    for(size_t i = 0; i < toWrite.size(); ++i)
    {
      f.putc(toWrite[i]);
    }
  }
  EXPECT_TRUE(testFileContents(fileName, toWrite, FileType::Binary));
}



TEST_F(TestFile, GetsBinary)
{
  File f(fileName, FileOpenMode::Read, FileType::Binary);
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
    File f(fileName, FileOpenMode::Write, FileType::Binary);
    f.puts(toWrite);
  }
  EXPECT_TRUE(testFileContents(fileName, toWrite, FileType::Binary));
}



TEST_F(TestFile, ReadBufferBinary)
{
  File f(fileName, FileOpenMode::Read, FileType::Binary);
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
    File f(fileName, FileOpenMode::Write, FileType::Binary);
    f.write(toWrite.data(), toWrite.size());
  }
  EXPECT_TRUE(testFileContents(fileName, toWrite, FileType::Binary));
}



TEST_F(TestFile, ReadStringBinary)
{
  File f(fileName, FileOpenMode::Read, FileType::Binary);
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
    File f(fileName, FileOpenMode::Write, FileType::Binary);
    f.write(toWrite);
  }
  EXPECT_TRUE(testFileContents(fileName, toWrite, FileType::Binary));
}



TEST_F(TestFile, ReadContainerBinary)
{
  File f(fileName, FileOpenMode::Read, FileType::Binary);
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
    File f(fileName, FileOpenMode::Write, FileType::Binary);
    f.write(toWrite);
  }
  EXPECT_TRUE(testFileContents(fileName, toWrite, FileType::Binary));
}



TEST_F(TestFile, AppendBinary)
{
  std::string toWrite = u8"I have\nwritten this";
  {
    File f(fileName, FileOpenMode::Append, FileType::Binary);
    f.write(toWrite);
  }
  EXPECT_TRUE(testFileContents(fileName, fileContent + toWrite
    , FileType::Binary));
}



TEST_F(TestFileDeathTest, ReadFromWriteOnlyFile)
{
  File f(fileName, FileOpenMode::Write, FileType::Binary);

  char c;
  HOU_EXPECT_ERROR(f.getc(c), std::runtime_error
    , get_text(SysError::FileRead));

  std::string buffer(3u, 0);
  HOU_EXPECT_ERROR(f.read(buffer), std::runtime_error
    , get_text(SysError::FileRead));

#if defined(HOU_USE_EXCEPTIONS)
  // With no exceptions handling, the HOU_EXPECT_ERROR macro does some magic,
  // so that in the end the error flag is not set for f.
  EXPECT_TRUE(f.error());
#endif
}



TEST_F(TestFileDeathTest, WriteToReadOnlyFile)
{
  File f(fileName, FileOpenMode::Read, FileType::Binary);

  HOU_EXPECT_ERROR(f.putc('a'), std::runtime_error
    , get_text(SysError::FileWrite));

  std::string toWrite = u8"I have\nwritten this";
  HOU_EXPECT_ERROR(f.write(toWrite), std::runtime_error
    , get_text(SysError::FileWrite));

#ifndef HOU_DISABLE_EXCEPTIONS
  // With no exceptions handling, the HOU_EXPECT_ERROR macro does some magic,
  // so that in the end the error flag is not set for f.
  EXPECT_TRUE(f.error());
#endif
}



TEST_F(TestFile, Eof)
{
  File f(fileName, FileOpenMode::Read, FileType::Binary);
  char c = 0;
  while(f.getc(c)) {}
  EXPECT_TRUE(f.eof());
}



TEST_F(TestFile, GetSizeAfterPutc)
{
  // Note: on some filesystems the size is not immediately updated.
  // For this reason it is necessary to open the file again to check the size.
  {
    File f(fileName, FileOpenMode::Append, FileType::Binary);
    EXPECT_EQ(fileContent.size(), f.getByteCount());
    f.putc('a');
  }
  {
    File f(fileName, FileOpenMode::Read, FileType::Binary);
    EXPECT_EQ(fileContent.size() + 1u, f.getByteCount());
  }
}



TEST_F(TestFile, GetSizeAfterPuts)
{
  // Note: on some filesystems the size is not immediately updated.
  // For this reason it is necessary to open the file again to check the size.
  std::string toWrite = u8"New stuff!";
  {
    File f(fileName, FileOpenMode::Append, FileType::Binary);
    EXPECT_EQ(fileContent.size(), f.getByteCount());
    f.puts(toWrite);
  }
  {
    File f(fileName, FileOpenMode::Read, FileType::Binary);
    EXPECT_EQ(fileContent.size() + toWrite.size(), f.getByteCount());
  }
}



TEST_F(TestFile, GetSizeAfterWrite)
{
  // Note: on some filesystems the size is not immediately updated.
  // For this reason it is necessary to open the file again to check the size.
  std::vector<uint16_t> toWrite{23, 12, 15, 0, 14, 1};
  {
    File f(fileName, FileOpenMode::Append, FileType::Binary);
    EXPECT_EQ(fileContent.size(), f.getByteCount());
    f.write(toWrite);
  }
  {
    File f(fileName, FileOpenMode::Read, FileType::Binary);
    EXPECT_EQ(fileContent.size() + toWrite.size() * sizeof(uint16_t)
      , f.getByteCount());
  }
}

// Test flush.
// Test flush error.
// Test close error.
// Test tell error.
// Tests for text files.

