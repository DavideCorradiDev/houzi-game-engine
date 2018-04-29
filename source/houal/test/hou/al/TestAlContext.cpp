// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/al/AlContext.hpp"
#include "hou/al/AlDevice.hpp"
#include "hou/al/AlError.hpp"

#include <memory>
#include <thread>
#include <vector>

using namespace hou;



TEST(TestAlContext, Creation)
{
  al::Device device;
  al::context ph_context(device);

  EXPECT_NE(0u, ph_context.get_uid());
  EXPECT_EQ(device.get_uid(), ph_context.getDeviceUid());
  EXPECT_FALSE(ph_context.is_current());
}



TEST(TestAlContext, MoveConstructor)
{
  al::Device device;
  al::context contextDummy(device);
  uint32_t uidRef = contextDummy.get_uid();
  al::context ph_context(std::move(contextDummy));

  EXPECT_EQ(uidRef, ph_context.get_uid());
  EXPECT_EQ(device.get_uid(), ph_context.getDeviceUid());
  EXPECT_FALSE(ph_context.is_current());
}



TEST(TestAlContext, CurrentContextMoveConstructor)
{
  al::Device device;
  al::context contextDummy(device);
  al::context::set_current(contextDummy);
  EXPECT_TRUE(contextDummy.is_current());
  EXPECT_EQ(&contextDummy, al::context::getCurrent());

  al::context ph_context(std::move(contextDummy));
  EXPECT_TRUE(ph_context.is_current());
  EXPECT_EQ(&ph_context, al::context::getCurrent());
}



TEST(TestAlContextDeathTest, ContextCreationFailed)
{
  // Artificially create an invalid ph_context by improper use of std::move.
  al::Device d1;
  al::Device d2(std::move(d1));

  HOU_EXPECT_ERROR(al::context c(d1), std::runtime_error
    , get_text(AlError::context_create));
}



TEST(TestAlContext, SetCurrent)
{
  al::Device d1;
  al::context c1(d1);
  al::Device d2;
  al::context c2(d2);

  EXPECT_FALSE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(nullptr, al::context::getCurrent());

  al::context::set_current(c1);
  EXPECT_TRUE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(&c1, al::context::getCurrent());

  al::context::set_current(c2);
  EXPECT_FALSE(c1.is_current());
  EXPECT_TRUE(c2.is_current());
  EXPECT_EQ(&c2, al::context::getCurrent());

  al::context::unset_current();
  EXPECT_FALSE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(nullptr, al::context::getCurrent());

  al::context::unset_current();
  EXPECT_FALSE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(nullptr, al::context::getCurrent());
}



TEST(TestAlContext, CurrentContextResetOnDestruction)
{
  {
    al::Device d;
    al::context c(d);
    al::context::set_current(c);
    EXPECT_EQ(&c, al::context::getCurrent());
  }
  EXPECT_EQ(nullptr, al::context::getCurrent());

  al::Device d1;
  al::context c1(d1);
  al::context::set_current(c1);
  {
    al::Device d2;
    al::context c2(d2);
  }
  EXPECT_EQ(&c1, al::context::getCurrent());
}



TEST(TestAlContext, MultithreadedGetCurrent)
{
  static constexpr size_t numThreads = 8u;

  al::Device d;
  al::context c(d);
  al::context::set_current(c);

  EXPECT_EQ(&c, al::context::getCurrent());
  EXPECT_TRUE(c.is_current());

  auto threadFun = [&c]()
  {
    EXPECT_EQ(&c, al::context::getCurrent());
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

  std::vector<al::Device> devices;
  std::vector<al::context> contexts;
  for(size_t i = 0; i < numThreads; ++i)
  {
    devices.push_back(al::Device());
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
    if(&c == al::context::getCurrent())
    {
      currentContextFound = true;
    }
  }
  EXPECT_TRUE(currentContextFound);
}

