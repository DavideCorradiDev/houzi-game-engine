// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_CHARACTER_ENCODINGS_HPP
#define HOU_COR_CHARACTER_ENCODINGS_HPP

#include "hou/cor/non_instantiable.hpp"

#include "hou/cor/assertions.hpp"

#include "hou/cor/cor_config.hpp"

#include <array>
#include <limits>



namespace hou
{

/** Unicode code point. */
using code_point = char32_t;

/** Container class for UTF-8 encoding functions
 */
class utf8 : public non_instantiable
{
public:
  /** UTF-8 code unit representation. */
  using code_unit = char;

public:
  /** Encodes the given code point into an UTF-8 code unit sequence.
   *
   * The user must ensure that out_first is a valid iterator and that the
   * container is large enough to contain the encoded code point.
   *
   * \tparam OutputIt the output iterator type.
   *
   * \param in the code point.
   *
   * \param out_first the begin of the output code unit sequence.
   *
   * \throws std::bad_alloc.
   *
   * \return an iterator to the code unit after the encoded code point.
   */
  template <typename OutputIt>
  static OutputIt encode(code_point in, OutputIt out_first);

  /** Decodes the first part of the given UTF-8 code unit sequence into a code
   * point.
   *
   * If the input iterator pair contains more than one encoded code point, the
   * first code point will be decoded and an iterator to the code unit after it
   * will be returned.
   *
   * \tparam InputIt the input iterator type.
   *
   * \param in_first the begin of the input code unit sequence.
   *
   * \param in_last the end of the input code unit sequence.
   *
   * \param out the output code point.
   *
   * \throws hou::precondition_violation if the given code unit sequence is
   * invalid.
   *
   * \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
  static InputIt decode(InputIt in_first, InputIt in_last, code_point& out);

  /** Returns an iterator to the next code point in the given UTF-8 code unit
   * sequence.
   *
   * If the given code unit sequence is not valid the returned iterator might
   * point to an invalid memory address.
   *
   * \tparam InputIt the input iterator type.
   *
   * \param in_first the begin of the input code unit sequence.
   *
   * \param in_last the end of the input code unit sequence.
   *
   * \throws hou::precondition_violation if the given code unit sequence is
   * invalid.
   *
   * \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
  static InputIt next(InputIt in_first, InputIt in_last);

  /** Counts the number of code points in the given UTF-8 code unit sequence.
   *
   * If the given code unit sequence is not valid the returned value has no
   * meaning.
   *
   * \tparam InputIt the input iterator type.
   *
   * \param in_first the begin of the input code unit sequence.
   *
   * \param in_last the end of the input code unit sequence.
   *
   * \throws hou::precondition_violation if the given code unit sequence is
   * invalid.
   *
   * \return the number of code points in the code unit sequence.
   */
  template <typename InputIt>
  static size_t count(InputIt in_first, InputIt in_last);

private:
  static inline size_t count_trailing_units(code_unit cu);
};

/** Container class for UTF-16 encoding functions
 */
class utf16 : public non_instantiable
{
public:
  /** UTF-16 code unit representation. */
  using code_unit = char16_t;

public:
  /** Encodes the given code point into an UTF-16 code unit sequence.
   *
   * The user must ensure that out_first points to a valid memory address and
   * that the container is large enough to contain the encoded code point.
   *
   * \tparam OutputIt the output iterator type.
   *
   * \param in the code point.
   *
   * \param out_first the begin of the output code unit sequence.
   *
   * \throws std::bad_alloc.
   *
   * \return an iterator to the code unit after the encoded code point.
   */
  template <typename OutputIt>
  static OutputIt encode(code_point in, OutputIt out_first);

