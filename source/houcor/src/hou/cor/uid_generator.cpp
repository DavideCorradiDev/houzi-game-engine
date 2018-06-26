// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/uid_generator.hpp"

#include "hou/cor/cor_exceptions.hpp"

#include <limits>



namespace hou
{

uid_generator::uid_generator(uid_type starting_value) noexcept
  : m_counter(starting_value)
{}



uid_generator::uid_type uid_generator::generate()
{
  HOU_CHECK_0(
    m_counter != std::numeric_limits<uid_type>::max(), overflow_error);
  return m_counter.fetch_add(1);
}

}  // namespace hou
