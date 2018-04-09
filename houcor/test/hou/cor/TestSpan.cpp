// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"

#include "hou/cor/Span.hpp"

#include <sstream>

using namespace hou;
using namespace hou::prv;
using namespace testing;



namespace
{

class TestSpan : public Test {};
class TestSpanDeathTest : public TestSpan {};

class Foo
{
public:
  Foo(int value);

  int getValue() const;
  void setValue(int value);

private:
  int mValue;
};

void fillContainer(const Span<int>& buf);
int sumContainer(const Span<const int>& buf);

struct Obj2Bytes
{
  Obj2Bytes(uint8_t a, uint8_t b);
  uint8_t elements[2];
};

struct Obj3Bytes
{
  uint8_t elements[3];
};



Foo::Foo(int value)
  : mValue(value)
{}



int Foo::getValue() const
{
  return mValue;
}



void Foo::setValue(int value)
{
  mValue = value;
}



void fillContainer(const Span<int>& buf)
{
  for(auto& i : buf)
  {
    i = 9;
  }
}



int sumContainer(const Span<const int>& buf)
{
  int sum = 0;
  for(auto i : buf)
  {
    sum += i;
  }
  return sum;
}



Obj2Bytes::Obj2Bytes(uint8_t a, uint8_t b)
  : elements{a, b}
{}

}



TEST_F(TestSpan, DefaultConstructor)
{
  Span<int> s;
  EXPECT_EQ(nullptr, s.data());
  EXPECT_EQ(0u, s.size());
}



TEST_F(TestSpan, PointerAndSizeConstructor)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v.data(), v.size());
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(TestSpan, PointerAndSizeConstructorNullSize)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v.data(), size_t(0u));
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(0u, s.size());
}



TEST_F(TestSpan, PointerAndSizeConstructorNullptr)
{
  Span<int> s(nullptr, size_t(0u));
  EXPECT_EQ(nullptr, s.data());
  EXPECT_EQ(0u, s.size());
}



TEST_F(TestSpan, PointerAndSizeConstructorNullptrErrorSizeGreaterThanZero)
{
  HOU_EXPECT_PRECONDITION(Span<int> s(nullptr, 1u));
}



TEST_F(TestSpan, BeginEndPointersConstructor)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v.data(), v.data() + 3);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(TestSpanDeathTest, BeginEndPointersConstructorErrorBothNullptr)
{
  HOU_EXPECT_PRECONDITION(Span<int> s(nullptr, nullptr));
}



TEST_F(TestSpanDeathTest, BeginEndPointersConstructorFirstNullptr)
{
  std::array<int, 3u> v{1, 2, 3};
  HOU_EXPECT_PRECONDITION(Span<int> s(nullptr, v.data()));
}



TEST_F(TestSpanDeathTest, BeginEndPointersConstructorLastNullptr)
{
  std::array<int, 3u> v{1, 2, 3};
  HOU_EXPECT_PRECONDITION(Span<int> s(v.data(), nullptr));
}



