// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_FILE_HANDLE_HPP
#define HOU_SYS_FILE_HANDLE_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/sys/file_open_mode.hpp"
#include "hou/sys/file_type.hpp"

#include "hou/sys/sys_config.hpp"

#include <string>



namespace hou
{

/**
 * Manages the lifetime of a file handle.
 */
class HOU_SYS_API file_handle final : public non_copyable
{
public:
  /**
   * Path constructor.
   *
   * \param path the path to the file to be opened.
   *
   * \param mode the mode in which to open the file.
   *
   * \param type the file type.
   *
   * \throws hou::file_open_error if the file could not be opened.
   */
  file_handle(const std::string& path, file_open_mode mode, file_type type);

  /**
   * Move constructor.
   *
   * \param other the other file_handle.
   */
  file_handle(file_handle&& other) noexcept;

  /**
   * Closes the file.
   *
   * It is not necessary to explicitly close the file, as it will be done by
   * the destructor, but calling close first will allow to catch exception,
   * while a failure to close the file in the destructor will terminate the
   * application.
   *
   * \throws hou::file_close_error if the file could not be closed (for example
   * if it was already been closed.
   */
  void close();

  /**
   * Destructor.
   */
  ~file_handle();

  /**
   * Conversion to FILE*.
   *
   * \return the corresponding pointer to FILE. Returns nullptr if the
   * file_handle has been closed.
   */
  operator FILE*() const noexcept;

private:
  FILE* m_file;
};

/**
 * Returns the file mode string equivalent to the provided file_open_mode and
 * file_type.
 *
 * The returned string can be used with functions like fopen.
 *
 * \param mode the file open mode.
 *
 * \param type the file type.
 *
 * \return the associated string.
 */
HOU_SYS_API std::string get_file_mode_string(
  file_open_mode mode, file_type type) noexcept;

/**
 * Opens a file.
 *
 * Supports unicode paths.
 *
 * \param path the path to the file.
 *
 * \param mode the mode string (see fopen documentation).
 *
 * \return a pointer to the opened file, or nullptr in case of failure.
 */
HOU_SYS_API FILE* open_file(
  const std::string& path, const std::string& mode) noexcept;

/**
 * Closes a file.
 *
 * \param f the file to be closed.
 *
 * \return true if the file was closed successfully.
 */
HOU_SYS_API bool close_file(FILE* f) noexcept;

/**
 * Checks if a directory exists.
 *
 * Supports unicode paths.
 *
 * \param path the directory to be checked.
 *
 * \return true if the directory exists.
 */
HOU_SYS_API bool check_dir(const std::string& path) noexcept;

/**
 * Removes the specified directory.
 *
 * Supports unicode paths.
 *
 * \param path the directory to be removed.
 *
 * \return true if the directory was actually removed.
 */
HOU_SYS_API bool remove_dir(const std::string& path) noexcept;

/**
 * Renames the specified directory.
 *
 * Supports unicode paths.
 *
 * \param old_path the directory to be moved.
 *
 * \param new_path the new directory.
 *
 * \return true if the directory was actually moved.
 */
HOU_SYS_API bool rename_dir(
  const std::string& old_path, const std::string& new_path) noexcept;

/**
 * Retrieves the size in bytes of a directory.
 *
 * Supports unicode paths.
 *
 * \param path the path.
 *
 * \return the size in bytes of the directory. In case of error, it returns
 * the maximum value possible for the return type.
 */
HOU_SYS_API size_t get_dir_byte_size(const std::string& path) noexcept;

/**
 * Retrieves the file descriptor integer associated to a file.
 *
 * If file is not a valid file handle, the behaviour of this function is
 * undefined.
 *
 * \param file the file pointer.
 *
 * \return the file descriptor, or -1 if the file is invalid.
 */
HOU_SYS_API int get_file_descriptor(FILE* file) noexcept;

/**
 * Retrieves the size of a file in bytes.
 *
 * \param file_descriptor the file descriptor. It can be obtained by using
 * get_file_descriptor.
 *
 * \return the size in bytes of the file. In case of error, it returns
 * the maximum value possible for the return type.
 */
HOU_SYS_API size_t get_file_byte_size(int file_descriptor) noexcept;

/**
 * Retrieves the filename extension of a given path.
 *
 * Supports unicode paths.
 *
 * \param path the path to be analyzed.
 *
 * \throws std::bad_alloc.
 *
 * \return the filename extension.
 */
HOU_SYS_API std::string get_filename_extension(const std::string& path);

}  // namespace hou

#endif
