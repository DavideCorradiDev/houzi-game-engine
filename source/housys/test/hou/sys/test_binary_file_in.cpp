// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/cor/span.hpp"

#include "hou/sys/binary_file_in.hpp"
#include "hou/sys/sys_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_binary_file_in : public Test
{
public:
  static void SetUpTestCase();
  static void TearDownTestCase();

public:
  static const std::string filename;
  static const std::vector<uint8_t> file_content;
};



class test_binary_file_in_death_test : public test_binary_file_in
{};



void test_binary_file_in::SetUpTestCase()
{
  file f(filename, file_open_mode::write, file_type::binary);
  f.write(file_content.data(), file_content.size());
}



void test_binary_file_in::TearDownTestCase()
{
  remove_dir(filename);
}



const std::string test_binary_file_in::filename
  = get_output_dir() + u8"test_binary_file_in-\U00004f60\U0000597d.txt";
const std::vector<uint8_t> test_binary_file_in::file_content
  = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

}  // namespace



TEST_F(test_binary_file_in, path_constructor)
{
  binary_file_in fi(filename);
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(file_content.size(), fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(0, fi.get_byte_pos());
  std::vector<uint8_t> buffer(file_content.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, file_content);
}



TEST_F(test_binary_file_in_death_test, path_constructor_failure)
{
  std::string invalid_filename = u8"InvalidFileName";
  EXPECT_ERROR_N(
    binary_file_in fi(invalid_filename), file_open_error, invalid_filename);
}



TEST_F(test_binary_file_in, move_constructor)
{
  binary_file_in fi_dummy(filename);
  binary_file_in fi(std::move(fi_dummy));
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(file_content.size(), fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(0, fi.get_byte_pos());
  std::vector<uint8_t> buffer(file_content.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, file_content);
}



TEST_F(test_binary_file_in, set_byte_pos)
{
  binary_file_in fi(filename);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(3);
  EXPECT_EQ(3, fi.get_byte_pos());
  fi.set_byte_pos(0);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.set_byte_pos(
    static_cast<binary_file_in::byte_position>(fi.get_byte_count()));
  EXPECT_EQ(static_cast<binary_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  fi.set_byte_pos(
    static_cast<binary_file_in::byte_position>(fi.get_byte_count() + 6));
  EXPECT_EQ(static_cast<binary_file_in::byte_position>(fi.get_byte_count() + 6),
    fi.get_byte_pos());
}



TEST_F(test_binary_file_in_death_test, set_byte_pos_error)
{
  binary_file_in fi(filename);
  EXPECT_ERROR_0(fi.set_byte_pos(-1), cursor_error);
}



TEST_F(test_binary_file_in, move_byte_pos)
{
  binary_file_in fi(filename);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(3);
  EXPECT_EQ(3, fi.get_byte_pos());
  fi.move_byte_pos(-2);
  EXPECT_EQ(1, fi.get_byte_pos());
  fi.move_byte_pos(-1);
  EXPECT_EQ(0, fi.get_byte_pos());
  fi.move_byte_pos(
    static_cast<binary_file_in::byte_position>(fi.get_byte_count()));
  EXPECT_EQ(static_cast<binary_file_in::byte_position>(fi.get_byte_count()),
    fi.get_byte_pos());
  fi.move_byte_pos(6);
  EXPECT_EQ(static_cast<binary_file_in::byte_position>(fi.get_byte_count() + 6),
    fi.get_byte_pos());
}



TEST_F(test_binary_file_in_death_test, move_byte_pos_error)
{
  binary_file_in fi(filename);
  EXPECT_ERROR_0(fi.move_byte_pos(-1), cursor_error);
}



TEST_F(test_binary_file_in, read_to_variable)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type);

  binary_file_in fi(filename);
  buffer_type buffer;

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(1u, fi.get_read_element_count());
  EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(&buffer), file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(1u, fi.get_read_element_count());
  const uint8_t* offset_data = file_content.data() + buffer_byte_size;
  EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(&buffer), offset_data, buffer_byte_size);
}



TEST_F(test_binary_file_in, read_to_basic_array)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  binary_file_in fi(filename);
  buffer_type buffer[buffer_size];

  fi.read(buffer, buffer_size);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(buffer), file_content.data(), buffer_byte_size);

  fi.read(buffer, buffer_size);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const uint8_t* offset_data = file_content.data() + buffer_byte_size;
  EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(buffer), offset_data, buffer_byte_size);
}



TEST_F(test_binary_file_in, read_to_array)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  binary_file_in fi(filename);
  std::array<buffer_type, buffer_size> buffer = {0, 0, 0};

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data()),
    file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const uint8_t* offset_data = file_content.data() + buffer_byte_size;
  EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(buffer.data()), offset_data, buffer_byte_size);
}



TEST_F(test_binary_file_in, read_to_vector)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  binary_file_in fi(filename);
  std::vector<buffer_type> buffer(buffer_size, 0u);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data()),
    file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const uint8_t* offset_data = file_content.data() + buffer_byte_size;
  EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(buffer.data()), offset_data, buffer_byte_size);
}



TEST_F(test_binary_file_in, read_to_string)
{
  using buffer_type = std::string::value_type;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  binary_file_in fi(filename);
  std::string buffer(buffer_size, 0);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_ARRAY_EQ(reinterpret_cast<const uint8_t*>(buffer.data()),
    file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const uint8_t* offset_data = file_content.data() + buffer_byte_size;
  EXPECT_ARRAY_EQ(reinterpret_cast<const uint8_t*>(buffer.data()), offset_data,
    buffer_byte_size);
}



TEST_F(test_binary_file_in, read_to_span)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  binary_file_in fi(filename);
  std::vector<buffer_type> vec(buffer_size, 0u);
  span<buffer_type> buffer(vec);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data()),
    file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const uint8_t* offset_data = file_content.data() + buffer_byte_size;
  EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(buffer.data()), offset_data, buffer_byte_size);
}



TEST_F(test_binary_file_in, read_all_to_vector)
{
  binary_file_in fi(filename);
  auto fi_content = fi.read_all<std::vector<uint8_t>>();

  EXPECT_EQ(file_content, fi_content);
  EXPECT_EQ(file_content.size(), fi.get_read_byte_count());
  EXPECT_EQ(file_content.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(test_binary_file_in, read_all_to_vector_not_from_start)
{
  binary_file_in fi(filename);
  fi.set_byte_pos(2u);
  auto fi_content = fi.read_all<std::vector<uint8_t>>();

  EXPECT_EQ(file_content, fi_content);
  EXPECT_EQ(file_content.size(), fi.get_read_byte_count());
  EXPECT_EQ(file_content.size(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(test_binary_file_in, eof)
{
  binary_file_in fi(filename);
  uint count = 0;
  while(!fi.eof())
  {
    uint8_t buffer;
    fi.read(buffer);
    ++count;
  }
  EXPECT_EQ(fi.get_byte_count() + 1u, count);
}
