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
  al::Context context(device);

  EXPECT_NE(0u, context.get_uid());
  EXPECT_EQ(device.get_uid(), context.getDeviceUid());
  EXPECT_FALSE(context.isCurrent());
}



TEST(TestAlContext, MoveConstructor)
{
  al::Device device;
  al::Context contextDummy(device);
  uint32_t uidRef = contextDummy.get_uid();
  al::Context context(std::move(contextDummy));

  EXPECT_EQ(uidRef, context.get_uid());
  EXPECT_EQ(device.get_uid(), context.getDeviceUid());
  EXPECT_FALSE(context.isCurrent());
}



TEST(TestAlContext, CurrentContextMoveConstructor)
{
  al::Device device;
  al::Context contextDummy(device);
  al::Context::setCurrent(contextDummy);
  EXPECT_TRUE(contextDummy.isCurrent());
  EXPECT_EQ(&contextDummy, al::Context::getCurrent());

  al::Context context(std::move(contextDummy));
  EXPECT_TRUE(context.isCurrent());
  EXPECT_EQ(&context, al::Context::getCurrent());
}



TEST(TestAlContextDeathTest, ContextCreationFailed)
{
  // Artificially create an invalid context by improper use of std::move.
  al::Device d1;
  al::Device d2(std::move(d1));

  HOU_EXPECT_ERROR(al::Context c(d1), std::runtime_error
    , get_text(AlError::ContextCreate));
}



TEST(TestAlContext, SetCurrent)
{
  al::Device d1;
  al::Context c1(d1);
  al::Device d2;
  al::Context c2(d2);

  EXPECT_FALSE(c1.isCurrent());
  EXPECT_FALSE(c2.isCurrent());
  EXPECT_EQ(nullptr, al::Context::getCurrent());

  al::Context::setCurrent(c1);
  EXPECT_TRUE(c1.isCurrent());
  EXPECT_FALSE(c2.isCurrent());
  EXPECT_EQ(&c1, al::Context::getCurrent());

  al::Context::setCurrent(c2);
  EXPECT_FALSE(c1.isCurrent());
  EXPECT_TRUE(c2.isCurrent());
  EXPECT_EQ(&c2, al::Context::getCurrent());

  al::Context::unsetCurrent();
  EXPECT_FALSE(c1.isCurrent());
  EXPECT_FALSE(c2.isCurrent());
  EXPECT_EQ(nullptr, al::Context::getCurrent());

  al::Context::unsetCurrent();
  EXPECT_FALSE(c1.isCurrent());
  EXPECT_FALSE(c2.isCurrent());
  EXPECT_EQ(nullptr, al::Context::getCurrent());
}



TEST(TestAlContext, CurrentContextResetOnDestruction)
{
  {
    al::Device d;
    al::Context c(d);
    al::Context::setCurrent(c);
    EXPECT_EQ(&c, al::Context::getCurrent());
  }
  EXPECT_EQ(nullptr, al::Context::getCurrent());

  al::Device d1;
  al::Context c1(d1);
  al::Context::setCurrent(c1);
  {
    al::Device d2;
    al::Context c2(d2);
  }
  EXPECT_EQ(&c1, al::Context::getCurrent());
}



TEST(TestAlContext, MultithreadedGetCurrent)
{
  static constexpr size_t numThreads = 8u;

  al::Device d;
  al::Context c(d);
  al::Context::setCurrent(c);

  EXPECT_EQ(&c, al::Context::getCurrent());
  EXPECT_TRUE(c.isCurrent());

  auto threadFun = [&c]()
  {
    EXPECT_EQ(&c, al::Context::getCurrent());
    EXPECT_TRUE(c.isCurrent());
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
  std::vector<al::Context> contexts;
  for(size_t i = 0; i < numThreads; ++i)
  {
    devices.push_back(al::Device());
    contexts.push_back(al::Context(devices[i]));
  }

  auto threadFun = [](al::Context& ctx)
  {
    al::Context::setCurrent(ctx);
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
    if(&c == al::Context::getCurrent())
    {
      currentContextFound = true;
    }
  }
  EXPECT_TRUE(currentContextFound);
}

