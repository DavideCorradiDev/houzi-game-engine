// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_ROTATION_2_HPP
#define HOU_MTH_ROTATION_2_HPP

#include "hou/mth/mth_export.hpp"

#include "hou/mth/matrix_fwd.hpp"
#include "hou/mth/rotation2_fwd.hpp"

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
class HOU_MTH_API rotation2
{
public:
  template <typename OtherT>
  friend class rotation2;

public:
  /** Returns the identity rotation.
   *
   * \return the identity rotation.
   */
  static rotation2 identity();

public:
  /** Creates an identity rotation.
   */
  rotation2();

  /** Creates a rotation with the given rotation angle.
   *
   * \param angle the angle in radians.
   */
  explicit rotation2(T angle);

  /** Creates a rotation with the given rotation matrix.
   *
   * Throws if the matrix is not a valid rotation matrix (determinant
   * equal to one and transpose equal to its inverse).
   *
   * \param m the rotation matrix.
   */
  explicit rotation2(const mat2x2<T>& m);

  /** Creates a rotation from a rotation with different scalar type.
   *
   * \tparam U the other scalar type.
   *
   * \param other the rotation to be copied.
   */
  template <typename U>
  HOU_MTH_API rotation2(const rotation2<U>& other);

  /** Returns the rotation angle.
   *
   * The angle is expressed in radians and included in the range (-pi_f; Pi].
   *
   * \return the rotation angle.
   */
  T get_angle() const;

  /** Returns the rotation matrix.
   *
   * \return the rotation matrix.
   */
  mat2x2<T> get_matrix() const;

  /** Combines this rotation with the given rotation.
   *
   * \param rhs the rotation to be combined.
   *
   * \return a reference to this rotation after the combination.
   */
  rotation2& operator*=(const rotation2& rhs);

  /** Inverts this rotation.
   *
   * \return a reference to this rotation after the inversion.
   */
  rotation2& invert();

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
HOU_MTH_API rotation2<T> operator*(rotation2<T> lhs, const rotation2<T>& rhs);

/** Computes the inverse of the given rotation.
 *
 * \tparam T the scalar type.
 *
 * \param r the rotation
 *
 * \return the inverse rotation.
 */
template <typename T>
HOU_MTH_API rotation2<T> inverse(rotation2<T> r);

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
HOU_MTH_API bool operator==(const rotation2<T>& lhs, const rotation2<T>& rhs);

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
HOU_MTH_API bool operator!=(const rotation2<T>& lhs, const rotation2<T>& rhs);

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
HOU_MTH_API bool close(const rotation2<T>& lhs, const rotation2<T>& rhs,
  T acc = std::numeric_limits<T>::epsilon());

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
HOU_MTH_API std::ostream& operator<<(std::ostream& os, const rotation2<T>& r);

}  // namespace hou

#endif
