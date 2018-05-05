// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/core_exceptions.hpp"



namespace hou
{

precondition_violated::precondition_violated(const std::string& path, uint line)
  : exception(path, line, u8"A precondition has been violated.")
{}

postcondition_violated::postcondition_violated(
  const std::string& path, uint line)
  : exception(path, line, u8"A postcondition has been violated.")
{}

invariant_violated::invariant_violated(const std::string& path, uint line)
  : exception(path, line, u8"An invariant has been violated.")
{}

}  // namespace hou
