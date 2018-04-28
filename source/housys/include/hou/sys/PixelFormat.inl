namespace hou
{

constexpr uint getPixelFormatByteCount(PixelFormat format)
{
  switch(format)
  {
  case PixelFormat::R:
    return 1u;
  case PixelFormat::RG:
    return 2u;
  case PixelFormat::RGB:
    return 3u;
  case PixelFormat::RGBA:
    return 4u;
  default:
    HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<int>(format));
    return 1u;
  };
}

}  // namespace hou
