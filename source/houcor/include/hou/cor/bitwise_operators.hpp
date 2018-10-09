// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_BITWISE_OPERATORS_HPP
#define HOU_COR_BITWISE_OPERATORS_HPP

#include "hou/cor/cor_config.hpp"

#include "hou/cor/std_vector.hpp"

#include <functional>
#include <type_traits>

namespace hou
{

/**
 * Enable bitwise operators for type T.
 *
 * \tparam T the type to enable bitwise operators for.
 */
template <typename T>
struct enable_bitwise_operators
{
  /**
   * Whether the bitwise operators are enabled for type T.
   *
   * Provide a class specialization setting this variable to true to enable
   * bitwise operators for type T.
   */
  static constexpr bool enable = false;
};

/**
 * Bitwise OR operator.
 *
 * \tparam T the type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the bitwise OR result.
 */
template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable, T>::type operator|(
  T lhs, T rhs) noexcept;

/**
 * Bitwise OR operator.
 *
 * \tparam T the type.
 *
 * \param lhs the left operand.
 * It will store the result of the operation.
 *
 * \param rhs the right operand.
 *
 * \return a reference to lhs after performing the bitwise or operation.
 */
template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable, T&>::type
  operator|=(T& lhs, T rhs) noexcept;

/**
 * Bitwise AND operator.
 *
 * \tparam T the type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the bitwise AND result.
 */
template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable, T>::type operator&(
  T lhs, T rhs) noexcept;

/**
 * Bitwise AND operator.
 *
 * \tparam T the type.
 *
 * \param lhs the left operand.
 * It will store the result of the operation.
 *
 * \param rhs the right operand.
 *
 * \return a reference to lhs after performing the bitwise or operation.
 */
template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable, T&>::type
  operator&=(T& lhs, T rhs) noexcept;

/**
 * Checks if all given bits are set in a bitfield.
 *
 * \tparam T the type.
 *
 * \param bitfield the field.
 *
 * \param bits the bits to be checked
 *
 * \return the result of the check.
 */
template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable, bool>::type
  check_all(T bitfield, T bits) noexcept;

/**
 * Checks if any of the given bits are set in a bitfield.
 *
 * \tparam T the type.
 *
 * \param bitfield the field.
 *
 * \param bits the bits to be checked
 *
 * \return the result of the check.
 */
template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable, bool>::type
  check_any(T bitfield, T bits) noexcept;

/**
 * Writes a bitfield into a stream.
 *
 * All bits set to 1 will be printed in the way specified by printer.
 * If more than one bit is set, the values will be separated by ' | '.
 * If no bits are set, a specific value will be printed if provided in the
 * definition of printer.
 *
 * \tparam T the bitfield type.
 *
 * \param os the output stream.
 *
 * \param bitfield the bitfield.
 *
 * \param printer a printer function specifying how each bit should be printed.
 * Even though this function is allowed to handle any value, only the values
 * corresponding to bitfields with a single bit set will be used and to no bits
 * set will be used.
 *
 * \return a reference to os.
 */
template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable,
  std::ostream&>::type
  stream_bitfield(std::ostream& os, T bitfield,
    std::function<void(std::ostream&, T)> printer);

}  // namespace hou

#include "hou/cor/bitwise_operators.inl"

#endif
