// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_INVALID_CONTEXT_ERROR_HPP
#define HOU_AL_AL_INVALID_CONTEXT_ERROR_HPP

#include "hou/cor/exception.hpp"

#include "hou/al/open_al.hpp"

#include "hou/al/al_config.hpp"



namespace hou
{

namespace al
{

class context_owned_object_handle;
class device;
class device_owned_object_handle;

/** Invalid OpenAL context error.
 *
 * This exception is thrown when an OpenAL call is made using an OpenAL object
 * which is not owned by the current context.
 */
class HOU_AL_API invalid_context_error : public exception
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
  invalid_context_error(const std::string& path, uint line);
};

/** Checks if the object is owned by the current context, and throws an
 * exception if it is not.
 *
 * \param o the object whose ownership has to be checked.
 *
 * \param path the source file path to be written in the exception in case of
 * an error.
 *
 * \param line the source file line to be written in the exception in case of
 * an error.
 *
 * \throws hou::al::invalid_context_error if the current OpenAL context does
 * not own the object.
 */
void HOU_AL_API check_context_ownership(
  const device_owned_object_handle& o, const std::string& path, int line);

/** Checks if the object is owned by the current context, and throws an
 * exception if it is not.
 *
 * \param o the object whose ownership has to be checked.
 *
 * \param path the source file path to be written in the exception in case of
 * an error.
 *
 * \param line the source file line to be written in the exception in case of
 * an error.
 *
 * \throws hou::al::invalid_context_error if the current OpenAL context does
 * not own the object.
 */
void HOU_AL_API check_context_ownership(
  const context_owned_object_handle& o, const std::string& path, int line);

}  // namespace al

}  // namespace hou



#ifdef HOU_ENABLE_AL_ERROR_CHECKS
#define HOU_AL_CHECK_CONTEXT_OWNERSHIP(objectHandle)                           \
  ::hou::al::check_context_ownership(objectHandle, __FILE__, __LINE__)
#else
#define HOU_AL_CHECK_CONTEXT_OWNERSHIP(objectHandle)
#endif

#endif
