// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gl/GlContextSettings.hpp"

namespace hou
{

namespace gl
{

const ContextSettings ContextSettings::Default = ContextSettings
  (Version::Default, ContextProfile::Core, 24u, 8u, 0u);



ContextSettings::ContextSettings
  ( const Version& version
  , ContextProfile profile
  , uint depthBits
  , uint stencilBits
  , uint antiAliasingLevel)
  : mVersion(version)
  , mProfile(profile)
  , mDepthBits(depthBits)
  , mStencilBits(stencilBits)
  , mAntiAliasingLevel(antiAliasingLevel) {}



void ContextSettings::setVersion(const Version& version)
{
  mVersion = version;
}



const Version& ContextSettings::getVersion() const
{
  return mVersion;
}



ContextProfile ContextSettings::getProfile() const
{
  return mProfile;
}



void ContextSettings::setProfile(ContextProfile value)
{
  mProfile = value;
}



uint ContextSettings::getDepthBits() const
{
  return mDepthBits;
}



void ContextSettings::setDepthBits(uint value)
{
  mDepthBits = value;
}



uint ContextSettings::getStencilBits() const
{
  return mStencilBits;
}



void ContextSettings::setStencilBits(uint value)
{
  mStencilBits = value;
}



uint ContextSettings::getAntialiasingLevel() const
{
  return mAntiAliasingLevel;
}



void ContextSettings::setAntialiasingLevel(uint value)
{
  mAntiAliasingLevel = value;
}



bool operator==(const ContextSettings& l, const ContextSettings& r)
{
  return l.getVersion() == r.getVersion()
    && l.getProfile() == r.getProfile()
    && l.getDepthBits() == r.getDepthBits()
    && l.getStencilBits() == r.getStencilBits()
    && l.getAntialiasingLevel() == r.getAntialiasingLevel();
}



bool operator!=(const ContextSettings& l, const ContextSettings& r)
{
  return !(l == r);
}

}

}

