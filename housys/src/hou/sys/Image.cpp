// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/Image.hpp"

#include "hou/cor/Error.hpp"

#include "hou/sys/BinaryFileIn.hpp"
#include "hou/sys/SysError.hpp"

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

template <size_t dim>
bool elementWiseLowerOrEqual(const Vec<uint, dim>& lhs, const Vec<uint, dim>& rhs);

template <size_t dimOut, size_t dimIn>
  Vec<uint, dimOut> padVector(const Vec<uint, dimIn>& vecIn, uint value);

template <PixelFormat fmt>
Image1<fmt> getImageSubImage(
  const Image1<fmt>& in, const Vec1u& offset, const Vec1u& size);

template <PixelFormat fmt>
Image2<fmt> getImageSubImage(
  const Image2<fmt>& in, const Vec2u& offset, const Vec2u& size);

template <PixelFormat fmt>
Image3<fmt> getImageSubImage(
  const Image3<fmt>& in, const Vec3u& offset, const Vec3u& size);

template <PixelFormat fmt>
void setImageSubImage(
  Image1<fmt>& out, const Vec1u& offset, const Image1<fmt>& in);

template <PixelFormat fmt>
void setImageSubImage(
  Image2<fmt>& out, const Vec2u& offset, const Image2<fmt>& in);

template <PixelFormat fmt>
void setImageSubImage(
  Image3<fmt>& out, const Vec3u& offset, const Image1<fmt>& in);

using SoilTestFunction = std::function<int(uchar const*, int)>;
using SoilLoadFunction
  = std::function<uchar*(uchar const*, int, int*, int*, int*, int)>;

int pixelFormatToSoilFormat(PixelFormat fmt);

bool soilTestMemory(SoilTestFunction testFun, uchar* buffer, size_t size);
bool soilTestFile(SoilTestFunction testFun, const std::string& path);
template <PixelFormat fmt>
std::tuple<Image2<fmt>, bool> soilLoadFromMemory(SoilLoadFunction loadFun,
  SoilTestFunction testFun, uchar* buffer, size_t size);
template <PixelFormat fmt>
std::tuple<Image2<fmt>, bool> soilLoadFromFile(
  SoilLoadFunction loadFun, SoilTestFunction testFun, const std::string& path);
template <PixelFormat fmt>
Image2<fmt> soilLoadFromFileWithCheck(SoilLoadFunction loadFun,
  SoilTestFunction testFun, const std::string& path, SysError ec);
template <PixelFormat fmt>
bool soilWriteToFile(
  const std::string& path, int imageType, const Image2<fmt>& im);
template <PixelFormat fmt>
void soilWriteToFileWithCheck(
  const std::string& path, int imageType, const Image2<fmt>& im, SysError ec);



template <size_t dim>
bool elementWiseLowerOrEqual(
  const Vec<uint, dim>& lhs, const Vec<uint, dim>& rhs)
{
  for(size_t i = 0; i < dim; ++i)
  {
    if(lhs(i) > rhs(i))
    {
      return false;
    }
  }
  return true;
}




template <size_t dimOut, size_t dimIn>
  Vec<uint, dimOut> padVector(const Vec<uint, dimIn>& vecIn, uint value)
{
  Vec<uint, dimOut> vecOut = Vec<uint, dimOut>::filled(value);
  for(size_t i = 0; i < std::min(dimOut, dimIn); ++i)
  {
    vecOut(i) = vecIn(i);
  }
  return vecOut;
}



template <PixelFormat fmt>
Image1<fmt> getImageSubImage(
  const Image1<fmt>& in, const Vec1u& offset, const Vec1u& size)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, in.getSize()));
  Image1<fmt> out(size);
  for(uint x = 0; x < size.x(); ++x)
  {
    Vec1u pos = Vec1u(x);
    out.getPixel(pos) = in.getPixel(offset + pos);
  }
  return out;
}



template <PixelFormat fmt>
Image2<fmt> getImageSubImage(
  const Image2<fmt>& in, const Vec2u& offset, const Vec2u& size)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, in.getSize()));
  Image2<fmt> out(size);
  for(uint x = 0; x < size.x(); ++x)
  {
    for(uint y = 0; y < size.y(); ++y)
    {
      Vec2u pos = Vec2u(x, y);
      out.getPixel(pos) = in.getPixel(offset + pos);
    }
  }
  return out;
}



