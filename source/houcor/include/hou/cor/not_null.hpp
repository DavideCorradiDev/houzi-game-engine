// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_NOT_NULL_HPP
#define HOU_COR_NOT_NULL_HPP

#include "hou/cor/cor_export.hpp"

#include <type_traits>



namespace hou
{

/** Wrapper for pointers which cannot be null.
 *
 * not_null works transparently as a pointer, but the wrapped pointer cannot be
 * assigned the nullptr value.
 *
 * \tparam PtrType the pointer type. It can be a naked pointer or a smart
 * pointer.
 */
template <typename PtrType>
class HOU_COR_API not_null
{
public:
  static_assert(std::is_assignable<PtrType&, std::nullptr_t>::value,
    "PtrType cannot be nullptr.");

public:
  /** Converting move constructor.
   *
   * \tparam OtherPtrType the other pointer type.
   *
   * \tparam Enable enabling parameter (should be left to default value).
   *
   * \param other pointer type.
   */
  template <typename OtherPtrType,
    typename Enable
    = std::enable_if_t<std::is_convertible<OtherPtrType, PtrType>::value>>
  constexpr not_null(OtherPtrType&& other) noexcept;

  /** Converting constructor.
   *
   * \tparam OtherPtrType the other pointer type.
   *
   * \tparam Enable enabling parameter (should be left to default value).
   *
   * \param other the other not_null object.
   */
  template <typename OtherPtrType,
    typename Enable
    = std::enable_if_t<std::is_convertible<OtherPtrType, PtrType>::value>>
  constexpr not_null(const not_null<OtherPtrType>& other) noexcept;

  /** Deleted default constructor.
   */
  not_null() = delete;

  /** Deleted nullptr constructor.
   */
  not_null(std::nullptr_t) = delete;

  /** Deleted nullptr assignment operator.
   */
  not_null& operator=(std::nullptr_t) = delete;

  /** Returns a const reference to the wrapped object.
   *
   * \return a const reference to the wrapped object.
   */
  constexpr const PtrType& get() const noexcept;

  /** Returns a reference to the wrapped object.
   *
   * \return a reference to the wrapped object.
   */
  constexpr PtrType& get() noexcept;

  /** Member access operator.
   *
   * Enables not_null to work transparently as a pointer.
   */
  constexpr decltype(auto) operator-> () const noexcept;

  /** Member access operator.
   *
   * Enables not_null to work transparently as a pointer.
   */
  constexpr decltype(auto) operator-> () noexcept;

  /** Unary dereference operator.
   *
   * Enables not_null to work transparently as a pointer.
   *
   * \return a reference to the pointed object.
   */
  constexpr decltype(auto) operator*() const noexcept;

  /** Converts to the underlying pointer type.
   *
   * As type conversion makes a copy, PtrType must be copyable.
   *
   * \return a copy of the underlying pointer of type PtrType.
   */
  constexpr operator PtrType() const noexcept;

private:
  PtrType m_ptr;
};

}  // namespace hou

#include "hou/cor/not_null.inl"

#endif
