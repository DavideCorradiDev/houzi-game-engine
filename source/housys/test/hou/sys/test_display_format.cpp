// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/display_format.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_display_format : public Test
{};

}  // namespace



TEST_F(test_display_format, get_bits_per_pixel)
{
    EXPECT_EQ(0u, get_bits_per_pixel(display::format::unknown));
    EXPECT_EQ(1u, get_bits_per_pixel(display::format::index1lsb));
    EXPECT_EQ(1u, get_bits_per_pixel(display::format::index1msb));
    EXPECT_EQ(4u, get_bits_per_pixel(display::format::index4lsb));
    EXPECT_EQ(4u, get_bits_per_pixel(display::format::index4msb));
    EXPECT_EQ(8u, get_bits_per_pixel(display::format::index8));
    EXPECT_EQ(8u, get_bits_per_pixel(display::format::rgb332));
    EXPECT_EQ(12u, get_bits_per_pixel(display::format::rgb444));
    EXPECT_EQ(15u, get_bits_per_pixel(display::format::rgb555));
    EXPECT_EQ(15u, get_bits_per_pixel(display::format::bgr555));
    EXPECT_EQ(16u, get_bits_per_pixel(display::format::argb4444));
    EXPECT_EQ(16u, get_bits_per_pixel(display::format::rgba4444));
    EXPECT_EQ(16u, get_bits_per_pixel(display::format::abgr4444));
    EXPECT_EQ(16u, get_bits_per_pixel(display::format::bgra4444));
    EXPECT_EQ(16u, get_bits_per_pixel(display::format::argb1555));
    EXPECT_EQ(16u, get_bits_per_pixel(display::format::rgba5551));
    EXPECT_EQ(16u, get_bits_per_pixel(display::format::abgr1555));
    EXPECT_EQ(16u, get_bits_per_pixel(display::format::bgra5551));
    EXPECT_EQ(16u, get_bits_per_pixel(display::format::rgb565));
    EXPECT_EQ(16u, get_bits_per_pixel(display::format::bgr565));
    EXPECT_EQ(24u, get_bits_per_pixel(display::format::rgb24));
    EXPECT_EQ(24u, get_bits_per_pixel(display::format::bgr24));
    EXPECT_EQ(24u, get_bits_per_pixel(display::format::rgb888));
    EXPECT_EQ(24u, get_bits_per_pixel(display::format::rgbx8888));
    EXPECT_EQ(24u, get_bits_per_pixel(display::format::bgr888));
    EXPECT_EQ(24u, get_bits_per_pixel(display::format::bgrx8888));
    EXPECT_EQ(32u, get_bits_per_pixel(display::format::argb8888));
    EXPECT_EQ(32u, get_bits_per_pixel(display::format::rgba8888));
    EXPECT_EQ(32u, get_bits_per_pixel(display::format::abgr8888));
    EXPECT_EQ(32u, get_bits_per_pixel(display::format::bgra8888));
    EXPECT_EQ(32u, get_bits_per_pixel(display::format::argb2101010));
    EXPECT_EQ(86u, get_bits_per_pixel(display::format::yv12));
    EXPECT_EQ(89u, get_bits_per_pixel(display::format::iyuv));
    EXPECT_EQ(85u, get_bits_per_pixel(display::format::yuy2));
    EXPECT_EQ(89u, get_bits_per_pixel(display::format::uyvy));
    EXPECT_EQ(86u, get_bits_per_pixel(display::format::yvyu));
    EXPECT_EQ(86u, get_bits_per_pixel(display::format::nv12));
    EXPECT_EQ(86u, get_bits_per_pixel(display::format::nv21));
}



