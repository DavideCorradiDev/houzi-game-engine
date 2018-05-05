// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/os_error.hpp"

#include "hou/cor/character_encodings.hpp"



namespace hou
{

std::string get_os_error_message(os_error_code ec)
{
  LPVOID lpMsgBuf = nullptr;

  // clang-format off
  FormatMessageW
    ( FORMAT_MESSAGE_ALLOCATE_BUFFER
    | FORMAT_MESSAGE_FROM_SYSTEM
    | FORMAT_MESSAGE_IGNORE_INSERTS
    , nullptr
    , ec
    , MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)
    , (LPWSTR)&lpMsgBuf
    , 0
    , nullptr);
  // clang-format on

  if(lpMsgBuf == nullptr)
  {
    return format_string(u8"OS error with code %d: unrecognized code.", ec);
  }
  else
  {
    // Convert Windows UNICODE encoding to utf-8 to store it in a std::string.
    std::string messageUtf8(convert_encoding<wide, utf8>((LPWSTR)lpMsgBuf));
    std::string winError
      = format_string(u8"OS error with code %d: %s", ec, messageUtf8.c_str());
    LocalFree(lpMsgBuf);
    // Remove the \r\n appended at the end.
    winError.resize(winError.size() - 2);
    return winError;
  }
}

}  // namespace hou
