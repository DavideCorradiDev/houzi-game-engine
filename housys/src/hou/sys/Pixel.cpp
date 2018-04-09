// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/Pixel.hpp"



namespace hou
{

namespace
{

uint8_t averageChannels(uint8_t r, uint8_t g, uint8_t b);

uint8_t averageChannels(uint8_t r, uint8_t g, uint8_t b)
{
  return static_cast<uint8_t>(
    (static_cast<int>(r) * 77u + static_cast<int>(g) * 150u
      + static_cast<int>(b) * 29u)
    / 256u);
}

}  // namespace



template <PixelFormat pf>
PixelFormat PixelT<pf>::getFormat()
{
  return pf;
}



template <PixelFormat pf>
uint PixelT<pf>::getByteCount()
{
  return getPixelFormatByteCount(pf);
}



template <PixelFormat pf>
PixelT<pf>::PixelT()
  : mChannels()
{
  mChannels.fill(0u);
}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
PixelT<pf>::PixelT(uint8_t r)
  : mChannels{r}
{}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
PixelT<pf>::PixelT(uint8_t r, uint8_t g)
  : mChannels{r, g}
{}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
PixelT<pf>::PixelT(uint8_t r, uint8_t g, uint8_t b)
  : mChannels{r, g, b}
{}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
PixelT<pf>::PixelT(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
  : mChannels{r, g, b, a}
{}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
PixelT<pf>::PixelT(const Color& c)
  : mChannels{c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha()}
{}



template <>
template <>
PixelT<PixelFormat::R>::PixelT<PixelFormat::RGB, void>(
  const PixelT<PixelFormat::RGB>& other)
  : mChannels{averageChannels(other.getR(), other.getG(), other.getB())}
{}



template <>
template <>
PixelT<PixelFormat::R>::PixelT<PixelFormat::RGBA, void>(
  const PixelT<PixelFormat::RGBA>& other)
  : mChannels{averageChannels(other.getR(), other.getG(), other.getB())}
{}



template <>
template <>
PixelT<PixelFormat::RG>::PixelT<PixelFormat::R, void>(
  const PixelT<PixelFormat::R>& other)
  : mChannels{other.getR(), 255u}
{}



template <>
template <>
PixelT<PixelFormat::RG>::PixelT<PixelFormat::RGB, void>(
  const PixelT<PixelFormat::RGB>& other)
  : mChannels{averageChannels(other.getR(), other.getG(), other.getB()), 255u}
{}



template <>
template <>
PixelT<PixelFormat::RG>::PixelT<PixelFormat::RGBA, void>(
  const PixelT<PixelFormat::RGBA>& other)
  : mChannels{
      averageChannels(other.getR(), other.getG(), other.getB()), other.getA()}
{}



template <>
template <>
PixelT<PixelFormat::RGB>::PixelT<PixelFormat::R, void>(
  const PixelT<PixelFormat::R>& other)
  : mChannels{other.getR(), other.getR(), other.getR()}
{}



template <>
template <>
PixelT<PixelFormat::RGB>::PixelT<PixelFormat::RG, void>(
  const PixelT<PixelFormat::RG>& other)
  : mChannels{other.getR(), other.getR(), other.getR()}
{}



template <>
template <>
PixelT<PixelFormat::RGB>::PixelT<PixelFormat::RGBA, void>(
  const PixelT<PixelFormat::RGBA>& other)
  : mChannels{other.getR(), other.getG(), other.getB()}
{}



template <>
template <>
PixelT<PixelFormat::RGBA>::PixelT<PixelFormat::R, void>(
  const PixelT<PixelFormat::R>& other)
  : mChannels{other.getR(), other.getR(), other.getR(), 255u}
{}



template <>
template <>
PixelT<PixelFormat::RGBA>::PixelT<PixelFormat::RG, void>(
  const PixelT<PixelFormat::RG>& other)
  : mChannels{other.getR(), other.getR(), other.getR(), other.getG()}
{}



template <>
template <>
PixelT<PixelFormat::RGBA>::PixelT<PixelFormat::RGB, void>(
  const PixelT<PixelFormat::RGB>& other)
  : mChannels{other.getR(), other.getG(), other.getB(), 255u}
{}



template <PixelFormat pf>
uint8_t PixelT<pf>::getR() const
{
  return mChannels[0];
}



template <PixelFormat pf>
void PixelT<pf>::setR(uint8_t value)
{
  mChannels[0] = value;
}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
uint8_t PixelT<pf>::getG() const
{
  return mChannels[1];
}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
void PixelT<pf>::setG(uint8_t value)
{
  mChannels[1] = value;
}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
uint8_t PixelT<pf>::getB() const
{
  return mChannels[2];
}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
void PixelT<pf>::setB(uint8_t value)
{
  mChannels[2] = value;
}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
uint8_t PixelT<pf>::getA() const
{
  return mChannels[3];
}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
void PixelT<pf>::setA(uint8_t value)
{
  mChannels[3] = value;
}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
Color PixelT<pf>::getColor() const
{
  return Color(mChannels[0], mChannels[1], mChannels[2], mChannels[3]);
}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
void PixelT<pf>::setColor(const Color& c)
{
  mChannels[0] = c.getRed();
  mChannels[1] = c.getGreen();
  mChannels[2] = c.getBlue();
  mChannels[3] = c.getAlpha();
}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
void PixelT<pf>::set(uint8_t r)
{
  mChannels[0] = r;
}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
void PixelT<pf>::set(uint8_t r, uint8_t g)
{
  mChannels[0] = r;
  mChannels[1] = g;
}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
void PixelT<pf>::set(uint8_t r, uint8_t g, uint8_t b)
{
  mChannels[0] = r;
  mChannels[1] = g;
  mChannels[2] = b;
}



template <PixelFormat pf>
template <PixelFormat f, typename Enable>
void PixelT<pf>::set(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  mChannels[0] = r;
  mChannels[1] = g;
  mChannels[2] = b;
  mChannels[3] = a;
}
template <>
template <>
PixelT<PixelFormat::R>::PixelT<PixelFormat::RG, void>(
  const PixelT<PixelFormat::RG>& other)
  : mChannels{other.getR()}
{}



template <>
std::ostream& operator<<<PixelFormat::R>(std::ostream& os, const PixelR& pixel)
{
  return os << "{R = " << static_cast<int>(pixel.getR()) << "}";
}



template <>
std::ostream& operator<<<PixelFormat::RG>(
  std::ostream& os, const PixelRG& pixel)
{
  return os << "{R = " << static_cast<int>(pixel.getR())
            << ", G = " << static_cast<int>(pixel.getG()) << "}";
}



template <>
std::ostream& operator<<<PixelFormat::RGB>(
  std::ostream& os, const PixelRGB& pixel)
{
  return os << "{R = " << static_cast<int>(pixel.getR())
            << ", G = " << static_cast<int>(pixel.getG())
            << ", B = " << static_cast<int>(pixel.getB()) << "}";
}



template <>
std::ostream& operator<<<PixelFormat::RGBA>(
  std::ostream& os, const PixelRGBA& pixel)
{
  return os << "{R = " << static_cast<int>(pixel.getR())
            << ", G = " << static_cast<int>(pixel.getG())
            << ", B = " << static_cast<int>(pixel.getB())
            << ", A = " << static_cast<int>(pixel.getA()) << "}";
}



#define INSTANTIATE_CONVERSION_CONSTRUCTOR(pf1, pf2) \
  template PixelT<pf1>::PixelT<pf2, void>(const PixelT<pf2>&);



#define INSTANTIATE_CHANNEL_FUNCTIONS(pf, Channel)             \
  template uint8_t PixelT<pf>::get##Channel<pf, void>() const; \
  template void PixelT<pf>::set##Channel<pf, void>(uint8_t);



template class PixelT<PixelFormat::R>;
template PixelT<PixelFormat::R>::PixelT<PixelFormat::R, void>(uint8_t);
template void PixelT<PixelFormat::R>::set<PixelFormat::R, void>(uint8_t);
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::R, PixelFormat::RG)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::R, PixelFormat::RGB)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::R, PixelFormat::RGBA)

