// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_single_context.hpp"

#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_functions.hpp"
#include "hou/gl/gl_missing_context_error.hpp"

#include "hou/sys/window.hpp"

using namespace hou;



namespace
{

class test_gl_functions : public test_gl_single_context
{};

using test_gl_functions_death_test = test_gl_functions;

}  // namespace
