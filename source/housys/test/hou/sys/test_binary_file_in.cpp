// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/cor/span.hpp"

#include "hou/sys/binary_file_in.hpp"
#include "hou/sys/sys_error.hpp"

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
  file f(fileName, file_open_mode::write, file_type::binary);
  f.write(fileContent.data(), fileContent.size());
}



void TestBinaryFileIn::TearDownTestCase()
{
  remove_dir(fileName);
}



const std::string TestBinaryFileIn::fileName = getOutputDir()
  + u8"TestBinaryFileIn-\U00004f60\U0000597d.txt";
const std::vector<uint8_t> TestBinaryFileIn::fileContent
  = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

}



TEST_F(TestBinaryFileIn, PathConstructor)
{
  binary_file_in fi(fileName);
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(fileContent.size(), fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(0, fi.get_byte_pos());
  std::vector<uint8_t> buffer(fileContent.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, fileContent);
}



TEST_F(TestBinaryFileInDeathTest, PathConstructorFailure)
{
  std::string invalidFileName = u8"InvalidFileName";
  HOU_EXPECT_ERROR(binary_file_in fi(invalidFileName), std::runtime_error
    , format_string(get_text(sys_error::file_open), invalidFileName.c_str()));
}



TEST_F(TestBinaryFileIn, MoveConstructor)
{
  binary_file_in fiDummy(fileName);
  binary_file_in fi(std::move(fiDummy));
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(fileContent.size(), fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(0, fi.get_byte_pos());
  std::vector<uint8_t> buffer(fileContent.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, fileContent);
}



TEST_F(TestBinaryFileIn, SetBytePos)
{
  binary_file_in fi(fileName);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(3);
  EXPECT_EQ(3, fi.get_byte_pos());
  fi.set_byte_pos(0);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(fi.get_byte_count());
  EXPECT_EQ(static_cast<binary_file_in::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
  fi.set_byte_pos(fi.get_byte_count() + 6);
  EXPECT_EQ(static_cast<binary_file_in::byte_position>(fi.get_byte_count() + 6)
    , fi.get_byte_pos());
}



TEST_F(TestBinaryFileInDeathTest, SetBytePosError)
{
  binary_file_in fi(fileName);
  HOU_EXPECT_ERROR(fi.set_byte_pos(-1), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestBinaryFileIn, MoveBytePos)
{
  binary_file_in fi(fileName);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(3);
  EXPECT_EQ(3, fi.get_byte_pos());
  fi.move_byte_pos(-2);
  EXPECT_EQ(1, fi.get_byte_pos());
  fi.move_byte_pos(-1);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(fi.get_byte_count());
  EXPECT_EQ(static_cast<binary_file_in::byte_position>(fi.get_byte_count())
    , fi.get_byte_pos());
  fi.move_byte_pos(6);
  EXPECT_EQ(static_cast<binary_file_in::byte_position>(fi.get_byte_count() + 6)
    , fi.get_byte_pos());
}



TEST_F(TestBinaryFileInDeathTest, MoveBytePosError)
{
  binary_file_in fi(fileName);
  HOU_EXPECT_ERROR(fi.move_byte_pos(-1), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestBinaryFileIn, ReadToVariable)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferByteSize = sizeof(BufferType);

  binary_file_in fi(fileName);
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
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(&buffer), offsetData
    , bufferByteSize);
}



TEST_F(TestBinaryFileIn, ReadToBasicArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  binary_file_in fi(fileName);
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
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer), offsetData
    , bufferByteSize);
}



TEST_F(TestBinaryFileIn, ReadToArray)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  binary_file_in fi(fileName);
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



TEST_F(TestBinaryFileIn, ReadToVector)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  binary_file_in fi(fileName);
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



TEST_F(TestBinaryFileIn, ReadToString)
{
  using BufferType = std::string::value_type;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  binary_file_in fi(fileName);
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



TEST_F(TestBinaryFileIn, ReadToSpan)
{
  using BufferType = uint16_t;
  static constexpr size_t bufferSize = 3u;
  static constexpr size_t bufferByteSize = sizeof(BufferType) * bufferSize;

  binary_file_in fi(fileName);
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



TEST_F(TestBinaryFileIn, ReadAllToVector)
{
  binary_file_in fi(fileName);
  auto fiContent = fi.read_all<std::vector<uint8_t>>();

  EXPECT_EQ(fileContent, fiContent);
  EXPECT_EQ(fileContent.size(), fi.get_read_byte_count());
  EXPECT_EQ(fileContent.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(TestBinaryFileIn, ReadAllToVectorNotFromStart)
{
  binary_file_in fi(fileName);
  fi.set_byte_pos(2u);
  auto fiContent = fi.read_all<std::vector<uint8_t>>();

  EXPECT_EQ(fileContent, fiContent);
  EXPECT_EQ(fileContent.size(), fi.get_read_byte_count());
  EXPECT_EQ(fileContent.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(TestBinaryFileIn, Eof)
{
  binary_file_in fi(fileName);
  uint count = 0;
  while(!fi.eof())
  {
    uint8_t buffer;
    fi.read(buffer);
    ++count;
  }
  EXPECT_EQ(fi.get_byte_count() + 1u, count);
}

