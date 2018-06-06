// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_COR_MODULE_HPP
#define HOU_COR_COR_MODULE_HPP

#include "hou/cor/module.hpp"

#include "hou/cor/cor_config.hpp"



namespace hou
{

namespace prv
{

/** Core module initialization manager implementation.
 */
class HOU_COR_API cor_module_impl : public non_instantiable
{
public:
  /** Retrieves the module name as string.
   *
   * \return the module name.
   */
  static std::string get_name();

  /** Sets up the cortem module.
   */
  static bool on_initialize();

  /** Tears down the cortem module.
   */
  static void on_terminate() noexcept;
};

}

/** Core module initialization manager.
 */
using cor_module = module<prv::cor_module_impl>;

}  // namespace hou

#endif

