// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_UID_GENERATOR_HPP
#define HOU_COR_UID_GENERATOR_HPP

#include <atomic>

#include "hou/cor/cor_config.hpp"



namespace hou
{

/**
 * A thread safe unique identifier generator.
 */
class HOU_COR_API uid_generator
{
public:
  /**
   * Unique identifier type.
   */
  using uid_type = uint32_t;

public:
  /**
   * Creates the generator.
   *
   * The constructor is not thread safe.
   */
  uid_generator(uid_type starting_value) noexcept;

  /**
   * Generates a unique identifier.
   *
   * Calling this function is thread safe.
   *
   * \throws hou::overflow_error if the uid generator counter overflows.
   */
  uid_type generate();

private:
  std::atomic<uid_type> m_counter;
};

}  // namespace hou

#endif
