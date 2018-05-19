// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/member_detector.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_member_detector : public Test
{};

class detector_test_class_true
{
  int answer()
  {
    return 42;
  }
};

class detector_test_class_false
{};

HOU_CREATE_MEMBER_DETECTOR(answer);

class type_detector_test_class_true
{
public:
  using my_type = int;
};

class type_detector_test_class_false
{};

HOU_CREATE_MEMBER_TYPE_DETECTOR(my_type);

}  // namespace



TEST_F(test_member_detector, MemberDetector)
{
  EXPECT_TRUE(has_member_answer<detector_test_class_true>::value);
  EXPECT_FALSE(has_member_answer<detector_test_class_false>::value);
  EXPECT_FALSE(has_member_answer<int>::value);
}



TEST_F(test_member_detector, TypeDetector)
{
  EXPECT_TRUE(has_member_type_my_type<type_detector_test_class_true>::value);
  EXPECT_FALSE(has_member_type_my_type<type_detector_test_class_false>::value);
  EXPECT_FALSE(has_member_type_my_type<int>::value);
}
