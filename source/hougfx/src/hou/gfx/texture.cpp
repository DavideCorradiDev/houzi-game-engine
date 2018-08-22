#include "hou/gfx/texture.hpp"

#include "hou/cor/assertions.hpp"

#include "hou/gl/gl_functions.hpp"

#include "hou/mth/math_functions.hpp"

#include <cmath>



namespace hou
{

void texture::bind(const texture& tex, uint tu)
{
  HOU_PRECOND(tu < get_texture_unit_count());
  gl::bind_texture(tex.m_handle, tu);
}



void texture::unbind(uint tu)
{
  HOU_PRECOND(tu < get_texture_unit_count());
  gl::unbind_texture(tu);
}



uint texture::get_texture_unit_count()
{
  return narrow_cast<uint>(gl::get_max_texture_image_units());
}



texture::texture(texture_type type, texture_format format)
  : m_handle(gl::texture_handle::create(static_cast<GLenum>(type)))
  , m_type(type)
  , m_format(format)
{}



texture::~texture()
{}



const gl::texture_handle& texture::get_handle() const noexcept
{
  return m_handle;
}



texture_type texture::get_type() const noexcept
{
  return m_type;
}



texture_format texture::get_format() const noexcept
{
  return m_format;
}



texture_channel_mapping texture::get_channel_mapping() const
{
  return texture_channel_mapping(
    texture_channel(get_texture_swizzle_r(m_handle)),
    texture_channel(get_texture_swizzle_g(m_handle)),
    texture_channel(get_texture_swizzle_b(m_handle)),
    texture_channel(get_texture_swizzle_a(m_handle)));
}



void texture::set_channel_mapping(const texture_channel_mapping& mapping)
{
  set_texture_swizzle_r(m_handle, static_cast<GLenum>(mapping.get_r()));
  set_texture_swizzle_g(m_handle, static_cast<GLenum>(mapping.get_g()));
  set_texture_swizzle_b(m_handle, static_cast<GLenum>(mapping.get_b()));
  set_texture_swizzle_a(m_handle, static_cast<GLenum>(mapping.get_a()));
}



bool texture::is_bound(uint tu) const
{
  HOU_PRECOND(tu < get_texture_unit_count());
  return gl::is_texture_bound(m_handle, tu);
}



texture_filter texture::get_filter_internal() const
{
  switch(gl::get_texture_min_filter(get_handle()))
  {
    case GL_NEAREST_MIPMAP_NEAREST:
      return texture_filter::nearest;
    case GL_NEAREST_MIPMAP_LINEAR:
      return texture_filter::linear;
    case GL_LINEAR_MIPMAP_NEAREST:
      return texture_filter::bilinear;
    case GL_LINEAR_MIPMAP_LINEAR:
      return texture_filter::trilinear;
    default:
      HOU_UNREACHABLE();
      return texture_filter::nearest;
  }
}



void texture::set_filter_internal(texture_filter filter)
{
  switch(filter)
  {
    case texture_filter::nearest:
      set_texture_min_filter(get_handle(), GL_NEAREST_MIPMAP_NEAREST);
      set_texture_mag_filter(get_handle(), GL_NEAREST);
      break;
    case texture_filter::linear:
      set_texture_min_filter(get_handle(), GL_NEAREST_MIPMAP_LINEAR);
      set_texture_mag_filter(get_handle(), GL_NEAREST);
      break;
    case texture_filter::bilinear:
      set_texture_min_filter(get_handle(), GL_LINEAR_MIPMAP_NEAREST);
      set_texture_mag_filter(get_handle(), GL_LINEAR);
      break;
    case texture_filter::trilinear:
      set_texture_min_filter(get_handle(), GL_LINEAR_MIPMAP_LINEAR);
      set_texture_mag_filter(get_handle(), GL_LINEAR);
      break;
    default:
      HOU_UNREACHABLE();
      break;
  }
}



texture2_base::texture2_base(
  texture_type type, const vec2u& size, texture_format format)
  : texture(type, format)
  , m_size(size)
{}



texture2_base::~texture2_base()
{}



const vec2u& texture2_base::get_size() const noexcept
{
  return m_size;
}



size_t texture2_base::get_byte_count() const
{
  return gl::compute_texture_size_bytes(m_size.x(), m_size.y(), 1u,
    gl::get_texture_external_format_for_internal_format(
      static_cast<GLenum>(get_format())));
}



const vec2u& texture2::get_max_size()
{
  static const vec2u max_size(narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_size()));
  return max_size;
}



