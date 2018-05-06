// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/cor/span.hpp"

#include "hou/sys/text_file_in.hpp"
#include "hou/sys/text_file_out.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_text_file_out
  : public Test
{
public:
  static const std::string filename;

public:
  test_text_file_out();
  ~test_text_file_out();
};



class test_text_file_out_death_test : public test_text_file_out {};



test_text_file_out::test_text_file_out()
{
  text_file_out fo(filename);
}



test_text_file_out::~test_text_file_out()
{
  remove_dir(filename);
}



const std::string test_text_file_out::filename = get_output_dir()
  + u8"test_text_file_out-\U00004f60\U0000597d.txt";

}



TEST_F(test_text_file_out, path_constructor)
{
  text_file_out fo(filename);
  EXPECT_FALSE(fo.eof());
  EXPECT_FALSE(fo.error());
  EXPECT_EQ(0u, fo.get_byte_count());
  EXPECT_EQ(0u, fo.get_write_byte_count());
  EXPECT_EQ(0u, fo.get_write_element_count());
  EXPECT_EQ(text_file_out::text_position::start, fo.get_text_pos());
}



TEST_F(test_text_file_out, move_constructor)
{
  text_file_out fo_dummy(filename);
  text_file_out fo(std::move(fo_dummy));
  EXPECT_FALSE(fo.eof());
  EXPECT_FALSE(fo.error());
  EXPECT_EQ(0u, fo.get_byte_count());
  EXPECT_EQ(0u, fo.get_write_byte_count());
  EXPECT_EQ(0u, fo.get_write_element_count());
  EXPECT_EQ(text_file_out::text_position::start, fo.get_text_pos());
}



TEST_F(test_text_file_out, set_text_pos)
{
  text_file_out fi(filename);
  std::string buffer = "ab";
  EXPECT_EQ(text_file_out::text_position::start, fi.get_text_pos());
  fi.write(buffer);
  text_file_out::text_position pos_ref = fi.get_text_pos();
  EXPECT_NE(text_file_out::text_position::start, pos_ref);
  fi.set_text_pos(text_file_out::text_position::start);
  EXPECT_EQ(text_file_out::text_position::start, fi.get_text_pos());
  fi.set_text_pos(pos_ref);
  EXPECT_EQ(pos_ref, fi.get_text_pos());
}



TEST_F(test_text_file_out, write_variable)
{
  using buffer_type = uint16_t;
  static constexpr size_t byte_count = sizeof(buffer_type);

  buffer_type buf_out = 3u;

  {
    text_file_out fo(filename);
    fo.write(buf_out);
    EXPECT_EQ(byte_count, fo.get_write_byte_count());
    EXPECT_EQ(1u, fo.get_write_element_count());
  }

  text_file_in fi(filename);
  buffer_type buf_in;
  fi.read(buf_in);
  EXPECT_EQ(byte_count, fi.get_byte_count());
  EXPECT_EQ(byte_count, fi.get_read_byte_count());
  EXPECT_EQ(buf_out, buf_in);
}



TEST_F(test_text_file_out, write_basic_array)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t byte_count = sizeof(buffer_type) * buffer_size;

  buffer_type buf_out[buffer_size] = {1u, 2u, 3u};

  {
    text_file_out fo(filename);
    fo.write(buf_out, buffer_size);
    EXPECT_EQ(byte_count, fo.get_write_byte_count());
    EXPECT_EQ(buffer_size, fo.get_write_element_count());
  }

  text_file_in fi(filename);
  buffer_type buf_in[buffer_size];
  fi.read(buf_in, buffer_size);
  EXPECT_EQ(byte_count, fi.get_byte_count());
  EXPECT_EQ(byte_count, fi.get_read_byte_count());
  EXPECT_ARRAY_EQ(reinterpret_cast<uint8_t*>(buf_in)
    , reinterpret_cast<uint8_t*>(buf_out), byte_count);
}



TEST_F(test_text_file_out, write_array)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t byte_count = sizeof(buffer_type) * buffer_size;

  std::array<buffer_type, buffer_size> buf_out = {1u, 2u, 3u};

  {
    text_file_out fo(filename);
    fo.write(buf_out);
    EXPECT_EQ(byte_count, fo.get_write_byte_count());
    EXPECT_EQ(buffer_size, fo.get_write_element_count());
  }

  text_file_in fi(filename);
  std::array<buffer_type, buffer_size> buf_in;
  fi.read(buf_in);
  EXPECT_EQ(byte_count, fi.get_byte_count());
  EXPECT_EQ(byte_count, fi.get_read_byte_count());
  EXPECT_EQ(buf_out, buf_in);
}



TEST_F(test_text_file_out, write_vector)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t byte_count = sizeof(buffer_type) * buffer_size;

  std::vector<buffer_type> buf_out = {1u, 2u, 3u};

  {
    text_file_out fo(filename);
    fo.write(buf_out);
    EXPECT_EQ(byte_count, fo.get_write_byte_count());
    EXPECT_EQ(buffer_size, fo.get_write_element_count());
  }

  text_file_in fi(filename);
  std::vector<buffer_type> buf_in(3u, 0u);
  fi.read(buf_in);
  EXPECT_EQ(byte_count, fi.get_byte_count());
  EXPECT_EQ(byte_count, fi.get_read_byte_count());
  EXPECT_EQ(buf_out, buf_in);
}



TEST_F(test_text_file_out, write_string)
{
  using buffer_type = std::string::value_type;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t byte_count = sizeof(buffer_type) * buffer_size;

  std::string buf_out = "abc";

  {
    text_file_out fo(filename);
    fo.write(buf_out);
    EXPECT_EQ(byte_count, fo.get_write_byte_count());
    EXPECT_EQ(buffer_size, fo.get_write_element_count());
  }

  text_file_in fi(filename);
  std::string buf_in(3u, 'a');
  fi.read(buf_in);
  EXPECT_EQ(byte_count, fi.get_byte_count());
  EXPECT_EQ(byte_count, fi.get_read_byte_count());
  EXPECT_EQ(buf_out, buf_in);
}



TEST_F(test_text_file_out, write_span)
{
  using buffer_type = uint16_t;
  static constexpr size_t buffer_size = 3u;
  static constexpr size_t byte_count = sizeof(buffer_type) * buffer_size;

  std::vector<buffer_type> vec_out = {1u, 2u, 3u};
  span<buffer_type> buf_out(vec_out);

  {
    text_file_out fo(filename);
    fo.write(buf_out);
    EXPECT_EQ(byte_count, fo.get_write_byte_count());
    EXPECT_EQ(buffer_size, fo.get_write_element_count());
  }

  text_file_in fi(filename);
  std::vector<buffer_type> vec_in(3u, 0u);
  span<buffer_type> buf_in(vec_in);
  fi.read(buf_in);
  EXPECT_EQ(byte_count, fi.get_byte_count());
  EXPECT_EQ(byte_count, fi.get_read_byte_count());
  EXPECT_EQ(vec_out, vec_in);
}

