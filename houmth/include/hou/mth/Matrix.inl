// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

template <typename T, size_t rows, size_t cols>
  constexpr size_t Matrix<T, rows, cols>::getRowsCount()
{
  return rows;
}



template <typename T, size_t rows, size_t cols>
  constexpr size_t Matrix<T, rows, cols>::getColumnsCount()
{
  return cols;
}



template <typename T, size_t rows, size_t cols>
  constexpr size_t Matrix<T, rows, cols>::getSize()
{
  return rows * cols;
}



template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols> Matrix<T, rows, cols>::zero()
{
  return Matrix<T, rows, cols>();
}



template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols> Matrix<T, rows, cols>::filled(T value)
{
  Matrix m;
  m.fill(value);
  return m;
}



#ifndef HOU_DOXYGEN
template <typename T, size_t rows, size_t cols>
template <size_t rc, typename Enable>
  Matrix<T, rows, cols> Matrix<T, rows, cols>::identity()
{
  Matrix m;
  for(size_t i = 0; i < rc; ++i)
  {
    m(i,i) = 1;
  }
  return m;
}
#endif



#ifndef HOU_DOXYGEN
template <typename T, size_t rows, size_t cols>
template <size_t rc, typename Enable>
  Matrix<T, rows, cols> Matrix<T, rows, cols>::diagonal
  (const Matrix<T, rc, 1u>& elements)
{
  Matrix m;
  for(size_t i = 0; i < rc; ++i)
  {
    m(i,i) = elements(i);
  }
  return m;
}
#endif



#ifndef HOU_DOXYGEN
template <typename T, size_t rows, size_t cols>
template <typename... Args, typename Enable>
  Matrix<T, rows, cols> Matrix<T, rows, cols>::diagonal(Args... elements)
{
  return diagonal(Matrix<T, rows, 1u>(elements...));
}
#endif



template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols>::Matrix()
  : mElements()
{
  fill(0);
}



template <typename T, size_t rows, size_t cols>
template <typename U, typename Enable>
  Matrix<T, rows, cols>::Matrix(const Matrix<U, rows, cols>& other)
  : mElements()
{
  std::copy(other.mElements.begin(), other.mElements.end(), mElements.begin());
}



template <typename T, size_t rows, size_t cols>
template <typename... Args, typename Enable>
  Matrix<T, rows, cols>::Matrix(Args... elements)
  : mElements{elements...}
{}



template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols>::Matrix(std::initializer_list<T> elements)
  : mElements()
{
  HOU_EXPECT(elements.size() == getSize());
  std::copy(elements.begin(), elements.end(), mElements.begin());
}



template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols>::~Matrix()
{}



template <typename T, size_t rows, size_t cols>
  T Matrix<T, rows, cols>::operator()(size_t row, size_t col) const
{
  HOU_EXPECT((row < rows) && (col < cols));
  return mElements[row * cols + col];
}



template <typename T, size_t rows, size_t cols>
  T& Matrix<T, rows, cols>::operator()(size_t row, size_t col)
{
  HOU_EXPECT((row < rows) && (col < cols));
  return mElements[row * cols + col];
}



template <typename T, size_t rows, size_t cols>
  T Matrix<T, rows, cols>::operator()(size_t index) const
{
  HOU_EXPECT(index < getSize());
  return mElements[index];
}



template <typename T, size_t rows, size_t cols>
  T& Matrix<T, rows, cols>::operator()(size_t index)
{
  HOU_EXPECT(index < getSize());
  return mElements[index];
}



template <typename T, size_t rows, size_t cols>
template <size_t c, typename Enable>
  T Matrix<T, rows, cols>::x() const
{
  return mElements[0];
}



template <typename T, size_t rows, size_t cols>
template <size_t c, typename Enable>
  T& Matrix<T, rows, cols>::x()
{
  return mElements[0];
}



template <typename T, size_t rows, size_t cols>
template <size_t r, size_t c, typename Enable>
  T Matrix<T, rows, cols>::y() const
{
  return mElements[1];
}



template <typename T, size_t rows, size_t cols>
template <size_t r, size_t c, typename Enable>
  T& Matrix<T, rows, cols>::y()
{
  return mElements[1];
}



template <typename T, size_t rows, size_t cols>
template <size_t r, size_t c, typename Enable>
  T Matrix<T, rows, cols>::z() const
{
  return mElements[2];
}



template <typename T, size_t rows, size_t cols>
template <size_t r, size_t c, typename Enable>
  T& Matrix<T, rows, cols>::z()
{
  return mElements[2];
}



template <typename T, size_t rows, size_t cols>
template <size_t r, size_t c, typename Enable>
  T Matrix<T, rows, cols>::w() const
{
  return mElements[3];
}