TEST_F(test_display_format, get_bytes_per_pixel)
{
  EXPECT_EQ(0u, get_bytes_per_pixel(display::format::unknown));
  EXPECT_EQ(0u, get_bytes_per_pixel(display::format::index1lsb));
  EXPECT_EQ(0u, get_bytes_per_pixel(display::format::index1msb));
  EXPECT_EQ(0u, get_bytes_per_pixel(display::format::index4lsb));
  EXPECT_EQ(0u, get_bytes_per_pixel(display::format::index4msb));
  EXPECT_EQ(1u, get_bytes_per_pixel(display::format::index8));
  EXPECT_EQ(1u, get_bytes_per_pixel(display::format::rgb332));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::rgb444));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::rgb555));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::bgr555));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::argb4444));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::rgba4444));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::abgr4444));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::bgra4444));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::argb1555));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::rgba5551));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::abgr1555));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::bgra5551));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::rgb565));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::bgr565));
  EXPECT_EQ(3u, get_bytes_per_pixel(display::format::rgb24));
  EXPECT_EQ(3u, get_bytes_per_pixel(display::format::bgr24));
  EXPECT_EQ(4u, get_bytes_per_pixel(display::format::rgb888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display::format::rgbx8888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display::format::bgr888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display::format::bgrx8888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display::format::argb8888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display::format::rgba8888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display::format::abgr8888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display::format::bgra8888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display::format::argb2101010));
  EXPECT_EQ(1u, get_bytes_per_pixel(display::format::yv12));
  EXPECT_EQ(1u, get_bytes_per_pixel(display::format::iyuv));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::yuy2));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::uyvy));
  EXPECT_EQ(2u, get_bytes_per_pixel(display::format::yvyu));
  EXPECT_EQ(1u, get_bytes_per_pixel(display::format::nv12));
  EXPECT_EQ(1u, get_bytes_per_pixel(display::format::nv21));
}



TEST_F(test_display_format, get_type)
{
  EXPECT_EQ(display::format_type::unknown, get_type(display::format::unknown));
  EXPECT_EQ(display::format_type::index1, get_type(display::format::index1lsb));
  EXPECT_EQ(display::format_type::index1, get_type(display::format::index1msb));
  EXPECT_EQ(display::format_type::index4, get_type(display::format::index4lsb));
  EXPECT_EQ(display::format_type::index4, get_type(display::format::index4msb));
  EXPECT_EQ(display::format_type::index8, get_type(display::format::index8));
  EXPECT_EQ(display::format_type::packed8, get_type(display::format::rgb332));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::rgb444));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::rgb555));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::bgr555));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::argb4444));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::rgba4444));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::abgr4444));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::bgra4444));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::argb1555));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::rgba5551));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::abgr1555));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::bgra5551));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::rgb565));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::bgr565));
  EXPECT_EQ(display::format_type::arrayu8, get_type(display::format::rgb24));
  EXPECT_EQ(display::format_type::arrayu8, get_type(display::format::bgr24));
  EXPECT_EQ(display::format_type::packed32, get_type(display::format::rgb888));
  EXPECT_EQ(display::format_type::packed32, get_type(display::format::rgbx8888));
  EXPECT_EQ(display::format_type::packed32, get_type(display::format::bgr888));
  EXPECT_EQ(display::format_type::packed32, get_type(display::format::bgrx8888));
  EXPECT_EQ(display::format_type::packed32, get_type(display::format::argb8888));
  EXPECT_EQ(display::format_type::packed32, get_type(display::format::rgba8888));
  EXPECT_EQ(display::format_type::packed32, get_type(display::format::abgr8888));
  EXPECT_EQ(display::format_type::packed32, get_type(display::format::bgra8888));
  EXPECT_EQ(display::format_type::packed32, get_type(display::format::argb2101010));
  EXPECT_EQ(display::format_type::index4, get_type(display::format::yv12));
  EXPECT_EQ(display::format_type::packed32, get_type(display::format::iyuv));
  EXPECT_EQ(display::format_type::index4, get_type(display::format::yuy2));
  EXPECT_EQ(display::format_type::arrayu32, get_type(display::format::uyvy));
  EXPECT_EQ(display::format_type::packed16, get_type(display::format::yvyu));
  EXPECT_EQ(display::format_type::index4, get_type(display::format::nv12));
  EXPECT_EQ(display::format_type::index1, get_type(display::format::nv21));
}



