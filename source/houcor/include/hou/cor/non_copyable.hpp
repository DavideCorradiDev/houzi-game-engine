// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_NONCOPYABLE_HPP
#define HOU_COR_NONCOPYABLE_HPP

#include "hou/cor/cor_config.hpp"



namespace hou
{

/** Non copyable class.
 *
 * A class inheriting from non_copyable cannot be copied.
 */
class non_copyable
{
public:
  /** default constructor
   */
  non_copyable() noexcept
  {}

  /** Destructor
   */
  virtual ~non_copyable()
  {}

  /** Deleted copy constructor
   */
  non_copyable(const non_copyable&) = delete;

  /** Defaulted move constructor
   */
  non_copyable(non_copyable&&) = default;

  /** Deleted copy assignment operator.
   */
  non_copyable& operator=(const non_copyable&) = delete;

  /** Defaulted move assignment operator.
   */
  non_copyable& operator=(non_copyable&&) = default;
};

}  // namespace hou

#endif
