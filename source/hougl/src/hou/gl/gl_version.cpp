// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_version.hpp"

#include <algorithm>
#include <cstring>
#include <vector>

namespace hou
{

namespace gl
{

version::version(uint major, uint minor) noexcept
  : m_major(major)
  , m_minor(minor)
{}



uint version::get_major() const noexcept
{
  return m_major;
}



uint version::get_minor() const noexcept
{
  return m_minor;
}



bool operator==(const version& l, const version& r) noexcept
{
  return l.get_major() == r.get_major() && l.get_minor() == r.get_minor();
}



bool operator!=(const version& l, const version& r) noexcept
{
  return l.get_major() != r.get_major() || l.get_minor() != r.get_minor();
}



bool operator>(const version& l, const version& r) noexcept
{
  return l.get_major() > r.get_major()
    || (l.get_major() == r.get_major() && l.get_minor() > r.get_minor());
}



bool operator>=(const version& l, const version& r) noexcept
{
  return l.get_major() > r.get_major()
    || (l.get_major() == r.get_major() && l.get_minor() >= r.get_minor());
}



bool operator<(const version& l, const version& r) noexcept
{
  return l.get_major() < r.get_major()
    || (l.get_major() == r.get_major() && l.get_minor() < r.get_minor());
}



bool operator<=(const version& l, const version& r) noexcept
{
  return l.get_major() < r.get_major()
    || (l.get_major() == r.get_major() && l.get_minor() <= r.get_minor());
}



std::ostream& operator<<(std::ostream& os, const version& v)
{
  return os << v.get_major() << "." << v.get_minor();
}

}  // namespace gl

}  // namespace hou