TEST_F(TestSpan, ArrayConstructor)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(TestSpan, ConstArrayConstructor)
{
  const std::array<int, 3u> v{1, 2, 3};
  Span<const int> s(v);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(TestSpan, VectorConstructor)
{
  std::vector<int> v{1, 2, 3};
  Span<int> s(v);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(TestSpan, ConstVectorConstructor)
{
  const std::vector<int> v{1, 2, 3};
  Span<const int> s(v);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(TestSpan, StringConstructor)
{
  std::string v{1, 2, 3};
  Span<char> s(v);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(TestSpan, ConstStringConstructor)
{
  const std::string v{1, 2, 3};
  Span<const char> s(v);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}




TEST_F(TestSpan, ModifyElement)
{
  std::vector<int> v{1, 2, 3};
  Span<int> s(v);
  s[1] = 4;
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(4, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(TestSpanDeathTest, ElementAccessErrorIndexOutOfBounds)
{
  std::vector<int> v{1, 2, 3};
  Span<int> s(v);
  HOU_EXPECT_PRECONDITION(s[3]);
}



TEST_F(TestSpanDeathTest, ElementAccessErrorNullptr)
{
  Span<int> s;
  HOU_EXPECT_PRECONDITION(s[3]);
}



TEST_F(TestSpan, IteratorBegin)
{
  std::vector<int> v{1, 2, 3};
  Span<int> s(v);
  EXPECT_EQ(v[0], *s.begin());
  *s.begin() = 4;
  EXPECT_EQ(4, *s.begin());
  EXPECT_EQ(v[0], *s.begin());
}



TEST_F(TestSpan, IteratorBeginConstContainer)
{
  const std::vector<int> v{1, 2, 3};
  Span<const int> s(v);
  EXPECT_EQ(v[0], *s.begin());
}



TEST_F(TestSpan, IteratorEnd)
{
  std::vector<int> v{1, 2, 3};
  Span<int> s(v);
  EXPECT_EQ(s.begin() + s.size(), s.end());
}



TEST_F(TestSpan, IteratorEndConstContainer)
{
  const std::vector<int> v{1, 2, 3};
  Span<const int> s(v);
  EXPECT_EQ(s.begin() + s.size(), s.end());
}



TEST_F(TestSpan, ConstIteratorBegin)
{
  std::vector<int> v{1, 2, 3};
  Span<int> s(v);
  EXPECT_EQ(v[0], *s.cbegin());
}



TEST_F(TestSpan, ConstIteratorBeginConstContainer)
{
  const std::vector<int> v{1, 2, 3};
  Span<const int> s(v);
  EXPECT_EQ(v[0], *s.cbegin());
}



TEST_F(TestSpan, ConstIteratorEnd)
{
  std::vector<int> v{1, 2, 3};
  Span<int> s(v);
  EXPECT_EQ(s.cbegin() + s.size(), s.cend());
}



TEST_F(TestSpan, ConstIteratorEndConstContainer)
{
  const std::vector<int> v{1, 2, 3};
  Span<const int> s(v);
  EXPECT_EQ(s.cbegin() + s.size(), s.cend());
}



TEST_F(TestSpan, ReverseIteratorBegin)
{
  std::vector<int> v{1, 2, 3};
  Span<int> s(v);
  EXPECT_EQ(v[2], *s.rbegin());
}



TEST_F(TestSpan, ReverseIteratorBeginConstContainer)
{
  const std::vector<int> v{1, 2, 3};
  Span<const int> s(v);
  EXPECT_EQ(v[2], *s.rbegin());
}



TEST_F(TestSpan, ReverseIteratorEnd)
{
  std::vector<int> v{1, 2, 3};
  Span<int> s(v);
  EXPECT_EQ(s.rbegin() + s.size(), s.rend());
}



TEST_F(TestSpan, ReverseIteratorEndConstContainer)
{
  const std::vector<int> v{1, 2, 3};
  Span<const int> s(v);
  EXPECT_EQ(s.rbegin() + s.size(), s.rend());
}



TEST_F(TestSpan, ComparisonOperators)
{
  const std::array<int, 3u> v1{1, 2, 3};
  const std::array<int, 3u> v2{1, 2, 3};
  const std::array<int, 2u> v3{1, 2};

  Span<const int> s1(v1);
  Span<const int> s2(s1);
  Span<const int> s3(v2);
  Span<const int> s4(v3);

  EXPECT_TRUE(s1 == s2);
  EXPECT_FALSE(s1 == s3);
  EXPECT_FALSE(s1 == s4);
  EXPECT_FALSE(s1 != s2);
  EXPECT_TRUE(s1 != s3);
  EXPECT_TRUE(s1 != s4);
}



TEST_F(TestSpan, OutputStreamOperator)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  std::stringstream outRefStream;
  outRefStream << "{Address = " << v.data() << ", Size = 3}";
  HOU_EXPECT_OUTPUT(outRefStream.str().c_str(), s);
}



TEST_F(TestSpan, IteratorSpanAndIndexConstructor)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 1);
  EXPECT_EQ(s[1], *si);
}



TEST_F(TestSpan, IteratorConstSpanAndIndexConstructor)
{
  const std::array<int, 3u> v{1, 2, 3};
  Span<const int> s(v);
  SpanIterator<const int> si(s, 1);
  EXPECT_EQ(s[1], *si);
}



TEST_F(TestSpan, IteratorSpanAndIndexConstructorLowerIndexBound)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 0u);
  SUCCEED();
}



TEST_F(TestSpan, IteratorSpanAndIndexConstructorUpperIndexBound)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, s.size());
  SUCCEED();
}



TEST_F(TestSpanDeathTest, IteratorSpanAndIndexConstructorErrorOutOfBounds)
{
  using Iter = SpanIterator<int>;
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  HOU_EXPECT_PRECONDITION(Iter si(s, s.size() + 1u));
}



TEST_F(TestSpan, IteratorElementAccess)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> s0(s, 0);
  SpanIterator<int> s1(s, 1);
  SpanIterator<int> s2(s, 2);
  EXPECT_EQ(s[0], *s0);
  EXPECT_EQ(s[1], *s1);
  EXPECT_EQ(s[2], *s2);
}



