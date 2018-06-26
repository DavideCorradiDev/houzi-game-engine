// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GFX_MODULE_HPP
#define HOU_GFX_GFX_MODULE_HPP

#include "hou/cor/module.hpp"

#include "hou/gfx/gfx_config.hpp"



namespace hou
{

namespace prv
{

/**
 * Aud module intializaton manager implementation.
 */
class HOU_GFX_API gfx_module_impl : public non_instantiable
{
public:
  /**
   * Retrieves the module name as string.
   *
   * \return the module name.
   */
  static std::string get_name();

  /**
   * Sets up the gfxtem module.
   */
  static bool on_initialize();

  /**
   * Tears down the gfxtem module.
   */
  static void on_terminate() noexcept;
};

}

/**
 * Aud module intializaton manager.
 */
using gfx_module = module<prv::gfx_module_impl>;

}  // namespace hou

#endif


