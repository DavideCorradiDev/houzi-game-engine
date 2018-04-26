// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.


namespace hou
{

template <typename T>
  Span<T>::Span()
  : mData(nullptr)
  , mSize(0u)
{}



#ifndef HOU_DOXYGEN
template <typename T>
  Span<T>::Span(pointer data, size_type size)
  : mData(data)
  , mSize(size)
{
  HOU_EXPECT((mData == nullptr && size == 0u)
    || (mData != nullptr));
}
#endif



template <typename T>
  Span<T>::Span(pointer first, pointer last)
  : Span(first, std::distance(first, last))
{
  HOU_EXPECT(first != nullptr && last != nullptr);
}



template <typename T>
template <typename Container, typename Enable>
  Span<T>::Span(const Container& c)
  : Span(c.data(), c.size())
{}



template <typename T>
template <typename Container, typename Enable>
  Span<T>::Span(Container& c)
  : Span(const_cast<typename Container::pointer>(c.data()), c.size())
{}



template <typename T>
  constexpr typename Span<T>::pointer Span<T>::data() const
{
  return mData;
}



template <typename T>
  constexpr typename Span<T>::size_type Span<T>::size() const
{
  return mSize;
}



template <typename T>
  constexpr typename Span<T>::reference Span<T>::operator[]
  (Span<T>::size_type idx) const
{
  HOU_EXPECT(mData != nullptr && idx < mSize);
  return *(mData + idx);
}



template <typename T>
  constexpr typename Span<T>::iterator Span<T>::begin() const
{
  return iterator(*this, 0u);
}



template <typename T>
  constexpr typename Span<T>::const_iterator Span<T>::cbegin() const
{
  return const_iterator(*this, 0u);
}



template <typename T>
  constexpr typename Span<T>::reverse_iterator Span<T>::rbegin() const
{
  return reverse_iterator(end());
}



template <typename T>
  constexpr typename Span<T>::const_reverse_iterator Span<T>::crbegin() const
{
  return const_reverse_iterator(cend());
}



template <typename T>
  constexpr typename Span<T>::iterator Span<T>::end() const
{
  return iterator(*this, mSize);
}



template <typename T>
  constexpr typename Span<T>::const_iterator Span<T>::cend() const
{
  return const_iterator(*this, mSize);
}



template <typename T>
  constexpr typename Span<T>::reverse_iterator Span<T>::rend() const
{
  return reverse_iterator(begin());
}



template <typename T>
  constexpr typename Span<T>::const_reverse_iterator Span<T>::crend() const
{
  return const_reverse_iterator(cbegin());
}



template <typename T>
  bool operator==(const Span<T>& lhs, const Span<T>& rhs)
{
  return lhs.data() == rhs.data() && lhs.size() == rhs.size();
}



template <typename T>
  bool operator!=(const Span<T>& lhs, const Span<T>& rhs)
{
  return !(lhs == rhs);
}



template <typename T>
  std::ostream& operator<<(std::ostream& os, const Span<T>& s)
{
  return os << "{Address = " << s.data() << ", Size = " << s.size() << "}";
}



template <typename Out, typename In>
Span<Out> reinterpretSpan(const Span<In>& in)
{
  size_t inByteCount = in.size() * sizeof(In);
  HOU_EXPECT(inByteCount % sizeof(Out) == 0);
  return Span<Out>(reinterpret_cast<typename Span<Out>::pointer>(in.data()),
    inByteCount / sizeof(Out));
}



namespace prv
{

template <typename T>
  constexpr SpanIterator<T>::SpanIterator(const Span<T>& span
  , size_type index)
  : mSpan(&span)
  , mIndex(index)
{
  HOU_EXPECT(index <= span.size());
}



template <typename T>
  constexpr typename SpanIterator<T>::reference
  SpanIterator<T>::operator*() const
{
  HOU_EXPECT_DEV(mSpan != nullptr);
  HOU_EXPECT(mIndex < mSpan->size());
  return *(mSpan->data() + mIndex);
}



template <typename T>
  constexpr typename SpanIterator<T>::pointer
  SpanIterator<T>::operator->() const
{
  HOU_EXPECT_DEV(mSpan != nullptr);
  HOU_EXPECT(mIndex < mSpan->size());
  return mSpan->data() + mIndex;
}



template <typename T>
  constexpr SpanIterator<T>& SpanIterator<T>::operator+=(difference_type rhs)
{
  HOU_EXPECT_DEV(mSpan != nullptr);
  HOU_EXPECT(mIndex + rhs <= mSpan->size());
  mIndex += rhs;
  return *this;
}



template <typename T>
  constexpr SpanIterator<T>& SpanIterator<T>::operator++()
{
  HOU_EXPECT_DEV(mSpan != nullptr);
  HOU_EXPECT(mIndex < mSpan->size());
  mIndex++;
  return *this;
}



template <typename T>
  constexpr SpanIterator<T> SpanIterator<T>::operator++(int)
{
  SpanIterator retval = *this;
  ++(*this);
  return retval;
}



template <typename T>
  constexpr SpanIterator<T>& SpanIterator<T>::operator-=(difference_type rhs)
{
  HOU_EXPECT(mIndex >= static_cast<size_type>(rhs));
  mIndex -= rhs;
  return *this;
}



template <typename T>
  constexpr SpanIterator<T>& SpanIterator<T>::operator--()
{
  HOU_EXPECT(mIndex > 0);
  mIndex--;
  return *this;
}



template <typename T>
  constexpr SpanIterator<T> SpanIterator<T>::operator--(int)
{
  SpanIterator retval = *this;
  --(*this);
  return retval;
}



template <typename T>
  constexpr typename SpanIterator<T>::reference SpanIterator<T>::operator[]
  (difference_type offset) const
{
  HOU_EXPECT_DEV(mSpan != nullptr);
  return (*mSpan)[mIndex + offset];
}

}

}
