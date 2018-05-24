// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_MATRIX_HPP
#define HOU_MTH_MATRIX_HPP

#include "hou/mth/matrix_fwd.hpp"

#include "hou/mth/mth_config.hpp"

#include "hou/cor/assertions.hpp"
#include "hou/cor/cor_exceptions.hpp"
#include "hou/cor/is_same_signedness.hpp"
#include "hou/cor/narrow_cast.hpp"
#include "hou/cor/pragmas.hpp"
#include "hou/cor/std_array.hpp"
#include "hou/cor/template_utils.hpp"

#include <cmath>
#include <iostream>
#include <limits>



namespace hou
{

HOU_PRAGMA_PACK_PUSH(1)
/** Represents a matrix.
 *
 * The size of the matrix is static and the object is allocated on the stack.
 * The elements of a row are contiguous in memory and columns are contiguous
 * in memory.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows.
 *
 * \tparam Cols the number of columns.
 */
template <typename T, size_t Rows, size_t Cols>
class matrix
{
  static_assert(Rows > 0 && Cols > 0, "The matrix size must be at least 1x1.");

public:
  template <typename otherT, size_t otherRows, size_t otherCols>
  friend class matrix;

public:
  /** The value type. */
  using value_type = T;

  /** The size type. */
  using size_type = std::size_t;

  /** The index difference type. */
  using difference_type = std::ptrdiff_t;

  /** The reference type. */
  using reference = value_type&;

  /** The const reference type. */
  using const_reference = const reference;

  /** The pointer type. */
  using pointer = std::add_pointer_t<reference>;

  /** The const_pointer type. */
  using const_pointer = std::add_pointer_t<const_reference>;

  /** The underlying data representation. */
  using data_type = std::array<T, Rows * Cols>;

  /** The iterator type. */
  using iterator = typename data_type::iterator;

  /** The const iterator type. */
  using const_iterator = typename data_type::const_iterator;

  /** The reverse iterator type. */
  using reverse_iterator = typename data_type::reverse_iterator;

  /** The const reverse iterator type. */
  using const_reverse_iterator = typename data_type::const_reverse_iterator;

public:
  /** Get the number of rows of the matrix.
   *
   * \return the number of rows of the matrix.
   */
  inline static constexpr size_t get_row_count() noexcept;

  /** Get the number of columns of the matrix.
   *
   * \return the number of columns of the matrix.
   */
  inline static constexpr size_t get_column_count() noexcept;

  /** Get the number of elements of the matrix.
   *
   * The number of elements is equal to the number of rows times the number of
   * columns.
   *
   * \return the number of elements of the matrix.
   */
  inline static constexpr size_t size() noexcept;

  /** Returns the zero matrix.
   *
   * \return the zero matrix.
   */
  static constexpr matrix zero() noexcept;

  /** Returns a matrix with all elements set to a given value.
   *
   * \param value the value of the elements of the matrix.
   *
   * \return a matrix with all element set to value.
   */
  static constexpr matrix filled(T value) noexcept;

  /** Returns the identity matrix.
   *
   * \tparam RC the number of rows or columns.
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \return the identity matrix.
   */
  template <size_t RC = Rows,
    typename Enable = std::enable_if_t<Rows == RC && Cols == RC>>
  static constexpr matrix identity() noexcept;

  /** Returns a diagonal matrix with the given diagonal elements.
   *
   * \tparam RC the number of rows or columns.
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \param elements a vector containing the elements on the diagonal.
   *
   * \return a diagonal matrix with the given diagonal elements.
   */
  template <size_t RC = Rows,
    typename Enable = std::enable_if_t<Rows == RC && Cols == RC>>
  static constexpr matrix diagonal(const matrix<T, RC, 1u>& elements) noexcept;

  /** Returns a diagonal matrix with the given diagonal elements.
   *
   * \tparam RC the number of rows or columns.
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \param elements the list of diagonal elements.
   *
   * \return a diagonal matrix with the given diagonal elements.
   */
  template <typename... Args,
    typename Enable = std::enable_if_t<Rows == Cols && sizeof...(Args) == Rows>>
  static constexpr matrix diagonal(Args... elements) noexcept;

public:
  /** Creates a matrix with all elements initialized to 0.
   */
  constexpr matrix() noexcept;

