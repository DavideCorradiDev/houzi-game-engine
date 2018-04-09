// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_IMAGE_HPP
#define HOU_SYS_IMAGE_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/cor/Span.hpp"
#include "hou/cor/StdVector.hpp"

#include "hou/mth/Matrix.hpp"

#include "hou/sys/ImageFwd.hpp"
#include "hou/sys/Pixel.hpp"

#include <iostream>
#include <vector>



namespace hou
{

template <size_t dim, PixelFormat fmt>
class HOU_SYS_API Image
{
public:
  using Size = Vec<uint, dim>;
  using Coordinates = Size;
  using Pixel = PixelT<fmt>;
  using PixelCollection = std::vector<Pixel>;

  template <size_t otherDim, PixelFormat otherFmt>
  friend class Image;

public:
  static constexpr size_t getDimensionCount();
  static constexpr PixelFormat getPixelFormat();
  static constexpr size_t getPixelByteCount();

public:
  Image();
  Image(const Size& size);
  Image(const Size& size, const Pixel& pixel);
  Image(const Size& size, const Span<const Pixel>& pixels);
  // Test conversions with different sizes.
  template <size_t otherDim, PixelFormat otherFmt,
    typename Enable = std::enable_if_t<(otherFmt != fmt || otherDim != dim)
      && (otherDim <= dim)>>
  HOU_SYS_API Image(const Image<otherDim, otherFmt>& other);

  const Size& getSize() const;
  const PixelCollection& getPixels() const;
  // To be testsd.
  void setPixels(const Span<const Pixel>& pixels);

  // Change to get / set?
  const Pixel& getPixel(const Coordinates& coordinates) const;
  void setPixel(const Coordinates& coordinates, const Pixel& value);

  void clear(const Pixel& pixel);

  // To be tested.
  Image getSubImage(const Coordinates& offset, const Size& size);
  void setSubImage(const Coordinates& offset, const Image& image);

  // Linear accessor?

private:
  size_t computePixelCount() const;
  size_t computePixelIndex(const Coordinates& coordinates) const;

private:
  Size mSize;
  PixelCollection mPixels;
};

template <size_t dim, PixelFormat fmt>
HOU_SYS_API bool operator==(
  const Image<dim, fmt>& lhs, const Image<dim, fmt>& rhs);
template <size_t dim, PixelFormat fmt>
HOU_SYS_API bool operator!=(
  const Image<dim, fmt>& lhs, const Image<dim, fmt>& rhs);
template <size_t dim, PixelFormat fmt>
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, const Image<dim, fmt>& im);



/** Checks if a file is a BMP file.
 *
 *  Throws if the file corresponding to the given path cannot be opened.
 *
 *  \param path the path to the file.
 *  \return whether the file is a BMP file or not.
 */
HOU_SYS_API bool bmpCheckFile(const std::string& path);

/** Creates an Image object from a BMP file.
 *
 *  Throws if the file corresponding to the given path cannot be opened.
 *  Throws if the file is not a BMP file.
 *
 *  \param path the path to the file.
 *  \param format the format to be used when creating the image.
 *  \return an Image built from the information contained in the file.
 */
template <PixelFormat fmt>
HOU_SYS_API Image2<fmt> bmpReadFile(const std::string& path);

/** Writes an image to disk as a BMP file.
 *
 *  Throws if it is not possible to write to the given path.
 *
 *  \param path the path of the image file to be created.
 *  \param image the image to be written to disk.
 */
template <PixelFormat fmt>
HOU_SYS_API void bmpWriteFile(
  const std::string& path, const Image2<fmt>& image);

/** Checks if a file is a PNG file.
 *
 *  Throws if the file corresponding to the given path cannot be opened.
 *
 *  \param path the path to the file.
 *  \return whether the file is a PNG file or not.
 */
HOU_SYS_API bool pngCheckFile(const std::string& path);

/** Creates an Image object from a PNG file.
 *
 *  Throws if the file corresponding to the given path cannot be opened.
 *  Throws if the file is not a PNG file.
 *
 *  \param path the path to the file.
 *  \param format the format to be used when creating the image.
 *  \return an Image built from the information contained in the file.
 */
template <PixelFormat fmt>
HOU_SYS_API Image2<fmt> pngReadFile(const std::string& path);


/** Checks if a file is a JPG file.
 *
 *  Throws if the file corresponding to the given path cannot be opened.
 *
 *  \param path the path to the file.
 *  \return whether the file is a JPG file or not.
 */
HOU_SYS_API bool jpgCheckFile(const std::string& path);

/** Creates an Image object from a JPG file.
 *
 *  Throws if the file corresponding to the given path cannot be opened.
 *  Throws if the file is not a JPG file.
 *
 *  \param path the path to the file.
 *  \param format the format to be used when creating the image.
 *  \return an Image built from the information contained in the file.
 */
template <PixelFormat fmt>
HOU_SYS_API Image2<fmt> jpgReadFile(const std::string& path);

}  // namespace hou

#include "hou/sys/Image.inl"

#endif
