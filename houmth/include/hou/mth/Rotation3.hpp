// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_MTH_ROTATION_3_HPP
#define HOU_MTH_ROTATION_3_HPP

#include "hou/mth/MthExport.hpp"

#include "hou/mth/MatrixFwd.hpp"
#include "hou/mth/Quaternion.hpp"
#include "hou/mth/Rotation3Fwd.hpp"

#include <iostream>
#include <limits>



namespace hou
{

/** Represents a rotation in 2d space.
 *
 *  The rotation is internally represented as a unit quaternion.
 *
 *  \tparam T the scalar type.
 */
template <typename T>
  class HOU_MTH_API Rotation3
{
public:
  template <typename otherT> friend class Rotation3;

public:
  /** Returns the identity rotation.
   *
   *  \return the identity rotation.
   */
  static Rotation3 identity();

  /** Returns a rotation around the x axis with the given angle.
   *
   *  \param angle the angle in radians.
   *  \return the rotation around the x axis.
   *
   */
  static Rotation3 x(T angle);

  /** Returns a rotation around the y axis with the given angle.
   *
   *  \param angle the angle in radians.
   *  \return the rotation around the y axis.
   *
   */
  static Rotation3 y(T angle);

  /** Returns a rotation around the z axis with the given angle.
   *
   *  \param angle the angle in radians.
   *  \return the rotation around the z axis.
   *
   */
  static Rotation3 z(T angle);

public:
  /** Creates an identity rotation.
   */
  Rotation3();

  /** Creates a rotation with the given quaternion
   *
   *  The quaternion will be normalized if it is not.
   *  Throws if passed the zero quaternion.
   *
   *  \param q the quaternion.
   */
  explicit Rotation3(const Quaternion<T>& q);

  /** Creates a rotation with the given vector.
   *
   *  The direction of the vector represents the axis of rotation and its
   *  magnitude represents the angle of rotation in radians.
   *
   *  \param v the vector representing the axis and angle of rotation.
   */
  explicit Rotation3(const Vec3<T>& v);

  /** Creates a rotation with the given rotation matrix.
   *
   *  If m is not a valid rotation matrix, the matrix will be converted to a
   *  quaternion which will then be normalized. This will result in a valid
   *  rotation, whose rotation matrix is a different one from the one provided.
   *  The caller must therefore ensure that m is a valid rotation matrix.
   *
   *  \param m the rotation matrix.
   */
  explicit Rotation3(const Mat3x3<T>& m);


  /** Creates a rotation from a rotation with different scalar type.
   *
   *  \tparam U the other scalar type.
   *  \param other the rotation to be copied.
   */
  template <typename U>
    HOU_MTH_API Rotation3(const Rotation3<U>& other);


  /** Returns a quaternion representing the rotation.
   *
   *  /return a quaternion representing the rotation.
   */
  const Quaternion<T>& getQuaternion() const;

  /** Returns a vector representing the rotation.
   *
   *  /return a vector representing the rotation.
   */
  Vec3<T> getVector() const;

  /** Returns a rotatin matrix representing the rotation.
   *
   *  /return a matrix representing the rotation.
   */
  Mat3x3<T> getMatrix() const;

  /** Combines this rotation with the given rotation.
   *
   *  \param rhs the rotation to be combined.
   *  \return a reference to this rotation after the combination.
   */
  Rotation3& operator*=(const Rotation3& rhs);

  /** Inverts this rotation.
   *
   *  \return a reference to this rotation after the inversion.
   */
  Rotation3& invert();

private:
  Quaternion<T> mQuaternion;
};

/** Computes the combination of two rotations.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return a rotation representing the two combined rotations.
 */
template <typename T>
  HOU_MTH_API Rotation3<T> operator*(Rotation3<T> lhs, const Rotation3<T>& rhs);

/** Computes the inverse of the given rotation.
 *
 *  \tparam T the scalar type.
 *  \param r the rotation
 *  \return the inverse rotation.
 */
template <typename T>
  HOU_MTH_API Rotation3<T> inverse(Rotation3<T> r);

/** Checks if two rotations are equal.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the comparison.
 */
template <typename T>
  HOU_MTH_API bool operator==(const Rotation3<T>& lhs, const Rotation3<T>& rhs);

/** Checks if two rotations are not equal.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the comparison.
 */
template <typename T>
  HOU_MTH_API bool operator!=(const Rotation3<T>& lhs, const Rotation3<T>& rhs);

/** Checks if two rotations are equal with the given accuracy.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \param acc the accuracy of the comparison.
 *  \return the result of the comparison.
 */
template <typename T>
  HOU_MTH_API bool close(const Rotation3<T>& lhs, const Rotation3<T>& rhs
  , T acc = std::numeric_limits<T>::epsilon());

/** Writes the object into a stream.
 *
 *  \tparam T the scalar type.
 *  \param os the output stream.
 *  \param r the rotation.
 *  \return a reference to the stream.
 */
template <typename T>
  HOU_MTH_API std::ostream& operator<<(std::ostream& os, const Rotation3<T>& r);

}

#endif

