// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/image.hpp"

#include "hou/cor/assertions.hpp"

#include "hou/sys/binary_file_in.hpp"
#include "hou/sys/sys_exceptions.hpp"

#include "soil/SOIL.h"

#include <functional>



// SOIL forward declarations.
// These functions are not included in SOIL.h
// Include the header stb_image_aug causes issues.
extern "C" {

int stbi_bmp_test_memory(unsigned char const* buffer, int len);
unsigned char* stbi_bmp_load_from_memory(unsigned char const* buffer, int len,
  int* x, int* y, int* comp, int req_comp);
int stbi_png_test_memory(unsigned char const* buffer, int len);
unsigned char* stbi_png_load_from_memory(unsigned char const* buffer, int len,
  int* x, int* y, int* comp, int req_comp);
int stbi_jpeg_test_memory(unsigned char const* buffer, int len);
unsigned char* stbi_jpeg_load_from_memory(unsigned char const* buffer, int len,
  int* x, int* y, int* comp, int req_comp);
}


namespace hou
{

namespace
{

template <size_t Dim>
bool element_wise_lower_or_equal(
  const vec<uint, Dim>& lhs, const vec<uint, Dim>& rhs);

template <size_t DimOut, size_t DimIn>
vec<uint, DimOut> pad_vector(const vec<uint, DimIn>& vec_in, uint value);

template <pixel_format PF>
image1<PF> get_image_sub_image(
  const image1<PF>& in, const vec1u& offset, const vec1u& size);

template <pixel_format PF>
image2<PF> get_image_sub_image(
  const image2<PF>& in, const vec2u& offset, const vec2u& size);

template <pixel_format PF>
image3<PF> get_image_sub_image(
  const image3<PF>& in, const vec3u& offset, const vec3u& size);

template <pixel_format PF>
void set_image_sub_image(
  image1<PF>& out, const vec1u& offset, const image1<PF>& in);

template <pixel_format PF>
void set_image_sub_image(
  image2<PF>& out, const vec2u& offset, const image2<PF>& in);

template <pixel_format PF>
void set_image_sub_image(
  image3<PF>& out, const vec3u& offset, const image1<PF>& in);

using SoilTestFunction = std::function<int(uchar const*, int)>;
using SoilLoadFunction
  = std::function<uchar*(uchar const*, int, int*, int*, int*, int)>;

int pixel_format_to_soil_format(pixel_format pf);

bool soil_test_memory(SoilTestFunction test_fun, uchar* buffer, size_t size);
bool soil_test_file(SoilTestFunction test_fun, const std::string& path);
template <pixel_format PF>
std::tuple<image2<PF>, bool> soil_load_from_memory(SoilLoadFunction load_fun,
  SoilTestFunction test_fun, uchar* buffer, size_t size);
template <pixel_format PF>
std::tuple<image2<PF>, bool> soil_load_from_file(SoilLoadFunction load_fun,
  SoilTestFunction test_fun, const std::string& path);
template <pixel_format PF>
image2<PF> soil_load_from_file_with_check(SoilLoadFunction load_fun,
  SoilTestFunction test_fun, const std::string& path);
template <pixel_format PF>
bool soil_write_to_file(
  const std::string& path, int imageType, const image2<PF>& im);
template <pixel_format PF>
void soil_write_to_file_with_check(
  const std::string& path, int imageType, const image2<PF>& im);



template <size_t Dim>
bool element_wise_lower_or_equal(
  const vec<uint, Dim>& lhs, const vec<uint, Dim>& rhs)
{
  for(size_t i = 0; i < Dim; ++i)
  {
    if(lhs(i) > rhs(i))
    {
      return false;
    }
  }
  return true;
}



template <size_t DimOut, size_t DimIn>
vec<uint, DimOut> pad_vector(const vec<uint, DimIn>& vec_in, uint value)
{
  vec<uint, DimOut> vec_out = vec<uint, DimOut>::filled(value);
  for(size_t i = 0; i < std::min(DimOut, DimIn); ++i)
  {
    vec_out(i) = vec_in(i);
  }
  return vec_out;
}



template <pixel_format PF>
image1<PF> get_image_sub_image(
  const image1<PF>& in, const vec1u& offset, const vec1u& size)
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + size, in.get_size()));
  image1<PF> out(size);
  for(uint x = 0; x < size.x(); ++x)
  {
    vec1u pos = vec1u(x);
    out.set_pixel(pos, in.get_pixel(offset + pos));
  }
  return out;
}



