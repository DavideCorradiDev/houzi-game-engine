// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
template <typename U, typename Enable>
constexpr not_null<T>::not_null(U&& value)
  : m_ptr(std::move(value))
{
  HOU_PRECOND(m_ptr != nullptr);
}



template <typename T>
template <typename U, typename Enable>
constexpr not_null<T>::not_null(const not_null<U>& other) noexcept
  : m_ptr(other.get())
{}



template <typename T>
constexpr const T& not_null<T>::get() const
{
  HOU_POSTCOND(m_ptr != nullptr);
  return m_ptr;
}



template <typename T>
constexpr decltype(auto) not_null<T>::operator-> () const
{
  return get();
}



template <typename T>
constexpr decltype(auto) not_null<T>::operator-> ()
{
  return get();
}



template <typename T>
constexpr decltype(auto) not_null<T>::operator*() const
{
  return *get();
}



template <typename T>
constexpr not_null<T>::operator T() const
{
  return get();
}



template <typename T>
typename std::remove_reference<T>::type&& move_content(not_null<T>&& t) noexcept
{
  return std::move(t.m_ptr);
}

}  // namespace hou