template class PixelT<PixelFormat::RG>;
template PixelT<PixelFormat::RG>::PixelT<PixelFormat::RG, void>(
  uint8_t, uint8_t);
template void PixelT<PixelFormat::RG>::set<PixelFormat::RG, void>(
  uint8_t, uint8_t);
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RG, PixelFormat::R)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RG, PixelFormat::RGB)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RG, PixelFormat::RGBA)
INSTANTIATE_CHANNEL_FUNCTIONS(PixelFormat::RG, G)

template class PixelT<PixelFormat::RGB>;
template PixelT<PixelFormat::RGB>::PixelT<PixelFormat::RGB, void>(
  uint8_t, uint8_t, uint8_t);
template void PixelT<PixelFormat::RGB>::set<PixelFormat::RGB, void>(
  uint8_t, uint8_t, uint8_t);
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RGB, PixelFormat::R)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RGB, PixelFormat::RG)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RGB, PixelFormat::RGBA)
INSTANTIATE_CHANNEL_FUNCTIONS(PixelFormat::RGB, G)
INSTANTIATE_CHANNEL_FUNCTIONS(PixelFormat::RGB, B)

template class PixelT<PixelFormat::RGBA>;
template PixelT<PixelFormat::RGBA>::PixelT<PixelFormat::RGBA, void>(
  uint8_t, uint8_t, uint8_t, uint8_t);
template void PixelT<PixelFormat::RGBA>::set<PixelFormat::RGBA, void>(
  uint8_t, uint8_t, uint8_t, uint8_t);
template PixelT<PixelFormat::RGBA>::PixelT<PixelFormat::RGBA, void>(
  const Color&);
template Color PixelT<PixelFormat::RGBA>::getColor<PixelFormat::RGBA, void>()
  const;
template void PixelT<PixelFormat::RGBA>::setColor<PixelFormat::RGBA, void>(
  const Color&);
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RGBA, PixelFormat::R)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RGBA, PixelFormat::RG)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RGBA, PixelFormat::RGB)
INSTANTIATE_CHANNEL_FUNCTIONS(PixelFormat::RGBA, G)
INSTANTIATE_CHANNEL_FUNCTIONS(PixelFormat::RGBA, B)
INSTANTIATE_CHANNEL_FUNCTIONS(PixelFormat::RGBA, A)

}  // namespace hou
