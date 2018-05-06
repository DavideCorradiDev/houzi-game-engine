// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_COR_EXCEPTIONS_HPP
#define HOU_COR_COR_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/cor/cor_export.hpp"



namespace hou
{

template <typename T>
class invalid_enum : public exception
{
  static_assert(std::is_enum<T>::value, "T must be an enum type.");

public:
  invalid_enum(const std::string& path, uint line, T enum_value);
};

class HOU_COR_API overflow_error : public exception
{
public:
  overflow_error(const std::string& path, uint line);
};

class HOU_COR_API underflow_error : public exception
{
public:
  underflow_error(const std::string& path, uint line);
};

class HOU_COR_API unreachable_code_error : public exception
{
public:
  unreachable_code_error(const std::string& path, uint line);
};

}  // namespace hou

#include "hou/cor/cor_exceptions.inl"

#endif
