// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/sys/TestData.hpp"

#include "hou/cor/Span.hpp"

#include "hou/sys/BinaryFileIn.hpp"
#include "hou/sys/BinaryFileOut.hpp"
#include "hou/sys/SysError.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestBinaryFileOut
  : public Test
{
public:
  static const std::string fileName;

public:
  TestBinaryFileOut();
  ~TestBinaryFileOut();
};



class TestBinaryFileOutDeathTest : public TestBinaryFileOut {};



TestBinaryFileOut::TestBinaryFileOut()
{
  BinaryFileOut fo(fileName);
}



TestBinaryFileOut::~TestBinaryFileOut()
{
  removeDir(fileName);
}



const std::string TestBinaryFileOut::fileName = getOutputDir()
  + u8"TestBinaryFileOut-\U00004f60\U0000597d.txt";

}



TEST_F(TestBinaryFileOut, FileNameConstructor)
{
  BinaryFileOut fo(fileName);
  EXPECT_FALSE(fo.eof());
  EXPECT_FALSE(fo.error());
  EXPECT_EQ(0u, fo.getByteCount());
  EXPECT_EQ(0u, fo.getWriteByteCount());
  EXPECT_EQ(0u, fo.getWriteElementCount());
  EXPECT_EQ(0, fo.getBytePos());
}



TEST_F(TestBinaryFileOut, MoveConstructor)
{
  BinaryFileOut foDummy(fileName);
  BinaryFileOut fo(std::move(foDummy));
  EXPECT_FALSE(fo.eof());
  EXPECT_FALSE(fo.error());
  EXPECT_EQ(0u, fo.getByteCount());
  EXPECT_EQ(0u, fo.getWriteByteCount());
  EXPECT_EQ(0u, fo.getWriteElementCount());
  EXPECT_EQ(0, fo.getBytePos());
}



TEST_F(TestBinaryFileOut, SetBytePos)
{
  BinaryFileOut fo(fileName);
  EXPECT_EQ(0, fo.getBytePos());
  fo.setBytePos(3);
  EXPECT_EQ(3, fo.getBytePos());
  fo.setBytePos(0);
  EXPECT_EQ(0, fo.getBytePos());
  fo.setBytePos(fo.getByteCount());
  EXPECT_EQ(static_cast<BinaryFileOut::BytePosition>(fo.getByteCount())
    , fo.getBytePos());
  fo.setBytePos(fo.getByteCount() + 6);
  EXPECT_EQ(static_cast<BinaryFileOut::BytePosition>(fo.getByteCount() + 6)
    , fo.getBytePos());
}



TEST_F(TestBinaryFileOutDeathTest, SetBytePosError)
{
  BinaryFileOut fo(fileName);
  HOU_EXPECT_ERROR(fo.setBytePos(-1), std::runtime_error
    , getText(SysError::FileSeek));
}



TEST_F(TestBinaryFileOut, MoveBytePos)
{
  BinaryFileOut fo(fileName);
  EXPECT_EQ(0, fo.getBytePos());
  fo.moveBytePos(3);
  EXPECT_EQ(3, fo.getBytePos());
  fo.moveBytePos(-2);
  EXPECT_EQ(1, fo.getBytePos());
  fo.moveBytePos(-1);
  EXPECT_EQ(0, fo.getBytePos());
  fo.moveBytePos(fo.getByteCount());
  EXPECT_EQ(static_cast<BinaryFileOut::BytePosition>(fo.getByteCount())
    , fo.getBytePos());
  fo.moveBytePos(6);
  EXPECT_EQ(static_cast<BinaryFileOut::BytePosition>(fo.getByteCount() + 6)
    , fo.getBytePos());
}



TEST_F(TestBinaryFileOutDeathTest, MoveBytePosError)
{
  BinaryFileOut fo(fileName);
  HOU_EXPECT_ERROR(fo.moveBytePos(-1), std::runtime_error
    , getText(SysError::FileSeek));
}



TEST_F(TestBinaryFileOut, WriteVariable)
{
  using BufferType = uint16_t;
  static constexpr size_t byteCount = sizeof(BufferType);

  BufferType bufOut = 3u;

  {
    BinaryFileOut fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.getWriteByteCount());
    EXPECT_EQ(1u, fo.getWriteElementCount());
  }

  BinaryFileIn fi(fileName);
  BufferType bufIn;
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.getByteCount());
  EXPECT_EQ(byteCount, fi.getReadByteCount());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestBinaryFileOut, WriteBasicArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  BufferType bufOut[bufferSize] = {1u, 2u, 3u};

  {
    BinaryFileOut fo(fileName);
    fo.write(bufOut, bufferSize);
    EXPECT_EQ(byteCount, fo.getWriteByteCount());
    EXPECT_EQ(bufferSize, fo.getWriteElementCount());
  }

  BinaryFileIn fi(fileName);
  BufferType bufIn[bufferSize];
  fi.read(bufIn, bufferSize);
  EXPECT_EQ(byteCount, fi.getByteCount());
  EXPECT_EQ(byteCount, fi.getReadByteCount());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(bufIn)
    , reinterpret_cast<uint8_t*>(bufOut), byteCount);
}



TEST_F(TestBinaryFileOut, WriteArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::array<BufferType, bufferSize> bufOut = {1u, 2u, 3u};

  {
    BinaryFileOut fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.getWriteByteCount());
    EXPECT_EQ(bufferSize, fo.getWriteElementCount());
  }

  BinaryFileIn fi(fileName);
  std::array<BufferType, bufferSize> bufIn;
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.getByteCount());
  EXPECT_EQ(byteCount, fi.getReadByteCount());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestBinaryFileOut, WriteVector)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::vector<BufferType> bufOut = {1u, 2u, 3u};

  {
    BinaryFileOut fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.getWriteByteCount());
    EXPECT_EQ(bufferSize, fo.getWriteElementCount());
  }

  BinaryFileIn fi(fileName);
  std::vector<BufferType> bufIn(3u, 0u);
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.getByteCount());
  EXPECT_EQ(byteCount, fi.getReadByteCount());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestBinaryFileOut, WriteString)
{
  using BufferType = std::string::value_type;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::string bufOut = "abc";

  {
    BinaryFileOut fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.getWriteByteCount());
    EXPECT_EQ(bufferSize, fo.getWriteElementCount());
  }

  BinaryFileIn fi(fileName);
  std::string bufIn(3u, 'a');
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.getByteCount());
  EXPECT_EQ(byteCount, fi.getReadByteCount());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestBinaryFileOut, WriteSpan)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::vector<BufferType> vecOut = {1u, 2u, 3u};
  Span<BufferType> bufOut(vecOut);

  {
    BinaryFileOut fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.getWriteByteCount());
    EXPECT_EQ(bufferSize, fo.getWriteElementCount());
  }

  BinaryFileIn fi(fileName);
  std::vector<BufferType> vecIn(3u, 0u);
  Span<BufferType> bufIn(vecIn);
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.getByteCount());
  EXPECT_EQ(byteCount, fi.getReadByteCount());
  EXPECT_EQ(vecOut, vecIn);
}

