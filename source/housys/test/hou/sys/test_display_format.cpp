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
  EXPECT_EQ(0u, get_bits_per_pixel(display_format::unknown));
  EXPECT_EQ(1u, get_bits_per_pixel(display_format::index1lsb));
  EXPECT_EQ(1u, get_bits_per_pixel(display_format::index1msb));
  EXPECT_EQ(4u, get_bits_per_pixel(display_format::index4lsb));
  EXPECT_EQ(4u, get_bits_per_pixel(display_format::index4msb));
  EXPECT_EQ(8u, get_bits_per_pixel(display_format::index8));
  EXPECT_EQ(8u, get_bits_per_pixel(display_format::rgb332));
  EXPECT_EQ(12u, get_bits_per_pixel(display_format::rgb444));
  EXPECT_EQ(15u, get_bits_per_pixel(display_format::rgb555));
  EXPECT_EQ(15u, get_bits_per_pixel(display_format::bgr555));
  EXPECT_EQ(16u, get_bits_per_pixel(display_format::argb4444));
  EXPECT_EQ(16u, get_bits_per_pixel(display_format::rgba4444));
  EXPECT_EQ(16u, get_bits_per_pixel(display_format::abgr4444));
  EXPECT_EQ(16u, get_bits_per_pixel(display_format::bgra4444));
  EXPECT_EQ(16u, get_bits_per_pixel(display_format::argb1555));
  EXPECT_EQ(16u, get_bits_per_pixel(display_format::rgba5551));
  EXPECT_EQ(16u, get_bits_per_pixel(display_format::abgr1555));
  EXPECT_EQ(16u, get_bits_per_pixel(display_format::bgra5551));
  EXPECT_EQ(16u, get_bits_per_pixel(display_format::rgb565));
  EXPECT_EQ(16u, get_bits_per_pixel(display_format::bgr565));
  EXPECT_EQ(24u, get_bits_per_pixel(display_format::rgb24));
  EXPECT_EQ(24u, get_bits_per_pixel(display_format::bgr24));
  EXPECT_EQ(24u, get_bits_per_pixel(display_format::rgb888));
  EXPECT_EQ(24u, get_bits_per_pixel(display_format::rgbx8888));
  EXPECT_EQ(24u, get_bits_per_pixel(display_format::bgr888));
  EXPECT_EQ(24u, get_bits_per_pixel(display_format::bgrx8888));
  EXPECT_EQ(32u, get_bits_per_pixel(display_format::argb8888));
  EXPECT_EQ(32u, get_bits_per_pixel(display_format::rgba8888));
  EXPECT_EQ(32u, get_bits_per_pixel(display_format::abgr8888));
  EXPECT_EQ(32u, get_bits_per_pixel(display_format::bgra8888));
  EXPECT_EQ(32u, get_bits_per_pixel(display_format::argb2101010));
  EXPECT_EQ(86u, get_bits_per_pixel(display_format::yv12));
  EXPECT_EQ(89u, get_bits_per_pixel(display_format::iyuv));
  EXPECT_EQ(85u, get_bits_per_pixel(display_format::yuy2));
  EXPECT_EQ(89u, get_bits_per_pixel(display_format::uyvy));
  EXPECT_EQ(86u, get_bits_per_pixel(display_format::yvyu));
  EXPECT_EQ(86u, get_bits_per_pixel(display_format::nv12));
  EXPECT_EQ(86u, get_bits_per_pixel(display_format::nv21));
}



