// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_MTH_MATRIX_HPP
#define HOU_MTH_MATRIX_HPP

#include "hou/mth/MthExport.hpp"

#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/Error.hpp"
#include "hou/cor/StdArray.hpp"
#include "hou/cor/TemplateUtils.hpp"

#include "hou/mth/MatrixFwd.hpp"

#include <cmath>
#include <initializer_list>
#include <iostream>
#include <limits>



namespace hou
{

/** Represents a matrix.
 *
 *  The size of the matrix is static and the object is allocated on the stack.
 *  The elements of a row are contiguous in memory and columns are contiguous
 *  in memory.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 */
template <typename T, size_t rows, size_t cols>
  class Matrix
{
  static_assert(rows > 0 && cols > 0, "Matrix size must be at least 1x1.");

public:
  template <typename otherT, size_t otherRows, size_t otherCols>
    friend class Matrix;

public:
  /** Get the number of rows of the matrix.
   *
   *  \return the number of rows of the matrix.
   */
  inline static constexpr size_t getRowsCount();

  /** Get the number of columns of the matrix.
   *
   *  \return the number of columns of the matrix.
   */
  inline static constexpr size_t getColumnsCount();

  /** Get the number of elements of the matrix.
   *
   *  The number of elements is equal to the number of rows times the number of
   *  columns.
   *
   *  \return the number of elements of the matrix.
   */
  inline static constexpr size_t getSize();

  /** Returns the zero matrix.
   *
   *  \return the zero matrix.
   */
  static Matrix zero();

  /** Returns a matrix with all elements set to a given value.
   *
   *  \param value the value of the elements of the matrix.
   *  \return a matrix with all element set to value.
   */
  static Matrix filled(T value);

  /** Returns the identity matrix.
   *
   *  \tparam rc the number of rows or columns.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return the identity matrix.
   */
  template <size_t rc = rows
    , typename Enable = std::enable_if_t<rows == rc && cols == rc>>
    static Matrix identity();

  /** Returns a diagonal matrix with the given diagonal elements.
   *
   *  \tparam rc the number of rows or columns.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \param elements a vector containing the elements on the diagonal.
   *  \return a diagonal matrix with the given diagonal elements.
   */
  template <size_t rc = rows
    , typename Enable = std::enable_if_t<rows == rc && cols == rc>>
    static Matrix diagonal(const Matrix<T, rc, 1u>& elements);

  /** Returns a diagonal matrix with the given diagonal elements.
   *
   *  \tparam rc the number of rows or columns.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \param elements the list of diagonal elements.
   *  \return a diagonal matrix with the given diagonal elements.
   */
  template <typename... Args
    , typename Enable = std::enable_if_t
    <rows == cols && sizeof...(Args) == rows>>
    static Matrix diagonal(Args... elements);

public:
  /** Creates a matrix with all elements initialized to 0.
   */
  Matrix();

  /** Creates a matrix from a matrix with same size but different scalar type.
   *
   *  U must be convertible to T.
   *
   *  \tparam U the scalar type of the other matrix.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \param other the matrix to be copied.
   */
  template <typename U
    , typename Enable = std::enable_if_t<std::is_convertible<U, T>::value>>
    Matrix(const Matrix<U, rows, cols>& other);

  /** Creates a matrix from the given elements.
   *
   *  Consider that the elements of a row are contiguous in memory. For example,
   *  for a 2x3 matrix, the following sequence of elements:
   *
   *      (1, 2, 3, 4, 5, 6)
   *
   *  would result in the following matrix:
   *
   *      (1, 2, 3)
   *      (4, 5, 6)
   *
   *  \tparam Args variable list of elements.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \param elements the matrix elements.
   */
  template <typename... Args
    , typename Enable = std::enable_if_t
    < sizeof...(Args) == rows * cols
    && conjunction<std::is_convertible<Args, T>::value...>::value>>
    Matrix(Args... elements);

  /** Creates a matrix from the elements given in the initializer list.
   *
   *  Consider that the elements of a row are contiguous in memory. For example,
   *  for a 2x3 matrix, the following initializer list:
   *
   *      {1, 2, 3, 4, 5, 6}
   *
   *  would result in the following matrix:
   *
   *      (1, 2, 3)
   *      (4, 5, 6)
   *
   *  Throws if the size of the initializer list is different from the size of
   *  the matrix.
   *
   *  \param elements an initializer list containing the elements of the matrix.
   */
  Matrix(std::initializer_list<T> elements);

