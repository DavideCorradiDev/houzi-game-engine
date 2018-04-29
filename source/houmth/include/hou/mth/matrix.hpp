// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_MATRIX_HPP
#define HOU_MTH_MATRIX_HPP

#include "hou/mth/mth_export.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/error.hpp"
#include "hou/cor/std_array.hpp"
#include "hou/cor/template_utils.hpp"

#include "hou/mth/matrix_fwd.hpp"

#include <cmath>
#include <initializer_list>
#include <iostream>
#include <limits>



namespace hou
{

/** Represents a ph_matrix.
 *
 *  The size of the ph_matrix is static and the object is allocated on the stack.
 *  The elements of a row are contiguous in memory and columns are contiguous
 *  in memory.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 */
template <typename T, size_t rows, size_t cols>
  class matrix
{
  static_assert(rows > 0 && cols > 0, "matrix size must be at least 1x1.");

public:
  template <typename otherT, size_t otherRows, size_t otherCols>
    friend class matrix;

public:
  /** Get the number of rows of the ph_matrix.
   *
   *  \return the number of rows of the ph_matrix.
   */
  inline static constexpr size_t get_row_count();

  /** Get the number of columns of the ph_matrix.
   *
   *  \return the number of columns of the ph_matrix.
   */
  inline static constexpr size_t get_column_count();

  /** Get the number of elements of the ph_matrix.
   *
   *  The number of elements is equal to the number of rows times the number of
   *  columns.
   *
   *  \return the number of elements of the ph_matrix.
   */
  inline static constexpr size_t get_size();

  /** Returns the zero ph_matrix.
   *
   *  \return the zero ph_matrix.
   */
  static matrix zero();

  /** Returns a ph_matrix with all elements set to a given value.
   *
   *  \param value the value of the elements of the ph_matrix.
   *  \return a ph_matrix with all element set to value.
   */
  static matrix filled(T value);

  /** Returns the identity ph_matrix.
   *
   *  \tparam rc the number of rows or columns.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return the identity ph_matrix.
   */
  template <size_t rc = rows
    , typename Enable = std::enable_if_t<rows == rc && cols == rc>>
    static matrix identity();

  /** Returns a diagonal ph_matrix with the given diagonal elements.
   *
   *  \tparam rc the number of rows or columns.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \param elements a vector containing the elements on the diagonal.
   *  \return a diagonal ph_matrix with the given diagonal elements.
   */
  template <size_t rc = rows
    , typename Enable = std::enable_if_t<rows == rc && cols == rc>>
    static matrix diagonal(const matrix<T, rc, 1u>& elements);

  /** Returns a diagonal ph_matrix with the given diagonal elements.
   *
   *  \tparam rc the number of rows or columns.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \param elements the list of diagonal elements.
   *  \return a diagonal ph_matrix with the given diagonal elements.
   */
  template <typename... Args
    , typename Enable = std::enable_if_t
    <rows == cols && sizeof...(Args) == rows>>
    static matrix diagonal(Args... elements);

public:
  /** Creates a ph_matrix with all elements initialized to 0.
   */
  matrix();

  /** Creates a ph_matrix from a ph_matrix with same size but different scalar type.
   *
   *  U must be convertible to T.
   *
   *  \tparam U the scalar type of the other ph_matrix.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \param other the ph_matrix to be copied.
   */
  template <typename U
    , typename Enable = std::enable_if_t<std::is_convertible<U, T>::value>>
    matrix(const matrix<U, rows, cols>& other);

  /** Creates a ph_matrix from the given elements.
   *
   *  Consider that the elements of a row are contiguous in memory. For example,
   *  for a 2x3 ph_matrix, the following sequence of elements:
   *
   *      (1, 2, 3, 4, 5, 6)
   *
   *  would result in the following ph_matrix:
   *
   *      (1, 2, 3)
   *      (4, 5, 6)
   *
   *  \tparam Args variable list of elements.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \param elements the ph_matrix elements.
   */
  template <typename... Args
    , typename Enable = std::enable_if_t
    < sizeof...(Args) == rows * cols
    && conjunction<std::is_convertible<Args, T>::value...>::value>>
    matrix(Args... elements);

