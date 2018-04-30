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
  = Types<image1R, image2R, image3R, image1RG, image2RG, image3RG, image1RGB,
    image2RGB, image3RGB, image1RGBA, image2RGBA, image3RGBA>;

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
typename image1R::size_type test_image<image1R>::generate_size()
{
  return vec1u{4u};
}



template <>
typename image1RG::size_type test_image<image1RG>::generate_size()
{
  return vec1u{4u};
}



template <>
typename image1RGB::size_type test_image<image1RGB>::generate_size()
{
  return vec1u{4u};
}



template <>
typename image1RGBA::size_type test_image<image1RGBA>::generate_size()
{
  return vec1u{4u};
}



template <>
typename image2R::size_type test_image<image2R>::generate_size()
{
  return vec2u{4u, 7u};
}



template <>
typename image2RG::size_type test_image<image2RG>::generate_size()
{
  return vec2u{4u, 7u};
}



template <>
typename image2RGB::size_type test_image<image2RGB>::generate_size()
{
  return vec2u{4u, 7u};
}



template <>
typename image2RGBA::size_type test_image<image2RGBA>::generate_size()
{
  return vec2u{4u, 7u};
}



template <>
typename image3R::size_type test_image<image3R>::generate_size()
{
  return vec3u{4u, 7u, 11u};
}



template <>
typename image3RG::size_type test_image<image3RG>::generate_size()
{
  return vec3u{4u, 7u, 11u};
}



template <>
typename image3RGB::size_type test_image<image3RGB>::generate_size()
{
  return vec3u{4u, 7u, 11u};
}



template <>
typename image3RGBA::size_type test_image<image3RGBA>::generate_size()
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

  TypeParam ph_image;
  EXPECT_EQ(size_type::zero(), ph_image.get_size());
  EXPECT_EQ(pixel_collection(), ph_image.get_pixels());
}



TYPED_TEST(test_image, size_constructor)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  TypeParam ph_image(size_ref);
  EXPECT_EQ(size_ref, ph_image.get_size());
  EXPECT_EQ(pixel_collection(TestFixture::multiply_elements(size_ref)),
    ph_image.get_pixels());
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
  TypeParam ph_image(size_ref, pixel_ref);

  EXPECT_EQ(size_ref, ph_image.get_size());
  EXPECT_EQ(pixels_ref, ph_image.get_pixels());
}



TYPED_TEST(test_image, pixels_constructor)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref = TestFixture::generate_pixels(size_ref);
  TypeParam ph_image(size_ref, pixels_ref);

  EXPECT_EQ(size_ref, ph_image.get_size());
  EXPECT_EQ(pixels_ref, ph_image.get_pixels());
}



TYPED_TEST(test_image_death_test, pixels_constructor_error_too_few_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) - 1u);
  HOU_EXPECT_PRECONDITION(TypeParam ph_image(size_ref, pixels_ref));
}



TYPED_TEST(test_image_death_test, pixels_constructor_error_too_many_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) + 1u);
  HOU_EXPECT_PRECONDITION(TypeParam ph_image(size_ref, pixels_ref));
}



TYPED_TEST(test_image, pixels_move_constructor)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref = TestFixture::generate_pixels(size_ref);
  pixel_collection pixels(pixels_ref);
  TypeParam ph_image(size_ref, std::move(pixels));

  EXPECT_EQ(size_ref, ph_image.get_size());
  EXPECT_EQ(pixels_ref, ph_image.get_pixels());
}



TYPED_TEST(test_image_death_test, pixels_move_constructor_error_too_few_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) - 1u);
  HOU_EXPECT_PRECONDITION(TypeParam ph_image(size_ref, std::move(pixels_ref)));
}



TYPED_TEST(test_image_death_test, pixels_move_constructor_error_too_many_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) + 1u);
  HOU_EXPECT_PRECONDITION(TypeParam ph_image(size_ref, std::move(pixels_ref)));
}



TYPED_TEST(test_image, set_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref = TestFixture::generate_pixels(size_ref);
  TypeParam ph_image(size_ref);
  ph_image.set_pixels(pixels_ref);
  EXPECT_EQ(pixels_ref, ph_image.get_pixels());
}



TYPED_TEST(test_image_death_test, set_pixels_error_too_few_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) - 1u);
  TypeParam ph_image(size_ref);
  HOU_EXPECT_PRECONDITION(ph_image.set_pixels(pixels_ref));
}



