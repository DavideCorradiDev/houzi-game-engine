#include "hou/gfx/TextBoxFormattingParams.hpp"



namespace hou
{

TextBoxFormattingParams::TextBoxFormattingParams(TextFlow textFlow)
  : mTextFlow(textFlow)
{}



TextFlow TextBoxFormattingParams::getTextFlow() const
{
  return mTextFlow;
}

}  // namespace hou
