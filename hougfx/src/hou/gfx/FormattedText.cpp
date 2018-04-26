#include "hou/gfx/FormattedText.hpp"

#include "hou/cor/Span.hpp"

#include "hou/gfx/Font.hpp"
#include "hou/gfx/Glyph.hpp"
#include "hou/gfx/TextureChannelMapping.hpp"

#include <map>
#include <set>



namespace hou
{

namespace
{

class GlyphCache
{
public:
  GlyphCache(const Span<const Utf32::CodeUnit>& characters, const Font& font);

  const std::map<Utf32::CodeUnit, Glyph>& getGlyphs() const;
  const Glyph& getGlyph(Utf32::CodeUnit c) const;
  const Vec2u& getMaxGlyphSize() const;
  uint getSize() const;

private:
  std::map<Utf32::CodeUnit, Glyph> mGlyphs;
  Vec2u mMaxGlyphSize;
};


class AtlasGlyphCoordinates
{
public:
  AtlasGlyphCoordinates(
    const Vec3u& pos, const Vec2u& size, const Vec3u& texSize);

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



class GlyphAtlas
{
public:
  GlyphAtlas(const GlyphCache& cache);

  const Image3R& getImage() const;
  const AtlasGlyphCoordinates& getAtlasGlyphCoordinates(
    Utf32::CodeUnit c) const;

private:
  static Vec3u computeAtlasGridSize(const GlyphCache& cache);

private:
  Vec3u mAtlasGridSize;
  Image3R mImage;
  std::map<Utf32::CodeUnit, AtlasGlyphCoordinates> mGlyphCoords;
};



class TextFormatter
{
public:
  TextFormatter(std::u32string text, const Font&, const GlyphCache& cache,
    const GlyphAtlas& atlas, const TextBoxFormattingParams params);

