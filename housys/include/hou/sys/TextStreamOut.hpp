// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_TEXT_STREAM_OUT_HPP
#define HOU_SYS_TEXT_STREAM_OUT_HPP

#include "hou/sys/SysExport.hpp"
#include "hou/sys/TextStream.hpp"
#include "hou/sys/StreamOut.hpp"



namespace hou
{

/** Text output stream interface.
 */
class HOU_SYS_API TextStreamOut
  : public TextStream
  , public StreamOut
{
public:
  /** Destructor.
   */
  virtual ~TextStreamOut() {};
};

}

#endif