TEST_F(test_display_format, get_bytes_per_pixel)
{
  EXPECT_EQ(0u, get_bytes_per_pixel(display_format::unknown));
  EXPECT_EQ(0u, get_bytes_per_pixel(display_format::index1lsb));
  EXPECT_EQ(0u, get_bytes_per_pixel(display_format::index1msb));
  EXPECT_EQ(0u, get_bytes_per_pixel(display_format::index4lsb));
  EXPECT_EQ(0u, get_bytes_per_pixel(display_format::index4msb));
  EXPECT_EQ(1u, get_bytes_per_pixel(display_format::index8));
  EXPECT_EQ(1u, get_bytes_per_pixel(display_format::rgb332));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::rgb444));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::rgb555));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::bgr555));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::argb4444));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::rgba4444));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::abgr4444));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::bgra4444));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::argb1555));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::rgba5551));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::abgr1555));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::bgra5551));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::rgb565));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::bgr565));
  EXPECT_EQ(3u, get_bytes_per_pixel(display_format::rgb24));
  EXPECT_EQ(3u, get_bytes_per_pixel(display_format::bgr24));
  EXPECT_EQ(4u, get_bytes_per_pixel(display_format::rgb888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display_format::rgbx8888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display_format::bgr888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display_format::bgrx8888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display_format::argb8888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display_format::rgba8888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display_format::abgr8888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display_format::bgra8888));
  EXPECT_EQ(4u, get_bytes_per_pixel(display_format::argb2101010));
  EXPECT_EQ(1u, get_bytes_per_pixel(display_format::yv12));
  EXPECT_EQ(1u, get_bytes_per_pixel(display_format::iyuv));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::yuy2));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::uyvy));
  EXPECT_EQ(2u, get_bytes_per_pixel(display_format::yvyu));
  EXPECT_EQ(1u, get_bytes_per_pixel(display_format::nv12));
  EXPECT_EQ(1u, get_bytes_per_pixel(display_format::nv21));
}



TEST_F(test_display_format, get_type)
{
  EXPECT_EQ(display_format_type::unknown, get_type(display_format::unknown));
  EXPECT_EQ(display_format_type::index1, get_type(display_format::index1lsb));
  EXPECT_EQ(display_format_type::index1, get_type(display_format::index1msb));
  EXPECT_EQ(display_format_type::index4, get_type(display_format::index4lsb));
  EXPECT_EQ(display_format_type::index4, get_type(display_format::index4msb));
  EXPECT_EQ(display_format_type::index8, get_type(display_format::index8));
  EXPECT_EQ(display_format_type::packed8, get_type(display_format::rgb332));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::rgb444));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::rgb555));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::bgr555));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::argb4444));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::rgba4444));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::abgr4444));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::bgra4444));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::argb1555));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::rgba5551));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::abgr1555));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::bgra5551));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::rgb565));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::bgr565));
  EXPECT_EQ(display_format_type::arrayu8, get_type(display_format::rgb24));
  EXPECT_EQ(display_format_type::arrayu8, get_type(display_format::bgr24));
  EXPECT_EQ(display_format_type::packed32, get_type(display_format::rgb888));
  EXPECT_EQ(display_format_type::packed32, get_type(display_format::rgbx8888));
  EXPECT_EQ(display_format_type::packed32, get_type(display_format::bgr888));
  EXPECT_EQ(display_format_type::packed32, get_type(display_format::bgrx8888));
  EXPECT_EQ(display_format_type::packed32, get_type(display_format::argb8888));
  EXPECT_EQ(display_format_type::packed32, get_type(display_format::rgba8888));
  EXPECT_EQ(display_format_type::packed32, get_type(display_format::abgr8888));
  EXPECT_EQ(display_format_type::packed32, get_type(display_format::bgra8888));
  EXPECT_EQ(
    display_format_type::packed32, get_type(display_format::argb2101010));
  EXPECT_EQ(display_format_type::index4, get_type(display_format::yv12));
  EXPECT_EQ(display_format_type::packed32, get_type(display_format::iyuv));
  EXPECT_EQ(display_format_type::index4, get_type(display_format::yuy2));
  EXPECT_EQ(display_format_type::arrayu32, get_type(display_format::uyvy));
  EXPECT_EQ(display_format_type::packed16, get_type(display_format::yvyu));
  EXPECT_EQ(display_format_type::index4, get_type(display_format::nv12));
  EXPECT_EQ(display_format_type::index1, get_type(display_format::nv21));
}



