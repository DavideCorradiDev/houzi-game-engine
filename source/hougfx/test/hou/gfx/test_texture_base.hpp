// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_TEST_TEXTURE_BASE_HPP
#define HOU_TEST_TEXTURE_BASE_HPP

#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/multisampled_texture2.hpp"
#include "hou/gfx/multisampled_texture2_array.hpp"
#include "hou/gfx/texture2.hpp"
#include "hou/gfx/texture2_array.hpp"
#include "hou/gfx/texture3.hpp"

#include "hou/cor/std_vector.hpp"

template <typename TexType>
class test_texture_base : public test_gfx_base
{
public:
  static TexType make_texture(
    hou::texture_format format = hou::texture_format::rgba);

public:
  static const std::vector<hou::texture_format> color_formats;
  static const std::vector<hou::texture_format> all_formats;
  static const std::vector<hou::texture_filter> all_filters;
  static const std::vector<hou::texture_wrap_mode> all_wrap_modes;
};

template <typename TexType>
const std::vector<hou::texture_format>
  test_texture_base<TexType>::color_formats{
    hou::texture_format::r,
    hou::texture_format::rg,
    hou::texture_format::rgb,
    hou::texture_format::rgba,
  };

template <typename TexType>
const std::vector<hou::texture_format> test_texture_base<TexType>::all_formats{
  hou::texture_format::r,
  hou::texture_format::rg,
  hou::texture_format::rgb,
  hou::texture_format::rgba,
  hou::texture_format::depth_stencil,
};

template <typename TexType>
const std::vector<hou::texture_filter> test_texture_base<TexType>::all_filters{
  hou::texture_filter::nearest,
  hou::texture_filter::linear,
  hou::texture_filter::bilinear,
  hou::texture_filter::trilinear,
};

template <typename TexType>
const std::vector<hou::texture_wrap_mode>
  test_texture_base<TexType>::all_wrap_modes{
    hou::texture_wrap_mode::repeat,
    hou::texture_wrap_mode::mirrored_repeat,
    hou::texture_wrap_mode::clamp_to_edge,
  };

#endif
