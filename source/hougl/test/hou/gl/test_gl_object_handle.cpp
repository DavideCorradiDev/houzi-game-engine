// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/test_gl_single_context.hpp"
#include "hou/gl/gl_object_handle.hpp"

#include "hou/gl/gl_context_settings.hpp"

#include "hou/sys/video_mode.hpp"



using namespace hou;



namespace
{

class TestGlObjectHandle : public test_gl_single_context {};

class ConcreteGlObjectHandle
  : public gl::object_handle
{
public:
  ConcreteGlObjectHandle(GLuint name)
    : gl::object_handle(name)
  {}
};



class ConcreteGlSharedObjectHandle
  : public gl::shared_object_handle
{
public:
  ConcreteGlSharedObjectHandle(GLuint name)
    : gl::shared_object_handle(name)
  {}
};



class ConcreteGlNonSharedObjectHandle
  : public gl::non_shared_object_handle
{
public:
  ConcreteGlNonSharedObjectHandle(GLuint name)
    : gl::non_shared_object_handle(name)
  {}
};

}



TEST_F(TestGlObjectHandle, Creation)
{
  ConcreteGlObjectHandle oh(1u);
  EXPECT_EQ(1u, oh.get_name());
  EXPECT_NE(0u, oh.get_uid());

  ConcreteGlObjectHandle oh2(1u);
  EXPECT_NE(oh.get_uid(), oh2.get_uid());
}



TEST_F(TestGlObjectHandle, SharedCreation)
{
  ConcreteGlSharedObjectHandle oh(2u);
  EXPECT_EQ(2u, oh.get_name());
  EXPECT_NE(0u, oh.get_uid());
  EXPECT_EQ(mContext.getSharingGroupUid(), oh.get_owning_sharing_group_uid());

  ConcreteGlObjectHandle oh2(1u);
  EXPECT_NE(oh.get_uid(), oh2.get_uid());
}



TEST_F(TestGlObjectHandle, NonSharedCreation)
{
  ConcreteGlNonSharedObjectHandle oh(3u);
  EXPECT_EQ(3u, oh.get_name());
  EXPECT_NE(0u, oh.get_uid());
  EXPECT_EQ(mContext.get_uid(), oh.get_owning_context_uid());

  ConcreteGlObjectHandle oh2(1u);
  EXPECT_NE(oh.get_uid(), oh2.get_uid());
}



TEST_F(TestGlObjectHandle, MoveConstructor)
{
  ConcreteGlObjectHandle oh_dummy(1u);
  ConcreteGlObjectHandle oh(std::move(oh_dummy));
  uint32_t ohUid_ref = oh.get_uid();
  EXPECT_EQ(0u, oh_dummy.get_name());
  EXPECT_EQ(0u, oh_dummy.get_uid());
  EXPECT_EQ(1u, oh.get_name());
  EXPECT_EQ(ohUid_ref, oh.get_uid());
}



TEST_F(TestGlObjectHandle, SharedMoveConstructor)
{
  ConcreteGlSharedObjectHandle oh_dummy(1u);
  ConcreteGlSharedObjectHandle oh(std::move(oh_dummy));
  uint32_t ohUid_ref = oh.get_uid();
  EXPECT_EQ(0u, oh_dummy.get_name());
  EXPECT_EQ(0u, oh_dummy.get_uid());
  EXPECT_EQ(mContext.getSharingGroupUid(), oh_dummy.get_owning_sharing_group_uid());
  EXPECT_EQ(1u, oh.get_name());
  EXPECT_EQ(ohUid_ref, oh.get_uid());
  EXPECT_EQ(mContext.getSharingGroupUid(), oh.get_owning_sharing_group_uid());
}



TEST_F(TestGlObjectHandle, NonSharedMoveConstructor)
{
  ConcreteGlNonSharedObjectHandle oh_dummy(1u);
  ConcreteGlNonSharedObjectHandle oh(std::move(oh_dummy));
  uint32_t ohUid_ref = oh.get_uid();
  EXPECT_EQ(0u, oh_dummy.get_name());
  EXPECT_EQ(0u, oh_dummy.get_uid());
  EXPECT_EQ(mContext.get_uid(), oh_dummy.get_owning_context_uid());
  EXPECT_EQ(1u, oh.get_name());
  EXPECT_EQ(ohUid_ref, oh.get_uid());
  EXPECT_EQ(mContext.get_uid(), oh.get_owning_context_uid());
}



TEST_F(TestGlObjectHandle, SharedOwnerUid)
{
  system_window w("Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w);
  gl::context c2(gl::context_settings::standard, w, c1);
  gl::context c3(gl::context_settings::standard, w);

  gl::context::set_current(c1, w);
  ConcreteGlSharedObjectHandle sh1(0u);

  gl::context::set_current(c2, w);
  ConcreteGlSharedObjectHandle sh2(0u);

  gl::context::set_current(c3, w);
  ConcreteGlSharedObjectHandle sh3(0u);

  EXPECT_EQ(c1.getSharingGroupUid(), sh1.get_owning_sharing_group_uid());
  EXPECT_EQ(c2.getSharingGroupUid(), sh2.get_owning_sharing_group_uid());
  EXPECT_EQ(c3.getSharingGroupUid(), sh3.get_owning_sharing_group_uid());

  EXPECT_EQ(sh1.get_owning_sharing_group_uid(), sh2.get_owning_sharing_group_uid());
  EXPECT_NE(sh1.get_owning_sharing_group_uid(), sh3.get_owning_sharing_group_uid());
  EXPECT_NE(sh2.get_owning_sharing_group_uid(), sh3.get_owning_sharing_group_uid());
}



TEST_F(TestGlObjectHandle, NonSharedOwnerUid)
{
  system_window w("Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w);
  gl::context c2(gl::context_settings::standard, w, c1);
  gl::context c3(gl::context_settings::standard, w);

  gl::context::set_current(c1, w);
  ConcreteGlNonSharedObjectHandle nsh1(0u);

  gl::context::set_current(c2, w);
  ConcreteGlNonSharedObjectHandle nsh2(0u);

  gl::context::set_current(c3, w);
  ConcreteGlNonSharedObjectHandle nsh3(0u);

  EXPECT_EQ(c1.get_uid(), nsh1.get_owning_context_uid());
  EXPECT_EQ(c2.get_uid(), nsh2.get_owning_context_uid());
  EXPECT_EQ(c3.get_uid(), nsh3.get_owning_context_uid());

  EXPECT_NE(nsh1.get_owning_context_uid(), nsh2.get_owning_context_uid());
  EXPECT_NE(nsh1.get_owning_context_uid(), nsh3.get_owning_context_uid());
  EXPECT_NE(nsh2.get_owning_context_uid(), nsh3.get_owning_context_uid());
}

