// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/sys/file.hpp"
#include "hou/sys/image.hpp"
#include "hou/sys/sys_exceptions.hpp"

using namespace hou;
using namespace testing;


namespace
{

template <typename ImageT>
class test_image : public Test
{
public:
  static typename ImageT::size_type generate_size();
  static typename ImageT::pixel_collection generate_pixels(
    const typename ImageT::size_type& size);
  static size_t multiply_elements(const typename ImageT::size_type& size);
  static size_t compute_pixel_index(
    const typename ImageT::offset_type& coordinates,
    const typename ImageT::size_type& size);
  static typename ImageT::offset_type compute_pixel_coordinates(
    size_t index, const typename ImageT::size_type& size);
};

template <typename ImageT>
class test_image_death_test : public test_image<ImageT>
{};

using image_types
  = Types<image1_r, image2_r, image3_r, image1_rg, image2_rg, image3_rg,
    image1_rgb, image2_rgb, image3_rgb, image1_rgba, image2_rgba, image3_rgba>;

class test_image_class_attributes : public Test
{};

class test_image_conversion_constructor : public Test
{};

class test_image_file : public Test
{
public:
  static const std::string test_image_bmp;
  static const std::string test_image_png;
  static const std::string test_image_jpg;
  static const std::string test_image_invalid;
};

class test_image_file_death_test : public test_image_file
{};



template <>
typename image1_r::size_type test_image<image1_r>::generate_size()
{
  return vec1u{4u};
}



template <>
typename image1_rg::size_type test_image<image1_rg>::generate_size()
{
  return vec1u{4u};
}



template <>
typename image1_rgb::size_type test_image<image1_rgb>::generate_size()
{
  return vec1u{4u};
}



template <>
typename image1_rgba::size_type test_image<image1_rgba>::generate_size()
{
  return vec1u{4u};
}



template <>
typename image2_r::size_type test_image<image2_r>::generate_size()
{
  return vec2u{4u, 7u};
}



template <>
typename image2_rg::size_type test_image<image2_rg>::generate_size()
{
  return vec2u{4u, 7u};
}



template <>
typename image2_rgb::size_type test_image<image2_rgb>::generate_size()
{
  return vec2u{4u, 7u};
}



template <>
typename image2_rgba::size_type test_image<image2_rgba>::generate_size()
{
  return vec2u{4u, 7u};
}



template <>
typename image3_r::size_type test_image<image3_r>::generate_size()
{
  return vec3u{4u, 7u, 11u};
}



template <>
typename image3_rg::size_type test_image<image3_rg>::generate_size()
{
  return vec3u{4u, 7u, 11u};
}



template <>
typename image3_rgb::size_type test_image<image3_rgb>::generate_size()
{
  return vec3u{4u, 7u, 11u};
}



template <>
typename image3_rgba::size_type test_image<image3_rgba>::generate_size()
{
  return vec3u{4u, 7u, 11u};
}



template <typename ImageT>
typename ImageT::pixel_collection test_image<ImageT>::generate_pixels(
  const typename ImageT::size_type& size)
{
  typename ImageT::pixel_collection retval(multiply_elements(size));
  for(size_t i = 0; i < retval.size(); ++i)
  {
    typename ImageT::pixel px;
    px.set_r(i);
    retval[i] = px;
  }
  return retval;
}



template <typename ImageT>
size_t test_image<ImageT>::multiply_elements(
  const typename ImageT::size_type& size)
{
  size_t retval = size(0);
  for(size_t i = 1; i < size.get_size(); ++i)
  {
    retval *= size(i);
  }
  return retval;
}



template <typename ImageT>
size_t test_image<ImageT>::compute_pixel_index(
  const typename ImageT::offset_type& coordinates,
  const typename ImageT::size_type& size)
{
  size_t idx = 0;
  size_t multiplier = 1;
  for(size_t i = 0; i < coordinates.get_size(); ++i)
  {
    idx += coordinates(i) * multiplier;
    multiplier *= size(i);
  }
  return idx;
}



template <typename ImageT>
typename ImageT::offset_type test_image<ImageT>::compute_pixel_coordinates(
  size_t index, const typename ImageT::size_type& size)
{
  using offset_type = typename ImageT::offset_type;

  offset_type coords;
  size_t divider = multiply_elements(size);
  for(size_t i = size.get_size() - 1; i > 0; --i)
  {
    divider /= size(i);
    coords(i) = index / divider;
    index %= divider;
  }
  coords(0) = index;
  return coords;
}



const std::string test_image_file::test_image_bmp
  = get_data_dir() + u8"TestImage.bmp";
const std::string test_image_file::test_image_png
  = get_data_dir() + u8"TestImage.png";
const std::string test_image_file::test_image_jpg
  = get_data_dir() + u8"TestImage.jpg";
const std::string test_image_file::test_image_invalid
  = get_data_dir() + u8"TestImage.xcf";

}  // namespace



