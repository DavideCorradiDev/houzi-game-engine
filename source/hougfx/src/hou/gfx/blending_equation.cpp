// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/blending_equation.hpp"

#include "hou/cor/exception.hpp"

#define BLENDING_EQUATION_CASE(be, os)                                         \
  case blending_equation::be:                                                  \
    return (os) << #be



namespace hou
{

std::ostream& operator<<(std::ostream& os, blending_equation be)
{
  switch(be)
  {
    BLENDING_EQUATION_CASE(add, os);
    BLENDING_EQUATION_CASE(subtract, os);
    BLENDING_EQUATION_CASE(reverse_subtract, os);
    BLENDING_EQUATION_CASE(min, os);
    BLENDING_EQUATION_CASE(max, os);
  }
  HOU_UNREACHABLE();
  return os;
}

}  // namespace hou

