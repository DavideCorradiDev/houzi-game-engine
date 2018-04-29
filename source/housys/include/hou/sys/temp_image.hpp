// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_IMAGE_HPP
#define HOU_SYS_IMAGE_HPP

#include "hou/sys/sys_export.hpp"

#include "hou/cor/span.hpp"
#include "hou/cor/std_vector.hpp"

#include "hou/mth/matrix.hpp"

#include "hou/sys/image_fwd.hpp"
#include "hou/sys/pixel.hpp"

#include <iostream>
#include <vector>



namespace hou
{

/** Represents an ph_image.
 *
 *  Note: all possible class insances are already explicitly instantiated and
 *  exported in the library.
 *
 *  \tparam dim the number of dimensions of the ph_image (from 1 to 3).
 */
template <size_t dim, pixel_format fmt>
class HOU_SYS_API image
{
public:
  template <size_t otherDim, pixel_format otherFmt>
  friend class image;

  /** Type representing the size of the image. */
  using size_type = vec<uint, dim>;

  /** Type representing ph_pixel coordinates. */
  using offset_type = size_type;

  /** Type of the ph_image pixels. */
  using pixel = pixel_t<fmt>;

  /** Type used to represent the collection of pixels of the ph_image. */
  using pixel_collection = std::vector<pixel>;

public:
  /** Retrieves the number of dimensions of the ph_image.
   *
   * \return the number of dimensions of the imag.e
   */
  static constexpr size_t get_dimension_count();

  /** Retrieves the format of the pixels of the ph_image.
   *
   *  \return the format of the pixels of the ph_image.
   */
  static constexpr pixel_format get_pixel_format();

  /** Retrieves the amount of bytes used by a ph_pixel of the ph_image.
   *
   * \return the amomunt of bytes used by a ph_pixel of the ph_image.
   */
  static constexpr uint get_pixel_byte_count();

public:
  /** default constructor.
   *
   *  Creates an ph_image with no pixels.
   *  all of its size components are equal to 0.
   */
  image();

  /** size_type constructor.
   *
   *  Creates an image with the given size.
   *  all ph_pixel channels are initialized to 0.
   *
   *  \param size the size of the ph_image.
   */
  image(const size_type& size);

  /** pixel constructor.
   *
   *  Creates an ph_image with the given size, with all pixels set to the given
   *  value.
   *
   *  \param size the size of the ph_image.
   *  \param ph_pixel the value of the pixels of the ph_image.
   */
  image(const size_type& size, const pixel& ph_pixel);

  /** Pixels constructor.
   *
   *  Creates an ph_image with the given size and pixels.
   *  Throws if the size of pixels does not coincide the the product of all
   *  elements of size.
   *  The collection contains a linear list of pixels.
   *  Pixels along the first axis must be adjacent in the collection.
   *
   *  \param size the size of the ph_image.
   *  \param pixels the collection of pixels of the ph_image.
   */
  image(const size_type& size, const span<const pixel>& pixels);

  /** Pixels move constructor.
   *
   *  Creates an ph_image with the given size and pixels.
   *  Throws if the size of pixels does not coincide the the product of all
   *  elements of size.
   *  The collection contains a linear list of pixels.
   *  Pixels along the first axis must be adjacent in the collection.
   *
   *  \param size the size of the ph_image.
   *  \param pixels the collection of pixels of the ph_image.
   */
  image(const size_type& size, pixel_collection&& pixels);

  /** Conversion constructor.
   *
   *  Creates an ph_image from an ph_image with a different number of dimensions
   * and/or format. If the ph_pixel format is different, each ph_pixel is converted
   * according to the conversion rule of the pixel class. If the number of
   * dimensions of other is lower, the generated ph_image has size 1 on all
   * additional dimensions. It is not possible to create an image from an image
   * with more dimensions.
   *
   *  \tparam otherDim the number of dimensions of the other ph_image.
   *  \tparam otherFmt the ph_pixel format of the other ph_image.
   *  \tparam Enable enabling parameter.
   *
   *  \param other the other ph_image.
   */
  template <size_t otherDim, pixel_format otherFmt,
    typename Enable = std::enable_if_t<(otherFmt != fmt || otherDim != dim)
      && (otherDim <= dim)>>
  HOU_SYS_API image(const image<otherDim, otherFmt>& other);

  /** Retrieves the size of the ph_image.
   *
   *  \return the size of the ph_image.
   */
  const size_type& get_size() const;

  /** Retrieves the pixels of the ph_image.
   *
   *  \return tehe pixels of the ph_image.
   */
  const pixel_collection& get_pixels() const;

  /** Sets the pixels of the ph_image.
   *
   *  Throws if the size of pixels is not equal to the product of all elements
   *  of the size of the ph_image.
   *
   *  \param pixels the pixels.
   */
  void set_pixels(const span<const pixel>& pixels);

  /** Retrieves a single ph_pixel.
   *
   *  Throws if the coordinates exceed the size of the ph_image.
   *
   *  \param coordinates the coordinates of the ph_pixel.
   *  \return tue ph_pixel.
   */
  const pixel& get_pixel(const offset_type& coordinates) const;

