#include "hou/gfx/formatted_text.hpp"

#include "hou/cor/narrow_cast.hpp"
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

class glyph_cache
{
public:
  glyph_cache(const span<const utf32::code_unit>& characters, const font& f);

  const std::map<utf32::code_unit, glyph>& get_glyphs() const;
  const glyph& get_glyph(utf32::code_unit c) const;
  const vec2u& get_max_glyph_size() const;
  uint get_size() const;

private:
  std::map<utf32::code_unit, glyph> m_glyphs;
  vec2u m_max_glyph_size;
};


class atlas_glyph_coordinates
{
public:
  atlas_glyph_coordinates(
    const vec3u& pos, const vec2u& size, const vec3u& tex_size);

  vec2f get_top_left_pos() const;
  vec2f get_top_right_pos() const;
  vec2f get_bottom_right_pos() const;
  vec2f get_bottom_left_pos() const;
  vec3f get_top_left_tex() const;
  vec3f get_top_right_tex() const;
  vec3f get_bottom_right_tex() const;
  vec3f get_bottom_left_tex() const;

private:
  vec3f m_pos;
  vec2f m_size;
  vec3f m_tex_size;
};



class glyph_atlas
{
public:
  glyph_atlas(const glyph_cache& cache);

  const image3_r& get_image() const;
  const atlas_glyph_coordinates& get_atlas_glyph_coordinates(
    utf32::code_unit c) const;

private:
  static vec3u compute_atlas_grid_size(const glyph_cache& cache);

private:
  vec3u m_atlas_grid_size;
  image3_r m_image;
  std::map<utf32::code_unit, atlas_glyph_coordinates> m_glyph_coords;
};



class text_formatter
{
public:
  text_formatter(std::u32string text, const font&, const glyph_cache& cache,
    const glyph_atlas& atlas, const text_box_formatting_params params);

  const std::vector<text_vertex>& get_vertices() const;
  const rectf& get_bounding_box() const;

private:
  static constexpr uint s_vertices_per_glyph = 6u;
  static constexpr utf32::code_unit s_line_feed = 0x0000000A;
  static constexpr utf32::code_unit s_whitespace = 0x00000020;

private:
  float compute_glyph_advance(const glyph_metrics& gm, const font& f) const;
  vec2f compute_glyph_bearing(const glyph_metrics& gm, const font& f) const;
  void insert_line_breaks(const font& f, const glyph_cache& cache,
    const text_box_formatting_params& tbfp);
  void generate_vertices(
    const font& f, const glyph_cache& cache, const glyph_atlas& atlas);
  void compute_bounding_box();

private:
  std::u32string m_text;
  std::vector<text_vertex> m_vertices;
  size_t m_line_coord;
  size_t m_column_coord;
  float m_line_spacing;
  float m_char_spacing_factor;
  rectf m_bounding_box;
};



glyph_cache::glyph_cache(
  const span<const utf32::code_unit>& characters, const font& f)
  : m_glyphs()
  , m_max_glyph_size()
{
  for(auto c : characters)
  {
    if(m_glyphs.count(c) == 0u)
    {
      auto inserted = m_glyphs.insert(std::make_pair(c, f.get_glyph(c)));
      HOU_DEV_ASSERT(inserted.second);
      const vec2u& glyph_size = inserted.first->second.get_image().get_size();
      for(size_t i = 0; i < vec2u::size(); ++i)
      {
        if(glyph_size(i) > m_max_glyph_size(i))
        {
          m_max_glyph_size(i) = glyph_size(i);
        }
      }
    }
  }
}



const std::map<utf32::code_unit, glyph>& glyph_cache::get_glyphs() const
{
  return m_glyphs;
}



const glyph& glyph_cache::get_glyph(utf32::code_unit c) const
{
  return m_glyphs.at(c);
}



const vec2u& glyph_cache::get_max_glyph_size() const
{
  return m_max_glyph_size;
}



vec3u glyph_atlas::compute_atlas_grid_size(const glyph_cache& cache)
{
  static const vec3u max_atlas_size(
    std::min(2048u, texture2_array::get_max_size().x()),
    std::min(2048u, texture2_array::get_max_size().y()),
    std::min(256u, texture2_array::get_max_size().z()));

  vec3u maxAtlasGridSize = max_atlas_size;
  maxAtlasGridSize.x() /= cache.get_max_glyph_size().x();
  maxAtlasGridSize.y() /= cache.get_max_glyph_size().y();

  uint char_count = cache.get_size();
  return vec3u(std::min(char_count, maxAtlasGridSize.x()),
    std::min(char_count / maxAtlasGridSize.x(), maxAtlasGridSize.y() - 1u) + 1u,
    std::min(char_count / (maxAtlasGridSize.x() * maxAtlasGridSize.y()),
      maxAtlasGridSize.z() - 1u)
      + 1u);
}



