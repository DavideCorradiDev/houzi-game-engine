// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_TEXT_INPUT_HPP
#define HOU_SYS_TEXT_INPUT_HPP

#include "hou/sys/sys_config.hpp"

#include "hou/mth/rectangle_fwd.hpp"



namespace hou
{

namespace text_input
{

void start();
void stop();
bool is_active();
void set_rect(const recti& rect);

}  // namespace text_input

}  // namespace hou

#endif
