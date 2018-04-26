// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_NON_INSTANTIABLE_HPP
#define HOU_COR_NON_INSTANTIABLE_HPP



namespace hou
{

/** Non instantiable class.
 *
 *  A class inheriting from NonInstantiable cannot be instantiated.
 */
class NonInstantiable
{
  /** Deleted default constructor.
   */
  NonInstantiable() = delete;

  /** Deleted copy constructor.
   */
  NonInstantiable(const NonInstantiable&) = delete;

  /** Deleted move constructor.
   */
  NonInstantiable(NonInstantiable&&) = delete;

  /** Deleted copy assignment operator.
   */
  NonInstantiable& operator=(const NonInstantiable&) = delete;

  /** Deleted move assignment operator.
   */
  NonInstantiable& operator=(NonInstantiable&&) = delete;

  /** Deleted destructor.
   */
  ~NonInstantiable() = delete;
};

}

#endif

