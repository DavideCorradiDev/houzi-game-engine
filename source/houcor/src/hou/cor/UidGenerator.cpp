// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/UidGenerator.hpp"

#include "hou/cor/CorError.hpp"
#include "hou/cor/Error.hpp"

#include <limits>



namespace hou
{

UidGenerator::UidGenerator(uint32_t startingValue)
  : mCounter(startingValue)
{}



uint32_t UidGenerator::generate()
{
  HOU_RUNTIME_CHECK(mCounter != std::numeric_limits<uint32_t>::max()
    , getText(CorError::Overflow));
  return mCounter.fetch_add(1);
}

}

