// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_BINARY_STREAM_IN_HPP
#define HOU_SYS_BINARY_STREAM_IN_HPP

#include "hou/sys/SysExport.hpp"
#include "hou/sys/BinaryStream.hpp"
#include "hou/sys/StreamIn.hpp"



namespace hou
{

/** Binary input stream interface.
 */
class HOU_SYS_API BinaryStreamIn
  : public BinaryStream
  , public StreamIn
{
public:
  /** Destructor.
   */
  virtual ~BinaryStreamIn() {};

  /** Reads the whole contents of the stream into memory.
   *
   *  \tparam T the container type to return.
   *
   *  \return a container containing the whole content of the file.
   */
  template <typename T>
    std::enable_if_t<isContiguousContainer<T>::value, T> readAll();
};

}

#include "hou/sys/BinaryStreamIn.inl"

#endif

