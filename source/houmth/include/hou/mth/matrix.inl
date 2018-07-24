// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T, size_t Rows, size_t Cols>
constexpr size_t matrix<T, Rows, Cols>::get_row_count() noexcept
{
  return Rows;
}



template <typename T, size_t Rows, size_t Cols>
constexpr size_t matrix<T, Rows, Cols>::get_column_count() noexcept
{
  return Cols;
}



template <typename T, size_t Rows, size_t Cols>
constexpr size_t matrix<T, Rows, Cols>::size() noexcept
{
  return Rows * Cols;
}



template <typename T, size_t Rows, size_t Cols>
const  matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::zero() noexcept
{
  static const matrix m;
  return m;
}



template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols> matrix<T, Rows, Cols>::filled(T value) noexcept
{
  matrix m;
  m.fill(value);
  return m;
}



#ifndef HOU_DOXYGEN
template <typename T, size_t Rows, size_t Cols>
template <size_t RC, typename Enable>
const matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::identity() noexcept
{
  static const matrix m = diagonal(vec<T, Rows>::filled(T(1)));
  return m;
}
#endif



#ifndef HOU_DOXYGEN
template <typename T, size_t Rows, size_t Cols>
template <size_t RC, typename Enable>
constexpr matrix<T, Rows, Cols> matrix<T, Rows, Cols>::diagonal(
  const matrix<T, RC, 1u>& elements) noexcept
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
constexpr matrix<T, Rows, Cols> matrix<T, Rows, Cols>::diagonal(
  Args... elements) noexcept
{
  return diagonal(matrix<T, Rows, 1u>(elements...));
}
#endif



template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols>::matrix() noexcept
  : m_elements()
{
  fill(T(0));
}



template <typename T, size_t Rows, size_t Cols>
template <typename U, typename Enable>
constexpr matrix<T, Rows, Cols>::matrix(
  const matrix<U, Rows, Cols>& other) noexcept
  : m_elements()
{
  for(size_t i = 0; i < size(); ++i)
  {
    m_elements[i] = static_cast<T>(other.m_elements[i]);
  }
}



template <typename T, size_t Rows, size_t Cols>
template <typename... Args, typename Enable>
constexpr matrix<T, Rows, Cols>::matrix(Args... elements) noexcept
  : m_elements{elements...}
{}



template <typename T, size_t Rows, size_t Cols>
constexpr T matrix<T, Rows, Cols>::operator[](size_t index) const noexcept
{
  HOU_DEV_ASSERT(index < size());
  return m_elements[index];
}



template <typename T, size_t Rows, size_t Cols>
constexpr T& matrix<T, Rows, Cols>::operator[](size_t index) noexcept
{
  HOU_DEV_ASSERT(index < size());
  return m_elements[index];
}



template <typename T, size_t Rows, size_t Cols>
constexpr T matrix<T, Rows, Cols>::operator()(size_t index) const
{
  HOU_CHECK_0(index < size(), out_of_range);
  return m_elements[index];
}



template <typename T, size_t Rows, size_t Cols>
constexpr T& matrix<T, Rows, Cols>::operator()(size_t index)
{
  HOU_CHECK_0(index < size(), out_of_range);
  return m_elements[index];
}



template <typename T, size_t Rows, size_t Cols>
constexpr T matrix<T, Rows, Cols>::operator()(size_t row, size_t col) const
{
  HOU_CHECK_0((row < Rows) && (col < Cols), out_of_range);
  return m_elements[row * Cols + col];
}



