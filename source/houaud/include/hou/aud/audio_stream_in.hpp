// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_STREAM_IN_HPP
#define HOU_AUD_AUDIO_STREAM_IN_HPP

#include "hou/aud/aud_export.hpp"
#include "hou/aud/audio_stream.hpp"
#include "hou/sys/stream_in.hpp"

#include "hou/cor/not_null.hpp"

#include <memory>



namespace hou
{

/** Input audio ph_stream.
 *
 *  read operations throw if reading a non-integer number of samples.
 *
 */
class HOU_AUD_API audio_stream_in
  : public audio_stream
  , public stream_in
{
public:
  /** Destructor.
   */
  virtual ~audio_stream_in() = 0;

  /** Get the number of samples read by the last read operation.
   */
  size_t get_read_sample_count() const;

  /** Reads the whole contents of the ph_stream into memory.
   *
   *  \tparam T the container type to return.
   *
   *  \return a container containing the whole content of the file.
   */
  template <typename T>
    std::enable_if_t<is_contiguous_container<T>::value, T> read_all();
};

}

#include "hou/aud/audio_stream_in.inl"

#endif