atlas_glyph_coordinates::atlas_glyph_coordinates(
  const vec3u& pos, const vec2u& size, const vec3u& tex_size)
  : m_pos(narrow_cast<vec3f>(pos))
  , m_size(narrow_cast<vec2f>(size))
  , m_tex_size(narrow_cast<vec3f>(tex_size))
{}



vec2f atlas_glyph_coordinates::get_top_left_pos() const
{
  return vec2f();
}



vec2f atlas_glyph_coordinates::get_top_right_pos() const
{
  return vec2f(m_size.x(), 0.f);
}



vec2f atlas_glyph_coordinates::get_bottom_right_pos() const
{
  return vec2f(m_size.x(), m_size.y());
}



vec2f atlas_glyph_coordinates::get_bottom_left_pos() const
{
  return vec2f(0.f, m_size.y());
}



vec3f atlas_glyph_coordinates::get_top_left_tex() const
{
  return vec3f(
    m_pos.x() / m_tex_size.x(), m_pos.y() / m_tex_size.y(), m_pos.z());
  ;
}



vec3f atlas_glyph_coordinates::get_top_right_tex() const
{
  return vec3f((m_pos.x() + m_size.x()) / m_tex_size.x(),
    m_pos.y() / m_tex_size.y(), m_pos.z());
}



vec3f atlas_glyph_coordinates::get_bottom_right_tex() const
{
  return vec3f((m_pos.x() + m_size.x()) / m_tex_size.x(),
    (m_pos.y() + m_size.y()) / m_tex_size.y(), m_pos.z());
}



vec3f atlas_glyph_coordinates::get_bottom_left_tex() const
{
  return vec3f(m_pos.x() / m_tex_size.x(),
    (m_pos.y() + m_size.y()) / m_tex_size.y(), m_pos.z());
}



uint glyph_cache::get_size() const
{
  return m_glyphs.size();
}



glyph_atlas::glyph_atlas(const glyph_cache& cache)
  : m_atlas_grid_size(compute_atlas_grid_size(cache))
  , m_image(vec3u(m_atlas_grid_size.x() * cache.get_max_glyph_size().x(),
      m_atlas_grid_size.y() * cache.get_max_glyph_size().y(),
      m_atlas_grid_size.z()))
  , m_glyph_coords()
{
  uint atlas_grid_layer_size = m_atlas_grid_size.x() * m_atlas_grid_size.y();
  uint idx = 0;
  for(const auto& kv : cache.get_glyphs())
  {
    vec3u glyph_position(idx % atlas_grid_layer_size % m_atlas_grid_size.x()
        * cache.get_max_glyph_size().x(),
      idx % atlas_grid_layer_size / m_atlas_grid_size.x()
        * cache.get_max_glyph_size().y(),
      idx / atlas_grid_layer_size);
    m_image.set_sub_image(glyph_position, kv.second.get_image());
    m_glyph_coords.insert(std::make_pair(kv.first,
      atlas_glyph_coordinates(
        glyph_position, kv.second.get_image().get_size(), m_image.get_size())));
    ++idx;
  }
}



const image3_r& glyph_atlas::get_image() const
{
  return m_image;
}



const atlas_glyph_coordinates& glyph_atlas::get_atlas_glyph_coordinates(
  utf32::code_unit c) const
{
  return m_glyph_coords.at(c);
}



text_formatter::text_formatter(std::u32string text, const font& f,
  const glyph_cache& cache, const glyph_atlas& atlas,
  const text_box_formatting_params tbfp)
  : m_text(text)
  , m_vertices(s_vertices_per_glyph * text.size(), text_vertex())
  , m_line_coord((tbfp.get_text_flow() == text_flow::left_right
                   || tbfp.get_text_flow() == text_flow::right_left)
        ? 0u
        : 1u)
  , m_column_coord(m_line_coord == 0u ? 1u : 0u)
  , m_line_spacing(m_line_coord == 0u ? f.get_pixel_line_spacing()
                                      : 0.5f * f.get_pixel_max_advance())
  , m_char_spacing_factor(tbfp.get_text_flow() == text_flow::left_right
          || tbfp.get_text_flow() == text_flow::top_bottom
        ? 1.f
        : -1.f)
  , m_bounding_box()
{
  insert_line_breaks(f, cache, tbfp);
  generate_vertices(f, cache, atlas);
  compute_bounding_box();
}



