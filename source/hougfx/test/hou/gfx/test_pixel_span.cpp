#include "hou/gfx/pixel_span.hpp"
#include "hou/test.hpp"

using namespace testing;
using namespace hou;



namespace
{

class test_pixel_span : public Test
{};

using test_pixel_span_death_test = test_pixel_span;

}  // namespace



TEST_F(test_pixel_span, default_constructor)
{
  pixel_span_2 ps;
  EXPECT_EQ(nullptr, ps.get_data());
  EXPECT_EQ(vec2u::zero(), ps.get_size());
  EXPECT_EQ(0u, ps.get_byte_depth());
  EXPECT_EQ(0u, ps.get_length());
}



TEST_F(test_pixel_span, data_constructor)
{
  std::vector<uint8_t> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

  pixel_span_2 ps2(v.data(), vec2u(2u, 4u), 2u);
  EXPECT_EQ(v.data(), ps2.get_data());
  EXPECT_EQ(vec2u(2u, 4u), ps2.get_size());
  EXPECT_EQ(2u, ps2.get_byte_depth());
  EXPECT_EQ(v.size(), ps2.get_length());

  pixel_span_3 ps3(v.data(), vec3u(2u, 2u, 2u), 2u);
  EXPECT_EQ(v.data(), ps3.get_data());
  EXPECT_EQ(vec3u(2u, 2u, 2u), ps3.get_size());
  EXPECT_EQ(2u, ps3.get_byte_depth());
  EXPECT_EQ(v.size(), ps3.get_length());
}



TEST_F(test_pixel_span, dimension_conversion_constructor)
{
  std::vector<uint8_t> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  pixel_span_2 ps2(v.data(), vec2u(2u, 4u), 2u);
  pixel_span_3 ps3(ps2);

  EXPECT_EQ(v.data(), ps3.get_data());
  EXPECT_EQ(vec3u(2u, 4u, 1u), ps3.get_size());
  EXPECT_EQ(2u, ps3.get_byte_depth());
  EXPECT_EQ(v.size(), ps3.get_length());
}



TEST_F(test_pixel_span, checked_element_access)
{
  std::vector<uint8_t> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  pixel_span_2 ps2(v.data(), vec2u(2u, 4u), 2u);

  for(size_t i = 0; i < ps2.get_length(); ++i)
  {
    EXPECT_EQ(v.at(i), ps2.at(i));
  }
}



TEST_F(test_pixel_span_death_test, checked_element_access_error)
{
  std::vector<uint8_t> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  pixel_span_2 ps2(v.data(), vec2u(2u, 4u), 2u);
  EXPECT_ERROR_0(ps2.at(ps2.get_length()), out_of_range);
}



TEST_F(test_pixel_span, unchecked_element_access)
{
  std::vector<uint8_t> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  pixel_span_2 ps2(v.data(), vec2u(2u, 4u), 2u);

  for(size_t i = 0; i < ps2.get_length(); ++i)
  {
    EXPECT_EQ(v[i], ps2[i]);
  }
}
