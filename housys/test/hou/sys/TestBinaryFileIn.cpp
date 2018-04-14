// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/TestData.hpp"

#include "hou/cor/Span.hpp"

#include "hou/sys/BinaryFileIn.hpp"
#include "hou/sys/SysError.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestBinaryFileIn
  : public Test
{
public:
  static void SetUpTestCase();
  static void TearDownTestCase();

public:
  static const std::string fileName;
  static const std::vector<uint8_t> fileContent;
};



class TestBinaryFileInDeathTest : public TestBinaryFileIn {};



void TestBinaryFileIn::SetUpTestCase()
{
  File f(fileName, FileOpenMode::Write, FileType::Binary);
  f.write(fileContent.data(), fileContent.size());
}



void TestBinaryFileIn::TearDownTestCase()
{
  removeDir(fileName);
}



const std::string TestBinaryFileIn::fileName = getOutputDir()
  + u8"TestBinaryFileIn-\U00004f60\U0000597d.txt";
const std::vector<uint8_t> TestBinaryFileIn::fileContent
  = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

}



TEST_F(TestBinaryFileIn, PathConstructor)
{
  BinaryFileIn fi(fileName);
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(fileContent.size(), fi.getByteCount());
  EXPECT_EQ(0u, fi.getReadByteCount());
  EXPECT_EQ(0u, fi.getReadElementCount());
  EXPECT_EQ(0, fi.getBytePos());
  std::vector<uint8_t> buffer(fileContent.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, fileContent);
}



TEST_F(TestBinaryFileInDeathTest, PathConstructorFailure)
{
  std::string invalidFileName = u8"InvalidFileName";
  HOU_EXPECT_ERROR(BinaryFileIn fi(invalidFileName), std::runtime_error
    , formatString(getText(SysError::FileOpen), invalidFileName.c_str()));
}



TEST_F(TestBinaryFileIn, MoveConstructor)
{
  BinaryFileIn fiDummy(fileName);
  BinaryFileIn fi(std::move(fiDummy));
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(fileContent.size(), fi.getByteCount());
  EXPECT_EQ(0u, fi.getReadByteCount());
  EXPECT_EQ(0u, fi.getReadElementCount());
  EXPECT_EQ(0, fi.getBytePos());
  std::vector<uint8_t> buffer(fileContent.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, fileContent);
}



TEST_F(TestBinaryFileIn, SetBytePos)
{
  BinaryFileIn fi(fileName);
  EXPECT_EQ(0, fi.getBytePos());
  fi.setBytePos(3);
  EXPECT_EQ(3, fi.getBytePos());
  fi.setBytePos(0);
  EXPECT_EQ(0, fi.getBytePos());
  fi.setBytePos(fi.getByteCount());
  EXPECT_EQ(static_cast<BinaryFileIn::BytePosition>(fi.getByteCount())
    , fi.getBytePos());
  fi.setBytePos(fi.getByteCount() + 6);
  EXPECT_EQ(static_cast<BinaryFileIn::BytePosition>(fi.getByteCount() + 6)
    , fi.getBytePos());
}



TEST_F(TestBinaryFileInDeathTest, SetBytePosError)
{
  BinaryFileIn fi(fileName);
  HOU_EXPECT_ERROR(fi.setBytePos(-1), std::runtime_error
    , getText(SysError::FileSeek));
}



TEST_F(TestBinaryFileIn, MoveBytePos)
{
  BinaryFileIn fi(fileName);
  EXPECT_EQ(0, fi.getBytePos());
  fi.moveBytePos(3);
  EXPECT_EQ(3, fi.getBytePos());
  fi.moveBytePos(-2);
  EXPECT_EQ(1, fi.getBytePos());
  fi.moveBytePos(-1);
  EXPECT_EQ(0, fi.getBytePos());
  fi.moveBytePos(fi.getByteCount());
  EXPECT_EQ(static_cast<BinaryFileIn::BytePosition>(fi.getByteCount())
    , fi.getBytePos());
  fi.moveBytePos(6);
  EXPECT_EQ(static_cast<BinaryFileIn::BytePosition>(fi.getByteCount() + 6)
    , fi.getBytePos());
}



