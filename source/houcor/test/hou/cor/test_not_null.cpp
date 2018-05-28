// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/not_null.hpp"

#include <memory>

using namespace testing;



namespace
{

class test_not_null : public Test
{};

class foo
{
public:
  foo();
  int get_int() const;
  void set_int(int value);

private:
  int m_int;
};



foo::foo()
  : m_int(0)
{}



int foo::get_int() const
{
  return m_int;
}



void foo::set_int(int value)
{
  m_int = value;
}

}  // namespace



TEST_F(test_not_null, unique_ptr_construction)
{
  using int_ptr = std::unique_ptr<int>;

  hou::not_null<int_ptr> nnp(std::make_unique<int>(2));
  EXPECT_EQ(2, *nnp.get());
  EXPECT_EQ(2, *nnp);
}



TEST_F(test_not_null, unique_ptr_get)
{
  using int_ptr = std::unique_ptr<int>;

  hou::not_null<int_ptr> nnp(std::make_unique<int>(2));
  int_ptr p = std::move(nnp.get());
  EXPECT_EQ(2, *p);
}



TEST_F(test_not_null, unique_ptr_dereferencing)
{
  using int_ptr = std::unique_ptr<int>;

  hou::not_null<int_ptr> nnp(std::make_unique<int>(2));
  EXPECT_EQ(2, *nnp);
  *nnp = 3;
  EXPECT_EQ(3, *nnp);
}



TEST_F(test_not_null, unique_ptr_class_method_dereferencing)
{
  using foo_ptr = std::unique_ptr<foo>;

  hou::not_null<foo_ptr> nnp(std::make_unique<foo>());
  EXPECT_EQ(0, nnp->get_int());
  nnp->set_int(42);
  EXPECT_EQ(42, nnp->get_int());
}



TEST_F(test_not_null, shared_ptr_construction)
{
  using int_ptr = std::shared_ptr<int>;

  int_ptr p = std::make_shared<int>(2);
  hou::not_null<int_ptr> nnp(p);
  EXPECT_EQ(2, *nnp.get());
  EXPECT_EQ(2, *nnp);
}



TEST_F(test_not_null, shared_ptr_get)
{
  using int_ptr = std::shared_ptr<int>;

  hou::not_null<int_ptr> nnp(std::make_shared<int>(2));
  int_ptr p = nnp.get();
  EXPECT_EQ(2, *p);
}



TEST_F(test_not_null, shared_ptr_dereferencing)
{
  using int_ptr = std::shared_ptr<int>;

  hou::not_null<int_ptr> nnp(std::make_shared<int>(2));
  EXPECT_EQ(2, *nnp);
  *nnp = 3;
  EXPECT_EQ(3, *nnp);
}



TEST_F(test_not_null, shared_ptr_class_method_dereferencing)
{
  using foo_ptr = std::shared_ptr<foo>;

  hou::not_null<foo_ptr> nnp(std::make_shared<foo>());
  EXPECT_EQ(0, nnp->get_int());
  nnp->set_int(42);
  EXPECT_EQ(42, nnp->get_int());
}



TEST_F(test_not_null, shared_ptr_conversion)
{
  using int_ptr = std::shared_ptr<int>;

  hou::not_null<int_ptr> nnp(std::make_shared<int>(2));
  int_ptr p = nnp;
  EXPECT_EQ(2, *p);
}



TEST_F(test_not_null, naked_ptr_construction)
{
  int* p = new int(2);
  hou::not_null<int*> nnp(p);
  EXPECT_EQ(2, *nnp.get());
  EXPECT_EQ(2, *nnp);
  delete p;
}



TEST_F(test_not_null, naked_ptr_get)
{
  int* p1 = new int(2);
  hou::not_null<int*> nnp(p1);
  int* p2 = nnp.get();
  EXPECT_EQ(2, *p2);
  delete p1;
}



TEST_F(test_not_null, naked_ptr_dereferencing)
{
  int* p = new int(2);
  hou::not_null<int*> nnp(p);
  EXPECT_EQ(2, *nnp);
  *nnp = 3;
  EXPECT_EQ(3, *nnp);
  delete p;
}



TEST_F(test_not_null, naked_ptr_class_method_dereferencing)
{
  foo* p = new foo();
  hou::not_null<foo*> nnp(p);
  EXPECT_EQ(0, nnp->get_int());
  nnp->set_int(42);
  EXPECT_EQ(42, nnp->get_int());
  delete p;
}



TEST_F(test_not_null, naked_ptr_conversion)
{
  int* p1 = new int(2);
  hou::not_null<int*> nnp(p1);
  int* p2 = nnp;
  EXPECT_EQ(2, *p2);
  delete p1;
}