TYPED_TEST_CASE(test_image, image_types);
TYPED_TEST_CASE(test_image_death_test, image_types);



TYPED_TEST(test_image, get_pixel_byte_count)
{
  EXPECT_EQ(
    TypeParam::pixel::get_byte_count(), TypeParam::get_pixel_byte_count());
}



TYPED_TEST(test_image, default_constructor)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  TypeParam image;
  EXPECT_EQ(size_type::zero(), image.get_size());
  EXPECT_EQ(pixel_collection(), image.get_pixels());
}



TYPED_TEST(test_image, size_constructor)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  TypeParam image(size_ref);
  EXPECT_EQ(size_ref, image.get_size());
  EXPECT_EQ(pixel_collection(TestFixture::multiply_elements(size_ref)),
    image.get_pixels());
}



TYPED_TEST(test_image, pixel_constructor)
{
  using size_type = typename TypeParam::size_type;
  using pixel = typename TypeParam::pixel;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel pixel_ref;
  pixel_ref.set_r(5u);
  pixel_collection pixels_ref(
    TestFixture::multiply_elements(size_ref), pixel_ref);
  TypeParam image(size_ref, pixel_ref);

  EXPECT_EQ(size_ref, image.get_size());
  EXPECT_EQ(pixels_ref, image.get_pixels());
}



TYPED_TEST(test_image, pixels_constructor)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref = TestFixture::generate_pixels(size_ref);
  TypeParam image(size_ref, pixels_ref);

  EXPECT_EQ(size_ref, image.get_size());
  EXPECT_EQ(pixels_ref, image.get_pixels());
}



TYPED_TEST(test_image_death_test, pixels_constructor_error_too_few_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) - 1u);
  EXPECT_PRECOND_ERROR(TypeParam image(size_ref, pixels_ref));
}



TYPED_TEST(test_image_death_test, pixels_constructor_error_too_many_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) + 1u);
  EXPECT_PRECOND_ERROR(TypeParam image(size_ref, pixels_ref));
}



TYPED_TEST(test_image, pixels_move_constructor)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref = TestFixture::generate_pixels(size_ref);
  pixel_collection pixels(pixels_ref);
  TypeParam image(size_ref, std::move(pixels));

  EXPECT_EQ(size_ref, image.get_size());
  EXPECT_EQ(pixels_ref, image.get_pixels());
}



TYPED_TEST(test_image_death_test, pixels_move_constructor_error_too_few_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) - 1u);
  EXPECT_PRECOND_ERROR(TypeParam image(size_ref, std::move(pixels_ref)));
}



TYPED_TEST(test_image_death_test, pixels_move_constructor_error_too_many_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) + 1u);
  EXPECT_PRECOND_ERROR(TypeParam image(size_ref, std::move(pixels_ref)));
}



TYPED_TEST(test_image, set_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref = TestFixture::generate_pixels(size_ref);
  TypeParam image(size_ref);
  image.set_pixels(pixels_ref);
  EXPECT_EQ(pixels_ref, image.get_pixels());
}



TYPED_TEST(test_image_death_test, set_pixels_error_too_few_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) - 1u);
  TypeParam image(size_ref);
  EXPECT_PRECOND_ERROR(image.set_pixels(pixels_ref));
}



TYPED_TEST(test_image_death_test, set_pixels_error_too_many_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) + 1u);
  TypeParam image(size_ref);
  EXPECT_PRECOND_ERROR(image.set_pixels(pixels_ref));
}



TYPED_TEST(test_image, get_pixel)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref = TestFixture::generate_pixels(size_ref);
  TypeParam image(size_ref, pixels_ref);

  for(size_t i = 0; i < pixels_ref.size(); ++i)
  {
    EXPECT_EQ(pixels_ref[i],
      image.get_pixel(
        TestFixture::compute_pixel_coordinates(i, image.get_size())));
  }
}



