// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_BINARY_STREAM_OUT_HPP
#define HOU_SYS_BINARY_STREAM_OUT_HPP

#include "hou/sys/SysExport.hpp"
#include "hou/sys/BinaryStream.hpp"
#include "hou/sys/StreamOut.hpp"



namespace hou
{

/** Binary output stream interface.
 */
class HOU_SYS_API BinaryStreamOut
  : public BinaryStream
  , public StreamOut
{
public:
  /** Destructor.
   */
  virtual ~BinaryStreamOut() {};
};

}

#endif




