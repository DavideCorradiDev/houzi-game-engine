#include "hou/gfx/formatted_text.hpp"

#include "hou/cor/span.hpp"

#include "hou/gfx/font.hpp"
#include "hou/gfx/glyph.hpp"
#include "hou/gfx/texture_channel_mapping.hpp"

#include <map>
#include <set>



namespace hou
{

namespace
{

class GlyphCache
{
public:
  GlyphCache(const span<const utf32::code_unit>& characters, const font& ph_font);

  const std::map<utf32::code_unit, glyph>& getGlyphs() const;
  const glyph& get_glyph(utf32::code_unit c) const;
  const vec2u& getMaxGlyphSize() const;
  uint get_size() const;

private:
  std::map<utf32::code_unit, glyph> mGlyphs;
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

  const image3R& get_image() const;
  const AtlasGlyphCoordinates& getAtlasGlyphCoordinates(
    utf32::code_unit c) const;

private:
  static vec3u computeAtlasGridSize(const GlyphCache& cache);

private:
  vec3u mAtlasGridSize;
  image3R m_image;
  std::map<utf32::code_unit, AtlasGlyphCoordinates> mGlyphCoords;
};



class TextFormatter
{
public:
  TextFormatter(std::u32string text, const font&, const GlyphCache& cache,
    const GlyphAtlas& atlas, const text_box_formatting_params params);