TYPED_TEST(test_image_death_test, get_pixel_error_out_of_range)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type size_ref = TestFixture::generate_size();
  TypeParam image(size_ref);

  for(size_t i = 0; i < size_ref.get_size(); ++i)
  {
    offset_type coords;
    coords(i) = size_ref(i);
    EXPECT_ERROR_0(image.get_pixel(coords), out_of_range);
  }
  EXPECT_ERROR_0(image.get_pixel(size_ref), out_of_range);
}



TYPED_TEST(test_image, set_pixel)
{
  using size_type = typename TypeParam::size_type;
  using pixel = typename TypeParam::pixel;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel pixel_ref;
  pixel_ref.set_r(42u);
  for(size_t i = 0; i < TestFixture::multiply_elements(size_ref); ++i)
  {
    TypeParam image(size_ref);
    pixel_collection pixels_ref = image.get_pixels();
    pixels_ref[i] = pixel_ref;
    image.set_pixel(
      TestFixture::compute_pixel_coordinates(i, image.get_size()), pixel_ref);
    EXPECT_EQ(pixels_ref[i],
      image.get_pixel(
        TestFixture::compute_pixel_coordinates(i, image.get_size())));
  }
}



TYPED_TEST(test_image_death_test, set_pixel_error_out_of_range)
{
  using size_type = typename TypeParam::size_type;
  using pixel = typename TypeParam::pixel;
  using offset_type = typename TypeParam::offset_type;

  size_type size_ref = TestFixture::generate_size();
  TypeParam image(size_ref);

  pixel pixel_ref;
  for(size_t i = 0; i < size_ref.get_size(); ++i)
  {
    offset_type coords;
    coords(i) = size_ref(i);
    EXPECT_ERROR_0(image.set_pixel(coords, pixel_ref), out_of_range);
  }
  EXPECT_ERROR_0(image.set_pixel(size_ref, pixel_ref), out_of_range);
}



TYPED_TEST(test_image, get_sub_image)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type imageSize;
  size_type sub_image_size;
  offset_type sub_image_offset;
  for(size_t i = 0; i < imageSize.get_size(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    sub_image_size(i) = (i + 1) * 2;
    sub_image_offset(i) = i + 1;
  }

  pixel_collection pixels_ref = TestFixture::generate_pixels(imageSize);
  pixel_collection subPixels_ref(
    TestFixture::multiply_elements(sub_image_size));
  for(size_t i = 0; i < subPixels_ref.size(); ++i)
  {
    offset_type subImageCoords
      = TestFixture::compute_pixel_coordinates(i, sub_image_size);
    offset_type imageCoords = sub_image_offset + subImageCoords;
    subPixels_ref[i]
      = pixels_ref[TestFixture::compute_pixel_index(imageCoords, imageSize)];
  }

  TypeParam image(imageSize, pixels_ref);
  TypeParam sub_image_ref(sub_image_size, subPixels_ref);
  EXPECT_EQ(
    sub_image_ref, image.get_sub_image(sub_image_offset, sub_image_size));
}



TYPED_TEST(test_image_death_test, get_sub_image_error_overflow)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type imageSize;
  size_type sub_image_size;
  offset_type sub_image_offset;
  for(size_t i = 0; i < imageSize.get_size(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    sub_image_offset(i) = i + 1;
    sub_image_size(i) = (i + 1) * 4 - sub_image_offset(i) + 1u;
  }

  TypeParam image(imageSize);
  EXPECT_ERROR_0(
    image.get_sub_image(sub_image_offset, sub_image_size), out_of_range);
}



