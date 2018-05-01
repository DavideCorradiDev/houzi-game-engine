// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/text_flow.hpp"

#define TEXT_FLOW_CASE(tf, os) \
  case text_flow::tf: \
    return (os) << #tf

namespace hou
{

std::ostream& operator<<(std::ostream& os, text_flow tf)
{
  switch(tf)
  {
    TEXT_FLOW_CASE(left_right, os);
    TEXT_FLOW_CASE(right_left, os);
    TEXT_FLOW_CASE(top_bottom, os);
    TEXT_FLOW_CASE(bottom_top, os);
    default:
      return os;
  }
}

}  // namespace hou
