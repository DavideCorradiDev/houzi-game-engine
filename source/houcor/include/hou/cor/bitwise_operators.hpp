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
  T lhs, T rhs) noexcept
{
  using utype = typename std::underlying_type<T>::type;
  return static_cast<T>(static_cast<utype>(lhs) | static_cast<utype>(rhs));
}

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
  operator|=(T& lhs, T rhs) noexcept
{
  return lhs = lhs | rhs;
}

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
  T lhs, T rhs) noexcept
{
  using utype = typename std::underlying_type<T>::type;
  return static_cast<T>(static_cast<utype>(lhs) & static_cast<utype>(rhs));
}

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
  operator&=(T& lhs, T rhs) noexcept
{
  return lhs = lhs & rhs;
}

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
  check_all(T bitfield, T bits) noexcept
{
  return (bitfield & bits) == bits;
}

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
  check_any(T bitfield, T bits) noexcept
{
  return (bitfield & bits) != T(0);
}



template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable,
  std::ostream&>::type
  stream_bitfield(
    std::ostream& os, T bitfield, std::function<void(std::ostream&, T)> printer)
{
  using bitfield_type = typename std::underlying_type<T>::type;

  std::vector<T> bits_to_print;

  bitfield_type all_bits = static_cast<bitfield_type>(bitfield);
  if(all_bits == 0)
  {
    bits_to_print.push_back(T(0));
  }
  else
  {
    bitfield_type current_bit = 1;
    while(current_bit <= all_bits)
    {
      if(current_bit & all_bits)
      {
        bits_to_print.push_back(T(current_bit));
      }
      current_bit <<= 1;
    }
  }

  for(auto it = bits_to_print.rbegin(); it != bits_to_print.rend(); ++it)
  {
    if(it != bits_to_print.rbegin())
    {
      os << " | ";
    }
    printer(os, *it);
  }

  return os;
}

}  // namespace hou

#endif