TYPED_TEST(test_image, set_sub_image)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type imageSize;
  size_type sub_image_size;
  offset_type sub_image_offset;
  for(size_t i = 0; i < imageSize.get_size(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    sub_image_size(i) = (i + 1) * 2;
    sub_image_offset(i) = i + 1;
  }

  pixel_collection pixels_ref(TestFixture::multiply_elements(imageSize));
  pixel_collection subPixels_ref(TestFixture::generate_pixels(sub_image_size));
  for(size_t i = 0; i < subPixels_ref.size(); ++i)
  {
    offset_type subImageCoords
      = TestFixture::compute_pixel_coordinates(i, sub_image_size);
    offset_type imageCoords = sub_image_offset + subImageCoords;
    pixels_ref[TestFixture::compute_pixel_index(imageCoords, imageSize)]
      = subPixels_ref[i];
  }

  TypeParam image(imageSize);
  TypeParam image_ref(imageSize, pixels_ref);
  TypeParam sub_image_ref(sub_image_size, subPixels_ref);
  image.set_sub_image(sub_image_offset, sub_image_ref);

  EXPECT_EQ(image_ref, image);
  EXPECT_EQ(
    sub_image_ref, image.get_sub_image(sub_image_offset, sub_image_size));
}



TYPED_TEST(test_image_death_test, set_sub_image_error_overflow)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type imageSize;
  size_type sub_image_size;
  offset_type sub_image_offset;
  for(size_t i = 0; i < imageSize.get_size(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    sub_image_offset(i) = i + 1;
    sub_image_size(i) = (i + 1) * 4 - sub_image_offset(i) + 1u;
  }

  TypeParam image(imageSize);
  TypeParam subImage(sub_image_size);
  EXPECT_ERROR_0(image.set_sub_image(sub_image_offset, subImage), out_of_range);
}



TYPED_TEST(test_image, clear)
{
  using size_type = typename TypeParam::size_type;
  using pixel = typename TypeParam::pixel;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  TypeParam image(size_ref);

  pixel pixel_ref;
  pixel_ref.set_r(42u);

  pixel_collection pixels_ref(
    TestFixture::multiply_elements(size_ref), pixel_ref);
  image.clear(pixel_ref);
  EXPECT_EQ(pixels_ref, image.get_pixels());
}



TYPED_TEST(test_image, comparison)
{
  using size_type = typename TypeParam::size_type;
  using pixel = typename TypeParam::pixel;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size1 = TestFixture::generate_size();
  size_type size2 = size1 * 2;
  pixel pixel1;
  pixel1.set_r(42);
  pixel pixel2;
  pixel2.set_r(88);
  pixel_collection pixels11(TestFixture::multiply_elements(size1), pixel1);
  pixel_collection pixels12(TestFixture::multiply_elements(size1), pixel2);
  pixel_collection pixels22(TestFixture::multiply_elements(size2), pixel2);

  TypeParam im0(size1, pixels11);
  TypeParam im1(im0);
  TypeParam im2(size1, pixels12);
  TypeParam im3(size2, pixels22);

  EXPECT_TRUE(im0 == im1);
  EXPECT_FALSE(im0 == im2);
  EXPECT_FALSE(im0 == im3);

  EXPECT_FALSE(im0 != im1);
  EXPECT_TRUE(im0 != im2);
  EXPECT_TRUE(im0 != im3);
}



TYPED_TEST(test_image, output_stream_operator)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref = TestFixture::generate_pixels(size_ref);

  TypeParam image(size_ref, pixels_ref);

  std::stringstream ss;
  ss << "{size_type = " << transpose(size_ref) << ", pixels = " << pixels_ref
     << "}";

  EXPECT_OUTPUT(ss.str().c_str(), image);
}



TEST_F(test_image_class_attributes, get_dimension_count)
{
  EXPECT_EQ(1u, image1_r::get_dimension_count());
  EXPECT_EQ(1u, image1_rg::get_dimension_count());
  EXPECT_EQ(1u, image1_rgb::get_dimension_count());
  EXPECT_EQ(1u, image1_rgba::get_dimension_count());
  EXPECT_EQ(2u, image2_r::get_dimension_count());
  EXPECT_EQ(2u, image2_rg::get_dimension_count());
  EXPECT_EQ(2u, image2_rgb::get_dimension_count());
  EXPECT_EQ(2u, image2_rgba::get_dimension_count());
  EXPECT_EQ(3u, image3_r::get_dimension_count());
  EXPECT_EQ(3u, image3_rg::get_dimension_count());
  EXPECT_EQ(3u, image3_rgb::get_dimension_count());
  EXPECT_EQ(3u, image3_rgba::get_dimension_count());
}



