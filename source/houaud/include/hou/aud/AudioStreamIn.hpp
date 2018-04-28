// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_STREAM_IN_HPP
#define HOU_AUD_AUDIO_STREAM_IN_HPP

#include "hou/aud/AudExport.hpp"
#include "hou/aud/AudioStream.hpp"
#include "hou/sys/StreamIn.hpp"

#include "hou/cor/not_null.hpp"

#include <memory>



namespace hou
{

/** Input audio stream.
 *
 *  Read operations throw if reading a non-integer number of samples.
 *
 */
class HOU_AUD_API AudioStreamIn
  : public AudioStream
  , public StreamIn
{
public:
  /** Destructor.
   */
  virtual ~AudioStreamIn() = 0;

  /** Get the number of samples read by the last read operation.
   */
  size_t getReadSampleCount() const;

  /** Reads the whole contents of the stream into memory.
   *
   *  \tparam T the container type to return.
   *
   *  \return a container containing the whole content of the file.
   */
  template <typename T>
    std::enable_if_t<is_contiguous_container<T>::value, T> readAll();
};

}

#include "hou/aud/AudioStreamIn.inl"

#endif