template <PixelFormat fmt>
Image3<fmt> getImageSubImage(
  const Image3<fmt>& in, const Vec3u& offset, const Vec3u& size)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + size, in.getSize()));
  Image3<fmt> out(size);
  for(uint x = 0; x < size.x(); ++x)
  {
    for(uint y = 0; y < size.y(); ++y)
    {
      for(uint z = 0; z < size.z(); ++z)
      {
        Vec3u pos = Vec3u(x, y, z);
        out.getPixel(pos) = in.getPixel(offset + pos);
      }
    }
  }
  return out;
}




template <PixelFormat fmt>
void setImageSubImage(
  Image1<fmt>& out, const Vec1u& offset, const Image1<fmt>& in)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + in.getSize(), out.getSize()));
  for(uint x = 0; x < in.getSize().x(); ++x)
  {
    Vec1u pos = Vec1u(x);
    out.getPixel(offset + pos) = in.getPixel(pos);
  }
}



template <PixelFormat fmt>
void setImageSubImage(
  Image2<fmt>& out, const Vec2u& offset, const Image2<fmt>& in)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + in.getSize(), out.getSize()));
  for(uint x = 0; x < in.getSize().x(); ++x)
  {
    for(uint y = 0; y < in.getSize().y(); ++y)
    {
      Vec2u pos = Vec2u(x, y);
      out.getPixel(offset + pos) = in.getPixel(pos);
    }
  }
}



template <PixelFormat fmt>
void setImageSubImage(
  Image3<fmt>& out, const Vec3u& offset, const Image3<fmt>& in)
{
  HOU_EXPECT(elementWiseLowerOrEqual(offset + in.getSize(), out.getSize()));
  for(uint x = 0; x < in.getSize().x(); ++x)
  {
    for(uint y = 0; y < in.getSize().y(); ++y)
    {
      for(uint z = 0; z < in.getSize().z(); ++z)
      {
        Vec3u pos = Vec3u(x, y, z);
        out.getPixel(offset + pos) = in.getPixel(pos);
      }
    }
  }
}



int pixelFormatToSoilFormat(PixelFormat fmt)
{
  switch(fmt)
  {
  case PixelFormat::R:
    return SOIL_LOAD_L;
  case PixelFormat::RG:
    return SOIL_LOAD_LA;
  case PixelFormat::RGB:
    return SOIL_LOAD_RGB;
  case PixelFormat::RGBA:
    return SOIL_LOAD_RGBA;
  default:
    HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), static_cast<int>(fmt));
    return 0u;
  }
}



bool soilTestMemory(SoilTestFunction testFun, uchar* buffer, size_t size)
{
  return testFun(buffer, size) != 0;
}



bool soilTestFile(SoilTestFunction testFun, const std::string& path)
{
  BinaryFileIn fi(path);
  std::vector<uchar> buffer(fi.getByteCount());
  fi.read(buffer);
  return soilTestMemory(testFun, buffer.data(), buffer.size());
}



template <PixelFormat fmt>
std::tuple<Image2<fmt>, bool> soilLoadFromMemory(SoilLoadFunction loadFun,
  SoilTestFunction testFun, uchar* buffer, size_t size)
{
  if(testFun(buffer, size) == 0)
  {
    return std::make_tuple(Image2<fmt>(), false);
  }

  int width;
  int height;
  uchar* rawImage = loadFun(buffer, static_cast<int>(size), &width, &height,
    nullptr, pixelFormatToSoilFormat(fmt));
  if(rawImage == nullptr)
  {
    return std::make_tuple(Image2<fmt>(), false);
  }

  Vec2u imageSize(static_cast<uint>(width), static_cast<uint>(height));
  Image2<fmt> retImage(imageSize,
    Span<const typename Image2<fmt>::Pixel>(
      reinterpret_cast<const typename Image2<fmt>::Pixel*>(rawImage),
      width * height));
  SOIL_free_image_data(rawImage);
  return std::make_tuple(retImage, true);
}