  const std::vector<text_vertex>& getVertices() const;
  const rectf& get_bounding_box() const;

private:
  static constexpr uint VerticesPerGlyph = 6u;
  static constexpr utf32::code_unit LineFeed = 0x0000000A;
  static constexpr utf32::code_unit WhiteSpace = 0x00000020;

private:
  float computeGlyphAdvance(const glyph_metrics& gm, const font& ph_font) const;
  vec2f computeGlyphBearing(const glyph_metrics& gm, const font& ph_font) const;
  void insertLineBreaks(const font& ph_font, const GlyphCache& cache,
    const text_box_formatting_params& tbfp);
  void generateVertices(
    const font& ph_font, const GlyphCache& cache, const GlyphAtlas& atlas);
  void computeBoundingBox();

private:
  std::u32string m_text;
  std::vector<text_vertex> mVertices;
  size_t mLineCoord;
  size_t mColumnCoord;
  float mLineSpacing;
  float mCharSpacingFactor;
  rectf m_bounding_box;
};



GlyphCache::GlyphCache(
  const span<const utf32::code_unit>& characters, const font& ph_font)
  : mGlyphs()
  , mMaxGlyphSize()
{
  for(auto c : characters)
  {
    if(mGlyphs.count(c) == 0u)
    {
      auto inserted = mGlyphs.insert(std::make_pair(c, ph_font.get_glyph(c)));
      HOU_EXPECT_DEV(inserted.second);
      const vec2u& glyphSize = inserted.first->second.get_image().get_size();
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



const std::map<utf32::code_unit, glyph>& GlyphCache::getGlyphs() const
{
  return mGlyphs;
}



const glyph& GlyphCache::get_glyph(utf32::code_unit c) const
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
    std::min(2048u, static_cast<uint>(gl::get_max_texture_size())),
    std::min(2048u, static_cast<uint>(gl::get_max_texture_size())),
    std::min(256u, static_cast<uint>(gl::get_max_texture_layers())));

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
  , m_image(vec3u(mAtlasGridSize.x() * cache.getMaxGlyphSize().x(),
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
    m_image.set_sub_image(glyphPosition, kv.second.get_image());
    mGlyphCoords.insert(std::make_pair(kv.first,
      AtlasGlyphCoordinates(
        glyphPosition, kv.second.get_image().get_size(), m_image.get_size())));
    ++idx;
  }
}



const image3R& GlyphAtlas::get_image() const
{
  return m_image;
}



const AtlasGlyphCoordinates& GlyphAtlas::getAtlasGlyphCoordinates(
  utf32::code_unit c) const
{
  return mGlyphCoords.at(c);
}



TextFormatter::TextFormatter(std::u32string text, const font& ph_font,
  const GlyphCache& cache, const GlyphAtlas& atlas,
  const text_box_formatting_params tbfp)
  : m_text(text)
  , mVertices(VerticesPerGlyph * text.size(), text_vertex())
  , mLineCoord((tbfp.get_text_flow() == text_flow::LeftRight
                 || tbfp.get_text_flow() == text_flow::RightLeft)
        ? 0u
        : 1u)
  , mColumnCoord(mLineCoord == 0u ? 1u : 0u)
  , mLineSpacing(mLineCoord == 0u ? ph_font.get_pixel_line_spacing()
                                  : 0.5f * ph_font.get_pixel_max_advance())
  , mCharSpacingFactor(tbfp.get_text_flow() == text_flow::LeftRight
          || tbfp.get_text_flow() == text_flow::TopBottom
        ? 1.f
        : -1.f)
  , m_bounding_box()
{
  insertLineBreaks(ph_font, cache, tbfp);
  generateVertices(ph_font, cache, atlas);
  computeBoundingBox();
}



float TextFormatter::computeGlyphAdvance(
  const glyph_metrics& gm, const font& ph_font) const
{
  return mCharSpacingFactor
    * (mLineCoord == 0u ? gm.get_pixel_horizontal_advance()
                        : (ph_font.has_vertical() ? gm.get_pixel_vertical_advance()
                                              : gm.get_pixel_size().y() * 1.5f));
}



vec2f TextFormatter::computeGlyphBearing(
  const glyph_metrics& gm, const font& ph_font) const
{
  vec2f vertBearing = ph_font.has_vertical()
    ? gm.get_pixel_vertical_bearing()
    : vec2f(-0.5f * gm.get_pixel_size().x(), 0.f);

  const vec2f& bearing
    = mLineCoord == 0 ? gm.get_pixel_horizontal_bearing() : vertBearing;

  return bearing;
}



void TextFormatter::insertLineBreaks(const font& ph_font, const GlyphCache& cache,
  const text_box_formatting_params& tbfp)
{
  // This function wraps text inside the bounding box.
  // The algorithm should be improved to be consistent with common typographic
  // rules.
  if(tbfp.get_max_size().x() <= 0.f || tbfp.get_max_size().y() <= 0.f)
  {
    return;
  }

  const float maxLineSize = tbfp.get_max_size()(mLineCoord);
  const float maxColumnSize = tbfp.get_max_size()(mColumnCoord);

  float lineSize = 0.f;
  float columnSize = mLineSpacing;
  size_t pos = 0;
  size_t newlinepos = m_text.find_first_of(LineFeed);
  while(pos < m_text.size())
  {
    // If the new line makes the m_text box overflow, delete the rest of the
    // string.
    if(columnSize > maxColumnSize)
    {
      m_text.erase(pos);
      break;
    }

    size_t wordStart = pos < m_text.size()
      ? std::min(m_text.find_first_not_of(WhiteSpace, pos), newlinepos)
      : m_text.size();
    size_t wordEnd = wordStart < m_text.size()
      ? std::min(m_text.find_first_of(WhiteSpace, wordStart), newlinepos)
      : m_text.size();

    // Compute the size of the next word.
    float wordSize = 0.f;
    for(size_t i = pos; i < wordEnd; ++i)
    {
      HOU_ENSURE_DEV(i < m_text.size());
      wordSize += std::fabs(
        computeGlyphAdvance(cache.get_glyph(m_text[i]).get_metrics(), ph_font));
    }

    // If the first word is a space, remove it for size computations.
    float wordSizeAdjustment = 0.f;
    if(m_text[pos] == WhiteSpace)
    {
      wordSizeAdjustment = std::fabs(
        computeGlyphAdvance(cache.get_glyph(WhiteSpace).get_metrics(), ph_font));
    }

    // If the word can't possibly fit on any line.
    // The rest of the string need not be rendered.
    if((wordSize - wordSizeAdjustment) > maxLineSize)
    {
      m_text.erase(pos);
      break;
    }

    // If the word doesn't fit on this line Add a line break in place of the
    // first space.
    lineSize += wordSize;
    if(lineSize > maxLineSize)
    {
      m_text[pos] = '\n';
      columnSize += mLineSpacing;
      lineSize = wordSize - wordSizeAdjustment;
    }

    // If the new line makes the m_text box overflow, delete the rest of the
    // string.
    if(columnSize > maxColumnSize)
    {
      m_text.erase(pos);
      break;
    }

    // If new line character, start a new line.
    pos = wordEnd;
    if(m_text[wordEnd] == LineFeed)
    {
      newlinepos = wordEnd + 1 < m_text.size()
        ? m_text.find_first_of(LineFeed, wordEnd + 1)
        : m_text.size();
      columnSize += mLineSpacing;
      lineSize = 0.f;
    }
  }
}



void TextFormatter::generateVertices(
  const font& ph_font, const GlyphCache& cache, const GlyphAtlas& atlas)
{
  vec2f penPos(0.f, 0.f);
  for(size_t i = 0; i < m_text.size(); ++i)
  {
    utf32::code_unit c = m_text[i];
    if(c == LineFeed)
    {
      penPos(mLineCoord) = 0.f;
      penPos(mColumnCoord) += mLineSpacing;
    }
    else
    {
      const glyph_metrics& gm = cache.get_glyph(c).get_metrics();
      const AtlasGlyphCoordinates& ac = atlas.getAtlasGlyphCoordinates(c);

      float advance = computeGlyphAdvance(gm, ph_font);

      if(advance < 0.f)
      {
        penPos(mLineCoord) += advance;
      }

      vec2f bearing = computeGlyphBearing(gm, ph_font);

      vec2f v0Pos = penPos + bearing + ac.getTopLeftPos();
      vec3f v0Tex = ac.getTopLeftTex();
      text_vertex v0(v0Pos, v0Tex);

      vec2f v1Pos = v0Pos + ac.getTopRightPos();
      vec3f v1Tex = ac.getTopRightTex();
      text_vertex v1(v1Pos, v1Tex);

      vec2f v2Pos = v0Pos + ac.getBottomLeftPos();
      vec3f v2Tex = ac.getBottomLeftTex();
      text_vertex v2(v2Pos, v2Tex);

      vec2f v3Pos = v0Pos + ac.getBottomRightPos();
      vec3f v3Tex = ac.getBottomRightTex();
      text_vertex v3(v3Pos, v3Tex);

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

  m_bounding_box.set_position(topLeft);
  m_bounding_box.set_size(bottomRight - topLeft);
}



const std::vector<text_vertex>& TextFormatter::getVertices() const
{
  return mVertices;
}



const rectf& TextFormatter::get_bounding_box() const
{
  return m_bounding_box;
}

}  // namespace



formatted_text::formatted_text(const std::string& text, const font& ph_font,
  const text_box_formatting_params& tbfp)
  : formatted_text(convert_encoding<utf8, utf32>(text), ph_font, tbfp)
{}



formatted_text::formatted_text(
  std::u32string text, const font& ph_font, const text_box_formatting_params& tbfp)
  : non_copyable()
  , m_atlas(nullptr)
  , m_mesh(nullptr)
  , m_bounding_box()
{
  GlyphCache glyphCache(text, ph_font);
  GlyphAtlas glyphAtlas(glyphCache);
  TextFormatter formatter(text, ph_font, glyphCache, glyphAtlas, tbfp);

  m_atlas = std::make_unique<texture2_array>(
    glyphAtlas.get_image(), texture_format::r, 1u);
  m_atlas->setChannelMapping(texture_channel_mapping::alpha);
  m_mesh = std::make_unique<text_mesh>(
    mesh_draw_mode::triangles, mesh_fill_mode::fill, formatter.getVertices());
  m_bounding_box = formatter.get_bounding_box();
}



formatted_text::formatted_text(formatted_text&& other)
  : non_copyable()
  , m_atlas(std::move(other.m_atlas))
  , m_mesh(std::move(other.m_mesh))
  , m_bounding_box(std::move(other.m_bounding_box))
{}



const texture2_array& formatted_text::get_atlas() const
{
  HOU_EXPECT_DEV(m_atlas != nullptr);
  return *m_atlas;
}



const text_mesh& formatted_text::get_mesh() const
{
  HOU_EXPECT_DEV(m_mesh != nullptr);
  return *m_mesh;
}



const rectf& formatted_text::get_bounding_box() const
{
  return m_bounding_box;
}

}  // namespace hou
