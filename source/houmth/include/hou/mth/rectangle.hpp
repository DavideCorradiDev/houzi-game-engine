// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_RECTANGLE_HPP
#define HOU_MTH_RECTANGLE_HPP

#include "hou/mth/matrix.hpp"
#include "hou/mth/rectangle_fwd.hpp"

#include "hou/mth/mth_config.hpp"

#include <iostream>
#include <limits>



namespace hou
{

/** Object representing an axis aligned rectangle.
 *
 *  \tparam T the scalar type.
 */
template <typename T>
class rectangle
{
public:
  /** Creates a rectangle at position (0,0) with size (0,0).
   */
  constexpr rectangle() noexcept;

  /** Creates a rectangle with the given position and size.
   *
   * \param position the position of the top-left vertex of the rectangle.
   *
   * \param size the length of the sides of the rectangle on the x and y axes.
   */
  constexpr rectangle(const vec2<T>& position, const vec2<T>& size) noexcept;

  /** Creates a rectangle with given position and size.
   *
   * \param x the x coordinate of the top-left vertex of the rectangle.
   *
   * \param y the y coordinate of the top-left vertex of the rectangle.
   *
   * \param w the length of the rectangle on the x axis (width).
   *
   * \param h the length of the rectangle on the y axis (height).
   */
  constexpr rectangle(T x, T y, T w, T h) noexcept;

  /** Creates a rectangle from a rectangle with different scalar type.
   *
   * \tparam U the other scalar type.
   *
   * \tparam Enable enabling parameter.
   *
   * \param other the rectangle to be copied.
   */
  template <typename U,
    typename Enable = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr rectangle(const rectangle<U>& other) noexcept;

  /** Retrieves the position of the top-left vertex of the rectangle.
   *
   * \return the position of the top-left vertex of the rectangle.
   */
  constexpr const vec2<T>& get_position() const noexcept;

  /** Sets the position of the top-left vertex of the rectangle.
   *
   * \param value the value to be assigned.
   */
  constexpr void set_position(const vec2<T>& value) noexcept;

  /** Retrieves the size of the rectangle on the x and y axes.
   *
   * \return the size of the rectangle on the x and y axes/
   */
  constexpr const vec2<T>& get_size() const noexcept;

  /** Sets the size of the rectangle on the x and y axes.
   *
   * \param value the value to be assigned.
   */
  constexpr void set_size(const vec2<T>& value) noexcept;

  /** Retrieves a copy of the x position of the top-left vertex of the
   * rectangle.
   *
   * \return a copy of the x position of the top-left vertex.
   */
  constexpr T x() const noexcept;

  /** Retrieves a reference to the x position of the top-left vertex of the
   * rectangle.
   *
   * \return a reference to the x position of the top-left vertex.
   */
  constexpr T& x() noexcept;

  /** Retrieves a copy of the y position of the top-left vertex of the
   * rectangle.
   *
   * \return a copy of the y position of the top-left vertex.
   */
  constexpr T y() const noexcept;

  /** Retrieves a reference to the y position of the top-left vertex of the
   * rectangle.
   *
   * \return a reference to the y position of the top-left vertex.
   */
  constexpr T& y() noexcept;

  /** Retrieves the size of the rectangle on the x axis.
   *
   * \return the size of the rectangle on the x axis.
   */
  constexpr T w() const noexcept;

  /** Retrieves a reference to the size of the rectangle on the x axis.
   *
   * \return a reference to the size on the x axis.
   */
  constexpr T& w() noexcept;

  /** Retrieves a reference to the size of the rectangle on the y axis.
   *
   * \return a reference to the size on the y axis.
   */
  constexpr T h() const noexcept;

  /** Retrieves a reference to the size of the rectangle on the y axis.
   *
   * \return a reference to the size on the y axis.
   */
  constexpr T& h() noexcept;

  /** Retrieves the coordinate of the left side of the rectangle.
   *
   * \return the coordinate of the left side of the rectangle.
   */
  constexpr T l() const noexcept;

  /** Retrieves the coordinate of the top side of the rectangle.
   *
   * \return the coordinate of the top side of the rectangle.
   */
  constexpr T t() const noexcept;

  /** Retrieves the coordinate of the right side of the rectangle.
   *
   * \return the coordinate of the right side of the rectangle.
   */
  constexpr T r() const noexcept;

  /** Retrieves the coordinate of the bottom side of the rectangle.
   *
   * \return the coordinate of the bottom side of the rectangle.
   */
  constexpr T b() const noexcept;

private:
  vec2<T> m_position;
  vec2<T> m_size;
};

/** Checks if two rectangles are equal.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the comparison.
 */
template <typename T>
constexpr bool operator==(
  const rectangle<T>& lhs, const rectangle<T>& rhs) noexcept;

/** Checks if two rectangles are not equal.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the comparison.
 */
template <typename T>
constexpr bool operator!=(
  const rectangle<T>& lhs, const rectangle<T>& rhs) noexcept;

/** Checks if two rectangles are equal with the given accuracy.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \param acc the accuracy used in the comparison.
 *
 * \return the result of the comparison.
 */
template <typename T>
constexpr bool close(const rectangle<T>& lhs, const rectangle<T>& rhs,
  T acc = std::numeric_limits<T>::epsilon()) noexcept;

/** Writes the object into a stream.
 *
 * \tparam T the scalar type.
 *
 * \param os the stream.
 *
 * \param rect the rectangle.
 *
 * \return a reference to the stream.
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const rectangle<T>& rect);

/** Checks if a point lies inside a rectangle.
 *
 * \tparam T the scalar type.
 *
 * \param r the rectangle.
 *
 * \param p the point.
 *
 * \return the result of the check.
 */
template <typename T>
constexpr bool is_point_in_rectangle(
  const rectangle<T>& r, const vec2<T>& p) noexcept;

}  // namespace hou

#include "hou/mth/rectangle.inl"

#endif
