#include "hou/gfx/FormattedText.hpp"

#include "hou/gfx/Font.hpp"
#include "hou/gfx/Glyph.hpp"
#include "hou/gfx/TextureChannelMapping.hpp"

#include <map>
#include <set>



namespace hou
{

namespace
{

class AtlasGlyphCoordinates
{
public:
  AtlasGlyphCoordinates(const Vec3u& pos, const Vec2u& size, const Vec3u& texSize);

  Vec2f getTopLeftPos() const;
  Vec2f getTopRightPos() const;
  Vec2f getBottomRightPos() const;
  Vec2f getBottomLeftPos() const;
  Vec3f getTopLeftTex() const;
  Vec3f getTopRightTex() const;
  Vec3f getBottomRightTex() const;
  Vec3f getBottomLeftTex() const;

private:
  Vec3f mPos;
  Vec2f mSize;
  Vec3f mTexSize;
};

AtlasGlyphCoordinates::AtlasGlyphCoordinates(
  const Vec3u& pos, const Vec2u& size, const Vec3u& texSize)
  : mPos(static_cast<Vec3f>(pos))
  , mSize(static_cast<Vec2f>(size))
  , mTexSize(static_cast<Vec3f>(texSize))
{}

Vec2f AtlasGlyphCoordinates::getTopLeftPos() const
{
  return Vec2f();
}

Vec2f AtlasGlyphCoordinates::getTopRightPos() const
{
  return Vec2f(mSize.x(), 0.f);
}

Vec2f AtlasGlyphCoordinates::getBottomRightPos() const
{
  return Vec2f(mSize.x(), mSize.y());
}

Vec2f AtlasGlyphCoordinates::getBottomLeftPos() const
{
  return Vec2f(0.f, mSize.y());
}

Vec3f AtlasGlyphCoordinates::getTopLeftTex() const
{
  return Vec3f(mPos.x() / mTexSize.x(), mPos.y() / mTexSize.y(), mPos.z());;
}

Vec3f AtlasGlyphCoordinates::getTopRightTex() const
{
  return Vec3f((mPos.x() + mSize.x()) / mTexSize.x(), mPos.y() / mTexSize.y(), mPos.z());
}

Vec3f AtlasGlyphCoordinates::getBottomRightTex() const
{
  return Vec3f((mPos.x() + mSize.x()) / mTexSize.x(), (mPos.y() + mSize.y()) / mTexSize.y(), mPos.z());
}

Vec3f AtlasGlyphCoordinates::getBottomLeftTex() const
{
  return Vec3f(mPos.x() / mTexSize.x(), (mPos.y() + mSize.y()) / mTexSize.y(), mPos.z());
}

}

FormattedText::FormattedText(const std::string& text, const Font& font)
  : FormattedText(convertEncoding<Utf8, Utf32>(text), font)
{}

FormattedText::FormattedText(const std::u32string& text, const Font& font)
  : NonCopyable()
  , mAtlas(nullptr)
  , mMesh(nullptr)
{
  // Get all distinct characters.
  std::set<Utf32::CodeUnit> charSet(text.begin(), text.end());

  // Load and cache info about all necessary characters.
  std::map<Utf32::CodeUnit, Glyph> charCache;
  for(auto c : charSet)
  {
    charCache.insert(std::make_pair(c, font.getGlyph(c)));
  }

  // Find out the max size of the necessary glyphs.
  Vec2u maxGlyphSize(1u, 1u);
  for(const auto& kv : charCache)
  {
    const Vec2u& glyphSize = kv.second.getImage().getSize();
    for(size_t i = 0; i < Vec2u::getSize(); ++i)
    {
      if(glyphSize(i) > maxGlyphSize(i))
      {
        maxGlyphSize(i) = glyphSize(i);
      }
    }
  }

  // Compute the size of the atlas.
  Vec3u maxAtlasSize(
    std::min(2048u, static_cast<uint>(gl::getMaxTextureSize())),
    std::min(2048u, static_cast<uint>(gl::getMaxTextureSize())),
    std::min(256u, static_cast<uint>(gl::getMaxTextureLayers())));

  Vec3u maxAtlasGridSize = maxAtlasSize;
  maxAtlasGridSize.x() /= maxGlyphSize.x();
  maxAtlasGridSize.y() /= maxGlyphSize.y();

  uint charCount = static_cast<uint>(charSet.size());
  Vec3u atlasGridSize(std::min(charCount, maxAtlasGridSize.x()),
    std::min(charCount / maxAtlasGridSize.x(), maxAtlasGridSize.y() - 1u) + 1u,
    std::min(charCount / (maxAtlasGridSize.x() * maxAtlasGridSize.y()),
      maxAtlasGridSize.z() - 1u)
      + 1u);

  Vec3u atlasSize(atlasGridSize.x() * maxGlyphSize.x(),
    atlasGridSize.y() * maxGlyphSize.y(), atlasGridSize.z());

  // Create the atlas image and the tex coordinates cache.
  std::map<Utf32::CodeUnit, AtlasGlyphCoordinates> atlasCoordinatesCache;
  Image3R atlasImage(atlasSize);
  uint atlasGridLayer = atlasGridSize.x() * atlasGridSize.y();
  uint idx = 0;
  for(const auto& kv : charCache)
  {
    Vec3u glyphPosition(
      idx % atlasGridLayer % atlasGridSize.x() * maxGlyphSize.x(),
      idx % atlasGridLayer / atlasGridSize.x() * maxGlyphSize.y(),
      idx / atlasGridLayer);
    atlasImage.setSubImage(glyphPosition, kv.second.getImage());
    atlasCoordinatesCache.insert(std::make_pair(kv.first,
      AtlasGlyphCoordinates(
        glyphPosition, kv.second.getImage().getSize(), atlasSize)));
    ++idx;
  }

  // Create vertex list.
  static constexpr Utf32::CodeUnit lineFeed = 0x0000000A;

  Vec2f penPos(0.f, 0.f);
  float lineSpacing = font.getPixelLineSpacing();
  std::vector<TextVertex> vertices(6u * text.size(), TextVertex());
  for(size_t i = 0; i < text.size(); ++i)
  {
    Utf32::CodeUnit c = text[i];
    if(c == lineFeed)
    {
      penPos.x() = 0.f;
      penPos.y() += lineSpacing;
    }
    else
    {
      const GlyphMetrics& gm = charCache.at(c).getMetrics();
      const AtlasGlyphCoordinates& ac = atlasCoordinatesCache.at(c);

      Vec2f v0Pos = penPos + gm.getPixelHorizontalBearing() + ac.getTopLeftPos();
      Vec3f v0Tex = ac.getTopLeftTex();
      TextVertex v0(v0Pos, v0Tex);

      Vec2f v1Pos = v0Pos + ac.getTopRightPos();
      Vec3f v1Tex = ac.getTopRightTex();
      TextVertex v1(v1Pos, v1Tex);

      Vec2f v2Pos = v0Pos + ac.getBottomLeftPos();
      Vec3f v2Tex = ac.getBottomLeftTex();
      TextVertex v2(v2Pos, v2Tex);

      Vec2f v3Pos = v0Pos + ac.getBottomRightPos();
      Vec3f v3Tex = ac.getBottomRightTex();
      TextVertex v3(v3Pos, v3Tex);

      vertices[i * 6 + 0] = v0;
      vertices[i * 6 + 1] = v1;
      vertices[i * 6 + 2] = v2;
      vertices[i * 6 + 3] = v2;
      vertices[i * 6 + 4] = v1;
      vertices[i * 6 + 5] = v3;

      penPos.x() += gm.getPixelHorizontalAdvance();
    }
  }

  // Create the texture and mesh.
  mAtlas = std::make_unique<Texture2Array>(atlasImage, TextureFormat::R, 1u);
  mAtlas->setChannelMapping(TextureChannelMapping::Alpha);
  mMesh = std::make_unique<TextMesh>(
    MeshDrawMode::Triangles, MeshFillMode::Fill, vertices);
}



FormattedText::FormattedText(FormattedText&& other)
  : NonCopyable()
  , mAtlas(std::move(other.mAtlas))
  , mMesh(std::move(other.mMesh))
{}



const Texture2Array& FormattedText::getAtlas() const
{
  HOU_EXPECT_DEV(mAtlas != nullptr);
  return *mAtlas;
}



const TextMesh& FormattedText::getMesh() const
{
  HOU_EXPECT_DEV(mMesh != nullptr);
  return *mMesh;
}

}
