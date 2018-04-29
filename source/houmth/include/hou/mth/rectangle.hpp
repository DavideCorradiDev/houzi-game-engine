// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_RECTANGLE_HPP
#define HOU_MTH_RECTANGLE_HPP

#include "hou/cor/basic_types.hpp"

#include "hou/mth/rectangle_fwd.hpp"
#include "hou/mth/matrix.hpp"

#include <iostream>
#include <limits>



namespace hou
{

/** Object representing an axis aligned ph_rectangle.
 *
 *  \tparam T the scalar type.
 */
template <typename T>
  class rectangle
{
public:
  /** Creates a ph_rectangle at position (0,0) with size (0,0).
   */
  rectangle();

  /** Creates a ph_rectangle with the given position and size.
   *
   *  \param position the position of the top-left ph_vertex of the ph_rectangle.
   *  \param size the length of the sides of the ph_rectangle on the x and y axes.
   */
  rectangle(const vec2<T>& position, const vec2<T>& size);

  /** Creates a ph_rectangle with given position and size.
   *
   *  \param x the x coordinate of the top-left ph_vertex of the ph_rectangle.
   *  \param y the y coordinate of the top-left ph_vertex of the ph_rectangle.
   *  \param w the length of the ph_rectangle on the x axis (width).
   *  \param h the length of the ph_rectangle on the y axis (height).
   */
  rectangle(T x, T y, T w, T h);

  /** Creates a ph_rectangle from a ph_rectangle with different scalar type.
   *
   *  \tparam U the other scalar type.
   *  \param other the ph_rectangle to be copied.
   */
  template <typename U>
    rectangle(const rectangle<U>& other);

  /** Retrieves the position of the top-left ph_vertex of the ph_rectangle.
   *
   *  \return the position of the top-left ph_vertex of the ph_rectangle.
   */
  const vec2<T>& get_position() const;

  /** Sets the position of the top-left ph_vertex of the ph_rectangle.
   *
   *  \param value the value to be assigned.
   */
  void set_position(const vec2<T>& value);

  /** Retrieves the size of the ph_rectangle on the x and y axes.
   *
   *  \return the size of the ph_rectangle on the x and y axes/
   */
  const vec2<T>& get_size() const;

  /** Sets the size of the ph_rectangle on the x and y axes.
   *
   *  \param value the value to be assigned.
   */
  void set_size(const vec2<T>& value);

  /** Retrieves a copy of the x position of the top-left ph_vertex of the ph_rectangle.
   *
   *  \return a copy of the x position of the top-left ph_vertex.
   */
  T x() const;

  /** Retrieves a reference to the x position of the top-left ph_vertex of the ph_rectangle.
   *
   *  \return a reference to the x position of the top-left ph_vertex.
   */
  T& x();

  /** Retrieves a copy of the y position of the top-left ph_vertex of the ph_rectangle.
   *
   *  \return a copy of the y position of the top-left ph_vertex.
   */
  T y() const;

  /** Retrieves a reference to the y position of the top-left ph_vertex of the ph_rectangle.
   *
   *  \return a reference to the y position of the top-left ph_vertex.
   */
  T& y();

  /** Retrieves the size of the ph_rectangle on the x axis.
   *
   *  \return the size of the ph_rectangle on the x axis.
   */
  T w() const;

  /** Retrieves a reference to the size of the ph_rectangle on the x axis.
   *
   *  \return a reference to the size on the x axis.
   */
  T& w();

  /** Retrieves a reference to the size of the ph_rectangle on the y axis.
   *
   *  \return a reference to the size on the y axis.
   */
  T h() const;

  /** Retrieves a reference to the size of the ph_rectangle on the y axis.
   *
   *  \return a reference to the size on the y axis.
   */
  T& h();

  /** Retrieves the coordinate of the left side of the ph_rectangle.
   *
   *  \return the coordinate of the left side of the ph_rectangle.
   */
  T l() const;

  /** Retrieves the coordinate of the top side of the ph_rectangle.
   *
   *  \return the coordinate of the top side of the ph_rectangle.
   */
  T t() const;

  /** Retrieves the coordinate of the right side of the ph_rectangle.
   *
   *  \return the coordinate of the right side of the ph_rectangle.
   */
  T r() const;

  /** Retrieves the coordinate of the bottom side of the ph_rectangle.
   *
   *  \return the coordinate of the bottom side of the ph_rectangle.
   */
  T b() const;

private:
  vec2<T> m_position;
  vec2<T> m_size;
};

/** Checks if two rectangles are equal.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the comparison.
 */
template <typename T>
  bool operator==(const rectangle<T>& lhs, const rectangle<T>& rhs);

/** Checks if two rectangles are not equal.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the comparison.
 */
template <typename T>
  bool operator!=(const rectangle<T>& lhs, const rectangle<T>& rhs);

/** Checks if two rectangles are equal with the given accuracy.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \param acc the accuracy used in the comparison.
 *  \return the result of the comparison.
 */
template <typename T>
  bool close(const rectangle<T>& lhs, const rectangle<T>& rhs
  , T acc = std::numeric_limits<T>::epsilon());

/** Writes the object into a ph_stream.
 *
 *  \tparam T the scalar type.
 *  \param os the ph_stream.
 *  \param rect the ph_rectangle.
 *  \return a reference to the ph_stream.
 */
template <typename T>
  std::ostream& operator<<(std::ostream& os, const rectangle<T>& rect);

/** Checks if a point lies inside a ph_rectangle.
 *
 *  \tparam T the scalar type.
 *  \param r the ph_rectangle.
 *  \param p the point.
 *  \return the result of the check.
 */
template <typename T>
  bool is_point_in_rectangle(const rectangle<T>& r, const vec2<T>& p);

}

#include "hou/mth/rectangle.inl"

#endif

