// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/not_null.hpp"

#include <memory>

using namespace hou;
using namespace testing;



namespace
{

class foo
{
public:
  foo(int value);
  int get() const;
  void set(int value);

private:
  int m_int;
};



foo::foo(int value)
  : m_int(value)
{}



int foo::get() const
{
  return m_int;
}



void foo::set(int value)
{
  m_int = value;
}



template <typename PtrType>
class test_not_null_smart_pointer : public Test
{
public:
  static PtrType make_ptr(const typename PtrType::element_type& value);
};



template <typename PtrType>
PtrType test_not_null_smart_pointer<PtrType>::make_ptr(
  const typename PtrType::element_type& value)
{
  return PtrType(new typename PtrType::element_type(value));
}



template <typename PtrType>
using test_not_null_copyable_smart_pointer = test_not_null_smart_pointer<PtrType>;
using copyable_smart_pointer_types = Types<std::shared_ptr<int>>;
TYPED_TEST_CASE(test_not_null_copyable_smart_pointer, copyable_smart_pointer_types);

template <typename PtrType>
using test_not_null_any_smart_pointer = test_not_null_smart_pointer<PtrType>;
using any_smart_pointer_types = Types<std::unique_ptr<int>, std::shared_ptr<int>>;
TYPED_TEST_CASE(test_not_null_any_smart_pointer, any_smart_pointer_types);

template <typename PtrType>
using test_not_null_any_smart_pointer_to_class = test_not_null_smart_pointer<PtrType>;
using any_smart_pointer_to_class_types
  = Types<std::unique_ptr<foo>, std::shared_ptr<foo>>;
TYPED_TEST_CASE(test_not_null_any_smart_pointer_to_class, any_smart_pointer_to_class_types);



TYPED_TEST(test_not_null_copyable_smart_pointer, pointer_copy_constructor)
{
  typename TypeParam::element_type v(2);
  TypeParam p = TestFixture::make_ptr(v);
  not_null<TypeParam> nnp(p);
  EXPECT_EQ(*p, *nnp);
}



TYPED_TEST(test_not_null_any_smart_pointer, pointer_move_constructor)
{
  typename TypeParam::element_type v(2);
  TypeParam p = TestFixture::make_ptr(v);
  not_null<TypeParam> nnp(std::move(p));
  EXPECT_EQ(v, *nnp);
}



TYPED_TEST(test_not_null_copyable_smart_pointer, nullptr_copy_constructor)
{
  TypeParam p = nullptr;
  EXPECT_PRECOND_ERROR(not_null<TypeParam> nnp(p));
}



TYPED_TEST(test_not_null_any_smart_pointer, nullptr_move_constructor)
{
  TypeParam p = nullptr;
  EXPECT_PRECOND_ERROR(not_null<TypeParam> nnp(std::move(p)));
}



TYPED_TEST(test_not_null_copyable_smart_pointer, copy_constructor)
{
  not_null<TypeParam> nnp1(
    TestFixture::make_ptr(typename TypeParam::element_type(2)));
  not_null<TypeParam> nnp2(nnp1);
  EXPECT_EQ(*nnp1, *nnp2);
}



TYPED_TEST(test_not_null_any_smart_pointer, move_constructor)
{
  typename TypeParam::element_type v(2);
  not_null<TypeParam> nnp1(TestFixture::make_ptr(v));
  not_null<TypeParam> nnp2(std::move(nnp1));
  EXPECT_EQ(v, *nnp2);
}



TYPED_TEST(test_not_null_copyable_smart_pointer, pointer_copy_assignment)
{
  typename TypeParam::element_type v1(2);
  TypeParam p1 = TestFixture::make_ptr(v1);

  typename TypeParam::element_type v2(3);
  TypeParam p2 = TestFixture::make_ptr(v2);

  not_null<TypeParam> nnp(p1);
  nnp = p2;

  EXPECT_EQ(*p2, *nnp);
}



TYPED_TEST(test_not_null_any_smart_pointer, pointer_move_assignment)
{
  typename TypeParam::element_type v1(2);
  TypeParam p1 = TestFixture::make_ptr(v1);

  typename TypeParam::element_type v2(3);
  TypeParam p2 = TestFixture::make_ptr(v2);

  not_null<TypeParam> nnp(std::move(p1));
  nnp = std::move(p2);

  EXPECT_EQ(v2, *nnp);
}



TYPED_TEST(test_not_null_copyable_smart_pointer, nullptr_copy_assignment)
{
  typename TypeParam::element_type v1(2);
  TypeParam p1 = TestFixture::make_ptr(v1);
  TypeParam p2 = nullptr;
  not_null<TypeParam> nnp(p1);
  EXPECT_PRECOND_ERROR(nnp = p2);
}



TYPED_TEST(test_not_null_any_smart_pointer, nullptr_move_assignment)
{
  typename TypeParam::element_type v1(2);
  TypeParam p1 = TestFixture::make_ptr(v1);
  TypeParam p2 = nullptr;
  not_null<TypeParam> nnp(std::move(p1));
  EXPECT_PRECOND_ERROR(nnp = std::move(p2));
}



TYPED_TEST(test_not_null_copyable_smart_pointer, copy_assignment)
{
  not_null<TypeParam> nnp1(
    TestFixture::make_ptr(typename TypeParam::element_type(2)));
  not_null<TypeParam> nnp2(
    TestFixture::make_ptr(typename TypeParam::element_type(3)));
  not_null<TypeParam> nnp3(nnp1);
  nnp3 = nnp2;
  EXPECT_EQ(*nnp2, *nnp3);
}



TYPED_TEST(test_not_null_any_smart_pointer, move_assignment)
{
  typename TypeParam::element_type v1(2);
  typename TypeParam::element_type v2(2);
  not_null<TypeParam> nnp1(TestFixture::make_ptr(v1));
  not_null<TypeParam> nnp2(TestFixture::make_ptr(v2));
  not_null<TypeParam> nnp3(std::move(nnp1));
  nnp3 = std::move(nnp2);
  EXPECT_EQ(v2, *nnp3);
}



TYPED_TEST(test_not_null_any_smart_pointer, move_content)
{
  typename TypeParam::element_type v(2);
  not_null<TypeParam> nnp(TestFixture::make_ptr(v));
  TypeParam p = move_content(std::move(nnp));
  EXPECT_EQ(v, *p);
}



TYPED_TEST(test_not_null_any_smart_pointer, get)
{
  typename TypeParam::element_type v(2);
  TypeParam p = TestFixture::make_ptr(v);
  auto ptr = p.get();
  not_null<TypeParam> nnp(std::move(p));
  EXPECT_EQ(ptr, nnp.get().get());
}



TYPED_TEST(test_not_null_copyable_smart_pointer, get)
{
  typename TypeParam::element_type v(2);
  TypeParam p = TestFixture::make_ptr(v);
  not_null<TypeParam> nnp(p);
  EXPECT_EQ(p, nnp.get());
}



TYPED_TEST(test_not_null_any_smart_pointer, get_error_when_null)
{
  typename TypeParam::element_type v(2);
  not_null<TypeParam> nnp1(TestFixture::make_ptr(v));
  not_null<TypeParam> nnp2(std::move(nnp1));
  EXPECT_POSTCOND_ERROR(nnp1.get());
}



TYPED_TEST(test_not_null_any_smart_pointer, dereferencing)
{
  typename TypeParam::element_type v1(2);
  typename TypeParam::element_type v2(3);
  not_null<TypeParam> nnp(TestFixture::make_ptr(v1));
  EXPECT_EQ(v1, *nnp);
  *nnp = v2;
  EXPECT_EQ(v2, *nnp);
}



TYPED_TEST(test_not_null_any_smart_pointer, dereferencing_error_when_null)
{
  typename TypeParam::element_type v(2);
  not_null<TypeParam> nnp1(TestFixture::make_ptr(v));
  not_null<TypeParam> nnp2(std::move(nnp1));
  EXPECT_POSTCOND_ERROR(*nnp1);
}



TYPED_TEST(test_not_null_any_smart_pointer_to_class, dereferencing_member)
{
  typename TypeParam::element_type v(2);
  TypeParam p = TestFixture::make_ptr(v);
  auto ptr = p.get();
  not_null<TypeParam> nnp(std::move(p));
  EXPECT_EQ(ptr->get(), nnp->get());
  ptr->set(5);
  EXPECT_EQ(ptr->get(), nnp->get());
  nnp->set(9);
  EXPECT_EQ(ptr->get(), nnp->get());
}



TYPED_TEST(test_not_null_any_smart_pointer_to_class, dereferencing_member_error_when_null)
{
  typename TypeParam::element_type v(2);
  not_null<TypeParam> nnp1(TestFixture::make_ptr(v));
  not_null<TypeParam> nnp2(std::move(nnp1));
  EXPECT_POSTCOND_ERROR(nnp1->get());
  EXPECT_POSTCOND_ERROR(nnp1->set(3));
}



TYPED_TEST(test_not_null_any_smart_pointer, comparison)
{
  typename TypeParam::element_type v1(2);
  TypeParam p1 = TestFixture::make_ptr(v1);
  typename TypeParam::element_type v2(3);
  TypeParam p2 = TestFixture::make_ptr(v2);

  not_null<TypeParam> nnp1(std::move(p1));
  not_null<TypeParam> nnp2(std::move(p2));

  EXPECT_FALSE(nnp1 == nnp2);
  EXPECT_TRUE(nnp1 != nnp2);
}



TYPED_TEST(test_not_null_copyable_smart_pointer, comparison)
{
  typename TypeParam::element_type v1(2);
  TypeParam p1 = TestFixture::make_ptr(v1);
  typename TypeParam::element_type v2(3);
  TypeParam p2 = TestFixture::make_ptr(v2);

  not_null<TypeParam> nnp1(p1);
  not_null<TypeParam> nnp2(p1);
  not_null<TypeParam> nnp3(p2);

  EXPECT_TRUE(nnp1 == nnp2);
  EXPECT_FALSE(nnp1 == nnp3);

  EXPECT_FALSE(nnp1 != nnp2);
  EXPECT_TRUE(nnp1 != nnp3);
}



// operator<< is missing for smart pointers, so operator<< for not_null does not
// compile.
// TYPED_TEST(test_not_null_any_smart_pointer, output_stream_operator)
// {
//   typename TypeParam::element_type v(2);
//   TypeParam p(v);
//   std::stringstream ss;
//   ss << p;
//   not_null<TypeParam> nnp(std::move(p));
//   EXPECT_OUTPUT(ss.str().c_str(), nnp);
// }




class test_not_null_naked_pointer : public Test
{};



TEST_F(test_not_null_naked_pointer, pointer_copy_constructor)
{
  int v = 2;
  int* p = &v;
  not_null<int*> nnp(p);
  EXPECT_EQ(*p, *nnp);
}



TEST_F(test_not_null_naked_pointer, pointer_move_constructor)
{
  int v = 2;
  int* p = &v;
  not_null<int*> nnp(std::move(p));
  EXPECT_EQ(v, *nnp);
}



TEST_F(test_not_null_naked_pointer, copy_constructor)
{
  int v = 2;
  not_null<int*> nnp1(&v);
  not_null<int*> nnp2(nnp1);
  EXPECT_EQ(*nnp1, *nnp2);
}



TEST_F(test_not_null_naked_pointer, move_constructor)
{
  int v = 2;
  not_null<int*> nnp1(&v);
  not_null<int*> nnp2(std::move(nnp1));
  EXPECT_EQ(v, *nnp2);
}



TEST_F(test_not_null_naked_pointer, nullptr_copy_constructor)
{
  int* p = nullptr;
  EXPECT_PRECOND_ERROR(not_null<int*> nnp(p));
}



TEST_F(test_not_null_naked_pointer, nullptr_move_constructor)
{
  int* p = nullptr;
  EXPECT_PRECOND_ERROR(not_null<int*> nnp(std::move(p)));
}



TEST_F(test_not_null_naked_pointer, pointer_copy_assignment)
{
  int v1 = 2;
  int v2 = 3;
  not_null<int*> nnp(&v1);
  nnp = &v2;
  EXPECT_EQ(v2, *nnp);
}



TEST_F(test_not_null_naked_pointer, pointer_move_assignment)
{
  int v1 = 2;
  int v2 = 3;
  not_null<int*> nnp(std::move(&v1));
  nnp = std::move(&v2);
  EXPECT_EQ(v2, *nnp);
}



TEST_F(test_not_null_naked_pointer, nullptr_copy_assignment)
{
  int v1 = 2;
  int* p2 = nullptr;
  not_null<int*> nnp(&v1);
  EXPECT_PRECOND_ERROR(nnp = p2);
}



TEST_F(test_not_null_naked_pointer, nullptr_move_assignment)
{
  int v1 = 2;
  int* p2 = nullptr;
  not_null<int*> nnp(std::move(&v1));
  EXPECT_PRECOND_ERROR(nnp = std::move(p2));
}



TEST_F(test_not_null_naked_pointer, copy_assignment)
{
  int v1 = 2;
  int v2 = 3;
  not_null<int*> nnp1(&v1);
  not_null<int*> nnp2(&v2);
  not_null<int*> nnp3(nnp1);
  nnp3 = nnp2;
  EXPECT_EQ(*nnp2, *nnp3);
}



TEST_F(test_not_null_naked_pointer, move_assignment)
{
  int v1 = 2;
  int v2 = 3;
  not_null<int*> nnp1(&v1);
  not_null<int*> nnp2(&v2);
  not_null<int*> nnp3(std::move(nnp1));
  nnp3 = std::move(nnp2);
  EXPECT_EQ(v2, *nnp3);
}



TEST_F(test_not_null_naked_pointer, move_content)
{
  int v = 2;
  not_null<int*> nnp(&v);
  int* p = move_content(std::move(nnp));
  EXPECT_EQ(v, *p);
}



TEST_F(test_not_null_naked_pointer, get)
{
  int v = 2;
  not_null<int*> nnp(&v);
  EXPECT_EQ(&v, nnp.get());
}



TEST_F(test_not_null_naked_pointer, dereferencing)
{
  int v1 = 2;
  int v2 = 3;
  not_null<int*> nnp(&v1);
  EXPECT_EQ(v1, *nnp);
  *nnp = v2;
  EXPECT_EQ(v2, *nnp);
}



TEST_F(test_not_null_naked_pointer, dereferencing_member)
{
  foo v(2);
  not_null<foo*> nnp(&v);
  EXPECT_EQ(v.get(), nnp->get());
  v.set(5);
  EXPECT_EQ(v.get(), nnp->get());
  nnp->set(9);
  EXPECT_EQ(v.get(), nnp->get());
}



// Note: it is not possible (and pointless) to test if get() and the
// dereferencing operators throw an exception when the internal pointer in null
// for naked pointers. The only way this can happen is by moving the not_null
// object, but naked pointers will not be reset to nullptr in that case (unlike
// smart pointers).



TEST_F(test_not_null_naked_pointer, comparison)
{
  int v1 = 2;
  int v2 = 3;

  not_null<int*> nnp1(&v1);
  not_null<int*> nnp2(&v1);
  not_null<int*> nnp3(&v2);

  EXPECT_TRUE(nnp1 == nnp2);
  EXPECT_FALSE(nnp1 == nnp3);

  EXPECT_FALSE(nnp1 != nnp2);
  EXPECT_TRUE(nnp1 != nnp3);
}



TEST_F(test_not_null_naked_pointer, output_stream_operator)
{
  int v = 2;
  std::stringstream ss;
  ss << &v;
  not_null<int*> nnp(&v);
  EXPECT_OUTPUT(ss.str().c_str(), nnp);
}

}
