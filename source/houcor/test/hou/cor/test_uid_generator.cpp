// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/cor/uid_generator.hpp"

#include "hou/cor/cor_error.hpp"

#include <limits>
#include <stdexcept>
#include <thread>

using namespace hou;
using namespace testing;



namespace
{

class TestUidGenerator : public Test {};
class TestUidGeneratorDeathTest : public TestUidGenerator {};

}



TEST_F(TestUidGenerator, Increment)
{
  uid_generator uidGen(3u);

  EXPECT_EQ(3u, uidGen.generate());
  EXPECT_EQ(4u, uidGen.generate());
  EXPECT_EQ(5u, uidGen.generate());
  EXPECT_EQ(6u, uidGen.generate());
}



TEST_F(TestUidGenerator, MultiThreadIncrement)
{
  uid_generator uidGen(2u);

  auto threadFun = [&uidGen] ()
  {
    uidGen.generate();
  };

  std::thread t1(threadFun);
  std::thread t2(threadFun);
  std::thread t3(threadFun);
  std::thread t4(threadFun);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  EXPECT_EQ(6u, uidGen.generate());
}



TEST_F(TestUidGeneratorDeathTest, overflow)
{
  uid_generator uidGen(std::numeric_limits<uint32_t>::max() - 1);

  uidGen.generate();
  HOU_EXPECT_ERROR(uidGen.generate(), std::runtime_error
    , get_text(cor_error::overflow));
}

