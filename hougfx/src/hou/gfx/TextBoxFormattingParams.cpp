#include "hou/gfx/TextBoxFormattingParams.hpp"



namespace hou
{

const TextBoxFormattingParams TextBoxFormattingParams::Default(
  TextFlow::LeftRight, Vec2f::zero());



TextBoxFormattingParams::TextBoxFormattingParams(
  TextFlow textFlow, const Vec2f& maxSize)
  : mTextFlow(textFlow)
  , mMaxSize(maxSize)
{}



TextFlow TextBoxFormattingParams::getTextFlow() const
{
  return mTextFlow;
}



const Vec2f& TextBoxFormattingParams::getMaxSize() const
{
  return mMaxSize;
}

}  // namespace hou
