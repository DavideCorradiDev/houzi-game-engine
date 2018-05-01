// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T, size_t Rows, size_t Cols>
constexpr size_t matrix<T, Rows, Cols>::get_row_count()
{
  return Rows;
}



template <typename T, size_t Rows, size_t Cols>
constexpr size_t matrix<T, Rows, Cols>::get_column_count()
{
  return Cols;
}



template <typename T, size_t Rows, size_t Cols>
constexpr size_t matrix<T, Rows, Cols>::get_size()
{
  return Rows * Cols;
}



template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols> matrix<T, Rows, Cols>::zero()
{
  return matrix<T, Rows, Cols>();
}



template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols> matrix<T, Rows, Cols>::filled(T value)
{
  matrix m;
  m.fill(value);
  return m;
}



#ifndef HOU_DOXYGEN
template <typename T, size_t Rows, size_t Cols>
template <size_t RC, typename Enable>
matrix<T, Rows, Cols> matrix<T, Rows, Cols>::identity()
{
  matrix m;
  for(size_t i = 0; i < RC; ++i)
  {
    m(i, i) = 1;
  }
  return m;
}
#endif



#ifndef HOU_DOXYGEN
template <typename T, size_t Rows, size_t Cols>
template <size_t RC, typename Enable>
matrix<T, Rows, Cols> matrix<T, Rows, Cols>::diagonal(
  const matrix<T, RC, 1u>& elements)
{
  matrix m;
  for(size_t i = 0; i < RC; ++i)
  {
    m(i, i) = elements(i);
  }
  return m;
}
#endif



#ifndef HOU_DOXYGEN
template <typename T, size_t Rows, size_t Cols>
template <typename... Args, typename Enable>
matrix<T, Rows, Cols> matrix<T, Rows, Cols>::diagonal(Args... elements)
{
  return diagonal(matrix<T, Rows, 1u>(elements...));
}
#endif



template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols>::matrix()
  : m_elements()
{
  fill(0);
}



template <typename T, size_t Rows, size_t Cols>
template <typename U, typename Enable>
matrix<T, Rows, Cols>::matrix(const matrix<U, Rows, Cols>& other)
  : m_elements()
{
  std::copy(
    other.m_elements.begin(), other.m_elements.end(), m_elements.begin());
}



template <typename T, size_t Rows, size_t Cols>
template <typename... Args, typename Enable>
matrix<T, Rows, Cols>::matrix(Args... elements)
  : m_elements{elements...}
{}



template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols>::matrix(std::initializer_list<T> elements)
  : m_elements()
{
  HOU_EXPECT(elements.size() == get_size());
  std::copy(elements.begin(), elements.end(), m_elements.begin());
}



template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols>::~matrix()
{}



template <typename T, size_t Rows, size_t Cols>
T matrix<T, Rows, Cols>::operator()(size_t row, size_t col) const
{
  HOU_EXPECT((row < Rows) && (col < Cols));
  return m_elements[row * Cols + col];
}



template <typename T, size_t Rows, size_t Cols>
T& matrix<T, Rows, Cols>::operator()(size_t row, size_t col)
{
  HOU_EXPECT((row < Rows) && (col < Cols));
  return m_elements[row * Cols + col];
}



template <typename T, size_t Rows, size_t Cols>
T matrix<T, Rows, Cols>::operator()(size_t index) const
{
  HOU_EXPECT(index < get_size());
  return m_elements[index];
}



