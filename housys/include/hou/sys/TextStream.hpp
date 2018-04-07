// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_TEXT_STREAM_HPP
#define HOU_SYS_TEXT_STREAM_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/sys/Stream.hpp"

#include <ostream>



namespace hou
{

/** Text stream interface.
 */
class HOU_SYS_API TextStream
  : public Stream
{
public:
  /** Position indicator for a TextStream.
   *
   *  This class is not supposed to be instantiated manually, only a TextStream
   *  object can do so.
   *  Mixing TextPosition objects coming from different TextStream objects is
   *  undefined behaviour.
   */
  class HOU_SYS_API TextPosition
  {
  public:
    friend class TextStream;

    /** Checks if two text position indicators are equal.
     *
     *  \param lhs the left operand.
     *  \param rhs the right operand.
     *  \return the result of the check.
     */
    friend HOU_SYS_API bool operator==(TextPosition lhs, TextPosition rhs);

    /** Checks if two text position indicators are not equal.
     *
     *  \param lhs the left operand.
     *  \param rhs the right operand.
     *  \return the result of the check.
     */
    friend HOU_SYS_API bool operator!=(TextPosition lhs, TextPosition rhs);

    /** Writes a text position indicator into a stream.
     *
     *  \param os the stream.
     *  \param p the text position indicator.
     *  \return a reference to the stream.
     */
    friend HOU_SYS_API std::ostream& operator<<(std::ostream& os
      , TextPosition p);

  public:
    /** Text position indicator representing the beginning of the file.
     */
    static const TextPosition Start;

  private:
    TextPosition(long value);

  private:
    long mValue;
  };

public:
  /** Destructor.
   */
  virtual ~TextStream() {};

  /** Gets the current text position indicator.
   *
   *  \return the current text position indicator.
   */
  virtual TextPosition getTextPos() const = 0;

  /** Sets the current text position indicator.
   *
   *  \param pos the current text position indicator. It must either be Start or
   *  a value obtained by calling getTextPos on this stream. Using a value
   *  obtained by calling getTextPos on another TextStream is undefined
   *  behaviour.
   *  \return a reference to this stream.
   */
  virtual TextStream& setTextPos(TextPosition pos) = 0;

protected:
  /** Creates a TextPosition object with the given value.
   *
   *  Since the TextPosition object constructor is private, derived classes can
   *  use this utility function to create one if necessary.
   *
   *  \param value the value of the TextPosition object.
   */
  static TextPosition createPositionObject(long value);

  /** Converts a position object to an integer type.
   *
   *  If a derived class needs to convert a TextPosition into an integer, it can
   *  use this utility method.
   *
   *  \param pos the TextPosition object.
   *  \return the corresponding value of the TextPosition object as an integer
   *  type.
   */
  static long convertPositionObject(TextPosition pos);
};

}

#endif


