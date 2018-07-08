// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_shader_sources.hpp"

#include "hou/gl/test_gl_base.hpp"

namespace
{

std::string get_gl_version_shader_string();

std::string get_gl_version_shader_string()
{
  if(get_test_default_context_settings().get_profile()
    == hou::gl::context_profile::es)
  {
    return "#version 300 es\n"
           "precision highp float;\n";
  }
  else
  {
    return "#version 450 core\n";
  }
}

}  // namespace



std::string get_fs_source()
{
  return get_gl_version_shader_string() +
         "uniform vec4 colorUni;"
         "out vec4 outColor;"
         "void main()"
         "{"
         "    outColor = colorUni;"
         "}";
}



std::string get_gs_source()
{
  return get_gl_version_shader_string() +
         "layout(points) in;"
         "layout(line_strip, max_vertices = 2) out;"
         "void main()"
         "{"
         "  gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);"
         "  EmitVertex();"
         "  gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, 0.0);"
         "  EmitVertex();"
         "  EndPrimitive();"
         "}";
}



std::string get_vs_source()
{
  return get_gl_version_shader_string() +
         "in vec2 pos;"
         "void main()"
         "{"
         "    gl_Position = vec4(pos, 0.0, 1.0);"
         "}";
}
