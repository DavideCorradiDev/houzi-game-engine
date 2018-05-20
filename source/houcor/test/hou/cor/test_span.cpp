// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/span.hpp"

#include <array>
#include <sstream>

using namespace hou;
using namespace hou::prv;
using namespace testing;



namespace
{

class test_span : public Test
{};

class test_span_death_test : public test_span
{};

class foo
{
public:
  foo(int value);

  int get_value() const;
  void set_value(int value);

private:
  int m_value;
};

void fill_container(const span<int>& buf);
int sum_container(const span<const int>& buf);

struct obj_2_bytes
{
  obj_2_bytes(uint8_t a, uint8_t b);
  uint8_t elements[2];
};

struct obj_3_bytes
{
  uint8_t elements[3];
};



foo::foo(int value)
  : m_value(value)
{}



int foo::get_value() const
{
  return m_value;
}



void foo::set_value(int value)
{
  m_value = value;
}



void fill_container(const span<int>& buf)
{
  for(auto& i : buf)
  {
    i = 9;
  }
}



int sum_container(const span<const int>& buf)
{
  int sum = 0;
  for(auto i : buf)
  {
    sum += i;
  }
  return sum;
}



obj_2_bytes::obj_2_bytes(uint8_t a, uint8_t b)
  : elements{a, b}
{}

}  // namespace



TEST_F(test_span, default_constructor)
{
  span<int> s;
  EXPECT_EQ(nullptr, s.data());
  EXPECT_EQ(0u, s.size());
}



TEST_F(test_span, pointer_and_size_constructor)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v.data(), v.size());
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(test_span, pointer_and_size_constructor_null_size)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v.data(), size_t(0u));
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(0u, s.size());
}



TEST_F(test_span, pointer_and_size_constructor_nullptr)
{
  span<int> s(nullptr, size_t(0u));
  EXPECT_EQ(nullptr, s.data());
  EXPECT_EQ(0u, s.size());
}



TEST_F(
  test_span, pointer_and_size_constructor_nullptr_error_size_greater_than_zero)
{
  EXPECT_PRECOND_ERROR(span<int> s(nullptr, 1u));
}



TEST_F(test_span, begin_end_pointers_constructor)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v.data(), v.data() + 3);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(test_span_death_test, begin_end_pointers_constructor_error_both_nullptr)
{
  EXPECT_PRECOND_ERROR(span<int> s(nullptr, nullptr));
}



TEST_F(test_span_death_test, begin_end_pointers_constructor_first_nullptr)
{
  std::array<int, 3u> v{1, 2, 3};
  EXPECT_PRECOND_ERROR(span<int> s(nullptr, v.data()));
}



TEST_F(test_span_death_test, begin_end_pointers_constructor_last_nullptr)
{
  std::array<int, 3u> v{1, 2, 3};
  EXPECT_PRECOND_ERROR(span<int> s(v.data(), nullptr));
}