  /** Creates a matrix from a matrix with same size but different scalar type.
   *
   * U must be convertible to T.
   *
   * \tparam U the scalar type of the other matrix.
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \param other the matrix to be copied.
   */
  template <typename U,
    typename Enable = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr matrix(const matrix<U, Rows, Cols>& other) noexcept;

  /** Creates a matrix from the given elements.
   *
   * Consider that the elements of a row are contiguous in memory. For example,
   * for a 2x3 matrix, the following sequence of elements:
   *
   *     (1, 2, 3, 4, 5, 6)
   *
   * would result in the following matrix:
   *
   *     (1, 2, 3)
   *     (4, 5, 6)
   *
   * \tparam Args variable list of elements.
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \param elements the matrix elements.
   */
  template <typename... Args,
    typename Enable = std::enable_if_t<sizeof...(Args) == Rows * Cols
      && conjunction<std::is_convertible<Args, T>::value...>::value>>
  constexpr matrix(Args... elements) noexcept;

  /** Retrieves a copy the element at the given index.
   *
   * Consider that elements in a row are contiguous. For example, for a 2x3
   * matrix, index 3 would correspond to the element at coordinates (1,0).
   *
   * An index equal or greater than the matrix size results in undefined
   * behaviour.
   *
   * \param index the index of the element.
   *
   * \return a copy of the element.
   */
  constexpr T operator[](size_t index) const noexcept;

  /** Retrieves a copy the element at the given index.
   *
   * Consider that elements in a row are contiguous. For example, for a 2x3
   * matrix, index 3 would correspond to the element at coordinates (1,0).
   *
   * An index equal or greater than the matrix size results in undefined
   * behaviour.
   *
   * \param index the index of the element.
   *
   * \return a copy of the element.
   */
  constexpr T& operator[](size_t index) noexcept;

  /** Retrieves a copy the element at the given index.
   *
   * Consider that elements in a row are contiguous. For example, for a 2x3
   * matrix, index 3 would correspond to the element at coordinates (1,0).
   *
   * \param index the index of the element.
   *
   * \throws hou::precondition_violation if index is not valid.
   *
   * \return a copy of the element.
   */
  constexpr T operator()(size_t index) const;

  /** Retrieves a reference to the element at the given index.
   *
   * Consider that elements in a row are contiguous. For example, for a 2x3
   * matrix, index 3 would correspond to the element at coordinates (1,0).
   *
   * \param index the index of the element.
   *
   * \throws hou::precondition_violation if index is not valid.
   *
   * \return a reference to the element
   */
  constexpr T& operator()(size_t index);

  /** Retrieves a copy of the element at the specified coordinates.
   *
   * \param row the row coordinate.
   *
   * \param col the column coordinate.
   *
   * \throws hou::precondition_violation if row or col are not valid.
   *
   * \return the copy of the element.
   */
  constexpr T operator()(size_t row, size_t col) const;

  /** Retrieves a reference to the element at the specified coordinates.
   *
   * \param row the row coordinate.
   *
   * \param col the column coordinate.
   *
   * \throws hou::precondition_violation if row or col are not valid.
   *
   * \return a reference to the element.
   */
  constexpr T& operator()(size_t row, size_t col);

  /** Retrieves a copy of the first element of a column vector.
   *
   * \tparam c the number of columns (should be left to the default value).
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \return a copy of the element.
   */
  template <size_t c = Cols,
    typename Enable = std::enable_if_t<(c == Cols && c == 1u)>>
  constexpr T x() const noexcept;

  /** Retrieves a reference to the first element of a column vector.
   *
   * \tparam c the number of columns (should be left to the default value).
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \return a reference to the element.
   */
  template <size_t c = Cols,
    typename Enable = std::enable_if_t<(c == Cols && c == 1u)>>
  constexpr T& x() noexcept;

