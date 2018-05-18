// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/checked_variable.hpp"

using namespace hou;
using namespace testing;



namespace hou
{

class test_checked_variable : public Test
{};

class test_checked_variable_death_test : public test_checked_variable
{};

template <typename T>
class dummy_checker
{
public:
  using value_type = T;

  static constexpr bool check(const T& t) noexcept
  {
    return t > T(0) && t < T(5);
  }
};

}  // namespace hou



TEST_F(test_checked_variable, construction)
{
  using cvar = checked_variable<int, dummy_checker<int>>;
  cvar v0(1);
  cvar v1(4);

  EXPECT_EQ(1, v0);
  EXPECT_EQ(1, v0.get());

  EXPECT_EQ(4, v1);
  EXPECT_EQ(4, v1.get());
}



TEST_F(test_checked_variable_death_test, construction_error)
{
  using cvar = checked_variable<int, dummy_checker<int>>;
  EXPECT_ERROR_0(cvar v(0), invalid_value);
  EXPECT_ERROR_0(cvar v(5), invalid_value);
}




TEST_F(test_checked_variable, assignment)
{
  using cvar = checked_variable<int, dummy_checker<int>>;
  cvar v0(1);
  EXPECT_EQ(1, v0);

  v0 = 2;
  EXPECT_EQ(2, v0);
}



TEST_F(test_checked_variable_death_test, assignment_error)
{
  using cvar = checked_variable<int, dummy_checker<int>>;
  cvar v0(1);
  EXPECT_EQ(1, v0);

  EXPECT_ERROR_0(v0 = 0, invalid_value);
  EXPECT_ERROR_0(v0 = 5, invalid_value);
}



TEST_F(test_checked_variable, comparison)
{
  using cvar = checked_variable<int, dummy_checker<int>>;

  cvar v0(2);
  cvar v1(v0);
  cvar v2(3);

  EXPECT_TRUE(v0 == v1);
  EXPECT_FALSE(v0 == v2);

  EXPECT_FALSE(v0 != v1);
  EXPECT_TRUE(v0 != v2);

  EXPECT_FALSE(v0 > v1);
  EXPECT_FALSE(v0 > v2);
  EXPECT_FALSE(v1 > v0);
  EXPECT_TRUE(v2 > v0);

  EXPECT_TRUE(v0 >= v1);
  EXPECT_FALSE(v0 >= v2);
  EXPECT_TRUE(v1 >= v0);
  EXPECT_TRUE(v2 >= v0);

  EXPECT_FALSE(v0 < v1);
  EXPECT_TRUE(v0 < v2);
  EXPECT_FALSE(v1 < v0);
  EXPECT_FALSE(v2 < v0);

  EXPECT_TRUE(v0 <= v1);
  EXPECT_TRUE(v0 <= v2);
  EXPECT_TRUE(v1 <= v0);
  EXPECT_FALSE(v2 <= v0);
}



TEST_F(test_checked_variable, arithmetic_operation)
{
  using cvar = checked_variable<int, dummy_checker<int>>;
  EXPECT_EQ(3, cvar(1) + cvar(2));
  EXPECT_EQ(3, cvar(4) - cvar(1));
  EXPECT_EQ(4, cvar(2) * cvar(2));
  EXPECT_EQ(1, cvar(3) / cvar(2));
}




TEST_F(test_checked_variable_death_test, arithmetic_operation_failure)
{
  using cvar = checked_variable<int, dummy_checker<int>>;
  EXPECT_ERROR_0(cvar(cvar(3) + cvar(2)), invalid_value);
  EXPECT_ERROR_0(cvar(cvar(4) - cvar(4)), invalid_value);
  EXPECT_ERROR_0(cvar(cvar(2) * cvar(3)), invalid_value);
  EXPECT_ERROR_0(cvar(cvar(3) / cvar(4)), invalid_value);
}



TEST_F(test_checked_variable, positive_checker)
{
  EXPECT_TRUE(positive_checker<int>::check(1));
  EXPECT_FALSE(positive_checker<int>::check(0));
  EXPECT_FALSE(positive_checker<int>::check(-1));

  EXPECT_TRUE(positive_checker<uint>::check(1));
  EXPECT_FALSE(positive_checker<uint>::check(0));

  EXPECT_TRUE(positive_checker<float>::check(1.f));
  EXPECT_FALSE(positive_checker<float>::check(0.f));
  EXPECT_FALSE(positive_checker<float>::check(-1.f));
}



TEST_F(test_checked_variable, positive)
{
  EXPECT_EQ(1, positive<int>(1));
  EXPECT_EQ(4u, positive<uint>(4u));
  EXPECT_EQ(1.4f, positive<float>(1.4f));
}



TEST_F(test_checked_variable_death_test, positive_failure)
{
  EXPECT_ERROR_0(positive<int>(0), invalid_value);
  EXPECT_ERROR_0(positive<int>(-1), invalid_value);
  EXPECT_ERROR_0(positive<uint>(0), invalid_value);
  EXPECT_ERROR_0(positive<float>(0.f), invalid_value);
  EXPECT_ERROR_0(positive<float>(-1.f), invalid_value);
}
