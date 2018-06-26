namespace hou
{

constexpr uint get_bits_per_pixel(pixel_format format) noexcept
{
  constexpr uint bits_per_byte = 8;
  return get_bytes_per_pixel(format) * bits_per_byte;
}



constexpr uint get_bytes_per_pixel(pixel_format format) noexcept
{
  switch(format)
  {
    case pixel_format::r:
      return 1u;
    case pixel_format::rg:
      return 2u;
    case pixel_format::rgb:
      return 3u;
    case pixel_format::rgba:
      return 4u;
  };
  return 1u;
}

}  // namespace hou