positive<uint> texture2::get_max_mipmap_level_count(const vec2u& size)
{
  return 1u
    + static_cast<uint>(
        log(static_cast<float>(std::max(size.x(), size.y())), 2));
}



texture2::texture2(const vec2u& size, texture_format format,
  positive<uint> mipmap_level_count, bool)
  : texture2_base(texture_type::texture2, size, format)
  , m_mipmap_level_count(mipmap_level_count)
{
  HOU_PRECOND(size.x() > 0 && size.x() <= get_max_size().x());
  HOU_PRECOND(size.y() > 0 && size.y() <= get_max_size().y());
  HOU_PRECOND(mipmap_level_count <= get_max_mipmap_level_count(size));

  gl::set_texture_storage_2d(get_handle(), mipmap_level_count,
    static_cast<GLenum>(format), size.x(), size.y());
}



texture2::texture2(const pixel_view2& pv, texture_format format,
  positive<uint> mipmap_level_count)
  : texture2(pv.get_size(), format, mipmap_level_count, true)
{
  set_image(pv);
}



texture2::texture2(
  const vec2u& size, texture_format format, positive<uint> mipmap_level_count)
  : texture2(size, format, mipmap_level_count, true)
{
  clear();
}



texture_filter texture2::get_filter() const
{
  return get_filter_internal();
}



void texture2::set_filter(texture_filter filter)
{
  set_filter_internal(filter);
}



positive<uint> texture2::get_mipmap_level_count() const
{
  return m_mipmap_level_count;
}



positive<uint> texture2::get_sample_count() const
{
  return 1u;
}



bool texture2::is_mipmapped() const
{
  return true;
}



bool texture2::is_multisampled() const
{
  return false;
}



texture2::wrap_mode texture2::get_wrap_mode() const
{
  return {texture_wrap_mode(gl::get_texture_wrap_mode_s(get_handle())),
    texture_wrap_mode(gl::get_texture_wrap_mode_t(get_handle()))};
}



void texture2::set_wrap_mode(const wrap_mode& wm)
{
  gl::set_texture_wrap_mode_s(get_handle(), static_cast<GLenum>(wm[0]));
  gl::set_texture_wrap_mode_t(get_handle(), static_cast<GLenum>(wm[1]));
}



std::vector<uint8_t> texture2::get_image() const
{
  return get_sub_image(vec2u::zero(), get_size());
}



std::vector<uint8_t> texture2::get_sub_image(
  const vec2u& offset, const vec2u& size) const
{
  vec2u bounds = offset + size;
  HOU_PRECOND(std::equal(bounds.begin(), bounds.end(), get_size().begin(),
    get_size().end(), std::less_equal<uint>()));

  gl::set_unpack_alignment(1u);
  std::vector<uint8_t> buffer(
    gl::compute_texture_size_bytes(size.x(), size.y(), 1u,
      gl::get_texture_external_format_for_internal_format(
        static_cast<GLenum>(get_format()))),
    0u);

  // clang-format off
  gl::get_texture_sub_image(get_handle(),
    offset.x(), offset.y(), 0,                            // offset
    size.x(), size.y(), 1,                                // size
    0,                                                    // level
    gl::get_texture_external_format_for_internal_format(
      static_cast<GLenum>(get_format())),                 // external format
    gl::get_texture_data_type_for_internal_format(
      static_cast<GLenum>(get_format())),                 // data type
    narrow_cast<GLsizei>(buffer.size()),                  // data size
    buffer.data());                                       // data
  // clang-format on

  return buffer;
}



void texture2::set_image(const pixel_view2& pv)
{
  set_sub_image(vec2u::zero(), pv);
}



