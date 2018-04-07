// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gl/TestGlShaderSources.hpp"



std::string getFsSource()
{
  return "#version 330 core\n"
    "uniform vec4 colorUni;"
    "out vec4 outColor;"
    "void main()"
    "{"
    "    outColor = colorUni;"
    "}";
}



std::string getGsSource()
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



std::string getVsSource()
{
  return "#version 330 core\n"
    "in vec2 pos;"
    "void main()"
    "{"
    "    gl_Position = vec4(pos, 0.0, 1.0);"
    "}";
}

