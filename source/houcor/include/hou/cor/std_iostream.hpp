// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_STD_IOSTREAM_HPP
#define HOU_COR_STD_IOSTREAM_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/cor/cor_config.hpp"

#include <iostream>



namespace hou
{

/**
 * Saves the current formatting of a std::basic_ios object and restores it upon
 * destruction.
 *
 * The formatting information saved includes the formatting flags, the
 * precision, the width, and the fill character.
 *
 * \tparam IosType the stream type.
 */
template <typename IosType>
class ios_formatting_saver : public non_copyable
{
public:
  /**
   * IosType
   */
  using stream_type = IosType;

public:
  /**
   * Saves the state of ios.
   *
   * The ios_formatting_saver will internally store a reference to ios and
   * will restore its formatting upon destruction.
   * It is therefore required to ensure that ios still exists when
   * ios_formatting_saver is destroyed.
   * Calling the destructor of ios_formatting_saver after ios has already been
   * destroyed is undefined behaviour.
   *
   * \param ios the stream whose state to save.
   */
  explicit ios_formatting_saver(IosType& ios);

  /**
   * Move constructor.
   */
  ios_formatting_saver(ios_formatting_saver&& other);

  /**
   * Destructor.
   *
   * Upon calling the constructor, the formatting of the internally referenced
   * stream will be restored to the state it had when this object was created.
   */
  ~ios_formatting_saver();

private:
  IosType* m_ios;
  typename IosType::fmtflags m_flags;
  std::streamsize m_precision;
  std::streamsize m_width;
  typename IosType::char_type m_fill;
};

}  // namespace hou

#include "hou/cor/std_iostream.inl"

#endif
