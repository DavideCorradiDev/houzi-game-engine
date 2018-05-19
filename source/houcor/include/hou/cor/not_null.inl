// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename PtrType>
template <typename OtherPtrType, typename Enable>
constexpr not_null<PtrType>::not_null(OtherPtrType&& other) noexcept
  : m_ptr(std::move(other))
{}



template <typename PtrType>
template <typename OtherPtrType, typename Enable>
constexpr not_null<PtrType>::not_null(
  const not_null<OtherPtrType>& other) noexcept
  : m_ptr(other.get())
{}



template <typename PtrType>
constexpr const PtrType& not_null<PtrType>::get() const noexcept
{
  return m_ptr;
}



template <typename PtrType>
constexpr PtrType& not_null<PtrType>::get() noexcept
{
  return m_ptr;
}



template <typename PtrType>
constexpr decltype(auto) not_null<PtrType>::operator-> () const noexcept
{
  return get();
}



template <typename PtrType>
constexpr decltype(auto) not_null<PtrType>::operator-> () noexcept
{
  return get();
}



template <typename PtrType>
constexpr decltype(auto) not_null<PtrType>::operator*() const noexcept
{
  return *get();
}



template <typename PtrType>
constexpr not_null<PtrType>::operator PtrType() const noexcept
{
  return get();
}

}  // namespace hou
