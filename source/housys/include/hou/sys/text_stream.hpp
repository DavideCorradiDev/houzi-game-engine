// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_TEXT_STREAM_HPP
#define HOU_SYS_TEXT_STREAM_HPP

#include "hou/sys/stream.hpp"

#include "hou/sys/sys_config.hpp"

#include <ostream>



namespace hou
{

/** text stream interface.
 */
class HOU_SYS_API text_stream : public stream
{
public:
  /** Position indicator for a text_stream.
   *
   * This class is not supposed to be instantiated manually, only a text_stream
   * object can do so.
   * Mixing text_position objects coming from different text_stream objects is
   * undefined behaviour.
   */
  class HOU_SYS_API text_position
  {
  public:
    friend class text_stream;

    /** Checks if two text position indicators are equal.
     *
     * \param lhs the left operand.
     *
     * \param rhs the right operand.
     *
     * \return the result of the check.
     */
    friend HOU_SYS_API bool operator==(
      text_position lhs, text_position rhs) noexcept;

    /** Checks if two text position indicators are not equal.
     *
     * \param lhs the left operand.
     *
     * \param rhs the right operand.
     *
     * \return the result of the check.
     */
    friend HOU_SYS_API bool operator!=(
      text_position lhs, text_position rhs) noexcept;

    /** Writes a text position indicator into a stream.
     *
     * \param os the stream.
     *
     * \param p the text position indicator.
     *
     * \return a reference to the stream.
     */
    friend HOU_SYS_API std::ostream& operator<<(
      std::ostream& os, text_position p);

  public:
    /** text position indicator representing the beginning of the file.
     */
    static const text_position start;

  private:
    text_position(long value) noexcept;

  private:
    long mValue;
  };

public:
  /** Gets the current text position indicator.
   *
   * \throws hou::cursor_error in case of an error.
   *
   * \return the current text position indicator.
   */
  virtual text_position get_text_pos() const = 0;

  /** Sets the current text position indicator.
   *
   * \param pos the current text position indicator. It must either be start or
   * a value obtained by calling get_text_pos on this stream. Using a value
   * obtained by calling get_text_pos on another text_stream is undefined
   * behaviour.
   *
   * \throws hou::cursor_error in case of an error.
   *
   * \return a reference to this stream.
   */
  virtual text_stream& set_text_pos(text_position pos) = 0;

protected:
  /** Creates a text_position object with the given value.
   *
   * Since the text_position object constructor is private, derived classes can
   * use this utility function to create one if necessary.
   *
   * \param value the value of the text_position object.
   */
  static text_position create_position_object(long value) noexcept;

  /** Converts a position object to an integer type.
   *
   * If a derived class needs to convert a text_position into an integer, it can
   * use this utility method.
   *
   * \param pos the text_position object.
   *
   * \return the corresponding value of the text_position object as an integer
   * type.
   */
  static long convert_position_object(text_position pos) noexcept;
};

}  // namespace hou

#endif
