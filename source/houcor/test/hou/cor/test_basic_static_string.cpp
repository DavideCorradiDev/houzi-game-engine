// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/basic_static_string.hpp"

using namespace hou;
using namespace testing;



namespace
{

template <typename CharT>
class test_basic_static_string : public Test
{};

template <typename CharT>
class test_basic_static_string_death_test
  : public test_basic_static_string<CharT>
{};

using char_types = Types<char, wchar_t, char16_t, char32_t>;

}  // namespace



TYPED_TEST_CASE(test_basic_static_string, char_types);
TYPED_TEST_CASE(test_basic_static_string_death_test, char_types);



TYPED_TEST(test_basic_static_string, default_constructor)
{
  using string4 = basic_static_string<TypeParam, 4u>;
  string4 s;

  EXPECT_TRUE(s.empty());
  EXPECT_EQ(0u, s.size());
  EXPECT_EQ(0u, s.length());
  EXPECT_EQ(4u, s.capacity());
}



TYPED_TEST(test_basic_static_string, size_constructor)
{
  using string4 = basic_static_string<TypeParam, 4u>;
  string4 s(3u, 'z');

  EXPECT_FALSE(s.empty());
  EXPECT_EQ(3u, s.size());
  EXPECT_EQ(3u, s.length());
  EXPECT_EQ(4u, s.capacity());
  for(size_t i = 0; i < s.size(); ++i)
  {
    EXPECT_EQ(static_cast<TypeParam>('z'), s[i]);
  }
}



TYPED_TEST(test_basic_static_string, czstr_constructor)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  TypeParam czstr[] = {'a', 'b', 'c'};
  string4 s(czstr);

  EXPECT_FALSE(s.empty());
  EXPECT_EQ(3u, s.size());
  EXPECT_EQ(3u, s.length());
  EXPECT_EQ(4u, s.capacity());
  HOU_EXPECT_ARRAY_EQ(czstr, s, s.size());
}



TYPED_TEST(test_basic_static_string, czstr_constructor_trim)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  TypeParam czstr[] = {'a', 'b', 'c', 'd', 'e'};
  string4 s(czstr);

  EXPECT_FALSE(s.empty());
  EXPECT_EQ(4u, s.size());
  EXPECT_EQ(4u, s.length());
  EXPECT_EQ(4u, s.capacity());
  HOU_EXPECT_ARRAY_EQ(czstr, s, s.size());
}



TYPED_TEST(test_basic_static_string, string_constructor)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  string4 s(stdstr);

  EXPECT_FALSE(s.empty());
  EXPECT_EQ(3u, s.size());
  EXPECT_EQ(3u, s.length());
  EXPECT_EQ(4u, s.capacity());
  HOU_EXPECT_ARRAY_EQ(stdstr, s, s.size());
}



TYPED_TEST(test_basic_static_string, string_constructor_trim)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c', 'd', 'e'};
  string4 s(stdstr);

  EXPECT_FALSE(s.empty());
  EXPECT_EQ(4u, s.size());
  EXPECT_EQ(4u, s.length());
  EXPECT_EQ(4u, s.capacity());
  HOU_EXPECT_ARRAY_EQ(stdstr, s, s.size());
}



TYPED_TEST(test_basic_static_string, at)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  string4 s(stdstr);

  for(size_t i = 0u; i < s.size(); ++i)
  {
    EXPECT_EQ(stdstr.at(i), s.at(i));
  }

  s.at(0) = static_cast<TypeParam>('x');
  s.at(1) = static_cast<TypeParam>('y');
  s.at(2) = static_cast<TypeParam>('z');
  EXPECT_EQ(static_cast<TypeParam>('x'), s.at(0));
  EXPECT_EQ(static_cast<TypeParam>('y'), s.at(1));
  EXPECT_EQ(static_cast<TypeParam>('z'), s.at(2));
}



TYPED_TEST(test_basic_static_string_death_test, at_error_out_of_range)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  string4 s(stdstr);

  HOU_EXPECT_PRECONDITION(s.at(4u));
  HOU_EXPECT_PRECONDITION(s.at(5u));
}



