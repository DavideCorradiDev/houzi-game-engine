// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_MODULE_HPP
#define HOU_GL_GL_MODULE_HPP

#include "hou/cor/module.hpp"

#include "hou/gl/gl_config.hpp"



namespace hou
{

namespace prv
{

/**
 * GL module initialization manager implementation.
 */
class HOU_GL_API gl_module_impl : public non_instantiable
{
public:
  /**
   * Retrieves the module name as string.
   *
   * \return the module name.
   */
  static std::string get_name();

  /**
   * Sets up the gltem module.
   */
  static bool on_initialize();

  /**
   * Tears down the gltem module.
   */
  static void on_terminate() noexcept;
};

}

/**
 * GL module initialization manager.
 */
using gl_module = module<prv::gl_module_impl>;

}  // namespace hou

#endif
