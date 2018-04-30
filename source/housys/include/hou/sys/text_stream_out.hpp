// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_TEXT_STREAM_OUT_HPP
#define HOU_SYS_TEXT_STREAM_OUT_HPP

#include "hou/sys/stream_out.hpp"
#include "hou/sys/sys_export.hpp"
#include "hou/sys/text_stream.hpp"



namespace hou
{

/** text output ph_stream interface.
 */
class HOU_SYS_API text_stream_out
  : public text_stream
  , public stream_out
{
public:
  /** Destructor.
   */
  virtual ~text_stream_out(){};
};

}  // namespace hou

#endif
