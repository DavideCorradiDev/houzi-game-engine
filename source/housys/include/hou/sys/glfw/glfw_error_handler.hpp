// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_GLFW_GLFW_ERROR_HANDLER_HPP
#define HOU_SYS_GLFW_GLFW_ERROR_HANDLER_HPP

#include "hou/cor/non_instantiable.hpp"

#include "hou/sys/sys_config.hpp"

#include <functional>
#include <map>



namespace hou
{

namespace prv
{

/** Stores callbacks for different glfw error handlers.
 */
class HOU_SYS_API glfw_error_handler : public non_instantiable
{
public:
  /** Callback type. */
  using callback_type = std::function<void(const char*)>;

public:
  /** Main callback function.
   *
   * This function checks if a callback for error has been registered and
   * eventually calls it.
   * If no callback has been registered, nothing happens.
   *
   * This function should be used as the callback for glfw errors.
   *
   * \param error the error code.
   *
   * \param description the error description.
   */
  static void callback(int error, const char* description);

  /** Sets a callback.
   *
   * If the callback was already set, it will be overwritten.
   * If passed nullptr, the callback will be removed.
   *
   * This function is not thread safe.
   *
   * \param error the error code.
   *
   * \param callback the callback function.
   * If nullptr, it simply removes the currently registered callback, if
   * present.
   */
  static void set_callback(int error, callback_type callback);

  /** Clear all callbacks.
   *
   * This function is not threads safe.
   */
  static void clear_callbacks();

private:
  static std::map<int, callback_type> s_callbacks;
};

}  // namespace prv

}  // namespace hou

#endif