TYPED_TEST(test_image_death_test, set_pixels_error_too_many_pixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref) + 1u);
  TypeParam ph_image(size_ref);
  HOU_EXPECT_PRECONDITION(ph_image.set_pixels(pixels_ref));
}



TYPED_TEST(test_image, get_pixel)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  pixel_collection pixels_ref = TestFixture::generate_pixels(size_ref);
  TypeParam ph_image(size_ref, pixels_ref);

  for(size_t i = 0; i < pixels_ref.size(); ++i)
  {
    EXPECT_EQ(pixels_ref[i],
      ph_image.get_pixel(
        TestFixture::compute_pixel_coordinates(i, ph_image.get_size())));
  }
}



TYPED_TEST(test_image_death_test, get_pixel_error_out_of_range)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type size_ref = TestFixture::generate_size();
  TypeParam ph_image(size_ref);

  for(size_t i = 0; i < size_ref.get_size(); ++i)
  {
    offset_type coords;
    coords(i) = size_ref(i);
    HOU_EXPECT_PRECONDITION(ph_image.get_pixel(coords));
  }
  HOU_EXPECT_PRECONDITION(ph_image.get_pixel(size_ref));
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
    TypeParam ph_image(size_ref);
    pixel_collection pixels_ref = ph_image.get_pixels();
    pixels_ref[i] = pixel_ref;
    ph_image.set_pixel(
      TestFixture::compute_pixel_coordinates(i, ph_image.get_size()), pixel_ref);
    EXPECT_EQ(pixels_ref[i],
      ph_image.get_pixel(
        TestFixture::compute_pixel_coordinates(i, ph_image.get_size())));
  }
}



TYPED_TEST(test_image_death_test, set_pixel_error_out_of_range)
{
  using size_type = typename TypeParam::size_type;
  using pixel = typename TypeParam::pixel;
  using offset_type = typename TypeParam::offset_type;

  size_type size_ref = TestFixture::generate_size();
  TypeParam ph_image(size_ref);

  pixel pixel_ref;
  for(size_t i = 0; i < size_ref.get_size(); ++i)
  {
    offset_type coords;
    coords(i) = size_ref(i);
    HOU_EXPECT_PRECONDITION(ph_image.set_pixel(coords, pixel_ref));
  }
  HOU_EXPECT_PRECONDITION(ph_image.set_pixel(size_ref, pixel_ref));
}



TYPED_TEST(test_image, get_sub_image)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type imageSize;
  size_type subImageSize;
  offset_type subImageOffset;
  for(size_t i = 0; i < imageSize.get_size(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    subImageSize(i) = (i + 1) * 2;
    subImageOffset(i) = i + 1;
  }

  pixel_collection pixels_ref = TestFixture::generate_pixels(imageSize);
  pixel_collection subPixels_ref(TestFixture::multiply_elements(subImageSize));
  for(size_t i = 0; i < subPixels_ref.size(); ++i)
  {
    offset_type subImageCoords
      = TestFixture::compute_pixel_coordinates(i, subImageSize);
    offset_type imageCoords = subImageOffset + subImageCoords;
    subPixels_ref[i]
      = pixels_ref[TestFixture::compute_pixel_index(imageCoords, imageSize)];
  }

  TypeParam ph_image(imageSize, pixels_ref);
  TypeParam subImage_ref(subImageSize, subPixels_ref);
  EXPECT_EQ(subImage_ref, ph_image.get_sub_image(subImageOffset, subImageSize));
}



TYPED_TEST(test_image_death_test, get_sub_image_error_overflow)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type imageSize;
  size_type subImageSize;
  offset_type subImageOffset;
  for(size_t i = 0; i < imageSize.get_size(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    subImageOffset(i) = i + 1;
    subImageSize(i) = (i + 1) * 4 - subImageOffset(i) + 1u;
  }

  TypeParam ph_image(imageSize);
  HOU_EXPECT_PRECONDITION(ph_image.get_sub_image(subImageOffset, subImageSize));
}



