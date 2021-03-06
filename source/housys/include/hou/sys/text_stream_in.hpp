// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_TEXT_STREAM_IN_HPP
#define HOU_SYS_TEXT_STREAM_IN_HPP

#include "hou/sys/stream_in.hpp"
#include "hou/sys/text_stream.hpp"

#include "hou/sys/sys_config.hpp"



namespace hou
{

/**
 * text input stream interface.
 */
class HOU_SYS_API text_stream_in
  : public text_stream
  , public stream_in
{
public:
  /**
   * Destructor.
   */
  virtual ~text_stream_in(){};

  /**
   * Reads the whole contents of the stream into memory.
   *
   * \tparam T the container type to return.
   *
   * \throws hou::read_error in case of an error.
   *
   * \return a container containing the whole content of the file.
   */
  template <typename T>
  std::enable_if_t<is_contiguous_container<T>::value, T> read_all();
};

}  // namespace hou

#include "hou/sys/text_stream_in.inl"

#endif