template <typename T, size_t Rows, size_t Cols>
constexpr T& matrix<T, Rows, Cols>::operator()(size_t row, size_t col)
{
  HOU_CHECK_0((row < Rows) && (col < Cols), out_of_range);
  return m_elements[row * Cols + col];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t c, typename Enable>
constexpr T matrix<T, Rows, Cols>::x() const noexcept
{
  return m_elements[0];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t c, typename Enable>
constexpr T& matrix<T, Rows, Cols>::x() noexcept
{
  return m_elements[0];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t r, size_t c, typename Enable>
constexpr T matrix<T, Rows, Cols>::y() const noexcept
{
  return m_elements[1];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t r, size_t c, typename Enable>
constexpr T& matrix<T, Rows, Cols>::y() noexcept
{
  return m_elements[1];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t r, size_t c, typename Enable>
constexpr T matrix<T, Rows, Cols>::z() const noexcept
{
  return m_elements[2];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t r, size_t c, typename Enable>
constexpr T& matrix<T, Rows, Cols>::z() noexcept
{
  return m_elements[2];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t r, size_t c, typename Enable>
constexpr T matrix<T, Rows, Cols>::w() const noexcept
{
  return m_elements[3];
}



template <typename T, size_t Rows, size_t Cols>
template <size_t r, size_t c, typename Enable>
constexpr T& matrix<T, Rows, Cols>::w() noexcept
{
  return m_elements[3];
}



template <typename T, size_t Rows, size_t Cols>
constexpr const T* matrix<T, Rows, Cols>::data() const noexcept
{
  return m_elements.data();
}



template <typename T, size_t Rows, size_t Cols>
constexpr T* matrix<T, Rows, Cols>::data() noexcept
{
  return m_elements.data();
}



template <typename T, size_t Rows, size_t Cols>
constexpr typename matrix<T, Rows, Cols>::const_iterator
  matrix<T, Rows, Cols>::begin() const noexcept
{
  return m_elements.begin();
}



template <typename T, size_t Rows, size_t Cols>
constexpr typename matrix<T, Rows, Cols>::iterator
  matrix<T, Rows, Cols>::begin() noexcept
{
  return m_elements.begin();
}



template <typename T, size_t Rows, size_t Cols>
constexpr typename matrix<T, Rows, Cols>::const_iterator
  matrix<T, Rows, Cols>::cbegin() const noexcept
{
  return m_elements.cbegin();
}



template <typename T, size_t Rows, size_t Cols>
constexpr typename matrix<T, Rows, Cols>::const_reverse_iterator
  matrix<T, Rows, Cols>::rbegin() const noexcept
{
  return m_elements.rbegin();
}



template <typename T, size_t Rows, size_t Cols>
constexpr typename matrix<T, Rows, Cols>::reverse_iterator
  matrix<T, Rows, Cols>::rbegin() noexcept
{
  return m_elements.rbegin();
}



template <typename T, size_t Rows, size_t Cols>
constexpr typename matrix<T, Rows, Cols>::const_reverse_iterator
  matrix<T, Rows, Cols>::crbegin() const noexcept
{
  return m_elements.crbegin();
}



template <typename T, size_t Rows, size_t Cols>
constexpr typename matrix<T, Rows, Cols>::const_iterator
  matrix<T, Rows, Cols>::end() const noexcept
{
  return m_elements.end();
}



template <typename T, size_t Rows, size_t Cols>
constexpr typename matrix<T, Rows, Cols>::iterator
  matrix<T, Rows, Cols>::end() noexcept
{
  return m_elements.end();
}



template <typename T, size_t Rows, size_t Cols>
constexpr typename matrix<T, Rows, Cols>::const_iterator
  matrix<T, Rows, Cols>::cend() const noexcept
{
  return m_elements.cend();
}



template <typename T, size_t Rows, size_t Cols>
constexpr typename matrix<T, Rows, Cols>::const_reverse_iterator
  matrix<T, Rows, Cols>::rend() const noexcept
{
  return m_elements.rend();
}



template <typename T, size_t Rows, size_t Cols>
constexpr typename matrix<T, Rows, Cols>::reverse_iterator
  matrix<T, Rows, Cols>::rend() noexcept
{
  return m_elements.rend();
}



template <typename T, size_t Rows, size_t Cols>
constexpr typename matrix<T, Rows, Cols>::const_reverse_iterator
  matrix<T, Rows, Cols>::crend() const noexcept
{
  return m_elements.crend();
}



template <typename T, size_t Rows, size_t Cols>
template <typename... Args, typename Enable>
constexpr void matrix<T, Rows, Cols>::set(Args... elements) noexcept
{
  *this = matrix(elements...);
}



template <typename T, size_t Rows, size_t Cols>
constexpr void matrix<T, Rows, Cols>::fill(T value) noexcept
{
  m_elements.fill(value);
}



template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::operator+=(
  const matrix<T, Rows, Cols>& rhs) noexcept
{
  for(size_t i = 0; i < size(); ++i)
  {
    m_elements[i] += rhs.m_elements[i];
  }
  return *this;
}



template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols> operator+(
  matrix<T, Rows, Cols> lhs, const matrix<T, Rows, Cols>& rhs) noexcept
{
  return lhs += rhs;
}



template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::operator-=(
  const matrix<T, Rows, Cols>& rhs) noexcept
{
  for(size_t i = 0; i < size(); ++i)
  {
    m_elements[i] -= rhs.m_elements[i];
  }
  return *this;
}



template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols> operator-(
  matrix<T, Rows, Cols> lhs, const matrix<T, Rows, Cols>& rhs) noexcept
{
  return lhs -= rhs;
}



template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols> operator-(matrix<T, Rows, Cols> m) noexcept
{
  for(size_t i = 0; i < m.size(); ++i)
  {
    m.m_elements[i] = -m.m_elements[i];
  }
  return m;
}



template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::operator*=(
  T rhs) noexcept
{
  for(size_t i = 0; i < size(); ++i)
  {
    m_elements[i] *= rhs;
  }
  return *this;
}



template <typename T, size_t Rows, size_t Mid, size_t Cols>
constexpr matrix<T, Rows, Cols> operator*(
  const matrix<T, Rows, Mid>& lhs, const matrix<T, Mid, Cols>& rhs) noexcept
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
constexpr matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::operator/=(
  T rhs) noexcept
{
  for(size_t i = 0; i < size(); ++i)
  {
    m_elements[i] /= rhs;
  }
  return *this;
}



template <typename T>
constexpr T det(const matrix<T, 1, 1>& m) noexcept
{
  return m(0);
}



template <typename T>
constexpr T det(const matrix<T, 2, 2>& m) noexcept
{
  return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
}



template <typename T>
constexpr T det(const matrix<T, 3, 3>& m) noexcept
{
  return m(0, 0) * m(1, 1) * m(2, 2) + m(0, 1) * m(1, 2) * m(2, 0)
    + m(0, 2) * m(1, 0) * m(2, 1) - m(0, 2) * m(1, 1) * m(2, 0)
    - m(0, 1) * m(1, 0) * m(2, 2) - m(0, 0) * m(1, 2) * m(2, 1);
}



template <typename T, size_t RC, typename Enable>
constexpr T det(const matrix<T, RC, RC>& m) noexcept
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
constexpr T trace(const matrix<T, RC, RC>& m) noexcept
{
  T result(0);
  for(size_t i = 0; i < RC; ++i)
  {
    result += m(i, i);
  }
  return result;
}



template <typename T, size_t Rows, size_t Cols, typename Enable>
constexpr matrix<T, Rows - 1, Cols - 1> reduce(
  const matrix<T, Rows, Cols>& m, size_t row, size_t col)
{
  HOU_PRECOND((row < Rows) && (col < Cols));
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
constexpr matrix<T, Cols, Rows> transpose(
  const matrix<T, Rows, Cols>& m) noexcept
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
constexpr matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::adjugate() noexcept
{
  *this = ::hou::adjugate(*this);
  return *this;
}
#endif



template <typename T>
constexpr matrix<T, 1, 1> adjugate(const matrix<T, 1, 1>&) noexcept
{
  return matrix<T, 1, 1>::identity();
}



template <typename T>
constexpr matrix<T, 2, 2> adjugate(const matrix<T, 2, 2>& m) noexcept
{
  return matrix<T, 2, 2>{m(3), -m(1), -m(2), m(0)};
}



template <typename T, size_t RC, typename Enable>
constexpr matrix<T, RC, RC> adjugate(const matrix<T, RC, RC>& m) noexcept
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
constexpr matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::invert()
{
  T determinant = det(*this);
  HOU_CHECK_0(!close(determinant, T(0)), inversion_error);
  return this->adjugate() /= determinant;
}
#endif



template <typename T, size_t RC>
constexpr matrix<T, RC, RC> inverse(matrix<T, RC, RC> m)
{
  return m.invert();
}



template <typename T, size_t Rows, size_t Cols>
constexpr T square_norm(const matrix<T, Rows, Cols>& m) noexcept
{
  T sn(0);
  for(size_t i = 0; i < Rows * Cols; ++i)
  {
    sn += m(i) * m(i);
  }
  return sn;
}



template <typename T, size_t Rows, size_t Cols>
constexpr T norm(const matrix<T, Rows, Cols>& m) noexcept
{
  return std::sqrt(square_norm(m));
}



template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols>& matrix<T, Rows, Cols>::normalize()
{
  T matNorm = norm(*this);
  HOU_PRECOND(!close(matNorm, T(0)));
  return *this /= matNorm;
}



template <typename T, size_t Rows, size_t Cols>
constexpr matrix<T, Rows, Cols> normalized(matrix<T, Rows, Cols> m)
{
  return m.normalize();
}



template <typename T>
constexpr matrix<T, 3u, 3u> cross_matrix(const matrix<T, 3u, 1u>& m) noexcept
{
  return matrix<T, 3u, 3u>{
    T(0), -m.z(), m.y(), m.z(), T(0), -m.x(), -m.y(), m.x(), T(0)};
}



template <typename T>
constexpr matrix<T, 2u, 1u> cross(const matrix<T, 2u, 1u>& v) noexcept
{
  return matrix<T, 2u, 1u>{v(1), -v(0)};
}



template <typename T>
constexpr matrix<T, 3u, 1u> cross(
  const matrix<T, 3u, 1u>& lhs, const matrix<T, 3u, 1u>& rhs) noexcept
{
  // clang-format off
  return matrix<T, 3u, 1u>{
    lhs(1) * rhs(2) - lhs(2) * rhs(1),
    lhs(2) * rhs(0) - lhs(0) * rhs(2),
    lhs(0) * rhs(1) - lhs(1) * rhs(0),
  };
  // clang-format on
}



template <typename T>
constexpr matrix<T, 3u, 3u> outer_product(
  const matrix<T, 3u, 1u>& lhs, const matrix<T, 3u, 1u>& rhs) noexcept
{
  // clang-format off
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
  // clang-format on
}



template <typename T, size_t Rows>
constexpr T dot(
  const matrix<T, Rows, 1u>& lhs, const matrix<T, Rows, 1u>& rhs) noexcept
{
  T result(0);
  for(size_t i = 0; i < Rows; ++i)
  {
    result += lhs(i) * rhs(i);
  }
  return result;
}



template <typename T, size_t Rows, size_t Cols>
bool operator==(
  const matrix<T, Rows, Cols>& lhs, const matrix<T, Rows, Cols>& rhs) noexcept
{
  return lhs.m_elements == rhs.m_elements;
}



template <typename T, size_t Rows, size_t Cols>
bool operator!=(
  const matrix<T, Rows, Cols>& lhs, const matrix<T, Rows, Cols>& rhs) noexcept
{
  return lhs.m_elements != rhs.m_elements;
}



template <typename T, size_t Rows, size_t Cols>
bool close(const matrix<T, Rows, Cols>& lhs, const matrix<T, Rows, Cols>& rhs,
  T acc) noexcept
{
  return close(lhs.m_elements, rhs.m_elements, acc);
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



template <typename T, typename U, size_t Rows, size_t Cols>
bool check_matching_sign<matrix<T, Rows, Cols>, matrix<U, Rows, Cols>>::check(
  const t_matrix& t, const u_matrix& u)
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

}  // namespace hou
