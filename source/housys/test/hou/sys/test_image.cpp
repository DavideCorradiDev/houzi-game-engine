// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/test_data.hpp"

#include "hou/sys/file.hpp"
#include "hou/sys/image.hpp"
#include "hou/sys/sys_error.hpp"

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
  = Types<image1r, image2r, image3r, image1rg, image2rg, image3rg, image1rgb,
    image2rgb, image3rgb, image1rgba, image2rgba, image3rgba>;

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
typename image1r::size_type test_image<image1r>::generate_size()
{
  return vec1u{4u};
}



template <>
typename image1rg::size_type test_image<image1rg>::generate_size()
{
  return vec1u{4u};
}



template <>
typename image1rgb::size_type test_image<image1rgb>::generate_size()
{
  return vec1u{4u};
}



template <>
typename image1rgba::size_type test_image<image1rgba>::generate_size()
{
  return vec1u{4u};
}



template <>
typename image2r::size_type test_image<image2r>::generate_size()
{
  return vec2u{4u, 7u};
}



template <>
typename image2rg::size_type test_image<image2rg>::generate_size()
{
  return vec2u{4u, 7u};
}



template <>
typename image2rgb::size_type test_image<image2rgb>::generate_size()
{
  return vec2u{4u, 7u};
}



template <>
typename image2rgba::size_type test_image<image2rgba>::generate_size()
{
  return vec2u{4u, 7u};
}



template <>
typename image3r::size_type test_image<image3r>::generate_size()
{
  return vec3u{4u, 7u, 11u};
}



template <>
typename image3rg::size_type test_image<image3rg>::generate_size()
{
  return vec3u{4u, 7u, 11u};
}



template <>
typename image3rgb::size_type test_image<image3rgb>::generate_size()
{
  return vec3u{4u, 7u, 11u};
}



template <>
typename image3rgba::size_type test_image<image3rgba>::generate_size()
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
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref), pixel_ref);
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
  HOU_EXPECT_PRECONDITION(TypeParam image(size_ref, pixels_ref));
}



TYPED_TEST(test_image_death_test, pixels_constructor_error_too_many_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) + 1u);
  HOU_EXPECT_PRECONDITION(TypeParam image(size_ref, pixels_ref));
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
  HOU_EXPECT_PRECONDITION(TypeParam image(size_ref, std::move(pixels_ref)));
}



TYPED_TEST(test_image_death_test, pixels_move_constructor_error_too_many_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) + 1u);
  HOU_EXPECT_PRECONDITION(TypeParam image(size_ref, std::move(pixels_ref)));
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
  HOU_EXPECT_PRECONDITION(image.set_pixels(pixels_ref));
}



TYPED_TEST(test_image_death_test, set_pixels_error_too_many_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) + 1u);
  TypeParam image(size_ref);
  HOU_EXPECT_PRECONDITION(image.set_pixels(pixels_ref));
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
    HOU_EXPECT_PRECONDITION(image.get_pixel(coords));
  }
  HOU_EXPECT_PRECONDITION(image.get_pixel(size_ref));
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
    HOU_EXPECT_PRECONDITION(image.set_pixel(coords, pixel_ref));
  }
  HOU_EXPECT_PRECONDITION(image.set_pixel(size_ref, pixel_ref));
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
  pixel_collection subPixels_ref(TestFixture::multiply_elements(sub_image_size));
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
  EXPECT_EQ(sub_image_ref, image.get_sub_image(sub_image_offset, sub_image_size));
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
  HOU_EXPECT_PRECONDITION(image.get_sub_image(sub_image_offset, sub_image_size));
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
  EXPECT_EQ(sub_image_ref, image.get_sub_image(sub_image_offset, sub_image_size));
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
  HOU_EXPECT_PRECONDITION(image.set_sub_image(sub_image_offset, subImage));
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

  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref), pixel_ref);
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

  HOU_EXPECT_OUTPUT(ss.str().c_str(), image);
}



TEST_F(test_image_class_attributes, get_dimension_count)
{
  EXPECT_EQ(1u, image1r::get_dimension_count());
  EXPECT_EQ(1u, image1rg::get_dimension_count());
  EXPECT_EQ(1u, image1rgb::get_dimension_count());
  EXPECT_EQ(1u, image1rgba::get_dimension_count());
  EXPECT_EQ(2u, image2r::get_dimension_count());
  EXPECT_EQ(2u, image2rg::get_dimension_count());
  EXPECT_EQ(2u, image2rgb::get_dimension_count());
  EXPECT_EQ(2u, image2rgba::get_dimension_count());
  EXPECT_EQ(3u, image3r::get_dimension_count());
  EXPECT_EQ(3u, image3rg::get_dimension_count());
  EXPECT_EQ(3u, image3rgb::get_dimension_count());
  EXPECT_EQ(3u, image3rgba::get_dimension_count());
}