TEST_F(test_span, array_constructor)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(test_span, const_array_constructor)
{
  const std::array<int, 3u> v{1, 2, 3};
  span<const int> s(v);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(test_span, vector_constructor)
{
  std::vector<int> v{1, 2, 3};
  span<int> s(v);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(test_span, const_vector_constructor)
{
  const std::vector<int> v{1, 2, 3};
  span<const int> s(v);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(test_span, string_constructor)
{
  std::string v{1, 2, 3};
  span<char> s(v);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(test_span, const_string_constructor)
{
  const std::string v{1, 2, 3};
  span<const char> s(v);
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(2, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(test_span, modify_element)
{
  std::vector<int> v{1, 2, 3};
  span<int> s(v);
  s[1] = 4;
  EXPECT_EQ(v.data(), s.data());
  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(1, s[0]);
  EXPECT_EQ(4, s[1]);
  EXPECT_EQ(3, s[2]);
}



TEST_F(test_span, element_access)
{
  std::vector<int> v{1, 2, 3};
  span<int> s(v);
  for(size_t i = 0; i < v.size(); ++i)
  {
    EXPECT_EQ(v[i], s[i]);
    EXPECT_EQ(v.at(i), s.at(i));
  }
}



TEST_F(test_span_death_test, element_access_error_index_out_of_bounds)
{
  std::vector<int> v{1, 2, 3};
  span<int> s(v);
  EXPECT_ERROR_0(s.at(3), out_of_range);
}



TEST_F(test_span_death_test, element_access_error_empty_span)
{
  span<int> s;
  EXPECT_ERROR_0(s.at(3), out_of_range);
}



TEST_F(test_span, iterator_begin)
{
  std::vector<int> v{1, 2, 3};
  span<int> s(v);
  EXPECT_EQ(v[0], *s.begin());
  *s.begin() = 4;
  EXPECT_EQ(4, *s.begin());
  EXPECT_EQ(v[0], *s.begin());
}



TEST_F(test_span, iterator_begin_const_container)
{
  const std::vector<int> v{1, 2, 3};
  span<const int> s(v);
  EXPECT_EQ(v[0], *s.begin());
}



TEST_F(test_span, iterator_end)
{
  std::vector<int> v{1, 2, 3};
  span<int> s(v);
  EXPECT_EQ(s.begin() + s.size(), s.end());
}



TEST_F(test_span, iterator_end_const_container)
{
  const std::vector<int> v{1, 2, 3};
  span<const int> s(v);
  EXPECT_EQ(s.begin() + s.size(), s.end());
}



TEST_F(test_span, const_iterator_begin)
{
  std::vector<int> v{1, 2, 3};
  span<int> s(v);
  EXPECT_EQ(v[0], *s.cbegin());
}



TEST_F(test_span, const_iterator_begin_const_container)
{
  const std::vector<int> v{1, 2, 3};
  span<const int> s(v);
  EXPECT_EQ(v[0], *s.cbegin());
}



TEST_F(test_span, const_iterator_end)
{
  std::vector<int> v{1, 2, 3};
  span<int> s(v);
  EXPECT_EQ(s.cbegin() + s.size(), s.cend());
}



TEST_F(test_span, const_iterator_end_const_container)
{
  const std::vector<int> v{1, 2, 3};
  span<const int> s(v);
  EXPECT_EQ(s.cbegin() + s.size(), s.cend());
}



TEST_F(test_span, reverse_iterator_begin)
{
  std::vector<int> v{1, 2, 3};
  span<int> s(v);
  EXPECT_EQ(v[2], *s.rbegin());
}



TEST_F(test_span, reverse_iterator_begin_const_container)
{
  const std::vector<int> v{1, 2, 3};
  span<const int> s(v);
  EXPECT_EQ(v[2], *s.rbegin());
}



TEST_F(test_span, reverse_iterator_end)
{
  std::vector<int> v{1, 2, 3};
  span<int> s(v);
  EXPECT_EQ(s.rbegin() + s.size(), s.rend());
}



TEST_F(test_span, reverse_iterator_end_const_container)
{
  const std::vector<int> v{1, 2, 3};
  span<const int> s(v);
  EXPECT_EQ(s.rbegin() + s.size(), s.rend());
}



TEST_F(test_span, comparison_operators)
{
  const std::array<int, 3u> v1{1, 2, 3};
  const std::array<int, 3u> v2{1, 2, 3};
  const std::array<int, 2u> v3{1, 2};

  span<const int> s1(v1);
  span<const int> s2(s1);
  span<const int> s3(v2);
  span<const int> s4(v3);

  EXPECT_TRUE(s1 == s2);
  EXPECT_FALSE(s1 == s3);
  EXPECT_FALSE(s1 == s4);
  EXPECT_FALSE(s1 != s2);
  EXPECT_TRUE(s1 != s3);
  EXPECT_TRUE(s1 != s4);
}



TEST_F(test_span, output_stream_operator)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  std::stringstream out_ref_stream;
  out_ref_stream << "{address = " << v.data() << ", size_type = 3}";
  EXPECT_OUTPUT(out_ref_stream.str().c_str(), s);
}



TEST_F(test_span, iterator_span_and_index_constructor)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, 1);
  EXPECT_EQ(s[1], *si);
}



TEST_F(test_span, iterator_const_span_and_index_constructor)
{
  const std::array<int, 3u> v{1, 2, 3};
  span<const int> s(v);
  span_iterator<const int> si(s, 1);
  EXPECT_EQ(s[1], *si);
}



TEST_F(test_span, iterator_span_and_index_constructor_lower_index_bound)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, 0u);
  SUCCEED();
}



TEST_F(test_span, iterator_span_and_index_constructor_upper_index_bound)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, s.size());
  SUCCEED();
}



TEST_F(test_span, iterator_element_access)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> s0(s, 0);
  span_iterator<int> s1(s, 1);
  span_iterator<int> s2(s, 2);
  EXPECT_EQ(s[0], *s0);
  EXPECT_EQ(s[1], *s1);
  EXPECT_EQ(s[2], *s2);
}



