// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/shader.hpp"

#include <utility>



namespace hou
{

shader::shader(const std::string& source, shader_type type)
  : non_copyable()
  , m_handle(gl::shader_handle::create(static_cast<GLenum>(type)))
{
  gl::compile_shader(m_handle, source.c_str());
}



shader::~shader()
{}



const gl::shader_handle& shader::get_handle() const
{
  return m_handle;
}



template <shader_type Type>
shader_t<Type>::shader_t(const std::string& source)
  : shader(source, Type)
{}



template class shader_t<shader_type::vertex>;
template class shader_t<shader_type::fragment>;
template class shader_t<shader_type::geometry>;

}  // namespace hou
