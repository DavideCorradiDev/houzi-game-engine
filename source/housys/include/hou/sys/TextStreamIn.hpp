// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_TEXT_STREAM_IN_HPP
#define HOU_SYS_TEXT_STREAM_IN_HPP

#include "hou/sys/sys_export.hpp"
#include "hou/sys/text_stream.hpp"
#include "hou/sys/stream_in.hpp"



namespace hou
{

/** text input ph_stream interface.
 */
class HOU_SYS_API text_stream_in
  : public text_stream
  , public stream_in
{
public:
  /** Destructor.
   */
  virtual ~text_stream_in() {};

  /** Reads the whole contents of the ph_stream into memory.
   *
   *  \tparam T the container type to return.
   *
   *  \return a container containing the whole content of the ph_file.
   */
  template <typename T>
    std::enable_if_t<is_contiguous_container<T>::value, T> read_all();
};

}

#include "hou/sys/text_stream_in.inl"

#endif

