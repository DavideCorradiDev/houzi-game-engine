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



FormattedText::FormattedText(const std::u32string& aText, const Font& font,
  const TextBoxFormattingParams& tbfp)
  : NonCopyable()
  , mAtlas(nullptr)
  , mMesh(nullptr)
  , mBoundingBox()
  , mTransform()
{
  std::u32string text = aText;
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
  // Todo: consider other type of space characters and tabs.
  static constexpr Utf32::CodeUnit whitespace = 0x00000020;

  size_t mainCoord = tbfp.getTextFlow() == TextFlow::LeftRight
      || tbfp.getTextFlow() == TextFlow::RightLeft
    ? 0u
    : 1u;
  size_t secCoord = mainCoord == 0u ? 1u : 0u;
  float dirMultiplier = tbfp.getTextFlow() == TextFlow::LeftRight
      || tbfp.getTextFlow() == TextFlow::TopBottom
    ? 1.f
    : -1.f;

  float lineSpacing = font.getPixelLineSpacing();
  std::vector<TextVertex> vertices(6u * text.size(), TextVertex());

  Vec2f penPos(0.f, 0.f);
  if(mainCoord == 0u)
  {
    penPos.y() += lineSpacing;
  }
  else
  {
    // no need for the full line spacing.
    penPos.x() += 0.5f * lineSpacing;
  }
  Vec2f startPos = penPos;

  auto computeAdvance = [&](const GlyphMetrics& gm) {
    return dirMultiplier
      * (mainCoord == 0u ? gm.getPixelHorizontalAdvance()
                         : (font.hasVertical() ? gm.getPixelVerticalAdvance()
                                               : gm.getPixelSize().y() * 1.5f));
  };

  // fit text to max size. Break lines and trim the text where necessary.
  if(tbfp.getMaxSize().x() > 0.f && tbfp.getMaxSize().y() > 0.f)
  {
    float lineSize = 0.f;
    float columnSize = lineSpacing;
    const float maxLineSize = tbfp.getMaxSize()(mainCoord);
    const float maxColumnSize = tbfp.getMaxSize()(secCoord);

    // Vertical space insufficient: no need to do anything..
    if(columnSize > maxColumnSize)
    {
      text.clear();
    }

    size_t pos = 0;
    size_t newlinepos = text.find_first_of(lineFeed);
    while(pos < text.size())
    {
      size_t wordStart = pos < text.size()
        ? std::min(text.find_first_not_of(whitespace, pos), newlinepos)
        : text.size();
      size_t wordEnd = wordStart < text.size()
        ? std::min(text.find_first_of(whitespace, wordStart), newlinepos)
        : text.size();
      float wordSize = 0.f;

      // std::cout << newlinepos << " - " << maxLineSize << " - " << maxColumnSize
      //           << " - " << pos << " - " << wordStart << " - " << wordEnd
      //           << " - " << lineSize << " - " << columnSize << " - '"
      //           << convertEncoding<Utf32, Utf8>(text.substr(pos, wordEnd - pos))
      //           << "'" << std::endl;

      for(size_t i = pos; i < wordEnd; ++i)
      {
        HOU_ENSURE_DEV(i < text.size());
        const GlyphMetrics& gm = charCache.at(text[i]).getMetrics();
        wordSize += dirMultiplier * computeAdvance(gm);
      }

      float adjustment = 0.f;
      if(text[pos] == whitespace)
      {
        adjustment = dirMultiplier * computeAdvance(charCache.at(whitespace).getMetrics());
      }

      // If the word can't possibly fit on any line.
      // The rest of the strnig need not be rendered.
      if((wordSize - adjustment) > maxLineSize)
      {
        text.erase(pos);
        break;
      }

      // If the word doesn't fit on this line.
      // Add a line break in place of the first space.
      lineSize += wordSize;
      if(lineSize > maxLineSize)
      {
        text[pos] = '\n';
        columnSize += lineSpacing;
        lineSize = wordSize - adjustment;
      }

      if(columnSize > maxColumnSize)
      {
        text.erase(pos);
        break;
      }

      pos = wordEnd;

      if(text[wordEnd] == lineFeed)
      {
        columnSize += lineSpacing;
        newlinepos = wordEnd + 1 < text.size()
          ? text.find_first_of(lineFeed, wordEnd + 1)
          : text.size();
        lineSize = 0.f;
      }

      if(columnSize > maxColumnSize)
      {
        text.erase(pos);
        break;
      }
    }
  }

  Vec2f topLeft;
  Vec2f bottomRight;
  for(size_t i = 0; i < text.size(); ++i)
  {
    Utf32::CodeUnit c = text[i];
    if(c == lineFeed)
    {
      penPos(mainCoord) = 0.f;
      penPos(secCoord) += lineSpacing;
    }
    else
    {
      const GlyphMetrics& gm = charCache.at(c).getMetrics();
      const AtlasGlyphCoordinates& ac = atlasCoordinatesCache.at(c);

      float advance = computeAdvance(gm);

      if(advance < 0.f)
      {
        penPos(mainCoord) += advance;
      }

      Vec2f horiBearing = font.hasVertical()
        ? gm.getPixelVerticalBearing()
        : Vec2f(-gm.getPixelSize().x() / 2.f, 0.f);
      const Vec2f& bearing
        = mainCoord == 0 ? gm.getPixelHorizontalBearing() : horiBearing;

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

      vertices[i * 6 + 0] = v0;
      vertices[i * 6 + 1] = v1;
      vertices[i * 6 + 2] = v2;
      vertices[i * 6 + 3] = v2;
      vertices[i * 6 + 4] = v1;
      vertices[i * 6 + 5] = v3;

      // Update bounding box.
      if(v0Pos.x() < topLeft.x())
      {
        topLeft.x() = v0Pos.x();
      }
      if(v0Pos.y() < topLeft.y())
      {
        topLeft.y() = v0Pos.y();
      }
      if(v3Pos.x() > bottomRight.x())
      {
        bottomRight.x() = v3Pos.x();
      }
      if(v3Pos.y() > bottomRight.y())
      {
        bottomRight.y() = v3Pos.y();
      }

      if(advance > 0.f)
      {
        penPos(mainCoord) += advance;
      }
    }
  }

  Vec2f offset;
  switch(tbfp.getTextAnchoring())
  {
  case TextAnchoring::TopLeft:
    offset = topLeft;
    break;
  case TextAnchoring::TopCenter:
    offset.x() = 0.5f * (topLeft.x() + bottomRight.x());
    offset.y() = topLeft.y();
    break;
  case TextAnchoring::TopRight:
    offset.x() = bottomRight.x();
    offset.y() = topLeft.y();
    break;
  case TextAnchoring::CenterLeft:
    offset.x() = topLeft.x();
    offset.y() = 0.5f * (topLeft.y() + bottomRight.y());
    break;
  case TextAnchoring::Center:
    offset.x() = 0.5f * (topLeft.x() + bottomRight.x());
    offset.y() = 0.5f * (topLeft.y() + bottomRight.y());
    break;
  case TextAnchoring::CenterRight:
    offset.x() = bottomRight.x();
    offset.y() = 0.5f * (topLeft.y() + bottomRight.y());
    break;
  case TextAnchoring::BottomLeft:
    offset.x() = topLeft.x();
    offset.y() = bottomRight.y();
    break;
  case TextAnchoring::BottomCenter:
    offset.x() = 0.5f * (topLeft.x() + bottomRight.x());
    offset.y() = bottomRight.y();
    break;
  case TextAnchoring::BottomRight:
    offset = bottomRight;
    break;
  case TextAnchoring::Baseline:
    offset = startPos;
    break;
  }
  for(auto& vertex : vertices)
  {
    vertex.setPosition(vertex.getPosition() - offset);
  }
  mBoundingBox.setPosition(topLeft-offset);
  mBoundingBox.setSize(bottomRight - topLeft);

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
