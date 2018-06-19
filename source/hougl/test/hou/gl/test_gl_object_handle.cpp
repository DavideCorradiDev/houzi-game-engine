// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_single_context.hpp"

#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_object_handle.hpp"

using namespace hou;



namespace
{

class test_gl_object_handle : public test_gl_single_context
{};



class concrete_gl_object_handle : public gl::object_handle
{
public:
  concrete_gl_object_handle(GLuint name)
    : gl::object_handle(name)
  {}
};



class concrete_gl_shared_object_handle : public gl::shared_object_handle
{
public:
  concrete_gl_shared_object_handle(GLuint name)
    : gl::shared_object_handle(name)
  {}
};



class concrete_gl_non_shared_object_handle : public gl::non_shared_object_handle
{
public:
  concrete_gl_non_shared_object_handle(GLuint name)
    : gl::non_shared_object_handle(name)
  {}
};

}  // namespace



TEST_F(test_gl_object_handle, creation)
{
  concrete_gl_object_handle oh(1u);
  EXPECT_EQ(1u, oh.get_name());
  EXPECT_NE(0u, oh.get_uid());

  concrete_gl_object_handle oh2(1u);
  EXPECT_NE(oh.get_uid(), oh2.get_uid());
}



TEST_F(test_gl_object_handle, shared_creation)
{
  concrete_gl_shared_object_handle oh(2u);
  EXPECT_EQ(2u, oh.get_name());
  EXPECT_NE(0u, oh.get_uid());
  EXPECT_EQ(
    m_context.get_sharing_group_uid(), oh.get_owning_sharing_group_uid());

  concrete_gl_object_handle oh2(1u);
  EXPECT_NE(oh.get_uid(), oh2.get_uid());
}



TEST_F(test_gl_object_handle, non_shared_creation)
{
  concrete_gl_non_shared_object_handle oh(3u);
  EXPECT_EQ(3u, oh.get_name());
  EXPECT_NE(0u, oh.get_uid());
  EXPECT_EQ(m_context.get_uid(), oh.get_owning_context_uid());

  concrete_gl_object_handle oh2(1u);
  EXPECT_NE(oh.get_uid(), oh2.get_uid());
}



TEST_F(test_gl_object_handle, move_constructor)
{
  concrete_gl_object_handle oh_dummy(1u);
  concrete_gl_object_handle oh(std::move(oh_dummy));
  gl::object_handle::uid_type oh_uid_ref = oh.get_uid();

  EXPECT_EQ(0u, oh_dummy.get_name());
  EXPECT_EQ(0u, oh_dummy.get_uid());
  EXPECT_EQ(1u, oh.get_name());
  EXPECT_EQ(oh_uid_ref, oh.get_uid());
}



TEST_F(test_gl_object_handle, shared_move_constructor)
{
  concrete_gl_shared_object_handle oh_dummy(1u);
  concrete_gl_shared_object_handle oh(std::move(oh_dummy));
  gl::object_handle::uid_type oh_uid_ref = oh.get_uid();

  EXPECT_EQ(0u, oh_dummy.get_name());
  EXPECT_EQ(0u, oh_dummy.get_uid());
  EXPECT_EQ(
    m_context.get_sharing_group_uid(), oh_dummy.get_owning_sharing_group_uid());
  EXPECT_EQ(1u, oh.get_name());
  EXPECT_EQ(oh_uid_ref, oh.get_uid());
  EXPECT_EQ(
    m_context.get_sharing_group_uid(), oh.get_owning_sharing_group_uid());
}



TEST_F(test_gl_object_handle, non_shared_move_constructor)
{
  concrete_gl_non_shared_object_handle oh_dummy(1u);
  concrete_gl_non_shared_object_handle oh(std::move(oh_dummy));
  gl::object_handle::uid_type oh_uid_ref = oh.get_uid();

  EXPECT_EQ(0u, oh_dummy.get_name());
  EXPECT_EQ(0u, oh_dummy.get_uid());
  EXPECT_EQ(m_context.get_uid(), oh_dummy.get_owning_context_uid());
  EXPECT_EQ(1u, oh.get_name());
  EXPECT_EQ(oh_uid_ref, oh.get_uid());
  EXPECT_EQ(m_context.get_uid(), oh.get_owning_context_uid());
}



TEST_F(test_gl_object_handle, shared_owner_uid)
{
  system_window w("Test", vec2u::zero());
  gl::context c1(gl::context_settings::get_default(), w);
  gl::context c2(gl::context_settings::get_default(), w, c1);
  gl::context c3(gl::context_settings::get_default(), w);

  gl::context::set_current(c1, w);
  concrete_gl_shared_object_handle sh1(0u);

  gl::context::set_current(c2, w);
  concrete_gl_shared_object_handle sh2(0u);

  gl::context::set_current(c3, w);
  concrete_gl_shared_object_handle sh3(0u);

  EXPECT_EQ(c1.get_sharing_group_uid(), sh1.get_owning_sharing_group_uid());
  EXPECT_EQ(c2.get_sharing_group_uid(), sh2.get_owning_sharing_group_uid());
  EXPECT_EQ(c3.get_sharing_group_uid(), sh3.get_owning_sharing_group_uid());

  EXPECT_EQ(
    sh1.get_owning_sharing_group_uid(), sh2.get_owning_sharing_group_uid());
  EXPECT_NE(
    sh1.get_owning_sharing_group_uid(), sh3.get_owning_sharing_group_uid());
  EXPECT_NE(
    sh2.get_owning_sharing_group_uid(), sh3.get_owning_sharing_group_uid());
}



TEST_F(test_gl_object_handle, non_shared_owner_uid)
{
  system_window w("Test", vec2u::zero());
  gl::context c1(gl::context_settings::get_default(), w);
  gl::context c2(gl::context_settings::get_default(), w, c1);
  gl::context c3(gl::context_settings::get_default(), w);

  gl::context::set_current(c1, w);
  concrete_gl_non_shared_object_handle nsh1(0u);

  gl::context::set_current(c2, w);
  concrete_gl_non_shared_object_handle nsh2(0u);

  gl::context::set_current(c3, w);
  concrete_gl_non_shared_object_handle nsh3(0u);

  EXPECT_EQ(c1.get_uid(), nsh1.get_owning_context_uid());
  EXPECT_EQ(c2.get_uid(), nsh2.get_owning_context_uid());
  EXPECT_EQ(c3.get_uid(), nsh3.get_owning_context_uid());

  EXPECT_NE(nsh1.get_owning_context_uid(), nsh2.get_owning_context_uid());
  EXPECT_NE(nsh1.get_owning_context_uid(), nsh3.get_owning_context_uid());
  EXPECT_NE(nsh2.get_owning_context_uid(), nsh3.get_owning_context_uid());
}
