// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_PIXEL_HPP
#define HOU_SYS_PIXEL_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/cor/pragmas.hpp"

#include "hou/sys/Color.hpp"
#include "hou/sys/PixelFwd.hpp"

#include <array>

namespace hou
{

HOU_PRAGMA_PACK_PUSH(1)

/** Represents a pixel.
 *
 *  Note: all possible class instances (one for each possible PixelFormat value)
 *  are already explicitly instantiated and exported in the library.
 *
 *  \tparam pf the pixel format.
 */
template <PixelFormat pf>
class HOU_SYS_API PixelT
{
public:
  /** Retrieves the format of the pixel.
   *
   *  \return the format of the pixel.
   */
  static constexpr PixelFormat getFormat();

  /** Retrieves the amount of bytes used by the pixel.
   *
   * \return the amomunt of bytes used by the pixel.
   */
  static constexpr uint getByteCount();

public:
  /** Default constructor.
   *
   *  Initializes all channels to 0.
   */
  PixelT();

  /** Channel constructor.
   *
   *  Initializes the pixel with the given channel values.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \param r the red channel value.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<f == PixelFormat::R>>
  HOU_SYS_API PixelT(uint8_t r);

  /** Channel constructor.
   *
   *  Initializes the pixel with the given channel values.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \param r the red channel value.
   *  \param g the green channel value.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<f == PixelFormat::RG>>
  HOU_SYS_API PixelT(uint8_t r, uint8_t g);

  /** Channel constructor.
   *
   *  Initializes the pixel with the given channel values.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \param r the red channel value.
   *  \param g the green channel value.
   *  \param b the blue channel value.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<f == PixelFormat::RGB>>
  HOU_SYS_API PixelT(uint8_t r, uint8_t g, uint8_t b);

  /** Channel constructor.
   *
   *  Initializes the pixel with the given channel values.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \param r the red channel value.
   *  \param g the green channel value.
   *  \param b the blue channel value.
   *  \param a the alpha channel value.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<f == PixelFormat::RGBA>>
  HOU_SYS_API PixelT(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  /** Color constructor.
   *
   *  Initializes the pixel with the given color.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \param c the color.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<f == PixelFormat::RGBA>>
  HOU_SYS_API PixelT(const Color& c);

  /** Format conversion constructor.
   *
   *  Initializes the pixel with the channel values of a pixel with a different
   *  format.
   *  The following rules are applied:
   *  * When converting from RG or RGBA to R or RGB, the last input channel (the
   *  transparency channel) is ignored.
   *  * When converting from R or RGB to RG or RGBA the last output channel (the
   *  transparency channel) is set to 255.
   *  * When converting from R or RG to RGB or RGBA, the R, G and B output
   * channels are set to the value of the R input channel.
   *  * When converting from RGB or RGBA to R or RG, the R output channel
   *  (the value channel) is set to a weighted average of the R, G, and B input
   *  channels: Rout = (77 * Rin + 150 * Gin + 29 * Bin) / 256.
   *
   *  \tparam otherFormat the other PixelFormat.
   *  \tparam Enable enabling template parameter.
   *  \param other the other pixel.
   */
  template <PixelFormat otherFormat,
    typename Enable = std::enable_if_t<otherFormat != pf>>
  HOU_SYS_API PixelT(const PixelT<otherFormat>& other);

  /** Retrieves the value of the red channel of the pixel.
   *
   *  \return the value of the channel.
   */
  uint8_t getR() const;

  /** Sets the value of the red channel of the pixel.
   *
   *  \param value the value.
   */
  void setR(uint8_t value);

  /** Retrieves the value of the green channel of the pixel.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \return the value of the channel.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<(getPixelFormatByteCount(f) > 1u)>>
  HOU_SYS_API uint8_t getG() const;

  /** Sets the value of the green channel of the pixel.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \param value the value.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<(getPixelFormatByteCount(f) > 1u)>>
  HOU_SYS_API void setG(uint8_t value);

  /** Retrieves the value of the blue channel of the pixel.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \return the value of the channel.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<(getPixelFormatByteCount(f) > 2u)>>
  HOU_SYS_API uint8_t getB() const;

  /** Sets the value of the blue channel of the pixel.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \param value the value.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<(getPixelFormatByteCount(f) > 1u)>>
  HOU_SYS_API void setB(uint8_t value);

  /** Retrieves the value of the alpha channel of the pixel.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \return the value of the channel.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<(getPixelFormatByteCount(f) > 3u)>>
  HOU_SYS_API uint8_t getA() const;

  /** Sets the value of the alpha channel of the pixel.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \param value the value.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<(getPixelFormatByteCount(f) > 1u)>>
  HOU_SYS_API void setA(uint8_t value);

  /** Retrieves the color of the pixel.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \return the color of the pixel.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<f == PixelFormat::RGBA>>
  HOU_SYS_API Color getColor() const;

  /** Sets the color of the pixel.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \param c the color of the pixel.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<f == PixelFormat::RGBA>>
  HOU_SYS_API void setColor(const Color& c);

  /** Sets the channels of the pixel.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \param r the red channel value.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<f == PixelFormat::R>>
  HOU_SYS_API void set(uint8_t r);

  /** Sets the channels of the pixel.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \param r the red channel value.
   *  \param g the green channel value.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<f == PixelFormat::RG>>
  HOU_SYS_API void set(uint8_t r, uint8_t g);

  /** Sets the channels of the pixel.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \param r the red channel value.
   *  \param g the green channel value.
   *  \param b the blue channel value.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<f == PixelFormat::RGB>>
  HOU_SYS_API void set(uint8_t r, uint8_t g, uint8_t b);

  /** Sets the channels of the pixel.
   *
   *  \tparam f dummy template parameter.
   *  \tparam Enable enabling template parameter.
   *  \param r the red channel value.
   *  \param g the green channel value.
   *  \param b the blue channel value.
   *  \param a the alpha channel value.
   */
  template <PixelFormat f = pf,
    typename Enable = std::enable_if_t<f == PixelFormat::RGBA>>
  HOU_SYS_API void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  /** Checks if two Pixel objects are equal.
   *
   *  \param lhs the left operand.
   *  \param rhs the right operand.
   *  \return the result of the check.
   */
  friend bool operator==(const PixelT& lhs, const PixelT& rhs)
  {
    return lhs.mChannels == rhs.mChannels;
  }

  /** Checks if two Pixel objects are not equal.
   *
   *  \param lhs the left operand.
   *  \param rhs the right operand.
   *  \return the result of the check.
   */
  friend bool operator!=(const PixelT& lhs, const PixelT& rhs)
  {
    return lhs.mChannels != rhs.mChannels;
  }

private:
  std::array<uint8_t, getPixelFormatByteCount(pf)> mChannels;
};

/** Writes the object into a stream.
 *
 *  \tparam pf the pixel format.
 *  \param os the stream.
 *  \param pixel the pixel.
 *  \return a reference to os.
 */
template <PixelFormat pf>
HOU_SYS_API std::ostream& operator<<(std::ostream& os, const PixelT<pf>& pixel);

HOU_PRAGMA_PACK_POP()

}  // namespace hou

#include "hou/sys/Pixel.inl"

#endif