TEST_F(test_image_class_attributes, get_pixel_format)
{
  EXPECT_EQ(pixel_format::r, image1r::get_pixel_format());
  EXPECT_EQ(pixel_format::rg, image1rg::get_pixel_format());
  EXPECT_EQ(pixel_format::rgb, image1rgb::get_pixel_format());
  EXPECT_EQ(pixel_format::rgba, image1rgba::get_pixel_format());
  EXPECT_EQ(pixel_format::r, image2r::get_pixel_format());
  EXPECT_EQ(pixel_format::rg, image2rg::get_pixel_format());
  EXPECT_EQ(pixel_format::rgb, image2rgb::get_pixel_format());
  EXPECT_EQ(pixel_format::rgba, image2rgba::get_pixel_format());
  EXPECT_EQ(pixel_format::r, image3r::get_pixel_format());
  EXPECT_EQ(pixel_format::rg, image3rg::get_pixel_format());
  EXPECT_EQ(pixel_format::rgb, image3rgb::get_pixel_format());
  EXPECT_EQ(pixel_format::rgba, image3rgba::get_pixel_format());
}



TEST_F(test_image_conversion_constructor, r2_rgba_constructor)
{
  image2r::size_type size(2u, 3u);
  image2r::pixel_collection pixelsR{
    image2r::pixel(1u),
    image2r::pixel(2u),
    image2r::pixel(3u),
    image2r::pixel(4u),
    image2r::pixel(5u),
    image2r::pixel(6u),
  };

  image2rgba::pixel_collection pixelsRGBA{
    image2rgba::pixel(1u, 1u, 1u, 255u),
    image2rgba::pixel(2u, 2u, 2u, 255u),
    image2rgba::pixel(3u, 3u, 3u, 255u),
    image2rgba::pixel(4u, 4u, 4u, 255u),
    image2rgba::pixel(5u, 5u, 5u, 255u),
    image2rgba::pixel(6u, 6u, 6u, 255u),
  };

  image2r imageR(size, pixelsR);
  image2rgba imageRGBA(imageR);

  EXPECT_EQ(size, imageRGBA.get_size());
  EXPECT_EQ(pixelsRGBA, imageRGBA.get_pixels());
}



TEST_F(test_image_conversion_constructor, rg2_rgba_constructor)
{
  image2rg::size_type size(2u, 3u);
  image2rg::pixel_collection pixelsRG{
    image2rg::pixel(1u, 11u),
    image2rg::pixel(2u, 12u),
    image2rg::pixel(3u, 13u),
    image2rg::pixel(4u, 14u),
    image2rg::pixel(5u, 15u),
    image2rg::pixel(6u, 16u),
  };

  image2rgba::pixel_collection pixelsRGBA{
    image2rgba::pixel(1u, 1u, 1u, 11u),
    image2rgba::pixel(2u, 2u, 2u, 12u),
    image2rgba::pixel(3u, 3u, 3u, 13u),
    image2rgba::pixel(4u, 4u, 4u, 14u),
    image2rgba::pixel(5u, 5u, 5u, 15u),
    image2rgba::pixel(6u, 6u, 6u, 16u),
  };

  image2rg imageRG(size, pixelsRG);
  image2rgba imageRGBA(imageRG);

  EXPECT_EQ(size, imageRGBA.get_size());
  EXPECT_EQ(pixelsRGBA, imageRGBA.get_pixels());
}



TEST_F(test_image_conversion_constructor, rgb2_rgba_constructor)
{
  image2rgb::size_type size(2u, 3u);
  image2rgb::pixel_collection pixelsRGB{
    image2rgb::pixel(200u, 118u, 93u),
    image2rgb::pixel(3u, 12u, 3u),
    image2rgb::pixel(5u, 11u, 2u),
    image2rgb::pixel(200u, 100u, 0u),
    image2rgb::pixel(0u, 21u, 0u),
    image2rgb::pixel(100u, 20u, 0u),
  };

  image2rgba::pixel_collection pixelsRGBA{
    image2rgba::pixel(200u, 118u, 93u, 255u),
    image2rgba::pixel(3u, 12u, 3u, 255u),
    image2rgba::pixel(5u, 11u, 2u, 255u),
    image2rgba::pixel(200u, 100u, 0u, 255u),
    image2rgba::pixel(0u, 21u, 0u, 255u),
    image2rgba::pixel(100u, 20u, 0u, 255u),
  };

  image2rgb imageRGB(size, pixelsRGB);
  image2rgba imageRGBA(imageRGB);

  EXPECT_EQ(size, imageRGBA.get_size());
  EXPECT_EQ(pixelsRGBA, imageRGBA.get_pixels());
}



