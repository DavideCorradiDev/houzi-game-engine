// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_VERSION_HPP
#define HOU_GL_GL_VERSION_HPP

#include "hou/gl/gl_config.hpp"

#include <iostream>



namespace hou
{

namespace gl
{

/**
 * Represents an OpenGL version.
 */
class HOU_GL_API version
{
public:
  /**
   * Constructor.
   *
   * \param major the major version.
   *
   * \param minor the minor version.
   */
  version(uint major, uint minor) noexcept;

  /**
   * Gets the major version.
   *
   * \return the major version.
   */
  uint get_major() const noexcept;

  /**
   * Gets the minor version.
   *
   * \return the minor version.
   */
  uint get_minor() const noexcept;

private:
  uint m_major;
  uint m_minor;
};

/**
 * Checks if two version objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_GL_API bool operator==(const version& l, const version& r) noexcept;

/**
 * Checks if two version objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_GL_API bool operator!=(const version& l, const version& r) noexcept;

/**
 * Checks if lhs is greater than rhs.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_GL_API bool operator>(const version& l, const version& r) noexcept;

/**
 * Checks if lhs is greater or equal to rhs.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_GL_API bool operator>=(const version& l, const version& r) noexcept;

/**
 * Checks if lhs is less than rhs.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_GL_API bool operator<(const version& l, const version& r) noexcept;

/**
 * Checks if lhs is less or equal to rhs.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_GL_API bool operator<=(const version& l, const version& r) noexcept;

/**
 * Writes a the object into a stream.
 *
 * \param os the stream.
 *
 * \param vm the display_mode object.
 *
 * \return a reference to the stream.
 */
HOU_GL_API std::ostream& operator<<(std::ostream& os, const version& v);

}  // namespace gl

}  // namespace hou

#endif