template <PixelFormat fmt>
std::tuple<Image2<fmt>, bool> soilLoadFromFile(
  SoilLoadFunction loadFun, SoilTestFunction testFun, const std::string& path)
{
  BinaryFileIn fi(path);
  std::vector<uchar> buffer(fi.getByteCount());
  fi.read(buffer);
  return soilLoadFromMemory<fmt>(
    loadFun, testFun, buffer.data(), buffer.size());
}



template <PixelFormat fmt>
Image2<fmt> soilLoadFromFileWithCheck(SoilLoadFunction loadFun,
  SoilTestFunction testFun, const std::string& path, SysError ec)
{
  Image2<fmt> im;
  bool rv = false;
  std::tie(im, rv) = soilLoadFromFile<fmt>(loadFun, testFun, path);
  HOU_RUNTIME_CHECK(rv, getText(ec), path.c_str());
  return im;
}



template <PixelFormat fmt>
bool soilWriteToFile(
  const std::string& path, int imageType, const Image2<fmt>& image)
{
  // Since SOIL does not support UNICODE filenames, first save the image to
  // a file with a standardized name, then rename the file to what is requested.
  static constexpr char tmpFileName[] = ".HziTmpImageFileName.hou";

  int saveResult = SOIL_save_image(tmpFileName, imageType, image.getSize().x(),
    image.getSize().y(), Image2<fmt>::Pixel::getByteCount(),
    reinterpret_cast<const uchar*>(image.getPixels().data()));
  return saveResult && renameDir(tmpFileName, path);
}



template <PixelFormat fmt>
void soilWriteToFileWithCheck(
  const std::string& path, int imageType, const Image2<fmt>& im, SysError ec)
{
  HOU_RUNTIME_CHECK(
    soilWriteToFile<fmt>(path, imageType, im), getText(ec), path.c_str());
}

}  // namespace



bool bmpCheckFile(const std::string& path)
{
  return soilTestFile(stbi_bmp_test_memory, path);
}



template <PixelFormat fmt>
Image2<fmt> bmpReadFile(const std::string& path)
{
  return soilLoadFromFileWithCheck<fmt>(stbi_bmp_load_from_memory,
    stbi_bmp_test_memory, path, SysError::ImageBmpRead);
}



template <PixelFormat fmt>
void bmpWriteFile(const std::string& path, const Image2<fmt>& image)
{
  soilWriteToFileWithCheck<fmt>(
    path, SOIL_SAVE_TYPE_BMP, image, SysError::ImageBmpWrite);
}



bool pngCheckFile(const std::string& path)
{
  return soilTestFile(stbi_png_test_memory, path);
}



template <PixelFormat fmt>
Image2<fmt> pngReadFile(const std::string& path)
{
  return soilLoadFromFileWithCheck<fmt>(stbi_png_load_from_memory,
    stbi_png_test_memory, path, SysError::ImagePngRead);
}



bool jpgCheckFile(const std::string& path)
{
  return soilTestFile(stbi_jpeg_test_memory, path);
}



template <PixelFormat fmt>
Image2<fmt> jpgReadFile(const std::string& path)
{
  return soilLoadFromFileWithCheck<fmt>(stbi_jpeg_load_from_memory,
    stbi_jpeg_test_memory, path, SysError::ImageJpgRead);
}



template <size_t dim, PixelFormat fmt>
Image<dim, fmt>::Image()
  : mSize()
  , mPixels()
{}



template <size_t dim, PixelFormat fmt>
Image<dim, fmt>::Image(const Size& size)
  : mSize(size)
  , mPixels(computePixelCount(), Pixel())
{}



template <size_t dim, PixelFormat fmt>
Image<dim, fmt>::Image(const Size& size, const Pixel& pixel)
  : mSize(size)
  , mPixels(computePixelCount(), pixel)
{}



template <size_t dim, PixelFormat fmt>
Image<dim, fmt>::Image(const Size& size, const Span<const Pixel>& pixels)
  : mSize(size)
  , mPixels(pixels.begin(), pixels.end())
{
  HOU_EXPECT(pixels.size() == computePixelCount());
}



template <size_t dim, PixelFormat fmt>
Image<dim, fmt>::Image(const Size& size, const Span<const uint8_t>& bytes)
  : Image(size,
      Span<const Pixel>(reinterpret_cast<const Pixel*>(bytes.data()),
        bytes.size() / sizeof(Pixel)))
{}



