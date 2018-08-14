// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/non_copyable.hpp"

#include "hou/gfx/pixel_view.hpp"
#include "hou/gfx/texture_channel_mapping.hpp"
#include "hou/gfx/texture_filter.hpp"
#include "hou/gfx/texture_format.hpp"
#include "hou/gfx/texture_type.hpp"
#include "hou/gfx/texture_wrap_mode.hpp"

#include "hou/gfx/gfx_config.hpp"

#include "hou/gl/gl_texture_handle.hpp"

#include "hou/cor/checked_variable.hpp"

#include "hou/mth/matrix_fwd.hpp"

#ifndef HOU_GFX_TEXTURE_HPP
#define HOU_GFX_TEXTURE_HPP

namespace hou
{

namespace exp
{

class HOU_GFX_API texture : public non_copyable
{
public:
  static void bind(const texture& tex, uint tu);
  static void unbind(uint tu);
  static uint get_texture_unit_count();

public:
  texture(texture_type type, texture_format format);
  texture(texture&& other) noexcept = default;
  virtual ~texture() = 0;

  const gl::texture_handle& get_handle() const noexcept;
  texture_format get_format() const noexcept;

  bool is_bound(uint tu) const;

protected:
  texture_filter get_filter_internal() const;
  void set_filter_internal(texture_filter filter);

private:
  gl::texture_handle m_handle;
  texture_format m_format;
};



class HOU_GFX_API texture2_base : public texture
{
public:
  texture2_base(texture_type type, const vec2u& size, texture_format format);
  texture2_base(texture2_base&& other) noexcept = default;
  virtual ~texture2_base() = 0;

  const vec2u& get_size() const noexcept;

private:
  vec2u m_size;
};



class HOU_GFX_API texture2 : public texture2_base
{
public:
  static const vec2u& get_max_size();
  static positive<uint> get_max_mipmap_level_count(const vec2u& size);

public:
  texture2(const vec2u& size, texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);
  texture2(const pixel_view2& pv, texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);
  texture2(texture2&& other) noexcept = default;

  positive<uint> get_mipmap_level_count() const noexcept;

  texture_filter get_filter() const;
  void set_filter(texture_filter filter);

  std::array<texture_wrap_mode, 2u> get_wrap_mode() const;
  void set_wrap_mode(const std::array<texture_wrap_mode, 2u>& wm);

  std::vector<uint8_t> get_image() const;
  std::vector<uint8_t> get_sub_image(
    const vec2u& offset, const vec2u& size) const;
  void set_image(const pixel_view2& pv);
  void set_sub_image(const vec2u& offset, const pixel_view2& pv);
  void clear();

private:
  texture2(const vec2u& size, texture_format format,
    positive<uint> mipmap_level_count, bool);

private:
  positive<uint> m_mipmap_level_count;
};



class HOU_GFX_API multisampled_texture2 : public texture2_base
{
public:
  static const vec2u& get_max_size();
  static positive<uint> get_max_sample_count();

public:
  multisampled_texture2(const vec2u& size,
    texture_format format = texture_format::rgba,
    positive<uint> sample_count = 1u, bool fixed_sample_locations = true);
  multisampled_texture2(multisampled_texture2&& other) noexcept = default;

  positive<uint> get_sample_count() const noexcept;
  bool has_fixed_sample_locations() const noexcept;

private:
  positive<uint> m_sample_count;
  bool m_fixed_sample_locations;
};



class HOU_GFX_API texture3_base : public texture
{
public:
  // Only color formats are supported.
  texture3_base(texture_type type, const vec3u& size, texture_format format);
  texture3_base(texture3_base&& other) noexcept = default;
  virtual ~texture3_base() = 0;

  const vec3u& get_size() const noexcept;

private:
  vec3u m_size;
};



class HOU_GFX_API mipmapped_texture3 : public texture3_base
{
public:
  mipmapped_texture3(texture_type type, const vec3u& size, texture_format format,
    positive<uint> mipmap_level_count);
  mipmapped_texture3(mipmapped_texture3&& other) noexcept = default;
  virtual ~mipmapped_texture3() = 0;

  positive<uint> get_mipmap_level_count() const noexcept;

  texture_filter get_filter() const;
  void set_filter(texture_filter filter);

  std::array<texture_wrap_mode, 3u> get_wrap_mode() const;
  void set_wrap_mode(const std::array<texture_wrap_mode, 3u>& wm);

  std::vector<uint8_t> get_image() const;
  std::vector<uint8_t> get_sub_image(
    const vec3u& offset, const vec3u& size) const;
  void set_image(const pixel_view3& pv);
  void set_sub_image(const vec3u& offset, const pixel_view3& pv);
  void clear();

private:
  positive<uint> m_mipmap_level_count;
};



class HOU_GFX_API texture2_array : public mipmapped_texture3
{
public:
  static const vec3u& get_max_size();
  static positive<uint> get_max_mipmap_level_count(const vec3u& size);

public:
  texture2_array(const vec3u& size,
    texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);
  texture2_array(const pixel_view3& pv,
    texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);
  texture2_array(texture2_array&& other) noexcept = default;

private:
  texture2_array(const vec3u& pv, texture_format format,
    positive<uint> mipmap_level_count, bool);
};



class HOU_GFX_API texture3 : public mipmapped_texture3
{
public:
  static const vec3u& get_max_size();
  static positive<uint> get_max_mipmap_level_count(const vec3u& size);

public:
  texture3(const vec3u& size, texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);
  texture3(const pixel_view3& pv, texture_format format = texture_format::rgba,
    positive<uint> mipmap_level_count = 1u);
  texture3(texture3&& other) noexcept = default;

private:
  texture3(const vec3u& pv, texture_format format,
    positive<uint> mipmap_level_count, bool);
};



class HOU_GFX_API multisampled_texture2_array : public texture3_base
{
public:
  static const vec3u& get_max_size();
  static positive<uint> get_max_sample_count();

public:
  multisampled_texture2_array(const vec3u& size,
    texture_format format = texture_format::rgba,
    positive<uint> sample_count = 1u, bool fixed_sample_locations = true);
  multisampled_texture2_array(multisampled_texture2_array&& other) noexcept
    = default;

  positive<uint> get_sample_count() const noexcept;
  bool has_fixed_sample_locations() const noexcept;

private:
  positive<uint> m_sample_count;
  bool m_fixed_sample_locations;
};

}  // namespace exp

}  // namespace hou

#endif
