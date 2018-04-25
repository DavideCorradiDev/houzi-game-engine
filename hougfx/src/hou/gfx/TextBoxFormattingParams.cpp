#include "hou/gfx/TextBoxFormattingParams.hpp"



namespace hou
{

const TextBoxFormattingParams TextBoxFormattingParams::Default(
  TextFlow::LeftRight, TextAnchoring::Baseline, Vec2f::zero());



TextBoxFormattingParams::TextBoxFormattingParams(
  TextFlow textFlow, TextAnchoring textAnchoring, const Vec2f& maxSize)
  : mTextFlow(textFlow)
  , mTextAnchoring(textAnchoring)
  , mMaxSize(maxSize)
{}



TextFlow TextBoxFormattingParams::getTextFlow() const
{
  return mTextFlow;
}



TextAnchoring TextBoxFormattingParams::getTextAnchoring() const
{
  return mTextAnchoring;
}



const Vec2f& TextBoxFormattingParams::getMaxSize() const
{
  return mMaxSize;
}

}  // namespace hou
