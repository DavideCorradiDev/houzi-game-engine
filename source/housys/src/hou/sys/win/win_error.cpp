// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/win/win_error.hpp"



namespace hou
{

namespace prv
{

os_error_code get_last_win_error_code() noexcept
{
  return GetLastError();
}

}  // namespace prv

}  // namespace hou
