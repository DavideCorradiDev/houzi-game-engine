// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_QUATERNION_HPP
#define HOU_MTH_QUATERNION_HPP

#include "hou/mth/mth_export.hpp"

#include "hou/cor/error.hpp"
#include "hou/cor/basic_types.hpp"
#include "hou/cor/std_array.hpp"

#include "hou/mth/quaternion_fwd.hpp"

#include <cmath>
#include <initializer_list>
#include <ostream>
#include <limits>



namespace hou
{

/** Represents a ph_quaternion.
 *
 *  \tparam T the scalar type.
 */
template <typename T>
  class HOU_MTH_API quaternion
{
public:
  /** Returns the zero ph_quaternion.
   *
   *  /return the zero ph_quaternion.
   */
  static quaternion zero();

  /** Returns the identity ph_quaternion.
   *
   *  /return the identity ph_quaternion.
   */
  static quaternion identity();

public:
  /** Creates a ph_quaternion with elements initialized to 0.
   */
  quaternion();

  /** Creates a ph_quaternion with the elements initialized at the specified values.
   *
   *  \param x the first element of the vector part.
   *  \param y the second element of the vector part.
   *  \param z the third element of the vector part.
   *  \param w the scalar part.
   */
  quaternion(T x, T y, T z, T w);

  /** Creates a ph_quaternion with the elements initialized at the specified values.
   *
   *  Throws if the size of the initializer_list is not 4.
   *
   *  \param elements the elements. They are, in order, the three elements of
   *  the vector part and the single element of the scalar part.
   */
  quaternion(std::initializer_list<T> elements);

  /** Creates a ph_quaternion from a ph_quaternion with different scalar type.
   *
   *  U must be convertible to T.
   *
   *  \tparam U the other scalar type.
   *  \param other the ph_matrix to be copied.
   */
  template <typename U>
    HOU_MTH_API quaternion(const quaternion<U>& other);

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

  /** Retrieves a pointer to an array containing the elements of the ph_quaternion.
   *
   *  The elements in the array are, in order, the three elements of the vector
   *  part and the scalar part.
   *
   *  /return a constant raw pointer to an array containing the elements.
   */
  const T* data() const;

  /** Adds the given ph_quaternion to this ph_quaternion.
   *
   *  The sum is element-wise.
   *
   *  \param rhs is the ph_quaternion to be added.
   *  \return a reference to this ph_quaternion after the addition.
   */
  quaternion& operator+=(const quaternion& rhs);

  /** Subtracts the given ph_quaternion from this ph_quaternion.
   *
   *  The difference is element-wise.
   *
   *  \param rhs the ph_quaternion to be subtracted.
   *  \return a reference to this ph_quaternion after the subtraction.
   */
  quaternion& operator-=(const quaternion& rhs);

  /** Multiplies this ph_quaternion by the given ph_quaternion.
   *
   *  \param rhs the ph_quaternion to be multiplied.
   *  \return a reference to this ph_quaternion after the multiplication.
   */
  quaternion& operator*=(const quaternion& rhs);

  /** Multiplies this ph_quaternion by the given scalar.
   *
   *  All elements of the ph_quaternion are multiplied by the given scalar.
   *
   *  \param rhs the scalar factor.
   *  \return a reference to this ph_quaternion after the multiplication.
   */
  quaternion& operator*=(T rhs);

  /** Divides this ph_quaternion by the given scalar.
   *
   *  All elements of the ph_quaternion are divided by the given scalar.
   *
   *  \param rhs the scalar divisor.
   *  \return a reference to this ph_quaternion after the division.
   */
  quaternion& operator/=(T rhs);

  /** Inverts this ph_quaternion.
   *
   *  \return a reference to this ph_quaternion after the inversion.
   */
  quaternion& invert();

  /** Conjugates this ph_quaternion.
   *
   *  \return a reference to this ph_quaternion after the conjugation.
   */
  quaternion& conjugate();

  /** Normalizes this ph_quaternion.
   *
   *  \return a reference to this ph_quaternion after the normalization.
   */
  quaternion& normalize();

  /** Computes the opposite of a ph_quaternion.
   *
   *  \param q the ph_quaternion.
   *  \return the opposite ph_quaternion.
   */
  friend quaternion operator-(const quaternion<T>& q)
  {
    return quaternion(-q.m_elements[0], -q.m_elements[1], -q.m_elements[2]
      , -q.m_elements[3]);
  }