TEST_F(test_image_conversion_constructor, image1_to_image2_constructor)
{
  image1rgb::size_type size(3u);
  image1rgba::pixel_collection pixelsRGBA{
    image1rgba::pixel(200u, 118u, 93u, 255u),
    image1rgba::pixel(3u, 12u, 3u, 255u),
    image1rgba::pixel(5u, 11u, 2u, 255u),
  };
  image1rgba image1rgba(size, pixelsRGBA);
  image2rgba image2rgba(image1rgba);
  EXPECT_EQ(vec2u(size.x(), 1u), image2rgba.get_size());
  EXPECT_EQ(pixelsRGBA, image2rgba.get_pixels());
}



TEST_F(test_image_conversion_constructor, image1_to_image3_constructor)
{
  image1rgb::size_type size(3u);
  image1rgba::pixel_collection pixelsRGBA{
    image1rgba::pixel(200u, 118u, 93u, 255u),
    image1rgba::pixel(3u, 12u, 3u, 255u),
    image1rgba::pixel(5u, 11u, 2u, 255u),
  };
  image1rgba image1rgba(size, pixelsRGBA);
  image3rgba image3rgba(image1rgba);
  EXPECT_EQ(vec3u(size.x(), 1u, 1u), image3rgba.get_size());
  EXPECT_EQ(pixelsRGBA, image3rgba.get_pixels());
}



TEST_F(test_image_conversion_constructor, image2_to_image3_constructor)
{
  image2rgb::size_type size(3u, 2u);
  image2rgba::pixel_collection pixelsRGBA{
    image2rgba::pixel(200u, 118u, 93u, 255u),
    image2rgba::pixel(3u, 12u, 3u, 255u),
    image2rgba::pixel(5u, 11u, 2u, 255u),
    image2rgba::pixel(200u, 118u, 93u, 255u),
    image2rgba::pixel(3u, 12u, 3u, 255u),
    image2rgba::pixel(5u, 11u, 2u, 255u),
  };
  image2rgba image1rgba(size, pixelsRGBA);
  image3rgba image3rgba(image1rgba);
  EXPECT_EQ(vec3u(size.x(), size.y(), 1u), image3rgba.get_size());
  EXPECT_EQ(pixelsRGBA, image3rgba.get_pixels());
}



TEST_F(test_image_file, load_bmp_rgba)
{
  // alpha channel in Bmp not supported.
  image2rgba im_ref(vec2u(3u, 2u),
    std::vector<image2rgba::pixel>{
      image2rgba::pixel(50u, 100u, 150u, 255u),
      image2rgba::pixel(150u, 100u, 50u, 255u),
      image2rgba::pixel(255u, 200u, 50u, 255u),
      image2rgba::pixel(50u, 100u, 150u, 255u),
      image2rgba::pixel(0u, 255u, 255u, 255u),
      image2rgba::pixel(255u, 200u, 50u, 255u),
    });
  image2rgba im = bmp_read_file<pixel_format::rgba>(test_image_bmp);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_bmp_rgba_error)
{
  HOU_EXPECT_ERROR(bmp_read_file<pixel_format::rgba>(test_image_png),
    std::runtime_error,
    format_string(get_text(sys_error::image_bmp_read), test_image_png.c_str()));
}



TEST_F(test_image_file, load_png_rgba)
{
  image2rgba im_ref(vec2u(3u, 2u),
    std::vector<image2rgba::pixel>{
      image2rgba::pixel(50u, 100u, 150u, 255u),
      image2rgba::pixel(150u, 100u, 50u, 255u),
      image2rgba::pixel(255u, 200u, 50u, 255u),
      image2rgba::pixel(50u, 100u, 150u, 63u),
      image2rgba::pixel(0u, 0u, 0u, 0u),
      image2rgba::pixel(255u, 200u, 50u, 127u),
    });
  image2rgba im = png_read_file<pixel_format::rgba>(test_image_png);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_png_rgba_error)
{
  HOU_EXPECT_ERROR(png_read_file<pixel_format::rgba>(test_image_jpg),
    std::runtime_error,
    format_string(get_text(sys_error::image_png_read), test_image_jpg.c_str()));
}



