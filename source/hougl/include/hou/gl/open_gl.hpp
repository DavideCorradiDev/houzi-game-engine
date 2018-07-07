#ifndef HOU_GL_OPEN_GL_HPP
#define HOU_GL_OPEN_GL_HPP

#include "hou/gl/gl_config.hpp"

#if defined(HOU_GL_WGL)
  #include "glad/glad_wgl.h"
#elif defined(HOU_GL_GLX)
  #include "glad/glad_glx.h"
#endif
#include "glad/glad_egl.h"

#include "glad/glad.h"

#endif
