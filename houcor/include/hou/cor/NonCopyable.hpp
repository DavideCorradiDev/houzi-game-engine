// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_COR_NONCOPYABLE_HPP
#define HOU_COR_NONCOPYABLE_HPP



namespace hou
{

/** Non copyable class.
 *
 *  A class inheriting from NonCopyable cannot be copied.
 */
class NonCopyable
{
public:
  /** Default constructor
   */
  NonCopyable() {}

  /** Destructor
   */
  virtual ~NonCopyable() {}

  /** Deleted copy constructor
   */
  NonCopyable(const NonCopyable&) = delete;

  /** Deleted move constructor
   */
  NonCopyable(NonCopyable&&) = delete;

  /** Deleted copy assignment operator.
   */
  NonCopyable& operator=(const NonCopyable&) = delete;

  /** Deleted move assignment operator.
   */
  NonCopyable& operator=(NonCopyable&&) = delete;
};

}

#endif

