// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_MATRIX_HPP
#define HOU_MTH_MATRIX_HPP

#include "hou/mth/mth_export.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/deprecated_error.hpp"
#include "hou/cor/std_array.hpp"
#include "hou/cor/template_utils.hpp"

#include "hou/mth/matrix_fwd.hpp"

#include <cmath>
#include <initializer_list>
#include <iostream>
#include <limits>



namespace hou
{

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
  /** Get the number of rows of the matrix.
   *
   * \return the number of rows of the matrix.
   */
  inline static constexpr size_t get_row_count();

  /** Get the number of columns of the matrix.
   *
   * \return the number of columns of the matrix.
   */
  inline static constexpr size_t get_column_count();

  /** Get the number of elements of the matrix.
   *
   * The number of elements is equal to the number of rows times the number of
   * columns.
   *
   * \return the number of elements of the matrix.
   */
  inline static constexpr size_t get_size();

  /** Returns the zero matrix.
   *
   * \return the zero matrix.
   */
  static matrix zero();

  /** Returns a matrix with all elements set to a given value.
   *
   * \param value the value of the elements of the matrix.
   *
   * \return a matrix with all element set to value.
   */
  static matrix filled(T value);

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
  static matrix identity();

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
  static matrix diagonal(const matrix<T, RC, 1u>& elements);

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
  static matrix diagonal(Args... elements);

public:
  /** Creates a matrix with all elements initialized to 0.
   */
  matrix();

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
  matrix(const matrix<U, Rows, Cols>& other);

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
  matrix(Args... elements);

  /** Creates a matrix from the elements given in the initializer list.
   *
   * Consider that the elements of a row are contiguous in memory. For example,
   * for a 2x3 matrix, the following initializer list:
   *
   *     {1, 2, 3, 4, 5, 6}
   *
   * would result in the following matrix:
   *
   *     (1, 2, 3)
   *     (4, 5, 6)
   *
   * Throws if the size of the initializer list is different from the size of
   * the matrix.
   *
   * \param elements an initializer list containing the elements of the matrix.
   */
  matrix(std::initializer_list<T> elements);

  /** Destructor.
   */
  virtual ~matrix();

  /** Retrieves a copy of the element at the specified coordinates.
   *
   * \param row the row coordinate.
   *
   * \param col the column coordinate.
   *
   * \return the copy of the element.
   */
  T operator()(size_t row, size_t col) const;

  /** Retrieves a reference to the element at the specified coordinates.
   *
   * \param row the row coordinate.
   *
   * \param col the column coordinate.
   *
   * \return a reference to the element.
   */
  T& operator()(size_t row, size_t col);

  /** Retrieves a copy the element at the given index.
   *
   * Consider that elements in a row are contiguous. For example, for a 2x3
   * matrix, index 3 would correspond to the element at coordinates (1,0).
   *
   * \param index the index of the element.
   *
   * \return a copy of the element.
   */
  T operator()(size_t index) const;

  /** Retrieves a reference to the element at the given index.
   *
   * Consider that elements in a row are contiguous. For example, for a 2x3
   * matrix, index 3 would correspond to the element at coordinates (1,0).
   *
   * \param index the index of the element.
   *
   * \return a reference to the element
   */
  T& operator()(size_t index);

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
  T x() const;

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
  T& x();

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
  T y() const;

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
  T& y();

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
  T z() const;

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
  T& z();

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
  T w() const;

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
  T& w();

  /** Retrieves a pointer to an array containing the matrix elements.
   *
   * The data is to be interpreted as a single array with size equal to the
   * number of elements of the matrix. Consider that elements in a row are
   * contiguous. For example, for a 2x3 matrix, the third element of the
   * array would correspond to the element at coordinates (1,0).
   *
   * \return a constant raw pointer to the matrix data.
   */
  const T* data() const;

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
  void set(Args... elements);

  /** Sets all elements of the matrix to the specified value.
   *
   * \param value the value to which th elements of the matrix have to be set.
   */
  void fill(T value);

  /** Adds the given matrix to this matrix.
   *
   * The sum is element-wise.
   *
   * \param rhs the matrix to be added.
   *
   * \return a reference to this matrix after the addition.
   */
  matrix& operator+=(const matrix& rhs);

  /** Subtracts the given matrix from this matrix.
   *
   * The difference is element-wise.
   *
   * \param rhs the matrix to be subtracted.
   *
   * \return a reference to this matrix after the subtraction.
   */
  matrix& operator-=(const matrix& rhs);

  /** Multiplies this matrix by the given scalar.
   *
   * All elements of the matrix are multiplied by the given scalar.
   *
   * \param rhs the scalar factor.
   *
   * \return a reference to this matrix after the multiplication.
   */
  matrix& operator*=(T rhs);

  /** Divides this matrix by the given scalar.
   *
   * All elements of the matrix are divided by the given scalar.
   *
   * \param rhs the scalar divisor.
   *
   * \return a reference to this matrix after the division.
   */
  matrix& operator/=(T rhs);

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
  matrix& adjugate();

  /** Inverts this matrix.
   *
   * \tparam RC the number of rows or columns.
   *
   * \tparam Enable enabling parameter (can be left to the default value).
   *
   * \return a reference to this matrix after the inversion.
   */
  template <size_t RC = Rows,
    typename Enable = std::enable_if_t<Rows == RC && Cols == RC>>
  matrix& invert();

  /** Normalizes the matrix.
   *
   * \return a reference to this matrix after normalization.
   */
  matrix& normalize();

