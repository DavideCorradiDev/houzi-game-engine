// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_COLOR_FORMAT_HPP
#define HOU_GL_COLOR_FORMAT_HPP

#include "hou/gl/gl_config.hpp"

#include <iostream>



namespace hou
{

namespace gl
{

class HOU_GL_API color_format
{
public:
  color_format(uint red, uint green, uint blue, uint alpha);

  uint get_red_bit_count() const;
  uint get_green_bit_count() const;
  uint get_blue_bit_count() const;
  uint get_alpha_bit_count() const;
  uint get_bit_count() const;

private:
  uint m_red_bit_count;
  uint m_green_bit_count;
  uint m_blue_bit_count;
  uint m_alpha_bit_count;
};

HOU_GL_API bool
  operator==(const color_format& lhs, const color_format& rhs);
HOU_GL_API bool operator!=(const color_format& lhs, const color_format& rhs);
HOU_GL_API std::ostream& operator<<(std::ostream& os, const color_format& cf);

}  // namespace gl

}  // namespace hou

#endif
