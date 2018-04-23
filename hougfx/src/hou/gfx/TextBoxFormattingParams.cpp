#include "hou/gfx/TextBoxFormattingParams.hpp"



namespace hou
{

const TextBoxFormattingParams
    TextBoxFormattingParams::Default(TextFlow::LeftRight);



TextBoxFormattingParams::TextBoxFormattingParams(TextFlow textFlow)
  : mTextFlow(textFlow)
{}



TextFlow TextBoxFormattingParams::getTextFlow() const
{
  return mTextFlow;
}

}  // namespace hou
