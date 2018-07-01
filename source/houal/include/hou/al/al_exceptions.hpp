// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_EXCEPTIONS_HPP
#define HOU_AL_AL_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/al/open_al.hpp"

#include "hou/al/al_config.hpp"

#include <cstdlib>



namespace hou
{

namespace al
{

class device;

/** OpenAL call error.
 *
 * This exception is thrown when an OpenAL call fails.
 * This is normally a programmer error and execution should be terminated.
 */
class HOU_AL_API call_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param ec the error code.
   *
   * \throws std::bad_alloc.
   */
  call_error(const std::string& path, uint line, ALenum ec);
};

/** OpenAL context call error.
 *
 * This exception is thrown when an OpenAL context-related call fails.
 * This is normally a programmer error and execution should be terminated.
 */
class HOU_AL_API context_call_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param ec the error code.
   *
   * \throws std::bad_alloc.
   */
  context_call_error(const std::string& path, uint line, ALenum ec);
};

/** Checks if an OpenAL call has failed and throws an exception in case.
 *
 * \param path the source file path to be written in the exception in case of
 * an error.
 *
 * \param line the source file line to be written in the exception in case of
 * an error.
 *
 * \throws hou::al::call_error if a previous OpenAL call has failed.
 */
void HOU_AL_API check_error(const std::string& path, int line);

/** Checks if an OpenAL context call has failed and throws an exception in case.
 *
 * \param path the source file path to be written in the exception in case of
 * an error.
 *
 * \param line the source file line to be written in the exception in case of
 * an error.
 *
 * \throws hou::al::context_call_error if a previous OpenAL call has failed.
 */
void HOU_AL_API check_context_error(
  device& device, const std::string& path, int line);

}  // namespace al

}  // namespace hou



#ifdef HOU_ENABLE_AL_ERROR_CHECKS
#define HOU_AL_CHECK_ERROR() ::hou::al::check_error(__FILE__, __LINE__)
#else
#define HOU_AL_CHECK_ERROR()
#endif



#ifdef HOU_ENABLE_AL_ERROR_CHECKS
#define HOU_AL_CHECK_CONTEXT_ERROR(device)                                     \
  ::hou::al::check_context_error(device, __FILE__, __LINE__)
#else
#define HOU_AL_CHECK_CONTEXT_ERROR(device)
#endif

#endif
