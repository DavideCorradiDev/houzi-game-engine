namespace hou
{

constexpr uint get_pixel_format_byte_count(pixel_format format)
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
    default:
      HOU_UNREACHABLE();
      return 1u;
  };
}

}  // namespace hou
