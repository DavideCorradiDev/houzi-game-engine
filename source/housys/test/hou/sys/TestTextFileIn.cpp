// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/TestData.hpp"

#include "hou/cor/span.hpp"

#include "hou/sys/text_file_in.hpp"
#include "hou/sys/sys_error.hpp"

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
  file f(fileName, file_open_mode::write, file_type::binary);
  f.write(fileContent.data(), fileContent.size());
}



void TestTextFileIn::TearDownTestCase()
{
  remove_dir(fileName);
}



const std::string TestTextFileIn::fileName = getOutputDir()
  + u8"TestTextFileIn-\U00004f60\U0000597d.txt";
const std::vector<uint8_t> TestTextFileIn::fileContent
  = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

}



TEST_F(TestTextFileIn, PathConstructor)
{
  text_file_in fi(fileName);
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(fileContent.size(), fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  std::vector<uint8_t> buffer(fileContent.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, fileContent);
}



TEST_F(TestTextFileInDeathTest, PathConstructorFailure)
{
  std::string invalidFileName = u8"InvalidFileName";
  HOU_EXPECT_ERROR(text_file_in fi(invalidFileName), std::runtime_error
    , format_string(get_text(sys_error::file_open), invalidFileName.c_str()));
}



TEST_F(TestTextFileIn, MoveConstructor)
{
  text_file_in fiDummy(fileName);
  text_file_in fi(std::move(fiDummy));
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(fileContent.size(), fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  std::vector<uint8_t> buffer(fileContent.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, fileContent);
}



TEST_F(TestTextFileIn, SetTextPos)
{
  text_file_in fi(fileName);
  std::string buffer(2, 0);
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  fi.read(buffer);
  text_file_in::text_position posRef = fi.get_text_pos();
  EXPECT_NE(text_file_in::text_position::start, posRef);
  fi.set_text_pos(text_file_in::text_position::start);
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  fi.set_text_pos(posRef);
  EXPECT_EQ(posRef, fi.get_text_pos());
}



TEST_F(TestTextFileIn, ReadToVariable)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferByteSize = sizeof(BufferType);

  text_file_in fi(fileName);
  BufferType buffer;

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(1u, fi.get_read_element_count());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(&buffer), fileContent.data()
    , bufferByteSize);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(1u, fi.get_read_element_count());
  const uint8_t* offsetData = fileContent.data() + bufferByteSize;
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(&buffer), offsetData, bufferByteSize);
}



TEST_F(TestTextFileIn, ReadToBasicArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  text_file_in fi(fileName);
  BufferType buffer[bufferSize];

  fi.read(buffer, bufferSize);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer), fileContent.data()
    , bufferByteSize);

  fi.read(buffer, bufferSize);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  const uint8_t* offsetData = fileContent.data() + bufferByteSize;
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer), offsetData, bufferByteSize);
}



TEST_F(TestTextFileIn, ReadToArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  text_file_in fi(fileName);
  std::array<BufferType, bufferSize> buffer = {0, 0, 0};

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data())
    , fileContent.data(), bufferByteSize);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  const uint8_t* offsetData = fileContent.data() + bufferByteSize;
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data()), offsetData
    , bufferByteSize);
}



TEST_F(TestTextFileIn, ReadToVector)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  text_file_in fi(fileName);
  std::vector<BufferType> buffer(bufferSize, 0u);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data())
    , fileContent.data(), bufferByteSize);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  const uint8_t* offsetData = fileContent.data() + bufferByteSize;
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data()), offsetData
    , bufferByteSize);
}



TEST_F(TestTextFileIn, ReadToString)
{
  using BufferType = std::string::value_type;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  text_file_in fi(fileName);
  std::string buffer(bufferSize, 0);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<const uint8_t*>(buffer.data())
    , fileContent.data(), bufferByteSize);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  const uint8_t* offsetData = fileContent.data() + bufferByteSize;
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<const uint8_t*>(buffer.data()), offsetData
    , bufferByteSize);
}



TEST_F(TestTextFileIn, ReadToSpan)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  text_file_in fi(fileName);
  std::vector<BufferType> vec(bufferSize, 0u);
  span<BufferType> buffer(vec);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data())
    , fileContent.data(), bufferByteSize);

  fi.read(buffer);
  EXPECT_EQ(bufferByteSize, fi.get_read_byte_count());
  EXPECT_EQ(bufferSize, fi.get_read_element_count());
  const uint8_t* offsetData = fileContent.data() + bufferByteSize;
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data()), offsetData
    , bufferByteSize);
}



TEST_F(TestTextFileIn, ReadAllToVector)
{
  text_file_in fi(fileName);
  auto fiContent = fi.read_all<std::vector<uint8_t>>();

  EXPECT_EQ(fileContent, fiContent);
  EXPECT_EQ(fileContent.size(), fi.get_read_byte_count());
}



TEST_F(TestTextFileIn, ReadAllToVectorNotFromStart)
{
  text_file_in fi(fileName);

  std::string buffer(2, 0);
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  fi.read(buffer);
  EXPECT_NE(text_file_in::text_position::start, fi.get_text_pos());

  auto fiContent = fi.read_all<std::vector<uint8_t>>();

  EXPECT_EQ(fileContent, fiContent);
  EXPECT_EQ(fileContent.size(), fi.get_read_byte_count());
}



TEST_F(TestTextFileIn, Eof)
{
  text_file_in fi(fileName);
  uint count = 0;
  while(!fi.eof())
  {
    uint8_t buffer;
    fi.read(buffer);
    ++count;
  }
  EXPECT_EQ(fi.get_byte_count() + 1u, count);
}

