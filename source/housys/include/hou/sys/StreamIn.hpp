// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_STREAM_IN_HPP
#define HOU_SYS_STREAM_IN_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/template_utils.hpp"

#include <array>
#include <string>
#include <vector>



namespace hou
{

/** Input stream interface.
 */
class HOU_SYS_API StreamIn
{
public:
  /** Destructor.
   */
  virtual ~StreamIn() {};

  /** Retrieves the number of bytes read by the last read operation.
   *
   *  \return the number of bytes read by the last read operation.
   */
  virtual size_t getReadByteCount() const = 0;

  /** Retrieves the number of elements read by the last read operation.
   *
   *  \return the number of elements read by the last read operation.
   */
  virtual size_t getReadElementCount() const = 0;

  /** Reads into a pod, not container variable.
   *
   *  Sets eof if reading over the end of the file.
   *  Throws in case of an error while reading.
   *
   *  \tparam T the element type.
   *  \param buf the variable to write into.
   *  \return a reference to this stream.
   */
  template <typename T>
    std::enable_if_t<std::is_pod<T>::value && !is_contiguous_container<T>::value
    , StreamIn>& read(T& buf);

  /** Reads into a contiguous container.
   *
   *  This function will try to read as many elements as the size of buf.
   *  If the end of the stream is reached, only part of buf will be written.
   *  Use getReadElementCount to determine how many elements were read.
   *
   *  Sets eof if reading over the end of the file.
   *  Throws in case of an error while reading.
   *
   *  \tparam T the container type
   *  \param buf the container to write into.
   *  \return a reference to this stream.
   */
  template <typename T>
    std::enable_if_t<is_contiguous_container<T>::value, StreamIn>& read(T& buf);

  /** Reads into a specified location in memory.
   *
   *  The caller must ensure that the memory range between buf and
   *  buf + (sizeof(T) * bufSize) is valid.
   *  If this is not the case, calling this function results in undefined
   *  behaviour.
   *
   *  This function will try to read bufSize elements.
   *  If the end of the stream is reached, only part of buf will be written.
   *  Use getReadElementCount to determine how many elements were read.
   *
   *  Sets eof if reading over the end of the file.
   *  Throws in case of an error while reading.
   *
   *  \tparam T the element type.
   *  \param buf pointer to the memory location to read into.
   *  \param bufSize the number of elements to be read.
   *  \return a reference to this stream.
   */
  template <typename T>
    StreamIn& read(T* buf, size_t bufSize);

protected:
  /** Reads into a specified location in memory.
   *
   *  The caller must ensure that the memory range between buf and
   *  buf + (elementSize * bufSize) is valid.
   *  If this is not the case, calling this function results in undefined
   *  behaviour.
   *
   *  This function will try to read bufSize elements.
   *  If the end of the stream is reached, only part of buf will be written.
   *  Use getReadElementCount to determine how many elements were read.
   *
   *  Sets eof if reading over the end of the file.
   *  Throws in case of an error while reading.
   *
   *  This function should be overridden by derived classes.
   *  All public read functions internally call this function.
   *
   *  \param buf a pointer to the memory location to write into.
   *  \param elementSize the size of a single element to be read.
   *  \param bufSize the number of elements to be read.
   */
  virtual void onRead(void* buf, size_t elementSize, size_t bufSize) = 0;
};

}



#include "hou/sys/StreamIn.inl"

#endif

