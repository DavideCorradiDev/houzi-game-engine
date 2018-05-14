// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_OS_ERROR_HPP
#define HOU_SYS_OS_ERROR_HPP

#include "hou/sys/sys_config.hpp"

#include "hou/cor/exception.hpp"



#if defined(HOU_SYSTEM_WINDOWS)

#include "hou/sys/win/win.hpp"

namespace hou
{
using os_error_code = DWORD;
}

#endif




namespace hou
{

/** OS error.
 *
 * This exception is thrown when an operating system API call fails.
 * The actual meaning of this exception depends on the current OS.
 */
class HOU_SYS_API os_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   *
   * \param ec the error code.
   */
  os_error(const std::string& path, uint line, os_error_code ec);
};

/** Converts an error code into a human readable error message.
 *
 * The supported error code values and the output depend on the current OS.
 *
 * \throws std::bad_alloc.
 *
 * \param ec the error code.
 */
HOU_SYS_API std::string get_os_error_message(os_error_code ec);

}

#endif
