// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_AL_AL_CHECK_HPP
#define HOU_AL_AL_CHECK_HPP

#include "hou/al/AlExport.hpp"

#include "hou/cor/BasicTypes.hpp"

#include <string>



namespace hou
{

namespace al
{

class ContextOwnedObjectHandle;
class Device;
class DeviceOwnedObjectHandle;

void HOU_AL_API checkError(const std::string& filename, int line);
void HOU_AL_API checkContextError(Device& device, const std::string& filename
  , int line);
void HOU_AL_API checkContextExistence(const std::string& filename, int line);
void HOU_AL_API checkContextOwnership(const DeviceOwnedObjectHandle& o
  , const std::string& filename, int line);
void HOU_AL_API checkContextOwnership(const ContextOwnedObjectHandle& o
  , const std::string& filename, int line);

}

}



#if defined(HOU_DISABLE_AL_ERROR_CHECKS)
  #define HOU_AL_CHECK_ERROR()
#else
  #define HOU_AL_CHECK_ERROR() \
    hou::al::checkError(__FILE__, __LINE__)
#endif



#if defined(HOU_DISABLE_AL_CONTEXT_ERROR_CHECKS)
  #define HOU_AL_CHECK_CONTEXT_ERROR(device)
#else
  #define HOU_AL_CHECK_CONTEXT_ERROR(device) \
    hou::al::checkContextError(device, __FILE__, __LINE__)
#endif



#if defined(HOU_DISABLE_AL_CONTEXT_EXISTENCE_CHECKS)
  #define HOU_AL_CHECK_CONTEXT_EXISTENCE()
#else
  #define HOU_AL_CHECK_CONTEXT_EXISTENCE() \
    hou::al::checkContextExistence(__FILE__, __LINE__)
#endif



#if defined(HOU_DISABLE_AL_CONTEXT_OWNERSHIP_CHECKS)
  #define HOU_AL_CHECK_CONTEXT_OWNERSHIP(objectHandle)
#else
  #define HOU_AL_CHECK_CONTEXT_OWNERSHIP(objectHandle) \
    hou::al::checkContextOwnership(objectHandle, __FILE__, __LINE__)
#endif

#endif

