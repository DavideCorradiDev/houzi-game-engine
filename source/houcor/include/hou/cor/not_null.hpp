// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_NOT_NULL_HPP
#define HOU_COR_NOT_NULL_HPP

#include "hou/cor/cor_config.hpp"

#include <type_traits>
#include <utility>



namespace hou
{

/** Wrapper for pointers which cannot be null.
 *
 * not_null works transparently as a pointer, but the wrapped pointer cannot be
 * assigned the nullptr value.
 *
 * \tparam T the pointer type. It can be a naked pointer or a smart
 * pointer.
 */
template <typename T>
class not_null
{
public:
  static_assert(
    std::is_assignable<T&, std::nullptr_t>::value, "T cannot be nullptr.");

public:
  /** Converting move constructor.
   *
   * \tparam U the value pointer type.
   *
   * \tparam Enable enabling parameter (should be left to default value).
   *
   * \param value pointer type.
   *
   * \throws hou::precondition_error if value is nullptr
   */
  template <typename U,
    typename Enable = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr not_null(U&& value);

  /** Converting constructor.
   *
   * \tparam U the other pointer type.
   *
   * \tparam Enable enabling parameter (should be left to default value).
   *
   * \param other the other not_null object.
   */
  template <typename U,
    typename Enable = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr not_null(const not_null<U>& other) noexcept;

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
   * \throws hou::postcondition_violation if the internally stored pointer is
   * nullptr.
   *
   * \return a const reference to the wrapped object.
   */
  constexpr const T& get() const;

  /** Member access operator.
   *
   * \throws hou::postcondition_violation if the internally stored pointer is
   * nullptr.
   *
   * Enables not_null to work transparently as a pointer.
   */
  constexpr decltype(auto) operator-> () const;

  /** Member access operator.
   *
   * \throws hou::postcondition_violation if the internally stored pointer is
   * nullptr.
   *
   * Enables not_null to work transparently as a pointer.
   */
  constexpr decltype(auto) operator-> ();

  /** Unary dereference operator.
   *
   * Enables not_null to work transparently as a pointer.
   *
   * \throws hou::postcondition_violation if the internally stored pointer is
   * nullptr.
   *
   * \return a reference to the pointed object.
   */
  constexpr decltype(auto) operator*() const;

  /** Converts to the underlying pointer type.
   *
   * As type conversion makes a copy, T must be copyable.
   *
   * \throws hou::postcondition_violation if the internally stored pointer is
   * nullptr.
   *
   * \return a copy of the underlying pointer of type T.
   */
  constexpr operator T() const;

  // Friend declarations.
  template <typename U>
  friend typename std::remove_reference<U>::type&& move_content(
    not_null<U>&& t) noexcept;

private:
  T m_ptr;
};

/** Moves the content away from the nullptr.
 *
 * \tparam T the pointer type.
 *
 * \param t the nullptr.
 *
 * \return an object of type T containing the object moved from T.
 */
template <typename T>
typename std::remove_reference<T>::type&& move_content(
  not_null<T>&& t) noexcept;

}  // namespace hou

#include "hou/cor/not_null.inl"

#endif
