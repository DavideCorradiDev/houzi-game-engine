// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/assertions.hpp"



namespace hou
{

assertion_violation::assertion_violation(const std::string& path, uint line,
  const std::string& message, const std::string& condition)
  : exception(path, line,
      format_string(u8"%s (%s).", message.c_str(), condition.c_str()))
{}



precondition_violation::precondition_violation(
  const std::string& path, uint line, const std::string& condition)
  : assertion_violation(
      path, line, u8"A precondition has been violated", condition)
{}



postcondition_violation::postcondition_violation(
  const std::string& path, uint line, const std::string& condition)
  : assertion_violation(
      path, line, u8"A postcondition has been violated", condition)
{}



invariant_violation::invariant_violation(
  const std::string& path, uint line, const std::string& condition)
  : assertion_violation(
      path, line, u8"An invariant has been violated", condition)
{}

}  // namespace hou
