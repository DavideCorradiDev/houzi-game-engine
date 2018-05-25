// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/pixel.hpp"



namespace hou
{

namespace
{

uint8_t average_channels(uint8_t r, uint8_t g, uint8_t b) noexcept;



uint8_t average_channels(uint8_t r, uint8_t g, uint8_t b) noexcept
{
  return static_cast<uint8_t>(
    (static_cast<int>(r) * 77u + static_cast<int>(g) * 150u
      + static_cast<int>(b) * 29u)
    / 256u);
}

}  // namespace



template <pixel_format PF>
pixel_format pixel<PF>::get_format() noexcept
{
  return format;
}



template <pixel_format PF>
uint pixel<PF>::get_byte_count() noexcept
{
  return byte_count;
}



template <pixel_format PF>
pixel<PF>::pixel() noexcept
  : m_channels()
{
  m_channels.fill(0u);
}



template <>
template <>
pixel<pixel_format::r>::pixel(
  const pixel<pixel_format::rg>& other) noexcept
  : m_channels{other.get_r()}
{}



template <>
template <>
pixel<pixel_format::r>::pixel(
  const pixel<pixel_format::rgb>& other) noexcept
  : m_channels{average_channels(other.get_r(), other.get_g(), other.get_b())}
{}



template <>
template <>
pixel<pixel_format::r>::pixel(
  const pixel<pixel_format::rgba>& other) noexcept
  : m_channels{average_channels(other.get_r(), other.get_g(), other.get_b())}
{}



template <>
template <>
pixel<pixel_format::rg>::pixel(
  const pixel<pixel_format::r>& other) noexcept
  : m_channels{other.get_r(), 255u}
{}



template <>
template <>
pixel<pixel_format::rg>::pixel(
  const pixel<pixel_format::rgb>& other) noexcept
  : m_channels{
      average_channels(other.get_r(), other.get_g(), other.get_b()), 255u}
{}



template <>
template <>
pixel<pixel_format::rg>::pixel(
  const pixel<pixel_format::rgba>& other) noexcept
  : m_channels{average_channels(other.get_r(), other.get_g(), other.get_b()),
      other.get_a()}
{}



template <>
template <>
pixel<pixel_format::rgb>::pixel(
  const pixel<pixel_format::r>& other) noexcept
  : m_channels{other.get_r(), other.get_r(), other.get_r()}
{}



template <>
template <>
pixel<pixel_format::rgb>::pixel(
  const pixel<pixel_format::rg>& other) noexcept
  : m_channels{other.get_r(), other.get_r(), other.get_r()}
{}



template <>
template <>
pixel<pixel_format::rgb>::pixel(
  const pixel<pixel_format::rgba>& other) noexcept
  : m_channels{other.get_r(), other.get_g(), other.get_b()}
{}



template <>
template <>
pixel<pixel_format::rgba>::pixel(
  const pixel<pixel_format::r>& other) noexcept
  : m_channels{other.get_r(), other.get_r(), other.get_r(), 255u}
{}



template <>
template <>
pixel<pixel_format::rgba>::pixel(
  const pixel<pixel_format::rg>& other) noexcept
  : m_channels{other.get_r(), other.get_r(), other.get_r(), other.get_g()}
{}



template <>
template <>
pixel<pixel_format::rgba>::pixel(
  const pixel<pixel_format::rgb>& other) noexcept
  : m_channels{other.get_r(), other.get_g(), other.get_b(), 255u}
{}



template <pixel_format PF>
uint8_t pixel<PF>::get_r() const noexcept
{
  return m_channels[0];
}



template <pixel_format PF>
void pixel<PF>::set_r(uint8_t value) noexcept
{
  m_channels[0] = value;
}



template <>
std::ostream& operator<<(std::ostream& os, const pixel_r& pixel)
{
  return os << "{r = " << static_cast<int>(pixel.get_r()) << "}";
}



template <>
std::ostream& operator<<(std::ostream& os, const pixel_rg& pixel)
{
  return os << "{r = " << static_cast<int>(pixel.get_r())
            << ", g = " << static_cast<int>(pixel.get_g()) << "}";
}



template <>
std::ostream& operator<<(std::ostream& os, const pixel_rgb& pixel)
{
  return os << "{r = " << static_cast<int>(pixel.get_r())
            << ", g = " << static_cast<int>(pixel.get_g())
            << ", b = " << static_cast<int>(pixel.get_b()) << "}";
}



template <>
std::ostream& operator<<(std::ostream& os, const pixel_rgba& pixel)
{
  return os << "{r = " << static_cast<int>(pixel.get_r())
            << ", g = " << static_cast<int>(pixel.get_g())
            << ", b = " << static_cast<int>(pixel.get_b())
            << ", a = " << static_cast<int>(pixel.get_a()) << "}";
}



template class pixel<pixel_format::r>;
template class pixel<pixel_format::rg>;
template class pixel<pixel_format::rgb>;
template class pixel<pixel_format::rgba>;

}  // namespace hou
