// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/test_sys_base.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/sys/file.hpp"
#include "hou/sys/image.hpp"
#include "hou/sys/image_file.hpp"
#include "hou/sys/sys_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_image_file : public test_sys_base
{
public:
  static const std::string test_image_bmp;
  static const std::string test_image_png;
  static const std::string test_image_jpg;
  static const std::string test_image_invalid;
};

using test_image_file_death_test = test_image_file;



const std::string test_image_file::test_image_bmp
  = get_data_dir() + u8"TestImage.bmp";

const std::string test_image_file::test_image_png
  = get_data_dir() + u8"TestImage.png";

const std::string test_image_file::test_image_jpg
  = get_data_dir() + u8"TestImage.jpg";

const std::string test_image_file::test_image_invalid
  = get_data_dir() + u8"TestImage.xcf";

}  // namespace



TEST_F(test_image_file, check_bmp)
{
  EXPECT_TRUE(bmp_image_file::check(test_image_bmp));
  EXPECT_FALSE(bmp_image_file::check(test_image_png));
  EXPECT_FALSE(bmp_image_file::check(test_image_jpg));
  EXPECT_FALSE(bmp_image_file::check(test_image_invalid));
}



TEST_F(test_image_file, check_png)
{
  EXPECT_TRUE(bmp_image_file::check(test_image_bmp));
  EXPECT_FALSE(bmp_image_file::check(test_image_png));
  EXPECT_FALSE(bmp_image_file::check(test_image_jpg));
  EXPECT_FALSE(bmp_image_file::check(test_image_invalid));
}



TEST_F(test_image_file, check_jpg)
{
  EXPECT_TRUE(bmp_image_file::check(test_image_bmp));
  EXPECT_FALSE(bmp_image_file::check(test_image_png));
  EXPECT_FALSE(bmp_image_file::check(test_image_jpg));
  EXPECT_FALSE(bmp_image_file::check(test_image_invalid));
}



TEST_F(test_image_file, load_bmp_rgba)
{
  // alpha channel in Bmp not supported.
  image2_rgba im_ref(vec2u(3u, 2u),
    std::vector<image2_rgba::pixel_type>{
      image2_rgba::pixel_type(50u, 100u, 150u, 255u),
      image2_rgba::pixel_type(150u, 100u, 50u, 255u),
      image2_rgba::pixel_type(255u, 200u, 50u, 255u),
      image2_rgba::pixel_type(50u, 100u, 150u, 255u),
      image2_rgba::pixel_type(0u, 255u, 255u, 255u),
      image2_rgba::pixel_type(255u, 200u, 50u, 255u),
    });
  image2_rgba im = bmp_image_file::read<pixel_format::rgba>(test_image_bmp);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_bmp_rgba_error)
{
  EXPECT_ERROR_0(bmp_image_file::read<pixel_format::rgba>(test_image_png),
    invalid_image_data);
}



TEST_F(test_image_file, load_png_rgba)
{
  image2_rgba im_ref(vec2u(3u, 2u),
    std::vector<image2_rgba::pixel_type>{
      image2_rgba::pixel_type(50u, 100u, 150u, 255u),
      image2_rgba::pixel_type(150u, 100u, 50u, 255u),
      image2_rgba::pixel_type(255u, 200u, 50u, 255u),
      image2_rgba::pixel_type(50u, 100u, 150u, 63u),
      image2_rgba::pixel_type(0u, 0u, 0u, 0u),
      image2_rgba::pixel_type(255u, 200u, 50u, 127u),
    });
  image2_rgba im = png_image_file::read<pixel_format::rgba>(test_image_png);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_png_rgba_error)
{
  EXPECT_ERROR_0(png_image_file::read<pixel_format::rgba>(test_image_jpg),
    invalid_image_data);
}