TEST_F(test_image_class_attributes, get_pixel_format)
{
  EXPECT_EQ(pixel_format::r, image1_r::get_pixel_format());
  EXPECT_EQ(pixel_format::rg, image1_rg::get_pixel_format());
  EXPECT_EQ(pixel_format::rgb, image1_rgb::get_pixel_format());
  EXPECT_EQ(pixel_format::rgba, image1_rgba::get_pixel_format());
  EXPECT_EQ(pixel_format::r, image2_r::get_pixel_format());
  EXPECT_EQ(pixel_format::rg, image2_rg::get_pixel_format());
  EXPECT_EQ(pixel_format::rgb, image2_rgb::get_pixel_format());
  EXPECT_EQ(pixel_format::rgba, image2_rgba::get_pixel_format());
  EXPECT_EQ(pixel_format::r, image3_r::get_pixel_format());
  EXPECT_EQ(pixel_format::rg, image3_rg::get_pixel_format());
  EXPECT_EQ(pixel_format::rgb, image3_rgb::get_pixel_format());
  EXPECT_EQ(pixel_format::rgba, image3_rgba::get_pixel_format());
}



TEST_F(test_image_conversion_constructor, r2_rgba_constructor)
{
  image2_r::size_type size(2u, 3u);
  image2_r::pixel_collection pixelsR{
    image2_r::pixel(1u),
    image2_r::pixel(2u),
    image2_r::pixel(3u),
    image2_r::pixel(4u),
    image2_r::pixel(5u),
    image2_r::pixel(6u),
  };

  image2_rgba::pixel_collection pixelsRGBA{
    image2_rgba::pixel(1u, 1u, 1u, 255u),
    image2_rgba::pixel(2u, 2u, 2u, 255u),
    image2_rgba::pixel(3u, 3u, 3u, 255u),
    image2_rgba::pixel(4u, 4u, 4u, 255u),
    image2_rgba::pixel(5u, 5u, 5u, 255u),
    image2_rgba::pixel(6u, 6u, 6u, 255u),
  };

  image2_r imageR(size, pixelsR);
  image2_rgba imageRGBA(imageR);

  EXPECT_EQ(size, imageRGBA.get_size());
  EXPECT_EQ(pixelsRGBA, imageRGBA.get_pixels());
}



TEST_F(test_image_conversion_constructor, rg2_rgba_constructor)
{
  image2_rg::size_type size(2u, 3u);
  image2_rg::pixel_collection pixelsRG{
    image2_rg::pixel(1u, 11u),
    image2_rg::pixel(2u, 12u),
    image2_rg::pixel(3u, 13u),
    image2_rg::pixel(4u, 14u),
    image2_rg::pixel(5u, 15u),
    image2_rg::pixel(6u, 16u),
  };

  image2_rgba::pixel_collection pixelsRGBA{
    image2_rgba::pixel(1u, 1u, 1u, 11u),
    image2_rgba::pixel(2u, 2u, 2u, 12u),
    image2_rgba::pixel(3u, 3u, 3u, 13u),
    image2_rgba::pixel(4u, 4u, 4u, 14u),
    image2_rgba::pixel(5u, 5u, 5u, 15u),
    image2_rgba::pixel(6u, 6u, 6u, 16u),
  };

  image2_rg imageRG(size, pixelsRG);
  image2_rgba imageRGBA(imageRG);

  EXPECT_EQ(size, imageRGBA.get_size());
  EXPECT_EQ(pixelsRGBA, imageRGBA.get_pixels());
}



TEST_F(test_image_conversion_constructor, rgb2_rgba_constructor)
{
  image2_rgb::size_type size(2u, 3u);
  image2_rgb::pixel_collection pixelsRGB{
    image2_rgb::pixel(200u, 118u, 93u),
    image2_rgb::pixel(3u, 12u, 3u),
    image2_rgb::pixel(5u, 11u, 2u),
    image2_rgb::pixel(200u, 100u, 0u),
    image2_rgb::pixel(0u, 21u, 0u),
    image2_rgb::pixel(100u, 20u, 0u),
  };

  image2_rgba::pixel_collection pixelsRGBA{
    image2_rgba::pixel(200u, 118u, 93u, 255u),
    image2_rgba::pixel(3u, 12u, 3u, 255u),
    image2_rgba::pixel(5u, 11u, 2u, 255u),
    image2_rgba::pixel(200u, 100u, 0u, 255u),
    image2_rgba::pixel(0u, 21u, 0u, 255u),
    image2_rgba::pixel(100u, 20u, 0u, 255u),
  };

  image2_rgb imageRGB(size, pixelsRGB);
  image2_rgba imageRGBA(imageRGB);

  EXPECT_EQ(size, imageRGBA.get_size());
  EXPECT_EQ(pixelsRGBA, imageRGBA.get_pixels());
}