TYPED_TEST(test_image, set_sub_image)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type imageSize;
  size_type subImageSize;
  offset_type subImageOffset;
  for(size_t i = 0; i < imageSize.get_size(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    subImageSize(i) = (i + 1) * 2;
    subImageOffset(i) = i + 1;
  }

  pixel_collection pixels_ref(TestFixture::multiply_elements(imageSize));
  pixel_collection subPixels_ref(TestFixture::generate_pixels(subImageSize));
  for(size_t i = 0; i < subPixels_ref.size(); ++i)
  {
    offset_type subImageCoords
      = TestFixture::compute_pixel_coordinates(i, subImageSize);
    offset_type imageCoords = subImageOffset + subImageCoords;
    pixels_ref[TestFixture::compute_pixel_index(imageCoords, imageSize)]
      = subPixels_ref[i];
  }

  TypeParam ph_image(imageSize);
  TypeParam image_ref(imageSize, pixels_ref);
  TypeParam subImage_ref(subImageSize, subPixels_ref);
  ph_image.set_sub_image(subImageOffset, subImage_ref);

  EXPECT_EQ(image_ref, ph_image);
  EXPECT_EQ(subImage_ref, ph_image.get_sub_image(subImageOffset, subImageSize));
}



TYPED_TEST(test_image_death_test, set_sub_image_error_overflow)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type imageSize;
  size_type subImageSize;
  offset_type subImageOffset;
  for(size_t i = 0; i < imageSize.get_size(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    subImageOffset(i) = i + 1;
    subImageSize(i) = (i + 1) * 4 - subImageOffset(i) + 1u;
  }

  TypeParam ph_image(imageSize);
  TypeParam subImage(subImageSize);
  HOU_EXPECT_PRECONDITION(ph_image.set_sub_image(subImageOffset, subImage));
}



TYPED_TEST(test_image, clear)
{
  using size_type = typename TypeParam::size_type;
  using pixel = typename TypeParam::pixel;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size_ref = TestFixture::generate_size();
  TypeParam ph_image(size_ref);

  pixel pixel_ref;
  pixel_ref.set_r(42u);

  pixel_collection pixels_ref(TestFixture::multiply_elements(size_ref), pixel_ref);
  ph_image.clear(pixel_ref);
  EXPECT_EQ(pixels_ref, ph_image.get_pixels());
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

  TypeParam ph_image(size_ref, pixels_ref);

  std::stringstream ss;
  ss << "{size_type = " << transpose(size_ref) << ", pixels = " << pixels_ref
     << "}";

  HOU_EXPECT_OUTPUT(ss.str().c_str(), ph_image);
}



TEST_F(test_image_class_attributes, get_dimension_count)
{
  EXPECT_EQ(1u, image1R::get_dimension_count());
  EXPECT_EQ(1u, image1RG::get_dimension_count());
  EXPECT_EQ(1u, image1RGB::get_dimension_count());
  EXPECT_EQ(1u, image1RGBA::get_dimension_count());
  EXPECT_EQ(2u, image2R::get_dimension_count());
  EXPECT_EQ(2u, image2RG::get_dimension_count());
  EXPECT_EQ(2u, image2RGB::get_dimension_count());
  EXPECT_EQ(2u, image2RGBA::get_dimension_count());
  EXPECT_EQ(3u, image3R::get_dimension_count());
  EXPECT_EQ(3u, image3RG::get_dimension_count());
  EXPECT_EQ(3u, image3RGB::get_dimension_count());
  EXPECT_EQ(3u, image3RGBA::get_dimension_count());
}



TEST_F(test_image_class_attributes, get_pixel_format)
{
  EXPECT_EQ(pixel_format::r, image1R::get_pixel_format());
  EXPECT_EQ(pixel_format::rg, image1RG::get_pixel_format());
  EXPECT_EQ(pixel_format::rgb, image1RGB::get_pixel_format());
  EXPECT_EQ(pixel_format::rgba, image1RGBA::get_pixel_format());
  EXPECT_EQ(pixel_format::r, image2R::get_pixel_format());
  EXPECT_EQ(pixel_format::rg, image2RG::get_pixel_format());
  EXPECT_EQ(pixel_format::rgb, image2RGB::get_pixel_format());
  EXPECT_EQ(pixel_format::rgba, image2RGBA::get_pixel_format());
  EXPECT_EQ(pixel_format::r, image3R::get_pixel_format());
  EXPECT_EQ(pixel_format::rg, image3RG::get_pixel_format());
  EXPECT_EQ(pixel_format::rgb, image3RGB::get_pixel_format());
  EXPECT_EQ(pixel_format::rgba, image3RGBA::get_pixel_format());
}