TEST_F(test_display_format, get_bitmap_order)
{
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::unknown));
  EXPECT_EQ(display::format_bitmap_order::ev4321, get_bitmap_order(display::format::index1lsb));
  EXPECT_EQ(display::format_bitmap_order::ev1234, get_bitmap_order(display::format::index1msb));
  EXPECT_EQ(display::format_bitmap_order::ev4321, get_bitmap_order(display::format::index4lsb));
  EXPECT_EQ(display::format_bitmap_order::ev1234, get_bitmap_order(display::format::index4msb));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::index8));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::rgb332));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::rgb444));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::rgb555));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::bgr555));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::argb4444));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::rgba4444));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::abgr4444));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::bgra4444));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::argb1555));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::rgba5551));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::abgr1555));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::bgra5551));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::rgb565));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::bgr565));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::rgb24));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::bgr24));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::rgb888));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::rgbx8888));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::bgr888));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::bgrx8888));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::argb8888));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::rgba8888));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::abgr8888));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::bgra8888));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::argb2101010));
  EXPECT_EQ(display::format_bitmap_order(3), get_bitmap_order(display::format::yv12));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::iyuv));
  EXPECT_EQ(display::format_bitmap_order(5), get_bitmap_order(display::format::yuy2));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::uyvy));
  EXPECT_EQ(display::format_bitmap_order::none, get_bitmap_order(display::format::yvyu));
  EXPECT_EQ(display::format_bitmap_order(3), get_bitmap_order(display::format::nv12));
  EXPECT_EQ(display::format_bitmap_order(3), get_bitmap_order(display::format::nv21));
}



TEST_F(test_display_format, get_packed_order)
{
  EXPECT_EQ(display::format_packed_order::none, get_packed_order(display::format::unknown));
  EXPECT_EQ(display::format_packed_order::none, get_packed_order(display::format::index1lsb));
  EXPECT_EQ(display::format_packed_order::none, get_packed_order(display::format::index1msb));
  EXPECT_EQ(display::format_packed_order::none, get_packed_order(display::format::index4lsb));
  EXPECT_EQ(display::format_packed_order::none, get_packed_order(display::format::index4msb));
  EXPECT_EQ(display::format_packed_order::none, get_packed_order(display::format::index8));
  EXPECT_EQ(display::format_packed_order::xrgb, get_packed_order(display::format::rgb332));
  EXPECT_EQ(display::format_packed_order::xrgb, get_packed_order(display::format::rgb444));
  EXPECT_EQ(display::format_packed_order::xrgb, get_packed_order(display::format::rgb555));
  EXPECT_EQ(display::format_packed_order::xbgr, get_packed_order(display::format::bgr555));
  EXPECT_EQ(display::format_packed_order::argb, get_packed_order(display::format::argb4444));
  EXPECT_EQ(display::format_packed_order::rgba, get_packed_order(display::format::rgba4444));
  EXPECT_EQ(display::format_packed_order::abgr, get_packed_order(display::format::abgr4444));
  EXPECT_EQ(display::format_packed_order::bgra, get_packed_order(display::format::bgra4444));
  EXPECT_EQ(display::format_packed_order::argb, get_packed_order(display::format::argb1555));
  EXPECT_EQ(display::format_packed_order::rgba, get_packed_order(display::format::rgba5551));
  EXPECT_EQ(display::format_packed_order::abgr, get_packed_order(display::format::abgr1555));
  EXPECT_EQ(display::format_packed_order::bgra, get_packed_order(display::format::bgra5551));
  EXPECT_EQ(display::format_packed_order::xrgb, get_packed_order(display::format::rgb565));
  EXPECT_EQ(display::format_packed_order::xbgr, get_packed_order(display::format::bgr565));
  EXPECT_EQ(display::format_packed_order::none, get_packed_order(display::format::rgb24));
  EXPECT_EQ(display::format_packed_order::none, get_packed_order(display::format::bgr24));
  EXPECT_EQ(display::format_packed_order::xrgb, get_packed_order(display::format::rgb888));
  EXPECT_EQ(display::format_packed_order::rgbx, get_packed_order(display::format::rgbx8888));
  EXPECT_EQ(display::format_packed_order::xbgr, get_packed_order(display::format::bgr888));
  EXPECT_EQ(display::format_packed_order::bgrx, get_packed_order(display::format::bgrx8888));
  EXPECT_EQ(display::format_packed_order::argb, get_packed_order(display::format::argb8888));
  EXPECT_EQ(display::format_packed_order::rgba, get_packed_order(display::format::rgba8888));
  EXPECT_EQ(display::format_packed_order::abgr, get_packed_order(display::format::abgr8888));
  EXPECT_EQ(display::format_packed_order::bgra, get_packed_order(display::format::bgra8888));
  EXPECT_EQ(display::format_packed_order::argb, get_packed_order(display::format::argb2101010));
  EXPECT_EQ(display::format_packed_order::none, get_packed_order(display::format::yv12));
  EXPECT_EQ(display::format_packed_order::xbgr, get_packed_order(display::format::iyuv));
  EXPECT_EQ(display::format_packed_order::none, get_packed_order(display::format::yuy2));
  EXPECT_EQ(display::format_packed_order::none, get_packed_order(display::format::uyvy));
  EXPECT_EQ(display::format_packed_order::xbgr, get_packed_order(display::format::yvyu));
  EXPECT_EQ(display::format_packed_order::none, get_packed_order(display::format::nv12));
  EXPECT_EQ(display::format_packed_order::none, get_packed_order(display::format::nv21));
}



