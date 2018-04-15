// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/FrameBufferStatus.hpp"

#define FRAME_BUFFER_STATUS_CASE(fbs, os) \
  case FrameBufferStatus::fbs:            \
    return (os) << #fbs



namespace hou
{

std::ostream& operator<<(std::ostream& os, FrameBufferStatus fbs)
{
  switch(fbs)
  {
    FRAME_BUFFER_STATUS_CASE(Complete, os);
    FRAME_BUFFER_STATUS_CASE(Undefined, os);
    FRAME_BUFFER_STATUS_CASE(Unsupported, os);
    FRAME_BUFFER_STATUS_CASE(IncompleteAttachment, os);
    FRAME_BUFFER_STATUS_CASE(IncompleteMissingAttachment, os);
    FRAME_BUFFER_STATUS_CASE(IncompleteDrawBuffer, os);
    FRAME_BUFFER_STATUS_CASE(IncompleteReadBuffer, os);
    FRAME_BUFFER_STATUS_CASE(IncompleteMultisample, os);
    FRAME_BUFFER_STATUS_CASE(IncompleteLayerTargets, os);
    default:
    return os;
  }
}

}  // namespace hou