  const std::vector<TextVertex>& getVertices() const;
  const Rectf& getBoundingBox() const;

private:
  static constexpr uint VerticesPerGlyph = 6u;
  static constexpr Utf32::CodeUnit LineFeed = 0x0000000A;
  static constexpr Utf32::CodeUnit WhiteSpace = 0x00000020;

private:
  float computeGlyphAdvance(const GlyphMetrics& gm, const Font& font) const;
  Vec2f computeGlyphBearing(const GlyphMetrics& gm, const Font& font) const;
  void insertLineBreaks(const Font& font, const GlyphCache& cache,
    const TextBoxFormattingParams& tbfp);
  void generateVertices(
    const Font& font, const GlyphCache& cache, const GlyphAtlas& atlas);
  void computeBoundingBox();

private:
  std::u32string mText;
  std::vector<TextVertex> mVertices;
  size_t mLineCoord;
  size_t mColumnCoord;
  float mLineSpacing;
  float mCharSpacingFactor;
  Rectf mBoundingBox;
};



GlyphCache::GlyphCache(
  const Span<const Utf32::CodeUnit>& characters, const Font& font)
  : mGlyphs()
  , mMaxGlyphSize()
{
  for(auto c : characters)
  {
    auto inserted = mGlyphs.insert(std::make_pair(c, font.getGlyph(c)));
    if(inserted.second)
    {
      const Vec2u& glyphSize = inserted.first->second.getImage().getSize();
      for(size_t i = 0; i < Vec2u::getSize(); ++i)
      {
        if(glyphSize(i) > mMaxGlyphSize(i))
        {
          mMaxGlyphSize(i) = glyphSize(i);
        }
      }
    }
  }
}



const std::map<Utf32::CodeUnit, Glyph>& GlyphCache::getGlyphs() const
{
  return mGlyphs;
}



const Glyph& GlyphCache::getGlyph(Utf32::CodeUnit c) const
{
  return mGlyphs.at(c);
}



const Vec2u& GlyphCache::getMaxGlyphSize() const
{
  return mMaxGlyphSize;
}



Vec3u GlyphAtlas::computeAtlasGridSize(const GlyphCache& cache)
{
  static const Vec3u maxAtlasSize(
    std::min(2048u, static_cast<uint>(gl::getMaxTextureSize())),
    std::min(2048u, static_cast<uint>(gl::getMaxTextureSize())),
    std::min(256u, static_cast<uint>(gl::getMaxTextureLayers())));

  Vec3u maxAtlasGridSize = maxAtlasSize;
  maxAtlasGridSize.x() /= cache.getMaxGlyphSize().x();
  maxAtlasGridSize.y() /= cache.getMaxGlyphSize().y();

  uint charCount = cache.getSize();
  return Vec3u(std::min(charCount, maxAtlasGridSize.x()),
    std::min(charCount / maxAtlasGridSize.x(), maxAtlasGridSize.y() - 1u) + 1u,
    std::min(charCount / (maxAtlasGridSize.x() * maxAtlasGridSize.y()),
      maxAtlasGridSize.z() - 1u)
      + 1u);
}



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
  return Vec3f(mPos.x() / mTexSize.x(), mPos.y() / mTexSize.y(), mPos.z());
  ;
}



Vec3f AtlasGlyphCoordinates::getTopRightTex() const
{
  return Vec3f(
    (mPos.x() + mSize.x()) / mTexSize.x(), mPos.y() / mTexSize.y(), mPos.z());
}



Vec3f AtlasGlyphCoordinates::getBottomRightTex() const
{
  return Vec3f((mPos.x() + mSize.x()) / mTexSize.x(),
    (mPos.y() + mSize.y()) / mTexSize.y(), mPos.z());
}



Vec3f AtlasGlyphCoordinates::getBottomLeftTex() const
{
  return Vec3f(
    mPos.x() / mTexSize.x(), (mPos.y() + mSize.y()) / mTexSize.y(), mPos.z());
}



uint GlyphCache::getSize() const
{
  return mGlyphs.size();
}



GlyphAtlas::GlyphAtlas(const GlyphCache& cache)
  : mAtlasGridSize(computeAtlasGridSize(cache))
  , mImage(Vec3u(mAtlasGridSize.x() * cache.getMaxGlyphSize().x(),
      mAtlasGridSize.y() * cache.getMaxGlyphSize().y(), mAtlasGridSize.z()))
  , mGlyphCoords()
{
  uint atlasGridLayer = mAtlasGridSize.x() * mAtlasGridSize.y();
  uint idx = 0;
  for(const auto& kv : cache.getGlyphs())
  {
    Vec3u glyphPosition(
      idx % atlasGridLayer % mAtlasGridSize.x() * cache.getMaxGlyphSize().x(),
      idx % atlasGridLayer / mAtlasGridSize.x() * cache.getMaxGlyphSize().y(),
      idx / atlasGridLayer);
    mImage.setSubImage(glyphPosition, kv.second.getImage());
    mGlyphCoords.insert(std::make_pair(kv.first,
      AtlasGlyphCoordinates(
        glyphPosition, kv.second.getImage().getSize(), mImage.getSize())));
    ++idx;
  }
}



const Image3R& GlyphAtlas::getImage() const
{
  return mImage;
}



const AtlasGlyphCoordinates& GlyphAtlas::getAtlasGlyphCoordinates(
  Utf32::CodeUnit c) const
{
  return mGlyphCoords.at(c);
}



TextFormatter::TextFormatter(std::u32string text, const Font& font,
  const GlyphCache& cache, const GlyphAtlas& atlas,
  const TextBoxFormattingParams tbfp)
  : mText(text)
  , mVertices(VerticesPerGlyph * text.size(), TextVertex())
  , mLineCoord((tbfp.getTextFlow() == TextFlow::LeftRight
                 || tbfp.getTextFlow() == TextFlow::RightLeft)
        ? 0u
        : 1u)
  , mColumnCoord(mLineCoord == 0u ? 1u : 0u)
  , mLineSpacing(mLineCoord == 0u ? font.getPixelLineSpacing()
                                  : 0.5f * font.getMaxPixelAdvance())
  , mCharSpacingFactor(tbfp.getTextFlow() == TextFlow::LeftRight
          || tbfp.getTextFlow() == TextFlow::TopBottom
        ? 1.f
        : -1.f)
  , mBoundingBox()
{
  insertLineBreaks(font, cache, tbfp);
  generateVertices(font, cache, atlas);
  computeBoundingBox();
}



float TextFormatter::computeGlyphAdvance(
  const GlyphMetrics& gm, const Font& font) const
{
  return mCharSpacingFactor
    * (mLineCoord == 0u ? gm.getPixelHorizontalAdvance()
                        : (font.hasVertical() ? gm.getPixelVerticalAdvance()
                                              : gm.getPixelSize().y() * 1.5f));
}



Vec2f TextFormatter::computeGlyphBearing(
  const GlyphMetrics& gm, const Font& font) const
{
  Vec2f vertBearing = font.hasVertical()
    ? gm.getPixelVerticalBearing()
    : Vec2f(-0.5f * gm.getPixelSize().x(), 0.f);

  const Vec2f& bearing
    = mLineCoord == 0 ? gm.getPixelHorizontalBearing() : vertBearing;

  return bearing;
}



void TextFormatter::insertLineBreaks(const Font& font, const GlyphCache& cache,
  const TextBoxFormattingParams& tbfp)
{
  // This function wraps text inside the bounding box.
  // The algorithm should be improved to be consistent with common typographic
  // rules.
  if(tbfp.getMaxSize().x() <= 0.f || tbfp.getMaxSize().y() <= 0.f)
  {
    return;
  }

  const float maxLineSize = tbfp.getMaxSize()(mLineCoord);
  const float maxColumnSize = tbfp.getMaxSize()(mColumnCoord);

  float lineSize = 0.f;
  float columnSize = mLineSpacing;
  size_t pos = 0;
  size_t newlinepos = mText.find_first_of(LineFeed);
  while(pos < mText.size())
  {
    // If the new line makes the mText box overflow, delete the rest of the
    // string.
    if(columnSize > maxColumnSize)
    {
      mText.erase(pos);
      break;
    }

    size_t wordStart = pos < mText.size()
      ? std::min(mText.find_first_not_of(WhiteSpace, pos), newlinepos)
      : mText.size();
    size_t wordEnd = wordStart < mText.size()
      ? std::min(mText.find_first_of(WhiteSpace, wordStart), newlinepos)
      : mText.size();

    // Compute the size of the next word.
    float wordSize = 0.f;
    for(size_t i = pos; i < wordEnd; ++i)
    {
      HOU_ENSURE_DEV(i < mText.size());
      wordSize += std::fabs(
        computeGlyphAdvance(cache.getGlyph(mText[i]).getMetrics(), font));
    }

    // If the first word is a space, remove it for size computations.
    float wordSizeAdjustment = 0.f;
    if(mText[pos] == WhiteSpace)
    {
      wordSizeAdjustment = std::fabs(
        computeGlyphAdvance(cache.getGlyph(WhiteSpace).getMetrics(), font));
    }

    // If the word can't possibly fit on any line.
    // The rest of the string need not be rendered.
    if((wordSize - wordSizeAdjustment) > maxLineSize)
    {
      mText.erase(pos);
      break;
    }

    // If the word doesn't fit on this line Add a line break in place of the
    // first space.
    lineSize += wordSize;
    if(lineSize > maxLineSize)
    {
      mText[pos] = '\n';
      columnSize += mLineSpacing;
      lineSize = wordSize - wordSizeAdjustment;
    }

    // If the new line makes the mText box overflow, delete the rest of the
    // string.
    if(columnSize > maxColumnSize)
    {
      mText.erase(pos);
      break;
    }

    // If new line character, start a new line.
    pos = wordEnd;
    if(mText[wordEnd] == LineFeed)
    {
      newlinepos = wordEnd + 1 < mText.size()
        ? mText.find_first_of(LineFeed, wordEnd + 1)
        : mText.size();
      columnSize += mLineSpacing;
      lineSize = 0.f;
    }
  }
}



void TextFormatter::generateVertices(
  const Font& font, const GlyphCache& cache, const GlyphAtlas& atlas)
{
  Vec2f penPos(0.f, 0.f);
  for(size_t i = 0; i < mText.size(); ++i)
  {
    Utf32::CodeUnit c = mText[i];
    if(c == LineFeed)
    {
      penPos(mLineCoord) = 0.f;
      penPos(mColumnCoord) += mLineSpacing;
    }
    else
    {
      const GlyphMetrics& gm = cache.getGlyph(c).getMetrics();
      const AtlasGlyphCoordinates& ac = atlas.getAtlasGlyphCoordinates(c);

      float advance = computeGlyphAdvance(gm, font);

      if(advance < 0.f)
      {
        penPos(mLineCoord) += advance;
      }

      Vec2f bearing = computeGlyphBearing(gm, font);

      Vec2f v0Pos = penPos + bearing + ac.getTopLeftPos();
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

      mVertices[i * 6 + 0] = v0;
      mVertices[i * 6 + 1] = v1;
      mVertices[i * 6 + 2] = v2;
      mVertices[i * 6 + 3] = v2;
      mVertices[i * 6 + 4] = v1;
      mVertices[i * 6 + 5] = v3;

      if(advance > 0.f)
      {
        penPos(mLineCoord) += advance;
      }
    }
  }
}


void TextFormatter::computeBoundingBox()
{
  if(mVertices.empty())
  {
    return;
  }

  static constexpr size_t tlOffset = 0u;
  static constexpr size_t brOffset = 5u;

  Vec2f topLeft = mVertices[tlOffset].getPosition();
  Vec2f bottomRight = mVertices[brOffset].getPosition();

  for(size_t i = VerticesPerGlyph; i < mVertices.size(); i += VerticesPerGlyph)
  {
    const Vec2f& tlPos = mVertices[i + tlOffset].getPosition();
    const Vec2f& brPos = mVertices[i + brOffset].getPosition();
    if(tlPos.x() < topLeft.x())
    {
      topLeft.x() = tlPos.x();
    }
    if(tlPos.y() < topLeft.y())
    {
      topLeft.y() = tlPos.y();
    }
    if(brPos.x() > bottomRight.x())
    {
      bottomRight.x() = brPos.x();
    }
    if(brPos.y() > bottomRight.y())
    {
      bottomRight.y() = brPos.y();
    }
  }

  mBoundingBox.setPosition(topLeft);
  mBoundingBox.setSize(bottomRight - topLeft);
}



const std::vector<TextVertex>& TextFormatter::getVertices() const
{
  return mVertices;
}



const Rectf& TextFormatter::getBoundingBox() const
{
  return mBoundingBox;
}

}  // namespace



FormattedText::FormattedText(const std::string& text, const Font& font)
  : FormattedText(text, font, TextBoxFormattingParams::Default)
{}



FormattedText::FormattedText(const std::u32string& text, const Font& font)
  : FormattedText(text, font, TextBoxFormattingParams::Default)
{}



FormattedText::FormattedText(const std::string& text, const Font& font,
  const TextBoxFormattingParams& tbfp)
  : FormattedText(convertEncoding<Utf8, Utf32>(text), font, tbfp)
{}



FormattedText::FormattedText(
  std::u32string text, const Font& font, const TextBoxFormattingParams& tbfp)
  : NonCopyable()
  , mAtlas(nullptr)
  , mMesh(nullptr)
  , mBoundingBox()
  , mTransform()
{
  GlyphCache glyphCache(text, font);
  GlyphAtlas glyphAtlas(glyphCache);
  TextFormatter formatter(text, font, glyphCache, glyphAtlas, tbfp);

  mAtlas = std::make_unique<Texture2Array>(
    glyphAtlas.getImage(), TextureFormat::R, 1u);
  mAtlas->setChannelMapping(TextureChannelMapping::Alpha);
  mMesh = std::make_unique<TextMesh>(
    MeshDrawMode::Triangles, MeshFillMode::Fill, formatter.getVertices());
  mBoundingBox = formatter.getBoundingBox();
}



FormattedText::FormattedText(FormattedText&& other)
  : NonCopyable()
  , mAtlas(std::move(other.mAtlas))
  , mMesh(std::move(other.mMesh))
  , mBoundingBox(std::move(other.mBoundingBox))
  , mTransform(std::move(other.mTransform))
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



const Rectf& FormattedText::getBoundingBox() const
{
  return mBoundingBox;
}



const Trans2f& FormattedText::getTransform() const
{
  return mTransform;
}

}  // namespace hou