TEST_F(test_image_conversion_constructor, image1_to_image2_constructor)
{
  image1_rgb::size_type size(3u);
  image1_rgba::pixel_collection pixelsRGBA{
    image1_rgba::pixel(200u, 118u, 93u, 255u),
    image1_rgba::pixel(3u, 12u, 3u, 255u),
    image1_rgba::pixel(5u, 11u, 2u, 255u),
  };
  image1_rgba image1_rgba(size, pixelsRGBA);
  image2_rgba image2_rgba(image1_rgba);
  EXPECT_EQ(vec2u(size.x(), 1u), image2_rgba.get_size());
  EXPECT_EQ(pixelsRGBA, image2_rgba.get_pixels());
}



TEST_F(test_image_conversion_constructor, image1_to_image3_constructor)
{
  image1_rgb::size_type size(3u);
  image1_rgba::pixel_collection pixelsRGBA{
    image1_rgba::pixel(200u, 118u, 93u, 255u),
    image1_rgba::pixel(3u, 12u, 3u, 255u),
    image1_rgba::pixel(5u, 11u, 2u, 255u),
  };
  image1_rgba image1_rgba(size, pixelsRGBA);
  image3_rgba image3_rgba(image1_rgba);
  EXPECT_EQ(vec3u(size.x(), 1u, 1u), image3_rgba.get_size());
  EXPECT_EQ(pixelsRGBA, image3_rgba.get_pixels());
}



TEST_F(test_image_conversion_constructor, image2_to_image3_constructor)
{
  image2_rgb::size_type size(3u, 2u);
  image2_rgba::pixel_collection pixelsRGBA{
    image2_rgba::pixel(200u, 118u, 93u, 255u),
    image2_rgba::pixel(3u, 12u, 3u, 255u),
    image2_rgba::pixel(5u, 11u, 2u, 255u),
    image2_rgba::pixel(200u, 118u, 93u, 255u),
    image2_rgba::pixel(3u, 12u, 3u, 255u),
    image2_rgba::pixel(5u, 11u, 2u, 255u),
  };
  image2_rgba image1_rgba(size, pixelsRGBA);
  image3_rgba image3_rgba(image1_rgba);
  EXPECT_EQ(vec3u(size.x(), size.y(), 1u), image3_rgba.get_size());
  EXPECT_EQ(pixelsRGBA, image3_rgba.get_pixels());
}



TEST_F(test_image_file, load_bmp_rgba)
{
  // alpha channel in Bmp not supported.
  image2_rgba im_ref(vec2u(3u, 2u),
    std::vector<image2_rgba::pixel>{
      image2_rgba::pixel(50u, 100u, 150u, 255u),
      image2_rgba::pixel(150u, 100u, 50u, 255u),
      image2_rgba::pixel(255u, 200u, 50u, 255u),
      image2_rgba::pixel(50u, 100u, 150u, 255u),
      image2_rgba::pixel(0u, 255u, 255u, 255u),
      image2_rgba::pixel(255u, 200u, 50u, 255u),
    });
  image2_rgba im = bmp_read_file<pixel_format::rgba>(test_image_bmp);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_bmp_rgba_error)
{
  EXPECT_ERROR_0(
    bmp_read_file<pixel_format::rgba>(test_image_png), invalid_image_data);
}



TEST_F(test_image_file, load_png_rgba)
{
  image2_rgba im_ref(vec2u(3u, 2u),
    std::vector<image2_rgba::pixel>{
      image2_rgba::pixel(50u, 100u, 150u, 255u),
      image2_rgba::pixel(150u, 100u, 50u, 255u),
      image2_rgba::pixel(255u, 200u, 50u, 255u),
      image2_rgba::pixel(50u, 100u, 150u, 63u),
      image2_rgba::pixel(0u, 0u, 0u, 0u),
      image2_rgba::pixel(255u, 200u, 50u, 127u),
    });
  image2_rgba im = png_read_file<pixel_format::rgba>(test_image_png);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_png_rgba_error)
{
  EXPECT_ERROR_0(
    png_read_file<pixel_format::rgba>(test_image_jpg), invalid_image_data);
}



