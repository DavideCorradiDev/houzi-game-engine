// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUD_MODULE_HPP
#define HOU_AUD_AUD_MODULE_HPP

#include "hou/cor/module.hpp"

#include "hou/aud/aud_config.hpp"



namespace hou
{

namespace prv
{

/**
 * Aud module intializaton manager implementation.
 */
class HOU_AUD_API aud_module_impl : public non_instantiable
{
public:
  /**
   * Retrieves the module name as string.
   *
   * \return the module name.
   */
  static std::string get_name();

  /**
   * Sets up the audtem module.
   */
  static bool on_initialize();

  /**
   * Tears down the audtem module.
   */
  static void on_terminate() noexcept;
};

}

/**
 * Aud module intializaton manager.
 */
using aud_module = module<prv::aud_module_impl>;

}  // namespace hou

#endif