  /** Destructor.
   */
  virtual ~Matrix();

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
   *  matrix, index 3 would correspond to the element at coordinates (1,0).
   *
   *  \param index the index of the element.
   *  \return a copy of the element.
   */
  T operator()(size_t index) const;

  /** Retrieves a reference to the element at the given index.
   *
   *  Consider that elements in a row are contiguous. For example, for a 2x3
   *  matrix, index 3 would correspond to the element at coordinates (1,0).
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

  /** Retrieves a pointer to an array containing the matrix elements.
   *
   *  The data is to be interpreted as a single array with size equal to the
   *  number of elements of the matrix. Consider that elements in a row are
   *  contiguous. For example, for a 2x3 matrix, the third element of the
   *  array would correspond to the element at coordinates (1,0).
   *
   *  \return a constant raw pointer to the matrix data.
   */
  const T* data() const;

  /** Sets the elements of the matrix to the given values.
   *
   *  \tparam Args the list of elements.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \param elements the matrix elements.
   */
  template <typename... Args
    , typename Enable = std::enable_if_t
    < sizeof...(Args) == rows * cols
    && conjunction<std::is_convertible<Args, T>::value...>::value>>
    void set(Args... elements);

  /** Sets all elements of the matrix to the specified value.
   *
   *  \param value the value to which th elements of the matrix have to be set.
   */
  void fill(T value);

  /** Adds the given matrix to this matrix.
   *
   *  The sum is element-wise.
   *
   *  \param rhs the matrix to be added.
   *  \return a reference to this matrix after the addition.
   */
  Matrix& operator+=(const Matrix& rhs);

  /** Subtracts the given matrix from this matrix.
   *
   *  The difference is element-wise.
   *
   *  \param rhs the matrix to be subtracted.
   *  \return a reference to this matrix after the subtraction.
   */
  Matrix& operator-=(const Matrix& rhs);

  /** Multiplies this matrix by the given scalar.
   *
   *  All elements of the matrix are multiplied by the given scalar.
   *
   *  \param rhs the scalar factor.
   *  \return a reference to this matrix after the multiplication.
   */
  Matrix& operator*=(T rhs);

  /** Divides this matrix by the given scalar.
   *
   *  All elements of the matrix are divided by the given scalar.
   *
   *  \param rhs the scalar divisor.
   *  \return a reference to this matrix after the division.
   */
  Matrix& operator/=(T rhs);

  /** Adjugates this matrix.
   *
   *  \tparam rc the number of rows or columns.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return a reference to this matrix after the operation.
   */
  template <size_t rc = rows
    , typename Enable = std::enable_if_t<rows == rc && cols == rc>>
    Matrix& adjugate();

  /** Inverts this matrix.
   *
   *  \tparam rc the number of rows or columns.
   *  \tparam Enable enabling parameter (can be left to the default value).
   *  \return a reference to this matrix after the inversion.
   */
  template <size_t rc = rows
    , typename Enable = std::enable_if_t<rows == rc && cols == rc>>
    Matrix& invert();

  /** Normalizes the matrix.
   *
   *  \return a reference to this matrix after normalization.
   */
  Matrix& normalize();

  /** Computes the opposite of a matrix.
   *
   *  All elements of the resulting matrix are the opposite of the corresponding
   *  original elements.
   *
   *  \param m the matrix.
   *  \return the opposite matrix.
   */
  friend Matrix operator-(Matrix m)
  {
    for(size_t i = 0; i < m.getSize(); ++i)
    {
      m.mElements[i] = -m.mElements[i];
    }
    return m;
  }

  /** Multiplies a matrix by a scalar.
   *
   *  All elements of the matrix are multiplied by the given scalar.
   *
   *  \param lhs the matrix.
   *  \param rhs the scalar factor.
   *  \return the result of the multiplication.
   */
  friend Matrix operator*(Matrix lhs, T rhs)
  {
    return lhs *= rhs;
  }