  /** Creates a ph_matrix from the elements given in the initializer list.
   *
   *  Consider that the elements of a row are contiguous in memory. For example,
   *  for a 2x3 ph_matrix, the following initializer list:
   *
   *      {1, 2, 3, 4, 5, 6}
   *
   *  would result in the following ph_matrix:
   *
   *      (1, 2, 3)
   *      (4, 5, 6)
   *
   *  Throws if the size of the initializer list is different from the size of
   *  the ph_matrix.
   *
   *  \param elements an initializer list containing the elements of the ph_matrix.
   */
  matrix(std::initializer_list<T> elements);

  /** Destructor.
   */
  virtual ~matrix();

  /** Retrieves a copy of the element at the specified coordinates.
   *
   *  \param row the row coordinate.
   *  \param col the column coordinate.
   *  \return the copy of the element.
   */
  T operator()(size_t row, size_t col) const;

  /** Retrieves a reference to the element at the specified coordinates.
   *
   *  \param row the row coordinate.
   *  \param col the column coordinate.
   *  \return a reference to the element.
   */
  T& operator()(size_t row, size_t col);

  /** Retrieves a copy the element at the given index.
   *
   *  Consider that elements in a row are contiguous. For example, for a 2x3
   *  ph_matrix, index 3 would correspond to the element at coordinates (1,0).
   *
   *  \param index the index of the element.
   *  \return a copy of the element.
   */
  T operator()(size_t index) const;

  /** Retrieves a reference to the element at the given index.
   *
   *  Consider that elements in a row are contiguous. For example, for a 2x3
   *  ph_matrix, index 3 would correspond to the element at coordinates (1,0).
   *
   *  \param index the index of the element.
   *  \return a reference to the element
   */
  T& operator()(size_t index);

  /** Retrieves a copy of the first element of a column vector.
   *
   *  \tparam c the number of columns (should be left to the default value).
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return a copy of the element.
   */
  template <size_t c = cols
    , typename Enable = std::enable_if_t<(c == cols && c == 1u)>>
    T x() const;

  /** Retrieves a reference to the first element of a column vector.
   *
   *  \tparam c the number of columns (should be left to the default value).
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return a reference to the element.
   */
  template <size_t c = cols
    , typename Enable = std::enable_if_t<(c == cols && c == 1u)>>
    T& x();

  /** Retrieves a copy of the second element of a column vector.
   *
   *  \tparam r the number of rows (should be left to the default value).
   *  \tparam c the number of columns (should be left to the default value).
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return a copy of the element.
   */
  template <size_t r = rows, size_t c = cols, typename Enable
    = std::enable_if_t<(r == rows && r > 1u && c == cols && c == 1u)>>
    T y() const;

  /** Retrieves a reference to the second element of a column vector.
   *
   *  \tparam r the number of rows (should be left to the default value).
   *  \tparam c the number of columns (should be left to the default value).
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return a reference to the element.
   */
  template <size_t r = rows, size_t c = cols, typename Enable
    = std::enable_if_t<(r == rows && r > 1u && c == cols && c == 1u)>>
    T& y();

  /** Retrieves a copy of the third element of a column vector.
   *
   *  \tparam r the number of rows (should be left to the default value).
   *  \tparam c the number of columns (should be left to the default value).
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return a copy of the element.
   */
  template <size_t r = rows, size_t c = cols, typename Enable
    = std::enable_if_t<(r == rows && r > 2u && c == cols && c == 1u)>>
    T z() const;

  /** Retrieves a reference to the third element of a column vector.
   *
   *  \tparam r the number of rows (should be left to the default value).
   *  \tparam c the number of columns (should be left to the default value).
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return a reference to the element.
   */
  template <size_t r = rows, size_t c = cols, typename Enable
    = std::enable_if_t<(r == rows && r > 2u && c == cols && c == 1u)>>
    T& z();

  /** Retrieves a copy of the fourth element of a column vector.
   *
   *  \tparam r the number of rows (should be left to the default value).
   *  \tparam c the number of columns (should be left to the default value).
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return a copy of the element.
   */
  template <size_t r = rows, size_t c = cols, typename Enable
    = std::enable_if_t<(r == rows && r > 3u && c == cols && c == 1u)>>
    T w() const;