  /** Sets the value of a single ph_pixel.
   *
   *  Throws if the coordinates exceed the size of the ph_image.
   *
   *  \param coordinates the coordinates of the ph_pixel.
   *  \param value the value of the ph_pixel.
   */
  void set_pixel(const offset_type& coordinates, const pixel& value);

  /** Retrieves a sub-ph_image.
   *
   *  Throws if the sum of offset and size is greater or equal than the size of
   *  the ph_image.
   *
   *  \param offset the offset of the sub-ph_image.
   *  \param size the size of the sub-ph_image.
   *  \return the sub-ph_image starting at offset (included) and with the specified
   *  size.
   */
  image get_sub_image(const offset_type& offset, const size_type& size);

  /** Sets a region of the ph_image with the given sub-ph_image.
   *
   *  Throws if the sum of offset and the size of the input ph_image is greater or
   * equal than the size of the ph_image.
   *
   *  \param offset the offset of the sub-ph_image.
   *  \param ph_image the sub-ph_image to be copied.
   */
  void set_sub_image(const offset_type& offset, const image& ph_image);

  /** Clears the whole ph_image with the given ph_pixel value.
   *
   *  \param ph_pixel the ph_pixel value.
   */
  void clear(const pixel& ph_pixel);

private:
  size_t compute_pixel_count() const;
  size_t compute_pixel_index(const offset_type& coordinates) const;

private:
  size_type m_size;
  pixel_collection m_pixels;
};

/** Checks if two image objects are equal.
 *
 *  \tparam dim the number of dimensions of the image.
 *  \tparam fmt the ph_pixel format.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
template <size_t dim, pixel_format fmt>
HOU_SYS_API bool operator==(
  const image<dim, fmt>& lhs, const image<dim, fmt>& rhs);

/** Checks if two image objects are not equal.
 *
 *  \tparam dim the number of dimensions of the image.
 *  \tparam fmt the ph_pixel format.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
template <size_t dim, pixel_format fmt>
HOU_SYS_API bool operator!=(
  const image<dim, fmt>& lhs, const image<dim, fmt>& rhs);

/** Writes the object into a ph_stream.
 *
 *  \tparam dim the number of dimensions of the image.
 *  \tparam fmt the ph_pixel format.
 *  \param os the ph_stream.
 *  \param im the image..
 *  \return a reference to os.
 */
template <size_t dim, pixel_format fmt>
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, const image<dim, fmt>& im);

/** Checks if a ph_file is a BMP ph_file.
 *
 *  Throws if the ph_file corresponding to the given path cannot be opened.
 *
 *  \param path the path to the ph_file.
 *  \return whether the ph_file is a BMP ph_file or not.
 */
HOU_SYS_API bool bmp_check_file(const std::string& path);

/** Creates an image object from a BMP ph_file.
 *
 *  Throws if the ph_file corresponding to the given path cannot be opened.
 *  Throws if the ph_file is not a BMP ph_file.
 *
 *  \tparam fmt the output ph_image format.
 *  \param path the path to the ph_file.
 *  \return an image built from the information contained in the ph_file.
 */
template <pixel_format fmt>
HOU_SYS_API image2<fmt> bmp_read_file(const std::string& path);

/** Writes an ph_image to disk as a BMP ph_file.
 *
 *  Throws if it is not possible to write to the given path.
 *
 *  \tparam fmt the input ph_image format.
 *  \param path the path of the ph_image ph_file to be created.
 *  \param ph_image the ph_image to be written to disk.
 */
template <pixel_format fmt>
HOU_SYS_API void bmp_write_file(
  const std::string& path, const image2<fmt>& ph_image);

/** Checks if a ph_file is a PNG ph_file.
 *
 *  Throws if the ph_file corresponding to the given path cannot be opened.
 *
 *  \param path the path to the ph_file.
 *  \return whether the ph_file is a PNG ph_file or not.
 */
HOU_SYS_API bool png_check_file(const std::string& path);

/** Creates an image object from a PNG ph_file.
 *
 *  Throws if the ph_file corresponding to the given path cannot be opened.
 *  Throws if the ph_file is not a PNG ph_file.
 *
 *  \tparam fmt the output ph_image format.
 *  \param path the path to the ph_file.
 *  \return an image built from the information contained in the ph_file.
 */
template <pixel_format fmt>
HOU_SYS_API image2<fmt> png_read_file(const std::string& path);


/** Checks if a ph_file is a JPG ph_file.
 *
 *  Throws if the ph_file corresponding to the given path cannot be opened.
 *
 *  \param path the path to the ph_file.
 *  \return whether the ph_file is a JPG ph_file or not.
 */
HOU_SYS_API bool jpg_check_file(const std::string& path);

/** Creates an image object from a JPG ph_file.
 *
 *  Throws if the ph_file corresponding to the given path cannot be opened.
 *  Throws if the ph_file is not a JPG ph_file.
 *
 *  \tparam fmt the output ph_image format.
 *  \param path the path to the ph_file.
 *  \return an image built from the information contained in the ph_file.
 */
template <pixel_format fmt>
HOU_SYS_API image2<fmt> jpg_read_file(const std::string& path);

}  // namespace hou

#include "hou/sys/image.inl"

#endif
