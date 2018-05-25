// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/sys/image.hpp"

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
    const typename ImageT::size_type& s);

  static size_t multiply_elements(const typename ImageT::size_type& s);

  static size_t compute_pixel_index(
    const typename ImageT::offset_type& coordinates,
    const typename ImageT::size_type& s);

  static typename ImageT::offset_type compute_pixel_coordinates(
    size_t index, const typename ImageT::size_type& s);
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
  const typename ImageT::size_type& s)
{
  typename ImageT::pixel_collection retval(multiply_elements(s));
  for(size_t i = 0; i < retval.size(); ++i)
  {
    typename ImageT::pixel px;
    px.set_r(static_cast<uint8_t>(i));
    retval[i] = px;
  }
  return retval;
}



template <typename ImageT>
size_t test_image<ImageT>::multiply_elements(
  const typename ImageT::size_type& s)
{
  size_t retval = s(0);
  for(size_t i = 1; i < s.size(); ++i)
  {
    retval *= s(i);
  }
  return retval;
}



template <typename ImageT>
size_t test_image<ImageT>::compute_pixel_index(
  const typename ImageT::offset_type& coordinates,
  const typename ImageT::size_type& s)
{
  size_t idx = 0;
  size_t multiplier = 1;
  for(size_t i = 0; i < coordinates.size(); ++i)
  {
    idx += coordinates(i) * multiplier;
    multiplier *= s(i);
  }
  return idx;
}



template <typename ImageT>
typename ImageT::offset_type test_image<ImageT>::compute_pixel_coordinates(
  size_t index, const typename ImageT::size_type& s)
{
  using offset_type = typename ImageT::offset_type;

  offset_type coords;
  size_t divider = multiply_elements(s);
  for(size_t i = s.size() - 1; i > 0; --i)
  {
    divider /= s(i);
    coords(i) = static_cast<uint>(index / divider);
    index %= divider;
  }
  coords(0) = static_cast<uint>(index);
  return coords;
}

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

  for(size_t i = 0; i < size_ref.size(); ++i)
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
  for(size_t i = 0; i < size_ref.size(); ++i)
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

  size_type image_size;
  size_type sub_image_size;
  offset_type sub_image_offset;
  for(size_t i = 0; i < image_size.size(); ++i)
  {
    image_size(i) = static_cast<uint>((i + 1) * 4);
    sub_image_size(i) = static_cast<uint>((i + 1) * 2);
    sub_image_offset(i) = static_cast<uint>(i + 1);
  }

  pixel_collection pixels_ref = TestFixture::generate_pixels(image_size);
  pixel_collection subPixels_ref(
    TestFixture::multiply_elements(sub_image_size));
  for(size_t i = 0; i < subPixels_ref.size(); ++i)
  {
    offset_type subImageCoords
      = TestFixture::compute_pixel_coordinates(i, sub_image_size);
    offset_type imageCoords = sub_image_offset + subImageCoords;
    subPixels_ref[i]
      = pixels_ref[TestFixture::compute_pixel_index(imageCoords, image_size)];
  }

  TypeParam image(image_size, pixels_ref);
  TypeParam sub_image_ref(sub_image_size, subPixels_ref);
  EXPECT_EQ(
    sub_image_ref, image.get_sub_image(sub_image_offset, sub_image_size));
}



TYPED_TEST(test_image_death_test, get_sub_image_error_overflow)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type image_size;
  size_type sub_image_size;
  offset_type sub_image_offset;
  for(size_t i = 0; i < image_size.size(); ++i)
  {
    image_size(i) = static_cast<uint>((i + 1) * 4);
    sub_image_offset(i) = static_cast<uint>(i + 1);
    sub_image_size(i) = static_cast<uint>((i + 1) * 4 - sub_image_offset(i) + 1u);
  }

  TypeParam image(image_size);
  EXPECT_ERROR_0(
    image.get_sub_image(sub_image_offset, sub_image_size), out_of_range);
}



