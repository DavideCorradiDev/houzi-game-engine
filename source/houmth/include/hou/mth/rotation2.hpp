// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_ROTATION_2_HPP
#define HOU_MTH_ROTATION_2_HPP

#include "hou/mth/mth_config.hpp"

#include "hou/mth/matrix_fwd.hpp"
#include "hou/mth/rotation2_fwd.hpp"

#include "hou/cor/pragmas.hpp"

#include <iostream>
#include <limits>



namespace hou
{

/** Represents a rotation in 2d space.
 *
 * The rotation is internally represented as an angle expressed in radians in
 * the range (-pi_f; Pi].
 *
 * \tparam T the scalar type.
 */
template <typename T>
class rotation2
{
public:
  template <typename OtherT>
  friend class rotation2;

public:
  /** Returns the identity rotation.
   *
   * \return the identity rotation.
   */
  static rotation2 identity() noexcept;

public:
  /** Creates an identity rotation.
   */
  rotation2() noexcept;

  /** Creates a rotation with the given rotation angle.
   *
   * \param angle the angle in radians.
   */
  explicit rotation2(T angle) noexcept;

  /** Creates a rotation with the given rotation matrix.
   *
   * Throws if the matrix is not a valid rotation matrix (determinant
   * equal to one and transpose equal to its inverse).
   *
   * \param m the rotation matrix.
   *
   * \throws hou::precondition_violation if m is not a valid rotation matrix
   * (determinat equal to 1 and inverse equal to its transpose).
   */
  explicit rotation2(const mat2x2<T>& m);

  /** Creates a rotation from a rotation with different scalar type.
   *
   * \tparam U the other scalar type.
   *
   * \param other the rotation to be copied.
   */
  template <typename U,
    typename Enable = std::enable_if_t<std::is_convertible<U, T>::value>>
  rotation2(const rotation2<U>& other) noexcept;

  /** Returns the rotation angle.
   *
   * The angle is expressed in radians and included in the range (-pi_f; Pi].
   *
   * \return the rotation angle.
   */
  T get_angle() const noexcept;

  /** Returns the rotation matrix.
   *
   * \return the rotation matrix.
   */
  mat2x2<T> get_matrix() const noexcept;

  /** Combines this rotation with the given rotation.
   *
   * \param rhs the rotation to be combined.
   *
   * \return a reference to this rotation after the combination.
   */
  rotation2& operator*=(const rotation2& rhs) noexcept;

  /** Inverts this rotation.
   *
   * \return a reference to this rotation after the inversion.
   */
  rotation2& invert() noexcept;

private:
  T m_angle;
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
rotation2<T> operator*(rotation2<T> lhs, const rotation2<T>& rhs) noexcept;

/** Computes the inverse of the given rotation.
 *
 * \tparam T the scalar type.
 *
 * \param r the rotation
 *
 * \return the inverse rotation.
 */
template <typename T>
rotation2<T> inverse(rotation2<T> r) noexcept;

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
bool operator==(const rotation2<T>& lhs, const rotation2<T>& rhs) noexcept;

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
bool operator!=(const rotation2<T>& lhs, const rotation2<T>& rhs) noexcept;

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
bool close(const rotation2<T>& lhs, const rotation2<T>& rhs,
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
std::ostream& operator<<(std::ostream& os, const rotation2<T>& r);



extern template class HOU_MTH_API rotation2<float>;
extern template class HOU_MTH_API rotation2<double>;

}  // namespace hou

#include "hou/mth/rotation2.inl"

#endif
