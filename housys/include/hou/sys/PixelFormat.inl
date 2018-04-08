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
    return 1u;
  };
}

}  // namespace hou
