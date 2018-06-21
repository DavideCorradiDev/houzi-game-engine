// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_MISSING_CONTEXT_ERROR_HPP
#define HOU_AL_AL_MISSING_CONTEXT_ERROR_HPP

#include "hou/cor/exception.hpp"

#include "hou/al/open_al.hpp"

#include "hou/al/al_config.hpp"



namespace hou
{

namespace al
{

/** Missing OpenAL context error.
 *
 * This exception is thrown when an OpenAL call is made without a current
 * context.
 */
class HOU_AL_API missing_context_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  missing_context_error(const std::string& path, uint line);
};

/** Checks if there is a current OpenAL context and throws an exception if not.
 *
 * \param path the source file path to be written in the exception in case of
 * an error.
 *
 * \param line the source file line to be written in the exception in case of
 * an error.
 *
 * \throws hou::al::missing_context_error if there is no current OpenAL context.
 */
void HOU_AL_API check_context_existence(const std::string& path, int line);

}  // namespace al

}  // namespace hou



#ifdef HOU_ENABLE_AL_ERROR_CHECKS
#define HOU_AL_CHECK_CONTEXT_EXISTENCE()                                       \
  ::hou::al::check_context_existence(__FILE__, __LINE__)
#else
#define HOU_AL_CHECK_CONTEXT_EXISTENCE()
#endif

#endif
