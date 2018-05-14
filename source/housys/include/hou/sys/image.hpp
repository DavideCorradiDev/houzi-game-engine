// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_IMAGE_HPP
#define HOU_SYS_IMAGE_HPP

#include "hou/sys/image_fwd.hpp"
#include "hou/sys/pixel.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/cor/span.hpp"
#include "hou/cor/std_vector.hpp"

#include "hou/mth/matrix.hpp"

#include <iostream>
#include <vector>



namespace hou
{

/** Represents an image.
 *
 * Note: all possible class insances are already explicitly instantiated and
 * exported in the library.
 *
 * \tparam Dim the number of dimensions of the image (from 1 to 3).
 */
template <size_t Dim, pixel_format PF>
class HOU_SYS_API image
{
public:
  template <size_t OtherDim, pixel_format OtherPF>
  friend class image;

  /** Type representing the size of the image. */
  using size_type = vec<uint, Dim>;

  /** Type representing pixel coordinates. */
  using offset_type = size_type;

  /** Type of the image pixels. */
  using pixel = pixel_t<PF>;

  /** Type used to represent the collection of pixels of the image. */
  using pixel_collection = std::vector<pixel>;

public:
  /** Retrieves the number of dimensions of the image.
   *
   * \return the number of dimensions of the imag.e
   */
  static constexpr size_t get_dimension_count() noexcept;

  /** Retrieves the format of the pixels of the image.
   *
   * \return the format of the pixels of the image.
   */
  static constexpr pixel_format get_pixel_format() noexcept;

  /** Retrieves the amount of bytes used by a pixel of the image.
   *
   * \return the amomunt of bytes used by a pixel of the image.
   */
  static constexpr uint get_pixel_byte_count() noexcept;

public:
  /** default constructor.
   *
   * Creates an image with no pixels.
   * all of its size components are equal to 0.
   *
   * \throws std::bad_alloc.
   */
  image();

  /** size_type constructor.
   *
   * Creates an image with the given size.
   * all pixel channels are initialized to 0.
   *
   * \param size the size of the image.
   *
   * \throws std::bad_alloc.
   */
  image(const size_type& size);

  /** pixel constructor.
   *
   * Creates an image with the given size, with all pixels set to the given
   * value.
   *
   * \param size the size of the image.
   *
   * \param px the value of the pixels of the image.
   *
   * \throws std::bad_alloc.
   */
  image(const size_type& size, const pixel& px);

  /** Pixels constructor.
   *
   * Creates an image with the given size and pixels.
   * The collection contains a linear list of pixels.
   * Pixels along the first axis must be adjacent in the collection.
   *
   * \param size the size of the image.
   *
   * \param pixels the collection of pixels of the image.
   *
   * \throws hou::precondition_violation if the size of pixels does not coincide
   * the the product of all elements of size.
   *
   * \throws std::bad_alloc.
   */
  image(const size_type& size, const span<const pixel>& pixels);

  /** Pixels move constructor.
   *
   * Creates an image with the given size and pixels.
   * The collection contains a linear list of pixels.
   * Pixels along the first axis must be adjacent in the collection.
   *
   * \param size the size of the image.
   *
   * \param pixels the collection of pixels of the image.
   *
   * \throws hou::precondition_violation if the size of pixels does not coincide
   * the the product of all elements of size.
   */
  image(const size_type& size, pixel_collection&& pixels);

  /** Conversion constructor.
   *
   * Creates an image from an image with a different number of dimensions
   * and/or format. If the pixel format is different, each pixel is converted
   * according to the conversion rule of the pixel class. If the number of
   * dimensions of other is lower, the generated image has size 1 on all
   * additional dimensions. It is not possible to create an image from an image
   * with more dimensions.
   *
   * \tparam OtherDim the number of dimensions of the other image.
   *
   * \tparam OtherPF the pixel format of the other image.
   *
   * \tparam Enable enabling parameter.
   *
   * \param other the other image.
   *
   * \throws std::bad_alloc.
   */
  template <size_t OtherDim, pixel_format OtherPF,
    typename Enable
    = std::enable_if_t<(OtherPF != PF || OtherDim != Dim) && (OtherDim <= Dim)>>
  HOU_SYS_API image(const image<OtherDim, OtherPF>& other);

  /** Retrieves the size of the image.
   *
   * \return the size of the image.
   */
  const size_type& get_size() const noexcept;

  /** Retrieves the pixels of the image.
   *
   * \return the pixels of the image.
   */
  const pixel_collection& get_pixels() const noexcept;

  /** Sets the pixels of the image.
   *
   * \param pixels the pixels.
   *
   * \throws hou::precondition_violation if the size of pixels is not equal to
   * the product of all elements of the size of the image.
   */
  void set_pixels(const span<const pixel>& pixels);

  /** Retrieves a single pixel.
   *
   * \param coordinates the coordinates of the pixel.
   *
   * \throws hou::out_of_range if the coordinates exceed the size of the image.
   *
   * \return tue pixel.
   */
  const pixel& get_pixel(const offset_type& coordinates) const;

  /** Sets the value of a single pixel.
   *
   * \param coordinates the coordinates of the pixel.
   *
   * \param value the value of the pixel.
   *
   * \throws hou::out_of_range if the coordinates exceed the size of the image.
   */
  void set_pixel(const offset_type& coordinates, const pixel& value);

