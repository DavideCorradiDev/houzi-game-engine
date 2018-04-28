#include "hou/gfx/FormattedText.hpp"

#include "hou/cor/span.hpp"

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
  GlyphCache(const span<const utf32::code_unit>& characters, const Font& font);

  const std::map<utf32::code_unit, Glyph>& getGlyphs() const;
  const Glyph& getGlyph(utf32::code_unit c) const;
  const vec2u& getMaxGlyphSize() const;
  uint get_size() const;

private:
  std::map<utf32::code_unit, Glyph> mGlyphs;
  vec2u mMaxGlyphSize;
};


class AtlasGlyphCoordinates
{
public:
  AtlasGlyphCoordinates(
    const vec3u& pos, const vec2u& size, const vec3u& texSize);

  vec2f getTopLeftPos() const;
  vec2f getTopRightPos() const;
  vec2f getBottomRightPos() const;
  vec2f getBottomLeftPos() const;
  vec3f getTopLeftTex() const;
  vec3f getTopRightTex() const;
  vec3f getBottomRightTex() const;
  vec3f getBottomLeftTex() const;

private:
  vec3f mPos;
  vec2f m_size;
  vec3f mTexSize;
};



class GlyphAtlas
{
public:
  GlyphAtlas(const GlyphCache& cache);

  const Image3R& getImage() const;
  const AtlasGlyphCoordinates& getAtlasGlyphCoordinates(
    utf32::code_unit c) const;

private:
  static vec3u computeAtlasGridSize(const GlyphCache& cache);

private:
  vec3u mAtlasGridSize;
  Image3R mImage;
  std::map<utf32::code_unit, AtlasGlyphCoordinates> mGlyphCoords;
};



class TextFormatter
{
public:
  TextFormatter(std::u32string text, const Font&, const GlyphCache& cache,
    const GlyphAtlas& atlas, const TextBoxFormattingParams params);

  const std::vector<TextVertex>& getVertices() const;
  const rectf& getBoundingBox() const;

private:
  static constexpr uint VerticesPerGlyph = 6u;
  static constexpr utf32::code_unit LineFeed = 0x0000000A;
  static constexpr utf32::code_unit WhiteSpace = 0x00000020;

private:
  float computeGlyphAdvance(const GlyphMetrics& gm, const Font& font) const;
  vec2f computeGlyphBearing(const GlyphMetrics& gm, const Font& font) const;
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
  rectf mBoundingBox;
};



GlyphCache::GlyphCache(
  const span<const utf32::code_unit>& characters, const Font& font)
  : mGlyphs()
  , mMaxGlyphSize()
{
  for(auto c : characters)
  {
    if(mGlyphs.count(c) == 0u)
    {
      auto inserted = mGlyphs.insert(std::make_pair(c, font.getGlyph(c)));
      HOU_EXPECT_DEV(inserted.second);
      const vec2u& glyphSize = inserted.first->second.getImage().get_size();
      for(size_t i = 0; i < vec2u::get_size(); ++i)
      {
        if(glyphSize(i) > mMaxGlyphSize(i))
        {
          mMaxGlyphSize(i) = glyphSize(i);
        }
      }
    }
  }
}



const std::map<utf32::code_unit, Glyph>& GlyphCache::getGlyphs() const
{
  return mGlyphs;
}



const Glyph& GlyphCache::getGlyph(utf32::code_unit c) const
{
  return mGlyphs.at(c);
}



const vec2u& GlyphCache::getMaxGlyphSize() const
{
  return mMaxGlyphSize;
}



vec3u GlyphAtlas::computeAtlasGridSize(const GlyphCache& cache)
{
  static const vec3u maxAtlasSize(
    std::min(2048u, static_cast<uint>(gl::getMaxTextureSize())),
    std::min(2048u, static_cast<uint>(gl::getMaxTextureSize())),
    std::min(256u, static_cast<uint>(gl::getMaxTextureLayers())));

  vec3u maxAtlasGridSize = maxAtlasSize;
  maxAtlasGridSize.x() /= cache.getMaxGlyphSize().x();
  maxAtlasGridSize.y() /= cache.getMaxGlyphSize().y();

  uint charCount = cache.get_size();
  return vec3u(std::min(charCount, maxAtlasGridSize.x()),
    std::min(charCount / maxAtlasGridSize.x(), maxAtlasGridSize.y() - 1u) + 1u,
    std::min(charCount / (maxAtlasGridSize.x() * maxAtlasGridSize.y()),
      maxAtlasGridSize.z() - 1u)
      + 1u);
}



AtlasGlyphCoordinates::AtlasGlyphCoordinates(
  const vec3u& pos, const vec2u& size, const vec3u& texSize)
  : mPos(static_cast<vec3f>(pos))
  , m_size(static_cast<vec2f>(size))
  , mTexSize(static_cast<vec3f>(texSize))
{}



vec2f AtlasGlyphCoordinates::getTopLeftPos() const
{
  return vec2f();
}



vec2f AtlasGlyphCoordinates::getTopRightPos() const
{
  return vec2f(m_size.x(), 0.f);
}



vec2f AtlasGlyphCoordinates::getBottomRightPos() const
{
  return vec2f(m_size.x(), m_size.y());
}



