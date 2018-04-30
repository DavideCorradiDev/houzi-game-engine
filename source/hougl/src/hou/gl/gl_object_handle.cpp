// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_object_handle.hpp"

#include "hou/gl/gl_check.hpp"
#include "hou/gl/gl_context.hpp"

#include "hou/cor/uid_generator.hpp"



namespace hou
{

namespace gl
{

namespace
{

uint32_t generate_uid();



uint32_t generate_uid()
{
  static uid_generator gen(1u);
  return gen.generate();
}

}  // namespace



object_handle::object_handle(GLuint name)
  : non_copyable()
  , m_name(name)
  , m_uid(generate_uid())
{}



object_handle::object_handle(object_handle&& other)
  : non_copyable()
  , m_name(other.m_name)
  , m_uid(other.m_uid)
{
  other.m_name = 0u;
  other.m_uid = 0u;
}



object_handle::~object_handle()
{}



GLuint object_handle::get_name() const
{
  return m_name;
}



uint32_t object_handle::get_uid() const
{
  return m_uid;
}



shared_object_handle::shared_object_handle(GLuint name)
  : object_handle(name)
  , m_owning_sharing_group_uid(0u)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  m_owning_sharing_group_uid = context::getCurrent()->get_sharing_group_uid();
}



shared_object_handle::shared_object_handle(shared_object_handle&& other)
  : object_handle(std::move(other))
  , m_owning_sharing_group_uid(other.m_owning_sharing_group_uid)
{}



shared_object_handle::~shared_object_handle()
{}



uint32_t shared_object_handle::get_owning_sharing_group_uid() const
{
  return m_owning_sharing_group_uid;
}



non_shared_object_handle::non_shared_object_handle(GLuint name)
  : object_handle(name)
  , m_owning_context_uid(0u)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  m_owning_context_uid = context::getCurrent()->get_uid();
}



non_shared_object_handle::non_shared_object_handle(
  non_shared_object_handle&& other)
  : object_handle(std::move(other))
  , m_owning_context_uid(other.m_owning_context_uid)
{}



non_shared_object_handle::~non_shared_object_handle()
{}



uint32_t non_shared_object_handle::get_owning_context_uid() const
{
  return m_owning_context_uid;
}

}  // namespace gl

}  // namespace hou