  /** Multiplies a matrix by a scalar.
   *
   *  All elements of the matrix are multiplied by the given scalar.
   *
   *  \param lhs the scalar factor.
   *  \param rhs the matrix.
   *  \return the result of the multiplication.
   */
  // Declared here as friend to enable automatic factor type casts.
  friend Matrix operator*(T lhs, Matrix rhs)
  {
    return rhs *= lhs;
  }

  /** Divides a matrix by a scalar.
   *
   *  All elements of the matrix are divided by the given scalar.
   *
   *  \param lhs the matrix.
   *  \param rhs the scalar divisor.
   *  \return the result of the division.
   */
  // Declared here as friend to enable automatic factor type casts.
  friend Matrix operator/(Matrix lhs, T rhs)
  {
    return lhs /= rhs;
  }

  /** Checks if two matrices are equal.
   *
   *  \param lhs the left operand.
   *  \param rhs the right operand.
   *  \return the result of the check.
   */
  friend bool operator==(const Matrix& lhs, const Matrix& rhs)
  {
    return lhs.mElements == rhs.mElements;
  }

  /** Checks if two matrices are not equal.
   *
   *  \param lhs the left operand.
   *  \param rhs the right operand.
   *  \return the result of the check.
   */
  friend bool operator!=(const Matrix& lhs, const Matrix& rhs)
  {
    return lhs.mElements != rhs.mElements;
  }

