// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

template <typename PtrType>
template <typename OtherPtrType, typename Enable>
  NotNull<PtrType>::NotNull(OtherPtrType&& other)
  : mPtr(std::move(other))
{
  HOU_EXPECT(mPtr != nullptr);
}



template <typename PtrType>
template <typename OtherPtrType, typename Enable>
  NotNull<PtrType>::NotNull(const NotNull<OtherPtrType>& other)
  : mPtr(other.get())
{
  HOU_EXPECT_DEV(mPtr != nullptr);
}



template <typename PtrType>
  const PtrType& NotNull<PtrType>::get() const
{
  HOU_EXPECT_DEV(mPtr != nullptr);
  return mPtr;
}



template <typename PtrType>
  PtrType& NotNull<PtrType>::get()
{
  HOU_EXPECT_DEV(mPtr != nullptr);
  return mPtr;
}



template <typename PtrType>
  decltype(auto) NotNull<PtrType>::operator->() const
{
  return get();
}



template <typename PtrType>
  decltype(auto) NotNull<PtrType>::operator->()
{
  return get();
}



template <typename PtrType>
  decltype(auto) NotNull<PtrType>::operator*() const
{
  return *get();
}



template <typename PtrType>
  NotNull<PtrType>::operator PtrType() const
{
  return get();
}

}

