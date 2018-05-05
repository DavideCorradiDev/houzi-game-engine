// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_CORE_EXCEPTIONS_HPP
#define HOU_COR_CORE_EXCEPTIONS_HPP

#include "hou/cor/cor_export.hpp"

#include "hou/cor/exception.hpp"



namespace hou
{

class HOU_COR_API precondition_violation : public exception
{
public:
  precondition_violation(const std::string& path, uint line);
};

class HOU_COR_API postcondition_violation : public exception
{
public:
  postcondition_violation(const std::string& path, uint line);
};

class HOU_COR_API invariant_violation : public exception
{
public:
  invariant_violation(const std::string& path, uint line);
};

template <typename T>
class invalid_enum : public exception
{
  static_assert(std::is_enum<T>::value, "T must be an enum type.");
public:
  invalid_enum(const std::string& path, uint line, T enum_value);
};

}  // namespace hou

#define HOU_PRECOND(condition) HOU_CHECK_0(condition, precondition_violation)

#define HOU_DEV_PRECOND(condition)                                             \
  HOU_DEV_CHECK_0(condition, precondition_violation)

#define HOU_POSTCOND(condition) HOU_CHECK_0(condition, postcondition_violation)

#define HOU_DEV_POSTCOND(condition)                                            \
  HOU_DEV_CHECK_0(condition, postcondition_violation)

#define HOU_INVARIANT(condition) HOU_CHECK_0(condition, invariant_violation)

#define HOU_DEV_INVARIANT(condition)                                           \
  HOU_DEV_CHECK_0(condition, invariant_violation)

#include "hou/cor/core_exceptions.inl"

#endif