TYPED_TEST(test_basic_static_string, const_at)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  const string4 s(stdstr);

  for(size_t i = 0u; i < s.size(); ++i)
  {
    EXPECT_EQ(stdstr.at(i), s.at(i));
  }
}



TYPED_TEST(test_basic_static_string_death_test, const_at_error_out_of_range)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  const string4 s(stdstr);

  HOU_EXPECT_PRECONDITION(s.at(4u));
  HOU_EXPECT_PRECONDITION(s.at(5u));
}



TYPED_TEST(test_basic_static_string, element_access)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  string4 s(stdstr);

  for(size_t i = 0u; i < s.size(); ++i)
  {
    EXPECT_EQ(stdstr[i], s[i]);
  }

  s[0] = static_cast<TypeParam>('x');
  s[1] = static_cast<TypeParam>('y');
  s[2] = static_cast<TypeParam>('z');
  EXPECT_EQ(static_cast<TypeParam>('x'), s[0]);
  EXPECT_EQ(static_cast<TypeParam>('y'), s[1]);
  EXPECT_EQ(static_cast<TypeParam>('z'), s[2]);
}



TYPED_TEST(test_basic_static_string, const_element_access)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  const string4 s(stdstr);

  for(size_t i = 0u; i < s.size(); ++i)
  {
    EXPECT_EQ(stdstr[i], s[i]);
  }
}



TYPED_TEST(test_basic_static_string, front)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  string4 s(stdstr);

  EXPECT_EQ(stdstr.front(), s.front());
  s.front() = static_cast<TypeParam>('z');
  EXPECT_EQ(static_cast<TypeParam>('z'), s.front());
}



TYPED_TEST(test_basic_static_string, const_front)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  const string4 s(stdstr);

  EXPECT_EQ(stdstr.front(), s.front());
}



TYPED_TEST(test_basic_static_string, back)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  string4 s(stdstr);

  EXPECT_EQ(stdstr.back(), s.back());
  s.back() = static_cast<TypeParam>('z');
  EXPECT_EQ(static_cast<TypeParam>('z'), s.back());
}



TYPED_TEST(test_basic_static_string, const_back)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  const string4 s(stdstr);

  EXPECT_EQ(stdstr.back(), s.back());
}



TYPED_TEST(test_basic_static_string, data)
{
  using string4 = basic_static_string<TypeParam, 4u>;
  using traits = std::char_traits<TypeParam>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  string4 s(stdstr);

  EXPECT_EQ(*stdstr.data(), *s.data());
  EXPECT_EQ(traits::length(stdstr.data()), traits::length(s.data()));
  EXPECT_EQ(s.size(), traits::length(s.data()));

  *s.data() = static_cast<TypeParam>('z');
  EXPECT_EQ(static_cast<TypeParam>('z'), *s.data());
}



TYPED_TEST(test_basic_static_string, const_data)
{
  using string4 = basic_static_string<TypeParam, 4u>;
  using traits = std::char_traits<TypeParam>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  const string4 s(stdstr);

  EXPECT_EQ(*stdstr.data(), *s.data());
  EXPECT_EQ(traits::length(stdstr.data()), traits::length(s.data()));
  EXPECT_EQ(s.size(), traits::length(s.data()));
}



TYPED_TEST(test_basic_static_string, c_str)
{
  using string4 = basic_static_string<TypeParam, 4u>;
  using traits = std::char_traits<TypeParam>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  string4 s(stdstr);

  EXPECT_EQ(*stdstr.c_str(), *s.c_str());
  EXPECT_EQ(traits::length(stdstr.c_str()), traits::length(s.c_str()));
  EXPECT_EQ(s.size(), traits::length(s.c_str()));
  EXPECT_EQ(s.data(), s.c_str());
}