TEST_F(test_image_conversion_constructor, r2_rgba_constructor)
{
  image2R::size_type size(2u, 3u);
  image2R::pixel_collection pixelsR{
    image2R::pixel(1u),
    image2R::pixel(2u),
    image2R::pixel(3u),
    image2R::pixel(4u),
    image2R::pixel(5u),
    image2R::pixel(6u),
  };

  image2RGBA::pixel_collection pixelsRGBA{
    image2RGBA::pixel(1u, 1u, 1u, 255u),
    image2RGBA::pixel(2u, 2u, 2u, 255u),
    image2RGBA::pixel(3u, 3u, 3u, 255u),
    image2RGBA::pixel(4u, 4u, 4u, 255u),
    image2RGBA::pixel(5u, 5u, 5u, 255u),
    image2RGBA::pixel(6u, 6u, 6u, 255u),
  };

  image2R imageR(size, pixelsR);
  image2RGBA imageRGBA(imageR);

  EXPECT_EQ(size, imageRGBA.get_size());
  EXPECT_EQ(pixelsRGBA, imageRGBA.get_pixels());
}



TEST_F(test_image_conversion_constructor, rg2_rgba_constructor)
{
  image2RG::size_type size(2u, 3u);
  image2RG::pixel_collection pixelsRG{
    image2RG::pixel(1u, 11u),
    image2RG::pixel(2u, 12u),
    image2RG::pixel(3u, 13u),
    image2RG::pixel(4u, 14u),
    image2RG::pixel(5u, 15u),
    image2RG::pixel(6u, 16u),
  };

  image2RGBA::pixel_collection pixelsRGBA{
    image2RGBA::pixel(1u, 1u, 1u, 11u),
    image2RGBA::pixel(2u, 2u, 2u, 12u),
    image2RGBA::pixel(3u, 3u, 3u, 13u),
    image2RGBA::pixel(4u, 4u, 4u, 14u),
    image2RGBA::pixel(5u, 5u, 5u, 15u),
    image2RGBA::pixel(6u, 6u, 6u, 16u),
  };

  image2RG imageRG(size, pixelsRG);
  image2RGBA imageRGBA(imageRG);

  EXPECT_EQ(size, imageRGBA.get_size());
  EXPECT_EQ(pixelsRGBA, imageRGBA.get_pixels());
}



TEST_F(test_image_conversion_constructor, rgb2_rgba_constructor)
{
  image2RGB::size_type size(2u, 3u);
  image2RGB::pixel_collection pixelsRGB{
    image2RGB::pixel(200u, 118u, 93u),
    image2RGB::pixel(3u, 12u, 3u),
    image2RGB::pixel(5u, 11u, 2u),
    image2RGB::pixel(200u, 100u, 0u),
    image2RGB::pixel(0u, 21u, 0u),
    image2RGB::pixel(100u, 20u, 0u),
  };

  image2RGBA::pixel_collection pixelsRGBA{
    image2RGBA::pixel(200u, 118u, 93u, 255u),
    image2RGBA::pixel(3u, 12u, 3u, 255u),
    image2RGBA::pixel(5u, 11u, 2u, 255u),
    image2RGBA::pixel(200u, 100u, 0u, 255u),
    image2RGBA::pixel(0u, 21u, 0u, 255u),
    image2RGBA::pixel(100u, 20u, 0u, 255u),
  };

  image2RGB imageRGB(size, pixelsRGB);
  image2RGBA imageRGBA(imageRGB);

  EXPECT_EQ(size, imageRGBA.get_size());
  EXPECT_EQ(pixelsRGBA, imageRGBA.get_pixels());
}



TEST_F(test_image_conversion_constructor, image1_to_image2_constructor)
{
  image1RGB::size_type size(3u);
  image1RGBA::pixel_collection pixelsRGBA{
    image1RGBA::pixel(200u, 118u, 93u, 255u),
    image1RGBA::pixel(3u, 12u, 3u, 255u),
    image1RGBA::pixel(5u, 11u, 2u, 255u),
  };
  image1RGBA image1RGBA(size, pixelsRGBA);
  image2RGBA image2RGBA(image1RGBA);
  EXPECT_EQ(vec2u(size.x(), 1u), image2RGBA.get_size());
  EXPECT_EQ(pixelsRGBA, image2RGBA.get_pixels());
}



TEST_F(test_image_conversion_constructor, image1_to_image3_constructor)
{
  image1RGB::size_type size(3u);
  image1RGBA::pixel_collection pixelsRGBA{
    image1RGBA::pixel(200u, 118u, 93u, 255u),
    image1RGBA::pixel(3u, 12u, 3u, 255u),
    image1RGBA::pixel(5u, 11u, 2u, 255u),
  };
  image1RGBA image1RGBA(size, pixelsRGBA);
  image3RGBA image3RGBA(image1RGBA);
  EXPECT_EQ(vec3u(size.x(), 1u, 1u), image3RGBA.get_size());
  EXPECT_EQ(pixelsRGBA, image3RGBA.get_pixels());
}



