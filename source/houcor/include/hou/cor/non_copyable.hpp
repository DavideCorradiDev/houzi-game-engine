// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_NONCOPYABLE_HPP
#define HOU_COR_NONCOPYABLE_HPP

#include "hou/cor/cor_config.hpp"



namespace hou
{

/**
 * Non copyable class.
 *
 * A class inheriting from non_copyable cannot be copied.
 */
class non_copyable
{
public:
  /**
   * Default constructor
   */
  non_copyable() noexcept = default;

  /**
   * Destructor
   */
  ~non_copyable() = default;

  /**
   * Move constructor
   */
  non_copyable(non_copyable&&) noexcept = default;

  /**
   * Move assignment operator.
   */
  non_copyable& operator=(non_copyable&&) = default;

  /**
   * Deleted copy constructor
   */
  non_copyable(const non_copyable&) = delete;

  /**
   * Deleted copy assignment operator.
   */
  non_copyable& operator=(const non_copyable&) = delete;
};

}  // namespace hou

#endif
