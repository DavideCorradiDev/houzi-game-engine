// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_STREAM_IN_HPP
#define HOU_SYS_STREAM_IN_HPP

#include "hou/sys/sys_export.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/template_utils.hpp"

#include <array>
#include <string>
#include <vector>



namespace hou
{

/** Input stream interface.
 */
class HOU_SYS_API stream_in
{
public:
  /** Destructor.
   */
  virtual ~stream_in(){};

  /** Retrieves the number of bytes read by the last read operation.
   *
   * \return the number of bytes read by the last read operation.
   */
  virtual size_t get_read_byte_count() const noexcept = 0;

  /** Retrieves the number of elements read by the last read operation.
   *
   * \return the number of elements read by the last read operation.
   */
  virtual size_t get_read_element_count() const noexcept = 0;

  /** Reads into a pod, not container variable.
   *
   * Sets eof if reading over the end of the file.
   *
   * \tparam T the element type.
   *
   * \param buf the variable to write into.
   *
   * \throws hou::file_read_error in case of an error.
   *
   * \return a reference to this stream.
   */
  template <typename T>
  std::enable_if_t<std::is_pod<T>::value && !is_contiguous_container<T>::value,
    stream_in>&
    read(T& buf);

  /** Reads into a contiguous container.
   *
   * This function will try to read as many elements as the size of buf.
   * If the end of the stream is reached, only part of buf will be written.
   * Use get_read_element_count to determine how many elements were read.
   *
   * Sets eof if reading over the end of the file.
   * Throws in case of an error while reading.
   *
   * \tparam T the container type
   *
   * \param buf the container to write into.
   *
   * \throws hou::file_read_error in case of an error.
   *
   * \return a reference to this stream.
   */
  template <typename T>
  std::enable_if_t<is_contiguous_container<T>::value, stream_in>& read(T& buf);

  /** Reads into a specified location in memory.
   *
   * The caller must ensure that the memory range between buf and
   * buf + (sizeof(T) * buf_size) is valid.
   * If this is not the case, calling this function results in undefined
   * behaviour.
   *
   * This function will try to read buf_size elements.
   * If the end of the stream is reached, only part of buf will be written.
   * Use get_read_element_count to determine how many elements were read.
   *
   * Sets eof if reading over the end of the file.
   * Throws in case of an error while reading.
   *
   * \tparam T the element type.
   *
   * \param buf pointer to the memory location to read into.
   *
   * \param buf_size the number of elements to be read.
   *
   * \throws hou::file_read_error in case of an error.
   *
   * \return a reference to this stream.
   */
  template <typename T>
  stream_in& read(T* buf, size_t buf_size);

protected:
  /** Reads into a specified location in memory.
   *
   * The caller must ensure that the memory range between buf and
   * buf + (element_size * buf_size) is valid.
   * If this is not the case, calling this function results in undefined
   * behaviour.
   *
   * This function will try to read buf_size elements.
   * If the end of the stream is reached, only part of buf will be written.
   * Use get_read_element_count to determine how many elements were read.
   *
   * Sets eof if reading over the end of the file.
   * Throws in case of an error while reading.
   *
   * This function should be overridden by derived classes.
   * all public read functions internally call this function.
   *
   * \param buf a pointer to the memory location to write into.
   *
   * \param element_size the size of a single element to be read.
   *
   * \param buf_size the number of elements to be read.
   *
   * \throws hou::file_read_error in case of an error.
   */
  virtual void on_read(void* buf, size_t element_size, size_t buf_size) = 0;
};

}  // namespace hou



#include "hou/sys/stream_in.inl"

#endif