TEST_F(test_image_conversion_constructor, image2_to_image3_constructor)
{
  image2RGB::size_type size(3u, 2u);
  image2RGBA::pixel_collection pixelsRGBA{
    image2RGBA::pixel(200u, 118u, 93u, 255u),
    image2RGBA::pixel(3u, 12u, 3u, 255u),
    image2RGBA::pixel(5u, 11u, 2u, 255u),
    image2RGBA::pixel(200u, 118u, 93u, 255u),
    image2RGBA::pixel(3u, 12u, 3u, 255u),
    image2RGBA::pixel(5u, 11u, 2u, 255u),
  };
  image2RGBA image1RGBA(size, pixelsRGBA);
  image3RGBA image3RGBA(image1RGBA);
  EXPECT_EQ(vec3u(size.x(), size.y(), 1u), image3RGBA.get_size());
  EXPECT_EQ(pixelsRGBA, image3RGBA.get_pixels());
}



TEST_F(test_image_file, load_bmp_rgba)
{
  // alpha channel in Bmp not supported.
  image2RGBA im_ref(vec2u(3u, 2u),
    std::vector<image2RGBA::pixel>{
      image2RGBA::pixel(50u, 100u, 150u, 255u),
      image2RGBA::pixel(150u, 100u, 50u, 255u),
      image2RGBA::pixel(255u, 200u, 50u, 255u),
      image2RGBA::pixel(50u, 100u, 150u, 255u),
      image2RGBA::pixel(0u, 255u, 255u, 255u),
      image2RGBA::pixel(255u, 200u, 50u, 255u),
    });
  image2RGBA im = bmp_read_file<pixel_format::rgba>(test_image_bmp);
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
  image2RGBA im_ref(vec2u(3u, 2u),
    std::vector<image2RGBA::pixel>{
      image2RGBA::pixel(50u, 100u, 150u, 255u),
      image2RGBA::pixel(150u, 100u, 50u, 255u),
      image2RGBA::pixel(255u, 200u, 50u, 255u),
      image2RGBA::pixel(50u, 100u, 150u, 63u),
      image2RGBA::pixel(0u, 0u, 0u, 0u),
      image2RGBA::pixel(255u, 200u, 50u, 127u),
    });
  image2RGBA im = png_read_file<pixel_format::rgba>(test_image_png);
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
  image2RGBA im_ref(vec2u(3u, 2u),
    std::vector<image2RGBA::pixel>{
      image2RGBA::pixel(72u, 86u, 133u, 255u),
      image2RGBA::pixel(134u, 111u, 80u, 255u),
      image2RGBA::pixel(252u, 204u, 46u, 255u),
      image2RGBA::pixel(189u, 225u, 247u, 255u),
      image2RGBA::pixel(255u, 253u, 240u, 255u),
      image2RGBA::pixel(255u, 232u, 139u, 255u),
    });
  image2RGBA im = jpg_read_file<pixel_format::rgba>(test_image_jpg);
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
  image2RGBA im_ref = bmp_read_file<pixel_format::rgba>(test_image_bmp);
  bmp_write_file(savePath, im_ref);
  image2RGBA im = bmp_read_file<pixel_format::rgba>(savePath);
  EXPECT_EQ(im_ref, im);
  EXPECT_TRUE(remove_dir(savePath));
}



TEST_F(test_image_file_death_test, save_bmp_error_rgba)
{
  const std::string savePath = get_output_dir() + "savedBmp.bmp";
  remove_dir(savePath);
  image2RGBA im_ref = bmp_read_file<pixel_format::rgba>(test_image_bmp);
  bmp_write_file(savePath, im_ref);
  HOU_EXPECT_ERROR(bmp_write_file<pixel_format::rgba>(savePath, im_ref),
    std::runtime_error,
    format_string(get_text(sys_error::image_bmp_write), savePath.c_str()));
  EXPECT_TRUE(remove_dir(savePath));
}



