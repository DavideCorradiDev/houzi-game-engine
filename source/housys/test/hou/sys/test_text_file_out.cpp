// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/cor/span.hpp"

#include "hou/sys/text_file_in.hpp"
#include "hou/sys/text_file_out.hpp"
#include "hou/sys/sys_error.hpp"

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
  text_file_out fo(fileName);
}



TestTextFileOut::~TestTextFileOut()
{
  remove_dir(fileName);
}



const std::string TestTextFileOut::fileName = getOutputDir()
  + u8"TestTextFileOut-\U00004f60\U0000597d.txt";

}



TEST_F(TestTextFileOut, PathConstructor)
{
  text_file_out fo(fileName);
  EXPECT_FALSE(fo.eof());
  EXPECT_FALSE(fo.error());
  EXPECT_EQ(0u, fo.get_byte_count());
  EXPECT_EQ(0u, fo.get_write_byte_count());
  EXPECT_EQ(0u, fo.get_write_element_count());
  EXPECT_EQ(text_file_out::text_position::start, fo.get_text_pos());
}



TEST_F(TestTextFileOut, MoveConstructor)
{
  text_file_out foDummy(fileName);
  text_file_out fo(std::move(foDummy));
  EXPECT_FALSE(fo.eof());
  EXPECT_FALSE(fo.error());
  EXPECT_EQ(0u, fo.get_byte_count());
  EXPECT_EQ(0u, fo.get_write_byte_count());
  EXPECT_EQ(0u, fo.get_write_element_count());
  EXPECT_EQ(text_file_out::text_position::start, fo.get_text_pos());
}



TEST_F(TestTextFileOut, SetTextPos)
{
  text_file_out fi(fileName);
  std::string buffer = "ab";
  EXPECT_EQ(text_file_out::text_position::start, fi.get_text_pos());
  fi.write(buffer);
  text_file_out::text_position posRef = fi.get_text_pos();
  EXPECT_NE(text_file_out::text_position::start, posRef);
  fi.set_text_pos(text_file_out::text_position::start);
  EXPECT_EQ(text_file_out::text_position::start, fi.get_text_pos());
  fi.set_text_pos(posRef);
  EXPECT_EQ(posRef, fi.get_text_pos());
}



TEST_F(TestTextFileOut, WriteVariable)
{
  using BufferType = uint16_t;
  static constexpr size_t byteCount = sizeof(BufferType);

  BufferType bufOut = 3u;

  {
    text_file_out fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.get_write_byte_count());
    EXPECT_EQ(1u, fo.get_write_element_count());
  }

  text_file_in fi(fileName);
  BufferType bufIn;
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.get_byte_count());
  EXPECT_EQ(byteCount, fi.get_read_byte_count());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestTextFileOut, WriteBasicArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  BufferType bufOut[bufferSize] = {1u, 2u, 3u};

  {
    text_file_out fo(fileName);
    fo.write(bufOut, bufferSize);
    EXPECT_EQ(byteCount, fo.get_write_byte_count());
    EXPECT_EQ(bufferSize, fo.get_write_element_count());
  }

  text_file_in fi(fileName);
  BufferType bufIn[bufferSize];
  fi.read(bufIn, bufferSize);
  EXPECT_EQ(byteCount, fi.get_byte_count());
  EXPECT_EQ(byteCount, fi.get_read_byte_count());
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
    text_file_out fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.get_write_byte_count());
    EXPECT_EQ(bufferSize, fo.get_write_element_count());
  }

  text_file_in fi(fileName);
  std::array<BufferType, bufferSize> bufIn;
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.get_byte_count());
  EXPECT_EQ(byteCount, fi.get_read_byte_count());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestTextFileOut, WriteVector)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::vector<BufferType> bufOut = {1u, 2u, 3u};

  {
    text_file_out fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.get_write_byte_count());
    EXPECT_EQ(bufferSize, fo.get_write_element_count());
  }

  text_file_in fi(fileName);
  std::vector<BufferType> bufIn(3u, 0u);
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.get_byte_count());
  EXPECT_EQ(byteCount, fi.get_read_byte_count());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestTextFileOut, WriteString)
{
  using BufferType = std::string::value_type;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::string bufOut = "abc";

  {
    text_file_out fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.get_write_byte_count());
    EXPECT_EQ(bufferSize, fo.get_write_element_count());
  }

  text_file_in fi(fileName);
  std::string bufIn(3u, 'a');
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.get_byte_count());
  EXPECT_EQ(byteCount, fi.get_read_byte_count());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestTextFileOut, WriteSpan)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::vector<BufferType> vecOut = {1u, 2u, 3u};
  span<BufferType> bufOut(vecOut);

  {
    text_file_out fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.get_write_byte_count());
    EXPECT_EQ(bufferSize, fo.get_write_element_count());
  }

  text_file_in fi(fileName);
  std::vector<BufferType> vecIn(3u, 0u);
  span<BufferType> bufIn(vecIn);
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.get_byte_count());
  EXPECT_EQ(byteCount, fi.get_read_byte_count());
  EXPECT_EQ(vecOut, vecIn);
}