  /** Retrieves a copy of the second element of a column vector.
   *
   * \tparam r the number of rows (should be left to the default value).
   *
   * \tparam c the number of columns (should be left to the default value).
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \return a copy of the element.
   */
  template <size_t r = Rows, size_t c = Cols,
    typename Enable
    = std::enable_if_t<(r == Rows && r > 1u && c == Cols && c == 1u)>>
  constexpr T y() const noexcept;

  /** Retrieves a reference to the second element of a column vector.
   *
   * \tparam r the number of rows (should be left to the default value).
   *
   * \tparam c the number of columns (should be left to the default value).
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \return a reference to the element.
   */
  template <size_t r = Rows, size_t c = Cols,
    typename Enable
    = std::enable_if_t<(r == Rows && r > 1u && c == Cols && c == 1u)>>
  constexpr T& y() noexcept;

  /** Retrieves a copy of the third element of a column vector.
   *
   * \tparam r the number of rows (should be left to the default value).
   *
   * \tparam c the number of columns (should be left to the default value).
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \return a copy of the element.
   */
  template <size_t r = Rows, size_t c = Cols,
    typename Enable
    = std::enable_if_t<(r == Rows && r > 2u && c == Cols && c == 1u)>>
  constexpr T z() const noexcept;

  /** Retrieves a reference to the third element of a column vector.
   *
   * \tparam r the number of rows (should be left to the default value).
   *
   * \tparam c the number of columns (should be left to the default value).
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \return a reference to the element.
   */
  template <size_t r = Rows, size_t c = Cols,
    typename Enable
    = std::enable_if_t<(r == Rows && r > 2u && c == Cols && c == 1u)>>
  constexpr T& z() noexcept;

  /** Retrieves a copy of the fourth element of a column vector.
   *
   * \tparam r the number of rows (should be left to the default value).
   *
   * \tparam c the number of columns (should be left to the default value).
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \return a copy of the element.
   */
  template <size_t r = Rows, size_t c = Cols,
    typename Enable
    = std::enable_if_t<(r == Rows && r > 3u && c == Cols && c == 1u)>>
  constexpr T w() const noexcept;

  /** Retrieves a reference to the fourth element of a column vector.
   *
   * \tparam r the number of rows (should be left to the default value).
   *
   * \tparam c the number of columns (should be left to the default value).
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \return a reference to the element.
   */
  template <size_t r = Rows, size_t c = Cols,
    typename Enable
    = std::enable_if_t<(r == Rows && r > 3u && c == Cols && c == 1u)>>
  constexpr T& w() noexcept;

  /** Retrieves a pointer to an array containing the matrix elements.
   *
   * The data is to be interpreted as a single array with size equal to the
   * number of elements of the matrix. Consider that elements in a row are
   * contiguous. For example, for a 2x3 matrix, the third element of the
   * array would correspond to the element at coordinates (1,0).
   *
   * \return a constant raw pointer to the matrix data.
   */
  constexpr const T* data() const noexcept;

  /** Retrieves a pointer to an array containing the matrix elements.
   *
   * The data is to be interpreted as a single array with size equal to the
   * number of elements of the matrix. Consider that elements in a row are
   * contiguous. For example, for a 2x3 matrix, the third element of the
   * array would correspond to the element at coordinates (1,0).
   *
   * \return a constant raw pointer to the matrix data.
   */
  constexpr T* data() noexcept;

  /** Gets an iterator to the first element of the buffer.
   *
   * \return an iterator to the first element of the buffer.
   */
  constexpr const_iterator begin() const noexcept;

  /** Gets an iterator to the first element of the buffer.
   *
   * \return an iterator to the first element of the buffer.
   */
  constexpr iterator begin() noexcept;

  /** Gets a const iterator to the first element of the buffer.
   *
   * \return const iterator to the first element of the buffer.
   */
  constexpr const_iterator cbegin() const noexcept;

  /** Gets a reverse iterator to the first element of the buffer.
   *
   * \return reverse iterator to the first element of the buffer.
   */
  constexpr const_reverse_iterator rbegin() const noexcept;

  /** Gets a reverse iterator to the first element of the buffer.
   *
   * \return reverse iterator to the first element of the buffer.
   */
  constexpr reverse_iterator rbegin() noexcept;

