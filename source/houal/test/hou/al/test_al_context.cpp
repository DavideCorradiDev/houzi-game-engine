// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_device.hpp"
#include "hou/al/al_context_exceptions.hpp"

#include <memory>
#include <thread>
#include <vector>

using namespace hou;
using namespace testing;



namespace
{

class test_al_context : public Test
{};

class test_al_context_death_test : public test_al_context
{};

}  // namespace



TEST_F(test_al_context, creation)
{
  al::device dev;
  al::context ctx(dev);

  EXPECT_NE(0u, ctx.get_uid());
  EXPECT_EQ(dev.get_uid(), ctx.get_device_uid());
  EXPECT_FALSE(ctx.is_current());
}



TEST_F(test_al_context, move_constructor)
{
  al::device dev;
  al::context ctx_dummy(dev);

  al::context::impl_type* impl_ref = ctx_dummy.get_impl();
  al::context::uid_type uid_ref = ctx_dummy.get_uid();

  al::context ctx(std::move(ctx_dummy));

  EXPECT_EQ(nullptr, ctx_dummy.get_impl());
  EXPECT_EQ(0u, ctx_dummy.get_uid());

  EXPECT_EQ(impl_ref, ctx.get_impl());
  EXPECT_EQ(uid_ref, ctx.get_uid());
  EXPECT_EQ(dev.get_uid(), ctx.get_device_uid());
  EXPECT_FALSE(ctx.is_current());
}



TEST_F(test_al_context, current_context_move_constructor)
{
  al::device dev;
  al::context ctx_dummy(dev);

  al::context::set_current(ctx_dummy);
  EXPECT_TRUE(ctx_dummy.is_current());
  EXPECT_EQ(&ctx_dummy, al::context::get_current());

  al::context ctx(std::move(ctx_dummy));
  EXPECT_NE(&ctx_dummy, al::context::get_current());
  EXPECT_EQ(&ctx, al::context::get_current());
  EXPECT_TRUE(ctx.is_current());
}



TEST_F(test_al_context, set_current)
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



TEST_F(test_al_context, current_context_reset_on_destruction)
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



TEST_F(test_al_context, multithreaded_get_current)
{
  static constexpr size_t num_threads = 8u;

  al::device d;
  al::context c(d);
  al::context::set_current(c);

  EXPECT_EQ(&c, al::context::get_current());
  EXPECT_TRUE(c.is_current());

  auto thread_fun = [&c]() {
    EXPECT_EQ(&c, al::context::get_current());
    EXPECT_TRUE(c.is_current());
  };

  std::vector<std::unique_ptr<std::thread>> threads;
  for(size_t i = 0; i < num_threads; ++i)
  {
    threads.push_back(std::make_unique<std::thread>(thread_fun));
  }

  for(size_t i = 0; i < threads.size(); ++i)
  {
    threads[i]->join();
  }
}



TEST_F(test_al_context, multithreaded_set_current)
{
  static constexpr size_t num_threads = 8u;

  std::vector<al::device> devices;
  std::vector<al::context> contexts;
  for(size_t i = 0; i < num_threads; ++i)
  {
    devices.push_back(al::device());
    contexts.push_back(al::context(devices[i]));
  }

  auto thread_fun = [](al::context& ctx) { al::context::set_current(ctx); };

  std::vector<std::unique_ptr<std::thread>> threads;
  for(size_t i = 0; i < contexts.size(); ++i)
  {
    threads.push_back(
      std::make_unique<std::thread>(thread_fun, std::ref(contexts[i])));
  }

  for(size_t i = 0; i < threads.size(); ++i)
  {
    threads[i]->join();
  }

  bool current_ctx_found = false;
  for(const auto& c : contexts)
  {
    if(&c == al::context::get_current())
    {
      current_ctx_found = true;
    }
  }
  EXPECT_TRUE(current_ctx_found);
}
