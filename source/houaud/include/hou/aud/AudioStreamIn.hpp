// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_STREAM_IN_HPP
#define HOU_AUD_AUDIO_STREAM_IN_HPP

#include "hou/aud/AudExport.hpp"
#include "hou/aud/AudioStream.hpp"
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
class HOU_AUD_API AudioStreamIn
  : public AudioStream
  , public stream_in
{
public:
  /** Destructor.
   */
  virtual ~AudioStreamIn() = 0;

  /** Get the number of samples read by the last read operation.
   */
  size_t getReadSampleCount() const;

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

#include "hou/aud/AudioStreamIn.inl"

#endif