TEST_F(TestSpan, IteratorConstSpanElementAccess)
{
  const std::array<int, 3u> v{1, 2, 3};
  Span<const int> s(v);
  SpanIterator<const int> s0(s, 0);
  SpanIterator<const int> s1(s, 1);
  SpanIterator<const int> s2(s, 2);
  EXPECT_EQ(s[0], *s0);
  EXPECT_EQ(s[1], *s1);
  EXPECT_EQ(s[2], *s2);
}



TEST_F(TestSpan, IteratorElementWriteAccess)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> s0(s, 0);
  SpanIterator<int> s1(s, 1);
  SpanIterator<int> s2(s, 2);
  *s0 = 4;
  *s1 = 5;
  *s2 = 6;
  EXPECT_EQ(4, s[0]);
  EXPECT_EQ(5, s[1]);
  EXPECT_EQ(6, s[2]);
  EXPECT_EQ(s[0], *s0);
  EXPECT_EQ(s[1], *s1);
  EXPECT_EQ(s[2], *s2);
}



TEST_F(TestSpanDeathTest, IteratorElementAccessErrorEnd)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, s.size());
  HOU_EXPECT_PRECONDITION(*si);
}



TEST_F(TestSpan, IteratorClassMemberAccess)
{
  std::array<Foo, 3u> v{1, 2, 3};
  Span<Foo> s(v);
  SpanIterator<Foo> s0(s, 0);
  SpanIterator<Foo> s1(s, 1);
  SpanIterator<Foo> s2(s, 2);
  EXPECT_EQ(1, s0->getValue());
  EXPECT_EQ(2, s1->getValue());
  EXPECT_EQ(3, s2->getValue());
}



TEST_F(TestSpan, IteratorConstSpanClassMemberAccess)
{
  const std::array<Foo, 3u> v{1, 2, 3};
  Span<const Foo> s(v);
  SpanIterator<const Foo> s0(s, 0);
  SpanIterator<const Foo> s1(s, 1);
  SpanIterator<const Foo> s2(s, 2);
  EXPECT_EQ(1, s0->getValue());
  EXPECT_EQ(2, s1->getValue());
  EXPECT_EQ(3, s2->getValue());
}



TEST_F(TestSpan, IteratorClassMemberWriteAccess)
{
  std::array<Foo, 3u> v{1, 2, 3};
  Span<Foo> s(v);
  SpanIterator<Foo> s0(s, 0);
  SpanIterator<Foo> s1(s, 1);
  SpanIterator<Foo> s2(s, 2);
  s0->setValue(4);
  s1->setValue(5);
  s2->setValue(6);
  EXPECT_EQ(4, v[0].getValue());
  EXPECT_EQ(5, v[1].getValue());
  EXPECT_EQ(6, v[2].getValue());
  EXPECT_EQ(4, s0->getValue());
  EXPECT_EQ(5, s1->getValue());
  EXPECT_EQ(6, s2->getValue());
}



TEST_F(TestSpanDeathTest, IteratorClassMemberAccessErrorEnd)
{
  std::array<Foo, 3u> v{1, 2, 3};
  Span<Foo> s(v);
  SpanIterator<Foo> si(s, s.size());
  HOU_EXPECT_PRECONDITION(si->getValue());
}



TEST_F(TestSpan, IteratorAssignmentSum)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 0);
  si += 2;
  EXPECT_EQ(s[2], *si);
  si += 1;
}



TEST_F(TestSpanDeathTest, IteratorAssignmentSumErrorOverflow)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 0);
  HOU_EXPECT_PRECONDITION(si += 4);
}



TEST_F(TestSpan, IteratorPreIncrement)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 0);
  EXPECT_EQ(s[1], *++si);
  EXPECT_EQ(s[2], *++si);
  ++si;
}



TEST_F(TestSpanDeathTest, IteratorPreIncrementErrorOverflow)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 0);
  ++si;
  ++si;
  ++si;
  HOU_EXPECT_PRECONDITION(++si);
}



TEST_F(TestSpan, IteratorPostIncrement)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 0);
  EXPECT_EQ(s[0], *si++);
  EXPECT_EQ(s[1], *si++);
  EXPECT_EQ(s[2], *si++);
}



TEST_F(TestSpanDeathTest, IteratorPostIncrementErrorOverflow)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 0);
  si++;
  si++;
  si++;
  HOU_EXPECT_PRECONDITION(si++);
}



TEST_F(TestSpan, IteratorPostSum)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 0);
  SpanIterator<int> siSum = si + 2;
  EXPECT_EQ(s[2], *siSum);
}



TEST_F(TestSpanDeathTest, IteratorPostSumErrorOverflow)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 0);
  HOU_EXPECT_PRECONDITION(si + 4);
}



