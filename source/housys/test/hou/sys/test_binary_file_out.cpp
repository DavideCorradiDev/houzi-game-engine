// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/cor/span.hpp"

#include "hou/sys/binary_file_in.hpp"
#include "hou/sys/binary_file_out.hpp"
#include "hou/sys/sys_error.hpp"

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
  binary_file_out fo(fileName);
}



TestBinaryFileOut::~TestBinaryFileOut()
{
  remove_dir(fileName);
}



const std::string TestBinaryFileOut::fileName = getOutputDir()
  + u8"TestBinaryFileOut-\U00004f60\U0000597d.txt";

}



TEST_F(TestBinaryFileOut, FileNameConstructor)
{
  binary_file_out fo(fileName);
  EXPECT_FALSE(fo.eof());
  EXPECT_FALSE(fo.error());
  EXPECT_EQ(0u, fo.get_byte_count());
  EXPECT_EQ(0u, fo.get_write_byte_count());
  EXPECT_EQ(0u, fo.get_write_element_count());
  EXPECT_EQ(0, fo.get_byte_pos());
}



TEST_F(TestBinaryFileOut, MoveConstructor)
{
  binary_file_out foDummy(fileName);
  binary_file_out fo(std::move(foDummy));
  EXPECT_FALSE(fo.eof());
  EXPECT_FALSE(fo.error());
  EXPECT_EQ(0u, fo.get_byte_count());
  EXPECT_EQ(0u, fo.get_write_byte_count());
  EXPECT_EQ(0u, fo.get_write_element_count());
  EXPECT_EQ(0, fo.get_byte_pos());
}



TEST_F(TestBinaryFileOut, SetBytePos)
{
  binary_file_out fo(fileName);
  EXPECT_EQ(0, fo.get_byte_pos());
  fo.set_byte_pos(3);
  EXPECT_EQ(3, fo.get_byte_pos());
  fo.set_byte_pos(0);
  EXPECT_EQ(0, fo.get_byte_pos());
  fo.set_byte_pos(fo.get_byte_count());
  EXPECT_EQ(static_cast<binary_file_out::byte_position>(fo.get_byte_count())
    , fo.get_byte_pos());
  fo.set_byte_pos(fo.get_byte_count() + 6);
  EXPECT_EQ(static_cast<binary_file_out::byte_position>(fo.get_byte_count() + 6)
    , fo.get_byte_pos());
}



TEST_F(TestBinaryFileOutDeathTest, SetBytePosError)
{
  binary_file_out fo(fileName);
  HOU_EXPECT_ERROR(fo.set_byte_pos(-1), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestBinaryFileOut, MoveBytePos)
{
  binary_file_out fo(fileName);
  EXPECT_EQ(0, fo.get_byte_pos());
  fo.move_byte_pos(3);
  EXPECT_EQ(3, fo.get_byte_pos());
  fo.move_byte_pos(-2);
  EXPECT_EQ(1, fo.get_byte_pos());
  fo.move_byte_pos(-1);
  EXPECT_EQ(0, fo.get_byte_pos());
  fo.move_byte_pos(fo.get_byte_count());
  EXPECT_EQ(static_cast<binary_file_out::byte_position>(fo.get_byte_count())
    , fo.get_byte_pos());
  fo.move_byte_pos(6);
  EXPECT_EQ(static_cast<binary_file_out::byte_position>(fo.get_byte_count() + 6)
    , fo.get_byte_pos());
}



TEST_F(TestBinaryFileOutDeathTest, MoveBytePosError)
{
  binary_file_out fo(fileName);
  HOU_EXPECT_ERROR(fo.move_byte_pos(-1), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestBinaryFileOut, WriteVariable)
{
  using BufferType = uint16_t;
  static constexpr size_t byteCount = sizeof(BufferType);

  BufferType bufOut = 3u;

  {
    binary_file_out fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.get_write_byte_count());
    EXPECT_EQ(1u, fo.get_write_element_count());
  }

  binary_file_in fi(fileName);
  BufferType bufIn;
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.get_byte_count());
  EXPECT_EQ(byteCount, fi.get_read_byte_count());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestBinaryFileOut, WriteBasicArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  BufferType bufOut[bufferSize] = {1u, 2u, 3u};

  {
    binary_file_out fo(fileName);
    fo.write(bufOut, bufferSize);
    EXPECT_EQ(byteCount, fo.get_write_byte_count());
    EXPECT_EQ(bufferSize, fo.get_write_element_count());
  }

  binary_file_in fi(fileName);
  BufferType bufIn[bufferSize];
  fi.read(bufIn, bufferSize);
  EXPECT_EQ(byteCount, fi.get_byte_count());
  EXPECT_EQ(byteCount, fi.get_read_byte_count());
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
    binary_file_out fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.get_write_byte_count());
    EXPECT_EQ(bufferSize, fo.get_write_element_count());
  }

  binary_file_in fi(fileName);
  std::array<BufferType, bufferSize> bufIn;
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.get_byte_count());
  EXPECT_EQ(byteCount, fi.get_read_byte_count());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestBinaryFileOut, WriteVector)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::vector<BufferType> bufOut = {1u, 2u, 3u};

  {
    binary_file_out fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.get_write_byte_count());
    EXPECT_EQ(bufferSize, fo.get_write_element_count());
  }

  binary_file_in fi(fileName);
  std::vector<BufferType> bufIn(3u, 0u);
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.get_byte_count());
  EXPECT_EQ(byteCount, fi.get_read_byte_count());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestBinaryFileOut, WriteString)
{
  using BufferType = std::string::value_type;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::string bufOut = "abc";

  {
    binary_file_out fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.get_write_byte_count());
    EXPECT_EQ(bufferSize, fo.get_write_element_count());
  }

  binary_file_in fi(fileName);
  std::string bufIn(3u, 'a');
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.get_byte_count());
  EXPECT_EQ(byteCount, fi.get_read_byte_count());
  EXPECT_EQ(bufOut, bufIn);
}



TEST_F(TestBinaryFileOut, WriteSpan)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t byteCount = sizeof(BufferType) * bufferSize;

  std::vector<BufferType> vecOut = {1u, 2u, 3u};
  span<BufferType> bufOut(vecOut);

  {
    binary_file_out fo(fileName);
    fo.write(bufOut);
    EXPECT_EQ(byteCount, fo.get_write_byte_count());
    EXPECT_EQ(bufferSize, fo.get_write_element_count());
  }

  binary_file_in fi(fileName);
  std::vector<BufferType> vecIn(3u, 0u);
  span<BufferType> bufIn(vecIn);
  fi.read(bufIn);
  EXPECT_EQ(byteCount, fi.get_byte_count());
  EXPECT_EQ(byteCount, fi.get_read_byte_count());
  EXPECT_EQ(vecOut, vecIn);
}