template <typename T, size_t Rows, size_t Cols>
T& matrix<T, Rows, Cols>::operator()(size_t index)
{
  HOU_EXPECT(index < get_size());
  return m_elements[index];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t c, typename Enable>
T matrix<T, Rows, Cols>::x() const
{
  return m_elements[0];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t c, typename Enable>
T& matrix<T, Rows, Cols>::x()
{
  return m_elements[0];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t r, size_t c, typename Enable>
T matrix<T, Rows, Cols>::y() const
{
  return m_elements[1];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t r, size_t c, typename Enable>
T& matrix<T, Rows, Cols>::y()
{
  return m_elements[1];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t r, size_t c, typename Enable>
T matrix<T, Rows, Cols>::z() const
{
  return m_elements[2];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t r, size_t c, typename Enable>
T& matrix<T, Rows, Cols>::z()
{
  return m_elements[2];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t r, size_t c, typename Enable>
T matrix<T, Rows, Cols>::w() const
{
  return m_elements[3];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t r, size_t c, typename Enable>
T& matrix<T, Rows, Cols>::w()
{
  return m_elements[3];
}



template <typename T, size_t Rows, size_t Cols>
const T* matrix<T, Rows, Cols>::data() const
{
  return m_elements.data();
}



template <typename T, size_t Rows, size_t Cols>
template <typename... Args, typename Enable>
void matrix<T, Rows, Cols>::set(Args... elements)
{
  *this = matrix(elements...);
}



template <typename T, size_t Rows, size_t Cols>
void matrix<T, Rows, Cols>::fill(T value)
{
  m_elements.fill(value);
}



template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::operator+=(
  const matrix<T, Rows, Cols>& rhs)
{
  for(size_t i = 0; i < get_size(); ++i)
  {
    m_elements[i] += rhs.m_elements[i];
  }
  return *this;
}



template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols> operator+(
  matrix<T, Rows, Cols> lhs, const matrix<T, Rows, Cols>& rhs)
{
  return lhs += rhs;
}



template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::operator-=(
  const matrix<T, Rows, Cols>& rhs)
{
  for(size_t i = 0; i < get_size(); ++i)
  {
    m_elements[i] -= rhs.m_elements[i];
  }
  return *this;
}



template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols> operator-(
  matrix<T, Rows, Cols> lhs, const matrix<T, Rows, Cols>& rhs)
{
  return lhs -= rhs;
}



template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::operator*=(T rhs)
{
  for(size_t i = 0; i < get_size(); ++i)
  {
    m_elements[i] *= rhs;
  }
  return *this;
}



template <typename T, size_t Rows, size_t Mid, size_t Cols>
matrix<T, Rows, Cols> operator*(
  const matrix<T, Rows, Mid>& lhs, const matrix<T, Mid, Cols>& rhs)
{
  matrix<T, Rows, Cols> retval;
  for(size_t r = 0; r < Rows; ++r)
  {
    for(size_t c = 0; c < Cols; ++c)
    {
      retval(r, c) = 0.f;
      for(size_t i = 0; i < Mid; ++i)
      {
        retval(r, c) += lhs(r, i) * rhs(i, c);
      }
    }
  }
  return retval;
}



template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::operator/=(T rhs)
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
  return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
}



template <typename T>
T det(const matrix<T, 3, 3>& m)
{
  return m(0, 0) * m(1, 1) * m(2, 2) + m(0, 1) * m(1, 2) * m(2, 0)
    + m(0, 2) * m(1, 0) * m(2, 1) - m(0, 2) * m(1, 1) * m(2, 0)
    - m(0, 1) * m(1, 0) * m(2, 2) - m(0, 0) * m(1, 2) * m(2, 1);
}



template <typename T, size_t RC, typename Enable>
T det(const matrix<T, RC, RC>& m)
{
  T result(0);
  for(size_t col = 0; col < RC; ++col)
  {
    T factor = (col % 2) == 0 ? T(1) : T(-1);
    result += factor * m(0, col) * det(reduce(m, 0, col));
  }
  return result;
}



template <typename T, size_t RC>
T trace(const matrix<T, RC, RC>& m)
{
  T result(0);
  for(size_t i = 0; i < RC; ++i)
  {
    result += m(i, i);
  }
  return result;
}



template <typename T, size_t Rows, size_t Cols, typename Enable>
matrix<T, Rows - 1, Cols - 1> reduce(
  const matrix<T, Rows, Cols>& m, size_t row, size_t col)
{
  HOU_EXPECT((row < Rows) && (col < Cols));
  matrix<T, Rows - 1, Cols - 1> retval;
  size_t rin = 0;
  for(size_t r = 0; r < Rows - 1; ++r)
  {
    if(rin == row)
    {
      ++rin;
    }
    size_t cin = 0;
    for(size_t c = 0; c < Cols - 1; ++c)
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
template <typename T, size_t Rows, size_t Cols>
matrix<T, Cols, Rows> transpose(const matrix<T, Rows, Cols>& m)
{
  matrix<T, Cols, Rows> retval;
  for(size_t r = 0; r < Rows; ++r)
  {
    for(size_t c = 0; c < Cols; ++c)
    {
      retval(c, r) = m(r, c);
    }
  }
  return retval;
}
#endif



#ifndef HOU_DOXYGEN
template <typename T, size_t Rows, size_t Cols>
template <size_t RC, typename Enable>
matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::adjugate()
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



template <typename T, size_t RC, typename Enable>
matrix<T, RC, RC> adjugate(const matrix<T, RC, RC>& m)
{
  matrix<T, RC, RC> adj;
  for(size_t r = 0; r < RC; ++r)
  {
    for(size_t c = 0; c < RC; ++c)
    {
      T factor = ((r + c) % 2) == 0 ? T(1) : T(-1);
      adj(r, c) = factor * det(reduce(m, c, r));
    }
  }
  return adj;
}



#ifndef HOU_DOXYGEN
template <typename T, size_t Rows, size_t Cols>
template <size_t RC, typename Enable>
matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::invert()
{
  T determinant = det(*this);
  HOU_EXPECT(!close(determinant, T(0)));
  return this->adjugate() /= determinant;
}
#endif



template <typename T, size_t RC>
matrix<T, RC, RC> inverse(matrix<T, RC, RC> m)
{
  return m.invert();
}



template <typename T, size_t Rows, size_t Cols>
T square_norm(const matrix<T, Rows, Cols>& m)
{
  T sn(0);
  for(size_t i = 0; i < Rows * Cols; ++i)
  {
    sn += m(i) * m(i);
  }
  return sn;
}



template <typename T, size_t Rows, size_t Cols>
T norm(const matrix<T, Rows, Cols>& m)
{
  return std::sqrt(square_norm(m));
}



template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::normalize()
{
  T matNorm = norm(*this);
  HOU_EXPECT(!close(matNorm, T(0)));
  return *this /= matNorm;
}



template <typename T, size_t Rows, size_t Cols>
matrix<T, Rows, Cols> normalized(matrix<T, Rows, Cols> m)
{
  return m.normalize();
}



template <typename T>
matrix<T, 3u, 3u> cross_matrix(const matrix<T, 3u, 1u>& m)
{
  return matrix<T, 3u, 3u>{
    T(0), -m.z(), m.y(), m.z(), T(0), -m.x(), -m.y(), m.x(), T(0)};
}



template <typename T>
matrix<T, 2u, 1u> cross(const matrix<T, 2u, 1u>& v)
{
  return matrix<T, 2u, 1u>{v(1), -v(0)};
}



template <typename T>
matrix<T, 3u, 1u> cross(
  const matrix<T, 3u, 1u>& lhs, const matrix<T, 3u, 1u>& rhs)
{
  return matrix<T, 3u, 1u>{
    lhs(1) * rhs(2) - lhs(2) * rhs(1),
    lhs(2) * rhs(0) - lhs(0) * rhs(2),
    lhs(0) * rhs(1) - lhs(1) * rhs(0),
  };
}



template <typename T>
matrix<T, 3u, 3u> outer_product(
  const matrix<T, 3u, 1u>& lhs, const matrix<T, 3u, 1u>& rhs)
{
  return matrix<T, 3u, 3u>{
    lhs.x() * rhs.x(),
    lhs.x() * rhs.y(),
    lhs.x() * rhs.z(),
    lhs.y() * rhs.x(),
    lhs.y() * rhs.y(),
    lhs.y() * rhs.z(),
    lhs.z() * rhs.x(),
    lhs.z() * rhs.y(),
    lhs.z() * rhs.z(),
  };
}



template <typename T, size_t Rows>
T dot(const matrix<T, Rows, 1u>& lhs, const matrix<T, Rows, 1u>& rhs)
{
  T result(0);
  for(size_t i = 0; i < Rows; ++i)
  {
    result += lhs(i) * rhs(i);
  }
  return result;
}



template <typename T, size_t Rows, size_t Cols>
std::ostream& operator<<(std::ostream& os, const matrix<T, Rows, Cols>& m)
{
  for(size_t r = 0; r < Rows; ++r)
  {
    if(r != 0)
    {
      os << "\n";
    }
    os << "(";
    for(size_t c = 0; c < Cols; ++c)
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

}  // namespace hou