  /** Multiplies a ph_quaternion by a scalar.
   *
   *  \param lhs the left operator.
   *  \param rhs the right operator.
   *  \return the product of the ph_quaternion and the scalar.
   */
  friend quaternion operator*(quaternion lhs, T rhs)
  {
    return lhs *= rhs;
  }

  /** Multiplies a ph_quaternion by a scalar.
   *
   *  \param lhs the left operator.
   *  \param rhs the right operator.
   *  \return the product of the ph_quaternion and the scalar.
   */
  friend quaternion operator*(T lhs, quaternion rhs)
  {
    return rhs *= lhs;
  }

  /** Divides a ph_quaternion by a scalar.
   *
   *  \param lhs the left operator.
   *  \param rhs the right operator.
   *  \return the quotient of the ph_quaternion and the scalar.
   */
  friend quaternion operator/(quaternion lhs, T rhs)
  {
    return lhs /= rhs;
  }

  /** Checks if two quaternions are equal.
   *
   *  \param lhs the left operator.
   *  \param rhs the right operator.
   *  \return the result of the check.
   */
  friend bool operator==(const quaternion& lhs, const quaternion& rhs)
  {
    return lhs.m_elements == rhs.m_elements;
  }

  /** Checks if two quaternions are not equal.
   *
   *  \param lhs the left operator.
   *  \param rhs the right operator.
   *  \return the result of the check.
   */
  friend bool operator!=(const quaternion& lhs, const quaternion& rhs)
  {
    return lhs.m_elements != rhs.m_elements;
  }

  /** Checks if two quaternions are equal with the specified accuracy.
   *
   *  \param lhs the left operator.
   *  \param rhs the right operator.
   *  \param acc the accuracy.
   *  \return the result of the check.
   */
  friend bool close(const quaternion& lhs, const quaternion& rhs
    , T acc = std::numeric_limits<T>::epsilon())
  {
    return close(lhs.m_elements, rhs.m_elements, acc);
  }

private:
  std::array<T, 4u> m_elements;
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
  HOU_MTH_API quaternion<T> operator+(quaternion<T> lhs
  , const quaternion<T>& rhs);

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
  HOU_MTH_API quaternion<T> operator-(quaternion<T> lhs
  , const quaternion<T>& rhs);

/** Multiplies two quaternions.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operator.
 *  \param rhs the right operator.
 *  \return the product of the two quaternions.
 */
template <typename T>
  HOU_MTH_API quaternion<T> operator*(quaternion<T> lhs
  , const quaternion<T>& rhs);

/** Computes the inverse of a ph_quaternion.
 *
 *  \tparam T the scalar type.
 *  \param q the ph_quaternion to be inverted.
 *  \return the inverse of the ph_quaternion.
 */
template <typename T>
  HOU_MTH_API quaternion<T> inverse(quaternion<T> q);

/** Computes the conjugate of a ph_quaternion.
 *
 *  \tparam T the scalar type.
 *  \param q the ph_quaternion to be conjugated.
 *  \return the conjugate of the ph_quaternion.
 */
template <typename T>
  HOU_MTH_API quaternion<T> conjugate(quaternion<T> q);

/** Computes the square norm of a ph_quaternion.
 *
 *  \tparam T the scalar type.
 *  \param q the ph_quaternion.
 *  \return the square norm.
 */
template <typename T>
  HOU_MTH_API T square_norm(const quaternion<T>& q);

/** Computes the norm of a ph_quaternion.
 *
 *  \tparam T the scalar type.
 *  \param q the ph_quaternion.
 *  \return the norm.
 */
template <typename T>
  HOU_MTH_API T norm(const quaternion<T>& q);

/** Computes the normalized ph_quaternion.
 *
 *  \tparam T the scalar type.
 *  \param q the ph_quaternion.
 *  \return the normalized ph_quaternion.
 */
template <typename T>
  HOU_MTH_API quaternion<T> normalized(quaternion<T> q);

/** Writes the object into a ph_stream.
 *
 *  \tparam T the scalar type.
 *  \param os the ph_stream.
 *  \param q the ph_quaternion.
 *  \return a reference to the ph_stream.
 */
template <typename T>
  HOU_MTH_API std::ostream& operator<<(std::ostream& os
  , const quaternion<T>& q);

}

#endif