TEST_F(test_image_file, load_bmp_rgb)
{
  // alpha channel in Bmp not supported.
  image2RGB im_ref(vec2u(3u, 2u),
    std::vector<image2RGB::pixel>{
      image2RGB::pixel(50u, 100u, 150u),
      image2RGB::pixel(150u, 100u, 50u),
      image2RGB::pixel(255u, 200u, 50u),
      image2RGB::pixel(50u, 100u, 150u),
      image2RGB::pixel(0u, 255u, 255u),
      image2RGB::pixel(255u, 200u, 50u),
    });
  image2RGB im = bmp_read_file<pixel_format::rgb>(test_image_bmp);
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
  image2RGB im_ref(vec2u(3u, 2u),
    std::vector<image2RGB::pixel>{
      image2RGB::pixel(50u, 100u, 150u),
      image2RGB::pixel(150u, 100u, 50u),
      image2RGB::pixel(255u, 200u, 50u),
      image2RGB::pixel(50u, 100u, 150u),
      image2RGB::pixel(0u, 0u, 0u),
      image2RGB::pixel(255u, 200u, 50u),
    });
  image2RGB im = png_read_file<pixel_format::rgb>(test_image_png);
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
  image2RGB im_ref(vec2u(3u, 2u),
    std::vector<image2RGB::pixel>{
      image2RGB::pixel(72u, 86u, 133u),
      image2RGB::pixel(134u, 111u, 80u),
      image2RGB::pixel(252u, 204u, 46u),
      image2RGB::pixel(189u, 225u, 247u),
      image2RGB::pixel(255u, 253u, 240u),
      image2RGB::pixel(255u, 232u, 139u),
    });
  image2RGB im = jpg_read_file<pixel_format::rgb>(test_image_jpg);
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
  image2RG im_ref(vec2u(3u, 2u),
    std::vector<image2RG::pixel>{
      image2RG::pixel(90u, 255u),
      image2RG::pixel(109u, 255u),
      image2RG::pixel(199u, 255u),
      image2RG::pixel(90u, 255u),
      image2RG::pixel(178u, 255u),
      image2RG::pixel(199u, 255u),
    });
  image2RG im = bmp_read_file<pixel_format::rg>(test_image_bmp);
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
  image2RG im_ref(vec2u(3u, 2u),
    std::vector<image2RG::pixel>{
      image2RG::pixel(90u, 255u),
      image2RG::pixel(109u, 255u),
      image2RG::pixel(199u, 255u),
      image2RG::pixel(90u, 63u),
      image2RG::pixel(0u, 0u),
      image2RG::pixel(199u, 127u),
    });
  image2RG im = png_read_file<pixel_format::rg>(test_image_png);
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
  image2RG im_ref(vec2u(3u, 2u),
    std::vector<image2RG::pixel>{
      image2RG::pixel(87u, 255u),
      image2RG::pixel(114u, 255u),
      image2RG::pixel(200u, 255u),
      image2RG::pixel(217u, 255u),
      image2RG::pixel(252u, 255u),
      image2RG::pixel(231u, 255u),
    });
  image2RG im = jpg_read_file<pixel_format::rg>(test_image_jpg);
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
  image2R im_ref(vec2u(3u, 2u),
    std::vector<image2R::pixel>{
      image2R::pixel(90u),
      image2R::pixel(109u),
      image2R::pixel(199u),
      image2R::pixel(90u),
      image2R::pixel(178u),
      image2R::pixel(199u),
    });
  image2R im = bmp_read_file<pixel_format::r>(test_image_bmp);
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
  image2R im_ref(vec2u(3u, 2u),
    std::vector<image2R::pixel>{
      image2R::pixel(90u),
      image2R::pixel(109u),
      image2R::pixel(199u),
      image2R::pixel(90u),
      image2R::pixel(0u),
      image2R::pixel(199u),
    });
  image2R im = png_read_file<pixel_format::r>(test_image_png);
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
  image2R im_ref(vec2u(3u, 2u),
    std::vector<image2R::pixel>{
      image2R::pixel(87u),
      image2R::pixel(114u),
      image2R::pixel(200u),
      image2R::pixel(217u),
      image2R::pixel(252u),
      image2R::pixel(231u),
    });
  image2R im = jpg_read_file<pixel_format::r>(test_image_jpg);
  EXPECT_EQ(im_ref, im);
}



TEST_F(test_image_file_death_test, load_jpg_r_error)
{
  HOU_EXPECT_ERROR(jpg_read_file<pixel_format::r>(test_image_png),
    std::runtime_error,
    format_string(get_text(sys_error::image_jpg_read), test_image_png.c_str()));
}