TEST_F(test_image_file, load_jpg_rgba)
{
  image2rgba im_ref(vec2u(3u, 2u),
    std::vector<image2rgba::pixel>{
      image2rgba::pixel(72u, 86u, 133u, 255u),
      image2rgba::pixel(134u, 111u, 80u, 255u),
      image2rgba::pixel(252u, 204u, 46u, 255u),
      image2rgba::pixel(189u, 225u, 247u, 255u),
      image2rgba::pixel(255u, 253u, 240u, 255u),
      image2rgba::pixel(255u, 232u, 139u, 255u),
    });
  image2rgba im = jpg_read_file<pixel_format::rgba>(test_image_jpg);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_jpg_rgba_error)
{
  HOU_EXPECT_ERROR(jpg_read_file<pixel_format::rgba>(test_image_png),
    std::runtime_error,
    format_string(get_text(sys_error::image_jpg_read), test_image_png.c_str()));
}



TEST_F(test_image_file, save_bmp_rgba)
{
  const std::string savePath = get_output_dir() + "savedBmp.bmp";
  remove_dir(savePath);
  image2rgba im_ref = bmp_read_file<pixel_format::rgba>(test_image_bmp);
  bmp_write_file(savePath, im_ref);
  image2rgba im = bmp_read_file<pixel_format::rgba>(savePath);
  EXPECT_EQ(im_ref, im);
  EXPECT_TRUE(remove_dir(savePath));
}



TEST_F(test_image_file_death_test, save_bmp_error_rgba)
{
  const std::string savePath = get_output_dir() + "savedBmp.bmp";
  remove_dir(savePath);
  image2rgba im_ref = bmp_read_file<pixel_format::rgba>(test_image_bmp);
  bmp_write_file(savePath, im_ref);
  HOU_EXPECT_ERROR(bmp_write_file<pixel_format::rgba>(savePath, im_ref),
    std::runtime_error,
    format_string(get_text(sys_error::image_bmp_write), savePath.c_str()));
  EXPECT_TRUE(remove_dir(savePath));
}



TEST_F(test_image_file, load_bmp_rgb)
{
  // alpha channel in Bmp not supported.
  image2rgb im_ref(vec2u(3u, 2u),
    std::vector<image2rgb::pixel>{
      image2rgb::pixel(50u, 100u, 150u),
      image2rgb::pixel(150u, 100u, 50u),
      image2rgb::pixel(255u, 200u, 50u),
      image2rgb::pixel(50u, 100u, 150u),
      image2rgb::pixel(0u, 255u, 255u),
      image2rgb::pixel(255u, 200u, 50u),
    });
  image2rgb im = bmp_read_file<pixel_format::rgb>(test_image_bmp);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_bmp_rgb_error)
{
  HOU_EXPECT_ERROR(bmp_read_file<pixel_format::rgb>(test_image_png),
    std::runtime_error,
    format_string(get_text(sys_error::image_bmp_read), test_image_png.c_str()));
}



TEST_F(test_image_file, load_png_rgb)
{
  image2rgb im_ref(vec2u(3u, 2u),
    std::vector<image2rgb::pixel>{
      image2rgb::pixel(50u, 100u, 150u),
      image2rgb::pixel(150u, 100u, 50u),
      image2rgb::pixel(255u, 200u, 50u),
      image2rgb::pixel(50u, 100u, 150u),
      image2rgb::pixel(0u, 0u, 0u),
      image2rgb::pixel(255u, 200u, 50u),
    });
  image2rgb im = png_read_file<pixel_format::rgb>(test_image_png);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_png_rgb_error)
{
  HOU_EXPECT_ERROR(png_read_file<pixel_format::rgb>(test_image_jpg),
    std::runtime_error,
    format_string(get_text(sys_error::image_png_read), test_image_jpg.c_str()));
}



TEST_F(test_image_file, load_jpg_rgb)
{
  image2rgb im_ref(vec2u(3u, 2u),
    std::vector<image2rgb::pixel>{
      image2rgb::pixel(72u, 86u, 133u),
      image2rgb::pixel(134u, 111u, 80u),
      image2rgb::pixel(252u, 204u, 46u),
      image2rgb::pixel(189u, 225u, 247u),
      image2rgb::pixel(255u, 253u, 240u),
      image2rgb::pixel(255u, 232u, 139u),
    });
  image2rgb im = jpg_read_file<pixel_format::rgb>(test_image_jpg);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_jpg_rgb_error)
{
  HOU_EXPECT_ERROR(jpg_read_file<pixel_format::rgb>(test_image_png),
    std::runtime_error,
    format_string(get_text(sys_error::image_jpg_read), test_image_png.c_str()));
}