TEST_F(test_display_format, get_bitmap_order)
{
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::unknown));
  EXPECT_EQ(display_format_bitmap_order::ev4321,
    get_bitmap_order(display_format::index1lsb));
  EXPECT_EQ(display_format_bitmap_order::ev1234,
    get_bitmap_order(display_format::index1msb));
  EXPECT_EQ(display_format_bitmap_order::ev4321,
    get_bitmap_order(display_format::index4lsb));
  EXPECT_EQ(display_format_bitmap_order::ev1234,
    get_bitmap_order(display_format::index4msb));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::index8));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::rgb332));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::rgb444));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::rgb555));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::bgr555));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::argb4444));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::rgba4444));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::abgr4444));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::bgra4444));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::argb1555));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::rgba5551));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::abgr1555));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::bgra5551));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::rgb565));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::bgr565));
  EXPECT_EQ(
    display_format_bitmap_order::none, get_bitmap_order(display_format::rgb24));
  EXPECT_EQ(
    display_format_bitmap_order::none, get_bitmap_order(display_format::bgr24));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::rgb888));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::rgbx8888));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::bgr888));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::bgrx8888));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::argb8888));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::rgba8888));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::abgr8888));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::bgra8888));
  EXPECT_EQ(display_format_bitmap_order::none,
    get_bitmap_order(display_format::argb2101010));
  EXPECT_EQ(
    display_format_bitmap_order(3), get_bitmap_order(display_format::yv12));
  EXPECT_EQ(
    display_format_bitmap_order::none, get_bitmap_order(display_format::iyuv));
  EXPECT_EQ(
    display_format_bitmap_order(5), get_bitmap_order(display_format::yuy2));
  EXPECT_EQ(
    display_format_bitmap_order::none, get_bitmap_order(display_format::uyvy));
  EXPECT_EQ(
    display_format_bitmap_order::none, get_bitmap_order(display_format::yvyu));
  EXPECT_EQ(
    display_format_bitmap_order(3), get_bitmap_order(display_format::nv12));
  EXPECT_EQ(
    display_format_bitmap_order(3), get_bitmap_order(display_format::nv21));
}



