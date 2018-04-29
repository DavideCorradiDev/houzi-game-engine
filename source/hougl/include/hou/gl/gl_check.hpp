// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_CHECK_HPP
#define HOU_GL_GL_CHECK_HPP

#include "hou/gl/gl_export.hpp"
#include "hou/gl/open_gl.hpp"

#include "hou/cor/basic_types.hpp"

#include <string>



namespace hou
{

namespace gl
{

class shared_object_handle;
class non_shared_object_handle;



void HOU_GL_API check_error(const std::string& filename, int line);
void HOU_GL_API check_context_existence(const std::string& filename, int line);
void HOU_GL_API check_context_ownership(const shared_object_handle& o
  , const std::string& filename, int line);
void HOU_GL_API check_context_ownership(const non_shared_object_handle& o
  , const std::string& filename, int line);

}

}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  #define HOU_GL_CHECK_ERROR() \
    hou::gl::check_error(__FILE__, __LINE__)
#else
  #define HOU_GL_CHECK_ERROR()
#endif



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
  #define HOU_GL_CHECK_CONTEXT_EXISTENCE() \
    hou::gl::check_context_existence(__FILE__, __LINE__)
#else
  #define HOU_GL_CHECK_CONTEXT_EXISTENCE()
#endif



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
  #define HOU_GL_CHECK_CONTEXT_OWNERSHIP(objectHandle) \
    hou::gl::check_context_ownership(objectHandle, __FILE__, __LINE__)
#else
  #define HOU_GL_CHECK_CONTEXT_OWNERSHIP(objectHandle)
#endif



#endif

