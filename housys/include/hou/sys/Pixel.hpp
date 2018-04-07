// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_PIXEL_HPP
#define HOU_SYS_PIXEL_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/sys/Color.hpp"
#include "hou/sys/PixelFwd.hpp"

#include <array>

namespace hou {

template <PixelFormat format> class HOU_SYS_API Pixel {
public:
  static constexpr PixelFormat getFormat();
  static constexpr size_t getByteCount();

public:
  Pixel();
  template <PixelFormat f = format,
            typename Enable = std::enable_if_t<f == PixelFormat::R>>
  HOU_SYS_API Pixel(uint8_t r);
  template <PixelFormat f = format,
            typename Enable = std::enable_if_t<f == PixelFormat::RG>>
  HOU_SYS_API Pixel(uint8_t r, uint8_t g);
  template <PixelFormat f = format,
            typename Enable = std::enable_if_t<f == PixelFormat::RGB>>
  HOU_SYS_API Pixel(uint8_t r, uint8_t g, uint8_t b);
  template <PixelFormat f = format,
            typename Enable = std::enable_if_t<f == PixelFormat::RGBA>>
  HOU_SYS_API Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  template <PixelFormat f = format,
            typename Enable = std::enable_if_t<f == PixelFormat::RGBA>>
  HOU_SYS_API Pixel(const Color &c);
  template <PixelFormat otherFormat,
            typename Enable = std::enable_if_t<otherFormat != format>>
  HOU_SYS_API Pixel(const Pixel<otherFormat> &other);

  uint8_t getR() const;
  void setR(uint8_t value);

  template <PixelFormat f = format, typename Enable = std::enable_if_t<
                                        (getPixelFormatByteCount(f) > 1u)>>
  HOU_SYS_API uint8_t getG() const;
  template <PixelFormat f = format, typename Enable = std::enable_if_t<
                                        (getPixelFormatByteCount(f) > 1u)>>
  HOU_SYS_API void setG(uint8_t value);

  template <PixelFormat f = format, typename Enable = std::enable_if_t<
                                        (getPixelFormatByteCount(f) > 2u)>>
  HOU_SYS_API uint8_t getB() const;
  template <PixelFormat f = format, typename Enable = std::enable_if_t<
                                        (getPixelFormatByteCount(f) > 1u)>>
  HOU_SYS_API void setB(uint8_t value);

  template <PixelFormat f = format, typename Enable = std::enable_if_t<
                                        (getPixelFormatByteCount(f) > 3u)>>
  HOU_SYS_API uint8_t getA() const;
  template <PixelFormat f = format, typename Enable = std::enable_if_t<
                                        (getPixelFormatByteCount(f) > 1u)>>
  HOU_SYS_API void setA(uint8_t value);

  template <PixelFormat f = format,
            typename Enable = std::enable_if_t<f == PixelFormat::RGBA>>
  HOU_SYS_API Color getColor() const;
  template <PixelFormat f = format,
            typename Enable = std::enable_if_t<f == PixelFormat::RGBA>>
  HOU_SYS_API void setColor(const Color &c);

  template <PixelFormat f = format,
            typename Enable = std::enable_if_t<f == PixelFormat::R>>
  HOU_SYS_API void set(uint8_t r);
  template <PixelFormat f = format,
            typename Enable = std::enable_if_t<f == PixelFormat::RG>>
  HOU_SYS_API void set(uint8_t r, uint8_t g);
  template <PixelFormat f = format,
            typename Enable = std::enable_if_t<f == PixelFormat::RGB>>
  HOU_SYS_API void set(uint8_t r, uint8_t g, uint8_t b);
  template <PixelFormat f = format,
            typename Enable = std::enable_if_t<f == PixelFormat::RGBA>>
  HOU_SYS_API void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  friend bool operator==(const Pixel &lhs, const Pixel &rhs) {
    return lhs.mChannels == rhs.mChannels;
  }

  friend bool operator!=(const Pixel &lhs, const Pixel &rhs) {
    return lhs.mChannels != rhs.mChannels;
  }

private:
  std::array<uint8_t, getByteCount()> mChannels;
};

template <PixelFormat format>
HOU_SYS_API std::ostream &operator<<(std::ostream &os,
                                     const Pixel<format> &pixel);
} // namespace hou

#include "hou/sys/Pixel.inl"

#endif