TEST_F(test_display_format, get_array_order)
{
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::unknown));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::index1lsb));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::index1msb));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::index4lsb));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::index4msb));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::index8));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::rgb332));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::rgb444));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::rgb555));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::bgr555));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::argb4444));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::rgba4444));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::abgr4444));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::bgra4444));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::argb1555));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::rgba5551));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::abgr1555));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::bgra5551));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::rgb565));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::bgr565));
  EXPECT_EQ(display::format_array_order::rgb, get_array_order(display::format::rgb24));
  EXPECT_EQ(display::format_array_order::bgr, get_array_order(display::format::bgr24));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::rgb888));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::rgbx8888));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::bgr888));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::bgrx8888));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::argb8888));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::rgba8888));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::abgr8888));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::bgra8888));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::argb2101010));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::yv12));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::iyuv));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::yuy2));
  EXPECT_EQ(display::format_array_order::bgra, get_array_order(display::format::uyvy));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::yvyu));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::nv12));
  EXPECT_EQ(display::format_array_order::none, get_array_order(display::format::nv21));
}



TEST_F(test_display_format, get_packed_layout)
{
  EXPECT_EQ(display::format_packed_layout::none, get_packed_layout(display::format::unknown));
  EXPECT_EQ(display::format_packed_layout::none, get_packed_layout(display::format::index1lsb));
  EXPECT_EQ(display::format_packed_layout::none, get_packed_layout(display::format::index1msb));
  EXPECT_EQ(display::format_packed_layout::none, get_packed_layout(display::format::index4lsb));
  EXPECT_EQ(display::format_packed_layout::none, get_packed_layout(display::format::index4msb));
  EXPECT_EQ(display::format_packed_layout::none, get_packed_layout(display::format::index8));
  EXPECT_EQ(display::format_packed_layout::ev332, get_packed_layout(display::format::rgb332));
  EXPECT_EQ(display::format_packed_layout::ev4444, get_packed_layout(display::format::rgb444));
  EXPECT_EQ(display::format_packed_layout::ev1555, get_packed_layout(display::format::rgb555));
  EXPECT_EQ(display::format_packed_layout::ev1555, get_packed_layout(display::format::bgr555));
  EXPECT_EQ(display::format_packed_layout::ev4444, get_packed_layout(display::format::argb4444));
  EXPECT_EQ(display::format_packed_layout::ev4444, get_packed_layout(display::format::rgba4444));
  EXPECT_EQ(display::format_packed_layout::ev4444, get_packed_layout(display::format::abgr4444));
  EXPECT_EQ(display::format_packed_layout::ev4444, get_packed_layout(display::format::bgra4444));
  EXPECT_EQ(display::format_packed_layout::ev1555, get_packed_layout(display::format::argb1555));
  EXPECT_EQ(display::format_packed_layout::ev5551, get_packed_layout(display::format::rgba5551));
  EXPECT_EQ(display::format_packed_layout::ev1555, get_packed_layout(display::format::abgr1555));
  EXPECT_EQ(display::format_packed_layout::ev5551, get_packed_layout(display::format::bgra5551));
  EXPECT_EQ(display::format_packed_layout::ev565, get_packed_layout(display::format::rgb565));
  EXPECT_EQ(display::format_packed_layout::ev565, get_packed_layout(display::format::bgr565));
  EXPECT_EQ(display::format_packed_layout::none, get_packed_layout(display::format::rgb24));
  EXPECT_EQ(display::format_packed_layout::none, get_packed_layout(display::format::bgr24));
  EXPECT_EQ(display::format_packed_layout::ev8888, get_packed_layout(display::format::rgb888));
  EXPECT_EQ(display::format_packed_layout::ev8888, get_packed_layout(display::format::rgbx8888));
  EXPECT_EQ(display::format_packed_layout::ev8888, get_packed_layout(display::format::bgr888));
  EXPECT_EQ(display::format_packed_layout::ev8888, get_packed_layout(display::format::bgrx8888));
  EXPECT_EQ(display::format_packed_layout::ev8888, get_packed_layout(display::format::argb8888));
  EXPECT_EQ(display::format_packed_layout::ev8888, get_packed_layout(display::format::rgba8888));
  EXPECT_EQ(display::format_packed_layout::ev8888, get_packed_layout(display::format::abgr8888));
  EXPECT_EQ(display::format_packed_layout::ev8888, get_packed_layout(display::format::bgra8888));
  EXPECT_EQ(display::format_packed_layout::ev2101010, get_packed_layout(display::format::argb2101010));
  EXPECT_EQ(display::format_packed_layout::none, get_packed_layout(display::format::yv12));
  EXPECT_EQ(display::format_packed_layout::ev565, get_packed_layout(display::format::iyuv));
  EXPECT_EQ(display::format_packed_layout::none, get_packed_layout(display::format::yuy2));
  EXPECT_EQ(display::format_packed_layout::none, get_packed_layout(display::format::uyvy));
  EXPECT_EQ(display::format_packed_layout(9), get_packed_layout(display::format::yvyu));
  EXPECT_EQ(display::format_packed_layout::none, get_packed_layout(display::format::nv12));
  EXPECT_EQ(display::format_packed_layout::none, get_packed_layout(display::format::nv21));
}



