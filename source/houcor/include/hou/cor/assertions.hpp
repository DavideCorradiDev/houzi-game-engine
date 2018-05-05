// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_ASSERTIONS_HPP
#define HOU_COR_ASSERTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/cor/cor_export.hpp"



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

#endif