template <size_t dim, PixelFormat fmt>
template <size_t otherDim, PixelFormat otherFmt, typename Enable>
Image<dim, fmt>::Image(const Image<otherDim, otherFmt>& other)
  : mSize(padVector<dim>(other.getSize(), 1u))
  , mPixels(computePixelCount())
{
  for(size_t i = 0; i < mPixels.size(); ++i)
  {
    mPixels[i] = other.mPixels[i];
  }
}



template <size_t dim, PixelFormat fmt>
const typename Image<dim, fmt>::Size& Image<dim, fmt>::getSize() const
{
  return mSize;
}



template <size_t dim, PixelFormat fmt>
const typename Image<dim, fmt>::PixelCollection& Image<dim, fmt>::getPixels()
  const
{
  return mPixels;
}



template <size_t dim, PixelFormat fmt>
void Image<dim, fmt>::setPixels(const Span<const Pixel>& pixels)
{
  HOU_EXPECT(pixels.size() == mPixels.size());
  std::copy(pixels.begin(), pixels.end(), mPixels.begin());
}



template <size_t dim, PixelFormat fmt>
typename Image<dim, fmt>::Pixel& Image<dim, fmt>::getPixel(
  const Coordinates& coordinates)
{
  return mPixels[computePixelIndex(coordinates)];
}



template <size_t dim, PixelFormat fmt>
const typename Image<dim, fmt>::Pixel& Image<dim, fmt>::getPixel(
  const Coordinates& coordinates) const
{
  return mPixels[computePixelIndex(coordinates)];
}



template <size_t dim, PixelFormat fmt>
void Image<dim, fmt>::clear(const Pixel& pixel)
{
  mPixels = PixelCollection(computePixelCount(), pixel);
}



template <size_t dim, PixelFormat fmt>
Image<dim, fmt> Image<dim, fmt>::getSubImage(const Coordinates& offset, const Size& size)
{
  return getImageSubImage(*this, offset, size);
}



template <size_t dim, PixelFormat fmt>
void Image<dim, fmt>::setSubImage(const Coordinates& offset, const Image& image)
{
  return setImageSubImage(*this, offset, image);
}



template <size_t dim, PixelFormat fmt>
size_t Image<dim, fmt>::computePixelCount() const
{
  size_t retval = 1u;
  for(size_t i = 0; i < dim; ++i)
  {
    retval *= mSize(i);
  }
  return retval;
}



template <size_t dim, PixelFormat fmt>
size_t Image<dim, fmt>::computePixelIndex(const Coordinates& coordinates) const
{
  for(size_t i = 0; i < dim; ++i)
  {
    HOU_EXPECT(coordinates(i) < mSize(i));
  }

  size_t idx = 0;
  size_t multiplier = 1;
  for(size_t i = 0; i < dim; ++i)
  {
    idx += coordinates(i) * multiplier;
    multiplier *= mSize(i);
  }
  return idx;
}



template <size_t dim, PixelFormat fmt>
bool operator==(const Image<dim, fmt>& lhs, const Image<dim, fmt>& rhs)
{
  return lhs.getSize() == rhs.getSize() && lhs.getPixels() == rhs.getPixels();
}



template <size_t dim, PixelFormat fmt>
bool operator!=(const Image<dim, fmt>& lhs, const Image<dim, fmt>& rhs)
{
  return !(lhs == rhs);
}



template <size_t dim, PixelFormat fmt>
std::ostream& operator<<(std::ostream& os, const Image<dim, fmt>& im)
{
  return os << "{Size = " << transpose(im.getSize())
            << ", Pixels = " << im.getPixels() << "}";
}



#define INSTANTIATE_IMAGE_BASE(dim, pf)            \
  template class Image<dim, pf>;                   \
  template bool operator==<dim, pf>(               \
    const Image<dim, pf>&, const Image<dim, pf>&); \
  template bool operator!=<dim, pf>(               \
    const Image<dim, pf>&, const Image<dim, pf>&); \
  template std::ostream& operator<<<dim, pf>(      \
    std::ostream&, const Image<dim, pf>&);



