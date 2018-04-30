// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/sys/sys_error.hpp"
#include "hou/sys/file_handle.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestFileHandle
  : public Test
{
public:
  static const std::string fileName;
  static const std::string fileContent;

public:
  TestFileHandle();
  virtual ~TestFileHandle();
};



class TestFileHandleDeathTest
  : public TestFileHandle
{
public:
  using TestFileHandle::TestFileHandle;
};



const std::string TestFileHandle::fileName = getOutputDir()
  + u8"TestFileHandle-\U00004f60\U0000597d.txt";
const std::string TestFileHandle::fileContent = u8"This is\na test file";



TestFileHandle::TestFileHandle()
{
  file_handle f(fileName, file_open_mode::write, file_type::binary);
  fwrite(fileContent.data(), sizeof(char), fileContent.size(), f);
}



TestFileHandle::~TestFileHandle()
{
  if(check_dir(fileName))
  {
    remove_dir(fileName);
  }
}

}



TEST_F(TestFileHandle, PathConstructor)
{
  file_handle f(fileName, file_open_mode::read, file_type::binary);
  EXPECT_NE(nullptr, static_cast<FILE*>(f));
}



TEST_F(TestFileHandleDeathTest, PathConstructorError)
{
  std::string invalidFileName = u8"InvalidFileName.txt";
  HOU_EXPECT_ERROR(file_handle f(invalidFileName, file_open_mode::read
    , file_type::binary), std::runtime_error
    , format_string(get_text(sys_error::file_open), invalidFileName.c_str()));
}



TEST_F(TestFileHandle, MoveConstructor)
{
  file_handle fDummy(fileName, file_open_mode::read, file_type::binary);
  FILE* fileRef = static_cast<FILE*>(fDummy);
  file_handle f(std::move(fDummy));
  EXPECT_EQ(fileRef, static_cast<FILE*>(f));
  EXPECT_EQ(nullptr, static_cast<FILE*>(fDummy));
}



TEST_F(TestFileHandle, get_file_mode_string)
{
  EXPECT_EQ("r", get_file_mode_string(file_open_mode::read, file_type::text));
  EXPECT_EQ("w", get_file_mode_string(file_open_mode::write, file_type::text));
  EXPECT_EQ("a", get_file_mode_string(file_open_mode::append, file_type::text));
  EXPECT_EQ("rb", get_file_mode_string(file_open_mode::read, file_type::binary));
  EXPECT_EQ("wb", get_file_mode_string(file_open_mode::write, file_type::binary));
  EXPECT_EQ("ab", get_file_mode_string(file_open_mode::append, file_type::binary));
}



TEST_F(TestFileHandle, OpenFile)
{
  FILE* f = open_file(fileName, "rb");
  EXPECT_NE(nullptr, f);
  fclose(f);
}



TEST_F(TestFileHandle, CheckDir)
{
  EXPECT_TRUE(check_dir(fileName));
  EXPECT_TRUE(check_dir(getOutputDir()));
  EXPECT_FALSE(check_dir(u8"DummyName"));
  EXPECT_FALSE(check_dir(u8"./DummyDir/"));
}



TEST_F(TestFileHandle, RenameDir)
{
  const std::string newName = getOutputDir()
    + u8"TestFileHandle-\U00004f61\U0000597e-2.txt";

  EXPECT_TRUE(check_dir(fileName));
  EXPECT_FALSE(check_dir(newName));

  EXPECT_TRUE(rename_dir(fileName, newName));
  EXPECT_FALSE(check_dir(fileName));
  EXPECT_TRUE(check_dir(newName));

  EXPECT_TRUE(rename_dir(newName, fileName));
  EXPECT_TRUE(check_dir(fileName));
  EXPECT_FALSE(check_dir(newName));

  // Just for safety reason... If the test fails and the file does not get
  // renamed back, it will not be cleaned up at the end of the test.
  if(check_dir(newName))
  {
    remove_dir(newName);
  }
}



TEST_F(TestFileHandle, RenameInvalidDir)
{
  EXPECT_FALSE(rename_dir(u8"notaValidFile.txt", u8"someOtherFile.txt"));
}



TEST_F(TestFileHandle, RemoveDir)
{
  const std::string newName = getOutputDir()
    + u8"TestFileHandle-\U00004f61\U0000597e-2.txt";
  const std::string toWrite = u8"I have\nwritten this";

  EXPECT_FALSE(check_dir(newName));

  {
    file_handle f(newName, file_open_mode::write, file_type::binary);
    fwrite(toWrite.data(), sizeof(char), toWrite.size(), f);
  }

  {
    file_handle f(newName, file_open_mode::read, file_type::binary);
    EXPECT_NE(nullptr, static_cast<FILE*>(f));
  }

  EXPECT_TRUE(check_dir(newName));
  EXPECT_TRUE(remove_dir(newName));
  EXPECT_FALSE(check_dir(newName));
}



TEST_F(TestFileHandle, RemoveInvalidDir)
{
  EXPECT_FALSE(remove_dir("notaValidFile.txt"));
}



TEST_F(TestFileHandle, GetDirByteSize)
{
  EXPECT_EQ(fileContent.size(), get_dir_byte_size(fileName));
}



TEST_F(TestFileHandle, GetInvalidDirByteSize)
{
  EXPECT_EQ(std::numeric_limits<size_t>::max(), get_dir_byte_size("invalid.txt"));
}



TEST_F(TestFileHandle, GetFilenameExtension)
{
  EXPECT_EQ(u8"", get_filename_extension(u8""));
  EXPECT_EQ(u8"", get_filename_extension(u8"fileWithoutExtension"));
  EXPECT_EQ(u8"txt", get_filename_extension(u8"fileWithExtension.txt"));
  EXPECT_EQ(u8"txt2", get_filename_extension(u8"filename.with.points.txt2"));
  EXPECT_EQ(u8"txt", get_filename_extension(u8".hiddenFile.txt"));
}



TEST_F(TestFileHandle, GetFileDescriptor)
{
  file_handle fh(fileName, file_open_mode::read, file_type::binary);
  EXPECT_GE(get_file_descriptor(fh), 0);
}



TEST_F(TestFileHandle, GetFileByteSize)
{
  file_handle fh(fileName, file_open_mode::read, file_type::binary);
  EXPECT_EQ(fileContent.size(), get_file_byte_size(get_file_descriptor(fh)));
}



TEST_F(TestFileHandle, GetInvalidFileByteSize)
{
  EXPECT_EQ(std::numeric_limits<size_t>::max(), get_file_byte_size(-1));
}