TEST_F(TestSpan, IteratorPreSum)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 0);
  SpanIterator<int> siSum = 2 + si;
  EXPECT_EQ(s[2], *siSum);
}



TEST_F(TestSpanDeathTest, IteratorPreSumErrorOverflow)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 0);
  HOU_EXPECT_PRECONDITION(4 + si);
}



TEST_F(TestSpan, IteratorAssignmentDifference)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 3);
  si -= 2;
  EXPECT_EQ(s[1], *si);
  si -= 1;
}



TEST_F(TestSpanDeathTest, IteratorAssignmentDifferenceErrorUnderflow)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 1);
  HOU_EXPECT_PRECONDITION(si -= 2);
}



TEST_F(TestSpan, IteratorPreDecrement)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 3);
  EXPECT_EQ(s[2], *--si);
  EXPECT_EQ(s[1], *--si);
  EXPECT_EQ(s[0], *--si);
}



TEST_F(TestSpanDeathTest, IteratorPreDecrementErrorOverflow)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 3);
  --si;
  --si;
  --si;
  HOU_EXPECT_PRECONDITION(--si);
}



TEST_F(TestSpan, IteratorPostDecrement)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 3);
  si--;
  EXPECT_EQ(s[2], *si--);
  EXPECT_EQ(s[1], *si--);
  EXPECT_EQ(s[0], *si);
}



TEST_F(TestSpanDeathTest, IteratorPostDecrementErrorUnderflow)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 3);
  --si;
  --si;
  --si;
  HOU_EXPECT_PRECONDITION(si--);
}



TEST_F(TestSpan, IteratorDifference)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 3);
  SpanIterator<int> siDifference = si - 2;
  EXPECT_EQ(s[1], *siDifference);
}



TEST_F(TestSpanDeathTest, IteratorDifferenceErrorUnderflow)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 2);
  HOU_EXPECT_PRECONDITION(si - 3);
}



TEST_F(TestSpan, IteratorDifferenceWithAnotherIterator)
{
  std::array<int, 5u> v{1, 2, 3, 4, 5};
  Span<int> s(v);
  SpanIterator<int> si1(s, 1);
  SpanIterator<int> si2(s, 4);
  SpanIterator<int> si3(s, 4);
  EXPECT_EQ(3, si2 - si1);
  EXPECT_EQ(0, si3 - si2);
}



TEST_F(TestSpan, IteratorDifferenceWithAnotherIteratorErrorUnderflow)
{
  std::array<int, 5u> v{1, 2, 3, 4, 5};
  Span<int> s(v);
  SpanIterator<int> si1(s, 1);
  SpanIterator<int> si2(s, 4);
  HOU_EXPECT_PRECONDITION(si1 - si2);
}



TEST_F(TestSpan, IteratorDifferenceWithAnotherIteratorErrorDifferentSpans)
{
  std::array<int, 5u> v1{1, 2, 3, 4, 5};
  std::array<int, 5u> v2{1, 2, 3, 4, 5};
  Span<int> s1(v1);
  Span<int> s2(v2);
  SpanIterator<int> si1(s1, 1);
  SpanIterator<int> si2(s2, 4);
  HOU_EXPECT_PRECONDITION(si2 - si1);
}



TEST_F(TestSpan, IteratorElementAccessOperator)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 1);
  EXPECT_EQ(s[1], si[0]);
  EXPECT_EQ(s[2], si[1]);
}



TEST_F(TestSpan, IteratorConstSpanElementAccessOperator)
{
  const std::array<int, 3u> v{1, 2, 3};
  Span<const int> s(v);
  SpanIterator<const int> si(s, 1);
  EXPECT_EQ(s[1], si[0]);
  EXPECT_EQ(s[2], si[1]);
}



TEST_F(TestSpan, IteratorElementAccessOperatorWrite)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 1);
  si[0] = 8;
  si[1] = 9;
  EXPECT_EQ(s[1], si[0]);
  EXPECT_EQ(s[2], si[1]);
  EXPECT_EQ(8, si[0]);
  EXPECT_EQ(9, si[1]);
}



TEST_F(TestSpanDeathTest, IteratorElementAccessOperatorErrorOutOfBounds)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s(v);
  SpanIterator<int> si(s, 1);
  HOU_EXPECT_PRECONDITION(si[2]);
}



