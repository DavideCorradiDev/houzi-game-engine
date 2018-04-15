// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_COR_ERROR_HPP
#define HOU_COR_COR_ERROR_HPP

#include "hou/cor/CorExport.hpp"

#include <string>



namespace hou
{

/** Core module error codes. */
enum class CorError
{
  InvalidEnum,
  Overflow,
  Postcondition,
  Precondition,
};

/** Retrieves the message string associated to a core module error code.
 *
 *  \param ec the error code.
 */
HOU_COR_API std::string getText(CorError ec);

}

#endif

