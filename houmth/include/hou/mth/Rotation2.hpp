// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_MTH_ROTATION_2_HPP
#define HOU_MTH_ROTATION_2_HPP

#include "hou/mth/MthExport.hpp"

#include "hou/mth/MatrixFwd.hpp"
#include "hou/mth/Rotation2Fwd.hpp"

#include <iostream>
#include <limits>



namespace hou
{

/** Represents a rotation in 2d space.
 *
 *  The rotation is internally represented as an angle expressed in radians in
 *  the range (-PI_F; Pi].
 *
 *  \tparam T the scalar type.
 */
template <typename T>
  class HOU_MTH_API Rotation2
{
public:
  template <typename otherT> friend class Rotation2;

public:
  /** Returns the identity rotation.
   *
   *  \return the identity rotation.
   */
  static Rotation2 identity();

public:
  /** Creates an identity rotation.
   */
  Rotation2();

  /** Creates a rotation with the given rotation angle.
   *
   *  \param angle the angle in radians.
   */
  explicit Rotation2(T angle);

  /** Creates a rotation with the given rotation matrix.
   *
   *  Throws if the matrix is not a valid rotation matrix (determinant equal to
   *  one and transpose equal to its inverse).
   *
   *  \param m the rotation matrix.
   */
  explicit Rotation2(const Mat2x2<T>& m);

  /** Creates a rotation from a rotation with different scalar type.
   *
   *  \tparam U the other scalar type.
   *  \param other the rotation to be copied.
   */
  template <typename U>
    HOU_MTH_API Rotation2(const Rotation2<U>& other);

  /** Returns the rotation angle.
   *
   *  The angle is expressed in radians and included in the range (-PI_F; Pi].
   *
   *  \return the rotation angle.
   */
  T getAngle() const;

  /** Returns the rotation matrix.
   *
   *  \return the rotation matrix.
   */
  Mat2x2<T> getMatrix() const;

  /** Combines this rotation with the given rotation.
   *
   *  \param rhs the rotation to be combined.
   *  \return a reference to this rotation after the combination.
   */
  Rotation2& operator*=(const Rotation2& rhs);

  /** Inverts this rotation.
   *
   *  \return a reference to this rotation after the inversion.
   */
  Rotation2& invert();

private:
  T mAngle;
};

/** Computes the combination of two rotations.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return a rotation representing the two combined rotations.
 */
template <typename T>
  HOU_MTH_API Rotation2<T> operator*(Rotation2<T> lhs, const Rotation2<T>& rhs);

/** Computes the inverse of the given rotation.
 *
 *  \tparam T the scalar type.
 *  \param r the rotation
 *  \return the inverse rotation.
 */
template <typename T>
  HOU_MTH_API Rotation2<T> inverse(Rotation2<T> r);

/** Checks if two rotations are equal.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the comparison.
 */
template <typename T>
  HOU_MTH_API bool operator==(const Rotation2<T>& lhs, const Rotation2<T>& rhs);

/** Checks if two rotations are not equal.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the comparison.
 */
template <typename T>
  HOU_MTH_API bool operator!=(const Rotation2<T>& lhs, const Rotation2<T>& rhs);

/** Checks if two rotations are equal with the given accuracy.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \param acc the accuracy of the comparison.
 *  \return the result of the comparison.
 */
template <typename T>
  HOU_MTH_API bool close(const Rotation2<T>& lhs, const Rotation2<T>& rhs
  , T acc = std::numeric_limits<T>::epsilon());

/** Writes the object into a stream.
 *
 *  \tparam T the scalar type.
 *  \param os the output stream.
 *  \param r the rotation.
 *  \return a reference to the stream.
 */
template <typename T>
  HOU_MTH_API std::ostream& operator<<(std::ostream& os, const Rotation2<T>& r);

}

#endif

