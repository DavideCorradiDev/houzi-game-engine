// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/TextAnchoring.hpp"

#define TEXT_ANCHORING_CASE(ta, os) \
  case TextAnchoring::ta:           \
    return (os) << #ta

namespace hou
{

std::ostream& operator<<(std::ostream& os, TextAnchoring ta)
{
  switch(ta)
  {
    TEXT_ANCHORING_CASE(TopLeft, os);
    TEXT_ANCHORING_CASE(TopCenter, os);
    TEXT_ANCHORING_CASE(TopRight, os);
    TEXT_ANCHORING_CASE(CenterLeft, os);
    TEXT_ANCHORING_CASE(Center, os);
    TEXT_ANCHORING_CASE(CenterRight, os);
    TEXT_ANCHORING_CASE(BottomLeft, os);
    TEXT_ANCHORING_CASE(BottomCenter, os);
    TEXT_ANCHORING_CASE(BottomRight, os);
    TEXT_ANCHORING_CASE(Baseline, os);
  default:
    return os;
  }
}

}  // namespace hou
