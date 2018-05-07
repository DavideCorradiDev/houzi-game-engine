// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_FILE_HPP
#define HOU_SYS_FILE_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/sys/file_handle.hpp"

#include "hou/sys/sys_export.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/template_utils.hpp"

#include <string>



namespace hou
{

/** Class representing a file.
 */
class HOU_SYS_API file : public non_copyable
{
public:
  /** Path constructor.
   *
   * \param path the path to the file.
   *
   * \param mode the file open mode.
   *
   * \param type the file type.
   *
   * \throws hou::file_open_error if the file could not be opened.
   */
  file(const std::string& path, file_open_mode mode, file_type type);

  /** Move constructor.
   *
   * \param other the other object.
   */
  file(file&& other);

  /** Checks the end of file indicator.
   *
   * \return true if the end of file indicator is set.
   */
  bool eof() const noexcept;

  /** Checks the error indicator.
   *
   * \return true if the error indicator is set.
   */
  bool error() const noexcept;

  /** Retrieves the size of the file in bytes.
   *
   * \return the size of the file in bytes.
   */
  size_t get_byte_count() const noexcept;

  /** Retrieves the current position indicator.
   *
   * \throws hou::file_cursor_error in case of an error.
   *
   * \return the current position indicator.
   */
  long tell() const;

  /** Sets the current position indicator.
   *
   * \throws hou::file_cursor_error in case of an error.
   *
   * \param pos the position indicator.
   * For text files, pos must be a value obtained by a previous call to tell()
   * on the same file object, otherwise the behaviour is undefined. For binary
   * files pos can be any non-negative value representing the offset in bytes
   * from the beginning of the file.
   */
  void seek_set(long pos);

  /** Moves the current position indicator to the specified position from the
   * end.
   *
   * Calling this function on text files is undefined.
   * Calling this function on binary files is unspecified.
   * If possible, avoid calling this function.
   * Throws if pos is a nagative value.
   *
   * \throws hou::file_cursor_error in case of an error.
   *
   * \param pos the position from the end of the file.
   */
  void seek_from_end(long pos);

  /** Moves the current position indicator.
   *
   * Calling this function on text files in undefined.
   * Throws if the current position indicator would move to a negative position.
   *
   * \throws hou::file_cursor_error in case of an error.
   *
   * \param offset the offset in bytes from the current position.
   */
  void seek_offset(long offset);

  /** Flushes the file.
   *
   * Throws if the current position indicator would move to a negative position.
   *
   * If the file is open for writing, any data in the output buffer is flushed
   * to the actual file.
   *
   * \throws std::file_write_error in case of an error.
   */
  void flush() const;

  /** Reads a character from the file.
   *
   * Sets eof if reading over the end of the file.
   *
   * \param c the character to be read into.
   *
   * \throws hou::file_read_error in case of an error.
   *
   * \return true if a character was read.
   */
  bool getc(char& c);

  /** Writes a character into the file.
   *
   * \param c the character to be written.
   *
   * \throws hou::file_write_error in case of an error.
   */
  void putc(char c);

  /** Reads a string from the file.
   *
   * It tries to read a number of characters equal to the size of the string,
   * or until a newline character is encountered.
   * If it is not possible to read enough characters, only the first characters
   * of the string will be set.
   * Check the return value to see how many characters were read.
   *
   * Sets eof if reading over the end of the file.
   *
   * \param str the string to be read into.
   *
   * \throws hou::file_read_error in case of an error.
   *
   * \return the number of characters read.
   */
  size_t gets(std::string& str);

  /** Writes a string into the file.
   *
   * \param str the string to be written.
   *
   * \throws hou::file_write_error in case of an error.
   */
  void puts(const std::string& str);

  /** Reads into a specified location in memory.
   *
   * The caller must ensure that the memory range between buf and
   * buf + (element_size * buf_size) is valid.
   * If this is not the case, calling this function results in undefined
   * behaviour.
   *
   * This function will try to read buf_size elements.
   * If the end of the stream is reached, only part of buf will be written.
   * Check the return value to see how many elements were read.
   *
   * Sets eof if reading over the end of the file.
   *
   * \param buf a pointer to the memory location to write into.
   *
   * \param element_size the size of a single element to be written.
   *
   * \param buf_size the number of elements to be written.
   *
   * \throws hou::file_read_error in case of an error.
   *
   * \return the number of elements read.
   */
  size_t read(void* buf, size_t element_size, size_t buf_size);

  /** Writes from a specified location in memory.
   *
   * The caller must ensure that the memory range between buf and
   * buf + (element_size * buf_size) is valid.
   * If this is not the case, calling this function results in undefined
   * behaviour.
   *
   * \param buf a pointer to the memory location to write into.
   *
   * \param element_size the size of a single element to be written.
   *
   * \throws hou::file_write_error in case of an error.
   *
   * \param buf_size the number of elements to be written.
   */
  void write(const void* buf, size_t element_size, size_t buf_size);

  /** Reads into a specified location in memory.
   *
   * The caller must ensure that the memory range between buf and
   * buf + (sizeof(T) * buf_size) is valid.
   * If this is not the case, calling this function results in undefined
   * behaviour.
   *
   * This function will try to read buf_size elements.
   * If the end of the stream is reached, only part of buf will be written.
   * Check the return value to see how many elements were read.
   *
   * Sets eof if reading over the end of the file.
   *
   * \tparam T the element type.
   *
   * \param buf pointer to the memory location to read into.
   *
   * \param buf_size the number of elements to be read.
   *
   * \throws hou::file_read_error in case of an error.
   *
   * \return the number of elements read.
   */
  template <typename T>
  size_t read(T* buf, size_t buf_size);

  /** Writes from a specified location in memory.
   *
   * The caller must ensure that the memory range between buf and
   * buf + (sizeof(T) * buf_size) is valid.
   * If this is not the case, calling this function results in undefined
   * behaviour.
   *
   * \tparam T the element type.
   *
   * \param buf pointer to the memory location to be written.
   *
   * \param buf_size the number of elements to be written.
   *
   * \throws hou::file_write_error in case of an error.
   *
   * \return a reference to this stream.
   */
  template <typename T>
  void write(const T* buf, size_t buf_size);

  /** Reads into a container.
   *
   * This function will try to read as many elements as the size of buffer.
   * If the end of the stream is reached, only part of buf will be written.
   * Check the return value to see how many elements were read.
   *
   * Sets eof if reading over the end of the file.
   *
   * \tparam Container the container type.
   *
   * \param buffer the container to read into.
   *
   * \throws hou::file_read_error in case of an error.
   *
   * \return the number of elements read.
   */
  template <typename Container, typename Enable
    = std::enable_if_t<is_contiguous_container<Container>::value>>
  size_t read(Container& buffer);

  /** Writes from a container.
   *
   * This function will write all the elements contained in buf.
   *
   * \tparam Container the container type.
   *
   * \param buffer the container to be written.
   *
   * \throws hou::file_write_error in case of an error.
   *
   * \return a reference to this stream.
   */
  template <typename Container, typename Enable
    = std::enable_if_t<is_contiguous_container<Container>::value>>
  void write(const Container& buffer);

private:
  void seek(long pos, int origin) const;
  void update_flags() noexcept;

private:
  file_handle m_handle;
  bool m_eof;
  bool m_error;
};

}  // namespace hou



#include "hou/sys/file.inl"

#endif
