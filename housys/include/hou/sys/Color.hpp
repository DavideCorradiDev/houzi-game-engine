// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_COLOR_HPP
#define HOU_SYS_COLOR_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/cor/BasicTypes.hpp"

#include <iostream>



namespace hou
{

/** Represents a color in RGBA format.
 */
class HOU_SYS_API Color
{
public:
  /** White color constant. */
  static const Color White;

  /** Grey color constant. */
  static const Color Grey;

  /** Black color constant. */
  static const Color Black;

  /** Red color constant. */
  static const Color Red;

  /** Yellow color constant. */
  static const Color Yellow;

  /** Green color constant. */
  static const Color Green;

  /** Cyan color constant. */
  static const Color Cyan;

  /** Blue color constant. */
  static const Color Blue;

  /** Magenta color constant. */
  static const Color Magenta;

  /** Transparent color constant. */
  static const Color Transparent;

public:
  /** Creates a Color object with the given RGBA values.
   *
   *  \param red the red value.
   *  \param green the green value.
   *  \param blue the blue value.
   *  \param alpha the alpha value.
   */
  Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

  /** Retrieves the red value as an integer between 0 and 255.
   *
   *  \return the red value as an integer between 0 and 255.
   */
  uint8_t getRed() const;

  /** Retrieves the red value as a float between 0 and 1.
   *
   *  \return the red value as a float between 0 and 1.
   */
  float getRedf() const;

  /** Sets the red value.
   *
   *  \param value the red value as an integer between 0 and 255.
   */
  void setRed(uint8_t value);

  /** Sets the red value.
   *
   *  \param value the red value as a float between 0 and 1.
   *  Values outside this range are truncated.
   */
  void setRedf(float value);

  /** Retrieves the green value as an integer between 0 and 255.
   *
   *  \return the green value as an integer between 0 and 255.
   */
  uint8_t getGreen() const;

  /** Retrieves the green value as a float between 0 and 1.
   *
   *  \return the green value as a float between 0 and 1.
   */
  float getGreenf() const;

  /** Sets the green value.
   *
   *  \param value the green value as an integer between 0 and 255.
   */
  void setGreen(uint8_t value);

  /** Sets the green value.
   *
   *  \param value the green value as a float between 0 and 1.
   *  Values outside this range are truncated.
   */
  void setGreenf(float value);

  /** Retrieves the blue value as an integer between 0 and 255.
   *
   *  \return the blue value as an integer between 0 and 255.
   */
  uint8_t getBlue() const;

  /** Retrieves the blue value as a float between 0 and 1.
   *
   *  \return the blue value as a float between 0 and 1.
   */
  float getBluef() const;

  /** Sets the blue value.
   *
   *  \param value the blue value as an integer between 0 and 255.
   */
  void setBlue(uint8_t value);

  /** Sets the blue value.
   *
   *  \param value the blue value as a float between 0 and 1.
   *  Values outside this range are truncated.
   */
  void setBluef(float value);

  /** Retrieves the alpha value as an integer between 0 and 255.
   *
   *  \return the alpha value as an integer between 0 and 255.
   */
  uint8_t getAlpha() const;

  /** Retrieves the alpha value as a float between 0 and 1.
   *
   *  \return the alpha value as a float between 0 and 1.
   */
  float getAlphaf() const;

  /** Sets the alpha value.
   *
   *  \param value the alpha value as an integer between 0 and 255.
   */
  void setAlpha(uint8_t value);

  /** Sets the alpha value.
   *
   *  \param value the alpha value as a float between 0 and 1.
   *  Values outside this range are truncated.
   */
  void setAlphaf(float value);

private:
  uint8_t mRed;
  uint8_t mGreen;
  uint8_t mBlue;
  uint8_t mAlpha;
};

/** Checks if two Color objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const Color& lhs, const Color& rhs);

/** Checks if two Color objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const Color& lhs, const Color& rhs);

/** Writes a Color object into a stream.
 *
 *  \param os the stream.
 *  \param c the Color object.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, const Color& c);

}

#endif

