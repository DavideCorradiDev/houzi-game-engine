// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FORMATTED_TEXT_HPP
#define HOU_GFX_FORMATTED_TEXT_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/NonCopyable.hpp"

#include "hou/cor/StdString.hpp"
#include "hou/cor/StdVector.hpp"

#include "hou/mth/Rectangle.hpp"
#include "hou/mth/Transform2.hpp"

#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/TextBoxFormattingParams.hpp"
#include "hou/gfx/TextVertex.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/sys/ImageFwd.hpp"

#include <memory>



namespace hou
{

class Font;

class HOU_GFX_API FormattedText
  : public NonCopyable
{
public:
  using VertexContainer = std::vector<TextVertex>;

public:
  FormattedText(const std::string& text, const Font& font);
  FormattedText(const std::u32string& text, const Font& font);
  FormattedText(const std::string& text, const Font& font,
    const TextBoxFormattingParams& tbfp);
  FormattedText(const std::u32string& text, const Font& font,
    const TextBoxFormattingParams& tbfp);
  FormattedText(FormattedText&& other);

  const Texture2Array& getAtlas() const;
  const TextMesh& getMesh() const;
  const Rectf& getBoundingBox() const;
  const Trans2f& getTransform() const;

private:
  std::unique_ptr<Texture2Array> mAtlas;
  std::unique_ptr<TextMesh> mMesh;
  Rectf mBoundingBox;
  Trans2f mTransform;
};

}

#endif
