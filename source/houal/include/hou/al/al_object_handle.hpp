// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_OBJECT_HANDLE_HPP
#define HOU_AL_AL_OBJECT_HANDLE_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_device.hpp"
#include "hou/al/open_al.hpp"

#include "hou/al/al_config.hpp"



namespace hou
{

namespace al
{

/**
 * Base class for all OpenAL objects.
 */
class HOU_AL_API object_handle : public non_copyable
{
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
  object_handle(ALuint name) noexcept;

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
  ALuint get_name() const noexcept;

private:
  ALuint m_name;
};



/**
 * Base class of all OpenAL objects owned by a device.
 */
class HOU_AL_API device_owned_object_handle : public object_handle
{
public:
  /**
   * Creates an object with the given name.
   *
   * \param the object name.
   */
  device_owned_object_handle(ALuint name);

  /**
   * Gets the unique identifier of the owning device.
   *
   * \param the unique identifier.
   */
  device::uid_type get_owning_device_uid() const noexcept;

private:
  device::uid_type m_owning_device_uid;
};



class HOU_AL_API context_owned_object_handle : public object_handle
{
public:
  /**
   * Creates an object with the given name.
   *
   * \param the object name.
   */
  context_owned_object_handle(ALuint name);

  /**
   * Gets the unique identifier of the owning context.
   *
   * \param the unique identifier.
   */
  context::uid_type get_owning_context_uid() const noexcept;

private:
  context::uid_type m_owning_context_uid;
};

}  // namespace al

}  // namespace hou

#endif
