// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_VERSION_HPP
#define HOU_GL_GL_VERSION_HPP

#include "hou/gl/gl_export.hpp"

#include "hou/cor/basic_types.hpp"

#include <iostream>



namespace hou
{

namespace gl
{

class HOU_GL_API version
{
public:
  version(uint major, uint minor) noexcept;

  uint get_major() const noexcept;
  uint get_minor() const noexcept;
  bool is_supported() const noexcept;

public:
  static version standard;

private:
  uint m_major;
  uint m_minor;
};

HOU_GL_API bool operator==(const version& l, const version& r) noexcept;
HOU_GL_API bool operator!=(const version& l, const version& r) noexcept;
HOU_GL_API bool operator>(const version& l, const version& r) noexcept;
HOU_GL_API bool operator>=(const version& l, const version& r) noexcept;
HOU_GL_API bool operator<(const version& l, const version& r) noexcept;
HOU_GL_API bool operator<=(const version& l, const version& r) noexcept;
HOU_GL_API std::ostream& operator<<(std::ostream& os, const version& v);

}  // namespace gl

}  // namespace hou

#endif