  /** Gets a constant reverse iterator to the first element of the buffer.
   *
   * \return constant reverse iterator to the first element of the buffer.
   */
  constexpr const_reverse_iterator crbegin() const noexcept;

  /** Gets an iterator to the position after the last element of the buffer.
   *
   * \return an iterator to the position after the last element of the buffer.
   */
  constexpr const_iterator end() const noexcept;

  /** Gets an iterator to the position after the last element of the buffer.
   *
   * \return an iterator to the position after the last element of the buffer.
   */
  constexpr iterator end() noexcept;

  /** Gets a constant iterator to the position after the last element of the
   * buffer.
   *
   * \return a constant iterator to the position after the last element of the
   * buffer.
   */
  constexpr const_iterator cend() const noexcept;

  /** Gets a reverse iterator to the position after the last element of the
   * buffer.
   *
   * \return a reverse iterator to the position after the last element of the
   * buffer.
   */
  constexpr const_reverse_iterator rend() const noexcept;

  /** Gets a reverse iterator to the position after the last element of the
   * buffer.
   *
   * \return a reverse iterator to the position after the last element of the
   * buffer.
   */
  constexpr reverse_iterator rend() noexcept;

  /** Gets a constant reverse iterator to the position after the last element of
   * the buffer.
   *
   * \return a constant reverse iterator to the position after the last element
   * of the buffer.
   */
  constexpr const_reverse_iterator crend() const noexcept;

  /** Sets the elements of the matrix to the given values.
   *
   * \tparam Args the list of elements.
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \param elements the matrix elements.
   */
  template <typename... Args,
    typename Enable = std::enable_if_t<sizeof...(Args) == Rows * Cols
      && conjunction<std::is_convertible<Args, T>::value...>::value>>
  constexpr void set(Args... elements) noexcept;

  /** Sets all elements of the matrix to the specified value.
   *
   * \param value the value to which th elements of the matrix have to be set.
   */
  constexpr void fill(T value) noexcept;

  /** Adds the given matrix to this matrix.
   *
   * The sum is element-wise.
   *
   * \param rhs the matrix to be added.
   *
   * \return a reference to this matrix after the addition.
   */
  constexpr matrix& operator+=(const matrix& rhs) noexcept;

  /** Subtracts the given matrix from this matrix.
   *
   * The difference is element-wise.
   *
   * \param rhs the matrix to be subtracted.
   *
   * \return a reference to this matrix after the subtraction.
   */
  constexpr matrix& operator-=(const matrix& rhs) noexcept;

  /** Multiplies this matrix by the given scalar.
   *
   * All elements of the matrix are multiplied by the given scalar.
   *
   * \param rhs the scalar factor.
   *
   * \return a reference to this matrix after the multiplication.
   */
  constexpr matrix& operator*=(T rhs) noexcept;

  /** Divides this matrix by the given scalar.
   *
   * All elements of the matrix are divided by the given scalar.
   *
   * \param rhs the scalar divisor.
   *
   * \return a reference to this matrix after the division.
   */
  constexpr matrix& operator/=(T rhs) noexcept;

  /** Adjugates this matrix.
   *
   * \tparam RC the number of rows or columns.
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \return a reference to this matrix after the operation.
   */
  template <size_t RC = Rows,
    typename Enable = std::enable_if_t<Rows == RC && Cols == RC>>
  constexpr matrix& adjugate() noexcept;

  /** Inverts this matrix.
   *
   * \tparam RC the number of rows or columns.
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \throws hou::precondition if the determinant of the matrix is 0.
   *
   * \return a reference to this matrix after the inversion.
   */
  template <size_t RC = Rows,
    typename Enable = std::enable_if_t<Rows == RC && Cols == RC>>
  constexpr matrix& invert();

  /** Normalizes the matrix.
   *
   * \throws hou::precondition_violation if the norm of the matrix is 0.
   *
   * \return a reference to this matrix after normalization.
   */
  constexpr matrix& normalize();

  /** Multiplies a matrix by a scalar.
   *
   * All elements of the matrix are multiplied by the given scalar.
   *
   * \param lhs the matrix.
   *
   * \param rhs the scalar factor.
   *
   * \return the result of the multiplication.
   */
  friend constexpr matrix<T, Rows, Cols> operator*(
    matrix<T, Rows, Cols> lhs, T rhs) noexcept
  {
    return lhs *= rhs;
  }