vec2f AtlasGlyphCoordinates::getBottomLeftPos() const
{
  return vec2f(0.f, m_size.y());
}



vec3f AtlasGlyphCoordinates::getTopLeftTex() const
{
  return vec3f(mPos.x() / mTexSize.x(), mPos.y() / mTexSize.y(), mPos.z());
  ;
}



vec3f AtlasGlyphCoordinates::getTopRightTex() const
{
  return vec3f(
    (mPos.x() + m_size.x()) / mTexSize.x(), mPos.y() / mTexSize.y(), mPos.z());
}



vec3f AtlasGlyphCoordinates::getBottomRightTex() const
{
  return vec3f((mPos.x() + m_size.x()) / mTexSize.x(),
    (mPos.y() + m_size.y()) / mTexSize.y(), mPos.z());
}



vec3f AtlasGlyphCoordinates::getBottomLeftTex() const
{
  return vec3f(
    mPos.x() / mTexSize.x(), (mPos.y() + m_size.y()) / mTexSize.y(), mPos.z());
}



uint GlyphCache::get_size() const
{
  return mGlyphs.size();
}



GlyphAtlas::GlyphAtlas(const GlyphCache& cache)
  : mAtlasGridSize(computeAtlasGridSize(cache))
  , mImage(vec3u(mAtlasGridSize.x() * cache.getMaxGlyphSize().x(),
      mAtlasGridSize.y() * cache.getMaxGlyphSize().y(), mAtlasGridSize.z()))
  , mGlyphCoords()
{
  uint atlasGridLayer = mAtlasGridSize.x() * mAtlasGridSize.y();
  uint idx = 0;
  for(const auto& kv : cache.getGlyphs())
  {
    vec3u glyphPosition(
      idx % atlasGridLayer % mAtlasGridSize.x() * cache.getMaxGlyphSize().x(),
      idx % atlasGridLayer / mAtlasGridSize.x() * cache.getMaxGlyphSize().y(),
      idx / atlasGridLayer);
    mImage.setSubImage(glyphPosition, kv.second.getImage());
    mGlyphCoords.insert(std::make_pair(kv.first,
      AtlasGlyphCoordinates(
        glyphPosition, kv.second.getImage().get_size(), mImage.get_size())));
    ++idx;
  }
}



const Image3R& GlyphAtlas::getImage() const
{
  return mImage;
}



const AtlasGlyphCoordinates& GlyphAtlas::getAtlasGlyphCoordinates(
  utf32::code_unit c) const
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



vec2f TextFormatter::computeGlyphBearing(
  const GlyphMetrics& gm, const Font& font) const
{
  vec2f vertBearing = font.hasVertical()
    ? gm.getPixelVerticalBearing()
    : vec2f(-0.5f * gm.getPixelSize().x(), 0.f);

  const vec2f& bearing
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
  vec2f penPos(0.f, 0.f);
  for(size_t i = 0; i < mText.size(); ++i)
  {
    utf32::code_unit c = mText[i];
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

      vec2f bearing = computeGlyphBearing(gm, font);

      vec2f v0Pos = penPos + bearing + ac.getTopLeftPos();
      vec3f v0Tex = ac.getTopLeftTex();
      TextVertex v0(v0Pos, v0Tex);

      vec2f v1Pos = v0Pos + ac.getTopRightPos();
      vec3f v1Tex = ac.getTopRightTex();
      TextVertex v1(v1Pos, v1Tex);

      vec2f v2Pos = v0Pos + ac.getBottomLeftPos();
      vec3f v2Tex = ac.getBottomLeftTex();
      TextVertex v2(v2Pos, v2Tex);

      vec2f v3Pos = v0Pos + ac.getBottomRightPos();
      vec3f v3Tex = ac.getBottomRightTex();
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

  vec2f topLeft = mVertices[tlOffset].get_position();
  vec2f bottomRight = mVertices[brOffset].get_position();

  for(size_t i = VerticesPerGlyph; i < mVertices.size(); i += VerticesPerGlyph)
  {
    const vec2f& tlPos = mVertices[i + tlOffset].get_position();
    const vec2f& brPos = mVertices[i + brOffset].get_position();
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

  mBoundingBox.set_position(topLeft);
  mBoundingBox.set_size(bottomRight - topLeft);
}



const std::vector<TextVertex>& TextFormatter::getVertices() const
{
  return mVertices;
}



const rectf& TextFormatter::getBoundingBox() const
{
  return mBoundingBox;
}

}  // namespace



FormattedText::FormattedText(const std::string& text, const Font& font,
  const TextBoxFormattingParams& tbfp)
  : FormattedText(convertEncoding<utf8, utf32>(text), font, tbfp)
{}



FormattedText::FormattedText(
  std::u32string text, const Font& font, const TextBoxFormattingParams& tbfp)
  : non_copyable()
  , mAtlas(nullptr)
  , mMesh(nullptr)
  , mBoundingBox()
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
  : non_copyable()
  , mAtlas(std::move(other.mAtlas))
  , mMesh(std::move(other.mMesh))
  , mBoundingBox(std::move(other.mBoundingBox))
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



const rectf& FormattedText::getBoundingBox() const
{
  return mBoundingBox;
}

}  // namespace hou
