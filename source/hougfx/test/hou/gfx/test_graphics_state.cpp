// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/graphics_state.hpp"

using namespace hou;
using namespace testing;



namespace hou
{

class test_graphics_state : public test_gfx_base
{
public:
  static std::vector<blending_factor> blending_factors;
  static std::vector<blending_equation> blending_equations;
};

std::vector<blending_factor> test_graphics_state::blending_factors{
  blending_factor::zero,
  blending_factor::one,
  blending_factor::src_color,
  blending_factor::one_minus_src_color,
  blending_factor::dst_color,
  blending_factor::one_minus_dst_color,
  blending_factor::src_alpha,
  blending_factor::one_minus_src_alpha,
  blending_factor::dst_alpha,
  blending_factor::one_minus_dst_alpha,
  blending_factor::constant_color,
  blending_factor::one_minus_constant_color,
  blending_factor::constant_alpha,
  blending_factor::one_minus_constant_alpha,
};

std::vector<blending_equation> test_graphics_state::blending_equations{
  blending_equation::add,
  blending_equation::subtract,
  blending_equation::reverse_subtract,
  blending_equation::min,
  blending_equation::max,
};

}  // namespace hou



TEST_F(test_graphics_state, set_vsync_mode)
{
  EXPECT_EQ(vsync_mode::enabled, get_vsync_mode());

  EXPECT_TRUE(set_vsync_mode(vsync_mode::disabled));
  EXPECT_EQ(vsync_mode::disabled, get_vsync_mode());

  if(set_vsync_mode(vsync_mode::adaptive))
  {
    EXPECT_EQ(vsync_mode::adaptive, get_vsync_mode());
  }

  EXPECT_TRUE(set_vsync_mode(vsync_mode::enabled));
  EXPECT_EQ(vsync_mode::enabled, get_vsync_mode());
}



TEST_F(test_graphics_state, multisampling_enabled)
{
  EXPECT_TRUE(is_multisampling_enabled());
  set_multisampling_enabled(true);
  EXPECT_TRUE(is_multisampling_enabled());
  set_multisampling_enabled(false);
  EXPECT_FALSE(is_multisampling_enabled());
  set_multisampling_enabled(false);
  EXPECT_FALSE(is_multisampling_enabled());
  set_multisampling_enabled(true);
  EXPECT_TRUE(is_multisampling_enabled());
}



TEST_F(test_graphics_state, blending_enabled)
{
  EXPECT_TRUE(is_blending_enabled());
  set_blending_enabled(true);
  EXPECT_TRUE(is_blending_enabled());
  set_blending_enabled(false);
  EXPECT_FALSE(is_blending_enabled());
  set_blending_enabled(false);
  EXPECT_FALSE(is_blending_enabled());
  set_blending_enabled(true);
  EXPECT_TRUE(is_blending_enabled());
}



TEST_F(test_graphics_state, source_blending_factor)
{
  blending_factor dst_factor = get_destination_blending_factor();
  EXPECT_EQ(blending_factor::src_alpha, get_source_blending_factor());
  for(auto f : blending_factors)
  {
    set_source_blending_factor(f);
    EXPECT_EQ(f, get_source_blending_factor());
    EXPECT_EQ(dst_factor, get_destination_blending_factor());
  }
  set_source_blending_factor(blending_factor::src_alpha);
}



TEST_F(test_graphics_state, destination_blending_factor)
{
  blending_factor src_factor = get_source_blending_factor();
  EXPECT_EQ(
    blending_factor::one_minus_src_alpha, get_destination_blending_factor());
  for(auto f : blending_factors)
  {
    set_destination_blending_factor(f);
    EXPECT_EQ(f, get_destination_blending_factor());
    EXPECT_EQ(src_factor, get_source_blending_factor());
  }
  set_destination_blending_factor(blending_factor::one_minus_src_alpha);
}



TEST_F(test_graphics_state, blending_equation)
{
  EXPECT_EQ(blending_equation::add, get_blending_equation());
  for(auto e : blending_equations)
  {
    set_blending_equation(e);
    EXPECT_EQ(e, get_blending_equation());
  }
  set_blending_equation(blending_equation::add);
}



TEST_F(test_graphics_state, blending_color)
{
  EXPECT_EQ(color::transparent(), get_blending_color());
  set_blending_color(color::red());
  EXPECT_EQ(color::red(), get_blending_color());
  set_blending_color(color::transparent());
  EXPECT_EQ(color::transparent(), get_blending_color());
}
