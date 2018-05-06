// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/assertions.hpp"



namespace hou
{

precondition_violation::precondition_violation(
  const std::string& path, uint line)
  : exception(path, line, u8"A precondition has been violated.")
{}



postcondition_violation::postcondition_violation(
  const std::string& path, uint line)
  : exception(path, line, u8"A postcondition has been violated.")
{}



invariant_violation::invariant_violation(const std::string& path, uint line)
  : exception(path, line, u8"An invariant has been violated.")
{}



unreachable_error::unreachable_error(const std::string& path, uint line)
  : exception(path, line, u8"An unreachable part of code has been reached.")
{}

}  // namespace hou