float text_formatter::compute_glyph_advance(
  const glyph_metrics& gm, const font& f) const
{
  return m_char_spacing_factor
    * (m_line_coord == 0u
          ? gm.get_pixel_horizontal_advance()
          : (f.has_vertical() ? gm.get_pixel_vertical_advance()
                              : gm.get_pixel_size().y() * 1.5f));
}



vec2f text_formatter::compute_glyph_bearing(
  const glyph_metrics& gm, const font& f) const
{
  vec2f vert_bearing = f.has_vertical()
    ? gm.get_pixel_vertical_bearing()
    : vec2f(-0.5f * gm.get_pixel_size().x(), 0.f);

  const vec2f& bearing
    = m_line_coord == 0 ? gm.get_pixel_horizontal_bearing() : vert_bearing;

  return bearing;
}



void text_formatter::insert_line_breaks(const font& f, const glyph_cache& cache,
  const text_box_formatting_params& tbfp)
{
  // This function wraps text inside the bounding box.
  // The algorithm should be improved to be consistent with common typographic
  // rules.
  if(tbfp.get_max_size().x() <= 0.f || tbfp.get_max_size().y() <= 0.f)
  {
    return;
  }

  const float max_line_size = tbfp.get_max_size()(m_line_coord);
  const float max_column_size = tbfp.get_max_size()(m_column_coord);

  float line_size = 0.f;
  float column_size = m_line_spacing;
  size_t pos = 0;
  size_t new_line_pos = m_text.find_first_of(s_line_feed);
  while(pos < m_text.size())
  {
    // If the new line makes the m_text box overflow, delete the rest of the
    // string.
    if(column_size > max_column_size)
    {
      m_text.erase(pos);
      break;
    }

    size_t wordStart = pos < m_text.size()
      ? std::min(m_text.find_first_not_of(s_whitespace, pos), new_line_pos)
      : m_text.size();
    size_t word_end = wordStart < m_text.size()
      ? std::min(m_text.find_first_of(s_whitespace, wordStart), new_line_pos)
      : m_text.size();

    // Compute the size of the next word.
    float word_size = 0.f;
    for(size_t i = pos; i < word_end; ++i)
    {
      HOU_DEV_ASSERT(i < m_text.size());
      word_size += std::fabs(
        compute_glyph_advance(cache.get_glyph(m_text[i]).get_metrics(), f));
    }

    // If the first word is a space, remove it for size computations.
    float word_size_adjustment = 0.f;
    if(m_text[pos] == s_whitespace)
    {
      word_size_adjustment = std::fabs(
        compute_glyph_advance(cache.get_glyph(s_whitespace).get_metrics(), f));
    }

    // If the word can't possibly fit on any line.
    // The rest of the string need not be rendered.
    if((word_size - word_size_adjustment) > max_line_size)
    {
      m_text.erase(pos);
      break;
    }

    // If the word doesn't fit on this line Add a line break in place of the
    // first space.
    line_size += word_size;
    if(line_size > max_line_size)
    {
      m_text[pos] = '\n';
      column_size += m_line_spacing;
      line_size = word_size - word_size_adjustment;
    }

    // If the new line makes the m_text box overflow, delete the rest of the
    // string.
    if(column_size > max_column_size)
    {
      m_text.erase(pos);
      break;
    }

    // If new line character, start a new line.
    pos = word_end;
    if(m_text[word_end] == s_line_feed)
    {
      new_line_pos = word_end + 1 < m_text.size()
        ? m_text.find_first_of(s_line_feed, word_end + 1)
        : m_text.size();
      column_size += m_line_spacing;
      line_size = 0.f;
    }
  }
}



