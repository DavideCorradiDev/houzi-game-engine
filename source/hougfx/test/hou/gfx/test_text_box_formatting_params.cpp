// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/text_box_formatting_params.hpp"

using namespace hou;
using namespace testing;

namespace
{

class test_text_box_formatting_params : public Test
{};

}  // namespace



TEST_F(test_text_box_formatting_params, constructor)
{
  text_flow text_flow_ref = text_flow::left_right;
  vec2f max_size_ref(1.f, 2.f);
  text_box_formatting_params tbfp(text_flow_ref, max_size_ref);

  EXPECT_EQ(text_flow_ref, tbfp.get_text_flow());
  EXPECT_FLOAT_CLOSE(max_size_ref, tbfp.get_max_size());
}



TEST_F(test_text_box_formatting_params, text_flow_values)
{
  std::vector<text_flow> text_flow_values{text_flow::left_right,
    text_flow::right_left, text_flow::top_bottom, text_flow::bottom_top};

  for(auto textFlow : text_flow_values)
  {
    text_box_formatting_params tbfp(textFlow, vec2f::zero());
    EXPECT_EQ(textFlow, tbfp.get_text_flow());
  }
}



TEST_F(test_text_box_formatting_params, max_size_values)
{
  std::vector<vec2f> max_size_values{
    vec2f(-1.f, -2.f),
    vec2f::zero(),
    vec2f(1.f, 2.f),
    vec2f(1024.5f, 768.25f),
  };

  for(auto max_size : max_size_values)
  {
    text_box_formatting_params tbfp(text_flow::left_right, max_size);
    EXPECT_EQ(max_size, tbfp.get_max_size());
  }
}
