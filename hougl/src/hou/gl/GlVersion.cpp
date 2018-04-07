// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gl/GlVersion.hpp"

#include <algorithm>
#include <cstring>
#include <vector>

namespace hou
{

namespace gl
{

namespace
{

const std::vector<Version> supportedVersions =
{
  Version(4u, 5u),
};

}



Version Version::Default(4u, 5u);



Version::Version(uint major, uint minor)
  : mMajor(major)
  , mMinor(minor) {}



uint Version::getMajor() const
{
  return mMajor;
}



uint Version::getMinor() const
{
  return mMinor;
}



bool Version::isSupported() const
{
  return(std::find(supportedVersions.begin(), supportedVersions.end(), *this)
    != supportedVersions.end());
}



bool operator==(const Version& l, const Version& r)
{
  return l.getMajor() == r.getMajor() && l.getMinor() == r.getMinor();
}



bool operator!=(const Version& l, const Version& r)
{
  return l.getMajor() != r.getMajor() || l.getMinor() != r.getMinor();
}



bool operator>(const Version& l, const Version& r)
{
  return l.getMajor() > r.getMajor() || (l.getMajor() == r.getMajor()
    && l.getMinor() > r.getMinor());
}



bool operator>=(const Version& l, const Version& r)
{
  return l.getMajor() > r.getMajor() || (l.getMajor() == r.getMajor()
    && l.getMinor() >= r.getMinor());
}



bool operator<(const Version& l, const Version& r)
{
  return l.getMajor() < r.getMajor() || (l.getMajor() == r.getMajor()
    && l.getMinor() < r.getMinor());
}



bool operator<=(const Version& l, const Version& r)
{
  return l.getMajor() < r.getMajor() || (l.getMajor() == r.getMajor()
    && l.getMinor() <= r.getMinor());
}



std::ostream& operator<<(std::ostream& os, const Version& v)
{
  return os << v.getMajor() << "." << v.getMinor();
}

}

}

