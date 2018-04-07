// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_SHADER_HPP
#define HOU_GFX_SHADER_HPP

#include "hou/cor/NonCopyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/gfx/ShaderFwd.hpp"

#include "hou/gl/GlShaderHandle.hpp"

#include <string>



namespace hou
{

class HOU_GFX_API Shader : public NonCopyable
{
public:
  Shader(const std::string& source, ShaderType type);
  Shader(Shader&& other);
  virtual ~Shader() = 0;

  const gl::ShaderHandle& getHandle() const;

private:
  gl::ShaderHandle mHandle;
};



template <ShaderType type>
class HOU_GFX_API ShaderTemplate : public Shader
{
public:
  explicit ShaderTemplate(const std::string& source);
  ShaderTemplate(ShaderTemplate&& other);
};

}  // namespace hou

#endif