TEST_F(test_image_file, load_jpg_rgba)
{
  image2_rgba im_ref(vec2u(3u, 2u),
    std::vector<image2_rgba::pixel>{
      image2_rgba::pixel(72u, 86u, 133u, 255u),
      image2_rgba::pixel(134u, 111u, 80u, 255u),
      image2_rgba::pixel(252u, 204u, 46u, 255u),
      image2_rgba::pixel(189u, 225u, 247u, 255u),
      image2_rgba::pixel(255u, 253u, 240u, 255u),
      image2_rgba::pixel(255u, 232u, 139u, 255u),
    });
  image2_rgba im = jpg_read_file<pixel_format::rgba>(test_image_jpg);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_jpg_rgba_error)
{
  EXPECT_ERROR_0(
    jpg_read_file<pixel_format::rgba>(test_image_png), invalid_image_data);
}



TEST_F(test_image_file, save_bmp_rgba)
{
  const std::string save_path = get_output_dir() + "savedBmp.bmp";
  remove_dir(save_path);
  image2_rgba im_ref = bmp_read_file<pixel_format::rgba>(test_image_bmp);
  bmp_write_file(save_path, im_ref);
  image2_rgba im = bmp_read_file<pixel_format::rgba>(save_path);
  EXPECT_EQ(im_ref, im);
  EXPECT_TRUE(remove_dir(save_path));
}



TEST_F(test_image_file_death_test, save_bmp_error_rgba)
{
  const std::string save_path = get_output_dir() + "savedBmp.bmp";
  remove_dir(save_path);
  image2_rgba im_ref = bmp_read_file<pixel_format::rgba>(test_image_bmp);
  bmp_write_file(save_path, im_ref);
  EXPECT_ERROR_0(
    bmp_write_file<pixel_format::rgba>(save_path, im_ref), invalid_image_data);
  EXPECT_TRUE(remove_dir(save_path));
}



TEST_F(test_image_file, load_bmp_rgb)
{
  // alpha channel in Bmp not supported.
  image2_rgb im_ref(vec2u(3u, 2u),
    std::vector<image2_rgb::pixel>{
      image2_rgb::pixel(50u, 100u, 150u),
      image2_rgb::pixel(150u, 100u, 50u),
      image2_rgb::pixel(255u, 200u, 50u),
      image2_rgb::pixel(50u, 100u, 150u),
      image2_rgb::pixel(0u, 255u, 255u),
      image2_rgb::pixel(255u, 200u, 50u),
    });
  image2_rgb im = bmp_read_file<pixel_format::rgb>(test_image_bmp);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_bmp_rgb_error)
{
  EXPECT_ERROR_0(
    bmp_read_file<pixel_format::rgb>(test_image_png), invalid_image_data);
}



TEST_F(test_image_file, load_png_rgb)
{
  image2_rgb im_ref(vec2u(3u, 2u),
    std::vector<image2_rgb::pixel>{
      image2_rgb::pixel(50u, 100u, 150u),
      image2_rgb::pixel(150u, 100u, 50u),
      image2_rgb::pixel(255u, 200u, 50u),
      image2_rgb::pixel(50u, 100u, 150u),
      image2_rgb::pixel(0u, 0u, 0u),
      image2_rgb::pixel(255u, 200u, 50u),
    });
  image2_rgb im = png_read_file<pixel_format::rgb>(test_image_png);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_png_rgb_error)
{
  EXPECT_ERROR_0(
    png_read_file<pixel_format::rgb>(test_image_jpg), invalid_image_data);
}



TEST_F(test_image_file, load_jpg_rgb)
{
  image2_rgb im_ref(vec2u(3u, 2u),
    std::vector<image2_rgb::pixel>{
      image2_rgb::pixel(72u, 86u, 133u),
      image2_rgb::pixel(134u, 111u, 80u),
      image2_rgb::pixel(252u, 204u, 46u),
      image2_rgb::pixel(189u, 225u, 247u),
      image2_rgb::pixel(255u, 253u, 240u),
      image2_rgb::pixel(255u, 232u, 139u),
    });
  image2_rgb im = jpg_read_file<pixel_format::rgb>(test_image_jpg);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_jpg_rgb_error)
{
  EXPECT_ERROR_0(
    jpg_read_file<pixel_format::rgb>(test_image_png), invalid_image_data);
}



