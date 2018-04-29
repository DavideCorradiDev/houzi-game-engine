// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
rectangle<T>::rectangle()
  : m_position()
  , m_size()
{}



template <typename T>
rectangle<T>::rectangle(const vec2<T>& position, const vec2<T>& size)
  : m_position(position)
  , m_size(size)
{}



template <typename T>
rectangle<T>::rectangle(T x, T y, T w, T h)
  : rectangle(vec2<T>(x, y), vec2<T>(w, h))
{}



template <typename T>
template <typename U>
rectangle<T>::rectangle(const rectangle<U>& other)
  : rectangle<T>(vec2<T>(other.get_position()), vec2<T>(other.get_size()))
{}



template <typename T>
const vec2<T>& rectangle<T>::get_position() const
{
  return m_position;
}



template <typename T>
void rectangle<T>::set_position(const vec2<T>& value)
{
  m_position = value;
}



template <typename T>
const vec2<T>& rectangle<T>::get_size() const
{
  return m_size;
}



template <typename T>
void rectangle<T>::set_size(const vec2<T>& value)
{
  m_size = value;
}



template <typename T>
T rectangle<T>::x() const
{
  return m_position.x();
}



template <typename T>
T& rectangle<T>::x()
{
  return m_position.x();
}



template <typename T>
T rectangle<T>::y() const
{
  return m_position.y();
}



template <typename T>
T& rectangle<T>::y()
{
  return m_position.y();
}



template <typename T>
T rectangle<T>::w() const
{
  return m_size.x();
}



template <typename T>
T& rectangle<T>::w()
{
  return m_size.x();
}



template <typename T>
T rectangle<T>::h() const
{
  return m_size.y();
}



template <typename T>
T& rectangle<T>::h()
{
  return m_size.y();
}



template <typename T>
T rectangle<T>::l() const
{
  return x();
}



template <typename T>
T rectangle<T>::t() const
{
  return y();
}



template <typename T>
T rectangle<T>::r() const
{
  return x() + w();
}



template <typename T>
T rectangle<T>::b() const
{
  return y() + h();
}



template <typename T>
bool operator==(const rectangle<T>& lhs, const rectangle<T>& rhs)
{
  return lhs.get_position() == rhs.get_position()
    && lhs.get_size() == rhs.get_size();
}




template <typename T>
bool operator!=(const rectangle<T>& lhs, const rectangle<T>& rhs)
{
  return !(lhs == rhs);
}



template <typename T>
  bool close(const rectangle<T>& lhs, const rectangle<T>& rhs, T acc)
{
  return close(lhs.get_position(), rhs.get_position(), acc)
    && close(lhs.get_size(), rhs.get_size(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const rectangle<T>& rect)
{
  return os << "{Position = " << transpose(rect.get_position())
    << ", size_type = " << transpose(rect.get_size()) << "}";
}



template <typename T>
  bool is_point_in_rectangle(const rectangle<T>& r, const vec2<T>& p)
{
  return p.x() >= r.l() && p.x() <= r.r() && p.y() >= r.t() && p.y() <= r.b();
}

}

