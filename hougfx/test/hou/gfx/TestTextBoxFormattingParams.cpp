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
  TextBoxFormattingParams tbfp(textFlowRef);

  EXPECT_EQ(textFlowRef, tbfp.getTextFlow());
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
    TextBoxFormattingParams tbfp(textFlow);
    EXPECT_EQ(textFlow, tbfp.getTextFlow());
  }
}