void texture2::set_sub_image(const vec2u& offset, const pixel_view2& pv)
{
  HOU_PRECOND(pv.get_bytes_per_pixel() == get_bytes_per_pixel(get_format()));

  vec2u bounds = offset + pv.get_size();
  HOU_PRECOND(std::equal(bounds.begin(), bounds.end(), get_size().begin(),
    get_size().end(), std::less_equal<uint>()));

  // clang-format off
  gl::set_texture_sub_image_2d(get_handle(),
    0,                                                    // level
    offset.x(), offset.y(),                               // offset
    pv.get_size().x(), pv.get_size().y(),                 // size
    gl::get_texture_external_format_for_internal_format(
      static_cast<GLenum>(get_format())),                 // external format
    gl::get_texture_data_type_for_internal_format(
      static_cast<GLenum>(get_format())),                 // data type
    reinterpret_cast<const void*>(pv.get_data()));        // data
  // clang-format on

  gl::generate_mip_map(get_handle());
}



void texture2::clear()
{
  gl::reset_texture_sub_image_2d(get_handle(), 0, 0, 0, get_size().x(),
    get_size().y(), static_cast<GLenum>(get_format()));
  gl::generate_mip_map(get_handle());
}



const vec2u& multisampled_texture2::get_max_size()
{
  static const vec2u max_size(narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_size()));
  return max_size;
}



positive<uint> multisampled_texture2::get_max_sample_count()
{
  return gl::get_max_texture_samples();
}



multisampled_texture2::multisampled_texture2(const vec2u& size,
  texture_format format, positive<uint> sample_count,
  bool fixed_sample_locations)
  : texture2_base(texture_type::multisampled_texture2, size, format)
  , m_sample_count(sample_count)
  , m_fixed_sample_locations(fixed_sample_locations)
{
  HOU_PRECOND(size.x() > 0 && size.x() <= get_max_size().x());
  HOU_PRECOND(size.y() > 0 && size.y() <= get_max_size().y());
  HOU_PRECOND(sample_count <= get_max_sample_count());

  gl::set_texture_storage_2d_multisample(get_handle(), sample_count,
    static_cast<GLenum>(format), size.x(), size.y(), fixed_sample_locations);
}



bool multisampled_texture2::has_fixed_sample_locations() const noexcept
{
  return m_fixed_sample_locations;
}



positive<uint> multisampled_texture2::get_mipmap_level_count() const
{
  return 1u;
}



positive<uint> multisampled_texture2::get_sample_count() const
{
  return m_sample_count;
}



bool multisampled_texture2::is_mipmapped() const
{
  return false;
}



bool multisampled_texture2::is_multisampled() const
{
  return true;
}



texture3_base::texture3_base(
  texture_type type, const vec3u& size, texture_format format)
  : texture(type, format)
  , m_size(size)
{}



texture3_base::~texture3_base()
{}



const vec3u& texture3_base::get_size() const noexcept
{
  return m_size;
}



size_t texture3_base::get_byte_count() const
{
  return gl::compute_texture_size_bytes(m_size.x(), m_size.y(), m_size.z(),
    gl::get_texture_external_format_for_internal_format(
      static_cast<GLenum>(get_format())));
}



mipmapped_texture3::mipmapped_texture3(texture_type type, const vec3u& size,
  texture_format format, positive<uint> mipmap_level_count)
  : texture3_base(type, size, format)
  , m_mipmap_level_count(mipmap_level_count)
{}



mipmapped_texture3::~mipmapped_texture3()
{}



texture_filter mipmapped_texture3::get_filter() const
{
  return get_filter_internal();
}



void mipmapped_texture3::set_filter(texture_filter filter)
{
  set_filter_internal(filter);
}



mipmapped_texture3::wrap_mode mipmapped_texture3::get_wrap_mode() const
{
  return {texture_wrap_mode(gl::get_texture_wrap_mode_s(get_handle())),
    texture_wrap_mode(gl::get_texture_wrap_mode_t(get_handle())),
    texture_wrap_mode(gl::get_texture_wrap_mode_r(get_handle()))};
}



void mipmapped_texture3::set_wrap_mode(const wrap_mode& wm)
{
  gl::set_texture_wrap_mode_s(get_handle(), static_cast<GLenum>(wm[0]));
  gl::set_texture_wrap_mode_t(get_handle(), static_cast<GLenum>(wm[1]));
  gl::set_texture_wrap_mode_r(get_handle(), static_cast<GLenum>(wm[2]));
}


