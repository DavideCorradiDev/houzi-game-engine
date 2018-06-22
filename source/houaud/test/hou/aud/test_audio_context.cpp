// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/aud/audio_context.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_audio_context : public Test
{};

}  // namespace



TEST_F(test_audio_context, default_creation)
{
  audio_context ctx;
  EXPECT_NE(nullptr, &ctx.get_impl());
  EXPECT_NE(nullptr, &ctx.get_device());
}



TEST_F(test_audio_context, device_name_creation)
{
  std::vector<std::string> device_names = audio_context::get_device_names();
  for(const auto& dev_name : device_names)
  {
    audio_context ctx(dev_name);
    EXPECT_NE(nullptr, &ctx.get_impl());
    EXPECT_NE(nullptr, &ctx.get_device());
  }
}



TEST_F(test_audio_context, move_constructor)
{
  audio_context ctx_dummy;
  al::context::uid_type ctx_uid = ctx_dummy.get_impl().get_uid();
  al::device::uid_type dev_uid = ctx_dummy.get_device().get_uid();

  audio_context ctx = std::move(ctx_dummy);
  EXPECT_EQ(0u, ctx_dummy.get_impl().get_uid());
  EXPECT_EQ(0u, ctx_dummy.get_device().get_uid());
  EXPECT_EQ(ctx_uid, ctx.get_impl().get_uid());
  EXPECT_EQ(dev_uid, ctx.get_device().get_uid());
}



TEST_F(test_audio_context, move_constructor_current_context)
{
  audio_context ctx_dummy;
  audio_context::set_current(ctx_dummy);
  audio_context ctx = std::move(ctx_dummy);
  EXPECT_TRUE(ctx.is_current());
}



TEST_F(test_audio_context, set_current)
{
  {
    audio_context ctx1;
    audio_context ctx2;

    EXPECT_FALSE(ctx1.is_current());
    EXPECT_FALSE(ctx2.is_current());

    audio_context::set_current(ctx1);
    EXPECT_TRUE(ctx1.is_current());
    EXPECT_FALSE(ctx2.is_current());

    audio_context::set_current(ctx2);
    EXPECT_FALSE(ctx1.is_current());
    EXPECT_TRUE(ctx2.is_current());

    audio_context::set_current(ctx2);
    EXPECT_FALSE(ctx1.is_current());
    EXPECT_TRUE(ctx2.is_current());

    audio_context::unset_current();
    EXPECT_FALSE(ctx1.is_current());
    EXPECT_FALSE(ctx2.is_current());

    audio_context::unset_current();
    EXPECT_FALSE(ctx1.is_current());
    EXPECT_FALSE(ctx2.is_current());
  }
  EXPECT_EQ(nullptr, al::context::get_current());
}
