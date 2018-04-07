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

template <PixelFormat format>
Pixel<format>::Pixel()
  : mChannels()
{
  mChannels.fill(0u);
}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
Pixel<format>::Pixel(uint8_t r)
  : mChannels{r}
{}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
Pixel<format>::Pixel(uint8_t r, uint8_t g)
  : mChannels{r, g}
{}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
Pixel<format>::Pixel(uint8_t r, uint8_t g, uint8_t b)
  : mChannels{r, g, b}
{}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
Pixel<format>::Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
  : mChannels{r, g, b, a}
{}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
Pixel<format>::Pixel(const Color& c)
  : mChannels{c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha()}
{}



template <PixelFormat format>
uint8_t Pixel<format>::getR() const
{
  return mChannels[0];
}



template <PixelFormat format>
void Pixel<format>::setR(uint8_t value)
{
  mChannels[0] = value;
}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
uint8_t Pixel<format>::getG() const
{
  return mChannels[1];
}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
void Pixel<format>::setG(uint8_t value)
{
  mChannels[1] = value;
}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
uint8_t Pixel<format>::getB() const
{
  return mChannels[2];
}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
void Pixel<format>::setB(uint8_t value)
{
  mChannels[2] = value;
}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
uint8_t Pixel<format>::getA() const
{
  return mChannels[3];
}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
void Pixel<format>::setA(uint8_t value)
{
  mChannels[3] = value;
}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
Color Pixel<format>::getColor() const
{
  return Color(mChannels[0], mChannels[1], mChannels[2], mChannels[3]);
}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
void Pixel<format>::setColor(const Color& c)
{
  mChannels[0] = c.getRed();
  mChannels[1] = c.getGreen();
  mChannels[2] = c.getBlue();
  mChannels[3] = c.getAlpha();
}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
void Pixel<format>::set(uint8_t r)
{
  mChannels[0] = r;
}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
void Pixel<format>::set(uint8_t r, uint8_t g)
{
  mChannels[0] = r;
  mChannels[1] = g;
}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
void Pixel<format>::set(uint8_t r, uint8_t g, uint8_t b)
{
  mChannels[0] = r;
  mChannels[1] = g;
  mChannels[2] = b;
}



template <PixelFormat format>
template <PixelFormat f, typename Enable>
void Pixel<format>::set(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  mChannels[0] = r;
  mChannels[1] = g;
  mChannels[2] = b;
  mChannels[3] = a;
}
template <>
template <>
Pixel<PixelFormat::R>::Pixel<PixelFormat::RG, void>(
  const Pixel<PixelFormat::RG>& other)
  : mChannels{other.getR()}
{}



template <>
template <>
Pixel<PixelFormat::R>::Pixel<PixelFormat::RGB, void>(
  const Pixel<PixelFormat::RGB>& other)
  : mChannels{averageChannels(other.getR(), other.getG(), other.getB())}
{}



template <>
template <>
Pixel<PixelFormat::R>::Pixel<PixelFormat::RGBA, void>(
  const Pixel<PixelFormat::RGBA>& other)
  : mChannels{averageChannels(other.getR(), other.getG(), other.getB())}
{}



template <>
template <>
Pixel<PixelFormat::RG>::Pixel<PixelFormat::R, void>(
  const Pixel<PixelFormat::R>& other)
  : mChannels{other.getR(), 255u}
{}



template <>
template <>
Pixel<PixelFormat::RG>::Pixel<PixelFormat::RGB, void>(
  const Pixel<PixelFormat::RGB>& other)
  : mChannels{averageChannels(other.getR(), other.getG(), other.getB()), 255u}
{}



template <>
template <>
Pixel<PixelFormat::RG>::Pixel<PixelFormat::RGBA, void>(
  const Pixel<PixelFormat::RGBA>& other)
  : mChannels{
      averageChannels(other.getR(), other.getG(), other.getB()), other.getA()}
{}



template <>
template <>
Pixel<PixelFormat::RGB>::Pixel<PixelFormat::R, void>(
  const Pixel<PixelFormat::R>& other)
  : mChannels{other.getR(), other.getR(), other.getR()}
{}



