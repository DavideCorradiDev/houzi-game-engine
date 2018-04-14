// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/TestData.hpp"

#include "hou/cor/Span.hpp"

#include "hou/sys/TextFileIn.hpp"
#include "hou/sys/SysError.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestTextFileIn
  : public Test
{
public:
  static void SetUpTestCase();
  static void TearDownTestCase();

public:
  static const std::string fileName;
  static const std::vector<uint8_t> fileContent;
};



class TestTextFileInDeathTest : public TestTextFileIn {};



void TestTextFileIn::SetUpTestCase()
{
  File f(fileName, FileOpenMode::Write, FileType::Binary);
  f.write(fileContent.data(), fileContent.size());
}



void TestTextFileIn::TearDownTestCase()
{
  removeDir(fileName);
}



const std::string TestTextFileIn::fileName = getOutputDir()
  + u8"TestTextFileIn-\U00004f60\U0000597d.txt";
const std::vector<uint8_t> TestTextFileIn::fileContent
  = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

}



TEST_F(TestTextFileIn, PathConstructor)
{
  TextFileIn fi(fileName);
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(fileContent.size(), fi.getByteCount());
  EXPECT_EQ(0u, fi.getReadByteCount());
  EXPECT_EQ(0u, fi.getReadElementCount());
  EXPECT_EQ(TextFileIn::TextPosition::Start, fi.getTextPos());
  std::vector<uint8_t> buffer(fileContent.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, fileContent);
}



TEST_F(TestTextFileInDeathTest, PathConstructorFailure)
{
  std::string invalidFileName = u8"InvalidFileName";
  HOU_EXPECT_ERROR(TextFileIn fi(invalidFileName), std::runtime_error
    , formatString(getText(SysError::FileOpen), invalidFileName.c_str()));
}



TEST_F(TestTextFileIn, MoveConstructor)
{
  TextFileIn fiDummy(fileName);
  TextFileIn fi(std::move(fiDummy));
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(fileContent.size(), fi.getByteCount());
  EXPECT_EQ(0u, fi.getReadByteCount());
  EXPECT_EQ(0u, fi.getReadElementCount());
  EXPECT_EQ(TextFileIn::TextPosition::Start, fi.getTextPos());
  std::vector<uint8_t> buffer(fileContent.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, fileContent);
}



TEST_F(TestTextFileIn, SetTextPos)
{
  TextFileIn fi(fileName);
  std::string buffer(2, 0);
  EXPECT_EQ(TextFileIn::TextPosition::Start, fi.getTextPos());
  fi.read(buffer);
  TextFileIn::TextPosition posRef = fi.getTextPos();
  EXPECT_NE(TextFileIn::TextPosition::Start, posRef);
  fi.setTextPos(TextFileIn::TextPosition::Start);
  EXPECT_EQ(TextFileIn::TextPosition::Start, fi.getTextPos());
  fi.setTextPos(posRef);
  EXPECT_EQ(posRef, fi.getTextPos());
}



TEST_F(TestTextFileIn, ReadToVariable)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferByteSize = sizeof(BufferType);

  TextFileIn fi(fileName);
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
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(&buffer), offsetData, bufferByteSize);
}



TEST_F(TestTextFileIn, ReadToBasicArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  TextFileIn fi(fileName);
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
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer), offsetData, bufferByteSize);
}



TEST_F(TestTextFileIn, ReadToArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  TextFileIn fi(fileName);
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



TEST_F(TestTextFileIn, ReadToVector)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  TextFileIn fi(fileName);
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



TEST_F(TestTextFileIn, ReadToString)
{
  using BufferType = std::string::value_type;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  TextFileIn fi(fileName);
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



TEST_F(TestTextFileIn, ReadToSpan)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  TextFileIn fi(fileName);
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



TEST_F(TestTextFileIn, Eof)
{
  TextFileIn fi(fileName);
  uint count = 0;
  while(!fi.eof())
  {
    uint8_t buffer;
    fi.read(buffer);
    ++count;
  }
  EXPECT_EQ(fi.getByteCount() + 1u, count);
}