template <typename T, size_t rows, size_t cols>
template <size_t r, size_t c, typename Enable>
  T& Matrix<T, rows, cols>::w()
{
  return mElements[3];
}



template <typename T, size_t rows, size_t cols>
  const T* Matrix<T, rows, cols>::data() const
{
  return mElements.data();
}



template <typename T, size_t rows, size_t cols>
template <typename... Args, typename Enable>
  void Matrix<T, rows, cols>::set(Args... elements)
{
  *this = Matrix(elements...);
}



template <typename T, size_t rows, size_t cols>
  void Matrix<T, rows, cols>::fill(T value)
{
  mElements.fill(value);
}



template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator+=
  (const Matrix<T, rows, cols>& rhs)
{
  for(size_t i = 0; i < getSize(); ++i)
  {
    mElements[i] += rhs.mElements[i];
  }
  return *this;
}



template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols> operator+(Matrix<T, rows, cols> lhs
  , const Matrix<T, rows, cols>& rhs)
{
  return lhs += rhs;
}



template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator-=
  (const Matrix<T, rows, cols>& rhs)
{
  for(size_t i = 0; i < getSize(); ++i)
  {
    mElements[i] -= rhs.mElements[i];
  }
  return *this;
}



template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols> operator-(Matrix<T, rows, cols> lhs
  , const Matrix<T, rows, cols>& rhs)
{
  return lhs -= rhs;
}



template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator*=(T rhs)
{
  for(size_t i = 0; i < getSize(); ++i)
  {
    mElements[i] *= rhs;
  }
  return *this;
}



template <typename T, size_t rows, size_t mid, size_t cols>
  Matrix<T, rows, cols> operator*(const Matrix<T, rows, mid>& lhs
  , const Matrix<T,mid, cols>& rhs)
{
  Matrix<T, rows, cols> retval;
  for(size_t r = 0; r < rows; ++r)
  {
    for(size_t c = 0; c < cols; ++c)
    {
      retval(r, c) = 0.f;
      for(size_t i = 0; i < mid; ++i)
      {
        retval(r, c) += lhs(r, i) * rhs(i, c);
      }
    }
  }
  return retval;
}



template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator/=(T rhs)
{
  for(size_t i = 0; i < getSize(); ++i)
  {
    mElements[i] /= rhs;
  }
  return *this;
}



template <typename T>
  T det(const Matrix<T, 1, 1>& m)
{
  return m(0);
}



template <typename T>
  T det(const Matrix<T, 2, 2>& m)
{
  return m(0,0) * m(1,1) - m(0,1) * m(1,0);
}



template <typename T>
  T det(const Matrix<T, 3, 3>& m)
{
  return m(0,0) * m(1,1) * m(2,2)
    + m(0,1) * m(1,2) * m(2,0)
    + m(0,2) * m(1,0) * m(2,1)
    - m(0,2) * m(1,1) * m(2,0)
    - m(0,1) * m(1,0) * m(2,2)
    - m(0,0) * m(1,2) * m(2,1);
}



template <typename T, size_t rc, typename Enable>
  T det(const Matrix<T, rc, rc>& m)
{
  T result(0);
  for(size_t col = 0; col < rc; ++col)
  {
    T factor = (col % 2) == 0 ? T(1) : T(-1);
    result += factor * m(0, col) * det(reduce(m, 0, col));
  }
  return result;
}



template <typename T, size_t rc>
  T trace(const Matrix<T, rc, rc>& m)
{
  T result(0);
  for(size_t i = 0; i < rc; ++i)
  {
    result += m(i, i);
  }
  return result;
}



template <typename T, size_t rows, size_t cols, typename Enable>
  Matrix<T, rows - 1, cols - 1> reduce(const Matrix<T, rows, cols>& m
    , size_t row, size_t col)
{
  HOU_EXPECT((row < rows) && (col < cols));
  Matrix<T, rows - 1, cols - 1> retval;
  size_t rin = 0;
  for(size_t r = 0; r < rows - 1; ++r)
  {
    if(rin == row)
    {
      ++rin;
    }
    size_t cin = 0;
    for(size_t c = 0; c < cols - 1; ++c)
    {
      if(cin == col)
      {
        ++cin;
      }
      retval(r, c) = m(rin, cin);
      ++cin;
    }
    ++rin;
  }
  return retval;
}



#ifndef HOU_DOXYGEN
template <typename T, size_t rows, size_t cols>
  Matrix<T, cols, rows> transpose(const Matrix<T, rows, cols>& m)
{
  Matrix<T, cols, rows> retval;
  for(size_t r = 0; r < rows; ++r)
  {
    for(size_t c = 0; c < cols; ++c)
    {
      retval(c,r) = m(r,c);
    }
  }
  return retval;
}
#endif



