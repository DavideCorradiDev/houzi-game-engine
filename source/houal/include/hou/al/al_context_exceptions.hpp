// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_CONTEXT_EXCEPTIONS_HPP
#define HOU_AL_AL_CONTEXT_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/al/al_config.hpp"



namespace hou
{

namespace al
{

/** Context creation error.
 *
 * This exception is thrown when creating an OpenAL context fails.
 */
class HOU_AL_API context_creation_error : public exception
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
  context_creation_error(const std::string& path, uint line);
};

/** Context destruction error.
 *
 * This exception is thrown when destroying an OpenAL context fails.
 */
class HOU_AL_API context_destruction_error : public exception
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
  context_destruction_error(const std::string& path, uint line);
};

/** OpenAL context switch error.
 *
 * This exceptions is thrown when switching the current OpenAL context fails.
 */
class HOU_AL_API context_switch_error : public exception
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
  context_switch_error(const std::string& path, uint line);
};

/** Device open error.
 *
 * This exception is thrown when opening an audio device fails.
 * This happens when trying to open a non-existent device.
 */
class HOU_AL_API device_open_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param device_name the name of the device.
   *
   * \throws std::bad_alloc.
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
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  device_close_error(const std::string& path, uint line);
};

}  // namespace al

}  // namespace hou

#endif
