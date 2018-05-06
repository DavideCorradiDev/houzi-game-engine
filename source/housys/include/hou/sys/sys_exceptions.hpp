// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SYS_EXCEPTIONS_HPP
#define HOU_SYS_SYS_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/sys/sys_export.hpp"



namespace hou
{

/** File open error.
 *
 * This exception is thrown when opening a file fails.
 */
class HOU_SYS_API file_open_error : public exception
{
public:
  /** Creates a file_open_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param filepath the path to the file.
   */
  file_open_error(
    const std::string& path, uint line, const std::string& filepath);
};

/** File close error.
 *
 * This exception is thrown when closing a file fails.
 */
class HOU_SYS_API file_close_error : public exception
{
public:
  /** Creates a file_close_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  file_close_error(const std::string& path, uint line);
};

/** File read error.
 *
 * This exception is thrown when reading from a file fails.
 */
class HOU_SYS_API file_read_error : public exception
{
public:
  /** Creates a file_read_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  file_read_error(const std::string& path, uint line);
};

/** File write error.
 *
 * This exception is thrown when writing to a file fails.
 */
class HOU_SYS_API file_write_error : public exception
{
public:
  /** Creates a file_write_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  file_write_error(const std::string& path, uint line);
};

/** File cursor error.
 *
 * This exception is thrown when setting the cursor position of a file fails.
 */
class HOU_SYS_API file_cursor_error : public exception
{
public:
  /** Creates a file_cursor_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  file_cursor_error(const std::string& path, uint line);
};

/** Image read error.
 *
 * This exception is thrown when reading image data fails.
 * This normally means that the data is corrupted or in a wrong format.
 */
class HOU_SYS_API image_read_error : public exception
{
public:
  /** Creates an image_read_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param filepath the path to the file.
   */
  image_read_error(
    const std::string& path, uint line, const std::string& filepath);
};

/** Image write error.
 *
 * This exception is thrown when writing an image to a file fails.
 */
class HOU_SYS_API image_write_error : public exception
{
public:
  /** Creates an image_write_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param filepath the path to the file.
   */
  image_write_error(
    const std::string& path, uint line, const std::string& filepath);
};

}  // namespace hou

#endif
