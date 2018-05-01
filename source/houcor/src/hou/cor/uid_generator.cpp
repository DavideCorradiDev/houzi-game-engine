// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/uid_generator.hpp"

#include "hou/cor/cor_error.hpp"
#include "hou/cor/error.hpp"

#include <limits>



namespace hou
{

uid_generator::uid_generator(uint32_t starting_value)
  : m_counter(starting_value)
{}



uint32_t uid_generator::generate()
{
  HOU_RUNTIME_CHECK(m_counter != std::numeric_limits<uint32_t>::max(),
    get_text(cor_error::overflow));
  return m_counter.fetch_add(1);
}

}  // namespace hou
