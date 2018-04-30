// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/win/win_error.hpp"

#include "hou/sys/win/win.hpp"

#include "hou/cor/character_encodings.hpp"



namespace hou
{

std::string get_last_win_error_message()
{
  LPVOID lpMsgBuf = nullptr;
  DWORD ec = GetLastError();

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
    return std::string();
  }
  else
  {
    // Convert Windows UNICODE encoding to utf-8 to store it in a std::string.
    std::string messageUtf8(convert_encoding<wide, utf8>((LPWSTR)lpMsgBuf));
    std::string winError
      = format_string(u8"Error code %d: %s", ec, messageUtf8.c_str());
    LocalFree(lpMsgBuf);
    // Remove the \r\n appended at the end.
    winError.resize(winError.size() - 2);
    return winError;
  }
}

}  // namespace hou
