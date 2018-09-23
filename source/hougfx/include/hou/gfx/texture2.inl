// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <pixel_format PF>
image2<PF> texture2::get_image() const
{
  return get_sub_image<PF>(vec2u::zero(), get_size());
}



template <pixel_format PF>
image2<PF> texture2::get_sub_image(const vec2u& offset, const vec2u& size)
{
  std::vector<uint8_t> pixels = get_sub_pixels(offset, size);
  switch(get_format())
  {
    case texture_format::r:
      return image2<PF>(image2_r(size,
        reinterpret_span<const pixel_r>(
          span<const uint8_t>(pixels.data(), pixels.size()))));
    case texture_format::rg:
      return image2<PF>(image2_rg(size,
        reinterpret_span<const pixel_rg>(
          span<const uint8_t>(pixels.data(), pixels.size()))));
    case texture_format::rgb:
      return image2<PF>(image2_rgb(size,
        reinterpret_span<const pixel_rgb>(
          span<const uint8_t>(pixels.data(), pixels.size()))));
    case texture_format::rgba:
    case texture_format::depth_stencil:
      return image2<PF>(image2_rgba(size,
        reinterpret_span<const pixel_rgba>(
          span<const uint8_t>(pixels.data(), pixels.size()))));
  }
}



template <pixel_format PF>
void texture2::set_image(const image2<PF>& img)
{
  return set_sub_image(vec2u::zero(), img);
}



template <pixel_format PF>
void texture2::set_sub_image(const vec2u& offset, const image2<PF>& img)
{
  switch(get_format())
  {
    case texture_format::r:
      set_sub_pixels(offset, img.get_size(),
        reinterpret_span<const uint8_t>(
          span<const pixel_r>(image2_r(img).get_pixels())));
      break;
    case texture_format::rg:
      set_sub_pixels(offset, img.get_size(),
        reinterpret_span<const uint8_t>(
          span<const pixel_rg>(image2_rg(img).get_pixels())));
      break;
    case texture_format::rgb:
      set_sub_pixels(offset, img.get_size(),
        reinterpret_span<const uint8_t>(
          span<const pixel_rgb>(image2_rgb(img).get_pixels())));
      break;
    case texture_format::rgba:
    case texture_format::depth_stencil:
      set_sub_pixels(offset, img.get_size(),
        reinterpret_span<const uint8_t>(
          span<const pixel_rgba>(image2_rgba(img).get_pixels())));
      break;
  }
}

}  // namespace hou
