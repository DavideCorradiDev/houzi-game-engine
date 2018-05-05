// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_OS_ERROR_HPP
#define HOU_SYS_OS_ERROR_HPP

#include "hou/cor/exception.hpp"

#include "hou/sys/sys_export.hpp"


#if defined(HOU_SYSTEM_WINDOWS)

#include "hou/sys/win/win.hpp"

namespace hou
{
using os_error_code = DWORD;
}

#endif




namespace hou
{

class HOU_SYS_API os_error : public exception
{
public:
  os_error(const std::string& path, uint line, os_error_code ec);
};

HOU_SYS_API std::string get_os_error_message(os_error_code ec);

}

#endif
