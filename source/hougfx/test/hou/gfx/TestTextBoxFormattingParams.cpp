// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/TextBoxFormattingParams.hpp"

using namespace hou;
using namespace testing;

namespace
{

class TestTextBoxFormattingParams : public Test
{};

}



TEST_F(TestTextBoxFormattingParams, Constructor)
{
  TextFlow textFlowRef = TextFlow::LeftRight;
  vec2f maxSizeRef(1.f, 2.f);
  TextBoxFormattingParams tbfp(textFlowRef, maxSizeRef);

  EXPECT_EQ(textFlowRef, tbfp.getTextFlow());
  HOU_EXPECT_FLOAT_CLOSE(maxSizeRef, tbfp.getMaxSize());
}



TEST_F(TestTextBoxFormattingParams, TextFlowValues)
{
  std::vector<TextFlow> textFlowValues
  {
    TextFlow::LeftRight,
    TextFlow::RightLeft,
    TextFlow::TopBottom,
    TextFlow::BottomTop
  };

  for(auto textFlow : textFlowValues)
  {
    TextBoxFormattingParams tbfp(textFlow, vec2f::zero());
    EXPECT_EQ(textFlow, tbfp.getTextFlow());
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
    TextBoxFormattingParams tbfp(TextFlow::LeftRight, maxSize);
    EXPECT_EQ(maxSize, tbfp.getMaxSize());
  }
}
