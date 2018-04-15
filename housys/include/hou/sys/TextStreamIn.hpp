// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_TEXT_STREAM_IN_HPP
#define HOU_SYS_TEXT_STREAM_IN_HPP

#include "hou/sys/SysExport.hpp"
#include "hou/sys/TextStream.hpp"
#include "hou/sys/StreamIn.hpp"



namespace hou
{

/** Text input stream interface.
 */
class HOU_SYS_API TextStreamIn
  : public TextStream
  , public StreamIn
{
public:
  /** Destructor.
   */
  virtual ~TextStreamIn() {};
};

}

#endif


