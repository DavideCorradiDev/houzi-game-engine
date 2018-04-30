// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_PIXEL_HPP
#define HOU_SYS_PIXEL_HPP

#include "hou/sys/sys_export.hpp"

#include "hou/cor/pragmas.hpp"

#include "hou/sys/color.hpp"
#include "hou/sys/pixel_fwd.hpp"

#include <array>

namespace hou
{

HOU_PRAGMA_PACK_PUSH(1)

/** Represents a pixel.
 *
 * Note: all possible class instances (one for each possible pixel_format value)
 * are already explicitly instantiated and exported in the library.
 *
 * \tparam PF the pixel format.
 */
template <pixel_format PF>
class HOU_SYS_API pixel_t
{
public:
  /** Retrieves the format of the pixel.
   *
   * \return the format of the pixel.
   */
  static constexpr pixel_format get_format();

  /** Retrieves the amount of bytes used by the pixel.
   *
   * \return the amomunt of bytes used by the pixel.
   */
  static constexpr uint get_byte_count();

public:
  /** default constructor.
   *
   * Initializes all channels to 0.
   */
  pixel_t();

  /** Channel constructor.
   *
   * Initializes the pixel with the given channel values.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param r the red channel value.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<PF2 == pixel_format::r>>
  HOU_SYS_API pixel_t(uint8_t r);

  /** Channel constructor.
   *
   * Initializes the pixel with the given channel values.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param r the red channel value.
   *
   * \param g the green channel value.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<PF2 == pixel_format::rg>>
  HOU_SYS_API pixel_t(uint8_t r, uint8_t g);

  /** Channel constructor.
   *
   * Initializes the pixel with the given channel values.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param r the red channel value.
   *
   * \param g the green channel value.
   *
   * \param b the blue channel value.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<PF2 == pixel_format::rgb>>
  HOU_SYS_API pixel_t(uint8_t r, uint8_t g, uint8_t b);

  /** Channel constructor.
   *
   * Initializes the pixel with the given channel values.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param r the red channel value.
   *
   * \param g the green channel value.
   *
   * \param b the blue channel value.
   *
   * \param a the alpha channel value.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<PF2 == pixel_format::rgba>>
  HOU_SYS_API pixel_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  /** color constructor.
   *
   * Initializes the pixel with the given color.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param c the color.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<PF2 == pixel_format::rgba>>
  HOU_SYS_API pixel_t(const color& c);

  /** Format conversion constructor.
   *
   * Initializes the pixel with the channel values of a pixel with a different
   * format.
   *
   * The following rules are applied:
   *
   * * When converting from rg or rgba to r or rgb, the last input channel (the
   * transparency channel) is ignored.
   *
   * * When converting from r or rgb to rg or rgba the last output channel (the
   * transparency channel) is set to 255.
   *
   * * When converting from r or rg to rgb or rgba, the r, g and b output
   * hannels are set to the value of the r input channel.
   *
   * * When converting from rgb or rgba to r or rg, the r output channel
   * (the value channel) is set to a weighted average of the r, g, and b input
   * channels: Rout = (77 * Rin + 150 * Gin + 29 * Bin) / 256.
   *
   * \tparam otherFormat the other pixel_format.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param other the other pixel.
   */
  template <pixel_format otherFormat,
    typename Enable = std::enable_if_t<otherFormat != PF>>
  HOU_SYS_API pixel_t(const pixel_t<otherFormat>& other);

  /** Retrieves the value of the red channel of the pixel.
   *
   * \return the value of the channel.
   */
  uint8_t get_r() const;

  /** Sets the value of the red channel of the pixel.
   *
   * \param value the value.
   */
  void set_r(uint8_t value);

  /** Retrieves the value of the green channel of the pixel.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \return the value of the channel.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<(get_pixel_format_byte_count(PF2) > 1u)>>
  HOU_SYS_API uint8_t get_g() const;

  /** Sets the value of the green channel of the pixel.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param value the value.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<(get_pixel_format_byte_count(PF2) > 1u)>>
  HOU_SYS_API void set_g(uint8_t value);

  /** Retrieves the value of the blue channel of the pixel.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \return the value of the channel.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<(get_pixel_format_byte_count(PF2) > 2u)>>
  HOU_SYS_API uint8_t get_b() const;

  /** Sets the value of the blue channel of the pixel.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param value the value.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<(get_pixel_format_byte_count(PF2) > 1u)>>
  HOU_SYS_API void set_b(uint8_t value);

  /** Retrieves the value of the alpha channel of the pixel.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \return the value of the channel.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<(get_pixel_format_byte_count(PF2) > 3u)>>
  HOU_SYS_API uint8_t get_a() const;

  /** Sets the value of the alpha channel of the pixel.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param value the value.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<(get_pixel_format_byte_count(PF2) > 1u)>>
  HOU_SYS_API void set_a(uint8_t value);

  /** Retrieves the color of the pixel.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \return the color of the pixel.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<PF2 == pixel_format::rgba>>
  HOU_SYS_API color get_color() const;

  /** Sets the color of the pixel.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param c the color of the pixel.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<PF2 == pixel_format::rgba>>
  HOU_SYS_API void set_color(const color& c);

  /** Sets the channels of the pixel.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param r the red channel value.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<PF2 == pixel_format::r>>
  HOU_SYS_API void set(uint8_t r);

  /** Sets the channels of the pixel.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param r the red channel value.
   *
   * \param g the green channel value.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<PF2 == pixel_format::rg>>
  HOU_SYS_API void set(uint8_t r, uint8_t g);

  /** Sets the channels of the pixel.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param r the red channel value.
   *
   * \param g the green channel value.
   *
   * \param b the blue channel value.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<PF2 == pixel_format::rgb>>
  HOU_SYS_API void set(uint8_t r, uint8_t g, uint8_t b);

  /** Sets the channels of the pixel.
   *
   * \tparam PF2 dummy template parameter.
   *
   * \tparam Enable enabling template parameter.
   *
   * \param r the red channel value.
   *
   * \param g the green channel value.
   *
   * \param b the blue channel value.
   *
   * \param a the alpha channel value.
   */
  template <pixel_format PF2 = PF,
    typename Enable = std::enable_if_t<PF2 == pixel_format::rgba>>
  HOU_SYS_API void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  /** Checks if two pixel objects are equal.
   *
   * \param lhs the left operand.
   *
   * \param rhs the right operand.
   *
   * \return the result of the check.
   */
  friend bool operator==(const pixel_t& lhs, const pixel_t& rhs)
  {
    return lhs.m_channels == rhs.m_channels;
  }

  /** Checks if two pixel objects are not equal.
   *
   * \param lhs the left operand.
   *
   * \param rhs the right operand.
   *
   * \return the result of the check.
   */
  friend bool operator!=(const pixel_t& lhs, const pixel_t& rhs)
  {
    return lhs.m_channels != rhs.m_channels;
  }

private:
  std::array<uint8_t, get_pixel_format_byte_count(PF)> m_channels;
};

/** Writes the object into a ph_stream.
 *
 * \tparam PF the pixel format.
 *
 * \param os the ph_stream.
 *
 * \param pixel the pixel.
 *
 * \return a reference to os.
 */
template <pixel_format PF>
HOU_SYS_API std::ostream& operator<<(std::ostream& os, const pixel_t<PF>& pixel);

HOU_PRAGMA_PACK_POP()

}  // namespace hou

#include "hou/sys/pixel.inl"

#endif
