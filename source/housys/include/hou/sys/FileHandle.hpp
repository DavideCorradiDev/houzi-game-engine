// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_FILE_HANDLE_HPP
#define HOU_SYS_FILE_HANDLE_HPP

#include "hou/sys/SysExport.hpp"
#include "hou/cor/non_copyable.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/not_null.hpp"

#include "hou/sys/FileOpenMode.hpp"
#include "hou/sys/FileType.hpp"

#include <string>



namespace hou
{

/** Manages the lifetime of a file handle.
 */
class HOU_SYS_API FileHandle
  : public non_copyable
{
public: 
  /** Path constructor.
   *
   *  Throws if the provided path is not valid.
   *
   *  \param path the path to the file to be opened.
   *  \param mode the mode in which to open the file.
   *  \param type the file type.
   */
  FileHandle(const std::string& path, FileOpenMode mode, FileType type);

  /** Move constructor.
   *
   *  \param other the other FileHandle.
   */
  FileHandle(FileHandle&& other);

  /** Destructor
   */
  ~FileHandle();

  /** Conversion to FILE*.
   *
   *  \return the corresponding pointer to FILE.
   */
  operator FILE*() const;

private:
  FILE* mFile;
};

/** Returns the file mode string equivalent to the provided FileOpenMode and
 *  FileType.
 *
 *  The returned string can be used with functions like fopen.
 *
 *  \param mode the file open mode.
 *  \param type the file type.
 *  \return the associated string.
 */
HOU_SYS_API std::string getFileModeString(FileOpenMode mode, FileType type);

/** Opens a file.
 *
 *  Supports unicode paths.
 *
 *  \param path the path to the file.
 *  \param mode the mode string (see fopen documentation).
 *  \return a pointer to the opened file, or nullptr in case of failure.
 */
HOU_SYS_API FILE* openFile(const std::string& path, const std::string& mode);

/** Checks if a directory exists.
 *
 *  Supports unicode paths.
 *
 *  \param path the directory to be checked.
 *  \return true if the directory exists.
 */
HOU_SYS_API bool checkDir(const std::string& path);

/** Removes the specified directory.
 *
 *  Supports unicode paths.
 *
 *  \param path the directory to be removed.
 *  \return true if the directory was actually removed.
 */
HOU_SYS_API bool removeDir(const std::string& path);

/** Renames the specified directory.
 *
 *  Supports unicode paths.
 *
 *  \param oldPath the directory to be moved.
 *  \param newPath the new directory.
 *  \return true if the directory was actually moved.
 */
HOU_SYS_API bool renameDir(const std::string& oldPath
, const std::string& newPath);

/** Retrieves the size in bytes of a directory.
 *
 *  Supports unicode paths.
 *
 *  \param path the path.
 *  \return the size in bytes of the directory. In case of error, it returns
 *  the maximum value possible for the return type.
 */
HOU_SYS_API size_t getDirByteSize(const std::string& path);

/** Retrieves the filename extension of a given path.
 *
 *  Supports unicode paths.
 *
 *  \param path the path to be analyzed.
 *  \return the filename extension.
 */
HOU_SYS_API std::string getFilenameExtension(const std::string& path);

/** Retrieves the file descriptor integer associated to a file.
 *
 *  If file is not a valid file handle, the behaviour of this function is
 *  undefined.
 *
 *  \param file the file pointer.
 *  \return the file descriptor.
 */
HOU_SYS_API int getFileDescriptor(not_null<FILE*> file);

/** Retrieves the size of a file in bytes.
 *
 *  \param fileDescriptor the file descriptor. It can be obtained by using
 *  getFileDescriptor.
 *  \return the size in bytes of the file. In case of error, it returns
 *  the maximum value possible for the return type.
 */
HOU_SYS_API size_t getFileByteSize(int fileDescriptor);

}

#endif

