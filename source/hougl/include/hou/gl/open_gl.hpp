#ifndef HOU_GL_OPEN_GL_HPP
#define HOU_GL_OPEN_GL_HPP

#include "hou/gl/gl_config.hpp"

#if defined(HOU_SYSTEM_WINDOWS)
  #ifdef HOU_COMPILER_MSVC
    #ifndef NOMINMAX
      #define NOMINMAX
    #endif
  #endif
  #include "glad/glad_wgl.h"
#elif defined(HOU_SYSTEM_LINUX)
  #include "glad/glad_glx.h"
#endif

#include "glad/glad.h"

#endif
