// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_BINARY_STREAM_OUT_HPP
#define HOU_SYS_BINARY_STREAM_OUT_HPP

#include "hou/sys/binary_stream.hpp"
#include "hou/sys/stream_out.hpp"
#include "hou/sys/sys_export.hpp"



namespace hou
{

/** binary output ph_stream interface.
 */
class HOU_SYS_API binary_stream_out
  : public binary_stream
  , public stream_out
{
public:
  /** Destructor.
   */
  virtual ~binary_stream_out(){};
};

}  // namespace hou

#endif
