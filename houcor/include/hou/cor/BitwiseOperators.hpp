// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_COR_BITWISE_OPERATORS_HPP
#define HOU_COR_BITWISE_OPERATORS_HPP

#include "hou/cor/BasicTypes.hpp"

#include <type_traits>



namespace hou
{

/** Enable bitwise operators for type T.
 *
 *  \tparam T the type to enable bitwise operators for.
 */
template <typename T>
  struct EnableBitwiseOperators
{
  /** Whether the bitwise operators are enabled for type T.
   *
   *  Provide a class specialization setting this variable to true to enable
   *  bitwise operators for type T.
   */
  static constexpr bool enable = false;
};

/** Bitwise OR operator.
 *
 *  \tparam T the type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the bitwise OR result.
 */
template <typename T>
  typename std::enable_if<EnableBitwiseOperators<T>::enable, T>::type
  operator|(T lhs, T rhs)
{
  using Utype = typename std::underlying_type<T>::type;
  return static_cast<T>(static_cast<Utype>(lhs) | static_cast<Utype>(rhs));
}

/** Bitwise OR operator.
 *
 *  \tparam T the type.
 *  \param lhs the left operand.
 *  It will store the result of the operation.
 *  \param rhs the right operand.
 *  \return a reference to lhs after performing the bitwise or operation.
 */
template <typename T>
  typename std::enable_if<EnableBitwiseOperators<T>::enable, T&>::type
  operator|=(T& lhs, T rhs)
{
  return lhs = lhs | rhs;
}

/** Bitwise AND operator.
 *
 *  \tparam T the type.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the bitwise AND result.
 */
template <typename T>
  typename std::enable_if<EnableBitwiseOperators<T>::enable, T>::type
  operator&(T lhs, T rhs)
{
  using Utype = typename std::underlying_type<T>::type;
  return static_cast<T>(static_cast<Utype>(lhs) & static_cast<Utype>(rhs));
}

/** Bitwise AND operator.
 *
 *  \tparam T the type.
 *  \param lhs the left operand.
 *  It will store the result of the operation.
 *  \param rhs the right operand.
 *  \return a reference to lhs after performing the bitwise or operation.
 */
template <typename T>
  typename std::enable_if<EnableBitwiseOperators<T>::enable, T&>::type
  operator&=(T& lhs, T rhs)
{
  return lhs = lhs & rhs;
}

/** Checks if a bit is set in a bitfield.
 *
 *  \tparam T the type.
 *  \param bitfield the field.
 *  \param bit the bit.
 *  \return the result of the check.
 */
template <typename T>
  typename std::enable_if<EnableBitwiseOperators<T>::enable, bool>::type
  checkBit(T bitfield, T bit)
{
  return (bitfield & bit) == bit;
}

}

#endif

