// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/pixel.hpp"



namespace hou
{

namespace
{

uint8_t average_channels(uint8_t r, uint8_t g, uint8_t b);

uint8_t average_channels(uint8_t r, uint8_t g, uint8_t b)
{
  return static_cast<uint8_t>(
    (static_cast<int>(r) * 77u + static_cast<int>(g) * 150u
      + static_cast<int>(b) * 29u)
    / 256u);
}

}  // namespace



template <pixel_format PF>
pixel_t<PF>::pixel_t()
  : m_channels()
{
  m_channels.fill(0u);
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
pixel_t<PF>::pixel_t(uint8_t r)
  : m_channels{r}
{}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
pixel_t<PF>::pixel_t(uint8_t r, uint8_t g)
  : m_channels{r, g}
{}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
pixel_t<PF>::pixel_t(uint8_t r, uint8_t g, uint8_t b)
  : m_channels{r, g, b}
{}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
pixel_t<PF>::pixel_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
  : m_channels{r, g, b, a}
{}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
pixel_t<PF>::pixel_t(const color& c)
  : m_channels{c.get_red(), c.get_green(), c.get_blue(), c.get_alpha()}
{}



template <>
template <>
pixel_t<pixel_format::r>::pixel_t<pixel_format::rgb, void>(
  const pixel_t<pixel_format::rgb>& other)
  : m_channels{average_channels(other.get_r(), other.get_g(), other.get_b())}
{}



template <>
template <>
pixel_t<pixel_format::r>::pixel_t<pixel_format::rgba, void>(
  const pixel_t<pixel_format::rgba>& other)
  : m_channels{average_channels(other.get_r(), other.get_g(), other.get_b())}
{}



template <>
template <>
pixel_t<pixel_format::rg>::pixel_t<pixel_format::r, void>(
  const pixel_t<pixel_format::r>& other)
  : m_channels{other.get_r(), 255u}
{}



template <>
template <>
pixel_t<pixel_format::rg>::pixel_t<pixel_format::rgb, void>(
  const pixel_t<pixel_format::rgb>& other)
  : m_channels{
      average_channels(other.get_r(), other.get_g(), other.get_b()), 255u}
{}



template <>
template <>
pixel_t<pixel_format::rg>::pixel_t<pixel_format::rgba, void>(
  const pixel_t<pixel_format::rgba>& other)
  : m_channels{average_channels(other.get_r(), other.get_g(), other.get_b()),
      other.get_a()}
{}



template <>
template <>
pixel_t<pixel_format::rgb>::pixel_t<pixel_format::r, void>(
  const pixel_t<pixel_format::r>& other)
  : m_channels{other.get_r(), other.get_r(), other.get_r()}
{}



template <>
template <>
pixel_t<pixel_format::rgb>::pixel_t<pixel_format::rg, void>(
  const pixel_t<pixel_format::rg>& other)
  : m_channels{other.get_r(), other.get_r(), other.get_r()}
{}



template <>
template <>
pixel_t<pixel_format::rgb>::pixel_t<pixel_format::rgba, void>(
  const pixel_t<pixel_format::rgba>& other)
  : m_channels{other.get_r(), other.get_g(), other.get_b()}
{}



template <>
template <>
pixel_t<pixel_format::rgba>::pixel_t<pixel_format::r, void>(
  const pixel_t<pixel_format::r>& other)
  : m_channels{other.get_r(), other.get_r(), other.get_r(), 255u}
{}



template <>
template <>
pixel_t<pixel_format::rgba>::pixel_t<pixel_format::rg, void>(
  const pixel_t<pixel_format::rg>& other)
  : m_channels{other.get_r(), other.get_r(), other.get_r(), other.get_g()}
{}



template <>
template <>
pixel_t<pixel_format::rgba>::pixel_t<pixel_format::rgb, void>(
  const pixel_t<pixel_format::rgb>& other)
  : m_channels{other.get_r(), other.get_g(), other.get_b(), 255u}
{}



template <pixel_format PF>
uint8_t pixel_t<PF>::get_r() const
{
  return m_channels[0];
}



template <pixel_format PF>
void pixel_t<PF>::set_r(uint8_t value)
{
  m_channels[0] = value;
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
uint8_t pixel_t<PF>::get_g() const
{
  return m_channels[1];
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel_t<PF>::set_g(uint8_t value)
{
  m_channels[1] = value;
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
uint8_t pixel_t<PF>::get_b() const
{
  return m_channels[2];
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel_t<PF>::set_b(uint8_t value)
{
  m_channels[2] = value;
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
uint8_t pixel_t<PF>::get_a() const
{
  return m_channels[3];
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel_t<PF>::set_a(uint8_t value)
{
  m_channels[3] = value;
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
color pixel_t<PF>::get_color() const
{
  return color(m_channels[0], m_channels[1], m_channels[2], m_channels[3]);
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel_t<PF>::set_color(const color& c)
{
  m_channels[0] = c.get_red();
  m_channels[1] = c.get_green();
  m_channels[2] = c.get_blue();
  m_channels[3] = c.get_alpha();
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel_t<PF>::set(uint8_t r)
{
  m_channels[0] = r;
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel_t<PF>::set(uint8_t r, uint8_t g)
{
  m_channels[0] = r;
  m_channels[1] = g;
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel_t<PF>::set(uint8_t r, uint8_t g, uint8_t b)
{
  m_channels[0] = r;
  m_channels[1] = g;
  m_channels[2] = b;
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel_t<PF>::set(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  m_channels[0] = r;
  m_channels[1] = g;
  m_channels[2] = b;
  m_channels[3] = a;
}
template <>
template <>
pixel_t<pixel_format::r>::pixel_t<pixel_format::rg, void>(
  const pixel_t<pixel_format::rg>& other)
  : m_channels{other.get_r()}
{}



template <>
std::ostream& operator<<<pixel_format::r>(
  std::ostream& os, const pixelr& ph_pixel)
{
  return os << "{r = " << static_cast<int>(ph_pixel.get_r()) << "}";
}



template <>
std::ostream& operator<<<pixel_format::rg>(
  std::ostream& os, const pixelrg& ph_pixel)
{
  return os << "{r = " << static_cast<int>(ph_pixel.get_r())
            << ", g = " << static_cast<int>(ph_pixel.get_g()) << "}";
}



template <>
std::ostream& operator<<<pixel_format::rgb>(
  std::ostream& os, const pixelrgb& ph_pixel)
{
  return os << "{r = " << static_cast<int>(ph_pixel.get_r())
            << ", g = " << static_cast<int>(ph_pixel.get_g())
            << ", b = " << static_cast<int>(ph_pixel.get_b()) << "}";
}



template <>
std::ostream& operator<<<pixel_format::rgba>(
  std::ostream& os, const pixelrgba& ph_pixel)
{
  return os << "{r = " << static_cast<int>(ph_pixel.get_r())
            << ", g = " << static_cast<int>(ph_pixel.get_g())
            << ", b = " << static_cast<int>(ph_pixel.get_b())
            << ", a = " << static_cast<int>(ph_pixel.get_a()) << "}";
}



#define INSTANTIATE_CONVERSION_CONSTRUCTOR(pf1, pf2) \
  template pixel_t<pf1>::pixel_t<pf2, void>(const pixel_t<pf2>&);



#define INSTANTIATE_CHANNEL_FUNCTIONS(PF, Channel) \
  template uint8_t pixel_t<PF>::get_##Channel<PF, void>() const; \
  template void pixel_t<PF>::set_##Channel<PF, void>(uint8_t);



template class pixel_t<pixel_format::r>;
template pixel_t<pixel_format::r>::pixel_t<pixel_format::r, void>(uint8_t);
template void pixel_t<pixel_format::r>::set<pixel_format::r, void>(uint8_t);
INSTANTIATE_CONVERSION_CONSTRUCTOR(pixel_format::r, pixel_format::rg)
INSTANTIATE_CONVERSION_CONSTRUCTOR(pixel_format::r, pixel_format::rgb)
INSTANTIATE_CONVERSION_CONSTRUCTOR(pixel_format::r, pixel_format::rgba)

template class pixel_t<pixel_format::rg>;
template pixel_t<pixel_format::rg>::pixel_t<pixel_format::rg, void>(
  uint8_t, uint8_t);
template void pixel_t<pixel_format::rg>::set<pixel_format::rg, void>(
  uint8_t, uint8_t);
INSTANTIATE_CONVERSION_CONSTRUCTOR(pixel_format::rg, pixel_format::r)
INSTANTIATE_CONVERSION_CONSTRUCTOR(pixel_format::rg, pixel_format::rgb)
INSTANTIATE_CONVERSION_CONSTRUCTOR(pixel_format::rg, pixel_format::rgba)
INSTANTIATE_CHANNEL_FUNCTIONS(pixel_format::rg, g)

template class pixel_t<pixel_format::rgb>;
template pixel_t<pixel_format::rgb>::pixel_t<pixel_format::rgb, void>(
  uint8_t, uint8_t, uint8_t);
template void pixel_t<pixel_format::rgb>::set<pixel_format::rgb, void>(
  uint8_t, uint8_t, uint8_t);
INSTANTIATE_CONVERSION_CONSTRUCTOR(pixel_format::rgb, pixel_format::r)
INSTANTIATE_CONVERSION_CONSTRUCTOR(pixel_format::rgb, pixel_format::rg)
INSTANTIATE_CONVERSION_CONSTRUCTOR(pixel_format::rgb, pixel_format::rgba)
INSTANTIATE_CHANNEL_FUNCTIONS(pixel_format::rgb, g)
INSTANTIATE_CHANNEL_FUNCTIONS(pixel_format::rgb, b)

template class pixel_t<pixel_format::rgba>;
template pixel_t<pixel_format::rgba>::pixel_t<pixel_format::rgba, void>(
  uint8_t, uint8_t, uint8_t, uint8_t);
template void pixel_t<pixel_format::rgba>::set<pixel_format::rgba, void>(
  uint8_t, uint8_t, uint8_t, uint8_t);
template pixel_t<pixel_format::rgba>::pixel_t<pixel_format::rgba, void>(
  const color&);
template color
  pixel_t<pixel_format::rgba>::get_color<pixel_format::rgba, void>() const;
template void pixel_t<pixel_format::rgba>::set_color<pixel_format::rgba, void>(
  const color&);
INSTANTIATE_CONVERSION_CONSTRUCTOR(pixel_format::rgba, pixel_format::r)
INSTANTIATE_CONVERSION_CONSTRUCTOR(pixel_format::rgba, pixel_format::rg)
INSTANTIATE_CONVERSION_CONSTRUCTOR(pixel_format::rgba, pixel_format::rgb)
INSTANTIATE_CHANNEL_FUNCTIONS(pixel_format::rgba, g)
INSTANTIATE_CHANNEL_FUNCTIONS(pixel_format::rgba, b)
INSTANTIATE_CHANNEL_FUNCTIONS(pixel_format::rgba, a)

}  // namespace hou