TEST_F(test_display_format, get_packed_order)
{
  EXPECT_EQ(display_format_packed_order::none,
    get_packed_order(display_format::unknown));
  EXPECT_EQ(display_format_packed_order::none,
    get_packed_order(display_format::index1lsb));
  EXPECT_EQ(display_format_packed_order::none,
    get_packed_order(display_format::index1msb));
  EXPECT_EQ(display_format_packed_order::none,
    get_packed_order(display_format::index4lsb));
  EXPECT_EQ(display_format_packed_order::none,
    get_packed_order(display_format::index4msb));
  EXPECT_EQ(display_format_packed_order::none,
    get_packed_order(display_format::index8));
  EXPECT_EQ(display_format_packed_order::xrgb,
    get_packed_order(display_format::rgb332));
  EXPECT_EQ(display_format_packed_order::xrgb,
    get_packed_order(display_format::rgb444));
  EXPECT_EQ(display_format_packed_order::xrgb,
    get_packed_order(display_format::rgb555));
  EXPECT_EQ(display_format_packed_order::xbgr,
    get_packed_order(display_format::bgr555));
  EXPECT_EQ(display_format_packed_order::argb,
    get_packed_order(display_format::argb4444));
  EXPECT_EQ(display_format_packed_order::rgba,
    get_packed_order(display_format::rgba4444));
  EXPECT_EQ(display_format_packed_order::abgr,
    get_packed_order(display_format::abgr4444));
  EXPECT_EQ(display_format_packed_order::bgra,
    get_packed_order(display_format::bgra4444));
  EXPECT_EQ(display_format_packed_order::argb,
    get_packed_order(display_format::argb1555));
  EXPECT_EQ(display_format_packed_order::rgba,
    get_packed_order(display_format::rgba5551));
  EXPECT_EQ(display_format_packed_order::abgr,
    get_packed_order(display_format::abgr1555));
  EXPECT_EQ(display_format_packed_order::bgra,
    get_packed_order(display_format::bgra5551));
  EXPECT_EQ(display_format_packed_order::xrgb,
    get_packed_order(display_format::rgb565));
  EXPECT_EQ(display_format_packed_order::xbgr,
    get_packed_order(display_format::bgr565));
  EXPECT_EQ(
    display_format_packed_order::none, get_packed_order(display_format::rgb24));
  EXPECT_EQ(
    display_format_packed_order::none, get_packed_order(display_format::bgr24));
  EXPECT_EQ(display_format_packed_order::xrgb,
    get_packed_order(display_format::rgb888));
  EXPECT_EQ(display_format_packed_order::rgbx,
    get_packed_order(display_format::rgbx8888));
  EXPECT_EQ(display_format_packed_order::xbgr,
    get_packed_order(display_format::bgr888));
  EXPECT_EQ(display_format_packed_order::bgrx,
    get_packed_order(display_format::bgrx8888));
  EXPECT_EQ(display_format_packed_order::argb,
    get_packed_order(display_format::argb8888));
  EXPECT_EQ(display_format_packed_order::rgba,
    get_packed_order(display_format::rgba8888));
  EXPECT_EQ(display_format_packed_order::abgr,
    get_packed_order(display_format::abgr8888));
  EXPECT_EQ(display_format_packed_order::bgra,
    get_packed_order(display_format::bgra8888));
  EXPECT_EQ(display_format_packed_order::argb,
    get_packed_order(display_format::argb2101010));
  EXPECT_EQ(
    display_format_packed_order::none, get_packed_order(display_format::yv12));
  EXPECT_EQ(
    display_format_packed_order::xbgr, get_packed_order(display_format::iyuv));
  EXPECT_EQ(
    display_format_packed_order::none, get_packed_order(display_format::yuy2));
  EXPECT_EQ(
    display_format_packed_order::none, get_packed_order(display_format::uyvy));
  EXPECT_EQ(
    display_format_packed_order::xbgr, get_packed_order(display_format::yvyu));
  EXPECT_EQ(
    display_format_packed_order::none, get_packed_order(display_format::nv12));
  EXPECT_EQ(
    display_format_packed_order::none, get_packed_order(display_format::nv21));
}



TEST_F(test_display_format, get_array_order)
{
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::unknown));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::index1lsb));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::index1msb));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::index4lsb));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::index4msb));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::index8));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::rgb332));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::rgb444));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::rgb555));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::bgr555));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::argb4444));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::rgba4444));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::abgr4444));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::bgra4444));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::argb1555));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::rgba5551));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::abgr1555));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::bgra5551));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::rgb565));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::bgr565));
  EXPECT_EQ(
    display_format_array_order::rgb, get_array_order(display_format::rgb24));
  EXPECT_EQ(
    display_format_array_order::bgr, get_array_order(display_format::bgr24));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::rgb888));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::rgbx8888));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::bgr888));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::bgrx8888));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::argb8888));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::rgba8888));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::abgr8888));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::bgra8888));
  EXPECT_EQ(display_format_array_order::none,
    get_array_order(display_format::argb2101010));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::yv12));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::iyuv));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::yuy2));
  EXPECT_EQ(
    display_format_array_order::bgra, get_array_order(display_format::uyvy));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::yvyu));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::nv12));
  EXPECT_EQ(
    display_format_array_order::none, get_array_order(display_format::nv21));
}



