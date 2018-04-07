// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_MTH_TRANSFORM_2_HPP
#define HOU_MTH_TRANSFORM_2_HPP

#include "hou/mth/MthExport.hpp"

#include "hou/mth/Matrix.hpp"
#include "hou/mth/RectangleFwd.hpp"
#include "hou/mth/Rotation2Fwd.hpp"
#include "hou/mth/Transform2Fwd.hpp"

#include "hou/cor/BasicTypes.hpp"

#include <iostream>
#include <limits>



namespace hou
{

/** Transform in 2d space.
 *
 *  It can be used to represent translation, rotation, scaling, shearing, or any
 *  combination thereof.
 *
 *  \tparam T the scalar type.
 */
template <typename T>
  class HOU_MTH_API Transform2
{
public:
  template <typename otherT> friend class Transform2;

public:
  /** Returns the identity transform.
   *
   *  /return the identity transform.
   */
  static Transform2 identity();

  /** Creates a 2d transform representing a translation.
   *
   *  \param translation the translation vector.
   *  \return a Transform2 object representing the translation.
   */
  static Transform2 translation(const Vec2<T>& translation);

  /** Creates a 2d transform representing a rotation.
   *
   *  \param rotation the rotation.
   *  \return a Transform2 object representing the rotation.
   */
  static Transform2 rotation(const Rot2<T>& rotation);

  /** Creates a 2d transform representing a scaling transformation.
   *
   *  \param scale the scaling factors.
   *  \return a Transform2 object representing the scaling.
   */
  static Transform2 scale(const Vec2<T>& scale);

  /** Creates a 2d transform representing a shearing transformation.
   *
   *  \param sxy the horizontal shear factor.
   *  \param syx the vertical shear factor.
   *  \return a Transform2 object representing the shearing.
   */
  static Transform2 shear(T sxy, T syx);

  /** Creates a 2d transform representing an ortographic transform.
   *
   *  The transform transforms from the rect specified by clipping plane into
   *  a rect with normalized coordinates going from -1 to +1.
   *  \param clippingPlane the rectangle to be transformed into normalized
   *    coordinates.
   *  \return a Transform2 object representing the ortographic projection.
   */
  static Transform2 orthographicProjection(const Rect<T>& clippingPlane);

public:
  /** Creates an identity transform.
   */
  Transform2();

  /** Creates a transform from a transform with a different scalar type.
   *
   *  \tparam U the other scalar type.
   *  \param other the transform to be converted.
   */
  template <typename U>
    HOU_MTH_API Transform2(const Transform2<U>& other);

  /** Builds a homogeneous transformation matrix corresponding to the transform.
   *
   *  \return the homogeneous transformation matrix corresponding to the
   *    transform.
   */
  Mat4x4<T> toMat4x4() const;

  /** Combines the transform with the given transform r.
   *
   *  \param rhs the transform to be combined.
   *  \return a reference to the object after the combination.
   */
  Transform2& operator*=(const Transform2& rhs);

  /** Inverts the transform.
   *
   *  \return a reference to the object after the inversion.
   */
  Transform2& invert();

  /** Transforms the given vector.
   *
   *  \param vec the vector to be transformed.
   *  \return the transformed vector.
   */
  Vec2<T> transformVector(const Vec2<T>& vec) const;

  /** Transforms the given point.
   *
   *  \param point the point to be transformed.
   *  \return the transformed point.
   */
  Vec2<T> transformPoint(const Vec2<T>& point) const;

  /** Checks if two transforms are equal.
   *
   *  \param lhs the left operand of the comparison.
   *  \param rhs the right operand of the comparison.
   *  \return the result of the check.
   */
  friend bool operator==(const Transform2& lhs, const Transform2& rhs)
  {
    return lhs.mMat == rhs.mMat && lhs.mVec == rhs.mVec;
  }

  /** Checks if two transforms are not equal.
   *
   *  \param lhs the left operand of the comparison.
   *  \param rhs the right operand of the comparison.
   *  \return the result of the check.
   */
  friend bool operator!=(const Transform2& lhs, const Transform2& rhs)
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
  friend bool close(const Transform2& lhs, const Transform2& rhs
    , T acc = std::numeric_limits<T>::epsilon())
  {
    return close(lhs.mMat, rhs.mMat, acc) && close(lhs.mVec, rhs.mVec, acc);
  }

private:
  Transform2(const Mat2x2<T>& r, const Vec2<T>& t);

private:
  Mat2x2<T> mMat;
  Vec2<T> mVec;
};

/** Combines two transforms.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the combined transform.
 */
template <typename T>
  HOU_MTH_API Transform2<T> operator*(Transform2<T> lhs
  , const Transform2<T>& rhs);

/** Computes the inverse of a transform.
 *
 *  \tparam T the scalar type.
 *  \param t the transform to be inverted.
 *  \return the inverse transform.
 */
template <typename T>
  HOU_MTH_API Transform2<T> inverse(Transform2<T> t);

/** Writes the object into a stream.
 *
 *  \tparam T the scalar type.
 *  \param os the stream.
 *  \param t the transform.
 *  \return a reference to the stream.
 */
template <typename T>
  HOU_MTH_API std::ostream& operator<<(std::ostream& os
  , const Transform2<T>& t);

}

#endif

