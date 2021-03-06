// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_BOUNDED_HPP
#define HOU_BOUNDED_HPP

#include "hou/cor/assertions.hpp"



template <typename T>
class bounded
{
public:
  bounded(T value, T min, T max);
  bounded& operator=(T value);
  const bounded& operator+=(T delta);
  const bounded& operator-=(T delta);
  const T& get() const;
  operator T() const;

private:
  T m_value;
  T m_min;
  T m_max;
};



template <typename T>
bounded<T>::bounded(T value, T min, T max)
  : m_value(value)
  , m_min(min)
  , m_max(max)
{
  HOU_PRECOND(value >= min && value <= max);
}



template <typename T>
bounded<T>& bounded<T>::operator=(T value)
{
  if(value > m_max)
  {
    m_value = m_max;
  }
  else if(value < m_min)
  {
    m_value = m_min;
  }
  else
  {
    m_value = value;

  }
  return *this;
}



template <typename T>
const bounded<T>& bounded<T>::operator+=(T delta)
{
  if(delta > T(0))
  {
    if(m_max - m_value <= delta)
    {
      m_value = m_max;
    }
    else
    {
      m_value += delta;
    }
  }
  else if(delta < T(0))
  {
    if(m_value - m_min <= -delta)
    {
      m_value = m_min;
    }
    else
    {
      m_value += delta;
    }
  }
  return *this;
}



template <typename T>
const bounded<T>& bounded<T>::operator-=(T delta)
{
  if (delta > T(0))
  {
    if(m_value - m_min <= delta)
    {
      m_value = m_min;
    }
    else
    {
      m_value -= delta;
    }
  }
  else if (delta < T(0))
  {
    if(m_max - m_value <= -delta)
    {
      m_value = m_max;
    }
    else
    {
      m_value -= delta;
    }
  }
  return *this;
}



template <typename T>
const T& bounded<T>::get() const
{
  return m_value;
}



template <typename T>
bounded<T>::operator T() const
{
  return get();
}

#endif