#ifndef HOU_DOXYGEN
template <typename T, size_t rows, size_t cols>
template <size_t rc, typename Enable>
  Matrix<T, rows, cols>& Matrix<T, rows, cols>::adjugate()
{
  *this = ::hou::adjugate(*this);
  return *this;
}
#endif



template <typename T>
  Matrix<T, 1, 1> adjugate(const Matrix<T, 1, 1>&)
{
  return Matrix<T, 1, 1>::identity();
}



template <typename T>
  Matrix<T, 2, 2> adjugate(const Matrix<T, 2, 2>& m)
{
  return Matrix<T, 2, 2>{m(3), -m(1), -m(2), m(0)};
}



template <typename T, size_t rc, typename Enable>
  Matrix<T, rc, rc> adjugate(const Matrix<T, rc, rc>& m)
{
  Matrix<T, rc, rc> adj;
  for(size_t r = 0; r < rc; ++r)
  {
    for(size_t c = 0; c < rc; ++c)
    {
      T factor = ((r + c) % 2) == 0 ? T(1) : T(-1);
      adj(r, c) = factor * det(reduce(m, c, r));
    }
  }
  return adj;
}



#ifndef HOU_DOXYGEN
template <typename T, size_t rows, size_t cols>
template <size_t rc, typename Enable>
  Matrix<T, rows, cols>& Matrix<T, rows, cols>::invert()
{
  T determinant = det(*this);
  HOU_EXPECT(!close(determinant, T(0)));
  return this->adjugate() /= determinant;
}
#endif



template <typename T, size_t rc>
  Matrix<T, rc, rc> inverse(Matrix<T, rc, rc> m)
{
  return m.invert();
}



template <typename T, size_t rows, size_t cols>
  T squareNorm(const Matrix<T, rows, cols>& m)
{
  T sn(0);
  for(size_t i = 0; i < rows * cols; ++i)
  {
    sn += m(i) * m(i);
  }
  return sn;
}



template <typename T, size_t rows, size_t cols>
  T norm(const Matrix<T, rows, cols>& m)
{
  return std::sqrt(squareNorm(m));
}



template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols>& Matrix<T, rows, cols>::normalize()
{
  T matNorm = norm(*this);
  HOU_EXPECT(!close(matNorm, T(0)));
  return *this /= matNorm;
}



template <typename T, size_t rows, size_t cols>
  Matrix<T, rows, cols> normalized(Matrix<T, rows, cols> m)
{
  return m.normalize();
}



template <typename T>
  Matrix<T, 3u, 3u> crossMatrix(const Matrix<T, 3u, 1u>& m)
{
  return Matrix<T, 3u, 3u>
  {
     T(0),   -m.z(),  m.y(),
     m.z(),  T(0),   -m.x(),
    -m.y(),  m.x(),  T(0)
  };
}



template <typename T>
  Matrix<T, 2u, 1u> cross(const Matrix<T, 2u, 1u>& v)
{
  return Matrix<T, 2u, 1u>{v(1), -v(0)};
}



template <typename T>
  Matrix<T, 3u, 1u> cross(const Matrix<T, 3u, 1u>& lhs
  , const Matrix<T, 3u, 1u>& rhs)
{
  return Matrix<T, 3u, 1u>
  {
    lhs(1) * rhs(2) - lhs(2) * rhs(1),
    lhs(2) * rhs(0) - lhs(0) * rhs(2),
    lhs(0) * rhs(1) - lhs(1) * rhs(0),
  };
}



template <typename T>
  Matrix<T, 3u, 3u> outerProduct(const Matrix<T, 3u, 1u>& lhs
  , const Matrix<T, 3u, 1u>& rhs)
{
  return Matrix<T, 3u, 3u>
  {
    lhs.x() * rhs.x(), lhs.x() * rhs.y(), lhs.x() * rhs.z(),
    lhs.y() * rhs.x(), lhs.y() * rhs.y(), lhs.y() * rhs.z(),
    lhs.z() * rhs.x(), lhs.z() * rhs.y(), lhs.z() * rhs.z(),
  };
}



template <typename T, size_t rows>
  T dot(const Matrix<T, rows, 1u>& lhs, const Matrix<T, rows, 1u>& rhs)
{
  T result(0);
  for(size_t i = 0; i < rows; ++i)
  {
    result += lhs(i) * rhs(i);
  }
  return result;
}



template <typename T, size_t rows, size_t cols>
  std::ostream& operator<<(std::ostream& os, const Matrix<T, rows, cols>& m)
{
  for(size_t r = 0; r < rows; ++r)
  {
    if(r != 0)
    {
      os << "\n";
    }
    os << "(";
    for(size_t c = 0; c < cols; ++c)
    {
      if(c != 0)
      {
        os << ", ";
      }
      os << m(r, c);
    }
    os << ")";
  }
  return os;
}

}

