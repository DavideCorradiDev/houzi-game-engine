// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_BASIC_STATIC_STRING_HPP
#define HOU_COR_BASIC_STATIC_STRING_HPP

#include "hou/cor/cor_export.hpp"

#include "hou/cor/basic_static_string_fwd.hpp"
#include "hou/cor/assertions.hpp"

#include <array>
#include <cstring>



namespace hou
{

template <typename CharT, size_t N, typename Traits = std::char_traits<CharT>>
class basic_static_string final
{
public:
  using traits_type = Traits;
  using value_type = CharT;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = const reference;
  using pointer = std::add_pointer_t<reference>;
  using const_pointer = std::add_pointer_t<const_reference>;
  // The buffer contains an extra element for the null-terminating character.
  using buffer_type = std::array<value_type, N + 1u>;
  using iterator = typename buffer_type::iterator;
  using const_iterator = typename buffer_type::const_iterator;
  using reverse_iterator = typename buffer_type::reverse_iterator;
  using const_reverse_iterator = typename buffer_type::const_reverse_iterator;

public:
  basic_static_string() noexcept;
  basic_static_string(size_t count, CharT ch) noexcept;
  // Trims.
  basic_static_string(const CharT* s) noexcept;
  template <typename Allocator>
  basic_static_string(
    const std::basic_string<CharT, Traits, Allocator>& s) noexcept;

  // throws std::out_of_range.
  CharT& at(size_type pos);
  const CharT& at(size_type pos) const;
  // undefined behaviour.
  CharT& operator[](size_type pos) noexcept;
  const CharT& operator[](size_type pos) const noexcept;
  // undefined behaviour.
  CharT& front() noexcept;
  const CharT& front() const noexcept;
  CharT& back() noexcept;
  const CharT& back() const noexcept;
  CharT* data() noexcept;
  const CharT* data() const noexcept;
  const CharT* c_str() const noexcept;

  template <typename Allocator>
  operator std::basic_string<CharT, Traits, Allocator>() const;

  // undefined behaviours.
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;
  reverse_iterator rbegin() noexcept;
  const_reverse_iterator rbegin() const noexcept;
  reverse_iterator rend() noexcept;
  const_reverse_iterator rend() const noexcept;
  const_reverse_iterator crbegin() const noexcept;
  const_reverse_iterator crend() const noexcept;

  bool empty() const noexcept;
  size_t size() const noexcept;
  size_t length() const noexcept;
  size_t capacity() const noexcept;

private:
  buffer_type m_buffer;
  size_t m_size;
};

template <typename CharT, size_t N, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(
  std::basic_ostream<CharT, Traits>& os,
  const basic_static_string<CharT, N, Traits>& s);

template <typename CharT, size_t N, typename Traits>
bool operator==(const basic_static_string<CharT, N, Traits>& lhs,
  const basic_static_string<CharT, N, Traits>& rhs) noexcept;

template <typename CharT, size_t N, typename Traits>
bool operator!=(const basic_static_string<CharT, N, Traits>& lhs,
  const basic_static_string<CharT, N, Traits>& rhs) noexcept;

}  // namespace hou

#include "hou/cor/basic_static_string.inl"

#endif
