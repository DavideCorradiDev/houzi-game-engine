// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_CONTEXT_HPP
#define HOU_AL_AL_CONTEXT_HPP

#include "hou/al/al_device.hpp"
#include "hou/al/open_al.hpp"

#include "hou/al/al_config.hpp"

#include "hou/cor/non_copyable.hpp"



namespace hou
{

namespace al
{

/**
 * Represents an OpenAL context.
 *
 * The context is an object containing OpenAL related global state.
 *
 * A context must be created and set as current in order to be able to perform
 * any OpenAL call.
 * A single context is sufficient, but it is possible to create multiple context
 * objects.
 * The current context is set at the application level, meaning that all threads
 * share the same current context.
 * If the library was build with HOU_ENABLE_AL_CHECKS, an exception will be
 * thrown if any OpenAL operation in the houal library is performed without a
 * current context.
 *
 * OpenAL objects created when a context is current belong either to that
 * context, or to the associated device.
 * If the library was built with HOU_ENABLE_AL_CHECKS, an exception will be
 * thrown if an operation is performed on an object not owned by the current
 * context or device.
 */
class HOU_AL_API context : public non_copyable
{
public:
  /**
   * Underlying implementation type.
   */
  using impl_type = ALCcontext;

  /**
   * Unique identifier type.
   */
  using uid_type = uint32_t;

public:
  /**
   * Sets the current context.
   *
   * Only one context can be current in the whole application.
   *
   * Calls to this function are thread safe.
   *
   * \param ctx the context to make current.
   *
   * \throws hou::al::context_switch_error in case setting the context failed.
   */
  static void set_current(context& ctx);

  /**
   * Unsets the current context.
   *
   * After a call to this function, there will be no current context, meaning
   * that no OpenAL call can be performed.
   *
   * Calls to this function are thread-safe.
   *
   * \throws hou::al::context_switch_error in case setting the context failed.
   */
  static void unset_current();

  /**
   * Gets the current context.
   *
   * Calls to this function are thread-safe.
   *
   * \return a pointer to the current context, or nullptr if there is no
   * current context.
   */
  static context* get_current();

public:
  /**
   * Creates a context.
   *
   * \param dev the device.
   *
   * \throws hou::al::context_creation_error in case of an error.
   */
  context(device& dev);

  /**
   * Move constructor.
   *
   * \param other the other context.
   */
  context(context&& other) noexcept;

  /**
   * Destructor.
   */
  ~context();

  /**
   * Gets a reference to the underlying implementation.
   *
   * \return a reference to the underlying implementation.
   */
  const impl_type* get_impl() const noexcept;

  /**
   * Gets a reference to the underlying implementation.
   *
   * \return a reference to the underlying implementation.
   */
  impl_type* get_impl() noexcept;

  /**
   * Gets the context unique identifier.
   *
   * \return the context unique identifier.
   */
  uid_type get_uid() const noexcept;

  /**
   * Gets the associated device unique identifier.
   *
   * \return the associated device unique identifier.
   */
  device::uid_type get_device_uid() const noexcept;

  /**
   * Checks whether this context is current in the current thread.
   *
   * \return true if the context is current, false otherwise.
   */
  bool is_current() const;

private:
  ALCcontext* m_context;
  uid_type m_uid;
  device::uid_type m_device_uid;
};

}  // namespace al

}  // namespace hou

#endif