TYPED_TEST(test_basic_static_string, iterators)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  string4 s(stdstr);

  EXPECT_EQ(*stdstr.begin(), *s.begin());
  EXPECT_EQ(*stdstr.cbegin(), *s.cbegin());
  EXPECT_EQ(*stdstr.rbegin(), *s.rbegin());
  EXPECT_EQ(*stdstr.crbegin(), *s.crbegin());

  EXPECT_EQ(*stdstr.end(), *s.end());
  EXPECT_EQ(*stdstr.cend(), *s.cend());
  EXPECT_EQ(*stdstr.rend(), *s.rend());
  EXPECT_EQ(*stdstr.crend(), *s.crend());

  *s.begin() = static_cast<TypeParam>('x');
  EXPECT_EQ(static_cast<TypeParam>('x'), s.front());
  *s.rbegin() = static_cast<TypeParam>('x');
  EXPECT_EQ(static_cast<TypeParam>('x'), s.back());

  EXPECT_EQ(
    static_cast<std::ptrdiff_t>(s.size()), std::distance(s.begin(), s.end()));
  EXPECT_EQ(
    static_cast<std::ptrdiff_t>(s.size()), std::distance(s.cbegin(), s.cend()));
  EXPECT_EQ(
    static_cast<std::ptrdiff_t>(s.size()), std::distance(s.rbegin(), s.rend()));
  EXPECT_EQ(static_cast<std::ptrdiff_t>(s.size()),
    std::distance(s.crbegin(), s.crend()));
}



TYPED_TEST(test_basic_static_string, const_iterators)
{
  using string4 = basic_static_string<TypeParam, 4u>;

  std::basic_string<TypeParam> stdstr = {'a', 'b', 'c'};
  const string4 s(stdstr);

  EXPECT_EQ(*stdstr.begin(), *s.begin());
  EXPECT_EQ(*stdstr.cbegin(), *s.cbegin());
  EXPECT_EQ(*stdstr.rbegin(), *s.rbegin());
  EXPECT_EQ(*stdstr.crbegin(), *s.crbegin());

  EXPECT_EQ(*stdstr.end(), *s.end());
  EXPECT_EQ(*stdstr.cend(), *s.cend());
  EXPECT_EQ(*stdstr.rend(), *s.rend());
  EXPECT_EQ(*stdstr.crend(), *s.crend());

  EXPECT_EQ(
    static_cast<std::ptrdiff_t>(s.size()), std::distance(s.begin(), s.end()));
  EXPECT_EQ(
    static_cast<std::ptrdiff_t>(s.size()), std::distance(s.cbegin(), s.cend()));
  EXPECT_EQ(
    static_cast<std::ptrdiff_t>(s.size()), std::distance(s.rbegin(), s.rend()));
  EXPECT_EQ(static_cast<std::ptrdiff_t>(s.size()),
    std::distance(s.crbegin(), s.crend()));
}


TYPED_TEST(test_basic_static_string, cast_to_basic_string)
{
  using string4 = basic_static_string<TypeParam, 4u>;
  using stdstr = std::basic_string<TypeParam>;

  stdstr str_in = {'a', 'b', 'c'};
  string4 s(str_in);
  stdstr str_out = static_cast<stdstr>(s);

  EXPECT_EQ(str_in, str_out);
}



TYPED_TEST(test_basic_static_string, comparison)
{
  using string4 = basic_static_string<TypeParam, 4u>;
  string4 s0(3u, 'a');
  string4 s1(s0);
  string4 s2(2u, 'a');
  string4 s3(3u, 'b');

  EXPECT_TRUE(s0 == s1);
  EXPECT_FALSE(s0 == s2);
  EXPECT_FALSE(s0 == s3);

  EXPECT_FALSE(s0 != s1);
  EXPECT_TRUE(s0 != s2);
  EXPECT_TRUE(s0 != s3);
}



TYPED_TEST(test_basic_static_string, output_stream_operator)
{
  using string4 = basic_static_string<TypeParam, 4u>;
  using stdstr = std::basic_string<TypeParam>;
  using sstream = std::basic_stringstream<TypeParam>;

  stdstr str_in = {'a', 'b', 'c'};
  string4 s(str_in);

  sstream ss1;
  ss1 << str_in;
  sstream ss2;
  ss2 << s;

  EXPECT_EQ(ss1.str(), ss2.str());
}
