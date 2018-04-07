// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_MTH_QUATERNION_HPP
#define HOU_MTH_QUATERNION_HPP

#include "hou/mth/MthExport.hpp"

#include "hou/cor/Error.hpp"
#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/StdArray.hpp"

#include "hou/mth/QuaternionFwd.hpp"

#include <cmath>
#include <initializer_list>
#include <ostream>
#include <limits>



namespace hou
{

/** Represents a quaternion.
 *
 *  \tparam T the scalar type.
 */
template <typename T>
  class HOU_MTH_API Quaternion
{
public:
  /** Returns the zero quaternion.
   *
   *  /return the zero quaternion.
   */
  static Quaternion zero();

  /** Returns the identity quaternion.
   *
   *  /return the identity quaternion.
   */
  static Quaternion identity();

public:
  /** Creates a quaternion with elements initialized to 0.
   */
  Quaternion();

  /** Creates a quaternion with the elements initialized at the specified values.
   *
   *  \param x the first element of the vector part.
   *  \param y the second element of the vector part.
   *  \param z the third element of the vector part.
   *  \param w the scalar part.
   */
  Quaternion(T x, T y, T z, T w);

  /** Creates a quaternion with the elements initialized at the specified values.
   *
   *  Throws if the size of the initializer_list is not 4.
   *
   *  \param elements the elements. They are, in order, the three elements of
   *  the vector part and the single element of the scalar part.
   */
  Quaternion(std::initializer_list<T> elements);

  /** Creates a quaternion from a quaternion with different scalar type.
   *
   *  U must be convertible to T.
   *
   *  \tparam U the other scalar type.
   *  \param other the matrix to be copied.
   */
  template <typename U>
    HOU_MTH_API Quaternion(const Quaternion<U>& other);

  /** Retrieves a copy of the first element of the vector part.
   *
   *  /return a copy of the element.
   */
  T x() const;

  /** Retrieves a reference to the first element of the vector part.
   *
   *  /return a reference to the element.
   */
  T& x();

  /** Retrieves a copy of the second element of the vector part.
   *
   *  /return a copy of the element.
   */
  T y() const;

  /** Retrieves a reference to the second element of the vector part.
   *
   *  /return a reference to the element.
   */
  T& y();

  /** Retrieves a copy of the third element of the vector part.
   *
   *  /return a copy of the element.
   */
  T z() const;

  /** Retrieves a reference to the third element of the vector part.
   *
   *  /return a reference to the element.
   */
  T& z();

  /** Retrieves a copy of the scalar part.
   *
   *  /return a copy of the element.
   */
  T w() const;

  /** Retrieves a reference to the scalar part.
   *
   *  /return a reference to the element.
   */
  T& w();

  /** Retrieves a pointer to an array containing the elements of the quaternion.
   *
   *  The elements in the array are, in order, the three elements of the vector
   *  part and the scalar part.
   *
   *  /return a constant raw pointer to an array containing the elements.
   */
  const T* data() const;

  /** Adds the given quaternion to this quaternion.
   *
   *  The sum is element-wise.
   *
   *  \param rhs is the quaternion to be added.
   *  \return a reference to this quaternion after the addition.
   */
  Quaternion& operator+=(const Quaternion& rhs);

  /** Subtracts the given quaternion from this quaternion.
   *
   *  The difference is element-wise.
   *
   *  \param rhs the quaternion to be subtracted.
   *  \return a reference to this quaternion after the subtraction.
   */
  Quaternion& operator-=(const Quaternion& rhs);

  /** Multiplies this quaternion by the given quaternion.
   *
   *  \param rhs the quaternion to be multiplied.
   *  \return a reference to this quaternion after the multiplication.
   */
  Quaternion& operator*=(const Quaternion& rhs);

  /** Multiplies this quaternion by the given scalar.
   *
   *  All elements of the quaternion are multiplied by the given scalar.
   *
   *  \param rhs the scalar factor.
   *  \return a reference to this quaternion after the multiplication.
   */
  Quaternion& operator*=(T rhs);

  /** Divides this quaternion by the given scalar.
   *
   *  All elements of the quaternion are divided by the given scalar.
   *
   *  \param rhs the scalar divisor.
   *  \return a reference to this quaternion after the division.
   */
  Quaternion& operator/=(T rhs);

  /** Inverts this quaternion.
   *
   *  \return a reference to this quaternion after the inversion.
   */
  Quaternion& invert();

  /** Conjugates this quaternion.
   *
   *  \return a reference to this quaternion after the conjugation.
   */
  Quaternion& conjugate();

  /** Normalizes this quaternion.
   *
   *  \return a reference to this quaternion after the normalization.
   */
  Quaternion& normalize();

