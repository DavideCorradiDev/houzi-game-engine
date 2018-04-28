// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_CHARACTER_ENCODINGS_HPP
#define HOU_COR_CHARACTER_ENCODINGS_HPP

#include "hou/cor/cor_export.hpp"
#include "hou/cor/non_instantiable.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/error.hpp"

#include <array>
#include <limits>



namespace hou
{

/** Unicode code point. */
using CodePoint = char32_t;

/** Container class for UTF-8 encoding functions
 */
class utf8
  : public non_instantiable
{
public:
  /** UTF-8 code unit representation. */
  using code_unit = char;

public:
  /** Encodes the given code point into an UTF-8 code unit sequence.
   *
   *  The user must ensure that outFirst is a valid iterator and that the
   *  container is large enough to contain the encoded code point.
   *
   *  \tparam OutputIt the output iterator type.
   *  \param in the code point.
   *  \param outFirst the begin of the output code unit sequence.
   *  \return an iterator to the code unit after the encoded code point.
   */
  template <typename OutputIt>
    static OutputIt encode(CodePoint in, OutputIt outFirst);

  /** Decodes the first part of the given UTF-8 code unit sequence into a code
   *  point.
   *
   *  If the input iterator pair contains more than one encoded code point, the
   *  first code point will be decoded and an iterator to the code unit after it
   *  will be returned.
   *  Throws if the given code unit sequence is invalid.
   *
   *  \tparam InputIt the input iterator type.
   *  \param inFirst the begin of the input code unit sequence.
   *  \param inLast the end of the input code unit sequence.
   *  \param out the output code point.
   *  \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
    static InputIt decode(InputIt inFirst, InputIt inLast, CodePoint& out);

  /** Returns an iterator to the next code point in the given UTF-8 code unit
   *  sequence.
   *
   *  If the given code unit sequence is not valid the returned iterator might
   *  point to an invalid memory address.
   *
   *  \tparam InputIt the input iterator type.
   *  \param inFirst the begin of the input code unit sequence.
   *  \param inLast the end of the input code unit sequence.
   *  \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
    static InputIt next(InputIt inFirst, InputIt inLast);

  /** Counts the number of code points in the given UTF-8 code unit sequence.
   *
   *  If the given code unit sequence is not valid the returned value has no
   *  meaning.
   *
   *  \tparam InputIt the input iterator type.
   *  \param inFirst the begin of the input code unit sequence.
   *  \param inLast the end of the input code unit sequence.
   *  \return the number of code points in the code unit sequence.
   */
  template <typename InputIt>
    static size_t count(InputIt inFirst, InputIt inLast);

private:
  static inline size_t count_trailing_units(code_unit cu);
};

/** Container class for UTF-16 encoding functions
 */
class utf16
  : public non_instantiable
{
public:
  /** UTF-16 code unit representation. */
  using code_unit = char16_t;

public:
  /** Encodes the given code point into an UTF-16 code unit sequence.
   *
   *  The user must ensure that outFirst points to a valid memory address and
   *  that the container is large enough to contain the encoded code point.
   *
   *  \tparam OutputIt the output iterator type.
   *  \param in the code point.
   *  \param outFirst the begin of the output code unit sequence.
   *  \return an iterator to the code unit after the encoded code point.
   */
  template <typename OutputIt>
    static OutputIt encode(CodePoint in, OutputIt outFirst);

  /** Decodes the first part of the given UTF-16 code unit sequence into a code
   *  point.
   *
   *  If the input iterator pair contains more than one encoded code point, the
   *  first code point will be decoded and an iterator to the code unit after it
   *  will be returned.
   *  Throws if the given code unit sequence is invalid.
   *
   *  \tparam InputIt the input iterator type.
   *  \param inFirst the begin of the input code unit sequence.
   *  \param inLast the end of the input code unit sequence.
   *  \param out the output code point.
   *  \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
    static InputIt decode(InputIt inFirst, InputIt inLast, CodePoint& out);

  /** Returns an iterator to the next code point in the given UTF-16 code unit
   *  sequence.
   *
   *  If the given code unit sequence is not valid the returned iterator might
   *  point to an invalid memory address.
   *
   *  \tparam InputIt the input iterator type.
   *  \param inFirst the begin of the input code unit sequence.
   *  \param inLast the end of the input code unit sequence.
   *  \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
    static InputIt next(InputIt inFirst, InputIt inLast);

  /** Counts the number of code points in the given UTF-16 code unit sequence.
   *
   *  If the given code unit sequence is not valid the returned value has no
   *  meaning.
   *
   *  \tparam InputIt the input iterator type.
   *  \param inFirst the begin of the input code unit sequence.
   *  \param inLast the end of the input code unit sequence.
   *  \return the number of code points in the code unit sequence.
   */
  template <typename InputIt>
    static size_t count(InputIt inFirst, InputIt inLast);
};

/** Container class for UTF-32 encoding functions
 */
class utf32
  : public non_instantiable
{
public:
  /** UTF-32 code unit representation. */
  using code_unit = char32_t;

public:
  /** Encodes the given code point into an UTF-32 code unit sequence.
   *
   *  The user must ensure that outFirst points to a valid memory address and
   *  that the container is large enough to contain the encoded code point.
   *
   *  \tparam OutputIt the output iterator type.
   *  \param in the code point.
   *  \param outFirst the begin of the output code unit sequence.
   *  \return an iterator to the code unit after the encoded code point.
   */
  template <typename OutputIt>
    static OutputIt encode(CodePoint in, OutputIt outFirst);

  /** Decodes the first part of the given UTF-32 code unit sequence into a code
   *  point.
   *
   *  If the input iterator pair contains more than one encoded code point, the
   *  first code point will be decoded and an iterator to the code unit after it
   *  will be returned.
   *  Throws if the given code unit sequence is invalid.
   *
   *  \tparam InputIt the input iterator type.
   *  \param inFirst the begin of the input code unit sequence.
   *  \param inLast the end of the input code unit sequence.
   *  \param out the output code point.
   *  \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
    static InputIt decode(InputIt inFirst, InputIt inLast, CodePoint& out);

  /** Returns an iterator to the next code point in the given UTF-32 code unit
   *  sequence.
   *
   *  If the given code unit sequence is not valid the returned iterator might
   *  point to an invalid memory address.
   *
   *  \tparam InputIt the input iterator type.
   *  \param inFirst the begin of the input code unit sequence.
   *  \param inLast the end of the input code unit sequence.
   *  \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
    static InputIt next(InputIt inFirst, InputIt inLast);

  /** Counts the number of code points in the given UTF-32 code unit sequence.
   *
   *  If the given code unit sequence is not valid the returned value has no
   *  meaning.
   *
   *  \tparam InputIt the input iterator type.
   *  \param inFirst the begin of the input code unit sequence.
   *  \param inLast the end of the input code unit sequence.
   *  \return the number of code points in the code unit sequence.
   */
  template <typename InputIt>
    static size_t count(InputIt inFirst, InputIt inLast);
};

/** Container class for wide encoding functions
 *
 */
class wide
  : public non_instantiable
{
public:
  /** wide code unit representation. */
  using code_unit = wchar_t;

public:
  /** Encodes the given code point into an wide code unit sequence.
   *
   *  The user must ensure that outFirst points to a valid memory address and
   *  that the container is large enough to contain the encoded code point.
   *
   *  \tparam OutputIt the output iterator type.
   *  \param in the code point.
   *  \param outFirst the begin of the output code unit sequence.
   *  \return an iterator to the code unit after the encoded code point.
   */
  template <typename OutputIt>
    static OutputIt encode(CodePoint in, OutputIt outFirst);

  /** Decodes the first part of the given wide code unit sequence into a code
   *  point.
   *
   *  If the input iterator pair contains more than one encoded code point, the
   *  first code point will be decoded and an iterator to the code unit after it
   *  will be returned.
   *  Throws if the given code unit sequence is invalid.
   *
   *  \tparam InputIt the input iterator type.
   *  \param inFirst the begin of the input code unit sequence.
   *  \param inLast the end of the input code unit sequence.
   *  \param out the output code point.
   *  \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
    static InputIt decode(InputIt inFirst, InputIt inLast, CodePoint& out);

  /** Returns an iterator to the next code point in the given wide code unit
   *  sequence.
   *
   *  If the given code unit sequence is not valid the returned iterator might
   *  point to an invalid memory address.
   *
   *  \tparam InputIt the input iterator type.
   *  \param inFirst the begin of the input code unit sequence.
   *  \param inLast the end of the input code unit sequence.
   *  \return an iterator to the code unit after the first encoded code point.
   */
  template <typename InputIt>
    static InputIt next(InputIt inFirst, InputIt inLast);

  /** Counts the number of code points in the given wide code unit sequence.
   *
   *  If the given code unit sequence is not valid the returned value has no
   *  meaning.
   *
   *  \tparam InputIt the input iterator type.
   *  \param inFirst the begin of the input code unit sequence.
   *  \param inLast the end of the input code unit sequence.
   *  \return the number of code points in the code unit sequence.
   */
  template <typename InputIt>
    static size_t count(InputIt inFirst, InputIt inLast);
};

/** Performs a conversion between two encodings.
 *
 *  If the input iterator pair contains more than one encoded code point, the
 *  first code point will be converted.
 *  Throws if the input iterator pair does not contain a valid code unit
 *  sequence.
 *  The user must ensure that outFirst is a valid itrator and that the container
 *  is large enough to contain the converted code point.
 *
 *  \tparam InputEncoding the input encoding.
 *  \tparam OutputEncoding the output encoding.
 *  \tparam InputIt the input iterator type.
 *  \tparam OutputIt the output iterator type.
 *  \param inFirst the begin of the input code unit sequence.
 *  \param inLast the end of the input code unit sequence.
 *  \param outFirst the begin of the output code unit sequence.
 *  \return an iterator to the output code unit after the converted code point.
 */
template <typename InputEncoding, typename OutputEncoding
  , typename InputIt, typename OutputIt>
  OutputIt convertEncoding(InputIt inFirst, InputIt inLast, OutputIt outFirst);

/** Converts an encoded string.
 *
 *  \tparam InputEncoding the input encoding.
 *  \tparam OutputEncoding the output encoding.
 *  \param s the input encoded string.
 *  \return the converted encoded string.
 */
template <typename InputEncoding, typename OutputEncoding>
  std::basic_string<typename OutputEncoding::code_unit> convertEncoding
  (const std::basic_string<typename InputEncoding::code_unit>& s);

}

#include "hou/cor/character_encodings.inl"

#endif

