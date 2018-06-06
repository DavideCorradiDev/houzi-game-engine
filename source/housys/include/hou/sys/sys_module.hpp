// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SYS_MODULE_HPP
#define HOU_SYS_SYS_MODULE_HPP

#include "hou/cor/module.hpp"

#include "hou/cor/std_string.hpp"

#include "hou/sys/sys_config.hpp"



namespace hou
{

namespace prv
{

/** System module initialization manager implementation.
 */
class HOU_SYS_API sys_module_impl : public non_instantiable
{
public:
  /** Retrieves the module name as string.
   *
   * \return the module name.
   */
  static std::string get_name();

  /** Sets up the system module.
   */
  static bool on_initialize();

  /** Tears down the system module.
   */
  static void on_terminate() noexcept;
};

}

/** System module initialization manager.
 */
using sys_module = module<prv::sys_module_impl>;

}  // namespace hou

#endif