TEST_F(test_image_file, load_jpg_rgba)
{
  image2_rgba im_ref(vec2u(3u, 2u),
    std::vector<image2_rgba::pixel_type>{
      image2_rgba::pixel_type(72u, 86u, 133u, 255u),
      image2_rgba::pixel_type(134u, 111u, 80u, 255u),
      image2_rgba::pixel_type(252u, 204u, 46u, 255u),
      image2_rgba::pixel_type(189u, 225u, 247u, 255u),
      image2_rgba::pixel_type(255u, 253u, 240u, 255u),
      image2_rgba::pixel_type(255u, 232u, 139u, 255u),
    });
  image2_rgba im = jpg_image_file::read<pixel_format::rgba>(test_image_jpg);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_jpg_rgba_error)
{
  EXPECT_ERROR_0(jpg_image_file::read<pixel_format::rgba>(test_image_png),
    invalid_image_data);
}



TEST_F(test_image_file, save_bmp_rgba)
{
  const std::string save_path = get_output_dir() + "savedBmp.bmp";
  remove_dir(save_path);
  image2_rgba im_ref = bmp_image_file::read<pixel_format::rgba>(test_image_bmp);
  bmp_image_file::write(save_path, im_ref);
  image2_rgba im = bmp_image_file::read<pixel_format::rgba>(save_path);
  EXPECT_EQ(im_ref, im);
  EXPECT_TRUE(remove_dir(save_path));
}



TEST_F(test_image_file_death_test, save_bmp_error_rgba)
{
  const std::string save_path = get_output_dir() + "savedBmp.bmp";
  remove_dir(save_path);
  image2_rgba im_ref = bmp_image_file::read<pixel_format::rgba>(test_image_bmp);
  bmp_image_file::write(save_path, im_ref);
  EXPECT_ERROR_0(bmp_image_file::write<pixel_format::rgba>(save_path, im_ref),
    invalid_image_data);
  EXPECT_TRUE(remove_dir(save_path));
}



TEST_F(test_image_file, load_bmp_rgb)
{
  // alpha channel in Bmp not supported.
  image2_rgb im_ref(vec2u(3u, 2u),
    std::vector<image2_rgb::pixel_type>{
      image2_rgb::pixel_type(50u, 100u, 150u),
      image2_rgb::pixel_type(150u, 100u, 50u),
      image2_rgb::pixel_type(255u, 200u, 50u),
      image2_rgb::pixel_type(50u, 100u, 150u),
      image2_rgb::pixel_type(0u, 255u, 255u),
      image2_rgb::pixel_type(255u, 200u, 50u),
    });
  image2_rgb im = bmp_image_file::read<pixel_format::rgb>(test_image_bmp);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_bmp_rgb_error)
{
  EXPECT_ERROR_0(bmp_image_file::read<pixel_format::rgb>(test_image_png),
    invalid_image_data);
}



TEST_F(test_image_file, load_png_rgb)
{
  image2_rgb im_ref(vec2u(3u, 2u),
    std::vector<image2_rgb::pixel_type>{
      image2_rgb::pixel_type(50u, 100u, 150u),
      image2_rgb::pixel_type(150u, 100u, 50u),
      image2_rgb::pixel_type(255u, 200u, 50u),
      image2_rgb::pixel_type(50u, 100u, 150u),
      image2_rgb::pixel_type(0u, 0u, 0u),
      image2_rgb::pixel_type(255u, 200u, 50u),
    });
  image2_rgb im = png_image_file::read<pixel_format::rgb>(test_image_png);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_png_rgb_error)
{
  EXPECT_ERROR_0(png_image_file::read<pixel_format::rgb>(test_image_jpg),
    invalid_image_data);
}



TEST_F(test_image_file, load_jpg_rgb)
{
  image2_rgb im_ref(vec2u(3u, 2u),
    std::vector<image2_rgb::pixel_type>{
      image2_rgb::pixel_type(72u, 86u, 133u),
      image2_rgb::pixel_type(134u, 111u, 80u),
      image2_rgb::pixel_type(252u, 204u, 46u),
      image2_rgb::pixel_type(189u, 225u, 247u),
      image2_rgb::pixel_type(255u, 253u, 240u),
      image2_rgb::pixel_type(255u, 232u, 139u),
    });
  image2_rgb im = jpg_image_file::read<pixel_format::rgb>(test_image_jpg);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_jpg_rgb_error)
{
  EXPECT_ERROR_0(jpg_image_file::read<pixel_format::rgb>(test_image_png),
    invalid_image_data);
}