TEST_F(test_image_file, load_bmp_rg)
{
  // alpha channel in Bmp not supported.
  image2rg im_ref(vec2u(3u, 2u),
    std::vector<image2rg::pixel>{
      image2rg::pixel(90u, 255u),
      image2rg::pixel(109u, 255u),
      image2rg::pixel(199u, 255u),
      image2rg::pixel(90u, 255u),
      image2rg::pixel(178u, 255u),
      image2rg::pixel(199u, 255u),
    });
  image2rg im = bmp_read_file<pixel_format::rg>(test_image_bmp);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_bmp_rg_error)
{
  HOU_EXPECT_ERROR(bmp_read_file<pixel_format::rg>(test_image_png),
    std::runtime_error,
    format_string(get_text(sys_error::image_bmp_read), test_image_png.c_str()));
}



TEST_F(test_image_file, load_png_rg)
{
  image2rg im_ref(vec2u(3u, 2u),
    std::vector<image2rg::pixel>{
      image2rg::pixel(90u, 255u),
      image2rg::pixel(109u, 255u),
      image2rg::pixel(199u, 255u),
      image2rg::pixel(90u, 63u),
      image2rg::pixel(0u, 0u),
      image2rg::pixel(199u, 127u),
    });
  image2rg im = png_read_file<pixel_format::rg>(test_image_png);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_png_rg_error)
{
  HOU_EXPECT_ERROR(png_read_file<pixel_format::rg>(test_image_jpg),
    std::runtime_error,
    format_string(get_text(sys_error::image_png_read), test_image_jpg.c_str()));
}



TEST_F(test_image_file, load_jpg_rg)
{
  image2rg im_ref(vec2u(3u, 2u),
    std::vector<image2rg::pixel>{
      image2rg::pixel(87u, 255u),
      image2rg::pixel(114u, 255u),
      image2rg::pixel(200u, 255u),
      image2rg::pixel(217u, 255u),
      image2rg::pixel(252u, 255u),
      image2rg::pixel(231u, 255u),
    });
  image2rg im = jpg_read_file<pixel_format::rg>(test_image_jpg);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_jpg_rg_error)
{
  HOU_EXPECT_ERROR(jpg_read_file<pixel_format::rg>(test_image_png),
    std::runtime_error,
    format_string(get_text(sys_error::image_jpg_read), test_image_png.c_str()));
}



TEST_F(test_image_file, load_bmp_r)
{
  // alpha channel in Bmp not supported.
  image2r im_ref(vec2u(3u, 2u),
    std::vector<image2r::pixel>{
      image2r::pixel(90u),
      image2r::pixel(109u),
      image2r::pixel(199u),
      image2r::pixel(90u),
      image2r::pixel(178u),
      image2r::pixel(199u),
    });
  image2r im = bmp_read_file<pixel_format::r>(test_image_bmp);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_bmp_r_error)
{
  HOU_EXPECT_ERROR(bmp_read_file<pixel_format::r>(test_image_png),
    std::runtime_error,
    format_string(get_text(sys_error::image_bmp_read), test_image_png.c_str()));
}



TEST_F(test_image_file, load_png_r)
{
  image2r im_ref(vec2u(3u, 2u),
    std::vector<image2r::pixel>{
      image2r::pixel(90u),
      image2r::pixel(109u),
      image2r::pixel(199u),
      image2r::pixel(90u),
      image2r::pixel(0u),
      image2r::pixel(199u),
    });
  image2r im = png_read_file<pixel_format::r>(test_image_png);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_png_r_error)
{
  HOU_EXPECT_ERROR(png_read_file<pixel_format::r>(test_image_jpg),
    std::runtime_error,
    format_string(get_text(sys_error::image_png_read), test_image_jpg.c_str()));
}



TEST_F(test_image_file, load_jpg_r)
{
  image2r im_ref(vec2u(3u, 2u),
    std::vector<image2r::pixel>{
      image2r::pixel(87u),
      image2r::pixel(114u),
      image2r::pixel(200u),
      image2r::pixel(217u),
      image2r::pixel(252u),
      image2r::pixel(231u),
    });
  image2r im = jpg_read_file<pixel_format::r>(test_image_jpg);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_jpg_r_error)
{
  HOU_EXPECT_ERROR(jpg_read_file<pixel_format::r>(test_image_png),
    std::runtime_error,
    format_string(get_text(sys_error::image_jpg_read), test_image_png.c_str()));
}
