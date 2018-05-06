// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_EXCEPTIONS_HPP
#define HOU_AL_AL_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/al/open_al.hpp"

#include "hou/al/al_export.hpp"

#include "hou/cor/std_string.hpp"



namespace hou
{

namespace al
{

class context_owned_object_handle;
class device;
class device_owned_object_handle;

/** Context creation error.
 *
 * This exception is thrown when creating an OpenAL context fails.
 */
class HOU_AL_API context_creation_error : public exception
{
public:
  /** Creates a context_creation_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  context_creation_error(const std::string& path, uint line);
};

/** Context destruction error.
 *
 * This exception is thrown when destroying an OpenAL context fails.
 */
class HOU_AL_API context_destruction_error : public exception
{
public:
  /** Creates a context_destruction_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  context_destruction_error(const std::string& path, uint line);
};

/** OpenAL context switch error.
 *
 * This exceptions is thrown when switching the current OpenAL context fails.
 */
class HOU_AL_API context_switch_error : public exception
{
public:
  /** Creates a context_switch_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  context_switch_error(const std::string& path, uint line);
};

/** Missing OpenAL context error.
 *
 * This exception is thrown when an OpenAL call is made without a current
 * context.
 */
class HOU_AL_API missing_context_error : public exception
{
public:
  /** Creates a missing_context_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  missing_context_error(const std::string& path, uint line);
};

/** Invalid OpenAL context error.
 *
 * This exception is thrown when an OpenAL call is made using an OpenAL object
 * which is not owned by the current context.
 */
class HOU_AL_API invalid_context_error : public exception
{
public:
  /** Creates an invalid_context_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  invalid_context_error(const std::string& path, uint line);
};

/** Device open error.
 *
 * This exception is thrown when opening an audio device fails.
 * This happens when trying to open a non-existent device.
 */
class HOU_AL_API device_open_error : public exception
{
public:
  /** Creates a device_open_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param device_name the name of the device.
   */
  device_open_error(
    const std::string& path, uint line, const std::string& device_name);
};

/** Device close error.
 *
 * This exception is thrown when closing an audio device fails.
 */
class HOU_AL_API device_close_error : public exception
{
public:
  /** Creates a device_close_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  device_close_error(const std::string& path, uint line);
};

/** OpenAL call error.
 *
 * This exception is thrown when an OpenAL call fails.
 * This is normally a programmer error and execution should be terminated.
 */
class HOU_AL_API call_error : public exception
{
public:
  /** Creates a call_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param ec the error code.
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
  /** Creates a context_call_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param ec the error code.
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
#define HOU_AL_CHECK_ERROR() ::hou::al::check_error(__FILE__, __LINE__)
#else
#define HOU_AL_CHECK_ERROR()
#endif



#ifdef HOU_ENABLE_AL_CONTEXT_ERROR_CHECKS
#define HOU_AL_CHECK_CONTEXT_ERROR(device)                                     \
  ::hou::al::check_context_error(device, __FILE__, __LINE__)
#else
#define HOU_AL_CHECK_CONTEXT_ERROR(device)
#endif



#ifdef HOU_ENABLE_AL_CONTEXT_EXISTENCE_CHECKS
#define HOU_AL_CHECK_CONTEXT_EXISTENCE()                                       \
  ::hou::al::check_context_existence(__FILE__, __LINE__)
#else
#define HOU_AL_CHECK_CONTEXT_EXISTENCE()
#endif



#ifdef HOU_ENABLE_AL_CONTEXT_OWNERSHIP_CHECKS
#define HOU_AL_CHECK_CONTEXT_OWNERSHIP(objectHandle)                           \
  ::hou::al::check_context_ownership(objectHandle, __FILE__, __LINE__)
#else
#define HOU_AL_CHECK_CONTEXT_OWNERSHIP(objectHandle)
#endif

#endif