  /** Computes the opposite of a quaternion.
   *
   *  \param q the quaternion.
   *  \return the opposite quaternion.
   */
  friend Quaternion operator-(const Quaternion<T>& q)
  {
    return Quaternion(-q.mElements[0], -q.mElements[1], -q.mElements[2]
      , -q.mElements[3]);
  }

  /** Multiplies a quaternion by a scalar.
   *
   *  \param lhs the left operator.
   *  \param rhs the right operator.
   *  \return the product of the quaternion and the scalar.
   */
  friend Quaternion operator*(Quaternion lhs, T rhs)
  {
    return lhs *= rhs;
  }

  /** Multiplies a quaternion by a scalar.
   *
   *  \param lhs the left operator.
   *  \param rhs the right operator.
   *  \return the product of the quaternion and the scalar.
   */
  friend Quaternion operator*(T lhs, Quaternion rhs)
  {
    return rhs *= lhs;
  }

  /** Divides a quaternion by a scalar.
   *
   *  \param lhs the left operator.
   *  \param rhs the right operator.
   *  \return the quotient of the quaternion and the scalar.
   */
  friend Quaternion operator/(Quaternion lhs, T rhs)
  {
    return lhs /= rhs;
  }

  /** Checks if two quaternions are equal.
   *
   *  \param lhs the left operator.
   *  \param rhs the right operator.
   *  \return the result of the check.
   */
  friend bool operator==(const Quaternion& lhs, const Quaternion& rhs)
  {
    return lhs.mElements == rhs.mElements;
  }

  /** Checks if two quaternions are not equal.
   *
   *  \param lhs the left operator.
   *  \param rhs the right operator.
   *  \return the result of the check.
   */
  friend bool operator!=(const Quaternion& lhs, const Quaternion& rhs)
  {
    return lhs.mElements != rhs.mElements;
  }

  /** Checks if two quaternions are equal with the specified accuracy.
   *
   *  \param lhs the left operator.
   *  \param rhs the right operator.
   *  \param acc the accuracy.
   *  \return the result of the check.
   */
  friend bool close(const Quaternion& lhs, const Quaternion& rhs
    , T acc = std::numeric_limits<T>::epsilon())
  {
    return close(lhs.mElements, rhs.mElements, acc);
  }

private:
  std::array<T, 4u> mElements;
};

/** Sums two quaternions.
 *
 *  The sum is element-wise.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operator.
 *  \param rhs the right operator.
 *  \return the sum of the two quaternions.
 */
template <typename T>
  HOU_MTH_API Quaternion<T> operator+(Quaternion<T> lhs
  , const Quaternion<T>& rhs);

/** Subtracts two quaternions.
 *
 *  The difference is element-wise.
 *
 *  \tparam T the scalar type.
 *  \tparam T the scalar type.
 *  \param lhs the left operator.
 *  \param rhs the right operator.
 *  \return the difference of the two quaternions.
 */
template <typename T>
  HOU_MTH_API Quaternion<T> operator-(Quaternion<T> lhs
  , const Quaternion<T>& rhs);

/** Multiplies two quaternions.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operator.
 *  \param rhs the right operator.
 *  \return the product of the two quaternions.
 */
template <typename T>
  HOU_MTH_API Quaternion<T> operator*(Quaternion<T> lhs
  , const Quaternion<T>& rhs);

/** Computes the inverse of a quaternion.
 *
 *  \tparam T the scalar type.
 *  \param q the quaternion to be inverted.
 *  \return the inverse of the quaternion.
 */
template <typename T>
  HOU_MTH_API Quaternion<T> inverse(Quaternion<T> q);

/** Computes the conjugate of a quaternion.
 *
 *  \tparam T the scalar type.
 *  \param q the quaternion to be conjugated.
 *  \return the conjugate of the quaternion.
 */
template <typename T>
  HOU_MTH_API Quaternion<T> conjugate(Quaternion<T> q);

/** Computes the square norm of a quaternion.
 *
 *  \tparam T the scalar type.
 *  \param q the quaternion.
 *  \return the square norm.
 */
template <typename T>
  HOU_MTH_API T squareNorm(const Quaternion<T>& q);

/** Computes the norm of a quaternion.
 *
 *  \tparam T the scalar type.
 *  \param q the quaternion.
 *  \return the norm.
 */
template <typename T>
  HOU_MTH_API T norm(const Quaternion<T>& q);

/** Computes the normalized quaternion.
 *
 *  \tparam T the scalar type.
 *  \param q the quaternion.
 *  \return the normalized quaternion.
 */
template <typename T>
  HOU_MTH_API Quaternion<T> normalized(Quaternion<T> q);

/** Writes the object into a stream.
 *
 *  \tparam T the scalar type.
 *  \param os the stream.
 *  \param q the quaternion.
 *  \return a reference to the stream.
 */
template <typename T>
  HOU_MTH_API std::ostream& operator<<(std::ostream& os
  , const Quaternion<T>& q);

}

#endif