template <pixel_format PF>
image2<PF> get_image_sub_image(
  const image2<PF>& in, const vec2u& offset, const vec2u& size)
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + size, in.get_size()));
  image2<PF> out(size);
  for(uint x = 0; x < size.x(); ++x)
  {
    for(uint y = 0; y < size.y(); ++y)
    {
      vec2u pos = vec2u(x, y);
      out.set_pixel(pos, in.get_pixel(offset + pos));
    }
  }
  return out;
}



template <pixel_format PF>
image3<PF> get_image_sub_image(
  const image3<PF>& in, const vec3u& offset, const vec3u& size)
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + size, in.get_size()));
  image3<PF> out(size);
  for(uint x = 0; x < size.x(); ++x)
  {
    for(uint y = 0; y < size.y(); ++y)
    {
      for(uint z = 0; z < size.z(); ++z)
      {
        vec3u pos = vec3u(x, y, z);
        out.set_pixel(pos, in.get_pixel(offset + pos));
      }
    }
  }
  return out;
}



template <pixel_format PF>
void set_image_sub_image(
  image1<PF>& out, const vec1u& offset, const image1<PF>& in)
{
  HOU_PRECOND(
    element_wise_lower_or_equal(offset + in.get_size(), out.get_size()));
  for(uint x = 0; x < in.get_size().x(); ++x)
  {
    vec1u pos = vec1u(x);
    out.set_pixel(offset + pos, in.get_pixel(pos));
  }
}



template <pixel_format PF>
void set_image_sub_image(
  image2<PF>& out, const vec2u& offset, const image2<PF>& in)
{
  HOU_PRECOND(
    element_wise_lower_or_equal(offset + in.get_size(), out.get_size()));
  for(uint x = 0; x < in.get_size().x(); ++x)
  {
    for(uint y = 0; y < in.get_size().y(); ++y)
    {
      vec2u pos = vec2u(x, y);
      out.set_pixel(offset + pos, in.get_pixel(pos));
    }
  }
}



template <pixel_format PF>
void set_image_sub_image(
  image3<PF>& out, const vec3u& offset, const image3<PF>& in)
{
  HOU_PRECOND(
    element_wise_lower_or_equal(offset + in.get_size(), out.get_size()));
  for(uint x = 0; x < in.get_size().x(); ++x)
  {
    for(uint y = 0; y < in.get_size().y(); ++y)
    {
      for(uint z = 0; z < in.get_size().z(); ++z)
      {
        vec3u pos = vec3u(x, y, z);
        out.set_pixel(offset + pos, in.get_pixel(pos));
      }
    }
  }
}



int pixel_format_to_soil_format(pixel_format pf)
{
  switch(pf)
  {
    case pixel_format::r:
      return SOIL_LOAD_L;
    case pixel_format::rg:
      return SOIL_LOAD_LA;
    case pixel_format::rgb:
      return SOIL_LOAD_RGB;
    case pixel_format::rgba:
      return SOIL_LOAD_RGBA;
    default:
      HOU_UNREACHABLE();
      return 0u;
  }
}



bool soil_test_memory(SoilTestFunction test_fun, uchar* buffer, size_t size)
{
  return test_fun(buffer, size) != 0;
}



bool soil_test_file(SoilTestFunction test_fun, const std::string& path)
{
  binary_file_in fi(path);
  std::vector<uchar> buffer(fi.get_byte_count());
  fi.read(buffer);
  return soil_test_memory(test_fun, buffer.data(), buffer.size());
}



