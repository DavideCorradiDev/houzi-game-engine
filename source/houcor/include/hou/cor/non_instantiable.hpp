// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_NON_INSTANTIABLE_HPP
#define HOU_COR_NON_INSTANTIABLE_HPP



namespace hou
{

/** Non instantiable class.
 *
 *  a class inheriting from non_instantiable cannot be instantiated.
 */
class non_instantiable
{
  /** Deleted default constructor.
   */
  non_instantiable() = delete;

  /** Deleted copy constructor.
   */
  non_instantiable(const non_instantiable&) = delete;

  /** Deleted move constructor.
   */
  non_instantiable(non_instantiable&&) = delete;

  /** Deleted copy assignment operator.
   */
  non_instantiable& operator=(const non_instantiable&) = delete;

  /** Deleted move assignment operator.
   */
  non_instantiable& operator=(non_instantiable&&) = delete;

  /** Deleted destructor.
   */
  ~non_instantiable() = delete;
};

}

#endif