  /** Computes the opposite of a matrix.
   *
   * All elements of the resulting matrix are the opposite of the corresponding
   * original elements.
   *
   * \param m the matrix.
   *
   * \return the opposite matrix.
   */
  friend matrix operator-(matrix m)
  {
    for(size_t i = 0; i < m.get_size(); ++i)
    {
      m.m_elements[i] = -m.m_elements[i];
    }
    return m;
  }

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
  friend matrix operator*(matrix lhs, T rhs)
  {
    return lhs *= rhs;
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
  friend matrix operator*(T lhs, matrix rhs)
  {
    return rhs *= lhs;
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
  friend matrix operator/(matrix lhs, T rhs)
  {
    return lhs /= rhs;
  }

  /** Checks if two matrices are equal.
   *
   * \param lhs the left operand.
   *
   * \param rhs the right operand.
   *
   * \return the result of the check.
   */
  friend bool operator==(const matrix& lhs, const matrix& rhs)
  {
    return lhs.m_elements == rhs.m_elements;
  }

  /** Checks if two matrices are not equal.
   *
   * \param lhs the left operand.
   *
   * \param rhs the right operand.
   *
   * \return the result of the check.
   */
  friend bool operator!=(const matrix& lhs, const matrix& rhs)
  {
    return lhs.m_elements != rhs.m_elements;
  }

  /** Checks if two matrices are equal with the specified accuracy.
   *
   * \param lhs the left operand.
   *
   * \param rhs the right operand.
   *
   * \param acc the accuracy.
   *
   * \return the result of the check.
   */
  friend bool close(const matrix<T, Rows, Cols>& lhs,
    const matrix<T, Rows, Cols>& rhs, T acc = std::numeric_limits<T>::epsilon())
  {
    return close(lhs.m_elements, rhs.m_elements, acc);
  }

private:
  std::array<T, Rows * Cols> m_elements;
};

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
matrix<T, Rows, Cols> operator+(
  matrix<T, Rows, Cols> lhs, const matrix<T, Rows, Cols>& rhs);

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
matrix<T, Rows, Cols> operator-(
  matrix<T, Rows, Cols> lhs, const matrix<T, Rows, Cols>& rhs);

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
matrix<T, Rows, Cols> operator*(
  const matrix<T, Rows, Mid>& lhs, const matrix<T, Mid, Cols>& rhs);

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
T det(const matrix<T, 1, 1>& m);

/** Computes the determinant of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \param m the input matrix.
 *
 * \return the determinant of the given matrix.
 */
template <typename T>
T det(const matrix<T, 2, 2>& m);

/** Computes the determinant of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \param m the input matrix.
 *
 * \return the determinant of the given matrix.
 */
template <typename T>
T det(const matrix<T, 3, 3>& m);

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
T trace(const matrix<T, RC, RC>& m);

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
T det(const matrix<T, RC, RC>& m);

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
 * \return a matrix equal to m but with the the specified row and column
 * removed.
 */
// Not a member function because returns a different type.
template <typename T, size_t Rows, size_t Cols,
  typename Enable = std::enable_if_t<(Rows > 1 && Cols > 1)>>
matrix<T, Rows - 1, Cols - 1> reduce(
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
matrix<T, Cols, Rows> transpose(const matrix<T, Rows, Cols>& m);

/** Computes the adjugate of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \param m the input matrix.
 *
 * \return the adjugate of the given matrix.
 */
template <typename T>
matrix<T, 1, 1> adjugate(const matrix<T, 1, 1>& m);

/** Computes the adjugate of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \param m the input matrix.
 *
 * \return the adjugate of the given matrix.
 */
template <typename T>
matrix<T, 2, 2> adjugate(const matrix<T, 2, 2>& m);

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
matrix<T, RC, RC> adjugate(const matrix<T, RC, RC>& m);

/** Computes the inverse of the given matrix.
 *
 * \tparam T the scalar type.
 *
 * \tparam RC the number of rows or columns.
 *
 * \param m the input matrix.
 *
 * \return the inverse of the given matrix.
 */
template <typename T, size_t RC>
matrix<T, RC, RC> inverse(matrix<T, RC, RC> m);

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
T square_norm(const matrix<T, Rows, Cols>& m);

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
T norm(const matrix<T, Rows, Cols>& m);

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
 * \return the normalized matrix.
 */
template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols> normalized(matrix<T, Rows, Cols> m);

/** Computes the cross product matrix associated to the given 3d vector.
 *
 * \tparam T the scalar type.
 *
 * \param m a 3d vector.
 *
 * \return the cross product matrix.
 */
template <typename T>
matrix<T, 3u, 3u> cross_matrix(const matrix<T, 3u, 1u>& m);

/** Computes the cross product of a 2d vector.
 *
 * \tparam T the scalar type.
 *
 * \param v the vector.
 *
 * \return the cross product of the 2d vector.
 */
template <typename T>
matrix<T, 2u, 1u> cross(const matrix<T, 2u, 1u>& v);

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
matrix<T, 3u, 1u> cross(
  const matrix<T, 3u, 1u>& lhs, const matrix<T, 3u, 1u>& rhs);

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
matrix<T, 3u, 3u> outer_product(
  const matrix<T, 3u, 1u>& lhs, const matrix<T, 3u, 1u>& rhs);

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
T dot(const matrix<T, Rows, 1u>& lhs, const matrix<T, Rows, 1u>& rhs);

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

}  // namespace hou



#include "hou/mth/matrix.inl"

#endif