  /** Decodes the first part of the given UTF-16 code unit sequence into a code
   * point.
   *
   * If the input iterator pair contains more than one encoded code point, the
   * first code point will be decoded and an iterator to the code unit after it
   * will be returned.
   *
   * \tparam InputIt the input iterator type.
   *
   * \param in_first the begin of the input code unit sequence.
   *
   * \param in_last the end of the input code unit sequence.
   *
   * \param out the output code point.
   *
   * \throws hou::precondition_violation if the given code unit sequence is
   * invalid.
   *
   * \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
  static InputIt decode(InputIt in_first, InputIt in_last, code_point& out);

  /** Returns an iterator to the next code point in the given UTF-16 code unit
   * sequence.
   *
   * If the given code unit sequence is not valid the returned iterator might
   * point to an invalid memory address.
   *
   * \tparam InputIt the input iterator type.
   *
   * \param in_first the begin of the input code unit sequence.
   *
   * \param in_last the end of the input code unit sequence.
   *
   * \throws hou::precondition_violation if the given code unit sequence is
   * invalid.
   *
   * \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
  static InputIt next(InputIt in_first, InputIt in_last);

  /** Counts the number of code points in the given UTF-16 code unit sequence.
   *
   * If the given code unit sequence is not valid the returned value has no
   * meaning.
   *
   * \tparam InputIt the input iterator type.
   *
   * \param in_first the begin of the input code unit sequence.
   *
   * \param in_last the end of the input code unit sequence.
   *
   * \throws hou::precondition_violation if the given code unit sequence is
   * invalid.
   *
   * \return the number of code points in the code unit sequence.
   */
  template <typename InputIt>
  static size_t count(InputIt in_first, InputIt in_last);
};

/** Container class for UTF-32 encoding functions
 */
class utf32 : public non_instantiable
{
public:
  /** UTF-32 code unit representation. */
  using code_unit = char32_t;

public:
  /** Encodes the given code point into an UTF-32 code unit sequence.
   *
   * The user must ensure that out_first points to a valid memory address and
   * that the container is large enough to contain the encoded code point.
   *
   * \tparam OutputIt the output iterator type.
   *
   * \param in the code point.
   *
   * \param out_first the begin of the output code unit sequence.
   *
   * \throws std::bad_alloc.
   *
   * \return an iterator to the code unit after the encoded code point.
   */
  template <typename OutputIt>
  static OutputIt encode(code_point in, OutputIt out_first);

  /** Decodes the first part of the given UTF-32 code unit sequence into a code
   * point.
   *
   * If the input iterator pair contains more than one encoded code point, the
   * first code point will be decoded and an iterator to the code unit after it
   * will be returned.
   *
   * \tparam InputIt the input iterator type.
   *
   * \param in_first the begin of the input code unit sequence.
   *
   * \param in_last the end of the input code unit sequence.
   *
   * \param out the output code point.
   *
   * \throws hou::precondition_violation if the given code unit sequence is
   * invalid.
   *
   * \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
  static InputIt decode(InputIt in_first, InputIt in_last, code_point& out);

  /** Returns an iterator to the next code point in the given UTF-32 code unit
   * sequence.
   *
   * If the given code unit sequence is not valid the returned iterator might
   * point to an invalid memory address.
   *
   * \tparam InputIt the input iterator type.
   *
   * \param in_first the begin of the input code unit sequence.
   *
   * \param in_last the end of the input code unit sequence.
   *
   * \throws hou::precondition_violation if the given code unit sequence is
   * invalid.
   *
   * \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
  static InputIt next(InputIt in_first, InputIt in_last);

  /** Counts the number of code points in the given UTF-32 code unit sequence.
   *
   * If the given code unit sequence is not valid the returned value has no
   * meaning.
   *
   * \tparam InputIt the input iterator type.
   *
   * \param in_first the begin of the input code unit sequence.
   *
   * \param in_last the end of the input code unit sequence.
   *
   * \throws hou::precondition_violation if the given code unit sequence is
   * invalid.
   *
   * \return the number of code points in the code unit sequence.
   */
  template <typename InputIt>
  static size_t count(InputIt in_first, InputIt in_last);
};

/** Container class for wide encoding functions
 *
 */
class wide : public non_instantiable
{
public:
  /** wide code unit representation. */
  using code_unit = wchar_t;

public:
  /** Encodes the given code point into an wide code unit sequence.
   *
   * The user must ensure that out_first points to a valid memory address and
   * that the container is large enough to contain the encoded code point.
   *
   * \tparam OutputIt the output iterator type.
   *
   * \param in the code point.
   *
   * \param out_first the begin of the output code unit sequence.
   *
   * \throws std::bad_alloc.
   *
   * \return an iterator to the code unit after the encoded code point.
   */
  template <typename OutputIt>
  static OutputIt encode(code_point in, OutputIt out_first);