TEST_F(test_image_file, load_bmp_rg)
{
  // alpha channel in Bmp not supported.
  image2_rg im_ref(vec2u(3u, 2u),
    std::vector<image2_rg::pixel>{
      image2_rg::pixel(90u, 255u),
      image2_rg::pixel(109u, 255u),
      image2_rg::pixel(199u, 255u),
      image2_rg::pixel(90u, 255u),
      image2_rg::pixel(178u, 255u),
      image2_rg::pixel(199u, 255u),
    });
  image2_rg im = bmp_read_file<pixel_format::rg>(test_image_bmp);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_bmp_rg_error)
{
  EXPECT_ERROR_0(
    bmp_read_file<pixel_format::rg>(test_image_png), invalid_image_data);
}



TEST_F(test_image_file, load_png_rg)
{
  image2_rg im_ref(vec2u(3u, 2u),
    std::vector<image2_rg::pixel>{
      image2_rg::pixel(90u, 255u),
      image2_rg::pixel(109u, 255u),
      image2_rg::pixel(199u, 255u),
      image2_rg::pixel(90u, 63u),
      image2_rg::pixel(0u, 0u),
      image2_rg::pixel(199u, 127u),
    });
  image2_rg im = png_read_file<pixel_format::rg>(test_image_png);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_png_rg_error)
{
  EXPECT_ERROR_0(
    png_read_file<pixel_format::rg>(test_image_jpg), invalid_image_data);
}



TEST_F(test_image_file, load_jpg_rg)
{
  image2_rg im_ref(vec2u(3u, 2u),
    std::vector<image2_rg::pixel>{
      image2_rg::pixel(87u, 255u),
      image2_rg::pixel(114u, 255u),
      image2_rg::pixel(200u, 255u),
      image2_rg::pixel(217u, 255u),
      image2_rg::pixel(252u, 255u),
      image2_rg::pixel(231u, 255u),
    });
  image2_rg im = jpg_read_file<pixel_format::rg>(test_image_jpg);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_jpg_rg_error)
{
  EXPECT_ERROR_0(
    jpg_read_file<pixel_format::rg>(test_image_png), invalid_image_data);
}



TEST_F(test_image_file, load_bmp_r)
{
  // alpha channel in Bmp not supported.
  image2_r im_ref(vec2u(3u, 2u),
    std::vector<image2_r::pixel>{
      image2_r::pixel(90u),
      image2_r::pixel(109u),
      image2_r::pixel(199u),
      image2_r::pixel(90u),
      image2_r::pixel(178u),
      image2_r::pixel(199u),
    });
  image2_r im = bmp_read_file<pixel_format::r>(test_image_bmp);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_bmp_r_error)
{
  EXPECT_ERROR_0(
    bmp_read_file<pixel_format::r>(test_image_png), invalid_image_data);
}



TEST_F(test_image_file, load_png_r)
{
  image2_r im_ref(vec2u(3u, 2u),
    std::vector<image2_r::pixel>{
      image2_r::pixel(90u),
      image2_r::pixel(109u),
      image2_r::pixel(199u),
      image2_r::pixel(90u),
      image2_r::pixel(0u),
      image2_r::pixel(199u),
    });
  image2_r im = png_read_file<pixel_format::r>(test_image_png);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_png_r_error)
{
  EXPECT_ERROR_0(
    png_read_file<pixel_format::r>(test_image_jpg), invalid_image_data);
}



TEST_F(test_image_file, load_jpg_r)
{
  image2_r im_ref(vec2u(3u, 2u),
    std::vector<image2_r::pixel>{
      image2_r::pixel(87u),
      image2_r::pixel(114u),
      image2_r::pixel(200u),
      image2_r::pixel(217u),
      image2_r::pixel(252u),
      image2_r::pixel(231u),
    });
  image2_r im = jpg_read_file<pixel_format::r>(test_image_jpg);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_jpg_r_error)
{
  EXPECT_ERROR_0(
    jpg_read_file<pixel_format::r>(test_image_png), invalid_image_data);
}
