// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_STD_ARRAY_HPP
#define HOU_COR_STD_ARRAY_HPP

#include "hou/cor/cor_export.hpp"

#include "hou/cor/core_functions.hpp"

#include <array>



namespace hou
{

/** Checks if the elements of two std::array objects are close with the given
 *  accuracy
 *
 *  \tparam T the accuracy type. It must be a floating point type.
 *  \tparam U the element type.
 *  \tparam N the size of the std::array objects.
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \param acc the accuracy.
 *  \return the result of the check.
 */
template <typename T, typename U, std::size_t N
  , typename Enable = std::enable_if_t<std::is_floating_point<T>::value>>
  bool close(const std::array<U, N>& lhs, const std::array<U, N>& rhs
  , T acc = std::numeric_limits<T>::epsilon());

/** Outputs a std::array to the given stream.
 *
 *  \tparam T the element type.
 *  \tparam N the size of the std::array object.
 *  \param os the output stream.
 *  \param c the std::array object.
 *  \return a reference to os.
 */
template <typename T, std::size_t N>
  std::ostream& operator<<(std::ostream& os, const std::array<T, N>& c);

}

#include "hou/cor/std_array.inl"

#endif