TEST_F(test_display_format, get_packed_layout)
{
  EXPECT_EQ(display_format_packed_layout::none,
    get_packed_layout(display_format::unknown));
  EXPECT_EQ(display_format_packed_layout::none,
    get_packed_layout(display_format::index1lsb));
  EXPECT_EQ(display_format_packed_layout::none,
    get_packed_layout(display_format::index1msb));
  EXPECT_EQ(display_format_packed_layout::none,
    get_packed_layout(display_format::index4lsb));
  EXPECT_EQ(display_format_packed_layout::none,
    get_packed_layout(display_format::index4msb));
  EXPECT_EQ(display_format_packed_layout::none,
    get_packed_layout(display_format::index8));
  EXPECT_EQ(display_format_packed_layout::ev332,
    get_packed_layout(display_format::rgb332));
  EXPECT_EQ(display_format_packed_layout::ev4444,
    get_packed_layout(display_format::rgb444));
  EXPECT_EQ(display_format_packed_layout::ev1555,
    get_packed_layout(display_format::rgb555));
  EXPECT_EQ(display_format_packed_layout::ev1555,
    get_packed_layout(display_format::bgr555));
  EXPECT_EQ(display_format_packed_layout::ev4444,
    get_packed_layout(display_format::argb4444));
  EXPECT_EQ(display_format_packed_layout::ev4444,
    get_packed_layout(display_format::rgba4444));
  EXPECT_EQ(display_format_packed_layout::ev4444,
    get_packed_layout(display_format::abgr4444));
  EXPECT_EQ(display_format_packed_layout::ev4444,
    get_packed_layout(display_format::bgra4444));
  EXPECT_EQ(display_format_packed_layout::ev1555,
    get_packed_layout(display_format::argb1555));
  EXPECT_EQ(display_format_packed_layout::ev5551,
    get_packed_layout(display_format::rgba5551));
  EXPECT_EQ(display_format_packed_layout::ev1555,
    get_packed_layout(display_format::abgr1555));
  EXPECT_EQ(display_format_packed_layout::ev5551,
    get_packed_layout(display_format::bgra5551));
  EXPECT_EQ(display_format_packed_layout::ev565,
    get_packed_layout(display_format::rgb565));
  EXPECT_EQ(display_format_packed_layout::ev565,
    get_packed_layout(display_format::bgr565));
  EXPECT_EQ(display_format_packed_layout::none,
    get_packed_layout(display_format::rgb24));
  EXPECT_EQ(display_format_packed_layout::none,
    get_packed_layout(display_format::bgr24));
  EXPECT_EQ(display_format_packed_layout::ev8888,
    get_packed_layout(display_format::rgb888));
  EXPECT_EQ(display_format_packed_layout::ev8888,
    get_packed_layout(display_format::rgbx8888));
  EXPECT_EQ(display_format_packed_layout::ev8888,
    get_packed_layout(display_format::bgr888));
  EXPECT_EQ(display_format_packed_layout::ev8888,
    get_packed_layout(display_format::bgrx8888));
  EXPECT_EQ(display_format_packed_layout::ev8888,
    get_packed_layout(display_format::argb8888));
  EXPECT_EQ(display_format_packed_layout::ev8888,
    get_packed_layout(display_format::rgba8888));
  EXPECT_EQ(display_format_packed_layout::ev8888,
    get_packed_layout(display_format::abgr8888));
  EXPECT_EQ(display_format_packed_layout::ev8888,
    get_packed_layout(display_format::bgra8888));
  EXPECT_EQ(display_format_packed_layout::ev2101010,
    get_packed_layout(display_format::argb2101010));
  EXPECT_EQ(display_format_packed_layout::none,
    get_packed_layout(display_format::yv12));
  EXPECT_EQ(display_format_packed_layout::ev565,
    get_packed_layout(display_format::iyuv));
  EXPECT_EQ(display_format_packed_layout::none,
    get_packed_layout(display_format::yuy2));
  EXPECT_EQ(display_format_packed_layout::none,
    get_packed_layout(display_format::uyvy));
  EXPECT_EQ(
    display_format_packed_layout(9), get_packed_layout(display_format::yvyu));
  EXPECT_EQ(display_format_packed_layout::none,
    get_packed_layout(display_format::nv12));
  EXPECT_EQ(display_format_packed_layout::none,
    get_packed_layout(display_format::nv21));
}



