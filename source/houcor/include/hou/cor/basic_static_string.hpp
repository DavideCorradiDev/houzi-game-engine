// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_BASIC_STATIC_STRING_HPP
#define HOU_COR_BASIC_STATIC_STRING_HPP

#include "hou/cor/cor_config.hpp"

#include "hou/cor/assertions.hpp"
#include "hou/cor/basic_static_string_fwd.hpp"

#include <array>
#include <cstring>



namespace hou
{

/** Stack allocated string.
 *
 * \tparam CharT the character type.
 *
 * \tparam N the maximum number of characters allowed in the string. The string
 * will allocate memory for N + 1 elements (the extra element is for the string
 * terminating character '\0').
 *
 * \tparam Traits the character traits.
 */
template <typename CharT, size_t N, typename Traits = std::char_traits<CharT>>
class basic_static_string final
{
public:
  /** Traits. */
  using traits_type = Traits;

  /** CharT. */
  using value_type = CharT;

  /** size_t. */
  using size_type = std::size_t;

  /** ptrdiff_t. */
  using difference_type = std::ptrdiff_t;

  /** value_type&. */
  using reference = value_type&;

  /** const value_type&. */
  using const_reference = std::add_const_t<reference>;

  /** value_type\*. */
  using pointer = std::add_pointer_t<reference>;

  /** const value_type\*. */
  using const_pointer = std::add_pointer_t<const_reference>;

  // The buffer contains an extra element for the null-terminating character.
  /** The underlying type. */
  using buffer_type = std::array<value_type, N + 1u>;

  /** RandomAccessIterator. */
  using iterator = typename buffer_type::iterator;

  /** Constant RandomAccessIterator. */
  using const_iterator = typename buffer_type::const_iterator;

  /** std::reverse_iterator<iterator>. */
  using reverse_iterator = typename buffer_type::reverse_iterator;

  /** std::reverse_iterator<const_iterator>. */
  using const_reverse_iterator = typename buffer_type::const_reverse_iterator;

public:
  /** Default constructor.
   *
   * Constructs an empty string.
   */
  basic_static_string() noexcept;

  /** Constructs the string with count copies of character ch.
   *
   * \param count the number of copies of ch.
   *
   * \param ch the character.
   */
  basic_static_string(size_t count, CharT ch) noexcept;

  /** Constructs the string with a copy of the null-terminated character string
   * pointed to by s.
   *
   * If the length of s is greater than N, only the first N characters of s
   * will be copied.
   *
   * The behaviour is undefined if s does not point at an array of at least
   * Traits::length(s) + 1 elements of CharT, including the case when s is a
   * null pointer.
   *
   * \param s the input null-terminated string.
   */
  basic_static_string(const CharT* s) noexcept;

  /** Constructs the string with a copy of the contents of s.
   *
   * If the length of s is greater than N, only the first N characters of s
   * will be copied.
   *
   * \param s the input string.
   */
  template <typename Allocator>
  basic_static_string(
    const std::basic_string<CharT, Traits, Allocator>& s) noexcept;

  /** Accesses the specified character with bounds checking.
   *
   * \param pos the position of the requested character.
   *
   * \throws std::out_of_range on invalid access.
   *
   * \return a reference to the character at the specified location pos.
   */
  CharT& at(size_type pos);

  /** Accesses the specified character with bounds checking.
   *
   * \param pos the position of the requested character.
   *
   * \throws std::out_of_range on invalid access.
   *
   * \return a reference to the character at the specified location pos.
   */
  const CharT& at(size_type pos) const;

  /** Accesses the specified character without bounds checking.
   *
   * The behaviour is undefined if pos > size().
   *
   * \param pos the position of the requested character.
   *
   * \return a reference to the character at the specified location pos.
   */
  CharT& operator[](size_type pos) noexcept;

  /** Accesses the specified character without bounds checking.
   *
   * The behaviour is undefined if pos > size().
   *
   * \param pos the position of the requested character.
   *
   * \return a reference to the character at the specified location pos.
   */
  const CharT& operator[](size_type pos) const noexcept;

  /** Accesses the first character.
   *
   * The behaviour is undefined if empty() == true.
   *
   * \return a reference to the first character.
   */
  CharT& front() noexcept;

  /** Accesses the first character.
   *
   * The behaviour is undefined if empty() == true.
   *
   * \return a reference to the first character.
   */
  const CharT& front() const noexcept;

  /** Accesses the last character.
   *
   * The behaviour is undefined if empty() == true.
   *
   * \return a reference to the last character.
   */
  CharT& back() noexcept;

  /** Accesses the last character.
   *
   * The behaviour is undefined if empty() == true.
   *
   * \return a reference to the last character.
   */
  const CharT& back() const noexcept;

  /** Returns a pointer to the first character.
   *
   * If empty() == true the return pointer should not be dereferenced.
   *
   * \return a pointer to the first character.
   */
  CharT* data() noexcept;

