// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/TestGlSingleContext.hpp"
#include "hou/gl/GlObjectHandle.hpp"

#include "hou/gl/GlContextSettings.hpp"

#include "hou/sys/video_mode.hpp"



using namespace hou;



namespace
{

class TestGlObjectHandle : public TestGlSingleContext {};

class ConcreteGlObjectHandle
  : public gl::ObjectHandle
{
public:
  ConcreteGlObjectHandle(GLuint name)
    : gl::ObjectHandle(name)
  {}
};



class ConcreteGlSharedObjectHandle
  : public gl::SharedObjectHandle
{
public:
  ConcreteGlSharedObjectHandle(GLuint name)
    : gl::SharedObjectHandle(name)
  {}
};



class ConcreteGlNonSharedObjectHandle
  : public gl::NonSharedObjectHandle
{
public:
  ConcreteGlNonSharedObjectHandle(GLuint name)
    : gl::NonSharedObjectHandle(name)
  {}
};

}



TEST_F(TestGlObjectHandle, Creation)
{
  ConcreteGlObjectHandle oh(1u);
  EXPECT_EQ(1u, oh.getName());
  EXPECT_NE(0u, oh.get_uid());

  ConcreteGlObjectHandle oh2(1u);
  EXPECT_NE(oh.get_uid(), oh2.get_uid());
}



TEST_F(TestGlObjectHandle, SharedCreation)
{
  ConcreteGlSharedObjectHandle oh(2u);
  EXPECT_EQ(2u, oh.getName());
  EXPECT_NE(0u, oh.get_uid());
  EXPECT_EQ(mContext.getSharingGroupUid(), oh.getOwningSharingGroupUid());

  ConcreteGlObjectHandle oh2(1u);
  EXPECT_NE(oh.get_uid(), oh2.get_uid());
}



TEST_F(TestGlObjectHandle, NonSharedCreation)
{
  ConcreteGlNonSharedObjectHandle oh(3u);
  EXPECT_EQ(3u, oh.getName());
  EXPECT_NE(0u, oh.get_uid());
  EXPECT_EQ(mContext.get_uid(), oh.getOwningContextUid());

  ConcreteGlObjectHandle oh2(1u);
  EXPECT_NE(oh.get_uid(), oh2.get_uid());
}



TEST_F(TestGlObjectHandle, MoveConstructor)
{
  ConcreteGlObjectHandle ohDummy(1u);
  ConcreteGlObjectHandle oh(std::move(ohDummy));
  uint32_t ohUidRef = oh.get_uid();
  EXPECT_EQ(0u, ohDummy.getName());
  EXPECT_EQ(0u, ohDummy.get_uid());
  EXPECT_EQ(1u, oh.getName());
  EXPECT_EQ(ohUidRef, oh.get_uid());
}



TEST_F(TestGlObjectHandle, SharedMoveConstructor)
{
  ConcreteGlSharedObjectHandle ohDummy(1u);
  ConcreteGlSharedObjectHandle oh(std::move(ohDummy));
  uint32_t ohUidRef = oh.get_uid();
  EXPECT_EQ(0u, ohDummy.getName());
  EXPECT_EQ(0u, ohDummy.get_uid());
  EXPECT_EQ(mContext.getSharingGroupUid(), ohDummy.getOwningSharingGroupUid());
  EXPECT_EQ(1u, oh.getName());
  EXPECT_EQ(ohUidRef, oh.get_uid());
  EXPECT_EQ(mContext.getSharingGroupUid(), oh.getOwningSharingGroupUid());
}



TEST_F(TestGlObjectHandle, NonSharedMoveConstructor)
{
  ConcreteGlNonSharedObjectHandle ohDummy(1u);
  ConcreteGlNonSharedObjectHandle oh(std::move(ohDummy));
  uint32_t ohUidRef = oh.get_uid();
  EXPECT_EQ(0u, ohDummy.getName());
  EXPECT_EQ(0u, ohDummy.get_uid());
  EXPECT_EQ(mContext.get_uid(), ohDummy.getOwningContextUid());
  EXPECT_EQ(1u, oh.getName());
  EXPECT_EQ(ohUidRef, oh.get_uid());
  EXPECT_EQ(mContext.get_uid(), oh.getOwningContextUid());
}



TEST_F(TestGlObjectHandle, SharedOwnerUid)
{
  system_window w("Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w);
  gl::Context c2(gl::ContextSettings::Default, w, c1);
  gl::Context c3(gl::ContextSettings::Default, w);

  gl::Context::setCurrent(c1, w);
  ConcreteGlSharedObjectHandle sh1(0u);

  gl::Context::setCurrent(c2, w);
  ConcreteGlSharedObjectHandle sh2(0u);

  gl::Context::setCurrent(c3, w);
  ConcreteGlSharedObjectHandle sh3(0u);

  EXPECT_EQ(c1.getSharingGroupUid(), sh1.getOwningSharingGroupUid());
  EXPECT_EQ(c2.getSharingGroupUid(), sh2.getOwningSharingGroupUid());
  EXPECT_EQ(c3.getSharingGroupUid(), sh3.getOwningSharingGroupUid());

  EXPECT_EQ(sh1.getOwningSharingGroupUid(), sh2.getOwningSharingGroupUid());
  EXPECT_NE(sh1.getOwningSharingGroupUid(), sh3.getOwningSharingGroupUid());
  EXPECT_NE(sh2.getOwningSharingGroupUid(), sh3.getOwningSharingGroupUid());
}



TEST_F(TestGlObjectHandle, NonSharedOwnerUid)
{
  system_window w("Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w);
  gl::Context c2(gl::ContextSettings::Default, w, c1);
  gl::Context c3(gl::ContextSettings::Default, w);

  gl::Context::setCurrent(c1, w);
  ConcreteGlNonSharedObjectHandle nsh1(0u);

  gl::Context::setCurrent(c2, w);
  ConcreteGlNonSharedObjectHandle nsh2(0u);

  gl::Context::setCurrent(c3, w);
  ConcreteGlNonSharedObjectHandle nsh3(0u);

  EXPECT_EQ(c1.get_uid(), nsh1.getOwningContextUid());
  EXPECT_EQ(c2.get_uid(), nsh2.getOwningContextUid());
  EXPECT_EQ(c3.get_uid(), nsh3.getOwningContextUid());

  EXPECT_NE(nsh1.getOwningContextUid(), nsh2.getOwningContextUid());
  EXPECT_NE(nsh1.getOwningContextUid(), nsh3.getOwningContextUid());
  EXPECT_NE(nsh2.getOwningContextUid(), nsh3.getOwningContextUid());
}

