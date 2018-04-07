// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

template <typename T>
Rectangle<T>::Rectangle()
  : mPosition()
  , mSize()
{}



template <typename T>
Rectangle<T>::Rectangle(const Vec2<T>& position, const Vec2<T>& size)
  : mPosition(position)
  , mSize(size)
{}



template <typename T>
Rectangle<T>::Rectangle(T x, T y, T w, T h)
  : Rectangle(Vec2<T>(x, y), Vec2<T>(w, h))
{}



template <typename T>
template <typename U>
Rectangle<T>::Rectangle(const Rectangle<U>& other)
  : Rectangle<T>(Vec2<T>(other.getPosition()), Vec2<T>(other.getSize()))
{}



template <typename T>
const Vec2<T>& Rectangle<T>::getPosition() const
{
  return mPosition;
}



template <typename T>
void Rectangle<T>::setPosition(const Vec2<T>& value)
{
  mPosition = value;
}



template <typename T>
const Vec2<T>& Rectangle<T>::getSize() const
{
  return mSize;
}



template <typename T>
void Rectangle<T>::setSize(const Vec2<T>& value)
{
  mSize = value;
}



template <typename T>
T Rectangle<T>::x() const
{
  return mPosition.x();
}



template <typename T>
T& Rectangle<T>::x()
{
  return mPosition.x();
}



template <typename T>
T Rectangle<T>::y() const
{
  return mPosition.y();
}



template <typename T>
T& Rectangle<T>::y()
{
  return mPosition.y();
}



template <typename T>
T Rectangle<T>::w() const
{
  return mSize.x();
}



template <typename T>
T& Rectangle<T>::w()
{
  return mSize.x();
}



template <typename T>
T Rectangle<T>::h() const
{
  return mSize.y();
}



template <typename T>
T& Rectangle<T>::h()
{
  return mSize.y();
}



template <typename T>
T Rectangle<T>::l() const
{
  return x();
}



template <typename T>
T Rectangle<T>::t() const
{
  return y();
}



template <typename T>
T Rectangle<T>::r() const
{
  return x() + w();
}



template <typename T>
T Rectangle<T>::b() const
{
  return y() + h();
}



template <typename T>
bool operator==(const Rectangle<T>& lhs, const Rectangle<T>& rhs)
{
  return lhs.getPosition() == rhs.getPosition()
    && lhs.getSize() == rhs.getSize();
}




template <typename T>
bool operator!=(const Rectangle<T>& lhs, const Rectangle<T>& rhs)
{
  return !(lhs == rhs);
}



template <typename T>
  bool close(const Rectangle<T>& lhs, const Rectangle<T>& rhs, T acc)
{
  return close(lhs.getPosition(), rhs.getPosition(), acc)
    && close(lhs.getSize(), rhs.getSize(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const Rectangle<T>& rect)
{
  return os << "{Position = " << transpose(rect.getPosition())
    << ", Size = " << transpose(rect.getSize()) << "}";
}



template <typename T>
  bool isPointInRectangle(const Rectangle<T>& r, const Vec2<T>& p)
{
  return p.x() >= r.l() && p.x() <= r.r() && p.y() >= r.t() && p.y() <= r.b();
}

}