TEST_F(test_display_format, is_indexed)
{
  EXPECT_FALSE(is_indexed(display_format::unknown));
  EXPECT_TRUE(is_indexed(display_format::index1lsb));
  EXPECT_TRUE(is_indexed(display_format::index1msb));
  EXPECT_TRUE(is_indexed(display_format::index4lsb));
  EXPECT_TRUE(is_indexed(display_format::index4msb));
  EXPECT_TRUE(is_indexed(display_format::index8));
  EXPECT_FALSE(is_indexed(display_format::rgb332));
  EXPECT_FALSE(is_indexed(display_format::rgb444));
  EXPECT_FALSE(is_indexed(display_format::rgb555));
  EXPECT_FALSE(is_indexed(display_format::bgr555));
  EXPECT_FALSE(is_indexed(display_format::argb4444));
  EXPECT_FALSE(is_indexed(display_format::rgba4444));
  EXPECT_FALSE(is_indexed(display_format::abgr4444));
  EXPECT_FALSE(is_indexed(display_format::bgra4444));
  EXPECT_FALSE(is_indexed(display_format::argb1555));
  EXPECT_FALSE(is_indexed(display_format::rgba5551));
  EXPECT_FALSE(is_indexed(display_format::abgr1555));
  EXPECT_FALSE(is_indexed(display_format::bgra5551));
  EXPECT_FALSE(is_indexed(display_format::rgb565));
  EXPECT_FALSE(is_indexed(display_format::bgr565));
  EXPECT_FALSE(is_indexed(display_format::rgb24));
  EXPECT_FALSE(is_indexed(display_format::bgr24));
  EXPECT_FALSE(is_indexed(display_format::rgb888));
  EXPECT_FALSE(is_indexed(display_format::rgbx8888));
  EXPECT_FALSE(is_indexed(display_format::bgr888));
  EXPECT_FALSE(is_indexed(display_format::bgrx8888));
  EXPECT_FALSE(is_indexed(display_format::argb8888));
  EXPECT_FALSE(is_indexed(display_format::rgba8888));
  EXPECT_FALSE(is_indexed(display_format::abgr8888));
  EXPECT_FALSE(is_indexed(display_format::bgra8888));
  EXPECT_FALSE(is_indexed(display_format::argb2101010));
  EXPECT_FALSE(is_indexed(display_format::yv12));
  EXPECT_FALSE(is_indexed(display_format::iyuv));
  EXPECT_FALSE(is_indexed(display_format::yuy2));
  EXPECT_FALSE(is_indexed(display_format::uyvy));
  EXPECT_FALSE(is_indexed(display_format::yvyu));
  EXPECT_FALSE(is_indexed(display_format::nv12));
  EXPECT_FALSE(is_indexed(display_format::nv21));
}



TEST_F(test_display_format, has_alpha)
{
  EXPECT_FALSE(has_alpha(display_format::unknown));
  EXPECT_FALSE(has_alpha(display_format::index1lsb));
  EXPECT_FALSE(has_alpha(display_format::index1msb));
  EXPECT_FALSE(has_alpha(display_format::index4lsb));
  EXPECT_FALSE(has_alpha(display_format::index4msb));
  EXPECT_FALSE(has_alpha(display_format::index8));
  EXPECT_FALSE(has_alpha(display_format::rgb332));
  EXPECT_FALSE(has_alpha(display_format::rgb444));
  EXPECT_FALSE(has_alpha(display_format::rgb555));
  EXPECT_FALSE(has_alpha(display_format::bgr555));
  EXPECT_TRUE(has_alpha(display_format::argb4444));
  EXPECT_TRUE(has_alpha(display_format::rgba4444));
  EXPECT_TRUE(has_alpha(display_format::abgr4444));
  EXPECT_TRUE(has_alpha(display_format::bgra4444));
  EXPECT_TRUE(has_alpha(display_format::argb1555));
  EXPECT_TRUE(has_alpha(display_format::rgba5551));
  EXPECT_TRUE(has_alpha(display_format::abgr1555));
  EXPECT_TRUE(has_alpha(display_format::bgra5551));
  EXPECT_FALSE(has_alpha(display_format::rgb565));
  EXPECT_FALSE(has_alpha(display_format::bgr565));
  EXPECT_FALSE(has_alpha(display_format::rgb24));
  EXPECT_FALSE(has_alpha(display_format::bgr24));
  EXPECT_FALSE(has_alpha(display_format::rgb888));
  EXPECT_FALSE(has_alpha(display_format::rgbx8888));
  EXPECT_FALSE(has_alpha(display_format::bgr888));
  EXPECT_FALSE(has_alpha(display_format::bgrx8888));
  EXPECT_TRUE(has_alpha(display_format::argb8888));
  EXPECT_TRUE(has_alpha(display_format::rgba8888));
  EXPECT_TRUE(has_alpha(display_format::abgr8888));
  EXPECT_TRUE(has_alpha(display_format::bgra8888));
  EXPECT_TRUE(has_alpha(display_format::argb2101010));
  EXPECT_FALSE(has_alpha(display_format::yv12));
  EXPECT_FALSE(has_alpha(display_format::iyuv));
  EXPECT_FALSE(has_alpha(display_format::yuy2));
  EXPECT_FALSE(has_alpha(display_format::uyvy));
  EXPECT_FALSE(has_alpha(display_format::yvyu));
  EXPECT_FALSE(has_alpha(display_format::nv12));
  EXPECT_FALSE(has_alpha(display_format::nv21));
}



