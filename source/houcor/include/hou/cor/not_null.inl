// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename PtrType>
template <typename OtherPtrType, typename Enable>
not_null<PtrType>::not_null(OtherPtrType&& other)
  : m_ptr(std::move(other))
{
  HOU_EXPECT(m_ptr != nullptr);
}



template <typename PtrType>
template <typename OtherPtrType, typename Enable>
not_null<PtrType>::not_null(const not_null<OtherPtrType>& other)
  : m_ptr(other.get())
{
  HOU_EXPECT_DEV(m_ptr != nullptr);
}



template <typename PtrType>
const PtrType& not_null<PtrType>::get() const
{
  HOU_EXPECT_DEV(m_ptr != nullptr);
  return m_ptr;
}



template <typename PtrType>
PtrType& not_null<PtrType>::get()
{
  HOU_EXPECT_DEV(m_ptr != nullptr);
  return m_ptr;
}



template <typename PtrType>
decltype(auto) not_null<PtrType>::operator-> () const
{
  return get();
}



template <typename PtrType>
decltype(auto) not_null<PtrType>::operator-> ()
{
  return get();
}



template <typename PtrType>
decltype(auto) not_null<PtrType>::operator*() const
{
  return *get();
}



template <typename PtrType>
not_null<PtrType>::operator PtrType() const
{
  return get();
}

}  // namespace hou
