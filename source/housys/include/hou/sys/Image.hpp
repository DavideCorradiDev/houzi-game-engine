// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_IMAGE_HPP
#define HOU_SYS_IMAGE_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/cor/span.hpp"
#include "hou/cor/std_vector.hpp"

#include "hou/mth/matrix.hpp"

#include "hou/sys/ImageFwd.hpp"
#include "hou/sys/Pixel.hpp"

#include <iostream>
#include <vector>



namespace hou
{

/** Represents an image.
 *
 *  Note: all possible class insances are already explicitly instantiated and
 *  exported in the library.
 *
 *  \tparam dim the number of dimensions of the image (from 1 to 3).
 */
template <size_t dim, PixelFormat fmt>
class HOU_SYS_API Image
{
public:
  template <size_t otherDim, PixelFormat otherFmt>
  friend class Image;

  /** Type representing the size of the Image. */
  using Size = vec<uint, dim>;

  /** Type representing pixel coordinates. */
  using Coordinates = Size;

  /** Type of the image pixels. */
  using Pixel = PixelT<fmt>;

  /** Type used to represent the collection of pixels of the image. */
  using PixelCollection = std::vector<Pixel>;

public:
  /** Retrieves the number of dimensions of the image.
   *
   * \return the number of dimensions of the imag.e
   */
  static constexpr size_t getDimensionCount();

  /** Retrieves the format of the pixels of the image.
   *
   *  \return the format of the pixels of the image.
   */
  static constexpr PixelFormat getPixelFormat();

  /** Retrieves the amount of bytes used by a pixel of the image.
   *
   * \return the amomunt of bytes used by a pixel of the image.
   */
  static constexpr uint getPixelByteCount();

public:
  /** Default constructor.
   *
   *  Creates an image with no pixels.
   *  All of its size components are equal to 0.
   */
  Image();

  /** Size constructor.
   *
   *  Creates an Image with the given size.
   *  All pixel channels are initialized to 0.
   *
   *  \param size the size of the image.
   */
  Image(const Size& size);

  /** Pixel constructor.
   *
   *  Creates an image with the given size, with all pixels set to the given
   *  value.
   *
   *  \param size the size of the image.
   *  \param pixel the value of the pixels of the image.
   */
  Image(const Size& size, const Pixel& pixel);

  /** Pixels constructor.
   *
   *  Creates an image with the given size and pixels.
   *  Throws if the size of pixels does not coincide the the product of all
   *  elements of size.
   *  The collection contains a linear list of pixels.
   *  Pixels along the first axis must be adjacent in the collection.
   *
   *  \param size the size of the image.
   *  \param pixels the collection of pixels of the image.
   */
  Image(const Size& size, const span<const Pixel>& pixels);

  /** Pixels move constructor.
   *
   *  Creates an image with the given size and pixels.
   *  Throws if the size of pixels does not coincide the the product of all
   *  elements of size.
   *  The collection contains a linear list of pixels.
   *  Pixels along the first axis must be adjacent in the collection.
   *
   *  \param size the size of the image.
   *  \param pixels the collection of pixels of the image.
   */
  Image(const Size& size, PixelCollection&& pixels);

  /** Conversion constructor.
   *
   *  Creates an image from an image with a different number of dimensions
   * and/or format. If the pixel format is different, each pixel is converted
   * according to the conversion rule of the Pixel class. If the number of
   * dimensions of other is lower, the generated image has size 1 on all
   * additional dimensions. It is not possible to create an Image from an Image
   * with more dimensions.
   *
   *  \tparam otherDim the number of dimensions of the other image.
   *  \tparam otherFmt the pixel format of the other image.
   *  \tparam Enable enabling parameter.
   *
   *  \param other the other image.
   */
  template <size_t otherDim, PixelFormat otherFmt,
    typename Enable = std::enable_if_t<(otherFmt != fmt || otherDim != dim)
      && (otherDim <= dim)>>
  HOU_SYS_API Image(const Image<otherDim, otherFmt>& other);

  /** Retrieves the size of the image.
   *
   *  \return the size of the image.
   */
  const Size& get_size() const;

  /** Retrieves the pixels of the image.
   *
   *  \return tehe pixels of the image.
   */
  const PixelCollection& getPixels() const;

  /** Sets the pixels of the image.
   *
   *  Throws if the size of pixels is not equal to the product of all elements
   *  of the size of the image.
   *
   *  \param pixels the pixels.
   */
  void setPixels(const span<const Pixel>& pixels);

  /** Retrieves a single pixel.
   *
   *  Throws if the coordinates exceed the size of the image.
   *
   *  \param coordinates the coordinates of the pixel.
   *  \return tue pixel.
   */
  const Pixel& getPixel(const Coordinates& coordinates) const;

  /** Sets the value of a single pixel.
   *
   *  Throws if the coordinates exceed the size of the image.
   *
   *  \param coordinates the coordinates of the pixel.
   *  \param value the value of the pixel.
   */
  void setPixel(const Coordinates& coordinates, const Pixel& value);

  /** Retrieves a sub-image.
   *
   *  Throws if the sum of offset and size is greater or equal than the size of
   *  the image.
   *
   *  \param offset the offset of the sub-image.
   *  \param size the size of the sub-image.
   *  \return the sub-image starting at offset (included) and with the specified
   *  size.
   */
  Image getSubImage(const Coordinates& offset, const Size& size);

  /** Sets a region of the image with the given sub-image.
   *
   *  Throws if the sum of offset and the size of the input image is greater or
   * equal than the size of the image.
   *
   *  \param offset the offset of the sub-image.
   *  \param image the sub-image to be copied.
   */
  void setSubImage(const Coordinates& offset, const Image& image);

  /** Clears the whole image with the given pixel value.
   *
   *  \param pixel the pixel value.
   */
  void clear(const Pixel& pixel);

private:
  size_t computePixelCount() const;
  size_t computePixelIndex(const Coordinates& coordinates) const;

private:
  Size m_size;
  PixelCollection mPixels;
};

/** Checks if two Image objects are equal.
 *
 *  \tparam dim the number of dimensions of the Image.
 *  \tparam fmt the pixel format.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
template <size_t dim, PixelFormat fmt>
HOU_SYS_API bool operator==(
  const Image<dim, fmt>& lhs, const Image<dim, fmt>& rhs);

/** Checks if two Image objects are not equal.
 *
 *  \tparam dim the number of dimensions of the Image.
 *  \tparam fmt the pixel format.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
template <size_t dim, PixelFormat fmt>
HOU_SYS_API bool operator!=(
  const Image<dim, fmt>& lhs, const Image<dim, fmt>& rhs);

/** Writes the object into a stream.
 *
 *  \tparam dim the number of dimensions of the Image.
 *  \tparam fmt the pixel format.
 *  \param os the stream.
 *  \param im the Image..
 *  \return a reference to os.
 */
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
 *  \tparam fmt the output image format.
 *  \param path the path to the file.
 *  \return an Image built from the information contained in the file.
 */
template <PixelFormat fmt>
HOU_SYS_API Image2<fmt> bmpReadFile(const std::string& path);

/** Writes an image to disk as a BMP file.
 *
 *  Throws if it is not possible to write to the given path.
 *
 *  \tparam fmt the input image format.
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
 *  \tparam fmt the output image format.
 *  \param path the path to the file.
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
 *  \tparam fmt the output image format.
 *  \param path the path to the file.
 *  \return an Image built from the information contained in the file.
 */
template <PixelFormat fmt>
HOU_SYS_API Image2<fmt> jpgReadFile(const std::string& path);

}  // namespace hou

#include "hou/sys/Image.inl"

#endif
