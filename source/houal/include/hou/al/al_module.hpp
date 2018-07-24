// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_MODULE_HPP
#define HOU_AL_AL_MODULE_HPP

#include "hou/cor/module.hpp"

#include "hou/al/al_config.hpp"



namespace hou
{

namespace prv
{

/**
 * AL module initialization manager implementation.
 */
class HOU_AL_API al_module_impl : public non_instantiable
{
public:
  /**
   * Retrieves the module name as string.
   *
   * \return the module name.
   */
  static std::string get_name();

  /**
   * Sets up the altem module.
   */
  static bool on_initialize();

  /**
   * Tears down the altem module.
   */
  static void on_terminate() noexcept;
};

}

/**
 * AL module initialization manager.
 */
using al_module = module<prv::al_module_impl>;

}  // namespace hou

#endif
