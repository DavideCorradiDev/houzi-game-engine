// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/TestData.hpp"

#include "hou/sys/SysError.hpp"
#include "hou/sys/FileHandle.hpp"

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
  FileHandle f(fileName, FileOpenMode::Write, FileType::Binary);
  fwrite(fileContent.data(), sizeof(char), fileContent.size(), f);
}



TestFileHandle::~TestFileHandle()
{
  if(checkDir(fileName))
  {
    removeDir(fileName);
  }
}

}



TEST_F(TestFileHandle, PathConstructor)
{
  FileHandle f(fileName, FileOpenMode::Read, FileType::Binary);
  EXPECT_NE(nullptr, static_cast<FILE*>(f));
}



TEST_F(TestFileHandleDeathTest, PathConstructorError)
{
  std::string invalidFileName = u8"InvalidFileName.txt";
  HOU_EXPECT_ERROR(FileHandle f(invalidFileName, FileOpenMode::Read
    , FileType::Binary), std::runtime_error
    , formatString(getText(SysError::FileOpen), invalidFileName.c_str()));
}



TEST_F(TestFileHandle, MoveConstructor)
{
  FileHandle fDummy(fileName, FileOpenMode::Read, FileType::Binary);
  FILE* fileRef = static_cast<FILE*>(fDummy);
  FileHandle f(std::move(fDummy));
  EXPECT_EQ(fileRef, static_cast<FILE*>(f));
  EXPECT_EQ(nullptr, static_cast<FILE*>(fDummy));
}



TEST_F(TestFileHandle, getFileModeString)
{
  EXPECT_EQ("r", getFileModeString(FileOpenMode::Read, FileType::Text));
  EXPECT_EQ("w", getFileModeString(FileOpenMode::Write, FileType::Text));
  EXPECT_EQ("a", getFileModeString(FileOpenMode::Append, FileType::Text));
  EXPECT_EQ("rb", getFileModeString(FileOpenMode::Read, FileType::Binary));
  EXPECT_EQ("wb", getFileModeString(FileOpenMode::Write, FileType::Binary));
  EXPECT_EQ("ab", getFileModeString(FileOpenMode::Append, FileType::Binary));
}



TEST_F(TestFileHandle, OpenFile)
{
  FILE* f = openFile(fileName, "rb");
  EXPECT_NE(nullptr, f);
  fclose(f);
}



TEST_F(TestFileHandle, CheckDir)
{
  EXPECT_TRUE(checkDir(fileName));
  EXPECT_TRUE(checkDir(getOutputDir()));
  EXPECT_FALSE(checkDir(u8"DummyName"));
  EXPECT_FALSE(checkDir(u8"./DummyDir/"));
}



TEST_F(TestFileHandle, RenameDir)
{
  const std::string newName = getOutputDir()
    + u8"TestFileHandle-\U00004f61\U0000597e-2.txt";

  EXPECT_TRUE(checkDir(fileName));
  EXPECT_FALSE(checkDir(newName));

  EXPECT_TRUE(renameDir(fileName, newName));
  EXPECT_FALSE(checkDir(fileName));
  EXPECT_TRUE(checkDir(newName));

  EXPECT_TRUE(renameDir(newName, fileName));
  EXPECT_TRUE(checkDir(fileName));
  EXPECT_FALSE(checkDir(newName));

  // Just for safety reason... If the test fails and the file does not get
  // renamed back, it will not be cleaned up at the end of the test.
  if(checkDir(newName))
  {
    removeDir(newName);
  }
}



TEST_F(TestFileHandle, RenameInvalidDir)
{
  EXPECT_FALSE(renameDir(u8"notaValidFile.txt", u8"someOtherFile.txt"));
}



TEST_F(TestFileHandle, RemoveDir)
{
  const std::string newName = getOutputDir()
    + u8"TestFileHandle-\U00004f61\U0000597e-2.txt";
  const std::string toWrite = u8"I have\nwritten this";

  EXPECT_FALSE(checkDir(newName));

  {
    FileHandle f(newName, FileOpenMode::Write, FileType::Binary);
    fwrite(toWrite.data(), sizeof(char), toWrite.size(), f);
  }

  {
    FileHandle f(newName, FileOpenMode::Read, FileType::Binary);
    EXPECT_NE(nullptr, static_cast<FILE*>(f));
  }

  EXPECT_TRUE(checkDir(newName));
  EXPECT_TRUE(removeDir(newName));
  EXPECT_FALSE(checkDir(newName));
}



TEST_F(TestFileHandle, RemoveInvalidDir)
{
  EXPECT_FALSE(removeDir("notaValidFile.txt"));
}



TEST_F(TestFileHandle, GetDirByteSize)
{
  EXPECT_EQ(fileContent.size(), getDirByteSize(fileName));
}



TEST_F(TestFileHandle, GetInvalidDirByteSize)
{
  EXPECT_EQ(std::numeric_limits<size_t>::max(), getDirByteSize("invalid.txt"));
}



TEST_F(TestFileHandle, GetFilenameExtension)
{
  EXPECT_EQ(u8"", getFilenameExtension(u8""));
  EXPECT_EQ(u8"", getFilenameExtension(u8"fileWithoutExtension"));
  EXPECT_EQ(u8"txt", getFilenameExtension(u8"fileWithExtension.txt"));
  EXPECT_EQ(u8"txt2", getFilenameExtension(u8"filename.with.points.txt2"));
  EXPECT_EQ(u8"txt", getFilenameExtension(u8".hiddenFile.txt"));
}



TEST_F(TestFileHandle, GetFileDescriptor)
{
  FileHandle fh(fileName, FileOpenMode::Read, FileType::Binary);
  EXPECT_GE(getFileDescriptor(fh), 0);
}



TEST_F(TestFileHandle, GetFileByteSize)
{
  FileHandle fh(fileName, FileOpenMode::Read, FileType::Binary);
  EXPECT_EQ(fileContent.size(), getFileByteSize(getFileDescriptor(fh)));
}



TEST_F(TestFileHandle, GetInvalidFileByteSize)
{
  EXPECT_EQ(std::numeric_limits<size_t>::max(), getFileByteSize(-1));
}