  /** Retrieves a reference to the fourth element of a column vector.
   *
   *  \tparam r the number of rows (should be left to the default value).
   *  \tparam c the number of columns (should be left to the default value).
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return a reference to the element.
   */
  template <size_t r = rows, size_t c = cols, typename Enable
    = std::enable_if_t<(r == rows && r > 3u && c == cols && c == 1u)>>
    T& w();

  /** Retrieves a pointer to an array containing the ph_matrix elements.
   *
   *  The data is to be interpreted as a single array with size equal to the
   *  number of elements of the ph_matrix. Consider that elements in a row are
   *  contiguous. For example, for a 2x3 ph_matrix, the third element of the
   *  array would correspond to the element at coordinates (1,0).
   *
   *  \return a constant raw pointer to the ph_matrix data.
   */
  const T* data() const;

  /** Sets the elements of the ph_matrix to the given values.
   *
   *  \tparam Args the list of elements.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \param elements the ph_matrix elements.
   */
  template <typename... Args
    , typename Enable = std::enable_if_t
    < sizeof...(Args) == rows * cols
    && conjunction<std::is_convertible<Args, T>::value...>::value>>
    void set(Args... elements);

  /** Sets all elements of the ph_matrix to the specified value.
   *
   *  \param value the value to which th elements of the ph_matrix have to be set.
   */
  void fill(T value);

  /** Adds the given ph_matrix to this ph_matrix.
   *
   *  The sum is element-wise.
   *
   *  \param rhs the ph_matrix to be added.
   *  \return a reference to this ph_matrix after the addition.
   */
  matrix& operator+=(const matrix& rhs);

  /** Subtracts the given ph_matrix from this ph_matrix.
   *
   *  The difference is element-wise.
   *
   *  \param rhs the ph_matrix to be subtracted.
   *  \return a reference to this ph_matrix after the subtraction.
   */
  matrix& operator-=(const matrix& rhs);

  /** Multiplies this ph_matrix by the given scalar.
   *
   *  all elements of the ph_matrix are multiplied by the given scalar.
   *
   *  \param rhs the scalar factor.
   *  \return a reference to this ph_matrix after the multiplication.
   */
  matrix& operator*=(T rhs);

  /** Divides this ph_matrix by the given scalar.
   *
   *  all elements of the ph_matrix are divided by the given scalar.
   *
   *  \param rhs the scalar divisor.
   *  \return a reference to this ph_matrix after the division.
   */
  matrix& operator/=(T rhs);

  /** Adjugates this ph_matrix.
   *
   *  \tparam rc the number of rows or columns.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return a reference to this ph_matrix after the operation.
   */
  template <size_t rc = rows
    , typename Enable = std::enable_if_t<rows == rc && cols == rc>>
    matrix& adjugate();

  /** Inverts this ph_matrix.
   *
   *  \tparam rc the number of rows or columns.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return a reference to this ph_matrix after the inversion.
   */
  template <size_t rc = rows
    , typename Enable = std::enable_if_t<rows == rc && cols == rc>>
    matrix& invert();

  /** Normalizes the ph_matrix.
   *
   *  \return a reference to this ph_matrix after normalization.
   */
  matrix& normalize();

  /** Computes the opposite of a ph_matrix.
   *
   *  all elements of the resulting ph_matrix are the opposite of the corresponding
   *  original elements.
   *
   *  \param m the ph_matrix.
   *  \return the opposite ph_matrix.
   */
  friend matrix operator-(matrix m)
  {
    for(size_t i = 0; i < m.get_size(); ++i)
    {
      m.m_elements[i] = -m.m_elements[i];
    }
    return m;
  }

  /** Multiplies a ph_matrix by a scalar.
   *
   *  all elements of the ph_matrix are multiplied by the given scalar.
   *
   *  \param lhs the ph_matrix.
   *  \param rhs the scalar factor.
   *  \return the result of the multiplication.
   */
  friend matrix operator*(matrix lhs, T rhs)
  {
    return lhs *= rhs;
  }

