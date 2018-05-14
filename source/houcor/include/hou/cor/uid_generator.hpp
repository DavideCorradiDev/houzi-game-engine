// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_UID_GENERATOR_HPP
#define HOU_COR_UID_GENERATOR_HPP

#include <atomic>

#include "hou/cor/cor_export.hpp"



namespace hou
{

/** a thread safe unique identifier generator.
 */
class HOU_COR_API uid_generator
{
public:
  /** Creates the generator.
   *
   * The constructor is not thread safe.
   */
  uid_generator(uint32_t starting_value) noexcept;

  /** Generates a unique identifier.
   *
   * Calling this function is thread safe.
   *
   * \throws hou::overflow_error if the uid generator counter overflows.
   */
  uint32_t generate();

private:
  std::atomic<uint32_t> m_counter;
};

}  // namespace hou

#endif