TEST_F(test_image_file, load_bmp_rg)
{
  // alpha channel in Bmp not supported.
  image2_rg im_ref(vec2u(3u, 2u),
    std::vector<image2_rg::pixel_type>{
      image2_rg::pixel_type(90u, 255u),
      image2_rg::pixel_type(109u, 255u),
      image2_rg::pixel_type(199u, 255u),
      image2_rg::pixel_type(90u, 255u),
      image2_rg::pixel_type(178u, 255u),
      image2_rg::pixel_type(199u, 255u),
    });
  image2_rg im = bmp_image_file::read<pixel_format::rg>(test_image_bmp);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_bmp_rg_error)
{
  EXPECT_ERROR_0(
    bmp_image_file::read<pixel_format::rg>(test_image_png), invalid_image_data);
}



TEST_F(test_image_file, load_png_rg)
{
  image2_rg im_ref(vec2u(3u, 2u),
    std::vector<image2_rg::pixel_type>{
      image2_rg::pixel_type(90u, 255u),
      image2_rg::pixel_type(109u, 255u),
      image2_rg::pixel_type(199u, 255u),
      image2_rg::pixel_type(90u, 63u),
      image2_rg::pixel_type(0u, 0u),
      image2_rg::pixel_type(199u, 127u),
    });
  image2_rg im = png_image_file::read<pixel_format::rg>(test_image_png);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_png_rg_error)
{
  EXPECT_ERROR_0(
    png_image_file::read<pixel_format::rg>(test_image_jpg), invalid_image_data);
}



TEST_F(test_image_file, load_jpg_rg)
{
  image2_rg im_ref(vec2u(3u, 2u),
    std::vector<image2_rg::pixel_type>{
      image2_rg::pixel_type(87u, 255u),
      image2_rg::pixel_type(114u, 255u),
      image2_rg::pixel_type(200u, 255u),
      image2_rg::pixel_type(217u, 255u),
      image2_rg::pixel_type(252u, 255u),
      image2_rg::pixel_type(231u, 255u),
    });
  image2_rg im = jpg_image_file::read<pixel_format::rg>(test_image_jpg);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_jpg_rg_error)
{
  EXPECT_ERROR_0(
    jpg_image_file::read<pixel_format::rg>(test_image_png), invalid_image_data);
}



TEST_F(test_image_file, load_bmp_r)
{
  // alpha channel in Bmp not supported.
  image2_r im_ref(vec2u(3u, 2u),
    std::vector<image2_r::pixel_type>{
      image2_r::pixel_type(90u),
      image2_r::pixel_type(109u),
      image2_r::pixel_type(199u),
      image2_r::pixel_type(90u),
      image2_r::pixel_type(178u),
      image2_r::pixel_type(199u),
    });
  image2_r im = bmp_image_file::read<pixel_format::r>(test_image_bmp);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_bmp_r_error)
{
  EXPECT_ERROR_0(
    bmp_image_file::read<pixel_format::r>(test_image_png), invalid_image_data);
}



TEST_F(test_image_file, load_png_r)
{
  image2_r im_ref(vec2u(3u, 2u),
    std::vector<image2_r::pixel_type>{
      image2_r::pixel_type(90u),
      image2_r::pixel_type(109u),
      image2_r::pixel_type(199u),
      image2_r::pixel_type(90u),
      image2_r::pixel_type(0u),
      image2_r::pixel_type(199u),
    });
  image2_r im = png_image_file::read<pixel_format::r>(test_image_png);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_png_r_error)
{
  EXPECT_ERROR_0(
    png_image_file::read<pixel_format::r>(test_image_jpg), invalid_image_data);
}



TEST_F(test_image_file, load_jpg_r)
{
  image2_r im_ref(vec2u(3u, 2u),
    std::vector<image2_r::pixel_type>{
      image2_r::pixel_type(87u),
      image2_r::pixel_type(114u),
      image2_r::pixel_type(200u),
      image2_r::pixel_type(217u),
      image2_r::pixel_type(252u),
      image2_r::pixel_type(231u),
    });
  image2_r im = jpg_image_file::read<pixel_format::r>(test_image_jpg);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_jpg_r_error)
{
  EXPECT_ERROR_0(
    jpg_image_file::read<pixel_format::r>(test_image_png), invalid_image_data);
}
