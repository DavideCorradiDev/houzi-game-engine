// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_IMAGE_FILE_HPP
#define HOU_SYS_IMAGE_FILE_HPP

#include "hou/cor/non_instantiable.hpp"

#include "hou/sys/image_fwd.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/cor/std_string.hpp"



namespace hou
{

/**
 * Contains methods to check, read, and write BMP files.
 */
class HOU_SYS_API bmp_image_file : public non_instantiable
{
public:
  /**
   * Checks if a file is a BMP file.
   *
   * \param path the path to the file.
   *
   * \throws hou::file_open_error if the file could not be opened.
   *
   * \return whether the file is a BMP file or not.
   */
  static bool check(const std::string& path);

  /**
   * Creates an image object from a BMP file.
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
  HOU_SYS_API static image2<PF> read(const std::string& path);

  /**
   * Writes an image to disk as a BMP file.
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
  static void write(const std::string& path, const image2<PF>& im);
};

#ifndef HOU_DOXYGEN
extern template HOU_SYS_API void bmp_image_file::write<pixel_format::r>(
  const std::string& path, const image2<pixel_format::r>& im);

extern template HOU_SYS_API void bmp_image_file::write<pixel_format::rg>(
  const std::string& path, const image2<pixel_format::rg>& im);

extern template HOU_SYS_API void bmp_image_file::write<pixel_format::rgb>(
  const std::string& path, const image2<pixel_format::rgb>& im);

extern template HOU_SYS_API void bmp_image_file::write<pixel_format::rgba>(
  const std::string& path, const image2<pixel_format::rgba>& im);

extern template HOU_SYS_API image2<pixel_format::r>
  bmp_image_file::read<pixel_format::r>(const std::string& path);

extern template HOU_SYS_API image2<pixel_format::rg>
  bmp_image_file::read<pixel_format::rg>(const std::string& path);

extern template HOU_SYS_API image2<pixel_format::rgb>
  bmp_image_file::read<pixel_format::rgb>(const std::string& path);

extern template HOU_SYS_API image2<pixel_format::rgba>
  bmp_image_file::read<pixel_format::rgba>(const std::string& path);
#endif

/**
 * Contains methods to check, read, and write PNG files.
 */
class HOU_SYS_API png_image_file : public non_instantiable
{
public:
  /**
   * Checks if a file is a PNG file.
   *
   * Throws if the file corresponding to the given path cannot be opened.
   *
   * \param path the path to the file.
   *
   * \throws hou::file_open_error if the file could not be opened.
   *
   * \return whether the file is a PNG file or not.
   */
  static bool check(const std::string& path);

  /**
   * Creates an image object from a PNG file.
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
  static image2<PF> read(const std::string& path);
};

#ifndef HOU_DOXYGEN
extern template HOU_SYS_API image2<pixel_format::r>
  png_image_file::read<pixel_format::r>(const std::string& path);

extern template HOU_SYS_API image2<pixel_format::rg>
  png_image_file::read<pixel_format::rg>(const std::string& path);

extern template HOU_SYS_API image2<pixel_format::rgb>
  png_image_file::read<pixel_format::rgb>(const std::string& path);

extern template HOU_SYS_API image2<pixel_format::rgba>
  png_image_file::read<pixel_format::rgba>(const std::string& path);
#endif

/**
 * Contains methods to check, read, and write JPG files.
 */
class HOU_SYS_API jpg_image_file : public non_instantiable
{
public:
  /**
   * Checks if a file is a JPG file.
   *
   * Throws if the file corresponding to the given path cannot be opened.
   *
   * \param path the path to the file.
   *
   * \throws hou::file_open_error if the file could not be opened.
   *
   * \return whether the file is a JPG file or not.
   */
  static bool check(const std::string& path);

  /**
   * Creates an image object from a JPG file.
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
  static image2<PF> read(const std::string& path);
};

#ifndef HOU_DOXYGEN
extern template HOU_SYS_API image2<pixel_format::r>
  jpg_image_file::read<pixel_format::r>(const std::string& path);

extern template HOU_SYS_API image2<pixel_format::rg>
  jpg_image_file::read<pixel_format::rg>(const std::string& path);

extern template HOU_SYS_API image2<pixel_format::rgb>
  jpg_image_file::read<pixel_format::rgb>(const std::string& path);

extern template HOU_SYS_API image2<pixel_format::rgba>
  jpg_image_file::read<pixel_format::rgba>(const std::string& path);
#endif

}  // namespace hou

#endif
