// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/not_null.hpp"

#include <memory>

using namespace testing;

// Not: not_null clashes with a gtest defined class. Therefore it is necessary to
// explicitly specify the namespace in this test case.



namespace
{

class TestNotNull : public Test {};

class Foo
{
public:
  Foo();
  int getInt() const;
  void setInt(int value);

private:
  int mInt;
};



Foo::Foo()
  : mInt(0)
{}



int Foo::getInt() const
{
  return mInt;
}



void Foo::setInt(int value)
{
  mInt = value;
}

}



TEST_F(TestNotNull, UniquePtrConstruction)
{
  using IntPtr = std::unique_ptr<int>;

  hou::not_null<IntPtr> nnp(std::make_unique<int>(2));
  EXPECT_EQ(2, *nnp.get());
  EXPECT_EQ(2, *nnp);
}



TEST_F(TestNotNull, UniquePtrGet)
{
  using IntPtr = std::unique_ptr<int>;

  hou::not_null<IntPtr> nnp(std::make_unique<int>(2));
  IntPtr p = std::move(nnp.get());
  EXPECT_EQ(2, *p);
}



TEST_F(TestNotNull, UniquePtrDereferencing)
{
  using IntPtr = std::unique_ptr<int>;

  hou::not_null<IntPtr> nnp(std::make_unique<int>(2));
  EXPECT_EQ(2, *nnp);
  *nnp = 3;
  EXPECT_EQ(3, *nnp);
}



TEST_F(TestNotNull, UniquePtrClassMethodDereferencing)
{
  using FooPtr = std::unique_ptr<Foo>;

  hou::not_null<FooPtr> nnp(std::make_unique<Foo>());
  EXPECT_EQ(0, nnp->getInt());
  nnp->setInt(42);
  EXPECT_EQ(42, nnp->getInt());
}



TEST_F(TestNotNull, SharedPtrConstruction)
{
  using IntPtr = std::shared_ptr<int>;

  IntPtr p = std::make_shared<int>(2);
  hou::not_null<IntPtr> nnp(p);
  EXPECT_EQ(2, *nnp.get());
  EXPECT_EQ(2, *nnp);
}



TEST_F(TestNotNull, SharedPtrGet)
{
  using IntPtr = std::shared_ptr<int>;

  hou::not_null<IntPtr> nnp(std::make_shared<int>(2));
  IntPtr p = nnp.get();
  EXPECT_EQ(2, *p);
}



TEST_F(TestNotNull, SharedPtrDereferencing)
{
  using IntPtr = std::shared_ptr<int>;

  hou::not_null<IntPtr> nnp(std::make_shared<int>(2));
  EXPECT_EQ(2, *nnp);
  *nnp = 3;
  EXPECT_EQ(3, *nnp);
}



TEST_F(TestNotNull, SharedPtrClassMethodDereferencing)
{
  using FooPtr = std::shared_ptr<Foo>;

  hou::not_null<FooPtr> nnp(std::make_shared<Foo>());
  EXPECT_EQ(0, nnp->getInt());
  nnp->setInt(42);
  EXPECT_EQ(42, nnp->getInt());
}



TEST_F(TestNotNull, SharedPtrConversion)
{
  using IntPtr = std::shared_ptr<int>;

  hou::not_null<IntPtr> nnp(std::make_shared<int>(2));
  IntPtr p = nnp;
  EXPECT_EQ(2, *p);
}



TEST_F(TestNotNull, NakedPtrConstruction)
{
  int* p = new int(2);
  hou::not_null<int*> nnp(p);
  EXPECT_EQ(2, *nnp.get());
  EXPECT_EQ(2, *nnp);
  delete p;
}



TEST_F(TestNotNull, NakedPtrGet)
{
  int* p1 = new int(2);
  hou::not_null<int*> nnp(p1);
  int* p2 = nnp.get();
  EXPECT_EQ(2, *p2);
  delete p1;
}



TEST_F(TestNotNull, NakedPtrDereferencing)
{
  int* p = new int(2);
  hou::not_null<int*> nnp(p);
  EXPECT_EQ(2, *nnp);
  *nnp = 3;
  EXPECT_EQ(3, *nnp);
  delete p;
}



TEST_F(TestNotNull, NakedPtrClassMethodDereferencing)
{
  Foo* p = new Foo();
  hou::not_null<Foo*> nnp(p);
  EXPECT_EQ(0, nnp->getInt());
  nnp->setInt(42);
  EXPECT_EQ(42, nnp->getInt());
  delete p;
}



TEST_F(TestNotNull, NakedPtrConversion)
{
  int* p1 = new int(2);
  hou::not_null<int*> nnp(p1);
  int* p2 = nnp;
  EXPECT_EQ(2, *p2);
  delete p1;
}