  /** Retrieves a sub-image.
   *
   * \param offset the offset of the sub-image.
   *
   * \param size the size of the sub-image.
   *
   * \throws hou::out_of_range if the sum of offset and size is
   * greater or equal than the size of the image.
   *
   * \throws std::bad_alloc.
   *
   * \return the sub-image starting at offset (included) and with the specified
   * size.
   */
  image get_sub_image(const offset_type& offset, const size_type& size);

  /** Sets a region of the image with the given sub-image.
   *
   * Throws if the sum of offset and the size of the input image is greater or
   * equal than the size of the image.
   *
   * \param offset the offset of the sub-image.
   *
   * \throws hou::out_of_range if the sum of offset and the size of
   * the input image is greater or equal than the size of the image.
   *
   * \param im the sub-image to be copied.
   */
  void set_sub_image(const offset_type& offset, const image& im);

  /** Clears the whole image with the given pixel value.
   *
   * \param px the pixel value.
   *
   * \throws std::bad_alloc.
   */
  void clear(const pixel& px);

private:
  size_t compute_pixel_count() const;
  size_t compute_pixel_index(const offset_type& coordinates) const;

private:
  size_type m_size;
  pixel_collection m_pixels;
};

/** Checks if two image objects are equal.
 *
 * \tparam Dim the number of dimensions of the image.
 *
 * \tparam PF the pixel format.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
template <size_t Dim, pixel_format PF>
HOU_SYS_API bool operator==(
  const image<Dim, PF>& lhs, const image<Dim, PF>& rhs) noexcept;

/** Checks if two image objects are not equal.
 *
 * \tparam Dim the number of dimensions of the image.
 *
 * \tparam PF the pixel format.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
template <size_t Dim, pixel_format PF>
HOU_SYS_API bool operator!=(
  const image<Dim, PF>& lhs, const image<Dim, PF>& rhs) noexcept;

/** Writes the object into a stream.
 *
 * \tparam Dim the number of dimensions of the image.
 *
 * \tparam PF the pixel format.
 *
 * \param os the stream.
 *
 * \param im the image..
 *
 * \return a reference to os.
 */
template <size_t Dim, pixel_format PF>
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, const image<Dim, PF>& im);

/** Checks if a file is a BMP file.
 *
 * \param path the path to the file.
 *
 * \throws hou::file_open_error if the file could not be opened.
 *
 * \return whether the file is a BMP file or not.
 */
HOU_SYS_API bool bmp_check_file(const std::string& path);

/** Creates an image object from a BMP file.
 *
 * \tparam PF the output image format.
 *
 * \param path the path to the file.
 *
 * \throws hou::file_open_error if the file could not be opened.
 *
 * \throws hou::invalid_image_data if the image data was not valid.
 *
 * \return an image built from the information contained in the file.
 */
template <pixel_format PF>
HOU_SYS_API image2<PF> bmp_read_file(const std::string& path);

/** Writes an image to disk as a BMP file.
 *
 * Throws if it is not possible to write to the given path.
 *
 * \tparam PF the input image format.
 *
 * \param path the path of the image file to be created.
 *
 * \param im the image to be written to disk.
 *
 * \throws hou::file_open_error if the file could not be opened.
 *
 * \throws hou::invalid_image_data if the image data was not valid.
 */
template <pixel_format PF>
HOU_SYS_API void bmp_write_file(const std::string& path, const image2<PF>& im);

/** Checks if a file is a PNG file.
 *
 * Throws if the file corresponding to the given path cannot be opened.
 *
 * \param path the path to the file.
 *
 * \throws hou::file_open_error if the file could not be opened.
 *
 * \return whether the file is a PNG file or not.
 */
HOU_SYS_API bool png_check_file(const std::string& path);

/** Creates an image object from a PNG file.
 *
 * Throws if the file corresponding to the given path cannot be opened.
 * Throws if the file is not a PNG file.
 *
 * \tparam PF the output image format.
 *
 * \param path the path to the file.
 *
 * \throws hou::file_open_error if the file could not be opened.
 *
 * \throws hou::invalid_image_data if the image data was not valid.
 *
 * \return an image built from the information contained in the file.
 */
template <pixel_format PF>
HOU_SYS_API image2<PF> png_read_file(const std::string& path);


/** Checks if a file is a JPG file.
 *
 * Throws if the file corresponding to the given path cannot be opened.
 *
 * \param path the path to the file.
 *
 * \throws hou::file_open_error if the file could not be opened.
 *
 * \return whether the file is a JPG file or not.
 */
HOU_SYS_API bool jpg_check_file(const std::string& path);

/** Creates an image object from a JPG file.
 *
 * Throws if the file corresponding to the given path cannot be opened.
 * Throws if the file is not a JPG file.
 *
 * \tparam PF the output image format.
 *
 * \param path the path to the file.
 *
 * \throws hou::file_open_error if the file could not be opened.
 *
 * \throws hou::invalid_image_data if the image data was not valid.
 *
 * \return an image built from the information contained in the file.
 */
template <pixel_format PF>
HOU_SYS_API image2<PF> jpg_read_file(const std::string& path);

}  // namespace hou

#include "hou/sys/image.inl"

#endif
