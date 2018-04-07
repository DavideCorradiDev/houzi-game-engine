// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"

#include "hou/cor/TemplateUtils.hpp"

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
  EXPECT_TRUE(isContiguousContainer<Array2>::value);
  EXPECT_FALSE(isContiguousContainer<std::list<int>>::value);
  using Mapif = std::map<int, float>;
  EXPECT_FALSE(isContiguousContainer<Mapif>::value);
  EXPECT_FALSE(isContiguousContainer<std::set<int>>::value);
  EXPECT_TRUE(isContiguousContainer<std::string>::value);
  using UnMapii = std::unordered_map<int, int>;
  EXPECT_FALSE(isContiguousContainer<UnMapii>::value);
  EXPECT_TRUE(isContiguousContainer<std::vector<int>>::value);
  EXPECT_FALSE(isContiguousContainer<int>::value);
  EXPECT_TRUE(isContiguousContainer<IsContiguousContainerTestTrue>::value);
  EXPECT_FALSE(isContiguousContainer<IsContiguousContainerTestFalseNoPointer>::value);
  EXPECT_FALSE(isContiguousContainer<IsContiguousContainerTestFalseNoData>::value);
  EXPECT_FALSE(isContiguousContainer<IsContiguousContainerTestFalseIncompatibleDataPointer>::value);
  EXPECT_FALSE(isContiguousContainer<std::unique_ptr<int>>::value);
  // This case does not compile because template conditions try to call data().
  // EXPECT_FALSE(isContiguousContainer<IsContiguousContainerTestFalseDataVariable>::value);
}