template <pixel_format PF>
std::tuple<image2<PF>, bool> soil_load_from_memory(SoilLoadFunction load_fun,
  SoilTestFunction test_fun, uchar* buffer, size_t size)
{
  if(test_fun(buffer, size) == 0)
  {
    return std::make_tuple(image2<PF>(), false);
  }

  int width;
  int height;
  uchar* raw_image = load_fun(buffer, static_cast<int>(size), &width, &height,
    nullptr, pixel_format_to_soil_format(PF));
  if(raw_image == nullptr)
  {
    return std::make_tuple(image2<PF>(), false);
  }

  vec2u imageSize(static_cast<uint>(width), static_cast<uint>(height));
  image2<PF> retImage(imageSize,
    span<const typename image2<PF>::pixel>(
      reinterpret_cast<const typename image2<PF>::pixel*>(raw_image),
      width * height));
  SOIL_free_image_data(raw_image);
  return std::make_tuple(retImage, true);
}



template <pixel_format PF>
std::tuple<image2<PF>, bool> soil_load_from_file(
  SoilLoadFunction load_fun, SoilTestFunction test_fun, const std::string& path)
{
  binary_file_in fi(path);
  std::vector<uchar> buffer(fi.get_byte_count());
  fi.read(buffer);
  return soil_load_from_memory<PF>(
    load_fun, test_fun, buffer.data(), buffer.size());
}



template <pixel_format PF>
image2<PF> soil_load_from_file_with_check(
  SoilLoadFunction load_fun, SoilTestFunction test_fun, const std::string& path)
{
  image2<PF> im;
  bool rv = false;
  std::tie(im, rv) = soil_load_from_file<PF>(load_fun, test_fun, path);
  HOU_CHECK_N(rv, image_read_error, path);
  return im;
}



template <pixel_format PF>
bool soil_write_to_file(
  const std::string& path, int imageType, const image2<PF>& image)
{
  // Since SOIL does not support UNICODE filenames, first save the image to
  // a file with a standardized name, then rename the file to what is requested.
  static constexpr char tmpFileName[] = ".HziTmpImageFileName.hou";

  int saveResult = SOIL_save_image(tmpFileName, imageType, image.get_size().x(),
    image.get_size().y(), image2<PF>::pixel::get_byte_count(),
    reinterpret_cast<const uchar*>(image.get_pixels().data()));
  return saveResult && rename_dir(tmpFileName, path);
}



template <pixel_format PF>
void soil_write_to_file_with_check(
  const std::string& path, int imageType, const image2<PF>& im)
{
  HOU_CHECK_N(
    soil_write_to_file<PF>(path, imageType, im), image_write_error, path);
}

}  // namespace



bool bmp_check_file(const std::string& path)
{
  return soil_test_file(stbi_bmp_test_memory, path);
}



template <pixel_format PF>
image2<PF> bmp_read_file(const std::string& path)
{
  return soil_load_from_file_with_check<PF>(
    stbi_bmp_load_from_memory, stbi_bmp_test_memory, path);
}



template <pixel_format PF>
void bmp_write_file(const std::string& path, const image2<PF>& image)
{
  soil_write_to_file_with_check<PF>(path, SOIL_SAVE_TYPE_BMP, image);
}



bool png_check_file(const std::string& path)
{
  return soil_test_file(stbi_png_test_memory, path);
}



template <pixel_format PF>
image2<PF> png_read_file(const std::string& path)
{
  return soil_load_from_file_with_check<PF>(
    stbi_png_load_from_memory, stbi_png_test_memory, path);
}



bool jpg_check_file(const std::string& path)
{
  return soil_test_file(stbi_jpeg_test_memory, path);
}



template <pixel_format PF>
image2<PF> jpg_read_file(const std::string& path)
{
  return soil_load_from_file_with_check<PF>(
    stbi_jpeg_load_from_memory, stbi_jpeg_test_memory, path);
}



template <size_t Dim, pixel_format PF>
image<Dim, PF>::image() noexcept
  : m_size()
  , m_pixels()
{}



template <size_t Dim, pixel_format PF>
image<Dim, PF>::image(const size_type& size) noexcept
  : m_size(size)
  , m_pixels(compute_pixel_count(), pixel())
{}



template <size_t Dim, pixel_format PF>
image<Dim, PF>::image(const size_type& size, const pixel& px) noexcept
  : m_size(size)
  , m_pixels(compute_pixel_count(), px)
{}