  /** Returns a pointer to the first character.
   *
   * If empty() == true the return pointer should not be dereferenced.
   *
   * \return a pointer to the first character.
   */
  const CharT* data() const noexcept;

  /** Returns a C character array version of the string.
   *
   * If empty() == true the return pointer should not be dereferenced.
   *
   * \return a C character array version of the string.
   */
  const CharT* c_str() const noexcept;

  /** Return a std::basic_string version of the string.
   *
   * \throws std::bad_alloc.
   *
   * \return a std::basic_string version of the string.
   */
  template <typename Allocator>
  operator std::basic_string<CharT, Traits, Allocator>() const;

  /** Returns an iterator to the beginning.
   * 
   * If empty() == true the return iterator should not be used.
   *
   * \return an iterator to the beginning.
   */
  iterator begin() noexcept;

  /** Returns an iterator to the beginning.
   * 
   * If empty() == true the return iterator should not be used.
   *
   * \return an iterator to the beginning.
   */
  const_iterator begin() const noexcept;

  /** Returns an iterator to the end.
   * 
   * If empty() == true the return iterator should not be used.
   *
   * \return an iterator to the end.
   */
  iterator end() noexcept;

  /** Returns an iterator to the end.
   * 
   * If empty() == true the return iterator should not be used.
   *
   * \return an iterator to the end.
   */
  const_iterator end() const noexcept;

  /** Returns an iterator to the beginning.
   * 
   * If empty() == true the return iterator should not be used.
   *
   * \return an iterator to the beginning.
   */
  const_iterator cbegin() const noexcept;

  /** Returns an iterator to the end.
   * 
   * If empty() == true the return iterator should not be used.
   *
   * \return an iterator to the end.
   */
  const_iterator cend() const noexcept;

  /** Returns a reverse iterator to the beginning.
   * 
   * If empty() == true the return iterator should not be used.
   *
   * \return a reverse iterator to the beginning.
   */
  reverse_iterator rbegin() noexcept;

  /** Returns a reverse iterator to the beginning.
   * 
   * If empty() == true the return iterator should not be used.
   *
   * \return a reverse iterator to the beginning.
   */
  const_reverse_iterator rbegin() const noexcept;

  /** Returns a reverse iterator to the end.
   * 
   * If empty() == true the return iterator should not be used.
   *
   * \return a reverse iterator to the end.
   */
  reverse_iterator rend() noexcept;

  /** Returns a reverse iterator to the beginning.
   * 
   * If empty() == true the return iterator should not be used.
   *
   * \return a reverse iterator to the beginning.
   */
  const_reverse_iterator rend() const noexcept;

  /** Returns a reverse iterator to the end.
   * 
   * If empty() == true the return iterator should not be used.
   *
   * \return a reverse iterator to the end.
   */
  const_reverse_iterator crbegin() const noexcept;

  /** Returns a reverse iterator to the end.
   * 
   * If empty() == true the return iterator should not be used.
   *
   * \return a reverse iterator to the end.
   */
  const_reverse_iterator crend() const noexcept;

  /** Checks whether the string is empty.
   *
   * \return true if the string is empty.
   */
  bool empty() const noexcept;

  /** Returns the number of characters.
   *
   * \return the number of characters.
   */
  size_t size() const noexcept;

  /** Returns the number of characters.
   *
   * \return the number of characters.
   */
  size_t length() const noexcept;

  /** Returns the maximum number of characters that can be held.
   *
   * This is equal to N.
   *
   * \return the maximum number of characters that can be held.
   */
  size_t capacity() const noexcept;

private:
  buffer_type m_buffer;
  size_t m_size;
};

/** Output stream operator.
 *
 * \tparam CharT the character type.
 *
 * \tparam N the maximum number of characters allowed in the string.
 *
 * \tparam Traits the character traits.
 *
 * \param os the output stream.
 *
 * \param s the basic_static_string.
 *
 * \return a reference to os.
 */
template <typename CharT, size_t N, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(
  std::basic_ostream<CharT, Traits>& os,
  const basic_static_string<CharT, N, Traits>& s);

/** Checks if two basic_static_string objects are equal.
 *
 * \tparam CharT the character type.
 *
 * \tparam N the maximum number of characters allowed in the string.
 *
 * \tparam Traits the character traits.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand
 *
 * \return the result of the check.
 */
template <typename CharT, size_t N, typename Traits>
bool operator==(const basic_static_string<CharT, N, Traits>& lhs,
  const basic_static_string<CharT, N, Traits>& rhs) noexcept;

/** Checks if two basic_static_string objects are not equal.
 *
 * \tparam CharT the character type.
 *
 * \tparam N the maximum number of characters allowed in the string.
 *
 * \tparam Traits the character traits.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand
 *
 * \return the result of the check.
 */
template <typename CharT, size_t N, typename Traits>
bool operator!=(const basic_static_string<CharT, N, Traits>& lhs,
  const basic_static_string<CharT, N, Traits>& rhs) noexcept;

}  // namespace hou

#include "hou/cor/basic_static_string.inl"

#endif
