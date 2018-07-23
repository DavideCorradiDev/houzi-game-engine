// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_DOXYGEN

namespace hou
{

// Instantiations.
extern template class HOU_GFX_API texture_t<texture_type::texture2>;
extern template class HOU_GFX_API texture_t<texture_type::texture2_array>;
extern template class HOU_GFX_API texture_t<texture_type::texture3>;
extern template class HOU_GFX_API texture_t<texture_type::multisample_texture2>;
extern template class HOU_GFX_API
  texture_t<texture_type::multisample_texture2_array>;



// Specializations.

template <>
template <>
HOU_GFX_API typename texture_t<texture_type::texture2>::wrap_mode
  texture_t<texture_type::texture2>::get_wrap_mode() const;

template <>
template <>
HOU_GFX_API typename texture_t<texture_type::texture2_array>::wrap_mode
  texture_t<texture_type::texture2_array>::get_wrap_mode() const;

template <>
template <>
HOU_GFX_API typename texture_t<texture_type::texture3>::wrap_mode
  texture_t<texture_type::texture3>::get_wrap_mode() const;



template <>
template <>
HOU_GFX_API void texture_t<texture_type::texture2>::set_wrap_mode(
  const wrap_mode& wrap_mode);

template <>
template <>
HOU_GFX_API void texture_t<texture_type::texture2_array>::set_wrap_mode(
  const wrap_mode& wrap_mode);

template <>
template <>
HOU_GFX_API void texture_t<texture_type::texture3>::set_wrap_mode(
  const wrap_mode& wrap_mode);



template <>
template <>
HOU_GFX_API typename texture_t<texture_type::texture2>::size_type
  texture_t<texture_type::texture2>::get_mipmap_size(uint mipmap_level) const;

template <>
template <>
HOU_GFX_API typename texture_t<texture_type::texture2_array>::size_type
  texture_t<texture_type::texture2_array>::get_mipmap_size(
    uint mipmap_level) const;

template <>
template <>
HOU_GFX_API typename texture_t<texture_type::texture3>::size_type
  texture_t<texture_type::texture3>::get_mipmap_size(uint mipmap_level) const;



template <>
template <>
HOU_GFX_API texture_t<texture_type::texture2>::texture_t(
  const size_type&, texture_format, positive<uint>);

template <>
template <>
HOU_GFX_API texture_t<texture_type::texture2_array>::texture_t(
  const size_type&, texture_format, positive<uint>);

template <>
template <>
HOU_GFX_API texture_t<texture_type::texture3>::texture_t(
  const size_type&, texture_format, positive<uint>);

template <>
template <>
HOU_GFX_API texture_t<texture_type::multisample_texture2>::texture_t(
  const size_type&, texture_format, positive<uint>, bool);

template <>
template <>
HOU_GFX_API texture_t<texture_type::multisample_texture2_array>::texture_t(
  const size_type&, texture_format, positive<uint>, bool);



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<Type>::clear(const pixel<PF>& px)
{
  set_image<PF, Type2, Enable>(image<PF>(get_size(), px));
}



template <>
template <texture_type Type2, typename Enable>
void texture_t<texture_type::texture2>::reset()
{
  gl::reset_texture_sub_image_2d(get_handle(), 0, 0, 0, get_width(),
    get_height(), static_cast<GLenum>(get_format()));
  generate_mip_map();
}



template <>
template <texture_type Type2, typename Enable>
void texture_t<texture_type::texture2_array>::reset()
{
  gl::reset_texture_sub_image_3d(get_handle(), 0, 0, 0, 0, get_width(),
    get_height(), get_depth(), static_cast<GLenum>(get_format()));
  generate_mip_map();
}



template <>
template <texture_type Type2, typename Enable>
void texture_t<texture_type::texture3>::reset()
{
  gl::reset_texture_sub_image_3d(get_handle(), 0, 0, 0, 0, get_width(),
    get_height(), get_depth(), static_cast<GLenum>(get_format()));
  generate_mip_map();
}



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
texture_t<Type>::texture_t(
  const image<PF>& im, texture_format format, positive<uint> mipmap_level_count)
  : texture_t(im.get_size(), format, mipmap_level_count)
{
  set_image<PF, Type2, Enable>(im);
}



template <texture_type Type>
template <texture_type Type2, typename Enable>
texture_filter texture_t<Type>::get_filter() const
{
  switch(get_texture_min_filter(get_handle()))
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



template <texture_type Type>
template <texture_type Type2, typename Enable>
void texture_t<Type>::set_filter(texture_filter filter)
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



template <texture_type Type>
template <pixel_format PF>
::hou::image<texture_t<Type>::dimension_count, PF>
  texture_t<Type>::get_image_internal(pixel_format pf,
    const typename texture_t<Type>::size_type& s,
    const std::vector<uint8_t>& buffer) const
{
  switch(pf)
  {
    case pixel_format::r:
      return image<PF>(image<pixel_format::r>(
        s, reinterpret_span<const pixel_r>(span<const uint8_t>(buffer))));
    case pixel_format::rg:
      return image<PF>(image<pixel_format::rg>(
        s, reinterpret_span<const pixel_rg>(span<const uint8_t>(buffer))));
    case pixel_format::rgb:
      return image<PF>(image<pixel_format::rgb>(
        s, reinterpret_span<const pixel_rgb>(span<const uint8_t>(buffer))));
    case pixel_format::rgba:
      return image<PF>(image<pixel_format::rgba>(
        s, reinterpret_span<const pixel_rgba>(span<const uint8_t>(buffer))));
  }
  HOU_UNREACHABLE();
  return image<PF>();
}



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
::hou::image<texture_t<Type>::dimension_count, PF> texture_t<Type>::get_image()
  const
{
  return get_mipmap_image<PF, Type2, Enable>(0u);
}



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
::hou::image<texture_t<Type>::dimension_count, PF>
  texture_t<Type>::get_mipmap_image(uint mipmap_level) const
{
  HOU_PRECOND(mipmap_level < get_mipmap_level_count());
  gl::set_unpack_alignment(1);
  pixel_format tex_pf = get_associated_pixel_format(get_format());
  size_type mipmap_size = get_mipmap_size<Type2, Enable>(mipmap_level);
  std::vector<uint8_t> buffer(compute_image_buffer_size(mipmap_size, tex_pf));
  gl::get_texture_image(get_handle(), mipmap_level,
    pixel_format_to_gl_pixel_format(tex_pf),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    narrow_cast<GLsizei>(buffer.size()), buffer.data());
  return this->template get_image_internal<PF>(tex_pf, mipmap_size, buffer);
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
::hou::image<texture_t<texture_type::texture2>::dimension_count, PF>
  texture_t<texture_type::texture2>::get_sub_image(
    const offset_type& offset, const size_type& s) const
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + s, get_size()));
  gl::set_unpack_alignment(1);
  pixel_format tex_pf = get_associated_pixel_format(get_format());
  std::vector<uint8_t> buffer(compute_image_buffer_size(s, tex_pf));
  gl::get_texture_sub_image(get_handle(), offset.x(), offset.y(), 0, s.x(),
    s.y(), 1, 0, pixel_format_to_gl_pixel_format(tex_pf),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    narrow_cast<GLsizei>(buffer.size()), buffer.data());
  return this->template get_image_internal<PF>(tex_pf, s, buffer);
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
::hou::image<texture_t<texture_type::texture2_array>::dimension_count, PF>
  texture_t<texture_type::texture2_array>::get_sub_image(
    const offset_type& offset, const size_type& s) const
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + s, get_size()));
  gl::set_unpack_alignment(1);
  pixel_format tex_pf = get_associated_pixel_format(get_format());
  std::vector<uint8_t> buffer(compute_image_buffer_size(s, tex_pf));
  gl::get_texture_sub_image(get_handle(), offset.x(), offset.y(), offset.z(),
    s.x(), s.y(), s.z(), 0, pixel_format_to_gl_pixel_format(tex_pf),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    narrow_cast<GLsizei>(buffer.size()), buffer.data());
  return this->template get_image_internal<PF>(tex_pf, s, buffer);
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
::hou::image<texture_t<texture_type::texture3>::dimension_count, PF>
  texture_t<texture_type::texture3>::get_sub_image(
    const offset_type& offset, const size_type& s) const
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + s, get_size()));
  gl::set_unpack_alignment(1);
  pixel_format tex_pf = get_associated_pixel_format(get_format());
  std::vector<uint8_t> buffer(compute_image_buffer_size(s, tex_pf));
  gl::get_texture_sub_image(get_handle(), offset.x(), offset.y(), offset.z(),
    s.x(), s.y(), s.z(), 0, pixel_format_to_gl_pixel_format(tex_pf),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    narrow_cast<GLsizei>(buffer.size()), buffer.data());
  return this->template get_image_internal<PF>(tex_pf, s, buffer);
}



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<Type>::set_image(const image<PF>& im)
{
  HOU_PRECOND(im.get_size() == get_size());
  set_sub_image<PF, Type2, Enable>(offset_type::zero(), im);
}