template <size_t Dim, pixel_format PF>
image<Dim, PF>::image(const size_type& size, const span<const pixel>& pixels)
  : m_size(size)
  , m_pixels(pixels.begin(), pixels.end())
{
  HOU_PRECOND(pixels.size() == compute_pixel_count());
}



template <size_t Dim, pixel_format PF>
image<Dim, PF>::image(const size_type& size, pixel_collection&& pixels)
  : m_size(size)
  , m_pixels(pixels)
{
  HOU_PRECOND(m_pixels.size() == compute_pixel_count());
}



template <size_t Dim, pixel_format PF>
template <size_t otherDim, pixel_format otherFmt, typename Enable>
image<Dim, PF>::image(const image<otherDim, otherFmt>& other)
  : m_size(pad_vector<Dim>(other.get_size(), 1u))
  , m_pixels(compute_pixel_count())
{
  for(size_t i = 0; i < m_pixels.size(); ++i)
  {
    m_pixels[i] = other.m_pixels[i];
  }
}



template <size_t Dim, pixel_format PF>
const typename image<Dim, PF>::size_type& image<Dim, PF>::get_size() const
{
  return m_size;
}



template <size_t Dim, pixel_format PF>
const typename image<Dim, PF>::pixel_collection& image<Dim, PF>::get_pixels()
  const
{
  return m_pixels;
}



template <size_t Dim, pixel_format PF>
void image<Dim, PF>::set_pixels(const span<const pixel>& pixels)
{
  HOU_PRECOND(pixels.size() == m_pixels.size());
  std::copy(pixels.begin(), pixels.end(), m_pixels.begin());
}



template <size_t Dim, pixel_format PF>
const typename image<Dim, PF>::pixel& image<Dim, PF>::get_pixel(
  const offset_type& coordinates) const
{
  return m_pixels[compute_pixel_index(coordinates)];
}



template <size_t Dim, pixel_format PF>
void image<Dim, PF>::set_pixel(
  const offset_type& coordinates, const pixel& value)
{
  m_pixels[compute_pixel_index(coordinates)] = value;
}



template <size_t Dim, pixel_format PF>
void image<Dim, PF>::clear(const pixel& pixel)
{
  m_pixels = pixel_collection(compute_pixel_count(), pixel);
}



template <size_t Dim, pixel_format PF>
image<Dim, PF> image<Dim, PF>::get_sub_image(
  const offset_type& offset, const size_type& size)
{
  return get_image_sub_image(*this, offset, size);
}



template <size_t Dim, pixel_format PF>
void image<Dim, PF>::set_sub_image(const offset_type& offset, const image& im)
{
  return set_image_sub_image(*this, offset, im);
}



template <size_t Dim, pixel_format PF>
size_t image<Dim, PF>::compute_pixel_count() const
{
  size_t retval = 1u;
  for(size_t i = 0; i < Dim; ++i)
  {
    retval *= m_size(i);
  }
  return retval;
}



template <size_t Dim, pixel_format PF>
size_t image<Dim, PF>::compute_pixel_index(const offset_type& coordinates) const
{
  for(size_t i = 0; i < Dim; ++i)
  {
    HOU_PRECOND(coordinates(i) < m_size(i));
  }

  size_t idx = 0;
  size_t multiplier = 1;
  for(size_t i = 0; i < Dim; ++i)
  {
    idx += coordinates(i) * multiplier;
    multiplier *= m_size(i);
  }
  return idx;
}



template <size_t Dim, pixel_format PF>
bool operator==(const image<Dim, PF>& lhs, const image<Dim, PF>& rhs)
{
  return lhs.get_size() == rhs.get_size()
    && lhs.get_pixels() == rhs.get_pixels();
}



template <size_t Dim, pixel_format PF>
bool operator!=(const image<Dim, PF>& lhs, const image<Dim, PF>& rhs)
{
  return !(lhs == rhs);
}



template <size_t Dim, pixel_format PF>
std::ostream& operator<<(std::ostream& os, const image<Dim, PF>& im)
{
  return os << "{size_type = " << transpose(im.get_size())
            << ", pixels = " << im.get_pixels() << "}";
}



