// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/cor_exceptions.hpp"
#include "hou/cor/uid_generator.hpp"

#include <limits>
#include <stdexcept>
#include <thread>

using namespace hou;
using namespace testing;



namespace
{

class test_uid_generator : public Test
{};
class test_uid_generator_death_test : public test_uid_generator
{};

}  // namespace



TEST_F(test_uid_generator, increment)
{
  uid_generator uid_gen(3u);

  EXPECT_EQ(3u, uid_gen.generate());
  EXPECT_EQ(4u, uid_gen.generate());
  EXPECT_EQ(5u, uid_gen.generate());
  EXPECT_EQ(6u, uid_gen.generate());
}



TEST_F(test_uid_generator, multi_thread_increment)
{
  uid_generator uid_gen(2u);

  auto thread_fun = [&uid_gen]() { uid_gen.generate(); };

  std::thread t1(thread_fun);
  std::thread t2(thread_fun);
  std::thread t3(thread_fun);
  std::thread t4(thread_fun);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  EXPECT_EQ(6u, uid_gen.generate());
}



TEST_F(test_uid_generator_death_test, overflow)
{
  uid_generator uid_gen(std::numeric_limits<uint32_t>::max() - 1);
  uid_gen.generate();
  EXPECT_ERROR_0(uid_gen.generate(), overflow_error);
}