std::vector<uint8_t> mipmapped_texture3::get_image() const
{
  return get_sub_image(vec3u::zero(), get_size());
}



std::vector<uint8_t> mipmapped_texture3::get_sub_image(
  const vec3u& offset, const vec3u& size) const
{
  vec3u bounds = offset + size;
  HOU_PRECOND(std::equal(bounds.begin(), bounds.end(), get_size().begin(),
    get_size().end(), std::less_equal<uint>()));

  gl::set_unpack_alignment(1u);
  std::vector<uint8_t> buffer(
    gl::compute_texture_size_bytes(size.x(), size.y(), size.z(),
      gl::get_texture_external_format_for_internal_format(
        static_cast<GLenum>(get_format()))),
    0u);

  // clang-format off
  gl::get_texture_sub_image(get_handle(),
    offset.x(), offset.y(), offset.z(),                   // offset
    size.x(), size.y(), size.z(),                         // size
    0,                                                    // level
    gl::get_texture_external_format_for_internal_format(
      static_cast<GLenum>(get_format())),                 // external format
    gl::get_texture_data_type_for_internal_format(
      static_cast<GLenum>(get_format())),                 // data type
    narrow_cast<GLsizei>(buffer.size()),                  // data size
    buffer.data());                                       // data
  // clang-format on

  return buffer;
}



void mipmapped_texture3::set_image(const pixel_view3& pv)
{
  set_sub_image(vec3u::zero(), pv);
}



void mipmapped_texture3::set_sub_image(
  const vec3u& offset, const pixel_view3& pv)
{
  HOU_PRECOND(pv.get_bytes_per_pixel() == get_bytes_per_pixel(get_format()));

  vec3u bounds = offset + pv.get_size();
  HOU_PRECOND(std::equal(bounds.begin(), bounds.end(), get_size().begin(),
    get_size().end(), std::less_equal<uint>()));

  // clang-format off
  gl::set_texture_sub_image_3d(get_handle(),
    0,                                                        // level
    offset.x(), offset.y(), offset.z(),                       // offset
    pv.get_size().x(), pv.get_size().y(), pv.get_size().z(),  // size
    gl::get_texture_external_format_for_internal_format(
      static_cast<GLenum>(get_format())),                     // external format
    gl::get_texture_data_type_for_internal_format(
      static_cast<GLenum>(get_format())),                     // data type
    reinterpret_cast<const void*>(pv.get_data()));            // data
  // clang-format on

  gl::generate_mip_map(get_handle());
}



void mipmapped_texture3::clear()
{
  gl::reset_texture_sub_image_3d(get_handle(), 0, 0, 0, 0, get_size().x(),
    get_size().y(), get_size().z(), static_cast<GLenum>(get_format()));
  gl::generate_mip_map(get_handle());
}



positive<uint> mipmapped_texture3::get_mipmap_level_count() const
{
  return m_mipmap_level_count;
}



positive<uint> mipmapped_texture3::get_sample_count() const
{
  return 1u;
}



bool mipmapped_texture3::is_mipmapped() const
{
  return true;
}



bool mipmapped_texture3::is_multisampled() const
{
  return false;
}



const vec3u& texture2_array::get_max_size()
{
  static const vec3u max_size(narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_layers()));
  return max_size;
}



positive<uint> texture2_array::get_max_mipmap_level_count(const vec3u& size)
{
  return 1u
    + static_cast<uint>(
        log(static_cast<float>(std::max(size.x(), size.y())), 2));
}



texture2_array::texture2_array(const vec3u& size, texture_format format,
  positive<uint> mipmap_level_count, bool)
  : mipmapped_texture3(
      texture_type::texture2_array, size, format, mipmap_level_count)
{
  HOU_PRECOND(size.x() > 0 && size.x() <= get_max_size().x());
  HOU_PRECOND(size.y() > 0 && size.y() <= get_max_size().y());
  HOU_PRECOND(size.z() > 0 && size.z() <= get_max_size().z());
  HOU_PRECOND(mipmap_level_count <= get_max_mipmap_level_count(size));

  gl::set_texture_storage_3d(get_handle(), mipmap_level_count,
    static_cast<GLenum>(format), size.x(), size.y(), size.z());
}



