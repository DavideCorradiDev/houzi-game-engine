#include "hou/gfx/TextBoxFormattingParams.hpp"



namespace hou
{

const TextBoxFormattingParams TextBoxFormattingParams::Default(
  TextFlow::LeftRight, vec2f::zero());



TextBoxFormattingParams::TextBoxFormattingParams(
  TextFlow textFlow, const vec2f& maxSize)
  : mTextFlow(textFlow)
  , mMaxSize(maxSize)
{}



TextFlow TextBoxFormattingParams::getTextFlow() const
{
  return mTextFlow;
}



const vec2f& TextBoxFormattingParams::getMaxSize() const
{
  return mMaxSize;
}

}  // namespace hou