template <>
template <>
Pixel<PixelFormat::RGB>::Pixel<PixelFormat::RG, void>(
  const Pixel<PixelFormat::RG>& other)
  : mChannels{other.getR(), other.getR(), other.getR()}
{}



template <>
template <>
Pixel<PixelFormat::RGB>::Pixel<PixelFormat::RGBA, void>(
  const Pixel<PixelFormat::RGBA>& other)
  : mChannels{other.getR(), other.getG(), other.getB()}
{}



template <>
template <>
Pixel<PixelFormat::RGBA>::Pixel<PixelFormat::R, void>(
  const Pixel<PixelFormat::R>& other)
  : mChannels{other.getR(), other.getR(), other.getR(), 255u}
{}



template <>
template <>
Pixel<PixelFormat::RGBA>::Pixel<PixelFormat::RG, void>(
  const Pixel<PixelFormat::RG>& other)
  : mChannels{other.getR(), other.getR(), other.getR(), other.getG()}
{}



template <>
template <>
Pixel<PixelFormat::RGBA>::Pixel<PixelFormat::RGB, void>(
  const Pixel<PixelFormat::RGB>& other)
  : mChannels{other.getR(), other.getG(), other.getB(), 255u}
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
  template Pixel<pf1>::Pixel<pf2, void>(const Pixel<pf2>&);



#define INSTANTIATE_CHANNEL_FUNCTIONS(pf, Channel)            \
  template uint8_t Pixel<pf>::get##Channel<pf, void>() const; \
  template void Pixel<pf>::set##Channel<pf, void>(uint8_t);



template class Pixel<PixelFormat::R>;
template Pixel<PixelFormat::R>::Pixel<PixelFormat::R, void>(uint8_t);
template void Pixel<PixelFormat::R>::set<PixelFormat::R, void>(uint8_t);
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::R, PixelFormat::RG)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::R, PixelFormat::RGB)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::R, PixelFormat::RGBA)

template class Pixel<PixelFormat::RG>;
template Pixel<PixelFormat::RG>::Pixel<PixelFormat::RG, void>(uint8_t, uint8_t);
template void Pixel<PixelFormat::RG>::set<PixelFormat::RG, void>(
  uint8_t, uint8_t);
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RG, PixelFormat::R)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RG, PixelFormat::RGB)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RG, PixelFormat::RGBA)
INSTANTIATE_CHANNEL_FUNCTIONS(PixelFormat::RG, G)

template class Pixel<PixelFormat::RGB>;
template Pixel<PixelFormat::RGB>::Pixel<PixelFormat::RGB, void>(
  uint8_t, uint8_t, uint8_t);
template void Pixel<PixelFormat::RGB>::set<PixelFormat::RGB, void>(
  uint8_t, uint8_t, uint8_t);
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RGB, PixelFormat::R)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RGB, PixelFormat::RG)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RGB, PixelFormat::RGBA)
INSTANTIATE_CHANNEL_FUNCTIONS(PixelFormat::RGB, G)
INSTANTIATE_CHANNEL_FUNCTIONS(PixelFormat::RGB, B)

template class Pixel<PixelFormat::RGBA>;
template Pixel<PixelFormat::RGBA>::Pixel<PixelFormat::RGBA, void>(
  uint8_t, uint8_t, uint8_t, uint8_t);
template void Pixel<PixelFormat::RGBA>::set<PixelFormat::RGBA, void>(
  uint8_t, uint8_t, uint8_t, uint8_t);
template Pixel<PixelFormat::RGBA>::Pixel<PixelFormat::RGBA, void>(const Color&);
template Color Pixel<PixelFormat::RGBA>::getColor<PixelFormat::RGBA, void>()
  const;
template void Pixel<PixelFormat::RGBA>::setColor<PixelFormat::RGBA, void>(
  const Color&);
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RGBA, PixelFormat::R)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RGBA, PixelFormat::RG)
INSTANTIATE_CONVERSION_CONSTRUCTOR(PixelFormat::RGBA, PixelFormat::RGB)
INSTANTIATE_CHANNEL_FUNCTIONS(PixelFormat::RGBA, G)
INSTANTIATE_CHANNEL_FUNCTIONS(PixelFormat::RGBA, B)
INSTANTIATE_CHANNEL_FUNCTIONS(PixelFormat::RGBA, A)

}  // namespace hou

