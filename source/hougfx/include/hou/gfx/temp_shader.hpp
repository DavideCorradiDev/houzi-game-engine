// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_SHADER_HPP
#define HOU_GFX_SHADER_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/gfx_export.hpp"

#include "hou/gfx/shader_fwd.hpp"

#include "hou/gl/gl_shader_handle.hpp"

#include <string>



namespace hou
{

class HOU_GFX_API shader : public non_copyable
{
public:
  shader(const std::string& source, shader_type type);
  shader(shader&& other);
  virtual ~shader() = 0;

  const gl::shader_handle& get_handle() const;

private:
  gl::shader_handle m_handle;
};



template <shader_type type>
class HOU_GFX_API shader_t : public shader
{
public:
  explicit shader_t(const std::string& source);
  shader_t(shader_t&& other);
};

}  // namespace hou

#endif