TEST_F(test_display_format, is_indexed)
{
  EXPECT_FALSE(is_indexed(display::format::unknown));
  EXPECT_TRUE(is_indexed(display::format::index1lsb));
  EXPECT_TRUE(is_indexed(display::format::index1msb));
  EXPECT_TRUE(is_indexed(display::format::index4lsb));
  EXPECT_TRUE(is_indexed(display::format::index4msb));
  EXPECT_TRUE(is_indexed(display::format::index8));
  EXPECT_FALSE(is_indexed(display::format::rgb332));
  EXPECT_FALSE(is_indexed(display::format::rgb444));
  EXPECT_FALSE(is_indexed(display::format::rgb555));
  EXPECT_FALSE(is_indexed(display::format::bgr555));
  EXPECT_FALSE(is_indexed(display::format::argb4444));
  EXPECT_FALSE(is_indexed(display::format::rgba4444));
  EXPECT_FALSE(is_indexed(display::format::abgr4444));
  EXPECT_FALSE(is_indexed(display::format::bgra4444));
  EXPECT_FALSE(is_indexed(display::format::argb1555));
  EXPECT_FALSE(is_indexed(display::format::rgba5551));
  EXPECT_FALSE(is_indexed(display::format::abgr1555));
  EXPECT_FALSE(is_indexed(display::format::bgra5551));
  EXPECT_FALSE(is_indexed(display::format::rgb565));
  EXPECT_FALSE(is_indexed(display::format::bgr565));
  EXPECT_FALSE(is_indexed(display::format::rgb24));
  EXPECT_FALSE(is_indexed(display::format::bgr24));
  EXPECT_FALSE(is_indexed(display::format::rgb888));
  EXPECT_FALSE(is_indexed(display::format::rgbx8888));
  EXPECT_FALSE(is_indexed(display::format::bgr888));
  EXPECT_FALSE(is_indexed(display::format::bgrx8888));
  EXPECT_FALSE(is_indexed(display::format::argb8888));
  EXPECT_FALSE(is_indexed(display::format::rgba8888));
  EXPECT_FALSE(is_indexed(display::format::abgr8888));
  EXPECT_FALSE(is_indexed(display::format::bgra8888));
  EXPECT_FALSE(is_indexed(display::format::argb2101010));
  EXPECT_FALSE(is_indexed(display::format::yv12));
  EXPECT_FALSE(is_indexed(display::format::iyuv));
  EXPECT_FALSE(is_indexed(display::format::yuy2));
  EXPECT_FALSE(is_indexed(display::format::uyvy));
  EXPECT_FALSE(is_indexed(display::format::yvyu));
  EXPECT_FALSE(is_indexed(display::format::nv12));
  EXPECT_FALSE(is_indexed(display::format::nv21));
}



