// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T, size_t rows, size_t cols>
  constexpr size_t matrix<T, rows, cols>::get_row_count()
{
  return rows;
}



template <typename T, size_t rows, size_t cols>
  constexpr size_t matrix<T, rows, cols>::get_column_count()
{
  return cols;
}



template <typename T, size_t rows, size_t cols>
  constexpr size_t matrix<T, rows, cols>::get_size()
{
  return rows * cols;
}



template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols> matrix<T, rows, cols>::zero()
{
  return matrix<T, rows, cols>();
}



template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols> matrix<T, rows, cols>::filled(T value)
{
  matrix m;
  m.fill(value);
  return m;
}



#ifndef HOU_DOXYGEN
template <typename T, size_t rows, size_t cols>
template <size_t rc, typename Enable>
  matrix<T, rows, cols> matrix<T, rows, cols>::identity()
{
  matrix m;
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
  matrix<T, rows, cols> matrix<T, rows, cols>::diagonal
  (const matrix<T, rc, 1u>& elements)
{
  matrix m;
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
  matrix<T, rows, cols> matrix<T, rows, cols>::diagonal(Args... elements)
{
  return diagonal(matrix<T, rows, 1u>(elements...));
}
#endif



template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols>::matrix()
  : m_elements()
{
  fill(0);
}



template <typename T, size_t rows, size_t cols>
template <typename U, typename Enable>
  matrix<T, rows, cols>::matrix(const matrix<U, rows, cols>& other)
  : m_elements()
{
  std::copy(other.m_elements.begin(), other.m_elements.end(), m_elements.begin());
}



template <typename T, size_t rows, size_t cols>
template <typename... Args, typename Enable>
  matrix<T, rows, cols>::matrix(Args... elements)
  : m_elements{elements...}
{}



template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols>::matrix(std::initializer_list<T> elements)
  : m_elements()
{
  HOU_EXPECT(elements.size() == get_size());
  std::copy(elements.begin(), elements.end(), m_elements.begin());
}



template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols>::~matrix()
{}



template <typename T, size_t rows, size_t cols>
  T matrix<T, rows, cols>::operator()(size_t row, size_t col) const
{
  HOU_EXPECT((row < rows) && (col < cols));
  return m_elements[row * cols + col];
}



template <typename T, size_t rows, size_t cols>
  T& matrix<T, rows, cols>::operator()(size_t row, size_t col)
{
  HOU_EXPECT((row < rows) && (col < cols));
  return m_elements[row * cols + col];
}



template <typename T, size_t rows, size_t cols>
  T matrix<T, rows, cols>::operator()(size_t index) const
{
  HOU_EXPECT(index < get_size());
  return m_elements[index];
}



template <typename T, size_t rows, size_t cols>
  T& matrix<T, rows, cols>::operator()(size_t index)
{
  HOU_EXPECT(index < get_size());
  return m_elements[index];
}



template <typename T, size_t rows, size_t cols>
template <size_t c, typename Enable>
  T matrix<T, rows, cols>::x() const
{
  return m_elements[0];
}



template <typename T, size_t rows, size_t cols>
template <size_t c, typename Enable>
  T& matrix<T, rows, cols>::x()
{
  return m_elements[0];
}



template <typename T, size_t rows, size_t cols>
template <size_t r, size_t c, typename Enable>
  T matrix<T, rows, cols>::y() const
{
  return m_elements[1];
}



template <typename T, size_t rows, size_t cols>
template <size_t r, size_t c, typename Enable>
  T& matrix<T, rows, cols>::y()
{
  return m_elements[1];
}



template <typename T, size_t rows, size_t cols>
template <size_t r, size_t c, typename Enable>
  T matrix<T, rows, cols>::z() const
{
  return m_elements[2];
}



template <typename T, size_t rows, size_t cols>
template <size_t r, size_t c, typename Enable>
  T& matrix<T, rows, cols>::z()
{
  return m_elements[2];
}



template <typename T, size_t rows, size_t cols>
template <size_t r, size_t c, typename Enable>
  T matrix<T, rows, cols>::w() const
{
  return m_elements[3];
}



template <typename T, size_t rows, size_t cols>
template <size_t r, size_t c, typename Enable>
  T& matrix<T, rows, cols>::w()
{
  return m_elements[3];
}



template <typename T, size_t rows, size_t cols>
  const T* matrix<T, rows, cols>::data() const
{
  return m_elements.data();
}



template <typename T, size_t rows, size_t cols>
template <typename... Args, typename Enable>
  void matrix<T, rows, cols>::set(Args... elements)
{
  *this = matrix(elements...);
}



template <typename T, size_t rows, size_t cols>
  void matrix<T, rows, cols>::fill(T value)
{
  m_elements.fill(value);
}



template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols>& matrix<T, rows, cols>::operator+=
  (const matrix<T, rows, cols>& rhs)
{
  for(size_t i = 0; i < get_size(); ++i)
  {
    m_elements[i] += rhs.m_elements[i];
  }
  return *this;
}



template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols> operator+(matrix<T, rows, cols> lhs
  , const matrix<T, rows, cols>& rhs)
{
  return lhs += rhs;
}



template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols>& matrix<T, rows, cols>::operator-=
  (const matrix<T, rows, cols>& rhs)
{
  for(size_t i = 0; i < get_size(); ++i)
  {
    m_elements[i] -= rhs.m_elements[i];
  }
  return *this;
}



template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols> operator-(matrix<T, rows, cols> lhs
  , const matrix<T, rows, cols>& rhs)
{
  return lhs -= rhs;
}



template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols>& matrix<T, rows, cols>::operator*=(T rhs)
{
  for(size_t i = 0; i < get_size(); ++i)
  {
    m_elements[i] *= rhs;
  }
  return *this;
}



template <typename T, size_t rows, size_t mid, size_t cols>
  matrix<T, rows, cols> operator*(const matrix<T, rows, mid>& lhs
  , const matrix<T,mid, cols>& rhs)
{
  matrix<T, rows, cols> retval;
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
  matrix<T, rows, cols>& matrix<T, rows, cols>::operator/=(T rhs)
{
  for(size_t i = 0; i < get_size(); ++i)
  {
    m_elements[i] /= rhs;
  }
  return *this;
}



template <typename T>
  T det(const matrix<T, 1, 1>& m)
{
  return m(0);
}



template <typename T>
  T det(const matrix<T, 2, 2>& m)
{
  return m(0,0) * m(1,1) - m(0,1) * m(1,0);
}



template <typename T>
  T det(const matrix<T, 3, 3>& m)
{
  return m(0,0) * m(1,1) * m(2,2)
    + m(0,1) * m(1,2) * m(2,0)
    + m(0,2) * m(1,0) * m(2,1)
    - m(0,2) * m(1,1) * m(2,0)
    - m(0,1) * m(1,0) * m(2,2)
    - m(0,0) * m(1,2) * m(2,1);
}



template <typename T, size_t rc, typename Enable>
  T det(const matrix<T, rc, rc>& m)
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
  T trace(const matrix<T, rc, rc>& m)
{
  T result(0);
  for(size_t i = 0; i < rc; ++i)
  {
    result += m(i, i);
  }
  return result;
}



template <typename T, size_t rows, size_t cols, typename Enable>
  matrix<T, rows - 1, cols - 1> reduce(const matrix<T, rows, cols>& m
    , size_t row, size_t col)
{
  HOU_EXPECT((row < rows) && (col < cols));
  matrix<T, rows - 1, cols - 1> retval;
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
  matrix<T, cols, rows> transpose(const matrix<T, rows, cols>& m)
{
  matrix<T, cols, rows> retval;
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
  matrix<T, rows, cols>& matrix<T, rows, cols>::adjugate()
{
  *this = ::hou::adjugate(*this);
  return *this;
}
#endif



template <typename T>
  matrix<T, 1, 1> adjugate(const matrix<T, 1, 1>&)
{
  return matrix<T, 1, 1>::identity();
}



template <typename T>
  matrix<T, 2, 2> adjugate(const matrix<T, 2, 2>& m)
{
  return matrix<T, 2, 2>{m(3), -m(1), -m(2), m(0)};
}



template <typename T, size_t rc, typename Enable>
  matrix<T, rc, rc> adjugate(const matrix<T, rc, rc>& m)
{
  matrix<T, rc, rc> adj;
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
  matrix<T, rows, cols>& matrix<T, rows, cols>::invert()
{
  T determinant = det(*this);
  HOU_EXPECT(!close(determinant, T(0)));
  return this->adjugate() /= determinant;
}
#endif



template <typename T, size_t rc>
  matrix<T, rc, rc> inverse(matrix<T, rc, rc> m)
{
  return m.invert();
}



template <typename T, size_t rows, size_t cols>
  T square_norm(const matrix<T, rows, cols>& m)
{
  T sn(0);
  for(size_t i = 0; i < rows * cols; ++i)
  {
    sn += m(i) * m(i);
  }
  return sn;
}



template <typename T, size_t rows, size_t cols>
  T norm(const matrix<T, rows, cols>& m)
{
  return std::sqrt(square_norm(m));
}



template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols>& matrix<T, rows, cols>::normalize()
{
  T matNorm = norm(*this);
  HOU_EXPECT(!close(matNorm, T(0)));
  return *this /= matNorm;
}



template <typename T, size_t rows, size_t cols>
  matrix<T, rows, cols> normalized(matrix<T, rows, cols> m)
{
  return m.normalize();
}



template <typename T>
  matrix<T, 3u, 3u> cross_matrix(const matrix<T, 3u, 1u>& m)
{
  return matrix<T, 3u, 3u>
  {
     T(0),   -m.z(),  m.y(),
     m.z(),  T(0),   -m.x(),
    -m.y(),  m.x(),  T(0)
  };
}



template <typename T>
  matrix<T, 2u, 1u> cross(const matrix<T, 2u, 1u>& v)
{
  return matrix<T, 2u, 1u>{v(1), -v(0)};
}



template <typename T>
  matrix<T, 3u, 1u> cross(const matrix<T, 3u, 1u>& lhs
  , const matrix<T, 3u, 1u>& rhs)
{
  return matrix<T, 3u, 1u>
  {
    lhs(1) * rhs(2) - lhs(2) * rhs(1),
    lhs(2) * rhs(0) - lhs(0) * rhs(2),
    lhs(0) * rhs(1) - lhs(1) * rhs(0),
  };
}



template <typename T>
  matrix<T, 3u, 3u> outer_product(const matrix<T, 3u, 1u>& lhs
  , const matrix<T, 3u, 1u>& rhs)
{
  return matrix<T, 3u, 3u>
  {
    lhs.x() * rhs.x(), lhs.x() * rhs.y(), lhs.x() * rhs.z(),
    lhs.y() * rhs.x(), lhs.y() * rhs.y(), lhs.y() * rhs.z(),
    lhs.z() * rhs.x(), lhs.z() * rhs.y(), lhs.z() * rhs.z(),
  };
}



template <typename T, size_t rows>
  T dot(const matrix<T, rows, 1u>& lhs, const matrix<T, rows, 1u>& rhs)
{
  T result(0);
  for(size_t i = 0; i < rows; ++i)
  {
    result += lhs(i) * rhs(i);
  }
  return result;
}



template <typename T, size_t rows, size_t cols>
  std::ostream& operator<<(std::ostream& os, const matrix<T, rows, cols>& m)
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

