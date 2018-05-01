// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_COR_UTILS_HPP
#define HOU_COR_COR_UTILS_HPP

#include "hou/cor/cor_export.hpp"

#include "hou/cor/basic_types.hpp"

#include <iostream>
#include <limits>



namespace hou
{

/** Checks if two floating point numbers are equal with the given accuracy.
 *
 * A specialization is provided only for float and double.
 *
 * \tparam T the floating point type.
 *
 * \tparam Enable enabling parameter.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \param acc the accuracy.
 *
 * \return the result of the check.
 */
template <
  typename T,
  typename Enable = std::enable_if_t<std::is_floating_point<T>::value>>
HOU_COR_API bool close(T lhs, T rhs, T acc = std::numeric_limits<T>::epsilon());

/** Checks if the elements of two containers are close with the given
 * accuracy.
 *
 * The first container is fully defined by the range provided by begin1 and
 * last1. The second container is defined by the range provided by begin2
 * and begin2 + (end1 - begin1). The user must ensure that the size of the
 * second container is at least the size of the first container. If the second
 * container contains more elements than the first one, only the first elements
 * will be compared.
 *
 * \tparam T the accuracy type.
 *
 * \tparam InputIt1 the iterator type of the first container.
 *
 * \tparam InputIt2 the iterator type of the second container.
 *
 * \tparam Enable enabling parameter.
 *
 * \param begin1 the iterator to the begin of the first container.
 *
 * \param end1 the iterator to the end of the first container.
 *
 * \param begin2 the iterator to the begin of the second container.
 *
 * \param acc the accuracy.
 *
 * \return the result of the check.
 */
template <
  typename T, typename InputIt1, typename InputIt2,
  typename Enable = std::enable_if_t<std::is_floating_point<T>::value>>
bool container_close(
  InputIt1 begin1, InputIt1 end1, InputIt2 begin2,
  T acc = std::numeric_limits<T>::epsilon());

/** Outputs a container to the given stream.
 *
 * \tparam Iterator the input iterator type.
 *
 * \param os the output stream.
 *
 * \param begin the iterator to the begin of the input container.
 *
 * \param end the iterator to the end of the input container.
 *
 * \return a reference to os.
 */
template <typename Iterator>
std::ostream& container_stream(std::ostream& os, Iterator begin, Iterator end);

}  // namespace hou



#include "hou/cor/core_functions.inl"

#endif
