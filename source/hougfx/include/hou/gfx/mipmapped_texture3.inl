// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <pixel_format PF>
image3<PF> mipmapped_texture3::get_image() const
{
  return get_sub_image<PF>(vec3u::zero(), get_size());
}



template <pixel_format PF>
image3<PF> mipmapped_texture3::get_sub_image(
  const vec3u& offset, const vec3u& size) const
{
  std::vector<uint8_t> pixels = get_sub_pixels(offset, size);
  switch(get_format())
  {
    case texture_format::r:
      return image3<PF>(image3_r(size,
        reinterpret_span<const pixel_r>(
          span<const uint8_t>(pixels.data(), pixels.size()))));
    case texture_format::rg:
      return image3<PF>(image3_rg(size,
        reinterpret_span<const pixel_rg>(
          span<const uint8_t>(pixels.data(), pixels.size()))));
    case texture_format::rgb:
      return image3<PF>(image3_rgb(size,
        reinterpret_span<const pixel_rgb>(
          span<const uint8_t>(pixels.data(), pixels.size()))));
    case texture_format::rgba:
    case texture_format::depth_stencil:
      return image3<PF>(image3_rgba(size,
        reinterpret_span<const pixel_rgba>(
          span<const uint8_t>(pixels.data(), pixels.size()))));
  }
}



template <pixel_format PF>
void mipmapped_texture3::set_image(const image3<PF>& img)
{
  HOU_PRECOND(img.get_size() == get_size());
  return set_sub_image(vec3u::zero(), img);
}



template <pixel_format PF>
void mipmapped_texture3::set_sub_image(
  const vec3u& offset, const image3<PF>& img)
{
  switch(get_format())
  {
    case texture_format::r:
      set_sub_pixels(offset, img.get_size(),
        reinterpret_span<const uint8_t>(
          span<const pixel_r>(image3_r(img).get_pixels())));
      break;
    case texture_format::rg:
      set_sub_pixels(offset, img.get_size(),
        reinterpret_span<const uint8_t>(
          span<const pixel_rg>(image3_rg(img).get_pixels())));
      break;
    case texture_format::rgb:
      set_sub_pixels(offset, img.get_size(),
        reinterpret_span<const uint8_t>(
          span<const pixel_rgb>(image3_rgb(img).get_pixels())));
      break;
    case texture_format::rgba:
    case texture_format::depth_stencil:
      set_sub_pixels(offset, img.get_size(),
        reinterpret_span<const uint8_t>(
          span<const pixel_rgba>(image3_rgba(img).get_pixels())));
      break;
  }
}

}  // namespace hou

