// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_RECTANGLE_HPP
#define HOU_MTH_RECTANGLE_HPP

#include "hou/mth/matrix.hpp"
#include "hou/mth/rectangle_fwd.hpp"

#include "hou/mth/mth_config.hpp"

#include "hou/cor/checked_variable.hpp"

#include <iostream>
#include <limits>



namespace hou
{

/**
 * Object representing an axis aligned rectangle.
 *
 * \tparam ScalPosT scalar position type.
 *
 * \tparam ScalSizeT scalar size type.
 */
template <typename ScalPosT, typename ScalSizeT>
class rectangle
{
  static_assert(std::is_convertible<ScalSizeT, ScalPosT>::value,
    "ScalSizeT must be convertible to ScalPosT");

public:
  using scalar_position_type = ScalPosT;
  using scalar_size_type = ScalSizeT;
  using position_type = vec2<scalar_position_type>;
  using size_type = vec2<scalar_size_type>;

public:
  /**
   * Creates a rectangle at position (0,0) with size (0,0).
   */
  constexpr rectangle() noexcept;

  /**
   * Creates a rectangle with the given position and size.
   *
   * \param position the position of the top-left vertex of the rectangle.
   *
   * \param size the length of the sides of the rectangle on the x and y axes.
   */
  constexpr rectangle(
    const position_type& position, const size_type& size) noexcept;

  /**
   * Creates a rectangle with given position and size.
   *
   * \param x the x coordinate of the top-left vertex of the rectangle.
   *
   * \param y the y coordinate of the top-left vertex of the rectangle.
   *
   * \param w the length of the rectangle on the x axis (width).
   *
   * \param h the length of the rectangle on the y axis (height).
   */
  constexpr rectangle(scalar_position_type x, scalar_position_type y,
    scalar_size_type w, scalar_size_type h) noexcept;

  /**
   * Creates a rectangle from a rectangle with different scalar type.
   *
   *  \tparam OtherScalPosT the other scalar position type.
   *
   *  \tparam OtherScalSizeT the other scalar size type.
   *
   * \tparam Enable enabling parameter.
   *
   * \param other the rectangle to be copied.
   */
  template <typename OtherScalPosT, typename OtherScalSizeT,
    typename Enable
    = std::enable_if_t<std::is_convertible<OtherScalPosT, ScalPosT>::value
      && std::is_convertible<OtherScalSizeT, ScalSizeT>::value>>
  constexpr rectangle(
    const rectangle<OtherScalPosT, OtherScalSizeT>& other) noexcept;

  /**
   * Retrieves the position of the top-left vertex of the rectangle.
   *
   * \return the position of the top-left vertex of the rectangle.
   */
  constexpr const position_type& get_position() const noexcept;

  /**
   * Sets the position of the top-left vertex of the rectangle.
   *
   * \param value the value to be assigned.
   */
  constexpr void set_position(const position_type& value) noexcept;

  /**
   * Retrieves the size of the rectangle on the x and y axes.
   *
   * \return the size of the rectangle on the x and y axes/
   */
  constexpr const size_type& get_size() const noexcept;

  /**
   * Sets the size of the rectangle on the x and y axes.
   *
   * \param value the value to be assigned.
   */
  constexpr void set_size(const size_type& value) noexcept;

  /**
   * Retrieves a copy of the x position of the top-left vertex of the
   * rectangle.
   *
   * \return a copy of the x position of the top-left vertex.
   */
  constexpr scalar_position_type x() const noexcept;

  /**
   * Retrieves a reference to the x position of the top-left vertex of the
   * rectangle.
   *
   * \return a reference to the x position of the top-left vertex.
   */
  constexpr scalar_position_type& x() noexcept;

  /**
   * Retrieves a copy of the y position of the top-left vertex of the
   * rectangle.
   *
   * \return a copy of the y position of the top-left vertex.
   */
  constexpr scalar_position_type y() const noexcept;

  /**
   * Retrieves a reference to the y position of the top-left vertex of the
   * rectangle.
   *
   * \return a reference to the y position of the top-left vertex.
   */
  constexpr scalar_position_type& y() noexcept;

  /**
   * Retrieves the size of the rectangle on the x axis.
   *
   * \return the size of the rectangle on the x axis.
   */
  constexpr scalar_size_type w() const noexcept;

