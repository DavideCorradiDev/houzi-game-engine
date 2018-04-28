// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_SPAN_HPP
#define HOU_COR_SPAN_HPP

#include "hou/cor/cor_export.hpp"

#include "hou/cor/error.hpp"
#include "hou/cor/template_utils.hpp"

#include <iostream>



namespace hou
{

template <typename T> struct is_span;

namespace prv
{

template <typename T> class span_iterator;

}



/** Lightweight proxy for any contiguous container which can be represented by
 *  a pointer and a size.
 *
 *  A span does not contain any elements, it just references elements placed
 *  elsewhere in memory.
 *  The user must ensure that a span always points at a valid memory block.
 *
 *  Note that a span has different semantics than containers, as they don't
 *  hold any elements but just a reference to a memory address.
 *
 *  \tparam T the value type. For constant containers it should be
 *  const value_type.
 */
template <typename T>
  class span
{
public:
  /** The value type. */
  using value_type = T;
  /** The size type. */
  using size_type = std::size_t;
  /** The index difference type. */
  using difference_type = std::ptrdiff_t;
  /** The reference type. */
  using reference = value_type&;
  /** The const reference type. */
  using const_reference = const reference;
  /** The pointer type. */
  using pointer = std::add_pointer_t<reference>;
  /** The const_pointer type. */
  using const_pointer = std::add_pointer_t<const_reference>;
  /** The iterator type. */
  using iterator = prv::span_iterator<T>;
  /** The const iterator type. */
  using const_iterator = iterator;
  /** The reverse iterator type. */
  using reverse_iterator = std::reverse_iterator<iterator>;
  /** The const reverse iterator type. */
  using const_reverse_iterator = reverse_iterator;

public:
  /** Builds a span pointing to no data.
   */
  span();

  /** Builds a span from the given pointer and size.
   *
   *  Throws if data is nullptr and size is not 0.
   *
   *  \param data the pointer to the beginning of the data buffer.
   *  \param size the size of the data buffer.
   */
  span(pointer data, size_type size);

  /** Builds a span from the given pointer to begin and end of the data buffer.
   *
   *  Throws if first or last is nullptr.
   *
   *  \param first a pointer to the begin of the data buffer.
   *  \param last a pointer to the end of the data buffer.
   */
  span(pointer first, pointer last);

  /** Builds a span from a constant container using contiguous memory.
   *
   *  \tparam Container the container type.
   *  \tparam Enable enabling parameter (it should be left to the default value).
   *  \param c the container.
   */
  template <typename Container
    , typename Enable = std::enable_if_t
    <std::is_const<T>::value
    && !std::is_const<Container>::value
    && !is_span<Container>::value
    && std::is_convertible<typename Container::pointer, pointer>::value
    && is_contiguous_container<Container>::value>>
    span(const Container& c);

  /** Builds a span from a container using contiguous memory.
   *
   *  \tparam Container the container type.
   *  \tparam Enable enabling parameter (it should be left to the default value).
   *  \param c the container.
   */
  template <typename Container
    , typename Enable = std::enable_if_t
    <!std::is_const<Container>::value
    && !is_span<Container>::value
    && std::is_convertible<typename Container::pointer, pointer>::value
    && is_contiguous_container<Container>::value>>
    span(Container& c);

  /** Gets a pointer to the begin of the data buffer.
   *
   *  \return a pointer to the begin of the data buffer.
   */
  constexpr pointer data() const;

  /** Gets the number of elements in the buffer.
   *
   *  \return the number of elements in the buffer.
   */
  constexpr size_type size() const;

  /** Access an element in the buffer.
   *
   *  \param idx the index of the element.
   *  \return a reference to the requested element.
   */
  constexpr reference operator[](size_type idx) const;

  /** Gets an iterator to the first element of the buffer.
   *
   *  \return an iterator to the first element of the buffer.
   */
  constexpr iterator begin() const;

  /** Gets a const iterator to the first element of the buffer.
   *
   *  \return const iterator to the first element of the buffer.
   */
  constexpr const_iterator cbegin() const;

  /** Gets a reverse iterator to the first element of the buffer.
   *
   *  \return reverse iterator to the first element of the buffer.
   */
  constexpr reverse_iterator rbegin() const;

  /** Gets a constant reverse iterator to the first element of the buffer.
   *
   *  \return constant reverse iterator to the first element of the buffer.
   */
  constexpr const_reverse_iterator crbegin() const;

  /** Gets an iterator to the position after the last element of the buffer.
   *
   *  \return an iterator to the position after the last element of the buffer.
   */
  constexpr iterator end() const;

  /** Gets a constant iterator to the position after the last element of the buffer.
   *
   *  \return a constant iterator to the position after the last element of the buffer.
   */
  constexpr const_iterator cend() const;

  /** Gets a reverse iterator to the position after the last element of the buffer.
   *
   *  \return a reverse iterator to the position after the last element of the buffer.
   */
  constexpr reverse_iterator rend() const;