  /** Decodes the first part of the given wide code unit sequence into a code
   *  point.
   *
   * If the input iterator pair contains more than one encoded code point, the
   * first code point will be decoded and an iterator to the code unit after it
   * will be returned.
   * Throws if the given code unit sequence is invalid.
   *
   * \tparam InputIt the input iterator type.
   *
   * \param in_first the begin of the input code unit sequence.
   *
   * \param in_last the end of the input code unit sequence.
   *
   * \param out the output code point.
   *
   * \throws hou::precondition_violation if the given code unit sequence is
   * invalid.
   *
   * \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
  static InputIt decode(InputIt in_first, InputIt in_last, code_point& out);

  /** Returns an iterator to the next code point in the given wide code unit
   * sequence.
   *
   * If the given code unit sequence is not valid the returned iterator might
   * point to an invalid memory address.
   *
   * \tparam InputIt the input iterator type.
   *
   * \param in_first the begin of the input code unit sequence.
   *
   * \param in_last the end of the input code unit sequence.
   *
   * \throws hou::precondition_violation if the given code unit sequence is
   * invalid.
   *
   * \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
  static InputIt next(InputIt in_first, InputIt in_last);

  /** Counts the number of code points in the given wide code unit sequence.
   *
   * If the given code unit sequence is not valid the returned value has no
   * meaning.
   *
   * \tparam InputIt the input iterator type.
   *
   * \param in_first the begin of the input code unit sequence.
   *
   * \param in_last the end of the input code unit sequence.
   *
   * \throws hou::precondition_violation if the given code unit sequence is
   * invalid.
   *
   * \return the number of code points in the code unit sequence.
   */
  template <typename InputIt>
  static size_t count(InputIt in_first, InputIt in_last);
};

/** Performs a conversion between two encodings.
 *
 * If the input iterator pair contains more than one encoded code point, the
 * first code point will be converted.
 * Throws if the input iterator pair does not contain a valid code unit
 * sequence.
 * The user must ensure that out_first is a valid itrator and that the container
 * is large enough to contain the converted code point.
 *
 * \tparam InputEncoding the input encoding.
 *
 * \tparam OutputEncoding the output encoding.
 *
 * \tparam InputIt the input iterator type.
 *
 * \tparam OutputIt the output iterator type.
 *
 * \param in_first the begin of the input code unit sequence.
 *
 * \param in_last the end of the input code unit sequence.
 *
 * \param out_first the begin of the output code unit sequence.
 *
 * \throws std::bad_alloc.
 *
 * \return an iterator to the output code unit after the converted code point.
 */
template <typename OutputEncoding, typename InputEncoding, typename OutputIt,
  typename InputIt>
OutputIt convert_encoding(
  InputIt in_first, InputIt in_last, OutputIt out_first);

/** Converts an encoded string.
 *
 * \tparam InputEncoding the input encoding.
 *
 * \tparam OutputEncoding the output encoding.
 *
 * \param s the input encoded string.
 *
 * \throws std::bad_alloc.
 *
 * \return the converted encoded string.
 */
template <typename OutputEncoding, typename InputEncoding>
std::basic_string<typename OutputEncoding::code_unit> convert_encoding(
  const std::basic_string<typename InputEncoding::code_unit>& s);

// Specializations.
/** convert_encoding specialization. */
template <>
HOU_COR_API std::string convert_encoding<utf8, utf8>(const std::string& s);

/** convert_encoding specialization. */
template <>
HOU_COR_API std::u16string convert_encoding<utf16, utf16>(
  const std::u16string& s);

/** convert_encoding specialization. */
template <>
HOU_COR_API std::u32string convert_encoding<utf32, utf32>(
  const std::u32string& s);

/** convert_encoding specialization. */
template <>
HOU_COR_API std::wstring convert_encoding<wide, wide>(const std::wstring& s);

// Instantiations.
/** convert_encoding instantion. */
extern template HOU_COR_API std::string convert_encoding<utf8, utf16>(
  const std::u16string& s);

/** convert_encoding instantion. */
extern template HOU_COR_API std::string convert_encoding<utf8, utf32>(
  const std::u32string& s);

/** convert_encoding instantion. */
extern template HOU_COR_API std::string convert_encoding<utf8, wide>(
  const std::wstring& s);

/** convert_encoding instantion. */
extern template HOU_COR_API std::u16string convert_encoding<utf16, utf8>(
  const std::string& s);

/** convert_encoding instantion. */
extern template HOU_COR_API std::u16string convert_encoding<utf16, utf32>(
  const std::u32string& s);

/** convert_encoding instantion. */
extern template HOU_COR_API std::u16string convert_encoding<utf16, wide>(
  const std::wstring& s);

/** convert_encoding instantion. */
extern template HOU_COR_API std::u32string convert_encoding<utf32, utf8>(
  const std::string& s);

/** convert_encoding instantion. */
extern template HOU_COR_API std::u32string convert_encoding<utf32, utf16>(
  const std::u16string& s);

/** convert_encoding instantion. */
extern template HOU_COR_API std::u32string convert_encoding<utf32, wide>(
  const std::wstring& s);

/** convert_encoding instantion. */
extern template HOU_COR_API std::wstring convert_encoding<wide, utf8>(
  const std::string& s);

/** convert_encoding instantion. */
extern template HOU_COR_API std::wstring convert_encoding<wide, utf16>(
  const std::u16string& s);

/** convert_encoding instantion. */
extern template HOU_COR_API std::wstring convert_encoding<wide, utf32>(
  const std::u32string& s);

}  // namespace hou

#include "hou/cor/character_encodings.inl"

#endif
