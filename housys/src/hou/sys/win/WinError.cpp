// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/win/WinError.hpp"

#include "hou/sys/win/Win.hpp"

#include "hou/cor/CharacterEncodings.hpp"



namespace hou
{

std::string getLastWinErrorMessage()
{
  LPVOID lpMsgBuf = nullptr;
  DWORD ec = GetLastError();

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

  if(lpMsgBuf == nullptr)
  {
    return std::string();
  }
  else
  {
    // Convert Windows UNICODE encoding to utf-8 to store it in a std::string.
    std::string messageUtf8(convertEncoding<Wide, Utf8>((LPWSTR)lpMsgBuf));
    std::string winError = formatString(u8"Error code %d: %s", ec
      , messageUtf8.c_str());
    LocalFree(lpMsgBuf);
    // Remove the \r\n appended at the end.
    winError.resize(winError.size() - 2);
    return winError;
  }
}

}

