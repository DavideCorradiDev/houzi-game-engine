// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_FILE_HANDLE_HPP
#define HOU_SYS_FILE_HANDLE_HPP

#include "hou/sys/sys_export.hpp"
#include "hou/cor/non_copyable.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/not_null.hpp"

#include "hou/sys/file_open_mode.hpp"
#include "hou/sys/file_type.hpp"

#include <string>



namespace hou
{

/** Manages the lifetime of a ph_file handle.
 */
class HOU_SYS_API file_handle
  : public non_copyable
{
public: 
  /** Path constructor.
   *
   *  Throws if the provided path is not valid.
   *
   *  \param path the path to the ph_file to be opened.
   *  \param mode the mode in which to open the ph_file.
   *  \param type the ph_file type.
   */
  file_handle(const std::string& path, file_open_mode mode, file_type type);

  /** Move constructor.
   *
   *  \param other the other file_handle.
   */
  file_handle(file_handle&& other);

  /** Destructor
   */
  ~file_handle();

  /** Conversion to FILE*.
   *
   *  \return the corresponding pointer to FILE.
   */
  operator FILE*() const;

private:
  FILE* m_file;
};

/** Returns the ph_file mode string equivalent to the provided file_open_mode and
 *  file_type.
 *
 *  The returned string can be used with functions like fopen.
 *
 *  \param mode the ph_file open mode.
 *  \param type the ph_file type.
 *  \return the associated string.
 */
HOU_SYS_API std::string get_file_mode_string(file_open_mode mode, file_type type);

/** Opens a ph_file.
 *
 *  Supports unicode paths.
 *
 *  \param path the path to the ph_file.
 *  \param mode the mode string (see fopen documentation).
 *  \return a pointer to the opened ph_file, or nullptr in case of failure.
 */
HOU_SYS_API FILE* open_file(const std::string& path, const std::string& mode);

/** Checks if a directory exists.
 *
 *  Supports unicode paths.
 *
 *  \param path the directory to be checked.
 *  \return true if the directory exists.
 */
HOU_SYS_API bool check_dir(const std::string& path);

/** Removes the specified directory.
 *
 *  Supports unicode paths.
 *
 *  \param path the directory to be removed.
 *  \return true if the directory was actually removed.
 */
HOU_SYS_API bool remove_dir(const std::string& path);

/** Renames the specified directory.
 *
 *  Supports unicode paths.
 *
 *  \param oldPath the directory to be moved.
 *  \param newPath the new directory.
 *  \return true if the directory was actually moved.
 */
HOU_SYS_API bool rename_dir(const std::string& oldPath
, const std::string& newPath);

/** Retrieves the size in bytes of a directory.
 *
 *  Supports unicode paths.
 *
 *  \param path the path.
 *  \return the size in bytes of the directory. In case of error, it returns
 *  the maximum value possible for the return type.
 */
HOU_SYS_API size_t get_dir_byte_size(const std::string& path);

/** Retrieves the filename extension of a given path.
 *
 *  Supports unicode paths.
 *
 *  \param path the path to be analyzed.
 *  \return the filename extension.
 */
HOU_SYS_API std::string get_filename_extension(const std::string& path);

/** Retrieves the ph_file descriptor integer associated to a ph_file.
 *
 *  If ph_file is not a valid ph_file handle, the behaviour of this function is
 *  undefined.
 *
 *  \param ph_file the ph_file pointer.
 *  \return the ph_file descriptor.
 */
HOU_SYS_API int get_file_descriptor(not_null<FILE*> ph_file);

/** Retrieves the size of a ph_file in bytes.
 *
 *  \param fileDescriptor the ph_file descriptor. It can be obtained by using
 *  get_file_descriptor.
 *  \return the size in bytes of the ph_file. In case of error, it returns
 *  the maximum value possible for the return type.
 */
HOU_SYS_API size_t get_file_byte_size(int fileDescriptor);

}

#endif

