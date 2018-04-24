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
  TextBoxFormattingParams tbfp(textFlowRef, textAnchoringRef);

  EXPECT_EQ(textFlowRef, tbfp.getTextFlow());
  EXPECT_EQ(textAnchoringRef, tbfp.getTextAnchoring());
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
    TextBoxFormattingParams tbfp(textFlow, TextAnchoring::Baseline);
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
    TextBoxFormattingParams tbfp(TextFlow::LeftRight, textAnchoring);
    EXPECT_EQ(textAnchoring, tbfp.getTextAnchoring());
  }
}