template <texture_type Type>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<Type>::set_sub_image(
  const offset_type& offset, const image<PF>& im)
{
  HOU_PRECOND(get_format() == texture_format::rgba
    || get_format() == texture_format::rgb || get_format() == texture_format::rg
    || get_format() == texture_format::r);
  switch(get_associated_pixel_format(get_format()))
  {
    case pixel_format::r:
      set_sub_image_internal<pixel_format::r, Type2, Enable>(offset, im);
      break;
    case pixel_format::rg:
      set_sub_image_internal<pixel_format::rg, Type2, Enable>(offset, im);
      break;
    case pixel_format::rgb:
      set_sub_image_internal<pixel_format::rgb, Type2, Enable>(offset, im);
      break;
    case pixel_format::rgba:
      set_sub_image_internal<pixel_format::rgba, Type2, Enable>(offset, im);
      break;
  }
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<texture_type::texture2>::set_sub_image_internal(
  const offset_type& offset, const image<PF>& im)
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + im.get_size(), get_size()));
  HOU_PRECOND(check_format_compatibility(get_format(), PF));
  gl::set_texture_sub_image_2d(get_handle(), 0, offset.x(), offset.y(),
    im.get_size().x(), im.get_size().y(), pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(im.get_pixels().data()));
  generate_mip_map();
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<texture_type::texture2_array>::set_sub_image_internal(
  const offset_type& offset, const image<PF>& im)
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + im.get_size(), get_size()));
  HOU_PRECOND(check_format_compatibility(get_format(), PF));
  gl::set_texture_sub_image_3d(get_handle(), 0, offset.x(), offset.y(),
    offset.z(), im.get_size().x(), im.get_size().y(), im.get_size().z(),
    pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(im.get_pixels().data()));
  generate_mip_map();
}



template <>
template <pixel_format PF, texture_type Type2, typename Enable>
void texture_t<texture_type::texture3>::set_sub_image_internal(
  const offset_type& offset, const image<PF>& im)
{
  HOU_PRECOND(element_wise_lower_or_equal(offset + im.get_size(), get_size()));
  HOU_PRECOND(check_format_compatibility(get_format(), PF));
  gl::set_texture_sub_image_3d(get_handle(), 0, offset.x(), offset.y(),
    offset.z(), im.get_size().x(), im.get_size().y(), im.get_size().z(),
    pixel_format_to_gl_pixel_format(PF),
    static_cast<GLenum>(to_gl_type<uint8_t>()),
    reinterpret_cast<const void*>(im.get_pixels().data()));
  generate_mip_map();
}

}  // namespace hou

#endif // HOU_DOXYGEN
