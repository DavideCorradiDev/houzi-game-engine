// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/image_file.hpp"

#include "hou/sys/binary_file_in.hpp"
#include "hou/sys/image.hpp"
#include "hou/sys/sys_exceptions.hpp"

#include "hou/cor/narrow_cast.hpp"

#include "hou/mth/matrix.hpp"

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
  }
  HOU_ERROR_N(invalid_enum,
    narrow_cast<int>(
      static_cast<std::underlying_type<pixel_format>::type>(pf)));
  return 0u;
}



bool soil_test_memory(SoilTestFunction test_fun, uchar* buffer, size_t size)
{
  return test_fun(buffer, narrow_cast<int>(size)) != 0;
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
  if(test_fun(buffer, narrow_cast<int>(size)) == 0)
  {
    return std::make_tuple(image2<PF>(), false);
  }

  int width;
  int height;
  uchar* raw_image = load_fun(buffer, narrow_cast<int>(size), &width, &height,
    nullptr, pixel_format_to_soil_format(PF));
  if(raw_image == nullptr)
  {
    return std::make_tuple(image2<PF>(), false);
  }

  vec2u image_size(narrow_cast<uint>(width), narrow_cast<uint>(height));
  image2<PF> ret_image(image_size,
    span<const typename image2<PF>::pixel_type>(
      reinterpret_cast<const typename image2<PF>::pixel_type*>(raw_image),
      width * height));
  SOIL_free_image_data(raw_image);
  return std::make_tuple(ret_image, true);
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
  HOU_CHECK_0(rv, invalid_image_data);
  return im;
}



template <pixel_format PF>
bool soil_write_to_file(
  const std::string& path, int imageType, const image2<PF>& image)
{
  if(check_dir(path))
  {
    return false;
  }

  // Since SOIL does not support UNICODE filenames, first save the image to
  // a file with a standardized name, then rename the file to what is requested.
  static constexpr char tmpFileName[] = ".HziTmpImageFileName.hou";

  int saveResult = SOIL_save_image(tmpFileName, imageType, image.get_size().x(),
    image.get_size().y(), image2<PF>::pixel_type::get_byte_count(),
    reinterpret_cast<const uchar*>(image.get_pixels().data()));
  return saveResult && rename_dir(tmpFileName, path);
}



template <pixel_format PF>
void soil_write_to_file_with_check(
  const std::string& path, int imageType, const image2<PF>& im)
{
  HOU_CHECK_0(soil_write_to_file<PF>(path, imageType, im), invalid_image_data);
}

}  // namespace



bool bmp_image_file::check(const std::string& path)
{
  return soil_test_file(stbi_bmp_test_memory, path);
}



template <pixel_format PF>
image2<PF> bmp_image_file::read(const std::string& path)
{
  return soil_load_from_file_with_check<PF>(
    stbi_bmp_load_from_memory, stbi_bmp_test_memory, path);
}



template <pixel_format PF>
void bmp_image_file::write(const std::string& path, const image2<PF>& im)
{
  soil_write_to_file_with_check<PF>(path, SOIL_SAVE_TYPE_BMP, im);
}



bool png_image_file::check(const std::string& path)
{
  return soil_test_file(stbi_png_test_memory, path);
}



template <pixel_format PF>
image2<PF> png_image_file::read(const std::string& path)
{
  return soil_load_from_file_with_check<PF>(
    stbi_png_load_from_memory, stbi_png_test_memory, path);
}



bool jpg_image_file::check(const std::string& path)
{
  return soil_test_file(stbi_jpeg_test_memory, path);
}



template <pixel_format PF>
image2<PF> jpg_image_file::read(const std::string& path)
{
  return soil_load_from_file_with_check<PF>(
    stbi_jpeg_load_from_memory, stbi_jpeg_test_memory, path);
}



#define INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(image_file_class, PF)  \
  template image2<PF> image_file_class::read<PF>(const std::string&);



#define INSTANTIATE_READ_FILE_FUNCTION(image_file_class)                       \
  INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(                             \
    image_file_class, pixel_format::r)                                         \
  INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(                             \
    image_file_class, pixel_format::rg)                                        \
  INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(                             \
    image_file_class, pixel_format::rgb)                                       \
  INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(                             \
    image_file_class, pixel_format::rgba)



#define INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(image_file_class, PF) \
  template void image_file_class::write<PF>(                                   \
    const std::string&, const image2<PF>&);



#define INSTANTIATE_WRITE_FILE_FUNCTION(image_file_class)                      \
  INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(                            \
    image_file_class, pixel_format::r)                                         \
  INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(                            \
    image_file_class, pixel_format::rg)                                        \
  INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(                            \
    image_file_class, pixel_format::rgb)                                       \
  INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(                            \
    image_file_class, pixel_format::rgba)



INSTANTIATE_READ_FILE_FUNCTION(bmp_image_file)
INSTANTIATE_WRITE_FILE_FUNCTION(bmp_image_file)

INSTANTIATE_READ_FILE_FUNCTION(png_image_file)

INSTANTIATE_READ_FILE_FUNCTION(jpg_image_file)

}  // namespace hou
