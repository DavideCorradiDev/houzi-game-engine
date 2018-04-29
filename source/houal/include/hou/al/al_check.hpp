// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_CHECK_HPP
#define HOU_AL_AL_CHECK_HPP

#include "hou/al/al_export.hpp"

#include "hou/cor/basic_types.hpp"

#include <string>



namespace hou
{

namespace al
{

class context_owned_object_handle;
class device;
class device_owned_object_handle;

void HOU_AL_API check_error(const std::string& filename, int line);
void HOU_AL_API check_context_error(device& ph_device, const std::string& filename
  , int line);
void HOU_AL_API check_context_existence(const std::string& filename, int line);
void HOU_AL_API check_context_ownership(const device_owned_object_handle& o
  , const std::string& filename, int line);
void HOU_AL_API check_context_ownership(const context_owned_object_handle& o
  , const std::string& filename, int line);

}

}



#ifdef HOU_ENABLE_AL_ERROR_CHECKS
  #define HOU_AL_CHECK_ERROR() \
    hou::al::check_error(__FILE__, __LINE__)
#else
  #define HOU_AL_CHECK_ERROR()
#endif



#ifdef HOU_ENABLE_AL_CONTEXT_ERROR_CHECKS
  #define HOU_AL_CHECK_CONTEXT_ERROR(ph_device) \
    hou::al::check_context_error(ph_device, __FILE__, __LINE__)
#else
  #define HOU_AL_CHECK_CONTEXT_ERROR(ph_device)
#endif



#ifdef HOU_ENABLE_AL_CONTEXT_EXISTENCE_CHECKS
  #define HOU_AL_CHECK_CONTEXT_EXISTENCE() \
    hou::al::check_context_existence(__FILE__, __LINE__)
#else
  #define HOU_AL_CHECK_CONTEXT_EXISTENCE()
#endif



#ifdef HOU_ENABLE_AL_CONTEXT_OWNERSHIP_CHECKS
  #define HOU_AL_CHECK_CONTEXT_OWNERSHIP(objectHandle) \
    hou::al::check_context_ownership(objectHandle, __FILE__, __LINE__)
#else
  #define HOU_AL_CHECK_CONTEXT_OWNERSHIP(objectHandle)
#endif

#endif