texture2_array::texture2_array(
  const vec3u& size, texture_format format, positive<uint> mipmap_level_count)
  : texture2_array(size, format, mipmap_level_count, true)
{
  clear();
}



texture2_array::texture2_array(const pixel_view3& pv, texture_format format,
  positive<uint> mipmap_level_count)
  : texture2_array(pv.get_size(), format, mipmap_level_count, true)
{
  set_image(pv);
}



const vec3u& texture3::get_max_size()
{
  static const vec3u max_size(narrow_cast<uint>(gl::get_max_3d_texture_size()),
    narrow_cast<uint>(gl::get_max_3d_texture_size()),
    narrow_cast<uint>(gl::get_max_3d_texture_size()));
  return max_size;
}



positive<uint> texture3::get_max_mipmap_level_count(const vec3u& size)
{
  return 1u
    + static_cast<uint>(log(
        static_cast<float>(std::max(size.x(), std::max(size.y(), size.z()))),
        2));
}



texture3::texture3(const vec3u& size, texture_format format,
  positive<uint> mipmap_level_count, bool)
  : mipmapped_texture3(texture_type::texture3, size, format, mipmap_level_count)
{
  HOU_PRECOND(format == texture_format::r || format == texture_format::rg
    || format == texture_format::rgb || format == texture_format::rgba);
  HOU_PRECOND(size.x() > 0 && size.x() <= get_max_size().x());
  HOU_PRECOND(size.y() > 0 && size.y() <= get_max_size().y());
  HOU_PRECOND(size.z() > 0 && size.z() <= get_max_size().z());
  HOU_PRECOND(mipmap_level_count <= get_max_mipmap_level_count(size));

  gl::set_texture_storage_3d(get_handle(), mipmap_level_count,
    static_cast<GLenum>(format), size.x(), size.y(), size.z());
}



texture3::texture3(
  const vec3u& size, texture_format format, positive<uint> mipmap_level_count)
  : texture3(size, format, mipmap_level_count, true)
{
  clear();
}



texture3::texture3(const pixel_view3& pv, texture_format format,
  positive<uint> mipmap_level_count)
  : texture3(pv.get_size(), format, mipmap_level_count, true)
{
  set_image(pv);
}



const vec3u& multisampled_texture2_array::get_max_size()
{
  static const vec3u max_size(narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_size()),
    narrow_cast<uint>(gl::get_max_texture_layers()));
  return max_size;
}



positive<uint> multisampled_texture2_array::get_max_sample_count()
{
  return gl::get_max_texture_samples();
}



multisampled_texture2_array::multisampled_texture2_array(const vec3u& size,
  texture_format format, positive<uint> sample_count,
  bool fixed_sample_locations)
  : texture3_base(texture_type::multisampled_texture2_array, size, format)
  , m_sample_count(sample_count)
  , m_fixed_sample_locations(fixed_sample_locations)
{
  HOU_PRECOND(size.x() > 0 && size.x() <= get_max_size().x());
  HOU_PRECOND(size.y() > 0 && size.y() <= get_max_size().y());
  HOU_PRECOND(size.z() > 0 && size.z() <= get_max_size().z());
  HOU_PRECOND(sample_count <= get_max_sample_count());

  gl::set_texture_storage_3d_multisample(get_handle(), sample_count,
    static_cast<GLenum>(format), size.x(), size.y(), size.z(),
    fixed_sample_locations);
}



bool multisampled_texture2_array::has_fixed_sample_locations() const noexcept
{
  return m_fixed_sample_locations;
}



positive<uint> multisampled_texture2_array::get_mipmap_level_count() const
{
  return 1u;
}



positive<uint> multisampled_texture2_array::get_sample_count() const
{
  return m_sample_count;
}



bool multisampled_texture2_array::is_mipmapped() const
{
  return false;
}



bool multisampled_texture2_array::is_multisampled() const
{
  return true;
}

}  // namespace hou
