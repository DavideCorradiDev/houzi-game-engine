#include "hou/gfx/TextBoxFormattingParams.hpp"



namespace hou
{

const TextBoxFormattingParams TextBoxFormattingParams::Default(
  TextFlow::LeftRight, TextAnchoring::Baseline);



TextBoxFormattingParams::TextBoxFormattingParams(
  TextFlow textFlow, TextAnchoring textAnchoring)
  : mTextFlow(textFlow)
  , mTextAnchoring(textAnchoring)
{}



TextFlow TextBoxFormattingParams::getTextFlow() const
{
  return mTextFlow;
}



TextAnchoring TextBoxFormattingParams::getTextAnchoring() const
{
  return mTextAnchoring;
}

}  // namespace hou
