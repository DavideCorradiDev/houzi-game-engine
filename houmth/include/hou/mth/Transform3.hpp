// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_MTH_TRANSFORM_3_HPP
#define HOU_MTH_TRANSFORM_3_HPP

#include "hou/mth/MthExport.hpp"

#include "hou/mth/Matrix.hpp"
#include "hou/mth/Rotation3.hpp"
#include "hou/mth/Transform3Fwd.hpp"

#include "hou/cor/BasicTypes.hpp"

#include <iostream>
#include <limits>



namespace hou
{

/** Transform in 3d space.
 *
 *  It can be used to represent translation, rotation, scaling, shearing, or any
 *  combination thereof.
 *
 *  \tparam T the scalar type.
 */
template <typename T>
  class HOU_MTH_API Transform3
{
public:
  template <typename otherT> friend class Transform3;

public:
  /** Returns the identity transform.
   *
   *  /return the identity transform.
   */
  static Transform3 identity();

  /** Creates a 3d transform representing a translation.
   *
   *  \param translation the translation vector.
   *  \return a Transform3 object representing the translation.
   */
  static Transform3 translation(const Vec3<T>& translation);

  /** Creates a 3d transform representing a rotation.
   *
   *  \param rotation the rotation.
   *  \return a Transform3 object representing the rotation.
   */
  static Transform3 rotation(const Rot3<T>& rotation);

  /** Creates a 3d transform representing a scaling transformation.
   *
   *  \param scale the scaling factors.
   *  \return a Transform3 object representing the scaling.
   */
  static Transform3 scale(const Vec3<T>& scale);

  /** Creates a 3d transform representing a shearing transformation.
   *
   *  \param sxy the x-y shear factor
   *  \param sxz the x-z shear factor
   *  \param syx the y-x shear factor
   *  \param syz the y-z shear factor
   *  \param szx the z-x shear factor
   *  \param szy the z-y shear factor
   *  \return a Transform3 object representing the shearing.
   */
  static Transform3 shear(T sxy, T sxz, T syx, T syz, T szx, T szy);

public:
  /** Creates an identity transform.
   */
  Transform3();

  /** Creates a transform from a transform with a different scalar type.
   *
   *  \tparam U the other scalar type.
   *  \param other the transform to be converted.
   */
  template <typename U>
    HOU_MTH_API Transform3(const Transform3<U>& other);

  /** Builds a homogeneous transformation matrix corresponding to the transform.
   *
   *  \return the homogeneous transformation matrix corresponding to the
   *    transform.
   */
  Mat4x4<T> toMat4x4() const;

  /** Combines the transform with the given transform r.
   *
   *  \param r the transform to be combined.
   *  \return a reference to the object after the combination.
   */
  Transform3& operator*=(const Transform3& r);

  /** Inverts the transform.
   *
   *  \return a reference to the object after the inversion.
   */
  Transform3& invert();

  /** Transforms the given vector.
   *
   *  \param vec the vector to be transformed.
   *  \return the transformed vector.
   */
  Vec3<T> transformVector(const Vec3<T>& vec) const;

  /** Transforms the given point.
   *
   *  \param point the point to be transformed.
   *  \return the transformed point.
   */
  Vec3<T> transformPoint(const Vec3<T>& point) const;

  /** Checks if two transforms are equal.
   *
   *  \param lhs the left operand of the comparison.
   *  \param rhs the right operand of the comparison.
   *  \return the result of the check.
   */
  friend operator==(const Transform3& lhs, const Transform3& rhs)
  {
    return lhs.mMat == rhs.mMat && lhs.mVec == rhs.mVec;
  }

  /** Checks if two transforms are not equal.
   *
   *  \param lhs the left operand of the comparison.
   *  \param rhs the right operand of the comparison.
   *  \return the result of the check.
   */
  friend operator!=(const Transform3& lhs, const Transform3& rhs)
  {
    return !(lhs == rhs);
  }

  /** Checks if two transforms are equal with the specified accuracy.
   *
   *  \param lhs the left operand of the comparison.
   *  \param rhs the right operand of the comparison.
   *  \param acc the accuracy.
   *  \return the result of the check.
   */
  friend bool close(const Transform3& lhs, const Transform3& rhs
    , T acc = std::numeric_limits<T>::epsilon())
  {
    return close(lhs.mMat, rhs.mMat, acc) && close(lhs.mVec, rhs.mVec, acc);
  }

private:
  Transform3(const Mat3x3<T>& r, const Vec3<T>& t);

private:
  Mat3x3<T> mMat;
  Vec3<T> mVec;
};

/** Combines two transforms.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the combined transform.
 */
template <typename T>
  HOU_MTH_API Transform3<T> operator*(Transform3<T> lhs
  , const Transform3<T>& rhs);

/** Computes the inverse of a transform.
 *
 *  \tparam T the scalar type.
 *  \param t the transform to be inverted.
 *  \return the inverse transform.
 */
template <typename T>
  HOU_MTH_API Transform3<T> inverse(Transform3<T> t);

/** Writes the object into a stream.
 *
 *  \tparam T the scalar type.
 *  \param os the stream.
 *  \param t the transform.
 *  \return a reference to the stream.
 */
template <typename T>
  HOU_MTH_API std::ostream& operator<<(std::ostream& os
  , const Transform3<T>& t);

}

#endif

