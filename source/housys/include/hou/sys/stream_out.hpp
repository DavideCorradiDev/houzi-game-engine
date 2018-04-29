// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HZI_SYS_STREAM_OUT_HPP
#define HZI_SYS_STREAM_OUT_HPP

#include "hou/sys/sys_export.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/template_utils.hpp"

#include <array>
#include <string>
#include <vector>



namespace hou
{

/** Output ph_stream interface.
 */
class HOU_SYS_API stream_out
{
public:
  /** Destructor.
   */
  virtual ~stream_out() {};

  /** Retrieves the number of bytes written by the last write operation.
   *
   *  \return the number of bytes written by the last write operation.
   */
  virtual size_t get_write_byte_count() const = 0;

  /** Retrieves the number of elements written by the last write operation.
   *
   *  \return the number of elements written by the last write operation.
   */
  virtual size_t get_write_element_count() const = 0;

  /** Writes from a pod, not container variable.
   *
   *  Throws in case of an error while writing.
   *
   *  \tparam T the element type.
   *  \param buf the variable to be written.
   *  \return a reference to this ph_stream.
   */
  template <typename T>
    std::enable_if_t<std::is_pod<T>::value && !is_contiguous_container<T>::value
    , stream_out>& write(const T& buf);

  /** Writes from a contiguous container.
   *
   *  This function will write all the elements contained in buf.
   *
   *  Throws in case of an error while writing.
   *
   *  \tparam T the container type.
   *  \param buf the container to be written.
   *  \return a reference to this ph_stream.
   */
  template <typename T>
    std::enable_if_t<is_contiguous_container<T>::value, stream_out>&
    write(const T& buf);

  /** Writes from a specified location in memory.
   *
   *  The caller must ensure that the memory range between buf and
   *  buf + (sizeof(T) * bufSize) is valid.
   *  If this is not the case, calling this function results in undefined
   *  behaviour.
   *
   *  Throws in case of an error while writing.
   *
   *  \tparam T the element type.
   *  \param buf pointer to the memory location to be written.
   *  \param bufSize the number of elements to be written.
   *  \return a reference to this ph_stream.
   */
  template <typename T>
    stream_out& write(const T* buf, size_t bufSize);

protected:
  /** Writes from a specified location in memory.
   *
   *  The caller must ensure that the memory range between buf and
   *  buf + (elementSize * bufSize) is valid.
   *  If this is not the case, calling this function results in undefined
   *  behaviour.
   *
   *  Throws in case of an error while writing.
   *
   *  This function should be overridden by derived classes.
   *  all public write functions internally call this function.
   *
   *  \param buf a pointer to the memory location to write into.
   *  \param elementSize the size of a single element to be written.
   *  \param bufSize the number of elements to be written.
   */
  virtual void on_write(const void* buf, size_t elementSize, size_t bufSize) = 0;
};

}



#include "hou/sys/stream_out.inl"

#endif

