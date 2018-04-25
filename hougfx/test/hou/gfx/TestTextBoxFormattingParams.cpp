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
  TextAnchoring textAnchoringRef = TextAnchoring::Baseline;
  Vec2f maxSizeRef(1.f, 2.f);
  TextBoxFormattingParams tbfp(textFlowRef, textAnchoringRef, maxSizeRef);

  EXPECT_EQ(textFlowRef, tbfp.getTextFlow());
  EXPECT_EQ(textAnchoringRef, tbfp.getTextAnchoring());
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
    TextBoxFormattingParams tbfp(textFlow, TextAnchoring::Baseline, Vec2f::zero());
    EXPECT_EQ(textFlow, tbfp.getTextFlow());
  }
}



TEST_F(TestTextBoxFormattingParams, TextAnchoringValues)
{
  std::vector<TextAnchoring> textAnchoringValues
  {
    TextAnchoring::TopLeft,
    TextAnchoring::TopCenter,
    TextAnchoring::TopRight,
    TextAnchoring::CenterLeft,
    TextAnchoring::Center,
    TextAnchoring::CenterRight,
    TextAnchoring::BottomLeft,
    TextAnchoring::BottomCenter,
    TextAnchoring::BottomRight,
    TextAnchoring::Baseline,
  };

  for(auto textAnchoring : textAnchoringValues)
  {
    TextBoxFormattingParams tbfp(TextFlow::LeftRight, textAnchoring, Vec2f::zero());
    EXPECT_EQ(textAnchoring, tbfp.getTextAnchoring());
  }
}



TEST_F(TestTextBoxFormattingParams, MaxSizeValues)
{
  std::vector<Vec2f> maxSizeValues
  {
    Vec2f(-1.f, -2.f),
    Vec2f::zero(),
    Vec2f(1.f, 2.f),
    Vec2f(1024.5f, 768.25f),
  };

  for(auto maxSize : maxSizeValues)
  {
    TextBoxFormattingParams tbfp(TextFlow::LeftRight, TextAnchoring::TopLeft, maxSize);
    EXPECT_EQ(maxSize, tbfp.getMaxSize());
  }
}