TEST_F(TestBinaryFileInDeathTest, MoveBytePosError)
{
  BinaryFileIn fi(fileName);
  HOU_EXPECT_ERROR(fi.moveBytePos(-1), std::runtime_error
    , getText(SysError::FileSeek));
}



TEST_F(TestBinaryFileIn, ReadToVariable)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferByteSize = sizeof(BufferType);

  BinaryFileIn fi(fileName);
  BufferType buffer;

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.getReadByteCount());
  EXPECT_EQ(1u, fi.getReadElementCount());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(&buffer), fileContent.data()
    , bufferByteSize);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.getReadByteCount());
  EXPECT_EQ(1u, fi.getReadElementCount());
  const uint8_t* offsetData = fileContent.data() + bufferByteSize;
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(&buffer), offsetData
    , bufferByteSize);
}



TEST_F(TestBinaryFileIn, ReadToBasicArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  BinaryFileIn fi(fileName);
  BufferType buffer[bufferSize];

  fi.read(buffer, bufferSize);
  EXPECT_EQ(bufferByteSize, fi.getReadByteCount());
  EXPECT_EQ(bufferSize, fi.getReadElementCount());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer), fileContent.data()
    , bufferByteSize);

  fi.read(buffer, bufferSize);
  EXPECT_EQ(bufferByteSize, fi.getReadByteCount());
  EXPECT_EQ(bufferSize, fi.getReadElementCount());
  const uint8_t* offsetData = fileContent.data() + bufferByteSize;
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer), offsetData
    , bufferByteSize);
}



TEST_F(TestBinaryFileIn, ReadToArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  BinaryFileIn fi(fileName);
  std::array<BufferType, bufferSize> buffer = {0, 0, 0};

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.getReadByteCount());
  EXPECT_EQ(bufferSize, fi.getReadElementCount());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data())
    , fileContent.data(), bufferByteSize);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.getReadByteCount());
  EXPECT_EQ(bufferSize, fi.getReadElementCount());
  const uint8_t* offsetData = fileContent.data() + bufferByteSize;
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data()), offsetData
    , bufferByteSize);
}



TEST_F(TestBinaryFileIn, ReadToVector)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  BinaryFileIn fi(fileName);
  std::vector<BufferType> buffer(bufferSize, 0u);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.getReadByteCount());
  EXPECT_EQ(bufferSize, fi.getReadElementCount());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data())
    , fileContent.data(), bufferByteSize);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.getReadByteCount());
  EXPECT_EQ(bufferSize, fi.getReadElementCount());
  const uint8_t* offsetData = fileContent.data() + bufferByteSize;
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data()), offsetData
    , bufferByteSize);
}



TEST_F(TestBinaryFileIn, ReadToString)
{
  using BufferType = std::string::value_type;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  BinaryFileIn fi(fileName);
  std::string buffer(bufferSize, 0);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.getReadByteCount());
  EXPECT_EQ(bufferSize, fi.getReadElementCount());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<const uint8_t*>(buffer.data())
    , fileContent.data(), bufferByteSize);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.getReadByteCount());
  EXPECT_EQ(bufferSize, fi.getReadElementCount());
  const uint8_t* offsetData = fileContent.data() + bufferByteSize;
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<const uint8_t*>(buffer.data()), offsetData
    , bufferByteSize);
}



TEST_F(TestBinaryFileIn, ReadToSpan)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  BinaryFileIn fi(fileName);
  std::vector<BufferType> vec(bufferSize, 0u);
  Span<BufferType> buffer(vec);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.getReadByteCount());
  EXPECT_EQ(bufferSize, fi.getReadElementCount());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data())
    , fileContent.data(), bufferByteSize);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.getReadByteCount());
  EXPECT_EQ(bufferSize, fi.getReadElementCount());
  const uint8_t* offsetData = fileContent.data() + bufferByteSize;
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data()), offsetData
    , bufferByteSize);
}



TEST_F(TestBinaryFileIn, Eof)
{
  BinaryFileIn fi(fileName);
  uint count = 0;
  while(!fi.eof())
  {
    uint8_t buffer;
    fi.read(buffer);
    ++count;
  }
  EXPECT_EQ(fi.getByteCount() + 1u, count);
}

