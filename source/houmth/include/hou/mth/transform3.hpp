// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_TRANSFORM_3_HPP
#define HOU_MTH_TRANSFORM_3_HPP

#include "hou/mth/mth_export.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/rotation3.hpp"
#include "hou/mth/transform3_fwd.hpp"

#include "hou/cor/basic_types.hpp"

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
  static transform3 identity();

  /** Creates a 3d transform representing a translation.
   *
   * \param translation the translation vector.
   *
   * \return a transform3 object representing the translation.
   */
  static transform3 translation(const vec3<T>& translation);

  /** Creates a 3d transform representing a rotation.
   *
   * \param rotation the rotation.
   *
   * \return a transform3 object representing the rotation.
   */
  static transform3 rotation(const rot3<T>& rotation);

  /** Creates a 3d transform representing a scaling transformation.
   *
   * \param scale the scaling factors.
   *
   * \return a transform3 object representing the scaling.
   */
  static transform3 scale(const vec3<T>& scale);

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
  static transform3 shear(T sxy, T sxz, T syx, T syz, T szx, T szy);

public:
  /** Creates an identity transform.
   */
  transform3();

  /** Creates a transform from a transform with a different scalar type.
   *
   * \tparam U the other scalar type.
   *
   * \param other the transform to be converted.
   */
  template <typename U>
  HOU_MTH_API transform3(const transform3<U>& other);

  /** Builds a homogeneous transformation ph_matrix corresponding to the
   * transform.
   *
   * \return the homogeneous transformation ph_matrix corresponding to the
   * transform.
   */
  mat4x4<T> to_mat4x4() const;

  /** Combines the transform with the given transform r.
   *
   * \param r the transform to be combined.
   *
   * \return a reference to the object after the combination.
   */
  transform3& operator*=(const transform3& r);

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
  vec3<T> transform_vector(const vec3<T>& vec) const;

  /** Transforms the given point.
   *
   * \param point the point to be transformed.
   *
   * \return the transformed point.
   */
  vec3<T> transform_point(const vec3<T>& point) const;

  /** Checks if two transforms are equal.
   *
   * \param lhs the left operand of the comparison.
   *
   * \param rhs the right operand of the comparison.
   *
   * \return the result of the check.
   */
  friend operator==(const transform3& lhs, const transform3& rhs)
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
  friend operator!=(const transform3& lhs, const transform3& rhs)
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
  friend bool close(const transform3& lhs, const transform3& rhs,
    T acc = std::numeric_limits<T>::epsilon())
  {
    return close(lhs.m_mat, rhs.m_mat, acc) && close(lhs.m_vec, rhs.m_vec, acc);
  }

private:
  transform3(const mat3x3<T>& r, const vec3<T>& t);

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
HOU_MTH_API transform3<T> operator*(
  transform3<T> lhs, const transform3<T>& rhs);

/** Computes the inverse of a transform.
 *
 * \tparam T the scalar type.
 *
 * \param t the transform to be inverted.
 *
 * \return the inverse transform.
 */
template <typename T>
HOU_MTH_API transform3<T> inverse(transform3<T> t);

/** Writes the object into a ph_stream.
 *
 * \tparam T the scalar type.
 *
 * \param os the ph_stream.
 *
 * \param t the transform.
 *
 * \return a reference to the ph_stream.
 */
template <typename T>
HOU_MTH_API std::ostream& operator<<(std::ostream& os, const transform3<T>& t);

}  // namespace hou

#endif
