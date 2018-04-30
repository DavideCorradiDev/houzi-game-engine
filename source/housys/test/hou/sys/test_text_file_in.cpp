// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/cor/span.hpp"

#include "hou/sys/sys_error.hpp"
#include "hou/sys/text_file_in.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_text_file_in : public Test
{
public:
  static void SetUpTestCase();
  static void TearDownTestCase();

public:
  static const std::string filename;
  static const std::vector<uint8_t> file_content;
};



class test_text_file_in_death_test : public test_text_file_in
{};



void test_text_file_in::SetUpTestCase()
{
  file f(filename, file_open_mode::write, file_type::binary);
  f.write(file_content.data(), file_content.size());
}



void test_text_file_in::TearDownTestCase()
{
  remove_dir(filename);
}



const std::string test_text_file_in::filename
  = get_output_dir() + u8"test_text_file_in-\U00004f60\U0000597d.txt";
const std::vector<uint8_t> test_text_file_in::file_content
  = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

}  // namespace



TEST_F(test_text_file_in, path_constructor)
{
  text_file_in fi(filename);
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(file_content.size(), fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  std::vector<uint8_t> buffer(file_content.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, file_content);
}



TEST_F(test_text_file_in_death_test, path_constructor_failure)
{
  std::string invalid_filename = u8"InvalidFileName";
  HOU_EXPECT_ERROR(text_file_in fi(invalid_filename), std::runtime_error,
    format_string(get_text(sys_error::file_open), invalid_filename.c_str()));
}



TEST_F(test_text_file_in, move_constructor)
{
  text_file_in fi_dummy(filename);
  text_file_in fi(std::move(fi_dummy));
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(file_content.size(), fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  std::vector<uint8_t> buffer(file_content.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, file_content);
}



TEST_F(test_text_file_in, set_text_pos)
{
  text_file_in fi(filename);
  std::string buffer(2, 0);
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  fi.read(buffer);
  text_file_in::text_position pos_ref = fi.get_text_pos();
  EXPECT_NE(text_file_in::text_position::start, pos_ref);
  fi.set_text_pos(text_file_in::text_position::start);
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  fi.set_text_pos(pos_ref);
  EXPECT_EQ(pos_ref, fi.get_text_pos());
}



TEST_F(test_text_file_in, read_to_variable)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type);

  text_file_in fi(filename);
  buffer_type buffer;

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(1u, fi.get_read_element_count());
  HOU_EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(&buffer), file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(1u, fi.get_read_element_count());
  const uint8_t* offset_data = file_content.data() + buffer_byte_size;
  HOU_EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(&buffer), offset_data, buffer_byte_size);
}



TEST_F(test_text_file_in, read_to_basic_array)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  text_file_in fi(filename);
  buffer_type buffer[buffer_size];

  fi.read(buffer, buffer_size);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  HOU_EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(buffer), file_content.data(), buffer_byte_size);

  fi.read(buffer, buffer_size);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const uint8_t* offset_data = file_content.data() + buffer_byte_size;
  HOU_EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(buffer), offset_data, buffer_byte_size);
}



TEST_F(test_text_file_in, read_to_array)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  text_file_in fi(filename);
  std::array<buffer_type, buffer_size> buffer = {0, 0, 0};

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data()),
    file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const uint8_t* offset_data = file_content.data() + buffer_byte_size;
  HOU_EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(buffer.data()), offset_data, buffer_byte_size);
}



TEST_F(test_text_file_in, read_to_vector)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  text_file_in fi(filename);
  std::vector<buffer_type> buffer(buffer_size, 0u);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data()),
    file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const uint8_t* offset_data = file_content.data() + buffer_byte_size;
  HOU_EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(buffer.data()), offset_data, buffer_byte_size);
}



TEST_F(test_text_file_in, read_to_string)
{
  using buffer_type = std::string::value_type;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  text_file_in fi(filename);
  std::string buffer(buffer_size, 0);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<const uint8_t*>(buffer.data()),
    file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const uint8_t* offset_data = file_content.data() + buffer_byte_size;
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<const uint8_t*>(buffer.data()),
    offset_data, buffer_byte_size);
}



TEST_F(test_text_file_in, read_to_span)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  text_file_in fi(filename);
  std::vector<buffer_type> vec(buffer_size, 0u);
  span<buffer_type> buffer(vec);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  HOU_EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buffer.data()),
    file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const uint8_t* offset_data = file_content.data() + buffer_byte_size;
  HOU_EXPECT_ARRAY_EQ(
    reinterpret_cast<uint8_t*>(buffer.data()), offset_data, buffer_byte_size);
}



TEST_F(test_text_file_in, read_all_to_vector)
{
  text_file_in fi(filename);
  auto fi_content = fi.read_all<std::vector<uint8_t>>();

  EXPECT_EQ(file_content, fi_content);
  EXPECT_EQ(file_content.size(), fi.get_read_byte_count());
}



TEST_F(test_text_file_in, read_all_to_vector_not_from_start)
{
  text_file_in fi(filename);

  std::string buffer(2, 0);
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  fi.read(buffer);
  EXPECT_NE(text_file_in::text_position::start, fi.get_text_pos());

  auto fi_content = fi.read_all<std::vector<uint8_t>>();

  EXPECT_EQ(file_content, fi_content);
  EXPECT_EQ(file_content.size(), fi.get_read_byte_count());
}



TEST_F(test_text_file_in, eof)
{
  text_file_in fi(filename);
  uint count = 0;
  while(!fi.eof())
  {
    uint8_t buffer;
    fi.read(buffer);
    ++count;
  }
  EXPECT_EQ(fi.get_byte_count() + 1u, count);
}