  /** Divides a matrix by a scalar.
   *
   * All elements of the matrix are divided by the given scalar.
   *
   * \param lhs the matrix.
   *
   * \param rhs the scalar divisor.
   *
   * \return the result of the division.
   */
  friend constexpr matrix<T, Rows, Cols> operator/(
    matrix<T, Rows, Cols> lhs, T rhs) noexcept
  {
    return lhs /= rhs;
  }

  /** Multiplies a matrix by a scalar.
   *
   * All elements of the matrix are multiplied by the given scalar.
   *
   * \param lhs the scalar factor.
   *
   * \param rhs the matrix.
   *
   * \return the result of the multiplication.
   */
  friend constexpr matrix<T, Rows, Cols> operator*(
    T lhs, matrix<T, Rows, Cols> rhs) noexcept
  {
    return rhs *= lhs;
  }

  // Friend functions.
  template <typename U, size_t R, size_t C>
  friend constexpr matrix<U, R, C> operator-(matrix<U, R, C> m) noexcept;

  template <typename U, size_t R, size_t C>
  friend bool operator==(
    const matrix<U, R, C>& lhs, const matrix<U, R, C>& rhs) noexcept;

  template <typename U, size_t R, size_t C>
  friend bool operator!=(
    const matrix<U, R, C>& lhs, const matrix<U, R, C>& rhs) noexcept;

