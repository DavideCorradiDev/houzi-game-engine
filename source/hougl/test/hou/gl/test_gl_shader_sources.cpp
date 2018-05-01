// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_shader_sources.hpp"



std::string get_fs_source()
{
  return "#version 330 core\n"
         "uniform vec4 colorUni;"
         "out vec4 outColor;"
         "void main()"
         "{"
         "    outColor = colorUni;"
         "}";
}



std::string get_gs_source()
{
  return "#version 330 core\n"
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
  return "#version 330 core\n"
         "in vec2 pos;"
         "void main()"
         "{"
         "    gl_Position = vec4(pos, 0.0, 1.0);"
         "}";
}