#define INSTANTIATE_CONVERSION_CONSTRUCTOR(dim1, dim2, pf1, pf2) \
  template Image<dim1, pf1>::Image<dim2, pf2, void>(const Image<dim2, pf2>&);



#define INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIMENSIONS(dim1, dim2) \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                   \
    dim1, dim2, PixelFormat::R, PixelFormat::RG)                        \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                   \
    dim1, dim2, PixelFormat::R, PixelFormat::RGB)                       \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                   \
    dim1, dim2, PixelFormat::R, PixelFormat::RGBA)                      \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                   \
    dim1, dim2, PixelFormat::RG, PixelFormat::R)                        \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                   \
    dim1, dim2, PixelFormat::RG, PixelFormat::RGB)                      \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                   \
    dim1, dim2, PixelFormat::RG, PixelFormat::RGBA)                     \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                   \
    dim1, dim2, PixelFormat::RGB, PixelFormat::R)                       \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                   \
    dim1, dim2, PixelFormat::RGB, PixelFormat::RG)                      \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                   \
    dim1, dim2, PixelFormat::RGB, PixelFormat::RGBA)                    \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                   \
    dim1, dim2, PixelFormat::RGBA, PixelFormat::R)                      \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                   \
    dim1, dim2, PixelFormat::RGBA, PixelFormat::RG)                     \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                   \
    dim1, dim2, PixelFormat::RGBA, PixelFormat::RGB)



#define INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_SAME_DIMENSION(dim) \
  INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIMENSIONS(dim, dim)



#define INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIFFERENT_DIMENSIONS( \
  dim1, dim2)                                                          \
  INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIMENSIONS(dim1, dim2)      \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                  \
    dim1, dim2, PixelFormat::R, PixelFormat::R)                        \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                  \
    dim1, dim2, PixelFormat::RG, PixelFormat::RG)                      \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                  \
    dim1, dim2, PixelFormat::RGB, PixelFormat::RGB)                    \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                  \
    dim1, dim2, PixelFormat::RGBA, PixelFormat::RGBA)



#define INSTANTIATE_IMAGE_WITH_DIMENSION(dim)    \
  INSTANTIATE_IMAGE_BASE(dim, PixelFormat::R)    \
  INSTANTIATE_IMAGE_BASE(dim, PixelFormat::RG)   \
  INSTANTIATE_IMAGE_BASE(dim, PixelFormat::RGB)  \
  INSTANTIATE_IMAGE_BASE(dim, PixelFormat::RGBA) \



INSTANTIATE_IMAGE_WITH_DIMENSION(1u)
INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_SAME_DIMENSION(1u)
INSTANTIATE_IMAGE_WITH_DIMENSION(2u)
INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIFFERENT_DIMENSIONS(2u, 1u)
INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_SAME_DIMENSION(2u)
INSTANTIATE_IMAGE_WITH_DIMENSION(3u)
INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIFFERENT_DIMENSIONS(3u, 1u)
INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIFFERENT_DIMENSIONS(3u, 2u)
INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_SAME_DIMENSION(3u)



#define INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, pf) \
  template Image2<pf> imType##ReadFile<pf>(const std::string&);



#define INSTANTIATE_READ_FILE_FUNCTION(imType)                              \
  INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, PixelFormat::R)   \
  INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, PixelFormat::RG)  \
  INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, PixelFormat::RGB) \
  INSTANTIATE_READ_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, PixelFormat::RGBA)



#define INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, pf) \
  template void imType##WriteFile<pf>(const std::string&, const Image2<pf>&);



#define INSTANTIATE_WRITE_FILE_FUNCTION(imType)                              \
  INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, PixelFormat::R)   \
  INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, PixelFormat::RG)  \
  INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, PixelFormat::RGB) \
  INSTANTIATE_WRITE_FILE_FUNCTION_FOR_PIXEL_FORMAT(imType, PixelFormat::RGBA)

INSTANTIATE_READ_FILE_FUNCTION(bmp)
INSTANTIATE_READ_FILE_FUNCTION(png)
INSTANTIATE_READ_FILE_FUNCTION(jpg)

INSTANTIATE_WRITE_FILE_FUNCTION(bmp)

}  // namespace hou