  /** Multiplies a ph_matrix by a scalar.
   *
   *  all elements of the ph_matrix are multiplied by the given scalar.
   *
   *  \param lhs the scalar factor.
   *  \param rhs the ph_matrix.
   *  \return the result of the multiplication.
   */
  // Declared here as friend to enable automatic factor type casts.
  friend matrix operator*(T lhs, matrix rhs)
  {
    return rhs *= lhs;
  }

  /** Divides a ph_matrix by a scalar.
   *
   *  all elements of the ph_matrix are divided by the given scalar.
   *
   *  \param lhs the ph_matrix.
   *  \param rhs the scalar divisor.
   *  \return the result of the division.
   */
  // Declared here as friend to enable automatic factor type casts.
  friend matrix operator/(matrix lhs, T rhs)
  {
    return lhs /= rhs;
  }

  /** Checks if two matrices are equal.
   *
   *  \param lhs the left operand.
   *  \param rhs the right operand.
   *  \return the result of the check.
   */
  friend bool operator==(const matrix& lhs, const matrix& rhs)
  {
    return lhs.m_elements == rhs.m_elements;
  }

  /** Checks if two matrices are not equal.
   *
   *  \param lhs the left operand.
   *  \param rhs the right operand.
   *  \return the result of the check.
   */
  friend bool operator!=(const matrix& lhs, const matrix& rhs)
  {
    return lhs.m_elements != rhs.m_elements;
  }

