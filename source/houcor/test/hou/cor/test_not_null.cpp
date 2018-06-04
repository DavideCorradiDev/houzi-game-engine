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

class test_not_null : public Test
{};

using test_not_null_death_test = test_not_null;



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



TEST_F(test_not_null_death_test, nullptr_assignment)
{
  using int_ptr = int*;
  int_ptr p = nullptr;
  EXPECT_PRECOND_ERROR(not_null<int_ptr> nn(p));
}



TEST_F(test_not_null, unique_ptr_construction)
{
  using int_ptr = std::unique_ptr<int>;

  not_null<int_ptr> nnp(std::make_unique<int>(2));
  EXPECT_EQ(2, *nnp.get());
  EXPECT_EQ(2, *nnp);
}



TEST_F(test_not_null, unique_ptr_move)
{
  using int_ptr = std::unique_ptr<int>;

  not_null<int_ptr> nnp(std::make_unique<int>(2));
  not_null<int_ptr> p = std::move(nnp);
  EXPECT_EQ(2, *p);
}



TEST_F(test_not_null_death_test, unique_ptr_move_dereferencing_error)
{
  using int_ptr = std::unique_ptr<int>;

  not_null<int_ptr> nnp(std::make_unique<int>(2));
  not_null<int_ptr> p = std::move(nnp);
  EXPECT_EQ(2, *p);
  EXPECT_POSTCOND_ERROR(nnp.get());
  EXPECT_POSTCOND_ERROR(*nnp);
}



TEST_F(test_not_null, unique_ptr_move_content)
{
  using int_ptr = std::unique_ptr<int>;

  not_null<int_ptr> nnp(std::make_unique<int>(2));
  int_ptr p = move_content(std::move(nnp));
  EXPECT_EQ(2, *p);
}



TEST_F(test_not_null_death_test, unique_ptr_move_content_dereferencing_error)
{
  using int_ptr = std::unique_ptr<int>;

  not_null<int_ptr> nnp(std::make_unique<int>(2));
  int_ptr p = move_content(std::move(nnp));
  EXPECT_EQ(2, *p);
  EXPECT_POSTCOND_ERROR(nnp.get());
  EXPECT_POSTCOND_ERROR(*nnp);
}



TEST_F(test_not_null, unique_ptr_get)
{
  using int_ptr = std::unique_ptr<int>;

  not_null<int_ptr> nnp(std::make_unique<int>(2));
  EXPECT_EQ(2, *nnp.get());
  *nnp = 3;
  EXPECT_EQ(3, *nnp.get());
}



TEST_F(test_not_null, unique_ptr_dereferencing)
{
  using int_ptr = std::unique_ptr<int>;

  not_null<int_ptr> nnp(std::make_unique<int>(2));
  EXPECT_EQ(2, *nnp);
  *nnp = 3;
  EXPECT_EQ(3, *nnp);
}



TEST_F(test_not_null, unique_ptr_class_method_dereferencing)
{
  using foo_ptr = std::unique_ptr<foo>;

  not_null<foo_ptr> nnp(std::make_unique<foo>());
  EXPECT_EQ(0, nnp->get_int());
  nnp->set_int(42);
  EXPECT_EQ(42, nnp->get_int());
}



TEST_F(test_not_null_death_test, unique_ptr_class_method_dereferencing_error)
{
  using foo_ptr = std::unique_ptr<foo>;

  not_null<foo_ptr> nnp(std::make_unique<foo>());
  not_null<foo_ptr> new_nnp(std::move(nnp));
  EXPECT_POSTCOND_ERROR(nnp->get_int());
}



TEST_F(test_not_null, shared_ptr_construction)
{
  using int_ptr = std::shared_ptr<int>;

  int_ptr p = std::make_shared<int>(2);
  not_null<int_ptr> nnp(p);
  EXPECT_EQ(2, *nnp.get());
  EXPECT_EQ(2, *nnp);
}



TEST_F(test_not_null, shared_ptr_get)
{
  using int_ptr = std::shared_ptr<int>;

  not_null<int_ptr> nnp(std::make_shared<int>(2));
  int_ptr p = nnp.get();
  EXPECT_EQ(2, *p);
}



TEST_F(test_not_null, shared_ptr_dereferencing)
{
  using int_ptr = std::shared_ptr<int>;

  not_null<int_ptr> nnp(std::make_shared<int>(2));
  EXPECT_EQ(2, *nnp);
  *nnp = 3;
  EXPECT_EQ(3, *nnp);
}



TEST_F(test_not_null, shared_ptr_class_method_dereferencing)
{
  using foo_ptr = std::shared_ptr<foo>;

  not_null<foo_ptr> nnp(std::make_shared<foo>());
  EXPECT_EQ(0, nnp->get_int());
  nnp->set_int(42);
  EXPECT_EQ(42, nnp->get_int());
}



TEST_F(test_not_null, shared_ptr_conversion)
{
  using int_ptr = std::shared_ptr<int>;

  not_null<int_ptr> nnp(std::make_shared<int>(2));
  int_ptr p = nnp;
  EXPECT_EQ(2, *p);
}



TEST_F(test_not_null, naked_ptr_construction)
{
  int* p = new int(2);
  not_null<int*> nnp(p);
  EXPECT_EQ(2, *nnp.get());
  EXPECT_EQ(2, *nnp);
  delete p;
}



TEST_F(test_not_null, naked_ptr_get)
{
  int* p1 = new int(2);
  not_null<int*> nnp(p1);
  int* p2 = nnp.get();
  EXPECT_EQ(2, *p2);
  delete p1;
}



TEST_F(test_not_null, naked_ptr_dereferencing)
{
  int* p = new int(2);
  not_null<int*> nnp(p);
  EXPECT_EQ(2, *nnp);
  *nnp = 3;
  EXPECT_EQ(3, *nnp);
  delete p;
}



TEST_F(test_not_null, naked_ptr_class_method_dereferencing)
{
  foo* p = new foo();
  not_null<foo*> nnp(p);
  EXPECT_EQ(0, nnp->get_int());
  nnp->set_int(42);
  EXPECT_EQ(42, nnp->get_int());
  delete p;
}



TEST_F(test_not_null, naked_ptr_conversion)
{
  int* p1 = new int(2);
  not_null<int*> nnp(p1);
  int* p2 = nnp;
  EXPECT_EQ(2, *p2);
  delete p1;
}



TEST_F(test_not_null, comparison)
{
  int* p1 = new int(2);
  int* p2 = new int(2);

  not_null<int*> nnp1(p1);
  not_null<int*> nnp2(p1);
  not_null<int*> nnp3(p2);

  EXPECT_TRUE(nnp1 == nnp2);
  EXPECT_FALSE(nnp1 == nnp3);

  EXPECT_FALSE(nnp1 != nnp2);
  EXPECT_TRUE(nnp1 != nnp3);

  delete p1;
  delete p2;
}



TEST_F(test_not_null, output_stream_operator)
{
  int* p = new int(2);
  not_null<int*> nnp(p);

  std::stringstream ss;
  ss << p;

  EXPECT_OUTPUT(ss.str().c_str(), nnp);

  delete p;
}