TEST_F(test_display_format, has_alpha)
{
  EXPECT_FALSE(has_alpha(display::format::unknown));
  EXPECT_FALSE(has_alpha(display::format::index1lsb));
  EXPECT_FALSE(has_alpha(display::format::index1msb));
  EXPECT_FALSE(has_alpha(display::format::index4lsb));
  EXPECT_FALSE(has_alpha(display::format::index4msb));
  EXPECT_FALSE(has_alpha(display::format::index8));
  EXPECT_FALSE(has_alpha(display::format::rgb332));
  EXPECT_FALSE(has_alpha(display::format::rgb444));
  EXPECT_FALSE(has_alpha(display::format::rgb555));
  EXPECT_FALSE(has_alpha(display::format::bgr555));
  EXPECT_TRUE(has_alpha(display::format::argb4444));
  EXPECT_TRUE(has_alpha(display::format::rgba4444));
  EXPECT_TRUE(has_alpha(display::format::abgr4444));
  EXPECT_TRUE(has_alpha(display::format::bgra4444));
  EXPECT_TRUE(has_alpha(display::format::argb1555));
  EXPECT_TRUE(has_alpha(display::format::rgba5551));
  EXPECT_TRUE(has_alpha(display::format::abgr1555));
  EXPECT_TRUE(has_alpha(display::format::bgra5551));
  EXPECT_FALSE(has_alpha(display::format::rgb565));
  EXPECT_FALSE(has_alpha(display::format::bgr565));
  EXPECT_FALSE(has_alpha(display::format::rgb24));
  EXPECT_FALSE(has_alpha(display::format::bgr24));
  EXPECT_FALSE(has_alpha(display::format::rgb888));
  EXPECT_FALSE(has_alpha(display::format::rgbx8888));
  EXPECT_FALSE(has_alpha(display::format::bgr888));
  EXPECT_FALSE(has_alpha(display::format::bgrx8888));
  EXPECT_TRUE(has_alpha(display::format::argb8888));
  EXPECT_TRUE(has_alpha(display::format::rgba8888));
  EXPECT_TRUE(has_alpha(display::format::abgr8888));
  EXPECT_TRUE(has_alpha(display::format::bgra8888));
  EXPECT_TRUE(has_alpha(display::format::argb2101010));
  EXPECT_FALSE(has_alpha(display::format::yv12));
  EXPECT_FALSE(has_alpha(display::format::iyuv));
  EXPECT_FALSE(has_alpha(display::format::yuy2));
  EXPECT_FALSE(has_alpha(display::format::uyvy));
  EXPECT_FALSE(has_alpha(display::format::yvyu));
  EXPECT_FALSE(has_alpha(display::format::nv12));
  EXPECT_FALSE(has_alpha(display::format::nv21));
}



