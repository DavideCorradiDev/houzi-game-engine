// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/test_texture_base.hpp"

template <>
hou::texture2 test_texture_base<hou::texture2>::make_texture(
  hou::texture_format format)
{
  return hou::texture2(hou::vec2u(1u, 1u), format);
}

template <>
hou::multisampled_texture2
  test_texture_base<hou::multisampled_texture2>::make_texture(
    hou::texture_format format)
{
  return hou::multisampled_texture2(hou::vec2u(1u, 1u), format);
}

template <>
hou::texture3 test_texture_base<hou::texture3>::make_texture(
  hou::texture_format format)
{
  return hou::texture3(hou::vec3u(1u, 1u, 1u), format);
}

template <>
hou::texture2_array test_texture_base<hou::texture2_array>::make_texture(
  hou::texture_format format)
{
  return hou::texture2_array(hou::vec3u(1u, 1u, 1u), format);
}

template <>
hou::multisampled_texture2_array
  test_texture_base<hou::multisampled_texture2_array>::make_texture(
    hou::texture_format format)
{
  return hou::multisampled_texture2_array(hou::vec3u(1u, 1u, 1u), format);
}