void text_formatter::generate_vertices(
  const font& f, const glyph_cache& cache, const glyph_atlas& atlas)
{
  vec2f pen_pos(0.f, 0.f);
  for(size_t i = 0; i < m_text.size(); ++i)
  {
    utf32::code_unit c = m_text[i];
    if(c == s_line_feed)
    {
      pen_pos(m_line_coord) = 0.f;
      pen_pos(m_column_coord) += m_line_spacing;
    }
    else
    {
      const glyph_metrics& gm = cache.get_glyph(c).get_metrics();
      const atlas_glyph_coordinates& ac = atlas.get_atlas_glyph_coordinates(c);

      float advance = compute_glyph_advance(gm, f);

      if(advance < 0.f)
      {
        pen_pos(m_line_coord) += advance;
      }

      vec2f bearing = compute_glyph_bearing(gm, f);

      vec2f v0_pos = pen_pos + bearing + ac.get_top_left_pos();
      vec3f v0_tex = ac.get_top_left_tex();
      text_vertex v0(v0_pos, v0_tex);

      vec2f v1_pos = v0_pos + ac.get_top_right_pos();
      vec3f v1_tex = ac.get_top_right_tex();
      text_vertex v1(v1_pos, v1_tex);

      vec2f v2_pos = v0_pos + ac.get_bottom_left_pos();
      vec3f v2_tex = ac.get_bottom_left_tex();
      text_vertex v2(v2_pos, v2_tex);

      vec2f v3_pos = v0_pos + ac.get_bottom_right_pos();
      vec3f v3_tex = ac.get_bottom_right_tex();
      text_vertex v3(v3_pos, v3_tex);

      m_vertices[i * 6 + 0] = v0;
      m_vertices[i * 6 + 1] = v1;
      m_vertices[i * 6 + 2] = v2;
      m_vertices[i * 6 + 3] = v2;
      m_vertices[i * 6 + 4] = v1;
      m_vertices[i * 6 + 5] = v3;

      if(advance > 0.f)
      {
        pen_pos(m_line_coord) += advance;
      }
    }
  }
}


void text_formatter::compute_bounding_box()
{
  if(m_vertices.empty())
  {
    return;
  }

  static constexpr size_t tl_offset = 0u;
  static constexpr size_t br_offset = 5u;

  vec2f top_left = m_vertices[tl_offset].get_position();
  vec2f bottom_right = m_vertices[br_offset].get_position();

  for(size_t i = s_vertices_per_glyph; i < m_vertices.size();
      i += s_vertices_per_glyph)
  {
    const vec2f& tl_pos = m_vertices[i + tl_offset].get_position();
    const vec2f& br_pos = m_vertices[i + br_offset].get_position();
    if(tl_pos.x() < top_left.x())
    {
      top_left.x() = tl_pos.x();
    }
    if(tl_pos.y() < top_left.y())
    {
      top_left.y() = tl_pos.y();
    }
    if(br_pos.x() > bottom_right.x())
    {
      bottom_right.x() = br_pos.x();
    }
    if(br_pos.y() > bottom_right.y())
    {
      bottom_right.y() = br_pos.y();
    }
  }

  m_bounding_box.set_position(top_left);
  m_bounding_box.set_size(bottom_right - top_left);
}



const std::vector<text_vertex>& text_formatter::get_vertices() const
{
  return m_vertices;
}



const rectf& text_formatter::get_bounding_box() const
{
  return m_bounding_box;
}

}  // namespace



formatted_text::formatted_text(const std::string& text, const font& f,
  const text_box_formatting_params& tbfp)
  : formatted_text(convert_encoding<utf32, utf8>(text), f, tbfp)
{}



formatted_text::formatted_text(
  std::u32string text, const font& f, const text_box_formatting_params& tbfp)
  : non_copyable()
  , m_atlas(nullptr)
  , m_mesh(nullptr)
  , m_bounding_box()
{
  glyph_cache gc(text, f);
  glyph_atlas ga(gc);
  text_formatter formatter(text, f, gc, ga, tbfp);

  m_atlas
    = std::make_unique<texture2_array>(ga.get_image(), texture_format::r, 1u);
  m_atlas->setChannelMapping(texture_channel_mapping::alpha);
  m_mesh = std::make_unique<text_mesh>(
    mesh_draw_mode::triangles, mesh_fill_mode::fill, formatter.get_vertices());
  m_bounding_box = formatter.get_bounding_box();
}



const texture2_array& formatted_text::get_atlas() const
{
  HOU_DEV_ASSERT(m_atlas != nullptr);
  return *m_atlas;
}



const text_mesh& formatted_text::get_mesh() const
{
  HOU_DEV_ASSERT(m_mesh != nullptr);
  return *m_mesh;
}



const rectf& formatted_text::get_bounding_box() const
{
  return m_bounding_box;
}

}  // namespace hou
