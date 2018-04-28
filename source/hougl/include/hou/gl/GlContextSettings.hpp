// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_CONTEXT_SETTINGS_HPP
#define HOU_GL_CONTEXT_SETTINGS_HPP

#include "hou/gl/GlExport.hpp"

#include "hou/gl/GlContextProfile.hpp"
#include "hou/gl/GlVersion.hpp"

#include "hou/cor/basic_types.hpp"



namespace hou
{

namespace gl
{

class HOU_GL_API ContextSettings
{
public:
  ContextSettings(const Version& version, ContextProfile profile,
    uint depthByteCount, uint stencilByteCount, uint sampleCount);

  const Version& getVersion() const;
  void setVersion(const Version& version);
  ContextProfile getProfile() const;
  void setProfile(ContextProfile value);
  uint getDepthByteCount() const;
  void setDepthByteCount(uint value);
  uint getStencilByteCount() const;
  void setStencilByteCount(uint value);
  uint getSampleCount() const;
  void setSampleCount(uint value);

public:
  static const ContextSettings Default;

private:
  Version mVersion;
  ContextProfile mProfile;
  uint mDepthByteCount;
  uint mStencilByteCount;
  uint mSampleCount;
};

HOU_GL_API bool operator==(const ContextSettings& l, const ContextSettings& r);
HOU_GL_API bool operator!=(const ContextSettings& l, const ContextSettings& r);

}  // namespace gl

}  // namespace hou

#endif
