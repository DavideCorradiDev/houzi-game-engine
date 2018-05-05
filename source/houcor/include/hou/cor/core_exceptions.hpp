// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_CORE_EXCEPTIONS_HPP
#define HOU_COR_CORE_EXCEPTIONS_HPP

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

class HOU_COR_API numeric_overflow : public exception
{
public:
  numeric_overflow(const std::string& path, uint line);
};

class HOU_COR_API numeric_underflow : public exception
{
public:
  numeric_underflow(const std::string& path, uint line);
};

}  // namespace hou

#include "hou/cor/core_exceptions.inl"

#endif
