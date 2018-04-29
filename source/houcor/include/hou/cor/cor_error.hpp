// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_COR_ERROR_HPP
#define HOU_COR_COR_ERROR_HPP

#include "hou/cor/cor_export.hpp"

#include <string>



namespace hou
{

/** core module error codes. */
enum class cor_error
{
  invalid_enum,
  overflow,
  post_condition,
  pre_condition,
};

/** Retrieves the message string associated to a core module error code.
 *
 *  \param ec the error code.
 */
HOU_COR_API std::string get_text(cor_error ec);

}

#endif