TEST_F(test_span, iterator_const_span_element_access)
{
  const std::array<int, 3u> v{1, 2, 3};
  span<const int> s(v);
  span_iterator<const int> s0(s, 0);
  span_iterator<const int> s1(s, 1);
  span_iterator<const int> s2(s, 2);
  EXPECT_EQ(s[0], *s0);
  EXPECT_EQ(s[1], *s1);
  EXPECT_EQ(s[2], *s2);
}



TEST_F(test_span, iterator_element_write_access)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> s0(s, 0);
  span_iterator<int> s1(s, 1);
  span_iterator<int> s2(s, 2);
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



TEST_F(test_span, iterator_class_member_access)
{
  std::array<foo, 3u> v{1, 2, 3};
  span<foo> s(v);
  span_iterator<foo> s0(s, 0);
  span_iterator<foo> s1(s, 1);
  span_iterator<foo> s2(s, 2);
  EXPECT_EQ(1, s0->get_value());
  EXPECT_EQ(2, s1->get_value());
  EXPECT_EQ(3, s2->get_value());
}



TEST_F(test_span, iterator_const_span_class_member_access)
{
  const std::array<foo, 3u> v{1, 2, 3};
  span<const foo> s(v);
  span_iterator<const foo> s0(s, 0);
  span_iterator<const foo> s1(s, 1);
  span_iterator<const foo> s2(s, 2);
  EXPECT_EQ(1, s0->get_value());
  EXPECT_EQ(2, s1->get_value());
  EXPECT_EQ(3, s2->get_value());
}



TEST_F(test_span, iterator_class_member_write_access)
{
  std::array<foo, 3u> v{1, 2, 3};
  span<foo> s(v);
  span_iterator<foo> s0(s, 0);
  span_iterator<foo> s1(s, 1);
  span_iterator<foo> s2(s, 2);
  s0->set_value(4);
  s1->set_value(5);
  s2->set_value(6);
  EXPECT_EQ(4, v[0].get_value());
  EXPECT_EQ(5, v[1].get_value());
  EXPECT_EQ(6, v[2].get_value());
  EXPECT_EQ(4, s0->get_value());
  EXPECT_EQ(5, s1->get_value());
  EXPECT_EQ(6, s2->get_value());
}



TEST_F(test_span, iterator_assignment_sum)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, 0);
  si += 2;
  EXPECT_EQ(s[2], *si);
  si += 1;
}



TEST_F(test_span, iterator_pre_increment)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, 0);
  EXPECT_EQ(s[1], *++si);
  EXPECT_EQ(s[2], *++si);
  ++si;
}



TEST_F(test_span, iterator_post_increment)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, 0);
  EXPECT_EQ(s[0], *si++);
  EXPECT_EQ(s[1], *si++);
  EXPECT_EQ(s[2], *si++);
}



TEST_F(test_span, iterator_post_sum)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, 0);
  span_iterator<int> si_sum = si + 2;
  EXPECT_EQ(s[2], *si_sum);
}



TEST_F(test_span, iterator_pre_sum)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, 0);
  span_iterator<int> si_sum = 2 + si;
  EXPECT_EQ(s[2], *si_sum);
}



TEST_F(test_span, iterator_assignment_difference)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, 3);
  si -= 2;
  EXPECT_EQ(s[1], *si);
  si -= 1;
}



TEST_F(test_span, iterator_pre_decrement)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, 3);
  EXPECT_EQ(s[2], *--si);
  EXPECT_EQ(s[1], *--si);
  EXPECT_EQ(s[0], *--si);
}



TEST_F(test_span, iterator_post_decrement)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, 3);
  si--;
  EXPECT_EQ(s[2], *si--);
  EXPECT_EQ(s[1], *si--);
  EXPECT_EQ(s[0], *si);
}



TEST_F(test_span, iterator_difference)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, 3);
  span_iterator<int> si_difference = si - 2;
  EXPECT_EQ(s[1], *si_difference);
}



TEST_F(test_span, iterator_difference_with_another_iterator)
{
  std::array<int, 5u> v{1, 2, 3, 4, 5};
  span<int> s(v);
  span_iterator<int> si1(s, 1);
  span_iterator<int> si2(s, 4);
  span_iterator<int> si3(s, 4);
  EXPECT_EQ(3, si2 - si1);
  EXPECT_EQ(0, si3 - si2);
}



