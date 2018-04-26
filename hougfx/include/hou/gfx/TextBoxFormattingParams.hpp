// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_BOX_FORMATTING_PARAMS_HPP
#define HOU_GFX_TEXT_BOX_FORMATTING_PARAMS_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/mth/Matrix.hpp"

#include "hou/gfx/TextFlow.hpp"



namespace hou
{

class HOU_GFX_API TextBoxFormattingParams
{
public:
  static const TextBoxFormattingParams Default;

public:
  TextBoxFormattingParams(TextFlow textFlow, const Vec2f& maxSize);

  TextFlow getTextFlow() const;
  const Vec2f& getMaxSize() const;

private:
  TextFlow mTextFlow;
  Vec2f mMaxSize;
};

}  // namespace hou

#endif
