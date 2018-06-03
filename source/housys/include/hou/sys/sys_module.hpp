// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SYS_MODULE_HPP
#define HOU_SYS_SYS_MODULE_HPP

#include "hou/cor/module.hpp"

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
  /** Sets up the system module.
   */
  static bool on_setup();

  /** Tears down the system module.
   */
  static void on_teardown() noexcept;
};

}

/** System module initialization manager.
 */
using sys_module = module<prv::sys_module_impl>;

}  // namespace hou

#endif
