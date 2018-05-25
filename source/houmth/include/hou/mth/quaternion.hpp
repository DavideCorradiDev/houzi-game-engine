// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_QUATERNION_HPP
#define HOU_MTH_QUATERNION_HPP

#include "hou/mth/quaternion_fwd.hpp"

#include "hou/mth/mth_config.hpp"

#include "hou/cor/assertions.hpp"
#include "hou/cor/std_array.hpp"

#include <cmath>
#include <initializer_list>
#include <limits>
#include <ostream>



namespace hou
{

/** Represents a quaternion.
 *
 * \tparam T the scalar type.
 */
template <typename T>
class quaternion
{
public:
  /** Returns the zero quaternion.
   *
   * \return the zero quaternion.
   */
  static const quaternion& zero() noexcept;

  /** Returns the identity quaternion.
   *
   * \return the identity quaternion.
   */
  static const quaternion& identity() noexcept;

public:
  /** Creates a quaternion with elements initialized to 0.
   */
  constexpr quaternion() noexcept;

  /** Creates a quaternion with the elements initialized at the specified
   * values.
   *
   * \param x the first element of the vector part.
   *
   * \param y the second element of the vector part.
   *
   * \param z the third element of the vector part.
   *
   * \param w the scalar part.
   */
  constexpr quaternion(T x, T y, T z, T w) noexcept;

  /** Creates a quaternion from a quaternion with different scalar type.
   *
   * U must be convertible to T.
   *
   * \tparam U the other scalar type.
   *
   * \param other the matrix to be copied.
   */
  template <typename U,
    typename Enable = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr quaternion(const quaternion<U>& other) noexcept;

  /** Retrieves a copy of the first element of the vector part.
   *
   * /return a copy of the element.
   */
  constexpr T x() const noexcept;

  /** Retrieves a reference to the first element of the vector part.
   *
   * /return a reference to the element.
   */
  constexpr T& x() noexcept;

  /** Retrieves a copy of the second element of the vector part.
   *
   * /return a copy of the element.
   */
  constexpr T y() const noexcept;

  /** Retrieves a reference to the second element of the vector part.
   *
   * /return a reference to the element.
   */
  constexpr T& y() noexcept;

  /** Retrieves a copy of the third element of the vector part.
   *
   * /return a copy of the element.
   */
  constexpr T z() const noexcept;

  /** Retrieves a reference to the third element of the vector part.
   *
   * /return a reference to the element.
   */
  constexpr T& z() noexcept;

  /** Retrieves a copy of the scalar part.
   *
   * /return a copy of the element.
   */
  constexpr T w() const noexcept;

  /** Retrieves a reference to the scalar part.
   *
   * /return a reference to the element.
   */
  constexpr T& w() noexcept;

  /** Retrieves a pointer to an array containing the elements of the
   * quaternion.
   *
   * The elements in the array are, in order, the three elements of the vector
   * part and the scalar part.
   *
   * /return a constant raw pointer to an array containing the elements.
   */
  constexpr const T* data() const noexcept;

  /** Adds the given quaternion to this quaternion.
   *
   * The sum is element-wise.
   *
   * \param rhs is the quaternion to be added.
   *
   * \return a reference to this quaternion after the addition.
   */
  constexpr quaternion& operator+=(const quaternion& rhs) noexcept;

  /** Subtracts the given quaternion from this quaternion.
   *
   * The difference is element-wise.
   *
   * \param rhs the quaternion to be subtracted.
   *
   * \return a reference to this quaternion after the subtraction.
   */
  constexpr quaternion& operator-=(const quaternion& rhs) noexcept;

  /** Multiplies this quaternion by the given quaternion.
   *
   * \param rhs the quaternion to be multiplied.
   *
   * \return a reference to this quaternion after the multiplication.
   */
  constexpr quaternion& operator*=(const quaternion& rhs) noexcept;

  /** Multiplies this quaternion by the given scalar.
   *
   * All elements of the quaternion are multiplied by the given scalar.
   *
   * \param rhs the scalar factor.
   *
   * \return a reference to this quaternion after the multiplication.
   */
  constexpr quaternion& operator*=(T rhs) noexcept;

  /** Divides this quaternion by the given scalar.
   *
   * All elements of the quaternion are divided by the given scalar.
   *
   * \param rhs the scalar divisor.
   *
   * \return a reference to this quaternion after the division.
   */
  constexpr quaternion& operator/=(T rhs) noexcept;

  /** Inverts this quaternion.
   *
   * \throws hou::precondition_violation if the norm of the quaternion is 0.
   *
   * \return a reference to this quaternion after the inversion.
   */
  constexpr quaternion& invert();

  /** Conjugates this quaternion.
   *
   * \return a reference to this quaternion after the conjugation.
   */
  constexpr quaternion& conjugate() noexcept;

  /** Normalizes this quaternion.
   *
   * \throws hou::precondition_violation if the norm of q is zero.
   *
   * \return a reference to this quaternion after the normalization.
   */
  constexpr quaternion& normalize();

  /** Computes the opposite of a quaternion.
   *
   * \param q the quaternion.
   *
   * \return the opposite quaternion.
   */
  friend constexpr quaternion operator-(const quaternion<T>& q) noexcept
  {
    return quaternion(
      -q.m_elements[0], -q.m_elements[1], -q.m_elements[2], -q.m_elements[3]);
  }

