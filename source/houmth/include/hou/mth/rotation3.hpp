// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_ROTATION_3_HPP
#define HOU_MTH_ROTATION_3_HPP

#include "hou/mth/mth_config.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/quaternion.hpp"
#include "hou/mth/rotation3_fwd.hpp"

#include <iostream>
#include <limits>



namespace hou
{

/** Represents a rotation in 2d space.
 *
 * The rotation is internally represented as a unit quaternion.
 *
 * \tparam T the scalar type.
 */
template <typename T>
class rotation3
{
public:
  template <typename OtherT>
  friend class rotation3;

public:
  /** The value type. */
  using value_type = T;

public:
  /** Returns the identity rotation.
   *
   * \return the identity rotation.
   */
  static const rotation3& identity() noexcept;

  /** Returns a rotation around the x axis with the given angle.
   *
   * \param angle the angle in radians.
   *
   * \return the rotation around the x axis.
   */
  static constexpr rotation3 x(T angle) noexcept;

  /** Returns a rotation around the y axis with the given angle.
   *
   * \param angle the angle in radians.
   *
   * \return the rotation around the y axis.
   */
  static constexpr rotation3 y(T angle) noexcept;

  /** Returns a rotation around the z axis with the given angle.
   *
   * \param angle the angle in radians.
   *
   * \return the rotation around the z axis.
   */
  static constexpr rotation3 z(T angle) noexcept;

public:
  /** Creates an identity rotation.
   */
  constexpr rotation3() noexcept;

  /** Creates a rotation with the given quaternion
   *
   * The quaternion will be normalized if it is not.
   *
   * \param q the quaternion.
   *
   * \throws hou::precondition_violation the norm of q is equal to 0.
   */
  explicit constexpr rotation3(const quaternion<T>& q);

  /** Creates a rotation with the given vector.
   *
   * The direction of the vector represents the axis of rotation and its
   * magnitude represents the angle of rotation in radians.
   *
   * \param v the vector representing the axis and angle of rotation.
   */
  explicit constexpr rotation3(const vec3<T>& v);

  /** Creates a rotation with the given rotation matrix.
   *
   * If m is not a valid rotation matrix, the matrix will be converted to a
   * quaternion which will then be normalized. This will result in a valid
   * rotation, whose rotation matrix is a different one from the one provided.
   * The caller must therefore ensure that m is a valid rotation matrix.
   *
   * \param m the rotation matrix.
   */
  explicit constexpr rotation3(const mat3x3<T>& m);

  /** Creates a rotation from a rotation with different scalar type.
   *
   * \tparam U the other scalar type.
   *
   * \param other the rotation to be copied.
   */
  template <typename U,
    typename Enable = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr rotation3(const rotation3<U>& other) noexcept;

  /** Returns a quaternion representing the rotation.
   *
   * \return a quaternion representing the rotation.
   */
  constexpr const quaternion<T>& get_quaternion() const noexcept;

  /** Returns a vector representing the rotation.
   *
   * \return a vector representing the rotation.
   */
  constexpr vec3<T> get_vector() const noexcept;

  /** Returns a rotatin matrix representing the rotation.
   *
   * \return a matrix representing the rotation.
   */
  constexpr mat3x3<T> get_matrix() const noexcept;

  /** Combines this rotation with the given rotation.
   *
   * \param rhs the rotation to be combined.
   *
   * \return a reference to this rotation after the combination.
   */
  constexpr rotation3& operator*=(const rotation3& rhs);

  /** Inverts this rotation.
   *
   * \return a reference to this rotation after the inversion.
   */
  constexpr rotation3& invert();

private:
  static constexpr quaternion<T> to_quaternion(vec3<T> v) noexcept;

  static constexpr quaternion<T> to_quaternion(const mat3x3<T>& m) noexcept;

  static constexpr vec3<T> to_vector(const quaternion<T>& q) noexcept;

  static constexpr mat3x3<T> to_matrix(const quaternion<T>& q) noexcept;

private:
  quaternion<T> m_quaternion;
};

/** Computes the combination of two rotations.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return a rotation representing the two combined rotations.
 */
template <typename T>
constexpr rotation3<T> operator*(rotation3<T> lhs, const rotation3<T>& rhs);

/** Computes the inverse of the given rotation.
 *
 * \tparam T the scalar type.
 *
 * \param r the rotation
 *
 * \return the inverse rotation.
 */
template <typename T>
constexpr rotation3<T> inverse(rotation3<T> r);

/** Checks if two rotations are equal.
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
  const rotation3<T>& lhs, const rotation3<T>& rhs) noexcept;

/** Checks if two rotations are not equal.
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
  const rotation3<T>& lhs, const rotation3<T>& rhs) noexcept;

/** Checks if two rotations are equal with the given accuracy.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \param acc the accuracy of the comparison.
 *
 * \return the result of the comparison.
 */
template <typename T>
constexpr bool close(const rotation3<T>& lhs, const rotation3<T>& rhs,
  T acc = std::numeric_limits<T>::epsilon()) noexcept;

/** Writes the object into a stream.
 *
 * \tparam T the scalar type.
 *
 * \param os the output stream.
 *
 * \param r the rotation.
 *
 * \return a reference to the stream.
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const rotation3<T>& r);

}  // namespace hou



#include "hou/mth/rotation3.inl"

#endif