  /** Checks if two matrices are equal with the specified accuracy.
   *
   *  \param lhs the left operand.
   *  \param rhs the right operand.
   *  \param acc the accuracy.
   *  \return the result of the check.
   */
  friend bool close(const Matrix<T, rows, cols>& lhs
    , const Matrix<T, rows, cols>& rhs
    , T acc = std::numeric_limits<T>::epsilon())
  {
    return close(lhs.mElements, rhs.mElements, acc);
  }

private:
  std::array<T, rows * cols> mElements;
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
  Matrix<T, rows, cols> operator+(Matrix<T, rows, cols> lhs
  , const Matrix<T, rows, cols>& rhs);

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
  Matrix<T, rows, cols> operator-(Matrix<T, rows, cols> lhs
  , const Matrix<T, rows, cols>& rhs);

/** Multiplies two matrices.
 *
 *  The result is the row-column product between the two matrices.
 *  The number of columns of the left matrix must be equal to the number of
 *  columns of the right matrix.
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
  Matrix<T, rows, cols> operator*(const Matrix<T, rows, mid>& lhs
  , const Matrix<T,mid, cols>& rhs);

/** Computes the determinant of the given matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam T the scalar type.
 *  \param m the input matrix.
 *  \return the determinant of the given matrix.
 */
template <typename T>
  T det(const Matrix<T, 1, 1>& m);

/** Computes the determinant of the given matrix.
 *
 *  \tparam T the scalar type.
 *  \param m the input matrix.
 *  \return the determinant of the given matrix.
 */
template <typename T>
  T det(const Matrix<T, 2, 2>& m);

/** Computes the determinant of the given matrix.
 *
 *  \tparam T the scalar type.
 *  \param m the input matrix.
 *  \return the determinant of the given matrix.
 */
template <typename T>
  T det(const Matrix<T, 3, 3>& m);

/** Computes the trace of the given square matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rc the number of rows and columns of the matrix.
 *  \param m the matrix.
 *  \return the trace of the given matrix.
 */
template <typename T, size_t rc>
  T trace(const Matrix<T, rc, rc>& m);

/** Computes the determinant of the given matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rc = the number of rows or columns.
 *  \tparam Enable enabling parameter (can be left to the default value).
 *  \param m the input matrix.
 *  \return the determinant of the given matrix.
 */
template <typename T, size_t rc, typename Enable = std::enable_if_t<(rc > 3)>>
  T det(const Matrix<T, rc, rc>& m);

/** Removes a row and a column from a matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \tparam Enable enabling parameter (can be left to the default value).
 *  \param m the matrix to be reduced.
 *  \param row the row to be removed.
 *  \param col the column to be removed.
 *  \return a matrix equal to m but with the the specified row and column
 *    removed.
 */
// No member function because returns a different type.
template <typename T, size_t rows, size_t cols
  , typename Enable = std::enable_if_t<(rows > 1 && cols > 1)>>
  Matrix<T, rows - 1, cols - 1> reduce(const Matrix<T, rows, cols>& m
    , size_t row, size_t col);

/** Computes the transpose of the given matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \param m the matrix to be transposed.
 *  \return the transpose of the given matrix.
 */
// No member function because returns a different type.
template <typename T, size_t rows, size_t cols>
  Matrix<T, cols, rows> transpose(const Matrix<T, rows, cols>& m);

/** Computes the adjugate of the given matrix.
 *
 *  \tparam T the scalar type.
 *  \param m the input matrix.
 *  \return the adjugate of the given matrix.
 */
template <typename T>
  Matrix<T, 1, 1> adjugate(const Matrix<T, 1, 1>& m);

/** Computes the adjugate of the given matrix.
 *
 *  \tparam T the scalar type.
 *  \param m the input matrix.
 *  \return the adjugate of the given matrix.
 */
template <typename T>
  Matrix<T, 2, 2> adjugate(const Matrix<T, 2, 2>& m);

/** Computes the adjugate of the given matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rc = the number of rows or columns.
 *  \tparam Enable enabling parameter (can be left to the default value).
 *  \param m the input matrix.
 *  \return the adjugate of the given matrix.
 */
template <typename T, size_t rc, typename Enable = std::enable_if_t<(rc > 2)>>
  Matrix<T, rc, rc> adjugate(const Matrix<T, rc, rc>& m);

/** Computes the inverse of the given matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rc = the number of rows or columns.
 *  \param m the input matrix.
 *  \return the inverse of the given matrix.
 */
template <typename T, size_t rc>
  Matrix<T, rc, rc> inverse(Matrix<T, rc, rc> m);

/** Computes the square norm of the given matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \param m the input matrix.
 *  \return the square norm.
 */
template <typename T, size_t rows, size_t cols>
  T squareNorm(const Matrix<T, rows, cols>& m);

/** Computes the norm of the given matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \param m the input matrix.
 *  \return the norm.
 */
template <typename T, size_t rows, size_t cols>
  T norm(const Matrix<T, rows, cols>& m);

/** Computes the normalized matrix.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \param m the input matrix.
 *  \return the normalized matrix.
 */
template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols> normalized(Matrix<T, rows, cols> m);

/** Computes the cross product matrix associated to the given 3d vector.
 *
 *  \tparam T the scalar type.
 *  \param m a 3d vector.
 *  \return the cross product matrix.
 */
template <typename T>
  Matrix<T, 3u, 3u> crossMatrix(const Matrix<T, 3u, 1u>& m);

/** Computes the cross product of a 2d vector.
 *
 *  \tparam T the scalar type.
 *  \param v the vector.
 *  \return the cross product of the 2d vector.
 */
template <typename T>
  Matrix<T, 2u, 1u> cross(const Matrix<T, 2u, 1u>& v);

/** Computes the cross product between two 3d vectors.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the cross product result.
 */
template <typename T>
  Matrix<T, 3u, 1u> cross(const Matrix<T, 3u, 1u>& lhs
  , const Matrix<T, 3u, 1u>& rhs);

/** Computes the outer product between the two given 3d vectors.
 *
 *  \tparam T the scalar type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the outer product result.
 */
template <typename T>
  Matrix<T, 3u, 3u> outerProduct(const Matrix<T, 3u, 1u>& lhs
  , const Matrix<T, 3u, 1u>& rhs);

/** Computes the dot product between the two given vectors.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the size of the vector.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the dot product.
 */
template <typename T, size_t rows>
  T dot(const Matrix<T, rows, 1u>& lhs, const Matrix<T, rows, 1u>& rhs);

/** Writes the object into a stream.
 *
 *  \tparam T the scalar type.
 *  \tparam rows the number of rows.
 *  \tparam cols the number of columns.
 *  \param os the stream.
 *  \param m the matrix.
 *  \return a reference to the stream.
 */
template <typename T, size_t rows, size_t cols>
  std::ostream& operator<<(std::ostream& os, const Matrix<T, rows, cols>& m);

}



#include "hou/mth/Matrix.inl"

#endif
