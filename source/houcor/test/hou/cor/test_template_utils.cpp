// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/template_utils.hpp"

#include <array>
#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace hou;
using namespace testing;



namespace
{

class test_template_utils : public Test
{};

class is_contiguous_container_test_true
{
public:
  using pointer = int*;
  pointer data()
  {
    return &m_value;
  };

private:
  int m_value;
};

class is_contiguous_container_test_false_no_pointer
{
  int* data()
  {
    return &m_value;
  };

private:
  int m_value;
};

class is_contiguous_container_test_false_no_data
{
public:
  using pointer = int*;
};

class is_contiguous_container_test_false_data_variable
{
public:
  using pointer = int*;
  int data;
};

class is_contiguous_container_test_false_incompatible_data_pointer
{
public:
  using pointer = float*;
  int* data()
  {
    return &m_value;
  };

private:
  int m_value;
};

}  // namespace



TEST_F(test_template_utils, IsContiguousContainer)
{
  using Array2 = std::array<int, 2u>;
  EXPECT_TRUE(is_contiguous_container<Array2>::value);
  EXPECT_FALSE(is_contiguous_container<std::list<int>>::value);
  using Mapif = std::map<int, float>;
  EXPECT_FALSE(is_contiguous_container<Mapif>::value);
  EXPECT_FALSE(is_contiguous_container<std::set<int>>::value);
  EXPECT_TRUE(is_contiguous_container<std::string>::value);
  using UnMapii = std::unordered_map<int, int>;
  EXPECT_FALSE(is_contiguous_container<UnMapii>::value);
  EXPECT_TRUE(is_contiguous_container<std::vector<int>>::value);
  EXPECT_FALSE(is_contiguous_container<int>::value);
  EXPECT_TRUE(
    is_contiguous_container<is_contiguous_container_test_true>::value);
  EXPECT_FALSE(is_contiguous_container<
               is_contiguous_container_test_false_no_pointer>::value);
  EXPECT_FALSE(
    is_contiguous_container<is_contiguous_container_test_false_no_data>::value);
  EXPECT_FALSE(
    is_contiguous_container<
      is_contiguous_container_test_false_incompatible_data_pointer>::value);
  EXPECT_FALSE(is_contiguous_container<std::unique_ptr<int>>::value);
  // This case does not compile because template conditions try to call data().
  // EXPECT_FALSE(is_contiguous_container<is_contiguous_container_test_false_data_variable>::value);
}
