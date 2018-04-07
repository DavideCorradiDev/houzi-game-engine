// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GL_GL_VERSION_HPP
#define HOU_GL_GL_VERSION_HPP

#include "hou/gl/GlExport.hpp"

#include "hou/cor/BasicTypes.hpp"

#include <iostream>



namespace hou
{

namespace gl
{

class HOU_GL_API Version
{
public:
  Version(uint major, uint minor);

  uint getMajor() const;
  uint getMinor() const;
  bool isSupported() const;

public:
  static Version Default;

private:
  uint mMajor;
  uint mMinor;
};

HOU_GL_API bool operator==(const Version& l, const Version& r);
HOU_GL_API bool operator!=(const Version& l, const Version& r);
HOU_GL_API bool operator>(const Version& l, const Version& r);
HOU_GL_API bool operator>=(const Version& l, const Version& r);
HOU_GL_API bool operator<(const Version& l, const Version& r);
HOU_GL_API bool operator<=(const Version& l, const Version& r);
HOU_GL_API std::ostream& operator<<(std::ostream& os, const Version& v);

}

}

#endif