  /** Multiplies a quaternion by a scalar.
   *
   * \param lhs the left operator.
   *
   * \param rhs the right operator.
   *
   * \return the product of the quaternion and the scalar.
   */
  friend constexpr quaternion operator*(quaternion<T> lhs, T rhs) noexcept
  {
    return lhs *= rhs;
  }

  /** Multiplies a quaternion by a scalar.
   *
   * \param lhs the left operator.
   *
   * \param rhs the right operator.
   *
   * \return the product of the quaternion and the scalar.
   */
  friend constexpr quaternion operator*(T lhs, quaternion<T> rhs) noexcept
  {
    return rhs *= lhs;
  }

  /** Divides a quaternion by a scalar.
   *
   * \param lhs the left operator.
   *
   * \param rhs the right operator.
   *
   * \return the quotient of the quaternion and the scalar.
   */
  friend constexpr quaternion operator/(quaternion<T> lhs, T rhs) noexcept
  {
    return lhs /= rhs;
  }

  template <typename U>
  friend constexpr bool operator==(
    const quaternion<U>& lhs, const quaternion<U>& rhs) noexcept;

  template <typename U>
  friend constexpr bool operator!=(
    const quaternion<U>& lhs, const quaternion<U>& rhs) noexcept;

  template <typename U>
  friend constexpr bool close(const quaternion<U>& lhs,
    const quaternion<U>& rhs, U acc) noexcept;

private:
  std::array<T, 4u> m_elements;
};

/** Sums two quaternions.
 *
 * The sum is element-wise.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operator.
 *
 * \param rhs the right operator.
 *
 * \return the sum of the two quaternions.
 */
template <typename T>
constexpr quaternion<T> operator+(
  quaternion<T> lhs, const quaternion<T>& rhs) noexcept;

/** Subtracts two quaternions.
 *
 * The difference is element-wise.
 *
 * \tparam T the scalar type.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operator.
 *
 * \param rhs the right operator.
 *
 * \return the difference of the two quaternions.
 */
template <typename T>
constexpr quaternion<T> operator-(
  quaternion<T> lhs, const quaternion<T>& rhs) noexcept;

/** Multiplies two quaternions.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operator.
 *
 * \param rhs the right operator.
 *
 * \return the product of the two quaternions.
 */
template <typename T>
constexpr quaternion<T> operator*(
  quaternion<T> lhs, const quaternion<T>& rhs) noexcept;

/** Computes the inverse of a quaternion.
 *
 * \tparam T the scalar type.
 *
 * \param q the quaternion to be inverted.
 *
 * \throws hou::precondition_violation if the norm of the quaternion is 0.
 *
 * \return the inverse of the quaternion.
 */
template <typename T>
constexpr quaternion<T> inverse(quaternion<T> q);

/** Computes the conjugate of a quaternion.
 *
 * \tparam T the scalar type.
 *
 * \param q the quaternion to be conjugated.
 *
 * \return the conjugate of the quaternion.
 */
template <typename T>
constexpr quaternion<T> conjugate(quaternion<T> q) noexcept;

/** Computes the square norm of a quaternion.
 *
 * \tparam T the scalar type.
 *
 * \param q the quaternion.
 *
 * \return the square norm.
 */
template <typename T>
constexpr T square_norm(const quaternion<T>& q) noexcept;

/** Computes the norm of a quaternion.
 *
 * \tparam T the scalar type.
 *
 * \param q the quaternion.
 *
 * \return the norm.
 */
template <typename T>
constexpr T norm(const quaternion<T>& q) noexcept;

/** Computes the normalized quaternion.
 *
 * \tparam T the scalar type.
 *
 * \param q the quaternion.
 *
 * \throws hou::precondition_violation if the norm of q is zero.
 *
 * \return the normalized quaternion.
 */
template <typename T>
constexpr quaternion<T> normalized(quaternion<T> q);

/** Checks if two quaternions are equal.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operator.
 *
 * \param rhs the right operator.
 *
 * \return the result of the check.
 */
template <typename T>
constexpr bool operator==(
  const quaternion<T>& lhs, const quaternion<T>& rhs) noexcept;

/** Checks if two quaternions are not equal.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operator.
 *
 * \param rhs the right operator.
 *
 * \return the result of the check.
 */
template <typename T>
constexpr bool operator!=(
  const quaternion<T>& lhs, const quaternion<T>& rhs) noexcept;

/** Checks if two quaternions are equal with the specified accuracy.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operator.
 *
 * \param rhs the right operator.
 *
 * \param acc the accuracy.
 *
 * \return the result of the check.
 */
template <typename T>
constexpr bool close(const quaternion<T>& lhs, const quaternion<T>& rhs,
  T acc = std::numeric_limits<T>::epsilon()) noexcept;

/** Writes the object into a stream.
 *
 * \tparam T the scalar type.
 *
 * \param os the stream.
 *
 * \param q the quaternion.
 *
 * \return a reference to the stream.
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const quaternion<T>& q);

}  // namespace hou

#include "hou/mth/quaternion.inl"

#endif
