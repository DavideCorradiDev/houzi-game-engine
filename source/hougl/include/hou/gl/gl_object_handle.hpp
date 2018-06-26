// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_OBJECT_HANDLE_HPP
#define HOU_GL_GL_OBJECT_HANDLE_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/open_gl.hpp"

#include "hou/gl/gl_config.hpp"



namespace hou
{

namespace gl
{

/**
 * Base class for all OpenGL objects.
 */
class HOU_GL_API object_handle : public non_copyable
{
public:
  /**
   * Unique identifier type.
   */
  using uid_type = uid_generator::uid_type;

public:
  /**
   * Creates an object with the given name.
   *
   * The name uniquely identifies the actual OpenGL resources, meaning that two
   * object_handle objects with the same name would actually manage the same
   * object.
   *
   * For this reason, two object_handle objects of the same type should never
   * be created with the same name.
   *
   * \param the object name.
   */
  object_handle(GLuint name) noexcept;

  /**
   * Move constructor.
   *
   * \param other the other object.
   */
  object_handle(object_handle&& other) noexcept;

  /**
   * Destructor.
   */
  virtual ~object_handle() = 0;

  /**
   * Gets the object name.
   *
   * \return the object name.
   */
  GLuint get_name() const noexcept;

  /**
   * Gets the object unique identifier.
   *
   * \return the object unique identifier.
   */
  uid_type get_uid() const noexcept;

private:
  GLuint m_name;
  uid_type m_uid;
};



/**
 * Base class of all OpenGL objects that can be shared among contexts.
 */
class HOU_GL_API shared_object_handle : public object_handle
{
public:
  /**
   * Creates an object with the given name.
   *
   * \param the object name.
   */
  shared_object_handle(GLuint name);

  /**
   * Gets the unique identifier of the group of sharing contexts owning the
   * object.
   *
   * \return the unique identifier.
   */
  context::uid_type get_owning_sharing_group_uid() const noexcept;

private:
  context::uid_type m_owning_sharing_group_uid;
};



/**
 * Base class of all OpenGL objects that cannot be shared among contexts and
 * that are therefore owned by a single context.
 */
class HOU_GL_API non_shared_object_handle : public object_handle
{
public:
  /**
   * Creates an object with the given name.
   *
   * \param the object name.
   */
  non_shared_object_handle(GLuint name);

  /**
   * Gets the unique identifier of the owning context.
   *
   * \return the unique identifier.
   */
  context::uid_type get_owning_context_uid() const noexcept;

private:
  context::uid_type m_owning_context_uid;
};

}  // namespace gl

}  // namespace hou

#endif
