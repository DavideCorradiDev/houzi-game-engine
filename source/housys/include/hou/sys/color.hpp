// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_COLOR_HPP
#define HOU_SYS_COLOR_HPP

#include "hou/sys/sys_config.hpp"

#include <iostream>



namespace hou
{

/** Represents a color in rgba format.
 */
class HOU_SYS_API color
{
public:
  /** White color constant. */
  static const color& white() noexcept;

  /** Grey color constant. */
  static const color& grey() noexcept;

  /** Black color constant. */
  static const color& black() noexcept;

  /** Red color constant. */
  static const color& red() noexcept;

  /** Yellow color constant. */
  static const color& yellow() noexcept;

  /** Green color constant. */
  static const color& green() noexcept;

  /** Cyan color constant. */
  static const color& cyan() noexcept;

  /** Blue color constant. */
  static const color& blue() noexcept;

  /** Magenta color constant. */
  static const color& magenta() noexcept;

  /** Transparent color constant. */
  static const color& transparent() noexcept;

public:
  /** Creates a color object with the given rgba values.
   *
   * \param red the red value.
   *
   * \param green the green value.
   *
   * \param blue the blue value.
   *
   * \param alpha the alpha value.
   */
  color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) noexcept;

  /** Retrieves the red value as an integer between 0 and 255.
   *
   * \return the red value as an integer between 0 and 255.
   */
  uint8_t get_red() const noexcept;

  /** Retrieves the red value as a float between 0 and 1.
   *
   * \return the red value as a float between 0 and 1.
   */
  float get_red_f() const noexcept;

  /** Sets the red value.
   *
   * \param value the red value as an integer between 0 and 255.
   */
  void set_red(uint8_t value) noexcept;

  /** Sets the red value.
   *
   * \param value the red value as a float between 0 and 1.
   * Values outside this range are truncated.
   */
  void set_red_f(float value) noexcept;

  /** Retrieves the green value as an integer between 0 and 255.
   *
   * \return the green value as an integer between 0 and 255.
   */
  uint8_t get_green() const noexcept;

  /** Retrieves the green value as a float between 0 and 1.
   *
   * \return the green value as a float between 0 and 1.
   */
  float get_green_f() const noexcept;

  /** Sets the green value.
   *
   * \param value the green value as an integer between 0 and 255.
   */
  void set_green(uint8_t value) noexcept;

  /** Sets the green value.
   *
   * \param value the green value as a float between 0 and 1.
   * Values outside this range are truncated.
   */
  void set_green_f(float value) noexcept;

  /** Retrieves the blue value as an integer between 0 and 255.
   *
   * \return the blue value as an integer between 0 and 255.
   */
  uint8_t get_blue() const noexcept;

  /** Retrieves the blue value as a float between 0 and 1.
   *
   * \return the blue value as a float between 0 and 1.
   */
  float get_blue_f() const noexcept;

  /** Sets the blue value.
   *
   * \param value the blue value as an integer between 0 and 255.
   */
  void set_blue(uint8_t value) noexcept;

  /** Sets the blue value.
   *
   * \param value the blue value as a float between 0 and 1.
   * Values outside this range are truncated.
   */
  void set_blue_f(float value) noexcept;

  /** Retrieves the alpha value as an integer between 0 and 255.
   *
   * \return the alpha value as an integer between 0 and 255.
   */
  uint8_t get_alpha() const noexcept;

  /** Retrieves the alpha value as a float between 0 and 1.
   *
   * \return the alpha value as a float between 0 and 1.
   */
  float get_alpha_f() const noexcept;

  /** Sets the alpha value.
   *
   * \param value the alpha value as an integer between 0 and 255.
   */
  void set_alpha(uint8_t value) noexcept;

  /** Sets the alpha value.
   *
   * \param value the alpha value as a float between 0 and 1.
   * Values outside this range are truncated.
   */
  void set_alpha_f(float value) noexcept;

private:
  uint8_t m_red;
  uint8_t m_green;
  uint8_t m_blue;
  uint8_t m_alpha;
};

/** Checks if two color objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator==(const color& lhs, const color& rhs) noexcept;

/** Checks if two color objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator!=(const color& lhs, const color& rhs) noexcept;

/** Writes a color object into a stream.
 *
 * \param os the stream.
 *
 * \param c the color object.
 *
 * \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, const color& c);

}  // namespace hou

#endif
