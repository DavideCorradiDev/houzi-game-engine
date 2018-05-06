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
    return u8"Unknown error.";
  }
  else
  {
    // Convert Windows UNICODE encoding to utf-8 to store it in a std::string.
    std::string message_utf8(convert_encoding<wide, utf8>((LPWSTR)lpMsgBuf));
    LocalFree(lpMsgBuf);
    // Remove the \r\n appended at the end.
    message_utf8.resize(message_utf8.size() - 2);
    return message_utf8;
  }
}

}  // namespace hou
