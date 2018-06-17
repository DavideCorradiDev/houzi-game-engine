// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SYSTEM_WINDOW_HPP
#define HOU_SYS_SYSTEM_WINDOW_HPP

#include "hou/sys/sys_config.hpp"

#include "hou/sys/window.hpp"



namespace hou
{

/**
 * Represents a window.
 */
class HOU_SYS_API system_window final : public window
{
public:
  /**
   * Creates a window.
   *
   * \param title the window title.
   *
   * \param size the size of the window client area.
   */
  system_window(const std::string& title, const vec2u& size);
};

}  // namespace hou

#endif
