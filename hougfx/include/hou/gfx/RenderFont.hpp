// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_RENDER_FONT_HPP
#define HOU_GFX_RENDER_FONT_HPP

#include "hou/gfx/GfxExport.hpp"
#include "hou/cor/NonCopyable.hpp"

#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/CharacterEncodings.hpp"

#include "hou/gfx/Font.hpp"
#include "hou/gfx/GlyphMetrics.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/mth/MatrixFwd.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>



namespace hou
{

class HOU_GFX_API RenderFont
  : public NonCopyable
{
public:
  using CharacterSet = std::vector<Utf32::CodeUnit>;

public:
  RenderFont(const CharacterSet& characterSet, const Font& font
    , const Vec3u& maxGlyphAtlasSize);
  RenderFont(const CharacterSet& characterSet, const Font& font);
  RenderFont(RenderFont&& other);

  // Change later to calls returning texture and mesh.
  void draw(const std::string& text) const;

private:
  class GlyphRenderInfo
  {
  public:
    GlyphRenderInfo();
    GlyphRenderInfo(const GlyphMetrics& metrics, const Vec3u& atlasPosition);

  public:
    GlyphMetrics mMetrics;
    Vec3u mAtlasPosition;
  };

private:
  const GlyphRenderInfo& getGlyphRenderInfo(Utf32::CodeUnit c) const;

private:
  Vec3u mAtlasSize;
  GlyphRenderInfo mPlaceholderGlyphRenderInfo;
  std::unordered_map<Utf32::CodeUnit, GlyphRenderInfo> mGlyphRenderInfoMap;
  std::unique_ptr<Texture2Array> mGlyphAtlas;
  float mLineSpacing;
};

}

#endif

