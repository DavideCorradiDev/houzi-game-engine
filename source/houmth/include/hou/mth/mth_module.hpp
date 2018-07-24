// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_MTH_MODULE_HPP
#define HOU_MTH_MTH_MODULE_HPP

#include "hou/cor/module.hpp"

#include "hou/mth/mth_config.hpp"



namespace hou
{

namespace prv
{

/**
 * Math module initialization manager implementation.
 */
class HOU_MTH_API mth_module_impl : public non_instantiable
{
public:
  /**
   * Retrieves the module name as string.
   *
   * \return the module name.
   */
  static std::string get_name();

  /**
   * Sets up the mthtem module.
   */
  static bool on_initialize();

  /**
   * Tears down the mthtem module.
   */
  static void on_terminate() noexcept;
};

}

/**
 * Math module initialization manager.
 */
using mth_module = module<prv::mth_module_impl>;

}  // namespace hou

#endif


