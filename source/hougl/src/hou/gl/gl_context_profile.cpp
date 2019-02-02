// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_context_profile.hpp"

#include "hou/cor/core_functions.hpp"

#define CONTEXT_PROFILE_CASE(cp, os)                                           \
  case context_profile::cp:                                                    \
    return (os) << #cp



namespace hou
{

namespace gl
{

std::ostream& operator<<(std::ostream& os, context_profile cp)
{
  switch(cp)
  {
    CONTEXT_PROFILE_CASE(any, os);
    CONTEXT_PROFILE_CASE(compatibility, os);
    CONTEXT_PROFILE_CASE(core, os);
    CONTEXT_PROFILE_CASE(es, os);
  }
  return STREAM_VALUE(os, context_profile, cp);
}

}  // namespace gl

}  // namespace hou
