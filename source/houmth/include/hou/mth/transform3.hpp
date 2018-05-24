// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_TRANSFORM_3_HPP
#define HOU_MTH_TRANSFORM_3_HPP

#include "hou/mth/matrix.hpp"
#include "hou/mth/rotation3.hpp"
#include "hou/mth/transform3_fwd.hpp"

#include "hou/mth/mth_config.hpp"

#include <iostream>
#include <limits>



namespace hou
{

/** Transform in 3d space.
 *
 * It can be used to represent translation, rotation, scaling, shearing, or any
 * combination thereof.
 *
 * \tparam T the scalar type.
 */
template <typename T>
class HOU_MTH_API transform3
{
public:
  template <typename OtherT>
  friend class transform3;

public:
  /** Returns the identity transform.
   *
   * /return the identity transform.
   */
  static transform3 identity() noexcept;

  /** Creates a 3d transform representing a translation.
   *
   * \param translation the translation vector.
   *
   * \return a transform3 object representing the translation.
   */
  static transform3 translation(const vec3<T>& translation) noexcept;

  /** Creates a 3d transform representing a rotation.
   *
   * \param rotation the rotation.
   *
   * \return a transform3 object representing the rotation.
   */
  static transform3 rotation(const rot3<T>& rotation) noexcept;

  /** Creates a 3d transform representing a scaling transformation.
   *
   * \param scale the scaling factors.
   *
   * \return a transform3 object representing the scaling.
   */
  static transform3 scale(const vec3<T>& scale) noexcept;

  /** Creates a 3d transform representing a shearing transformation.
   *
   * \param sxy the x-y shear factor
   *
   * \param sxz the x-z shear factor
   *
   * \param syx the y-x shear factor
   *
   * \param syz the y-z shear factor
   *
   * \param szx the z-x shear factor
   *
   * \param szy the z-y shear factor
   *
   * \return a transform3 object representing the shearing.
   */
  static transform3 shear(T sxy, T sxz, T syx, T syz, T szx, T szy) noexcept;

public:
  /** Creates an identity transform.
   */
  transform3() noexcept;

  /** Creates a transform from a transform with a different scalar type.
   *
   * \tparam U the other scalar type.
   * \tparam Enable enabling parameter.
   *
   * \param other the transform to be converted.
   */
  template <typename U,
    typename Enable = std::enable_if_t<std::is_convertible<U, T>::value>>
  transform3(const transform3<U>& other) noexcept;

  /** Builds a homogeneous transformation matrix corresponding to the
   * transform.
   *
   * \return the homogeneous transformation matrix corresponding to the
   * transform.
   */
  mat4x4<T> to_mat4x4() const noexcept;

  /** Combines the transform with the given transform r.
   *
   * \param r the transform to be combined.
   *
   * \return a reference to the object after the combination.
   */
  transform3& operator*=(const transform3& r) noexcept;

  /** Inverts the transform.
   *
   * \return a reference to the object after the inversion.
   */
  transform3& invert();

  /** Transforms the given vector.
   *
   * \param vec the vector to be transformed.
   *
   * \return the transformed vector.
   */
  vec3<T> transform_vector(const vec3<T>& vec) const noexcept;

  /** Transforms the given point.
   *
   * \param point the point to be transformed.
   *
   * \return the transformed point.
   */
  vec3<T> transform_point(const vec3<T>& point) const noexcept;

  template <typename U>
  friend bool operator==(
    const transform3<U>& lhs, const transform3<U>& rhs) noexcept;

  template <typename U>
  friend bool operator!=(
    const transform3<U>& lhs, const transform3<U>& rhs) noexcept;

  template <typename U>
  friend bool close(
    const transform3<U>& lhs, const transform3<U>& rhs, U acc) noexcept;

private:
  transform3(const mat3x3<T>& r, const vec3<T>& t) noexcept;

private:
  mat3x3<T> m_mat;
  vec3<T> m_vec;
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
transform3<T> operator*(transform3<T> lhs, const transform3<T>& rhs) noexcept;

/** Computes the inverse of a transform.
 *
 * \tparam T the scalar type.
 *
 * \param t the transform to be inverted.
 *
 * \return the inverse transform.
 */
template <typename T>
transform3<T> inverse(transform3<T> t);

/** Checks if two transforms are equal.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operand of the comparison.
 *
 * \param rhs the right operand of the comparison.
 *
 * \return the result of the check.
 */
template <typename T>
bool operator==(const transform3<T>& lhs, const transform3<T>& rhs) noexcept;

/** Checks if two transforms are not equal.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operand of the comparison.
 *
 * \param rhs the right operand of the comparison.
 *
 * \return the result of the check.
 */
template <typename T>
bool operator!=(const transform3<T>& lhs, const transform3<T>& rhs) noexcept;

/** Checks if two transforms are equal with the specified accuracy.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operand of the comparison.
 *
 * \param rhs the right operand of the comparison.
 *
 * \param acc the accuracy.
 *
 * \return the result of the check.
 */
template <typename T>
bool close(const transform3<T>& lhs, const transform3<T>& rhs,
  T acc = std::numeric_limits<T>::epsilon()) noexcept;

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
std::ostream& operator<<(std::ostream& os, const transform3<T>& t);



extern template class HOU_MTH_API transform3<float>;
extern template class HOU_MTH_API transform3<double>;

}  // namespace hou

#include "hou/mth/transform3.inl"

#endif
