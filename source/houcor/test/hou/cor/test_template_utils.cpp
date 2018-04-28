// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

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

class TestTemplateUtils : public Test {};

class DetectorTestClassTrue
{
  int answer() { return 42; }
};

class DetectorTestClassFalse {};

HOU_CREATE_MEMBER_DETECTOR(answer);

class TypeDetectorTestClassTrue
{
public:
  using MyType = int;
};

class TypeDetectorTestClassFalse {};

HOU_CREATE_TYPE_DETECTOR(MyType);

class IsContiguousContainerTestTrue
{
public:
  using pointer = int*;
  pointer data() { return &mValue; };

private:
  int mValue;
};

class IsContiguousContainerTestFalseNoPointer
{
  int* data() { return &mValue; };

private:
  int mValue;
};

class IsContiguousContainerTestFalseNoData
{
public:
  using pointer = int*;
};

class IsContiguousContainerTestFalseDataVariable
{
public:
  using pointer = int*;
  int data;
};

class IsContiguousContainerTestFalseIncompatibleDataPointer
{
public:
  using pointer = float*;
  int* data() { return &mValue; };

private:
  int mValue;
};

}



TEST_F(TestTemplateUtils, MemberDetector)
{
  EXPECT_TRUE(detect_member_answer<DetectorTestClassTrue>::value);
  EXPECT_FALSE(detect_member_answer<DetectorTestClassFalse>::value);
  EXPECT_FALSE(detect_member_answer<int>::value);
}



TEST_F(TestTemplateUtils, TypeDetector)
{
  EXPECT_TRUE(detect_type_MyType<TypeDetectorTestClassTrue>::value);
  EXPECT_FALSE(detect_type_MyType<TypeDetectorTestClassFalse>::value);
  EXPECT_FALSE(detect_type_MyType<int>::value);
}



TEST_F(TestTemplateUtils, IsContiguousContainer)
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
  EXPECT_TRUE(is_contiguous_container<IsContiguousContainerTestTrue>::value);
  EXPECT_FALSE(is_contiguous_container<IsContiguousContainerTestFalseNoPointer>::value);
  EXPECT_FALSE(is_contiguous_container<IsContiguousContainerTestFalseNoData>::value);
  EXPECT_FALSE(is_contiguous_container<IsContiguousContainerTestFalseIncompatibleDataPointer>::value);
  EXPECT_FALSE(is_contiguous_container<std::unique_ptr<int>>::value);
  // This case does not compile because template conditions try to call data().
  // EXPECT_FALSE(is_contiguous_container<IsContiguousContainerTestFalseDataVariable>::value);
}

