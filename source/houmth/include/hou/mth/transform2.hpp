// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_TRANSFORM_2_HPP
#define HOU_MTH_TRANSFORM_2_HPP

#include "hou/mth/matrix.hpp"
#include "hou/mth/rectangle_fwd.hpp"
#include "hou/mth/rotation2_fwd.hpp"
#include "hou/mth/transform2_fwd.hpp"

#include "hou/mth/mth_config.hpp"

#include <iostream>
#include <limits>



namespace hou
{

/** Transform in 2d space.
 *
 * It can be used to represent translation, rotation, scaling, shearing, or any
 * combination thereof.
 *
 * \tparam T the scalar type.
 */
template <typename T>
class HOU_MTH_API transform2
{
public:
  template <typename OtherT>
  friend class transform2;

public:
  /** Returns the identity transform.
   *
   * /return the identity transform.
   */
  static transform2 identity() noexcept;

  /** Creates a 2d transform representing a translation.
   *
   * \param translation the translation vector.
   *
   * \return a transform2 object representing the translation.
   */
  static transform2 translation(const vec2<T>& translation) noexcept;

  /** Creates a 2d transform representing a rotation.
   *
   * \param rotation the rotation.
   *
   * \return a transform2 object representing the rotation.
   */
  static transform2 rotation(const rot2<T>& rotation) noexcept;

  /** Creates a 2d transform representing a scaling transformation.
   *
   * \param scale the scaling factors.
   *
   * \return a transform2 object representing the scaling.
   */
  static transform2 scale(const vec2<T>& scale) noexcept;

  /** Creates a 2d transform representing a shearing transformation.
   *
   * \param sxy the horizontal shear factor.
   *
   * \param syx the vertical shear factor.
   *
   * \return a transform2 object representing the shearing.
   */
  static transform2 shear(T sxy, T syx) noexcept;

  /** Creates a 2d transform representing an ortographic transform.
   *
   * The transform transforms from the rect specified by clipping plane into
   * a rect with normalized coordinates going from -1 to +1.
   *
   * \param clipping_plane the rectangle to be transformed into normalized
   * coordinates.
   *
   * \return a transform2 object representing the ortographic projection.
   */
  static transform2 orthographic_projection(
    const rect<T>& clipping_plane) noexcept;

public:
  /** Creates an identity transform.
   */
  transform2() noexcept;

  /** Creates a transform from a transform with a different scalar type.
   *
   * \tparam U the other scalar type.
   * \tparam Enable enabling parameter.
   *
   * \param other the transform to be converted.
   */
  template <typename U,
    typename Enable = std::enable_if_t<std::is_convertible<U, T>::value>>
  HOU_MTH_API transform2(const transform2<U>& other) noexcept;

  /** Builds a homogeneous transformation matrix corresponding to the
   * transform.
   *
   * \return the homogeneous transformation matrix corresponding to the
   * transform.
   */
  mat4x4<T> to_mat4x4() const noexcept;

  /** Combines the transform with the given transform r.
   *
   * \param rhs the transform to be combined.
   *
   * \return a reference to the object after the combination.
   */
  transform2& operator*=(const transform2& rhs) noexcept;

  /** Inverts the transform.
   *
   * \return a reference to the object after the inversion.
   */
  transform2& invert();

  /** Transforms the given vector.
   *
   * \param vec the vector to be transformed.
   *
   * \return the transformed vector.
   */
  vec2<T> transform_vector(const vec2<T>& vec) const noexcept;

  /** Transforms the given point.
   *
   * \param point the point to be transformed.
   *
   * \return the transformed point.
   */
  vec2<T> transform_point(const vec2<T>& point) const noexcept;

  /** Checks if two transforms are equal.
   *
   * \param lhs the left operand of the comparison.
   *
   * \param rhs the right operand of the comparison.
   *
   * \return the result of the check.
   */
  friend constexpr bool operator==(
    const transform2& lhs, const transform2& rhs) noexcept
  {
    return lhs.m_mat == rhs.m_mat && lhs.m_vec == rhs.m_vec;
  }

  /** Checks if two transforms are not equal.
   *
   * \param lhs the left operand of the comparison.
   *
   * \param rhs the right operand of the comparison.
   *
   * \return the result of the check.
   */
  friend constexpr bool operator!=(
    const transform2& lhs, const transform2& rhs) noexcept
  {
    return !(lhs == rhs);
  }

  /** Checks if two transforms are equal with the specified accuracy.
   *
   * \param lhs the left operand of the comparison.
   *
   * \param rhs the right operand of the comparison.
   *
   * \param acc the accuracy.
   *
   * \return the result of the check.
   */
  friend constexpr bool close(const transform2& lhs, const transform2& rhs,
    T acc = std::numeric_limits<T>::epsilon()) noexcept
  {
    return close(lhs.m_mat, rhs.m_mat, acc) && close(lhs.m_vec, rhs.m_vec, acc);
  }

private:
  transform2(const mat2x2<T>& r, const vec2<T>& t) noexcept;

private:
  mat2x2<T> m_mat;
  vec2<T> m_vec;
};

/** Combines two transforms.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the combined transform.
 */
template <typename T>
HOU_MTH_API transform2<T> operator*(
  transform2<T> lhs, const transform2<T>& rhs) noexcept;

/** Computes the inverse of a transform.
 *
 * \tparam T the scalar type.
 *
 * \param t the transform to be inverted.
 *
 * \return the inverse transform.
 */
template <typename T>
HOU_MTH_API transform2<T> inverse(transform2<T> t);

/** Writes the object into a stream.
 *
 * \tparam T the scalar type.
 *
 * \param os the stream.
 *
 * \param t the transform.
 *
 * \return a reference to the stream.
 */
template <typename T>
HOU_MTH_API std::ostream& operator<<(std::ostream& os, const transform2<T>& t);

}  // namespace hou

#endif