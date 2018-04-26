// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <PixelFormat pf>
constexpr PixelFormat PixelT<pf>::getFormat()
{
  return pf;
}



template <PixelFormat pf>
constexpr uint PixelT<pf>::getByteCount()
{
  return getPixelFormatByteCount(pf);
}

}  // namespace hou
