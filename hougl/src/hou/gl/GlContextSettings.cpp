// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gl/GlContextSettings.hpp"

namespace hou
{

namespace gl
{

const ContextSettings ContextSettings::Default
  = ContextSettings(Version::Default, ContextProfile::Core, 3u, 1u, 0u);



ContextSettings::ContextSettings(const Version& version, ContextProfile profile,
  uint depthByteCount, uint stencilByteCount, uint sampleCount)
  : mVersion(version)
  , mProfile(profile)
  , mDepthByteCount(depthByteCount)
  , mStencilByteCount(stencilByteCount)
  , mSampleCount(sampleCount)
{}



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



uint ContextSettings::getDepthByteCount() const
{
  return mDepthByteCount;
}



void ContextSettings::setDepthByteCount(uint value)
{
  mDepthByteCount = value;
}



uint ContextSettings::getStencilByteCount() const
{
  return mStencilByteCount;
}



void ContextSettings::setStencilByteCount(uint value)
{
  mStencilByteCount = value;
}



uint ContextSettings::getSampleCount() const
{
  return mSampleCount;
}



void ContextSettings::setSampleCount(uint value)
{
  mSampleCount = value;
}



bool operator==(const ContextSettings& l, const ContextSettings& r)
{
  return l.getVersion() == r.getVersion() && l.getProfile() == r.getProfile()
    && l.getDepthByteCount() == r.getDepthByteCount()
    && l.getStencilByteCount() == r.getStencilByteCount()
    && l.getSampleCount() == r.getSampleCount();
}



bool operator!=(const ContextSettings& l, const ContextSettings& r)
{
  return !(l == r);
}

}  // namespace gl

}  // namespace hou
