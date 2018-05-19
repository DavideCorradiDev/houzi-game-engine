// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_STD_STRING_HPP
#define HOU_COR_STD_STRING_HPP

#include "hou/cor/cor_config.hpp"

#include <sstream>
#include <string>
#include <vector>



namespace hou
{

/** Replaces all occurrences of a given substring with another substring.
 *
 * \param s the string to be modified.
 *
 * \param from the substring to be replaced.
 *
 * \param to the substring that will replace from.
 *
 * \throws std::bad_alloc.
 *
 * \return the modified string.
 */
HOU_COR_API std::string replace_all(
  std::string s, const std::string& from, const std::string& to);

/** Escapes special characters in a regular expression.
 *
 * \param s the string to be modified.
 *
 * \throws std::bad_alloc.
 *
 * \return a string with all regular expression special characters escaped.
 */
HOU_COR_API std::string escape_regex(std::string s);

/** Fills a format string with the given format values.
 *
 * \tparam Args the format variables.
 *
 * \param s the string to be modified.
 *
 * \param args the format values.
 *
 * \throws std::bad_alloc.
 *
 * \return the formatted string.
 */
template <typename... Args>
std::string format_string(const std::string& s, Args... args);

/** Splits a string into all substrings delimited by a given character.
 *
 * The user must ensure that out is a valid iterator and that the associated
 * container can contain all generated substrings.
 *
 * \tparam OutputIterator the output iterator type.
 *
 * \param s the string th be split.
 *
 * \param delimiter the delimiting character.
 *
 * \param out an iterator to the output container into which to write the
 * substrings.
 *
 * \throws std::bad_alloc.
 *
 * \return an iterator pointing to the element following the last inserted.
 */
template <typename OutputIterator>
OutputIterator split_string(
  const std::string& s, char delimiter, OutputIterator out);

/** Converts an object into a string.
 *
 * The output stream operator must be defined for T and will be used to
 * generate the string.
 *
 * \tparam T the type of the object to be converted into a string.
 *
 * \param obj the object.
 *
 * \throws std::bad_alloc.
 *
 * \return the string resulting from the object conversion.
 */
template <typename T>
std::string to_string(const T& obj);

/** Converts a boolean into a string.
 *
 * The resulting string will be either "true" or "false".
 *
 * \param value the boolean value.
 *
 * \throws std::bad_alloc.
 *
 * \return the boolean converted to string.
 */
HOU_COR_API std::string to_string(bool value);

}  // namespace hou



#include "hou/cor/std_string.inl"

#endif
