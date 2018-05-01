// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_device.hpp"
#include "hou/al/al_error.hpp"

#include <memory>
#include <thread>
#include <vector>

using namespace hou;



TEST(TestAlContext, Creation)
{
  al::device ph_device;
  al::context ph_context(ph_device);

  EXPECT_NE(0u, ph_context.get_uid());
  EXPECT_EQ(ph_device.get_uid(), ph_context.get_device_uid());
  EXPECT_FALSE(ph_context.is_current());
}



TEST(TestAlContext, MoveConstructor)
{
  al::device ph_device;
  al::context context_dummy(ph_device);
  uint32_t uid_ref = context_dummy.get_uid();
  al::context ph_context(std::move(context_dummy));

  EXPECT_EQ(uid_ref, ph_context.get_uid());
  EXPECT_EQ(ph_device.get_uid(), ph_context.get_device_uid());
  EXPECT_FALSE(ph_context.is_current());
}



TEST(TestAlContext, CurrentContextMoveConstructor)
{
  al::device ph_device;
  al::context context_dummy(ph_device);
  al::context::set_current(context_dummy);
  EXPECT_TRUE(context_dummy.is_current());
  EXPECT_EQ(&context_dummy, al::context::get_current());

  al::context ph_context(std::move(context_dummy));
  EXPECT_TRUE(ph_context.is_current());
  EXPECT_EQ(&ph_context, al::context::get_current());
}



TEST(TestAlContextDeathTest, ContextCreationFailed)
{
  // Artificially create an invalid ph_context by improper use of std::move.
  al::device d1;
  al::device d2(std::move(d1));

  HOU_EXPECT_ERROR(al::context c(d1), std::runtime_error
    , get_text(al_error::context_create));
}



TEST(TestAlContext, SetCurrent)
{
  al::device d1;
  al::context c1(d1);
  al::device d2;
  al::context c2(d2);

  EXPECT_FALSE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(nullptr, al::context::get_current());

  al::context::set_current(c1);
  EXPECT_TRUE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(&c1, al::context::get_current());

  al::context::set_current(c2);
  EXPECT_FALSE(c1.is_current());
  EXPECT_TRUE(c2.is_current());
  EXPECT_EQ(&c2, al::context::get_current());

  al::context::unset_current();
  EXPECT_FALSE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(nullptr, al::context::get_current());

  al::context::unset_current();
  EXPECT_FALSE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(nullptr, al::context::get_current());
}



TEST(TestAlContext, CurrentContextResetOnDestruction)
{
  {
    al::device d;
    al::context c(d);
    al::context::set_current(c);
    EXPECT_EQ(&c, al::context::get_current());
  }
  EXPECT_EQ(nullptr, al::context::get_current());

  al::device d1;
  al::context c1(d1);
  al::context::set_current(c1);
  {
    al::device d2;
    al::context c2(d2);
  }
  EXPECT_EQ(&c1, al::context::get_current());
}



TEST(TestAlContext, MultithreadedGetCurrent)
{
  static constexpr size_t numThreads = 8u;

  al::device d;
  al::context c(d);
  al::context::set_current(c);

  EXPECT_EQ(&c, al::context::get_current());
  EXPECT_TRUE(c.is_current());

  auto threadFun = [&c]()
  {
    EXPECT_EQ(&c, al::context::get_current());
    EXPECT_TRUE(c.is_current());
  };

  std::vector<std::unique_ptr<std::thread>> threads;
  for(size_t i = 0; i < numThreads; ++i)
  {
    threads.push_back(std::make_unique<std::thread>(threadFun));
  }

  for(size_t i = 0; i < threads.size(); ++i)
  {
    threads[i]->join();
  }
}



TEST(TestAlContext, MultithreadedSetCurrent)
{
  static constexpr size_t numThreads = 8u;

  std::vector<al::device> devices;
  std::vector<al::context> contexts;
  for(size_t i = 0; i < numThreads; ++i)
  {
    devices.push_back(al::device());
    contexts.push_back(al::context(devices[i]));
  }

  auto threadFun = [](al::context& ctx)
  {
    al::context::set_current(ctx);
  };

  std::vector<std::unique_ptr<std::thread>> threads;
  for(size_t i = 0; i < contexts.size(); ++i)
  {
    threads.push_back(std::make_unique<std::thread>(threadFun
      , std::ref(contexts[i])));
  }

  for(size_t i = 0; i < threads.size(); ++i)
  {
    threads[i]->join();
  }

  bool currentContextFound = false;
  for(const auto& c : contexts)
  {
    if(&c == al::context::get_current())
    {
      currentContextFound = true;
    }
  }
  EXPECT_TRUE(currentContextFound);
}

