// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/cor/span.hpp"

#include "hou/sys/sys_exceptions.hpp"
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
  static const std::vector<char> file_content;
  static const std::string gen_filename;
  static const std::vector<char> gen_file_content;
};

using test_text_file_in_death_test = test_text_file_in;



void test_text_file_in::SetUpTestCase()
{
  Test::SetUpTestCase();
  file f(gen_filename, file_open_mode::write, file_type::binary);
  f.write(gen_file_content.data(), gen_file_content.size());
}



void test_text_file_in::TearDownTestCase()
{
  remove_dir(gen_filename);
  Test::TearDownTestCase();
}



const std::string test_text_file_in::filename
  = get_data_dir() + u8"test-file.txt";
const std::vector<char> test_text_file_in::file_content
  = {'a', 'b', 'c', 'd', 'e', 'f', '\n'};
const std::string test_text_file_in::gen_filename
  = get_output_dir() + u8"test_text_file_in-\U00004f60\U0000597d.txt";
const std::vector<char> test_text_file_in::gen_file_content
  = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

}  // namespace



TEST_F(test_text_file_in, non_generated_file_path_constructor)
{
  text_file_in fi(filename);
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(file_content.size(), fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  std::vector<char> buffer(file_content.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, file_content);
}



TEST_F(test_text_file_in, path_constructor)
{
  text_file_in fi(gen_filename);
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(gen_file_content.size(), fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  std::vector<char> buffer(gen_file_content.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, gen_file_content);
}



TEST_F(test_text_file_in_death_test, path_constructor_failure)
{
  std::string invalid_filename = u8"InvalidFileName";
  EXPECT_ERROR_N(
    text_file_in fi(invalid_filename), file_open_error, invalid_filename);
}



TEST_F(test_text_file_in, move_constructor)
{
  text_file_in fi_dummy(gen_filename);
  text_file_in fi(std::move(fi_dummy));
  EXPECT_FALSE(fi.eof());
  EXPECT_FALSE(fi.error());
  EXPECT_EQ(gen_file_content.size(), fi.get_byte_count());
  EXPECT_EQ(0u, fi.get_read_byte_count());
  EXPECT_EQ(0u, fi.get_read_element_count());
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  std::vector<char> buffer(gen_file_content.size(), 0u);
  fi.read(buffer);
  EXPECT_EQ(buffer, gen_file_content);
}



TEST_F(test_text_file_in, set_text_pos)
{
  text_file_in fi(gen_filename);
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

  text_file_in fi(gen_filename);
  buffer_type buffer;

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(1u, fi.get_read_element_count());
  EXPECT_ARRAY_EQ(
    reinterpret_cast<char*>(&buffer), gen_file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(1u, fi.get_read_element_count());
  const char* offset_data = gen_file_content.data() + buffer_byte_size;
  EXPECT_ARRAY_EQ(
    reinterpret_cast<char*>(&buffer), offset_data, buffer_byte_size);
}



TEST_F(test_text_file_in, read_to_basic_array)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  text_file_in fi(gen_filename);
  buffer_type buffer[buffer_size];

  fi.read(buffer, buffer_size);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_ARRAY_EQ(
    reinterpret_cast<char*>(buffer), gen_file_content.data(), buffer_byte_size);

  fi.read(buffer, buffer_size);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const char* offset_data = gen_file_content.data() + buffer_byte_size;
  EXPECT_ARRAY_EQ(
    reinterpret_cast<char*>(buffer), offset_data, buffer_byte_size);
}



TEST_F(test_text_file_in, read_to_array)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  text_file_in fi(gen_filename);
  std::array<buffer_type, buffer_size> buffer = {0, 0, 0};

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_ARRAY_EQ(reinterpret_cast<char*>(buffer.data()),
    gen_file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const char* offset_data = gen_file_content.data() + buffer_byte_size;
  EXPECT_ARRAY_EQ(
    reinterpret_cast<char*>(buffer.data()), offset_data, buffer_byte_size);
}



TEST_F(test_text_file_in, read_to_vector)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  text_file_in fi(gen_filename);
  std::vector<buffer_type> buffer(buffer_size, 0u);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_ARRAY_EQ(reinterpret_cast<char*>(buffer.data()),
    gen_file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const char* offset_data = gen_file_content.data() + buffer_byte_size;
  EXPECT_ARRAY_EQ(
    reinterpret_cast<char*>(buffer.data()), offset_data, buffer_byte_size);
}



TEST_F(test_text_file_in, read_to_string)
{
  using buffer_type = std::string::value_type;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  text_file_in fi(gen_filename);
  std::string buffer(buffer_size, 0);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_ARRAY_EQ(reinterpret_cast<const char*>(buffer.data()),
    gen_file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const char* offset_data = gen_file_content.data() + buffer_byte_size;
  EXPECT_ARRAY_EQ(reinterpret_cast<const char*>(buffer.data()),
    offset_data, buffer_byte_size);
}



TEST_F(test_text_file_in, read_to_span)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t buffer_byte_size = sizeof(buffer_type) * buffer_size;

  text_file_in fi(gen_filename);
  std::vector<buffer_type> vec(buffer_size, 0u);
  span<buffer_type> buffer(vec);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  EXPECT_ARRAY_EQ(reinterpret_cast<char*>(buffer.data()),
    gen_file_content.data(), buffer_byte_size);

  fi.read(buffer);
  EXPECT_EQ(buffer_byte_size, fi.get_read_byte_count());
  EXPECT_EQ(buffer_size, fi.get_read_element_count());
  const char* offset_data = gen_file_content.data() + buffer_byte_size;
  EXPECT_ARRAY_EQ(
    reinterpret_cast<char*>(buffer.data()), offset_data, buffer_byte_size);
}



TEST_F(test_text_file_in, read_all_to_vector)
{
  text_file_in fi(gen_filename);
  auto fi_content = fi.read_all<std::vector<char>>();

  EXPECT_EQ(gen_file_content, fi_content);
  EXPECT_EQ(gen_file_content.size(), fi.get_read_byte_count());
}



TEST_F(test_text_file_in, read_all_to_vector_not_from_start)
{
  text_file_in fi(gen_filename);

  std::string buffer(2, 0);
  EXPECT_EQ(text_file_in::text_position::start, fi.get_text_pos());
  fi.read(buffer);
  EXPECT_NE(text_file_in::text_position::start, fi.get_text_pos());

  auto fi_content = fi.read_all<std::vector<char>>();

  EXPECT_EQ(gen_file_content, fi_content);
  EXPECT_EQ(gen_file_content.size(), fi.get_read_byte_count());
}



TEST_F(test_text_file_in, eof)
{
  text_file_in fi(gen_filename);
  uint count = 0;
  while(!fi.eof())
  {
    char buffer;
    fi.read(buffer);
    ++count;
  }
  EXPECT_EQ(fi.get_byte_count() + 1u, count);
}
