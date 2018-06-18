// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_context_profile.hpp"

#include "hou/cor/exception.hpp"

#define CONTEXT_PROFILE_CASE(co, os)                                           \
  case context_profile::co:                                                    \
    return (os) << #co



namespace hou
{

namespace gl
{

std::ostream& operator<<(std::ostream& os, context_profile co)
{
  switch(co)
  {
    CONTEXT_PROFILE_CASE(compatibility, os);
    CONTEXT_PROFILE_CASE(core, os);
    CONTEXT_PROFILE_CASE(es, os);
  }
  HOU_UNREACHABLE();
  return os;
}

}  // namespace gl

}  // namespace hou
