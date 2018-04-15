// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_SPAN_HPP
#define HOU_COR_SPAN_HPP

#include "hou/cor/CorExport.hpp"

#include "hou/cor/Error.hpp"
#include "hou/cor/TemplateUtils.hpp"

#include <iostream>



namespace hou
{

template <typename T> struct isSpan;

namespace prv
{

template <typename T> class SpanIterator;

}



/** Lightweight proxy for any contiguous container which can be represented by
 *  a pointer and a size.
 *
 *  A Span does not contain any elements, it just references elements placed
 *  elsewhere in memory.
 *  The user must ensure that a Span always points at a valid memory block.
 *
 *  Note that a Span has different semantics than containers, as they don't
 *  hold any elements but just a reference to a memory address.
 *
 *  \tparam T the value type. For constant containers it should be
 *  const value_type.
 */
template <typename T>
  class Span
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
  using iterator = prv::SpanIterator<T>;
  /** The const iterator type. */
  using const_iterator = iterator;
  /** The reverse iterator type. */
  using reverse_iterator = std::reverse_iterator<iterator>;
  /** The const reverse iterator type. */
  using const_reverse_iterator = reverse_iterator;

public:
  /** Builds a span pointing to no data.
   */
  Span();

  /** Builds a span from the given pointer and size.
   *
   *  Throws if data is nullptr and size is not 0.
   *
   *  \param data the pointer to the beginning of the data buffer.
   *  \param size the size of the data buffer.
   */
  Span(pointer data, size_type size);

  /** Builds a span from the given pointer to begin and end of the data buffer.
   *
   *  Throws if first or last is nullptr.
   *
   *  \param first a pointer to the begin of the data buffer.
   *  \param last a pointer to the end of the data buffer.
   */
  Span(pointer first, pointer last);

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
    && !isSpan<Container>::value
    && std::is_convertible<typename Container::pointer, pointer>::value
    && isContiguousContainer<Container>::value>>
    Span(const Container& c);

  /** Builds a span from a container using contiguous memory.
   *
   *  \tparam Container the container type.
   *  \tparam Enable enabling parameter (it should be left to the default value).
   *  \param c the container.
   */
  template <typename Container
    , typename Enable = std::enable_if_t
    <!std::is_const<Container>::value
    && !isSpan<Container>::value
    && std::is_convertible<typename Container::pointer, pointer>::value
    && isContiguousContainer<Container>::value>>
    Span(Container& c);

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
  size_type mSize;
};

/** Checks if two Span objects are equal.
 *
 *  Two spans are equal if the memory adress the point at and the size is the
 *  same, the check does not compare the elements in the buffer.
 *
 *  \tparam T the value type of the Span.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two Span objects are equal.
 */
template <typename T>
  bool operator==(const Span<T>& lhs, const Span<T>& rhs);

/** Checks if two Span objects are not equal.
 *
 *  Two spans are equal if the memory adress the point at and the size is the
 *  same, the check does not compare the elements in the buffer.
 *
 *  \tparam T the value type of the Span.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two Span objects are not equal.
 */
template <typename T>
  bool operator!=(const Span<T>& lhs, const Span<T>& rhs);

/** Outsputs a Span object into a stream.
 *
 *  \tparam T the value type of the Span.
 *  \param os the output stream.
 *  \param s the Span.
 *  \return a reference to os.
 */
template <typename T>
  std::ostream& operator<<(std::ostream& os, const Span<T>& s);

/** Reinterprets the Span as a Span with a different underlying type.
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
Span<Out> reinterpretSpan(const Span<In>& in);



namespace prv
{

template <class T>
  struct isSpanHelper : std::false_type {};

template <class T>
  struct isSpanHelper<Span<T>> : std::true_type {};

}

/** Template checker to determine if the type is a Span.
 *
 *  \tparam T the type to be checked.
 */
template <class T>
  struct isSpan : public prv::isSpanHelper<std::remove_cv_t<T>> {};



namespace prv
{

template <typename T>
  class SpanIterator
{
  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = typename Span<T>::value_type;
    using size_type = typename Span<T>::size_type;
    using difference_type = typename Span<T>::difference_type;
    using reference = typename Span<T>::reference;
    using pointer = typename Span<T>::pointer;

  public:
    constexpr SpanIterator(const Span<T>& span, size_type index);

    constexpr reference operator*() const;
    constexpr pointer operator->() const;
    constexpr SpanIterator& operator+=(difference_type rhs);
    constexpr SpanIterator& operator++();
    constexpr SpanIterator operator++(int);
    constexpr SpanIterator& operator-=(difference_type rhs);
    constexpr SpanIterator& operator--();
    constexpr SpanIterator operator--(int);
    constexpr reference operator[](difference_type offset) const;

    friend constexpr SpanIterator operator+(SpanIterator lhs
      , difference_type rhs)
    {
      return lhs += rhs;
    }

    friend constexpr SpanIterator operator+(difference_type lhs
      , SpanIterator rhs)
    {
      return rhs += lhs;
    }

    friend constexpr SpanIterator operator-(SpanIterator lhs
      , difference_type rhs)
    {
      return lhs -= rhs;
    }

    friend constexpr difference_type operator-(const SpanIterator& lhs
      , const SpanIterator& rhs)
    {
      HOU_EXPECT(lhs.mSpan == rhs.mSpan);
      HOU_EXPECT(lhs.mIndex >= rhs.mIndex);
      return lhs.mIndex - rhs.mIndex;
    }

    friend constexpr bool operator==(const SpanIterator& lhs
      , const SpanIterator& rhs)
    {
      return lhs.mSpan == rhs.mSpan && lhs.mIndex == rhs.mIndex;
    }

    friend constexpr bool operator!=(const SpanIterator& lhs
      , const SpanIterator& rhs)
    {
      return !(lhs == rhs);
    }

    friend constexpr bool operator<(const SpanIterator& lhs
      , const SpanIterator& rhs)
    {
      HOU_EXPECT(lhs.mSpan == rhs.mSpan);
      return lhs.mIndex < rhs.mIndex;
    }

    friend constexpr bool operator<=(const SpanIterator& lhs
      , const SpanIterator& rhs)
    {
      HOU_EXPECT(lhs.mSpan == rhs.mSpan);
      return lhs.mIndex <= rhs.mIndex;
    }

    friend constexpr bool operator>(const SpanIterator& lhs
      , const SpanIterator& rhs)
    {
      HOU_EXPECT(lhs.mSpan == rhs.mSpan);
      return lhs.mIndex > rhs.mIndex;
    }

    friend constexpr bool operator>=(const SpanIterator& lhs
      , const SpanIterator& rhs)
    {
      HOU_EXPECT(lhs.mSpan == rhs.mSpan);
      return lhs.mIndex >= rhs.mIndex;
    }

  private:
    const Span<T>* mSpan;
    size_type mIndex;
};

}

}



#include "hou/cor/Span.inl"

#endif

