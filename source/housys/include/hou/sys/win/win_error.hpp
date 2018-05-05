// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_WIN_WIN_ERROR_HPP
#define HOU_SYS_WIN_WIN_ERROR_HPP

#include "hou/sys/os_error.hpp"

#include "hou/sys/sys_export.hpp"



namespace hou
{

namespace prv
{

os_error_code get_last_win_error_code() noexcept;

}

}  // namespace hou



#define HOU_WIN_TERMINATE() \
  HOU_TERMINATE(::hou::prv::get_os_error_message(get_last_win_error_code()))

#define HOU_WIN_ERROR() \
  HOU_ERROR_N(os_error, get_last_win_error_code())

#define HOU_WIN_ASSERT(statement) \
  HOU_CHECK_TEMPLATE(statement, HOU_WIN_TERMINATE())

#define HOU_DEV_WIN_ASSERT(statement) \
  HOU_DEV_CHECK_TEMPLATE(statement, HOU_WIN_TERMINATE())

#define HOU_WIN_CHECK(statement) \
  HOU_CHECK_TEMPLATE(statement, HOU_WIN_ERROR())

#define HOU_DEV_WIN_CHECK(statement) \
  HOU_DEV_CHECK_TEMPLATE(statement, HOU_WIN_ERROR())

#endif
