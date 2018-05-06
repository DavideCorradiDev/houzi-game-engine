// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SYS_EXCEPTIONS_HPP
#define HOU_SYS_SYS_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/sys/sys_export.hpp"



namespace hou
{

class HOU_SYS_API file_open_error : public exception
{
public:
  file_open_error(
    const std::string& path, uint line, const std::string& filepath);
};

class HOU_SYS_API file_close_error : public exception
{
public:
  file_close_error(
    const std::string& path, uint line);
};

class HOU_SYS_API file_read_error : public exception
{
public:
  file_read_error(const std::string& path, uint line);
};

class HOU_SYS_API file_write_error : public exception
{
public:
  file_write_error(const std::string& path, uint line);
};

class HOU_SYS_API file_cursor_error : public exception
{
public:
  file_cursor_error(const std::string& path, uint line);
};

class HOU_SYS_API image_read_error : public exception
{
public:
  image_read_error(
    const std::string& path, uint line, const std::string& filepath);
};

class HOU_SYS_API image_write_error : public exception
{
public:
  image_write_error(
    const std::string& path, uint line, const std::string& filepath);
};

}  // namespace hou

#endif
