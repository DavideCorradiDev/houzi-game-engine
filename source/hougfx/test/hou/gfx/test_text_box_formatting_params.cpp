// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/text_box_formatting_params.hpp"

using namespace hou;
using namespace testing;

namespace
{

class TestTextBoxFormattingParams : public Test
{};

}



TEST_F(TestTextBoxFormattingParams, Constructor)
{
  text_flow textFlowRef = text_flow::LeftRight;
  vec2f maxSizeRef(1.f, 2.f);
  text_box_formatting_params tbfp(textFlowRef, maxSizeRef);

  EXPECT_EQ(textFlowRef, tbfp.get_text_flow());
  HOU_EXPECT_FLOAT_CLOSE(maxSizeRef, tbfp.get_max_size());
}



TEST_F(TestTextBoxFormattingParams, TextFlowValues)
{
  std::vector<text_flow> textFlowValues
  {
    text_flow::LeftRight,
    text_flow::RightLeft,
    text_flow::TopBottom,
    text_flow::BottomTop
  };

  for(auto textFlow : textFlowValues)
  {
    text_box_formatting_params tbfp(textFlow, vec2f::zero());
    EXPECT_EQ(textFlow, tbfp.get_text_flow());
  }
}



TEST_F(TestTextBoxFormattingParams, MaxSizeValues)
{
  std::vector<vec2f> maxSizeValues
  {
    vec2f(-1.f, -2.f),
    vec2f::zero(),
    vec2f(1.f, 2.f),
    vec2f(1024.5f, 768.25f),
  };

  for(auto maxSize : maxSizeValues)
  {
    text_box_formatting_params tbfp(text_flow::LeftRight, maxSize);
    EXPECT_EQ(maxSize, tbfp.get_max_size());
  }
}