TEST_F(test_display_format, is_fourcc)
{
  EXPECT_FALSE(is_fourcc(display_format::unknown));
  EXPECT_FALSE(is_fourcc(display_format::index1lsb));
  EXPECT_FALSE(is_fourcc(display_format::index1msb));
  EXPECT_FALSE(is_fourcc(display_format::index4lsb));
  EXPECT_FALSE(is_fourcc(display_format::index4msb));
  EXPECT_FALSE(is_fourcc(display_format::index8));
  EXPECT_FALSE(is_fourcc(display_format::rgb332));
  EXPECT_FALSE(is_fourcc(display_format::rgb444));
  EXPECT_FALSE(is_fourcc(display_format::rgb555));
  EXPECT_FALSE(is_fourcc(display_format::bgr555));
  EXPECT_FALSE(is_fourcc(display_format::argb4444));
  EXPECT_FALSE(is_fourcc(display_format::rgba4444));
  EXPECT_FALSE(is_fourcc(display_format::abgr4444));
  EXPECT_FALSE(is_fourcc(display_format::bgra4444));
  EXPECT_FALSE(is_fourcc(display_format::argb1555));
  EXPECT_FALSE(is_fourcc(display_format::rgba5551));
  EXPECT_FALSE(is_fourcc(display_format::abgr1555));
  EXPECT_FALSE(is_fourcc(display_format::bgra5551));
  EXPECT_FALSE(is_fourcc(display_format::rgb565));
  EXPECT_FALSE(is_fourcc(display_format::bgr565));
  EXPECT_FALSE(is_fourcc(display_format::rgb24));
  EXPECT_FALSE(is_fourcc(display_format::bgr24));
  EXPECT_FALSE(is_fourcc(display_format::rgb888));
  EXPECT_FALSE(is_fourcc(display_format::rgbx8888));
  EXPECT_FALSE(is_fourcc(display_format::bgr888));
  EXPECT_FALSE(is_fourcc(display_format::bgrx8888));
  EXPECT_FALSE(is_fourcc(display_format::argb8888));
  EXPECT_FALSE(is_fourcc(display_format::rgba8888));
  EXPECT_FALSE(is_fourcc(display_format::abgr8888));
  EXPECT_FALSE(is_fourcc(display_format::bgra8888));
  EXPECT_FALSE(is_fourcc(display_format::argb2101010));
  EXPECT_TRUE(is_fourcc(display_format::yv12));
  EXPECT_TRUE(is_fourcc(display_format::iyuv));
  EXPECT_TRUE(is_fourcc(display_format::yuy2));
  EXPECT_TRUE(is_fourcc(display_format::uyvy));
  EXPECT_TRUE(is_fourcc(display_format::yvyu));
  EXPECT_TRUE(is_fourcc(display_format::nv12));
  EXPECT_TRUE(is_fourcc(display_format::nv21));
}
