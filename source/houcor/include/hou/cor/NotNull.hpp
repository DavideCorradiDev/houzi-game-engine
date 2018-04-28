// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_NOT_NULL_HPP
#define HOU_COR_NOT_NULL_HPP

#include "hou/cor/CorExport.hpp"

#include "hou/cor/Error.hpp"

#include <type_traits>



namespace hou
{

/** Wrapper for pointers which cannot be null.
 *
 *  NotNull works transparently as a pointer, but the wrapped pointer cannot be
 *  assigned the nullptr value.
 *
 *  \tparam PtrType the pointer type. It can be a naked pointer or a smart
 *  pointer.
 */
template <typename PtrType>
  class HOU_COR_API NotNull
{
public:
  static_assert(std::is_assignable<PtrType&, std::nullptr_t>::value
    , "PtrType cannot be assigned nullptr.");

public:
  /** Converting move constructor.
   *
   *  \tparam OtherPtrType the other pointer type.
   *  \tparam Enable enabling parameter (should be left to default value).
   *  \param other pointer type.
   */
  template <typename OtherPtrType, typename Enable
    = std::enable_if_t<std::is_convertible<OtherPtrType, PtrType>::value>>
    NotNull(OtherPtrType&& other);

  /** Converting constructor.
   *
   *  \tparam OtherPtrType the other pointer type.
   *  \tparam Enable enabling parameter (should be left to default value).
   *  \param other the other NotNull object.
   */
  template <typename OtherPtrType, typename Enable
    = std::enable_if_t<std::is_convertible<OtherPtrType, PtrType>::value>>
    NotNull(const NotNull<OtherPtrType>& other);

  /** Deleted default constructor.
   */
  NotNull() = delete;

  /** Deleted nullptr constructor.
   */
  NotNull(std::nullptr_t) = delete;

  /** Deleted nullptr assignment operator.
   */
  NotNull& operator=(std::nullptr_t) = delete;

  /** Returns a const reference to the wrapped object.
   *
   *  \return a const reference to the wrapped object.
   */
  const PtrType& get() const;

  /** Returns a reference to the wrapped object.
   *
   *  \return a reference to the wrapped object.
   */
  PtrType& get();

  /** Member access operator.
   *
   *  Enables NotNull to work transparently as a pointer.
   */
  decltype(auto) operator->() const;

  /** Member access operator.
   *
   *  Enables NotNull to work transparently as a pointer.
   */
  decltype(auto) operator->();

  /** Unary dereference operator.
   *
   *  Enables NotNull to work transparently as a pointer.
   *
   *  \return a reference to the pointed object.
   */
  decltype(auto) operator*() const;

  /** Converts to the underlying pointer type.
   *
   *  As type conversion makes a copy, PtrType must be copyable.
   *
   *  \return a copy of the underlying pointer of type PtrType.
   */
  operator PtrType() const;

private:
  PtrType mPtr;
};

}



#include "hou/cor/NotNull.inl"

#endif

