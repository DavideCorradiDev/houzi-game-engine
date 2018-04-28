// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_ROTATION_3_HPP
#define HOU_MTH_ROTATION_3_HPP

#include "hou/mth/mth_export.hpp"

#include "hou/mth/matrix_fwd.hpp"
#include "hou/mth/quaternion.hpp"
#include "hou/mth/rotation3_fwd.hpp"

#include <iostream>
#include <limits>



namespace hou
{

/** Represents a rotation in 2d space.
 *
 *  The rotation is internally represented as a unit ph_quaternion.
 *
 *  \tparam T the scalar type.
 */
template <typename T>
  class HOU_MTH_API rotation3
{
public:
  template <typename otherT> friend class rotation3;

public:
  /** Returns the identity rotation.
   *
   *  \return the identity rotation.
   */
  static rotation3 identity();

  /** Returns a rotation around the x axis with the given angle.
   *
   *  \param angle the angle in radians.
   *  \return the rotation around the x axis.
   *
   */
  static rotation3 x(T angle);

  /** Returns a rotation around the y axis with the given angle.
   *
   *  \param angle the angle in radians.
   *  \return the rotation around the y axis.
   *
   */
  static rotation3 y(T angle);

  /** Returns a rotation around the z axis with the given angle.
   *
   *  \param angle the angle in radians.
   *  \return the rotation around the z axis.
   *
   */
  static rotation3 z(T angle);

public:
  /** Creates an identity rotation.
   */
  rotation3();

  /** Creates a rotation with the given ph_quaternion
   *
   *  The ph_quaternion will be normalized if it is not.
   *  Throws if passed the zero ph_quaternion.
   *
   *  \param q the ph_quaternion.
   */
  explicit rotation3(const quaternion<T>& q);

  /** Creates a rotation with the given vector.
   *
   *  The direction of the vector represents the axis of rotation and its
   *  magnitude represents the angle of rotation in radians.
   *
   *  \param v the vector representing the axis and angle of rotation.
   */
  explicit rotation3(const vec3<T>& v);

  /** Creates a rotation with the given rotation ph_matrix.
   *
   *  If m is not a valid rotation ph_matrix, the ph_matrix will be converted to a
   *  ph_quaternion which will then be normalized. This will result in a valid
   *  rotation, whose rotation ph_matrix is a different one from the one provided.
   *  The caller must therefore ensure that m is a valid rotation ph_matrix.
   *
   *  \param m the rotation ph_matrix.
   */
  explicit rotation3(const mat3x3<T>& m);


  /** Creates a rotation from a rotation with different scalar type.
   *
   *  \tparam U the other scalar type.
   *  \param other the rotation to be copied.
   */
  template <typename U>
    HOU_MTH_API rotation3(const rotation3<U>& other);


  /** Returns a ph_quaternion representing the rotation.
   *
   *  /return a ph_quaternion representing the rotation.
   */
  const quaternion<T>& get_quaternion() const;

  /** Returns a vector representing the rotation.
   *
   *  /return a vector representing the rotation.
   */
  vec3<T> get_vector() const;

  /** Returns a rotatin ph_matrix representing the rotation.
   *
   *  /return a ph_matrix representing the rotation.
   */
  mat3x3<T> get_matrix() const;

  /** Combines this rotation with the given rotation.
   *
   *  \param rhs the rotation to be combined.
   *  \return a reference to this rotation after the combination.
   */
  rotation3& operator*=(const rotation3& rhs);

  /** Inverts this rotation.
   *
   *  \return a reference to this rotation after the inversion.
   */
  rotation3& invert();

private:
  quaternion<T> m_quaternion;
};

/** Computes the combination of two rotations.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return a rotation representing the two combined rotations.
 */
template <typename T>
  HOU_MTH_API rotation3<T> operator*(rotation3<T> lhs, const rotation3<T>& rhs);

/** Computes the inverse of the given rotation.
 *
 *  \tparam T the scalar type.
 *  \param r the rotation
 *  \return the inverse rotation.
 */
template <typename T>
  HOU_MTH_API rotation3<T> inverse(rotation3<T> r);

/** Checks if two rotations are equal.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the comparison.
 */
template <typename T>
  HOU_MTH_API bool operator==(const rotation3<T>& lhs, const rotation3<T>& rhs);

/** Checks if two rotations are not equal.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the comparison.
 */
template <typename T>
  HOU_MTH_API bool operator!=(const rotation3<T>& lhs, const rotation3<T>& rhs);

/** Checks if two rotations are equal with the given accuracy.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \param acc the accuracy of the comparison.
 *  \return the result of the comparison.
 */
template <typename T>
  HOU_MTH_API bool close(const rotation3<T>& lhs, const rotation3<T>& rhs
  , T acc = std::numeric_limits<T>::epsilon());

/** Writes the object into a stream.
 *
 *  \tparam T the scalar type.
 *  \param os the output stream.
 *  \param r the rotation.
 *  \return a reference to the stream.
 */
template <typename T>
  HOU_MTH_API std::ostream& operator<<(std::ostream& os, const rotation3<T>& r);

}

#endif

