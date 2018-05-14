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

namespace
{

const std::vector<version> supported_versions = {
  version(4u, 5u),
};
}



version version::standard(4u, 5u);



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



bool version::is_supported() const noexcept
{
  return (std::find(supported_versions.begin(), supported_versions.end(), *this)
    != supported_versions.end());
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
