// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GLYPH_RENDER_INFO_HPP
#define HOU_GFX_GLYPH_RENDER_INFO_HPP

#include "hou/gfx/GfxExport.hpp"
#include "hou/cor/NonCopyable.hpp"

#include "hou/gfx/GlyphMetrics.hpp"
#include "hou/gfx/TextureFwd.hpp"
#include "hou/gfx/Vertex2.hpp"



namespace hou
{

class HOU_GFX_API GlyphRenderInfo
  : public NonCopyable
{
public:
  GlyphRenderInfo(const GlyphMetrics& metrics, const Texture2& texture
    , const Vec2f& textureOffset);
  GlyphRenderInfo(GlyphRenderInfo&& other);

  const GlyphMetrics& getMetrics() const;
  const Mesh2& getMesh() const;
  const Texture2& getTexture() const;

private:
  GlyphMetrics mMetrics;
  Mesh2 mMesh;
  const Texture2* mTexture;
};

}

#endif