#define INSTANTIATE_IMAGE_BASE(Dim, PF)                                        \
  template class image<Dim, PF>;                                               \
  template bool operator==<Dim, PF>(                                           \
    const image<Dim, PF>&, const image<Dim, PF>&);                             \
  template bool operator!=<Dim, PF>(                                           \
    const image<Dim, PF>&, const image<Dim, PF>&);                             \
  template std::ostream& operator<<<Dim, PF>(                                  \
    std::ostream&, const image<Dim, PF>&);



#define INSTANTIATE_CONVERSION_CONSTRUCTOR(Dim1, Dim2, pf1, pf2)               \
  template image<Dim1, pf1>::image<Dim2, pf2, void>(const image<Dim2, pf2>&);



#define INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIMENSIONS(Dim1, Dim2)        \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::r, pixel_format::rg)                             \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::r, pixel_format::rgb)                            \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::r, pixel_format::rgba)                           \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rg, pixel_format::r)                             \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rg, pixel_format::rgb)                           \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rg, pixel_format::rgba)                          \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgb, pixel_format::r)                            \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgb, pixel_format::rg)                           \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgb, pixel_format::rgba)                         \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgba, pixel_format::r)                           \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgba, pixel_format::rg)                          \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgba, pixel_format::rgb)



#define INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_SAME_DIMENSION(Dim)           \
  INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIMENSIONS(Dim, Dim)



#define INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIFFERENT_DIMENSIONS(         \
  Dim1, Dim2)                                                                  \
  INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIMENSIONS(Dim1, Dim2)              \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::r, pixel_format::r)                              \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rg, pixel_format::rg)                            \
    INSTANTIATE_CONVERSION_CONSTRUCTOR(Dim1, Dim2, pixel_format::rgb,          \
      pixel_format::rgb) INSTANTIATE_CONVERSION_CONSTRUCTOR(Dim1, Dim2,        \
      pixel_format::rgba, pixel_format::rgba)



#define INSTANTIATE_IMAGE_WITH_DIMENSION(Dim)                                  \
  INSTANTIATE_IMAGE_BASE(Dim, pixel_format::r)                                 \
  INSTANTIATE_IMAGE_BASE(Dim, pixel_format::rg)                                \
  INSTANTIATE_IMAGE_BASE(Dim, pixel_format::rgb)                               \
  INSTANTIATE_IMAGE_BASE(Dim, pixel_format::rgba)



INSTANTIATE_IMAGE_WITH_DIMENSION(1u)
INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_SAME_DIMENSION(
  1u) INSTANTIATE_IMAGE_WITH_DIMENSION(2u)
  INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIFFERENT_DIMENSIONS(2u, 1u)
    INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_SAME_DIMENSION(2u)
      INSTANTIATE_IMAGE_WITH_DIMENSION(3u)
        INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIFFERENT_DIMENSIONS(3u, 1u)
          INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIFFERENT_DIMENSIONS(3u, 2u)
            INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_SAME_DIMENSION(3u)



#define INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, PF)            \
  template image2<PF> imType##_read_file<PF>(const std::string&);



#define INSTANTIATE_READ_FILE_FUNCTION(imType)                                 \
  INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, pixel_format::r)     \
  INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, pixel_format::rg)    \
  INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, pixel_format::rgb)   \
  INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, pixel_format::rgba)



#define INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, PF)           \
  template void imType##_write_file<PF>(const std::string&, const image2<PF>&);



#define INSTANTIATE_WRITE_FILE_FUNCTION(imType)                                \
  INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, pixel_format::r)    \
  INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, pixel_format::rg)   \
  INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, pixel_format::rgb)  \
  INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, pixel_format::rgba)

              INSTANTIATE_READ_FILE_FUNCTION(bmp)
                INSTANTIATE_READ_FILE_FUNCTION(png)
                  INSTANTIATE_READ_FILE_FUNCTION(jpg)

                    INSTANTIATE_WRITE_FILE_FUNCTION(bmp)

}  // namespace hou