TEST_F(test_display_format, is_fourcc)
{
  EXPECT_FALSE(is_fourcc(display::format::unknown));
  EXPECT_FALSE(is_fourcc(display::format::index1lsb));
  EXPECT_FALSE(is_fourcc(display::format::index1msb));
  EXPECT_FALSE(is_fourcc(display::format::index4lsb));
  EXPECT_FALSE(is_fourcc(display::format::index4msb));
  EXPECT_FALSE(is_fourcc(display::format::index8));
  EXPECT_FALSE(is_fourcc(display::format::rgb332));
  EXPECT_FALSE(is_fourcc(display::format::rgb444));
  EXPECT_FALSE(is_fourcc(display::format::rgb555));
  EXPECT_FALSE(is_fourcc(display::format::bgr555));
  EXPECT_FALSE(is_fourcc(display::format::argb4444));
  EXPECT_FALSE(is_fourcc(display::format::rgba4444));
  EXPECT_FALSE(is_fourcc(display::format::abgr4444));
  EXPECT_FALSE(is_fourcc(display::format::bgra4444));
  EXPECT_FALSE(is_fourcc(display::format::argb1555));
  EXPECT_FALSE(is_fourcc(display::format::rgba5551));
  EXPECT_FALSE(is_fourcc(display::format::abgr1555));
  EXPECT_FALSE(is_fourcc(display::format::bgra5551));
  EXPECT_FALSE(is_fourcc(display::format::rgb565));
  EXPECT_FALSE(is_fourcc(display::format::bgr565));
  EXPECT_FALSE(is_fourcc(display::format::rgb24));
  EXPECT_FALSE(is_fourcc(display::format::bgr24));
  EXPECT_FALSE(is_fourcc(display::format::rgb888));
  EXPECT_FALSE(is_fourcc(display::format::rgbx8888));
  EXPECT_FALSE(is_fourcc(display::format::bgr888));
  EXPECT_FALSE(is_fourcc(display::format::bgrx8888));
  EXPECT_FALSE(is_fourcc(display::format::argb8888));
  EXPECT_FALSE(is_fourcc(display::format::rgba8888));
  EXPECT_FALSE(is_fourcc(display::format::abgr8888));
  EXPECT_FALSE(is_fourcc(display::format::bgra8888));
  EXPECT_FALSE(is_fourcc(display::format::argb2101010));
  EXPECT_TRUE(is_fourcc(display::format::yv12));
  EXPECT_TRUE(is_fourcc(display::format::iyuv));
  EXPECT_TRUE(is_fourcc(display::format::yuy2));
  EXPECT_TRUE(is_fourcc(display::format::uyvy));
  EXPECT_TRUE(is_fourcc(display::format::yvyu));
  EXPECT_TRUE(is_fourcc(display::format::nv12));
  EXPECT_TRUE(is_fourcc(display::format::nv21));
}
