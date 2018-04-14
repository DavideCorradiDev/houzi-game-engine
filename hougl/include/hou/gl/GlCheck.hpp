// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_CHECK_HPP
#define HOU_GL_GL_CHECK_HPP

#include "hou/gl/GlExport.hpp"
#include "hou/gl/OpenGl.hpp"

#include "hou/cor/BasicTypes.hpp"

#include <string>



namespace hou
{

namespace gl
{

class SharedObjectHandle;
class NonSharedObjectHandle;



void HOU_GL_API checkError(const std::string& filename, int line);
void HOU_GL_API checkContextExistence(const std::string& filename, int line);
void HOU_GL_API checkContextOwnership(const SharedObjectHandle& o
  , const std::string& filename, int line);
void HOU_GL_API checkContextOwnership(const NonSharedObjectHandle& o
  , const std::string& filename, int line);

}

}



#if defined(HOU_DISABLE_GL_ERROR_CHECKS)
  #define HOU_GL_CHECK_ERROR()
#else
  #define HOU_GL_CHECK_ERROR() \
    hou::gl::checkError(__FILE__, __LINE__)
#endif



#if defined(HOU_DISABLE_GL_CONTEXT_EXISTENCE_CHECKS)
  #define HOU_GL_CHECK_CONTEXT_EXISTENCE()
#else
  #define HOU_GL_CHECK_CONTEXT_EXISTENCE() \
    hou::gl::checkContextExistence(__FILE__, __LINE__)
#endif



#if defined(HOU_DISABLE_GL_CONTEXT_OWNERSHIP_CHECKS)
  #define HOU_GL_CHECK_CONTEXT_OWNERSHIP(objectHandle)
#else
  #define HOU_GL_CHECK_CONTEXT_OWNERSHIP(objectHandle) \
    hou::gl::checkContextOwnership(objectHandle, __FILE__, __LINE__)
#endif



#endif