  /** Checks if two matrices are equal with the specified accuracy.
   *
   *  \param lhs the left operand.
   *  \param rhs the right operand.
   *  \param acc the accuracy.
   *  \return the result of the check.
   */
  friend bool close(const matrix<T, rows, cols>& lhs
    , const matrix<T, rows, cols>& rhs
    , T acc = std::numeric_limits<T>::epsilon())
  {
    return close(lhs.m_elements, rhs.m_elements, acc);
  }

private:
  std::array<T, rows * cols> m_elements;
};

/** Sums two matrices.
 *
 *  The sum is element-wise.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the sum of the two matrices.
 */
template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols> operator+(matrix<T, rows, cols> lhs
  , const matrix<T, rows, cols>& rhs);

/** Subtracts two matrices.
 *
 *  The difference is element-wise.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the difference of the two matrices.
 */
template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols> operator-(matrix<T, rows, cols> lhs
  , const matrix<T, rows, cols>& rhs);

/** Multiplies two matrices.
 *
 *  The result is the row-column product between the two matrices.
 *  The number of columns of the left ph_matrix must be equal to the number of
 *  columns of the right ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows of lhs.
 *  \tparam mid the number of columns of lhs and rows of rhs.
 *  \tparam cols the number of columns of rhs.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the row-column product of the two matrices.
 */
template <typename T, size_t rows, size_t mid, size_t cols>
  matrix<T, rows, cols> operator*(const matrix<T, rows, mid>& lhs
  , const matrix<T,mid, cols>& rhs);

/** Computes the determinant of the given ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam T the scalar type.
 *  \param m the input ph_matrix.
 *  \return the determinant of the given ph_matrix.
 */
template <typename T>
  T det(const matrix<T, 1, 1>& m);

/** Computes the determinant of the given ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \param m the input ph_matrix.
 *  \return the determinant of the given ph_matrix.
 */
template <typename T>
  T det(const matrix<T, 2, 2>& m);

/** Computes the determinant of the given ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \param m the input ph_matrix.
 *  \return the determinant of the given ph_matrix.
 */
template <typename T>
  T det(const matrix<T, 3, 3>& m);

/** Computes the trace of the given square ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rc the number of rows and columns of the ph_matrix.
 *  \param m the ph_matrix.
 *  \return the trace of the given ph_matrix.
 */
template <typename T, size_t rc>
  T trace(const matrix<T, rc, rc>& m);

/** Computes the determinant of the given ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rc = the number of rows or columns.
 *  \tparam Enable enabling parameter (can be left to the default value).
 *  \param m the input ph_matrix.
 *  \return the determinant of the given ph_matrix.
 */
template <typename T, size_t rc, typename Enable = std::enable_if_t<(rc > 3)>>
  T det(const matrix<T, rc, rc>& m);

/** Removes a row and a column from a ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \tparam Enable enabling parameter (can be left to the default value).
 *  \param m the ph_matrix to be reduced.
 *  \param row the row to be removed.
 *  \param col the column to be removed.
 *  \return a ph_matrix equal to m but with the the specified row and column
 *    removed.
 */
// No member function because returns a different type.
template <typename T, size_t rows, size_t cols
  , typename Enable = std::enable_if_t<(rows > 1 && cols > 1)>>
  matrix<T, rows - 1, cols - 1> reduce(const matrix<T, rows, cols>& m
    , size_t row, size_t col);

/** Computes the transpose of the given ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \param m the ph_matrix to be transposed.
 *  \return the transpose of the given ph_matrix.
 */
// No member function because returns a different type.
template <typename T, size_t rows, size_t cols>
  matrix<T, cols, rows> transpose(const matrix<T, rows, cols>& m);

/** Computes the adjugate of the given ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \param m the input ph_matrix.
 *  \return the adjugate of the given ph_matrix.
 */
template <typename T>
  matrix<T, 1, 1> adjugate(const matrix<T, 1, 1>& m);

/** Computes the adjugate of the given ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \param m the input ph_matrix.
 *  \return the adjugate of the given ph_matrix.
 */
template <typename T>
  matrix<T, 2, 2> adjugate(const matrix<T, 2, 2>& m);

/** Computes the adjugate of the given ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rc = the number of rows or columns.
 *  \tparam Enable enabling parameter (can be left to the default value).
 *  \param m the input ph_matrix.
 *  \return the adjugate of the given ph_matrix.
 */
template <typename T, size_t rc, typename Enable = std::enable_if_t<(rc > 2)>>
  matrix<T, rc, rc> adjugate(const matrix<T, rc, rc>& m);

/** Computes the inverse of the given ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rc = the number of rows or columns.
 *  \param m the input ph_matrix.
 *  \return the inverse of the given ph_matrix.
 */
template <typename T, size_t rc>
  matrix<T, rc, rc> inverse(matrix<T, rc, rc> m);

/** Computes the square norm of the given ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \param m the input ph_matrix.
 *  \return the square norm.
 */
template <typename T, size_t rows, size_t cols>
  T square_norm(const matrix<T, rows, cols>& m);

/** Computes the norm of the given ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \param m the input ph_matrix.
 *  \return the norm.
 */
template <typename T, size_t rows, size_t cols>
  T norm(const matrix<T, rows, cols>& m);

/** Computes the normalized ph_matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \param m the input ph_matrix.
 *  \return the normalized ph_matrix.
 */
template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols> normalized(matrix<T, rows, cols> m);

/** Computes the cross product ph_matrix associated to the given 3d vector.
 *
 *  \tparam T the scalar type.
 *  \param m a 3d vector.
 *  \return the cross product ph_matrix.
 */
template <typename T>
  matrix<T, 3u, 3u> cross_matrix(const matrix<T, 3u, 1u>& m);

/** Computes the cross product of a 2d vector.
 *
 *  \tparam T the scalar type.
 *  \param v the vector.
 *  \return the cross product of the 2d vector.
 */
template <typename T>
  matrix<T, 2u, 1u> cross(const matrix<T, 2u, 1u>& v);

/** Computes the cross product between two 3d vectors.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the cross product result.
 */
template <typename T>
  matrix<T, 3u, 1u> cross(const matrix<T, 3u, 1u>& lhs
  , const matrix<T, 3u, 1u>& rhs);

/** Computes the outer product between the two given 3d vectors.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the outer product result.
 */
template <typename T>
  matrix<T, 3u, 3u> outer_product(const matrix<T, 3u, 1u>& lhs
  , const matrix<T, 3u, 1u>& rhs);

/** Computes the dot product between the two given vectors.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the size of the vector.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the dot product.
 */
template <typename T, size_t rows>
  T dot(const matrix<T, rows, 1u>& lhs, const matrix<T, rows, 1u>& rhs);

/** Writes the object into a ph_stream.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \param os the ph_stream.
 *  \param m the ph_matrix.
 *  \return a reference to the ph_stream.
 */
template <typename T, size_t rows, size_t cols>
  std::ostream& operator<<(std::ostream& os, const matrix<T, rows, cols>& m);

}



#include "hou/mth/matrix.inl"

#endif

