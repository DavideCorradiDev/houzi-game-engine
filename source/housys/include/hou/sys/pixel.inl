// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <pixel_format PF>
template <pixel_format PF2, typename Enable>
pixel<PF>::pixel(uint8_t r) noexcept
  : m_channels{r}
{}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
pixel<PF>::pixel(uint8_t r, uint8_t g) noexcept
  : m_channels{r, g}
{}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
pixel<PF>::pixel(uint8_t r, uint8_t g, uint8_t b) noexcept
  : m_channels{r, g, b}
{}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
pixel<PF>::pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept
  : m_channels{r, g, b, a}
{}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
pixel<PF>::pixel(const color& c) noexcept
  : m_channels{c.get_red(), c.get_green(), c.get_blue(), c.get_alpha()}
{}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
uint8_t pixel<PF>::get_g() const noexcept
{
  return m_channels[1];
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel<PF>::set_g(uint8_t value) noexcept
{
  m_channels[1] = value;
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
uint8_t pixel<PF>::get_b() const noexcept
{
  return m_channels[2];
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel<PF>::set_b(uint8_t value) noexcept
{
  m_channels[2] = value;
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
uint8_t pixel<PF>::get_a() const noexcept
{
  return m_channels[3];
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel<PF>::set_a(uint8_t value) noexcept
{
  m_channels[3] = value;
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
color pixel<PF>::get_color() const noexcept
{
  return color(m_channels[0], m_channels[1], m_channels[2], m_channels[3]);
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel<PF>::set_color(const color& c) noexcept
{
  m_channels[0] = c.get_red();
  m_channels[1] = c.get_green();
  m_channels[2] = c.get_blue();
  m_channels[3] = c.get_alpha();
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel<PF>::set(uint8_t r) noexcept
{
  m_channels[0] = r;
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel<PF>::set(uint8_t r, uint8_t g) noexcept
{
  m_channels[0] = r;
  m_channels[1] = g;
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel<PF>::set(uint8_t r, uint8_t g, uint8_t b) noexcept
{
  m_channels[0] = r;
  m_channels[1] = g;
  m_channels[2] = b;
}



template <pixel_format PF>
template <pixel_format PF2, typename Enable>
void pixel<PF>::set(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept
{
  m_channels[0] = r;
  m_channels[1] = g;
  m_channels[2] = b;
  m_channels[3] = a;
}



template <pixel_format PF>
constexpr bool operator==(
  const pixel<PF>& lhs, const pixel<PF>& rhs) noexcept
{
  return lhs.m_channels == rhs.m_channels;
}



template <pixel_format PF>
constexpr bool operator!=(
  const pixel<PF>& lhs, const pixel<PF>& rhs) noexcept
{
  return lhs.m_channels != rhs.m_channels;
}



extern template class HOU_SYS_API pixel<pixel_format::r>;
extern template class HOU_SYS_API pixel<pixel_format::rg>;
extern template class HOU_SYS_API pixel<pixel_format::rgb>;
extern template class HOU_SYS_API pixel<pixel_format::rgba>;

template <>
template <>
HOU_SYS_API pixel<pixel_format::r>::pixel(
  const pixel<pixel_format::rg>& other) noexcept;

template <>
template <>
HOU_SYS_API pixel<pixel_format::r>::pixel(
  const pixel<pixel_format::rgb>& other) noexcept;

template <>
template <>
HOU_SYS_API pixel<pixel_format::r>::pixel(
  const pixel<pixel_format::rgba>& other) noexcept;

template <>
template <>
HOU_SYS_API pixel<pixel_format::rg>::pixel(
  const pixel<pixel_format::r>& other) noexcept;

template <>
template <>
HOU_SYS_API pixel<pixel_format::rg>::pixel(
  const pixel<pixel_format::rgb>& other) noexcept;

template <>
template <>
HOU_SYS_API pixel<pixel_format::rg>::pixel(
  const pixel<pixel_format::rgba>& other) noexcept;

template <>
template <>
HOU_SYS_API pixel<pixel_format::rgb>::pixel(
  const pixel<pixel_format::r>& other) noexcept;

template <>
template <>
HOU_SYS_API pixel<pixel_format::rgb>::pixel(
  const pixel<pixel_format::rg>& other) noexcept;

template <>
template <>
HOU_SYS_API pixel<pixel_format::rgb>::pixel(
  const pixel<pixel_format::rgba>& other) noexcept;

template <>
template <>
HOU_SYS_API pixel<pixel_format::rgba>::pixel(
  const pixel<pixel_format::r>& other) noexcept;

template <>
template <>
HOU_SYS_API pixel<pixel_format::rgba>::pixel(
  const pixel<pixel_format::rg>& other) noexcept;

template <>
template <>
HOU_SYS_API pixel<pixel_format::rgba>::pixel(
  const pixel<pixel_format::rgb>& other) noexcept;

template <>
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, const pixel<pixel_format::r>& pixel);

template <>
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, const pixel<pixel_format::rg>& pixel);

template <>
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, const pixel<pixel_format::rgb>& pixel);

template <>
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, const pixel<pixel_format::rgba>& pixel);

}  // namespace hou