  template <typename U, size_t R, size_t C>
  friend bool close(
    const matrix<U, R, C>& lhs, const matrix<U, R, C>& rhs, U acc) noexcept;

private:
  data_type m_elements;
};
HOU_PRAGMA_PACK_POP()

/** Sums two matrices.
 *
 * The sum is element-wise.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows.
 *
 * \tparam Cols the number of columns.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the sum of the two matrices.
 */
template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols> operator+(
  matrix<T, Rows, Cols> lhs, const matrix<T, Rows, Cols>& rhs) noexcept;

/** Subtracts two matrices.
 *
 * The difference is element-wise.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows.
 *
 * \tparam Cols the number of columns.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the difference of the two matrices.
 */
template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols> operator-(
  matrix<T, Rows, Cols> lhs, const matrix<T, Rows, Cols>& rhs) noexcept;

/** Computes the opposite of a matrix.
 *
 * All elements of the resulting matrix are the opposite of the corresponding
 * original elements.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows.
 *
 * \tparam Cols the number of columns.
 *
 * \param m the matrix.
 *
 * \return the opposite matrix.
 */
template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols> operator-(matrix<T, Rows, Cols> m) noexcept;

/** Multiplies two matrices.
 *
 * The result is the row-column product between the two matrices.
 * The number of columns of the left matrix must be equal to the number of
 * columns of the right matrix.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows of lhs.
 *
 * \tparam Mid the number of columns of lhs and rows of rhs.
 *
 * \tparam Cols the number of columns of rhs.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the row-column product of the two matrices.
 */
template <typename T, size_t Rows, size_t Mid, size_t Cols>
constexpr matrix<T, Rows, Cols> operator*(
  const matrix<T, Rows, Mid>& lhs, const matrix<T, Mid, Cols>& rhs) noexcept;

/** Computes the determinant of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \tparam T the scalar type.
 *
 * \param m the input matrix.
 *
 * \return the determinant of the given matrix.
 */
template <typename T>
constexpr T det(const matrix<T, 1, 1>& m) noexcept;

/** Computes the determinant of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \param m the input matrix.
 *
 * \return the determinant of the given matrix.
 */
template <typename T>
constexpr T det(const matrix<T, 2, 2>& m) noexcept;

/** Computes the determinant of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \param m the input matrix.
 *
 * \return the determinant of the given matrix.
 */
template <typename T>
constexpr T det(const matrix<T, 3, 3>& m) noexcept;

/** Computes the determinant of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \tparam RC = the number of rows or columns.
 *
 * \tparam Enable enabling parameter (can be left to the default value).
 *
 * \param m the input matrix.
 *
 * \return the determinant of the given matrix.
 */
template <typename T, size_t RC, typename Enable = std::enable_if_t<(RC > 3)>>
constexpr T det(const matrix<T, RC, RC>& m) noexcept;

/** Computes the trace of the given square matrix.
 *
 * \tparam T the scalar type.
 *
 * \tparam RC the number of rows and columns of the matrix.
 *
 * \param m the matrix.
 *
 * \return the trace of the given matrix.
 */
template <typename T, size_t RC>
constexpr T trace(const matrix<T, RC, RC>& m) noexcept;

/** Removes a row and a column from a matrix.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows.
 *
 * \tparam Cols the number of columns.
 *
 * \tparam Enable enabling parameter (can be left to the default value).
 *
 * \param m the matrix to be reduced.
 *
 * \param row the row to be removed.
 *
 * \param col the column to be removed.
 *
 * \throws hou::precondition_violation if row or col are invalid.
 *
 * \return a matrix equal to m but with the the specified row and column
 * removed.
 */
// Not a member function because returns a different type.
template <typename T, size_t Rows, size_t Cols,
  typename Enable = std::enable_if_t<(Rows > 1 && Cols > 1)>>
constexpr matrix<T, Rows - 1, Cols - 1> reduce(
  const matrix<T, Rows, Cols>& m, size_t row, size_t col);

/** Computes the transpose of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows.
 *
 * \tparam Cols the number of columns.
 *
 * \param m the matrix to be transposed.
 *
 * \return the transpose of the given matrix.
 */
// No member function because returns a different type.
template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Cols, Rows> transpose(
  const matrix<T, Rows, Cols>& m) noexcept;

/** Computes the adjugate of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \param m the input matrix.
 *
 * \return the adjugate of the given matrix.
 */
template <typename T>
constexpr matrix<T, 1, 1> adjugate(const matrix<T, 1, 1>& m) noexcept;

/** Computes the adjugate of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \param m the input matrix.
 *
 * \return the adjugate of the given matrix.
 */
template <typename T>
constexpr matrix<T, 2, 2> adjugate(const matrix<T, 2, 2>& m) noexcept;

/** Computes the adjugate of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \tparam RC the number of rows or columns.
 *
 * \tparam Enable enabling parameter (can be left to the default value).
 *
 * \param m the input matrix.
 *
 * \return the adjugate of the given matrix.
 */
template <typename T, size_t RC, typename Enable = std::enable_if_t<(RC > 2)>>
constexpr matrix<T, RC, RC> adjugate(const matrix<T, RC, RC>& m) noexcept;

/** Computes the inverse of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \tparam RC the number of rows or columns.
 *
 * \param m the input matrix.
 *
 * \throws hou::precondition if the determinant of the matrix is 0.
 *
 * \return the inverse of the given matrix.
 */
template <typename T, size_t RC>
constexpr matrix<T, RC, RC> inverse(matrix<T, RC, RC> m);

/** Computes the square norm of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows.
 *
 * \tparam Cols the number of columns.
 *
 * \param m the input matrix.
 *
 * \return the square norm.
 */
template <typename T, size_t Rows, size_t Cols>
constexpr T square_norm(const matrix<T, Rows, Cols>& m) noexcept;

/** Computes the norm of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows.
 *
 * \tparam Cols the number of columns.
 *
 * \param m the input matrix.
 *
 * \return the norm.
 */
template <typename T, size_t Rows, size_t Cols>
constexpr T norm(const matrix<T, Rows, Cols>& m) noexcept;

/** Computes the normalized matrix.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows.
 *
 * \tparam Cols the number of columns.
 *
 * \param m the input matrix.
 *
 * \throws hou::precondition_violation if the norm of the matrix is 0.
 *
 * \return the normalized matrix.
 */
template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols> normalized(matrix<T, Rows, Cols> m);

/** Computes the cross product matrix associated to the given 3d vector.
 *
 * \tparam T the scalar type.
 *
 * \param m a 3d vector.
 *
 * \return the cross product matrix.
 */
template <typename T>
constexpr matrix<T, 3u, 3u> cross_matrix(const matrix<T, 3u, 1u>& m) noexcept;

/** Computes the cross product of a 2d vector.
 *
 * \tparam T the scalar type.
 *
 * \param v the vector.
 *
 * \return the cross product of the 2d vector.
 */
template <typename T>
constexpr matrix<T, 2u, 1u> cross(const matrix<T, 2u, 1u>& v) noexcept;

/** Computes the cross product between two 3d vectors.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the cross product result.
 */
template <typename T>
constexpr matrix<T, 3u, 1u> cross(
  const matrix<T, 3u, 1u>& lhs, const matrix<T, 3u, 1u>& rhs) noexcept;

/** Computes the outer product between the two given 3d vectors.
 *
 * \tparam T the scalar type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the outer product result.
 */
template <typename T>
constexpr matrix<T, 3u, 3u> outer_product(
  const matrix<T, 3u, 1u>& lhs, const matrix<T, 3u, 1u>& rhs) noexcept;

/** Computes the dot product between the two given vectors.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the size of the vector.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the dot product.
 */
template <typename T, size_t Rows>
constexpr T dot(
  const matrix<T, Rows, 1u>& lhs, const matrix<T, Rows, 1u>& rhs) noexcept;

/** Checks if two matrices are equal.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows.
 *
 * \tparam Cols the number of columns.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
template <typename T, size_t Rows, size_t Cols>
bool operator==(
  const matrix<T, Rows, Cols>& lhs, const matrix<T, Rows, Cols>& rhs) noexcept;

/** Checks if two matrices are not equal.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows.
 *
 * \tparam Cols the number of columns.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
template <typename T, size_t Rows, size_t Cols>
bool operator!=(
  const matrix<T, Rows, Cols>& lhs, const matrix<T, Rows, Cols>& rhs) noexcept;

/** Checks if two matrices are equal with the specified accuracy.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows.
 *
 * \tparam Cols the number of columns.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \param acc the accuracy.
 *
 * \return the result of the check.
 */
template <typename T, size_t Rows, size_t Cols>
bool close(const matrix<T, Rows, Cols>& lhs, const matrix<T, Rows, Cols>& rhs,
  T acc = std::numeric_limits<T>::epsilon()) noexcept;

/** Writes the object into a stream.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows.
 *
 * \tparam Cols the number of columns.
 *
 * \param os the stream.
 *
 * \param m the matrix.
 *
 * \return a reference to the stream.
 */
template <typename T, size_t Rows, size_t Cols>
std::ostream& operator<<(std::ostream& os, const matrix<T, Rows, Cols>& m);

/** Specialization of check_matching_sign for matrix.
 *
 * \tparam T the first scalar type.
 *
 * \tparam U the second scalar type.
 *
 * \tparam Rows the number of rows in the matrix.
 *
 * \tparam Cols the number of columns in the matrix.
 */
template <typename T, typename U, size_t Rows, size_t Cols>
class check_matching_sign<matrix<T, Rows, Cols>, matrix<U, Rows, Cols>>
{
private:
  using t_matrix = matrix<T, Rows, Cols>;
  using u_matrix = matrix<U, Rows, Cols>;

public:
  /** Checks if t and u have matching sign.
   *
   * \param t the first parameter.
   *
   * \param u the second parameter.
   *
   * \return true if the signs of t and u match.
   */
  static bool check(const t_matrix& t, const u_matrix& u)
  {
    HOU_DEV_ASSERT(t.size() == u.size());
    for(size_t i = 0; i < t.size(); ++i)
    {
      if((t[i] < T(0)) != (u[i] < U(0)))
      {
        return false;
      }
    }
    return true;
  }
};

}  // namespace hou



namespace std
{

/** Specialization of std::is_signed for hou::matrix.
 *
 * \tparam T the scalar type.
 *
 * \tparam Rows the number of rows in the matrix.
 *
 * \tparam Cols the number of columns in the matrix.
 */
template <typename T, size_t Rows, size_t Cols>
struct is_signed<::hou::matrix<T, Rows, Cols>>
  : public integral_constant<bool, is_signed<T>::value>
{};

}  // namespace std



#include "hou/mth/matrix.inl"

#endif