TYPED_TEST(test_image, set_sub_image)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type image_size;
  size_type sub_image_size;
  offset_type sub_image_offset;
  for(size_t i = 0; i < image_size.size(); ++i)
  {
    image_size(i) = static_cast<uint>((i + 1) * 4);
    sub_image_size(i) = static_cast<uint>((i + 1) * 2);
    sub_image_offset(i) = static_cast<uint>(i + 1);
  }

  pixel_collection pixels_ref(TestFixture::multiply_elements(image_size));
  pixel_collection subPixels_ref(TestFixture::generate_pixels(sub_image_size));
  for(size_t i = 0; i < subPixels_ref.size(); ++i)
  {
    offset_type subImageCoords
      = TestFixture::compute_pixel_coordinates(i, sub_image_size);
    offset_type imageCoords = sub_image_offset + subImageCoords;
    pixels_ref[TestFixture::compute_pixel_index(imageCoords, image_size)]
      = subPixels_ref[i];
  }

  TypeParam image(image_size);
  TypeParam image_ref(image_size, pixels_ref);
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

  size_type image_size;
  size_type sub_image_size;
  offset_type sub_image_offset;
  for(size_t i = 0; i < image_size.size(); ++i)
  {
    image_size(i) = static_cast<uint>((i + 1) * 4);
    sub_image_offset(i) = static_cast<uint>(i + 1);
    sub_image_size(i) = static_cast<uint>((i + 1) * 4 - sub_image_offset(i) + 1u);
  }

  TypeParam image(image_size);
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
  ss << "{size = " << transpose(size_ref) << ", pixels = " << pixels_ref << "}";

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
  image2_r::size_type s(2u, 3u);
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

  image2_r im_r(s, pixelsR);
  image2_rgba im_rgba(im_r);

  EXPECT_EQ(s, im_rgba.get_size());
  EXPECT_EQ(pixelsRGBA, im_rgba.get_pixels());
}



TEST_F(test_image_conversion_constructor, rg2_rgba_constructor)
{
  image2_rg::size_type s(2u, 3u);
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

  image2_rg im_rg(s, pixelsRG);
  image2_rgba im_rgba(im_rg);

  EXPECT_EQ(s, im_rgba.get_size());
  EXPECT_EQ(pixelsRGBA, im_rgba.get_pixels());
}



TEST_F(test_image_conversion_constructor, rgb2_rgba_constructor)
{
  image2_rgb::size_type s(2u, 3u);
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

  image2_rgb im_rgb(s, pixelsRGB);
  image2_rgba im_rgba(im_rgb);

  EXPECT_EQ(s, im_rgba.get_size());
  EXPECT_EQ(pixelsRGBA, im_rgba.get_pixels());
}



TEST_F(test_image_conversion_constructor, image1_to_image2_constructor)
{
  image1_rgb::size_type s(3u);
  image1_rgba::pixel_collection pixelsRGBA{
    image1_rgba::pixel(200u, 118u, 93u, 255u),
    image1_rgba::pixel(3u, 12u, 3u, 255u),
    image1_rgba::pixel(5u, 11u, 2u, 255u),
  };
  image1_rgba image1_rgba(s, pixelsRGBA);
  image2_rgba image2_rgba(image1_rgba);
  EXPECT_EQ(vec2u(s.x(), 1u), image2_rgba.get_size());
  EXPECT_EQ(pixelsRGBA, image2_rgba.get_pixels());
}



TEST_F(test_image_conversion_constructor, image1_to_image3_constructor)
{
  image1_rgb::size_type s(3u);
  image1_rgba::pixel_collection pixelsRGBA{
    image1_rgba::pixel(200u, 118u, 93u, 255u),
    image1_rgba::pixel(3u, 12u, 3u, 255u),
    image1_rgba::pixel(5u, 11u, 2u, 255u),
  };
  image1_rgba image1_rgba(s, pixelsRGBA);
  image3_rgba image3_rgba(image1_rgba);
  EXPECT_EQ(vec3u(s.x(), 1u, 1u), image3_rgba.get_size());
  EXPECT_EQ(pixelsRGBA, image3_rgba.get_pixels());
}



TEST_F(test_image_conversion_constructor, image2_to_image3_constructor)
{
  image2_rgb::size_type s(3u, 2u);
  image2_rgba::pixel_collection pixelsRGBA{
    image2_rgba::pixel(200u, 118u, 93u, 255u),
    image2_rgba::pixel(3u, 12u, 3u, 255u),
    image2_rgba::pixel(5u, 11u, 2u, 255u),
    image2_rgba::pixel(200u, 118u, 93u, 255u),
    image2_rgba::pixel(3u, 12u, 3u, 255u),
    image2_rgba::pixel(5u, 11u, 2u, 255u),
  };
  image2_rgba image1_rgba(s, pixelsRGBA);
  image3_rgba image3_rgba(image1_rgba);
  EXPECT_EQ(vec3u(s.x(), s.y(), 1u), image3_rgba.get_size());
  EXPECT_EQ(pixelsRGBA, image3_rgba.get_pixels());
}