TEST_F(test_span, iterator_element_access_operator)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, 1);
  EXPECT_EQ(s[1], si[0]);
  EXPECT_EQ(s[2], si[1]);
}



TEST_F(test_span, iterator_const_span_element_access_operator)
{
  const std::array<int, 3u> v{1, 2, 3};
  span<const int> s(v);
  span_iterator<const int> si(s, 1);
  EXPECT_EQ(s[1], si[0]);
  EXPECT_EQ(s[2], si[1]);
}



TEST_F(test_span, iterator_element_access_operator_write)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s(v);
  span_iterator<int> si(s, 1);
  si[0] = 8;
  si[1] = 9;
  EXPECT_EQ(s[1], si[0]);
  EXPECT_EQ(s[2], si[1]);
  EXPECT_EQ(8, si[0]);
  EXPECT_EQ(9, si[1]);
}



TEST_F(test_span, iterator_comparison_operators)
{
  std::array<int, 3u> v{1, 2, 3};
  span<int> s1(v);
  span<int> s2(v);
  span_iterator<int> si1(s1, 0);
  span_iterator<int> si2(si1);
  span_iterator<int> si3(s1, 1);
  span_iterator<int> si4(s1, 2);
  span_iterator<int> si5(s2, 0);

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



TEST_F(test_span, function_call_vector_implicit_conversion)
{
  std::vector<int> v{0, 0, 0};
  std::vector<int> v_ref{9, 9, 9};
  fill_container(v);
  EXPECT_EQ(v_ref, v);
}



TEST_F(test_span, function_call_const_vector_implicit_conversion)
{
  const std::vector<int> v{2, 1, 3};
  EXPECT_EQ(6, sum_container(v));
}



TEST_F(test_span, is_span)
{
  EXPECT_TRUE(is_span<span<int>>::value);
  EXPECT_TRUE(is_span<span<float>>::value);
  EXPECT_FALSE(is_span<float>::value);
}



TEST_F(test_span, reinterpret_span_larger_out_type)
{
  const std::vector<uint8_t> v8{0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  span<const uint8_t> span8_ref(v8);
  span<const uint16_t> span8To16 = reinterpret_span<const uint16_t>(span8_ref);

  EXPECT_EQ(v8.size(), span8_ref.size());
  EXPECT_EQ(
    span8_ref.data(), reinterpret_cast<const uint8_t*>(span8To16.data()));
  EXPECT_EQ(span8_ref.size() / 2, span8To16.size());

  const std::vector<uint16_t> v_ref{0x0201, 0x0403, 0x0605};
  ASSERT_EQ(v_ref.size(), span8To16.size());
  for(size_t i = 0; i < v_ref.size(); ++i)
  {
    EXPECT_EQ(v_ref[i], span8To16[i]);
  }
}



TEST_F(test_span, reinterpret_span_larger_in_type)
{
  const std::vector<uint16_t> v16{0x0201, 0x0403, 0x0605};
  span<const uint16_t> span16_ref(v16);
  span<const uint8_t> span16To8 = reinterpret_span<const uint8_t>(span16_ref);

  EXPECT_EQ(v16.size(), span16_ref.size());
  EXPECT_EQ(
    span16_ref.data(), reinterpret_cast<const uint16_t*>(span16To8.data()));
  EXPECT_EQ(span16_ref.size() * 2, span16To8.size());

  const std::vector<uint8_t> v_ref{0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ASSERT_EQ(v_ref.size(), span16To8.size());
  for(size_t i = 0; i < v_ref.size(); ++i)
  {
    EXPECT_EQ(v_ref[i], span16To8[i]);
  }
}



TEST_F(test_span_death_test, reinterpret_span_error_incompatible_sizes)
{
  ASSERT_EQ(2u, sizeof(obj_2_bytes));
  ASSERT_EQ(3u, sizeof(obj_3_bytes));
  const std::vector<obj_2_bytes> v{obj_2_bytes(1u, 2u), obj_2_bytes(3u, 4u),
                                   obj_2_bytes(5u, 6u), obj_2_bytes(7u, 8u)};
  span<const obj_2_bytes> span2(v);
  EXPECT_PRECOND_ERROR(reinterpret_span<const obj_3_bytes>(span2));
}



TEST_F(test_span_death_test, empty_vector_constructor)
{
  std::vector<int> v;
  EXPECT_TRUE(v.empty());
  span<int> s(v);
  EXPECT_EQ(0u, s.size());
}