  /** Gets a constant reverse iterator to the position after the last element of the buffer.
   *
   *  \return a constant reverse iterator to the position after the last element of the buffer.
   */
  constexpr const_reverse_iterator crend() const;

private:
  pointer mData;
  size_type m_size;
};

/** Checks if two span objects are equal.
 *
 *  Two spans are equal if the memory adress the point at and the size is the
 *  same, the check does not compare the elements in the buffer.
 *
 *  \tparam T the value type of the span.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two span objects are equal.
 */
template <typename T>
  bool operator==(const span<T>& lhs, const span<T>& rhs);

/** Checks if two span objects are not equal.
 *
 *  Two spans are equal if the memory adress the point at and the size is the
 *  same, the check does not compare the elements in the buffer.
 *
 *  \tparam T the value type of the span.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two span objects are not equal.
 */
template <typename T>
  bool operator!=(const span<T>& lhs, const span<T>& rhs);

/** Outsputs a span object into a ph_stream.
 *
 *  \tparam T the value type of the span.
 *  \param os the output ph_stream.
 *  \param s the span.
 *  \return a reference to os.
 */
template <typename T>
  std::ostream& operator<<(std::ostream& os, const span<T>& s);

/** Reinterprets the span as a span with a different underlying type.
 *
 *  Throws if the size of the input span in bytes is not divisible by the size
 *  of Out.
 *
 *  \tparam Out the output type.
 *  \tparam In the input type.
 *  \param in the input span.
 *  \return the input span reinterpreted with Out as underlying type.
 */
template <typename Out, typename In>
span<Out> reinterpret_span(const span<In>& in);



namespace prv
{

template <class T>
  struct is_span_helper : std::false_type {};

template <class T>
  struct is_span_helper<span<T>> : std::true_type {};

}

/** Template checker to determine if the type is a span.
 *
 *  \tparam T the type to be checked.
 */
template <class T>
  struct is_span : public prv::is_span_helper<std::remove_cv_t<T>> {};



namespace prv
{

template <typename T>
  class span_iterator
{
  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = typename span<T>::value_type;
    using size_type = typename span<T>::size_type;
    using difference_type = typename span<T>::difference_type;
    using reference = typename span<T>::reference;
    using pointer = typename span<T>::pointer;

  public:
    constexpr span_iterator(const span<T>& span, size_type index);

    constexpr reference operator*() const;
    constexpr pointer operator->() const;
    constexpr span_iterator& operator+=(difference_type rhs);
    constexpr span_iterator& operator++();
    constexpr span_iterator operator++(int);
    constexpr span_iterator& operator-=(difference_type rhs);
    constexpr span_iterator& operator--();
    constexpr span_iterator operator--(int);
    constexpr reference operator[](difference_type offset) const;

    friend constexpr span_iterator operator+(span_iterator lhs
      , difference_type rhs)
    {
      return lhs += rhs;
    }

    friend constexpr span_iterator operator+(difference_type lhs
      , span_iterator rhs)
    {
      return rhs += lhs;
    }

    friend constexpr span_iterator operator-(span_iterator lhs
      , difference_type rhs)
    {
      return lhs -= rhs;
    }

    friend constexpr difference_type operator-(const span_iterator& lhs
      , const span_iterator& rhs)
    {
      HOU_EXPECT(lhs.m_span == rhs.m_span);
      HOU_EXPECT(lhs.m_index >= rhs.m_index);
      return lhs.m_index - rhs.m_index;
    }

    friend constexpr bool operator==(const span_iterator& lhs
      , const span_iterator& rhs)
    {
      return lhs.m_span == rhs.m_span && lhs.m_index == rhs.m_index;
    }

    friend constexpr bool operator!=(const span_iterator& lhs
      , const span_iterator& rhs)
    {
      return !(lhs == rhs);
    }

    friend constexpr bool operator<(const span_iterator& lhs
      , const span_iterator& rhs)
    {
      HOU_EXPECT(lhs.m_span == rhs.m_span);
      return lhs.m_index < rhs.m_index;
    }

    friend constexpr bool operator<=(const span_iterator& lhs
      , const span_iterator& rhs)
    {
      HOU_EXPECT(lhs.m_span == rhs.m_span);
      return lhs.m_index <= rhs.m_index;
    }

    friend constexpr bool operator>(const span_iterator& lhs
      , const span_iterator& rhs)
    {
      HOU_EXPECT(lhs.m_span == rhs.m_span);
      return lhs.m_index > rhs.m_index;
    }

    friend constexpr bool operator>=(const span_iterator& lhs
      , const span_iterator& rhs)
    {
      HOU_EXPECT(lhs.m_span == rhs.m_span);
      return lhs.m_index >= rhs.m_index;
    }

  private:
    const span<T>* m_span;
    size_type m_index;
};

}

}



#include "hou/cor/span.inl"

#endif

