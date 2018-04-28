// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename PtrType>
template <typename OtherPtrType, typename Enable>
  not_null<PtrType>::not_null(OtherPtrType&& other)
  : mPtr(std::move(other))
{
  HOU_EXPECT(mPtr != nullptr);
}



template <typename PtrType>
template <typename OtherPtrType, typename Enable>
  not_null<PtrType>::not_null(const not_null<OtherPtrType>& other)
  : mPtr(other.get())
{
  HOU_EXPECT_DEV(mPtr != nullptr);
}



template <typename PtrType>
  const PtrType& not_null<PtrType>::get() const
{
  HOU_EXPECT_DEV(mPtr != nullptr);
  return mPtr;
}



template <typename PtrType>
  PtrType& not_null<PtrType>::get()
{
  HOU_EXPECT_DEV(mPtr != nullptr);
  return mPtr;
}



template <typename PtrType>
  decltype(auto) not_null<PtrType>::operator->() const
{
  return get();
}



template <typename PtrType>
  decltype(auto) not_null<PtrType>::operator->()
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

}

