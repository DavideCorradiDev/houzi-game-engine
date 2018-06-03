// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SYS_EXCEPTIONS_HPP
#define HOU_SYS_SYS_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/sys/sys_config.hpp"



namespace hou
{

/** File open error.
 *
 * This exception is thrown when opening a file fails.
 */
class HOU_SYS_API file_open_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param filepath the path to the file.
   *
   * \throws std::bad_alloc.
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
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  file_close_error(const std::string& path, uint line);
};

/** File read error.
 *
 * This exception is thrown when a read operation fails.
 */
class HOU_SYS_API read_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  read_error(const std::string& path, uint line);
};

/** File write error.
 *
 * This exception is thrown when a write operation fails.
 */
class HOU_SYS_API write_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  write_error(const std::string& path, uint line);
};

/** File cursor error.
 *
 * This exception is thrown when setting or getting the cursor position in a
 * file or stream fails.
 */
class HOU_SYS_API cursor_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  cursor_error(const std::string& path, uint line);
};

/** Invalid image data error.
 *
 * This exception is thrown when reading or writing image data fails due to the
 * data being invalid.
 */
class HOU_SYS_API invalid_image_data : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  invalid_image_data(const std::string& path, uint line);
};



/** System module not initialized error.
 *
 * This error is thrown when the system module has not been initialized and
 * a call requiring the initialization has been made.
 */
class HOU_SYS_API sys_not_initialized : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  sys_not_initialized(const std::string& path, uint line);
};


/** Platform-specific error.
 *
 * This exception is thrown when a platform-specific error occurs.
 */
class HOU_SYS_API platform_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param description the error description.
   *
   * \throws std::bad_alloc.
   */
  platform_error(
    const std::string& path, uint line, const std::string& description);
};

}  // namespace hou

#endif
