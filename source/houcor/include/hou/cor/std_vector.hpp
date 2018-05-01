// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_STD_VECTOR_HPP
#define HOU_COR_STD_VECTOR_HPP

#include "hou/cor/cor_export.hpp"

#include "hou/cor/core_functions.hpp"

#include <vector>



namespace hou
{

/** Checks if the elements of two std::vector objects are close with the given
 * accuracy
 *
 * \tparam T the accuracy type. It must be a floating point type.
 *
 * \tparam U the element type.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \param acc the accuracy.
 *
 * \return the result of the check.
 */
template <typename T, typename U,
  typename Enable = std::enable_if_t<std::is_floating_point<T>::value>>
bool close(const std::vector<U>& lhs, const std::vector<U>& rhs,
  T acc = std::numeric_limits<T>::epsilon());

/** Outputs a std::vector to the given stream.
 *
 * \tparam T the element type.
 *
 * \param os the output stream.
 *
 * \param c the std::vector object.
 *
 * \return a reference to os.
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& c);

}  // namespace hou



#include "hou/cor/std_vector.inl"

#endif
