// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/sys/TestData.hpp"

#include "hou/cor/Span.hpp"

#include "hou/sys/TextFileIn.hpp"
#include "hou/sys/TextFileOut.hpp"
#include "hou/sys/SysError.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestTextFileOut
  : public Test
{
public:
  static const std::string fileName;

public:
  TestTextFileOut();
  ~TestTextFileOut();
};



class TestTextFileOutDeathTest : public TestTextFileOut {};



TestTextFileOut::TestTextFileOut()
{
  TextFileOut fo(fileName);
}



TestTextFileOut::~TestTextFileOut()
{
  removeDir(fileName);
}



const std::string TestTextFileOut::fileName = getOutputDir()
  + u8"TestTextFileOut-\U00004f60\U0000597d.txt";

}



TEST_F(TestTextFileOut, PathConstructor)
{
  TextFileOut fo(fileName);
  EXPECT_FALSE(fo.eof());
  EXPECT_FALSE(fo.error());
  EXPECT_EQ(0u, fo.getByteCount());
  EXPECT_EQ(0u, fo.getWriteByteCount());
  EXPECT_EQ(0u, fo.getWriteElementCount());
  EXPECT_EQ(TextFileOut::TextPosition::Start, fo.getTextPos());
}



TEST_F(TestTextFileOut, MoveConstructor)
{
  TextFileOut foDummy(fileName);
  TextFileOut fo(std::move(foDummy));
  EXPECT_FALSE(fo.eof());
  EXPECT_FALSE(fo.error());
  EXPECT_EQ(0u, fo.getByteCount());
  EXPECT_EQ(0u, fo.getWriteByteCount());
  EXPECT_EQ(0u, fo.getWriteElementCount());
  EXPECT_EQ(TextFileOut::TextPosition::Start, fo.getTextPos());
}



TEST_F(TestTextFileOut, SetTextPos)
{
  TextFileOut fi(fileName);
  std::string buffer = "ab";
  EXPECT_EQ(TextFileOut::TextPosition::Start, fi.getTextPos());
  fi.write(buffer);
  TextFileOut::TextPosition posRef = fi.getTextPos();
  EXPECT_NE(TextFileOut::TextPosition::Start, posRef);
  fi.setTextPos(TextFileOut::TextPosition::Start);
  EXPECT_EQ(TextFileOut::TextPosition::Start, fi.getTextPos());
  fi.setTextPos(posRef);
  EXPECT_EQ(posRef, fi.getTextPos());
}



TEST_F(TestTextFileOut, WriteVariable)
{
  using BufferType = uint16_t;
  static constexpr size_t byteCount = sizeof(BufferType);

  BufferType bufOut = 3u;

  {
    TextFileOut fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.getWriteByteCount());
    EXPECT_EQ(1u, fo.getWriteElementCount());
  }

  TextFileIn fi(fileName);
  BufferType bufIn;
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.getByteCount());
  EXPECT_EQ(byteCount, fi.getReadByteCount());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestTextFileOut, WriteBasicArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  BufferType bufOut[bufferSize] = {1u, 2u, 3u};

  {
    TextFileOut fo(fileName);
    fo.write(bufOut, bufferSize);
    EXPECT_EQ(byteCount, fo.getWriteByteCount());
    EXPECT_EQ(bufferSize, fo.getWriteElementCount());
  }

  TextFileIn fi(fileName);
  BufferType bufIn[bufferSize];
  fi.read(bufIn, bufferSize);
  EXPECT_EQ(byteCount, fi.getByteCount());
  EXPECT_EQ(byteCount, fi.getReadByteCount());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(bufIn)
    , reinterpret_cast<uint8_t*>(bufOut), byteCount);
}



TEST_F(TestTextFileOut, WriteArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::array<BufferType, bufferSize> bufOut = {1u, 2u, 3u};

  {
    TextFileOut fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.getWriteByteCount());
    EXPECT_EQ(bufferSize, fo.getWriteElementCount());
  }

  TextFileIn fi(fileName);
  std::array<BufferType, bufferSize> bufIn;
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.getByteCount());
  EXPECT_EQ(byteCount, fi.getReadByteCount());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestTextFileOut, WriteVector)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::vector<BufferType> bufOut = {1u, 2u, 3u};

  {
    TextFileOut fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.getWriteByteCount());
    EXPECT_EQ(bufferSize, fo.getWriteElementCount());
  }

  TextFileIn fi(fileName);
  std::vector<BufferType> bufIn(3u, 0u);
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.getByteCount());
  EXPECT_EQ(byteCount, fi.getReadByteCount());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestTextFileOut, WriteString)
{
  using BufferType = std::string::value_type;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::string bufOut = "abc";

  {
    TextFileOut fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.getWriteByteCount());
    EXPECT_EQ(bufferSize, fo.getWriteElementCount());
  }

  TextFileIn fi(fileName);
  std::string bufIn(3u, 'a');
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.getByteCount());
  EXPECT_EQ(byteCount, fi.getReadByteCount());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestTextFileOut, WriteSpan)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::vector<BufferType> vecOut = {1u, 2u, 3u};
  Span<BufferType> bufOut(vecOut);

  {
    TextFileOut fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.getWriteByteCount());
    EXPECT_EQ(bufferSize, fo.getWriteElementCount());
  }

  TextFileIn fi(fileName);
  std::vector<BufferType> vecIn(3u, 0u);
  Span<BufferType> bufIn(vecIn);
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.getByteCount());
  EXPECT_EQ(byteCount, fi.getReadByteCount());
  EXPECT_EQ(vecOut, vecIn);
}