TEST_F(TestSpan, IteratorComparisonOperators)
{
  std::array<int, 3u> v{1, 2, 3};
  Span<int> s1(v);
  Span<int> s2(v);
  SpanIterator<int> si1(s1, 0);
  SpanIterator<int> si2(si1);
  SpanIterator<int> si3(s1, 1);
  SpanIterator<int> si4(s1, 2);
  SpanIterator<int> si5(s2, 0);

  EXPECT_TRUE(si1 == si2);
  EXPECT_FALSE(si1 == si3);
  EXPECT_FALSE(si1 == si4);
  EXPECT_FALSE(si1 == si5);

  EXPECT_FALSE(si1 != si2);
  EXPECT_TRUE(si1 != si3);
  EXPECT_TRUE(si1 != si4);
  EXPECT_TRUE(si1 != si5);

  EXPECT_FALSE(si1 < si2);
  EXPECT_TRUE(si1 < si3);
  EXPECT_TRUE(si1 < si4);
  EXPECT_FALSE(si3 < si1);
  EXPECT_TRUE(si3 < si4);

  EXPECT_TRUE(si1 <= si2);
  EXPECT_TRUE(si1 <= si3);
  EXPECT_TRUE(si1 <= si4);
  EXPECT_FALSE(si3 <= si1);
  EXPECT_TRUE(si3 <= si4);

  EXPECT_FALSE(si1 > si2);
  EXPECT_FALSE(si1 > si3);
  EXPECT_FALSE(si1 > si4);
  EXPECT_TRUE(si3 > si1);
  EXPECT_FALSE(si3 > si4);

  EXPECT_TRUE(si1 >= si2);
  EXPECT_FALSE(si1 >= si3);
  EXPECT_FALSE(si1 >= si4);
  EXPECT_TRUE(si3 >= si1);
  EXPECT_FALSE(si3 >= si4);
}



TEST_F(TestSpan, FunctionCallVectorImplicitConversion)
{
  std::vector<int> v{0, 0, 0};
  std::vector<int> vRef{9, 9, 9};
  fillContainer(v);
  EXPECT_EQ(vRef, v);
}



TEST_F(TestSpan, FunctionCallConstVectorImplicitConversion)
{
  const std::vector<int> v{2, 1, 3};
  EXPECT_EQ(6, sumContainer(v));
}



TEST_F(TestSpan, IsSpan)
{
  EXPECT_TRUE(isSpan<Span<int>>::value);
  EXPECT_TRUE(isSpan<Span<float>>::value);
  EXPECT_FALSE(isSpan<float>::value);
}



TEST_F(TestSpan, ReinterpretSpanLargerOutType)
{
  const std::vector<uint8_t> v8{0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  Span<const uint8_t> span8Ref(v8);
  Span<const uint16_t> span8To16 = reinterpretSpan<const uint16_t>(span8Ref);

  EXPECT_EQ(v8.size(), span8Ref.size());
  EXPECT_EQ(span8Ref.data(), reinterpret_cast<const uint8_t*>(span8To16.data()));
  EXPECT_EQ(span8Ref.size() / 2, span8To16.size());

  const std::vector<uint16_t> vRef{0x0201, 0x0403, 0x0605};
  ASSERT_EQ(vRef.size(), span8To16.size());
  for(size_t i = 0; i < vRef.size(); ++i)
  {
    EXPECT_EQ(vRef[i], span8To16[i]);
  }
}



TEST_F(TestSpan, ReinterpretSpanLargerInType)
{
  const std::vector<uint16_t> v16{0x0201, 0x0403, 0x0605};
  Span<const uint16_t> span16Ref(v16);
  Span<const uint8_t> span16To8 = reinterpretSpan<const uint8_t>(span16Ref);

  EXPECT_EQ(v16.size(), span16Ref.size());
  EXPECT_EQ(span16Ref.data(), reinterpret_cast<const uint16_t*>(span16To8.data()));
  EXPECT_EQ(span16Ref.size() * 2, span16To8.size());

  const std::vector<uint8_t> vRef{0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ASSERT_EQ(vRef.size(), span16To8.size());
  for(size_t i = 0; i < vRef.size(); ++i)
  {
    EXPECT_EQ(vRef[i], span16To8[i]);
  }
}



TEST_F(TestSpanDeathTest, ReinterpretSpanErrorIncompatibleSizes)
{
  ASSERT_EQ(2u, sizeof(Obj2Bytes));
  ASSERT_EQ(3u, sizeof(Obj3Bytes));
  const std::vector<Obj2Bytes> v{
    Obj2Bytes(1u, 2u), Obj2Bytes(3u, 4u), Obj2Bytes(5u, 6u), Obj2Bytes(7u, 8u)};
  Span<const Obj2Bytes> span2(v);
  HOU_EXPECT_PRECONDITION(reinterpretSpan<const Obj3Bytes>(span2));
}