  /**
   * Retrieves a reference to the size of the rectangle on the x axis.
   *
   * \return a reference to the size on the x axis.
   */
  constexpr scalar_size_type& w() noexcept;

  /**
   * Retrieves a reference to the size of the rectangle on the y axis.
   *
   * \return a reference to the size on the y axis.
   */
  constexpr scalar_size_type h() const noexcept;

  /**
   * Retrieves a reference to the size of the rectangle on the y axis.
   *
   * \return a reference to the size on the y axis.
   */
  constexpr scalar_size_type& h() noexcept;

  /**
   * Retrieves the coordinate of the left side of the rectangle.
   *
   * \return the coordinate of the left side of the rectangle.
   */
  constexpr scalar_position_type l() const noexcept;

  /**
   * Retrieves the coordinate of the top side of the rectangle.
   *
   * \return the coordinate of the top side of the rectangle.
   */
  constexpr scalar_position_type t() const noexcept;

  /**
   * Retrieves the coordinate of the right side of the rectangle.
   *
   * \return the coordinate of the right side of the rectangle.
   */
  constexpr scalar_position_type r() const noexcept;

  /**
   * Retrieves the coordinate of the bottom side of the rectangle.
   *
   * \return the coordinate of the bottom side of the rectangle.
   */
  constexpr scalar_position_type b() const noexcept;

private:
  position_type m_position;
  size_type m_size;
};

/**
 * Checks if two rectangles are equal.
 *
 * \tparam ScalPosT scalar position type.
 *
 * \tparam ScalSizeT scalar size type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the comparison.
 */
template <typename ScalPosT, typename ScalSizeT>
constexpr bool operator==(const rectangle<ScalPosT, ScalSizeT>& lhs,
  const rectangle<ScalPosT, ScalSizeT>& rhs) noexcept;

/**
 * Checks if two rectangles are not equal.
 *
 * \tparam ScalPosT scalar position type.
 *
 * \tparam ScalSizeT scalar size type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the comparison.
 */
template <typename ScalPosT, typename ScalSizeT>
constexpr bool operator!=(const rectangle<ScalPosT, ScalSizeT>& lhs,
  const rectangle<ScalPosT, ScalSizeT>& rhs) noexcept;

/**
 * Checks if two rectangles are equal with the given accuracy.
 *
 * \tparam ScalPosT scalar position type.
 *
 * \tparam ScalSizeT scalar size type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \param acc the accuracy used in the comparison.
 *
 * \return the result of the comparison.
 */
template <typename ScalPosT, typename ScalSizeT>
constexpr bool close(const rectangle<ScalPosT, ScalSizeT>& lhs,
  const rectangle<ScalPosT, ScalSizeT>& rhs, ScalPosT posAcc,
  ScalSizeT sizeAcc) noexcept;

/**
 * Checks if two rectangles are equal with the given accuracy.
 *
 * \tparam ScalPosT scalar position type.
 *
 * \tparam ScalSizeT scalar size type.
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
constexpr bool close(const rectangle<T, T>& lhs, const rectangle<T, T>& rhs,
  T acc = std::numeric_limits<T>::epsilon()) noexcept;

/**
 * Writes the object into a stream.
 *
 * \tparam ScalPosT scalar position type.
 *
 * \tparam ScalSizeT scalar size type.
 *
 * \param os the stream.
 *
 * \param rect the rectangle.
 *
 * \return a reference to the stream.
 */
template <typename ScalPosT, typename ScalSizeT>
std::ostream& operator<<(
  std::ostream& os, const rectangle<ScalPosT, ScalSizeT>& rect);

/**
 * Checks if a point lies inside a rectangle.
 *
 * \tparam ScalPosT scalar position type.
 *
 * \tparam ScalSizeT scalar size type.
 *
 * \param r the rectangle.
 *
 * \param p the point.
 *
 * \return the result of the check.
 */
template <typename ScalPosT, typename ScalSizeT>
constexpr bool is_point_in_rectangle(const rectangle<ScalPosT, ScalSizeT>& r,
  const typename rectangle<ScalPosT, ScalSizeT>::position_type & p) noexcept;

}  // namespace hou

#include "hou/mth/rectangle.inl"

#endif
