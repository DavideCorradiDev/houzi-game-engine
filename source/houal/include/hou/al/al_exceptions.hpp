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

class HOU_AL_API context_creation_error : public exception
{
public:
  context_creation_error(const std::string& path, uint line);
};

class HOU_AL_API context_destruction_error : public exception
{
public:
  context_destruction_error(const std::string& path, uint line);
};

class HOU_AL_API context_switch_error : public exception
{
public:
  context_switch_error(const std::string& path, uint line);
};

class HOU_AL_API missing_context_error : public exception
{
public:
  missing_context_error(const std::string& path, uint line);
};

class HOU_AL_API invalid_context_error : public exception
{
public:
  invalid_context_error(const std::string& path, uint line);
};

class HOU_AL_API device_open_error : public exception
{
public:
  device_open_error(
    const std::string& path, uint line, const std::string& device_name);
};

class HOU_AL_API device_close_error : public exception
{
public:
  device_close_error(const std::string& path, uint line);
};

class HOU_AL_API call_error : public exception
{
public:
  call_error(const std::string& path, uint line, ALenum ec);
};

class HOU_AL_API context_call_error : public exception
{
public:
  context_call_error(const std::string& path, uint line, ALenum ec);
};

void HOU_AL_API check_error(const std::string& path, int line);
void HOU_AL_API check_context_error(
  device& device, const std::string& path, int line);
void HOU_AL_API check_context_existence(const std::string& path, int line);
void HOU_AL_API check_context_ownership(
  const device_owned_object_handle& o, const std::string& path, int line);
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
