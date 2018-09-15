#include "hou/gfx/pixel_view.hpp"
#include "hou/test.hpp"

using namespace testing;
using namespace hou;



namespace
{

class test_pixel_view : public Test
{};

using test_pixel_view_death_test = test_pixel_view;

}  // namespace



TEST_F(test_pixel_view, default_constructor)
{
  pixel_view2 ps;
  EXPECT_EQ(nullptr, ps.get_data());
  EXPECT_EQ(vec2u::zero(), ps.get_size());
  EXPECT_EQ(0u, ps.get_bytes_per_pixel());
  EXPECT_EQ(0u, ps.get_byte_count());
}



TEST_F(test_pixel_view, data_constructor)
{
  std::vector<uint8_t> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

  pixel_view2 ps2(v.data(), vec2u(2u, 4u), 2u);
  EXPECT_EQ(v.data(), ps2.get_data());
  EXPECT_EQ(vec2u(2u, 4u), ps2.get_size());
  EXPECT_EQ(2u, ps2.get_bytes_per_pixel());
  EXPECT_EQ(v.size(), ps2.get_byte_count());

  pixel_view3 ps3(v.data(), vec3u(2u, 2u, 2u), 2u);
  EXPECT_EQ(v.data(), ps3.get_data());
  EXPECT_EQ(vec3u(2u, 2u, 2u), ps3.get_size());
  EXPECT_EQ(2u, ps3.get_bytes_per_pixel());
  EXPECT_EQ(v.size(), ps3.get_byte_count());
}



TEST_F(test_pixel_view, image_constructor)
{
  image2_rgba im(vec2u(3u, 5u));

  pixel_view2 ps2(im);
  EXPECT_EQ(
    reinterpret_cast<const uint8_t*>(im.get_pixels().data()), ps2.get_data());
  EXPECT_EQ(im.get_size(), ps2.get_size());
  EXPECT_EQ(im.get_pixel_byte_count(), ps2.get_bytes_per_pixel());
  EXPECT_EQ(
    im.get_pixels().size() * im.get_pixel_byte_count(), ps2.get_byte_count());
}



TEST_F(test_pixel_view, dimension_conversion_constructor)
{
  std::vector<uint8_t> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  pixel_view2 ps2(v.data(), vec2u(2u, 4u), 2u);
  pixel_view3 ps3(ps2);

  EXPECT_EQ(v.data(), ps3.get_data());
  EXPECT_EQ(vec3u(2u, 4u, 1u), ps3.get_size());
  EXPECT_EQ(2u, ps3.get_bytes_per_pixel());
  EXPECT_EQ(v.size(), ps3.get_byte_count());
}



TEST_F(test_pixel_view, checked_element_access)
{
  std::vector<uint8_t> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  pixel_view2 ps2(v.data(), vec2u(2u, 4u), 2u);

  for(size_t i = 0; i < ps2.get_byte_count(); ++i)
  {
    EXPECT_EQ(v.at(i), ps2.at(i));
  }
}



TEST_F(test_pixel_view_death_test, checked_element_access_error)
{
  std::vector<uint8_t> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  pixel_view2 ps2(v.data(), vec2u(2u, 4u), 2u);
  EXPECT_ERROR_0(ps2.at(ps2.get_byte_count()), out_of_range);
}



TEST_F(test_pixel_view, unchecked_element_access)
{
  std::vector<uint8_t> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  pixel_view2 ps2(v.data(), vec2u(2u, 4u), 2u);

  for(size_t i = 0; i < ps2.get_byte_count(); ++i)
  {
    EXPECT_EQ(v[i], ps2[i]);
  }
}
