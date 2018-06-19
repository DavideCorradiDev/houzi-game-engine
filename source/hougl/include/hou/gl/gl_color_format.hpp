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

/**
 * Represents a pixel color format.
 */
class HOU_GL_API color_format
{
public:
  /**
   * Constructor.
   *
   * \param red the number of red bits.
   *
   * \param green the number of green bits.
   *
   * \param blue the number of blue bits.
   *
   * \param alpha the number of alpha bits.
   */
  color_format(uint red, uint green, uint blue, uint alpha);

  /**
   * Gets the number of red bits.
   *
   * \return the number of red bits.
   */
  uint get_red_bit_count() const;

  /**
   * Gets the number of green bits.
   *
   * \return the number of green bits.
   */
  uint get_green_bit_count() const;

  /**
   * Gets the number of blue bits.
   *
   * \return the number of blue bits.
   */
  uint get_blue_bit_count() const;

  /**
   * Gets the number of alpha bits.
   *
   * \return the number of alpha bits.
   */
  uint get_alpha_bit_count() const;

  /**
   * Gets the total number of color bits.
   *
   * \return the total number of color bits.
   */
  uint get_bit_count() const;

private:
  uint m_red_bit_count;
  uint m_green_bit_count;
  uint m_blue_bit_count;
  uint m_alpha_bit_count;
};

/** Checks if two color_format objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_GL_API bool
  operator==(const color_format& lhs, const color_format& rhs);

/** Checks if two color_format objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_GL_API bool operator!=(const color_format& lhs, const color_format& rhs);

/** Writes the object into a stream.
 *
 * \param os the stream.
 *
 * \param cf the color_format object.
 *
 * \return a reference to os.
 */
HOU_GL_API std::ostream& operator<<(std::ostream& os, const color_format& cf);

}  // namespace gl

}  // namespace hou

#endif
