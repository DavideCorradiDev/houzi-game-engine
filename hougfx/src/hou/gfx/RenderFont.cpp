#include "hou/gfx/RenderFont.hpp"

#include "hou/gfx/Glyph.hpp"
#include "hou/gfx/TextureChannelMapping.hpp"
#include "hou/gfx/VertexBuffer.hpp"
#include "hou/gfx/VertexArray.hpp"
#include "hou/gfx/VertexFormat.hpp"
#include "hou/gfx/TextVertex.hpp"
#include "hou/gfx/Mesh.hpp"

#include "hou/gl/GlUtils.hpp"

#include "hou/mth/Matrix.hpp"
#include "hou/mth/Rectangle.hpp"

#include <algorithm>



namespace hou
{

RenderFont::RenderFont(const CharacterSet& characterSet, const Font& font
  , const Vec3u& maxGlyphAtlasSize)
  : NonCopyable()
  , mAtlasSize()
  , mPlaceholderGlyphRenderInfo()
  , mGlyphRenderInfoMap()
  , mGlyphAtlas(nullptr)
  , mLineSpacing(font.getLineSpacing() / 64.f)
{
  // Check that no glyph is loaded twice?
  HOU_EXPECT(maxGlyphAtlasSize.x() > 0u
    && maxGlyphAtlasSize.x() < static_cast<uint>(gl::getMaxTextureSize()));
  HOU_EXPECT(maxGlyphAtlasSize.y() > 0u
    && maxGlyphAtlasSize.y() < static_cast<uint>(gl::getMaxTextureSize()));
  HOU_EXPECT(maxGlyphAtlasSize.z() > 0u 
    && maxGlyphAtlasSize.z() < static_cast<uint>(gl::getMaxTextureLayers()));

  uint characterCount = characterSet.size() + 1;
  Recti glyphBoundingBox = font.getGlyphBoundingBox();
  Vec2f globalFloatGlyphMaxSize = static_cast<Vec2f>(glyphBoundingBox.getSize()
    - glyphBoundingBox.getPosition()) / 64.f;
  Vec2u globalGlyphMaxSize(
    static_cast<uint>(std::ceil(globalFloatGlyphMaxSize.x())),
    static_cast<uint>(std::ceil(globalFloatGlyphMaxSize.y())));
  Vec2f floatGlyphMaxSize;
  for(auto c : characterSet)
  {
    Glyph g = font.getGlyph(c);
    if(g.getMetrics().getSize().x() > floatGlyphMaxSize.x())
    {
      floatGlyphMaxSize.x() = g.getMetrics().getSize().x();
    }
    if(g.getMetrics().getSize().y() > floatGlyphMaxSize.y())
    {
      floatGlyphMaxSize.y() = g.getMetrics().getSize().y();
    }
  }
  floatGlyphMaxSize /= 64.f;
  Vec2u glyphMaxSize(static_cast<uint>(std::ceil(floatGlyphMaxSize.x())),
      static_cast<uint>(std::ceil(floatGlyphMaxSize.y())));

  Vec3u maxGlyphAtlasGridSize
    ( maxGlyphAtlasSize.x() / glyphMaxSize.x()
    , maxGlyphAtlasSize.y() / glyphMaxSize.y()
    , maxGlyphAtlasSize.z());

  std::cout << "maxGlyphAtlasSize " << transpose(maxGlyphAtlasSize) << std::endl;
  std::cout << "maxGlyphAtlasGridSize " << transpose(maxGlyphAtlasGridSize) << std::endl;

  HOU_EXPECT(maxGlyphAtlasGridSize.x() > 0u);
  HOU_EXPECT(maxGlyphAtlasGridSize.y() > 0u);
  HOU_EXPECT(maxGlyphAtlasGridSize.z() > 0u);
  HOU_EXPECT(maxGlyphAtlasGridSize.x() * maxGlyphAtlasGridSize.y()
    * maxGlyphAtlasGridSize.z() >= characterCount);

  Vec3u glyphAtlasGridSize
    ( std::min(characterCount, maxGlyphAtlasGridSize.x())
    , std::min(characterCount / maxGlyphAtlasGridSize.x()
      , maxGlyphAtlasGridSize.y() - 1) + 1
    , std::min(characterCount / maxGlyphAtlasGridSize.x()
      / maxGlyphAtlasGridSize.y(), maxGlyphAtlasGridSize.z() - 1) + 1
    );
  mAtlasSize = Vec3u
    ( std::max(1u, glyphAtlasGridSize.x() * glyphMaxSize.x())
    , std::max(1u, glyphAtlasGridSize.y() * glyphMaxSize.y())
    , std::max(1u, glyphAtlasGridSize.z()));

  std::cout << "glyphBoundingBox " << glyphBoundingBox << std::endl;
  std::cout << "globalFloatGlyphMaxSize " << transpose(globalFloatGlyphMaxSize) << std::endl;
  std::cout << "globalGlyphMaxSize " << transpose(globalGlyphMaxSize) << std::endl;
  std::cout << "floatGlyphMaxSize " << transpose(floatGlyphMaxSize) << std::endl;
  std::cout << "glyphMaxSize " << transpose(glyphMaxSize) << std::endl;
  std::cout << "mAtlasSize " << transpose(mAtlasSize) << std::endl;
  std::cout << "glyphAtlasGridSize " << transpose(glyphAtlasGridSize) << std::endl;

  HOU_ENSURE(glyphAtlasGridSize.x() * glyphAtlasGridSize.y()
    * glyphAtlasGridSize.z() >= characterCount);

  mGlyphAtlas = std::make_unique<Texture2Array>(mAtlasSize, TextureFormat::R);
  mGlyphAtlas->setChannelMapping(TextureChannelMapping::Alpha);

  uint atlasLayerGridSize = glyphAtlasGridSize.x() * glyphAtlasGridSize.y();

  Glyph placeholderGlyph = font.getGlyph(std::numeric_limits<Utf32::CodeUnit>::max());
  mPlaceholderGlyphRenderInfo.mMetrics = placeholderGlyph.getMetrics();
  mGlyphAtlas->setSubImage(Vec3u::zero(), Image3R(placeholderGlyph.getImage()));

  for(size_t i = 0; i < characterSet.size(); ++i)
  {
    Vec3u glyphAtlasPosition
      ( static_cast<uint>((i+1) % atlasLayerGridSize % glyphAtlasGridSize.x() * glyphMaxSize.x())
      , static_cast<uint>((i+1) % atlasLayerGridSize / glyphAtlasGridSize.x() * glyphMaxSize.y())
      , static_cast<uint>((i+1) / atlasLayerGridSize));
    Glyph g = font.getGlyph(characterSet[i]);
    // std::cout << "character " << i << " '" << characterSet[i] << "'; ";
    // std::cout << "glyphAtlasPosition " << transpose(glyphAtlasPosition) << "; ";
    // std::cout << "bmpSize " << transpose(g.getImage().getSize()) << std::endl;
    mGlyphRenderInfoMap.insert(std::make_pair(characterSet[i]
      , GlyphRenderInfo(g.getMetrics(), glyphAtlasPosition)));
    mGlyphAtlas->setSubImage(glyphAtlasPosition, Image3R(g.getImage()));
  }
}



RenderFont::RenderFont(const CharacterSet& characterSet, const Font& font)
  : RenderFont(characterSet, font, Vec3u
    ( std::min(2048u, static_cast<uint>(gl::getMaxTextureSize()))
    , std::min(2048u, static_cast<uint>(gl::getMaxTextureSize()))
    , std::min(256u, static_cast<uint>(gl::getMaxTextureLayers()))))
{}



RenderFont::RenderFont(RenderFont&& other)
  : mAtlasSize(std::move(other.mAtlasSize))
  , mPlaceholderGlyphRenderInfo(std::move(other.mPlaceholderGlyphRenderInfo))
  , mGlyphRenderInfoMap(std::move(other.mGlyphRenderInfoMap))
  , mGlyphAtlas(std::move(other.mGlyphAtlas))
{}



void RenderFont::draw(const std::string& text) const
{
  static constexpr Utf32::CodeUnit sLineFeed = 0x0000000A;

  Vec2f penPos(0.f, 0.f);
  std::u32string textUtf32 = convertEncoding<Utf8, Utf32>(text);
  std::vector<TextVertex> vertices(6u * textUtf32.size(), TextVertex());
  for(size_t i = 0; i < textUtf32.size(); ++i)
  {
    Utf32::CodeUnit c = textUtf32[i];
    if(c == sLineFeed)
    {
      penPos.x() = 0.f;
      penPos.y() += mLineSpacing;
    }
    else
    {
      const GlyphRenderInfo& gri = getGlyphRenderInfo(c);

      Vec2f v0Pos = penPos
        + static_cast<Vec2f>(gri.mMetrics.getHorizontalBearing()) / 64.f;
      Vec3f v0Tex(static_cast<float>(gri.mAtlasPosition.x())
          / static_cast<float>(mAtlasSize.x()),
        static_cast<float>(gri.mAtlasPosition.y())
          / static_cast<float>(mAtlasSize.y()),
        static_cast<float>(gri.mAtlasPosition.z()));
      TextVertex v0(v0Pos, v0Tex);

      Vec2f v1Pos = v0Pos + Vec2f(gri.mMetrics.getSize().x() / 64.f, 0.f);
      Vec3f v1Tex = v0Tex
        + Vec3f(gri.mMetrics.getSize().x() / 64.f
              / static_cast<float>(mAtlasSize.x()),
            0.f, 0.f);
      TextVertex v1(v1Pos, v1Tex);

      Vec2f v2Pos = v0Pos + Vec2f(0.f, gri.mMetrics.getSize().y() / 64.f);
      Vec3f v2Tex = v0Tex
        + Vec3f(0.f,
            gri.mMetrics.getSize().y() / 64.f
              / static_cast<float>(mAtlasSize.y()),
            0.f);
      TextVertex v2(v2Pos, v2Tex);

      Vec2f v3Pos(v1Pos.x(), v2Pos.y());
      Vec3f v3Tex(v1Tex.x(), v2Tex.y(), v0Tex.z());
      TextVertex v3(v3Pos, v3Tex);

      vertices[i * 6 + 0] = v0;
      vertices[i * 6 + 1] = v1;
      vertices[i * 6 + 2] = v2;
      vertices[i * 6 + 3] = v2;
      vertices[i * 6 + 4] = v1;
      vertices[i * 6 + 5] = v3;

      penPos.x() += gri.mMetrics.getHorizontalAdvance() / 64.f;
    }
  }
  Texture::bind(*mGlyphAtlas, 0u);
  TextMesh mesh(MeshDrawMode::Triangles, MeshFillMode::Fill, vertices);
  TextMesh::draw(mesh);
}



const RenderFont::GlyphRenderInfo& RenderFont::getGlyphRenderInfo(Utf32::CodeUnit c) const
{
  auto glyphInfoFoundIt = mGlyphRenderInfoMap.find(c);
  if(glyphInfoFoundIt == mGlyphRenderInfoMap.end())
  {
    return mPlaceholderGlyphRenderInfo;
  }
  return glyphInfoFoundIt->second;
}



RenderFont::GlyphRenderInfo::GlyphRenderInfo()
  : mMetrics()
  , mAtlasPosition()
{}



RenderFont::GlyphRenderInfo::GlyphRenderInfo(const GlyphMetrics& metrics
  , const Vec3u& atlasPosition)
  : mMetrics(metrics)
  , mAtlasPosition(atlasPosition)
{}

}
