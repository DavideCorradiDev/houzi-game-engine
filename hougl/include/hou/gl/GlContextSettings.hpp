// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GL_CONTEXT_SETTINGS_HPP
#define HOU_GL_CONTEXT_SETTINGS_HPP

#include "hou/gl/GlExport.hpp"

#include "hou/gl/GlContextProfile.hpp"
#include "hou/gl/GlVersion.hpp"

#include "hou/cor/BasicTypes.hpp"



namespace hou
{

namespace gl
{

class HOU_GL_API ContextSettings
{
public:
  ContextSettings
    ( const Version& version
    , ContextProfile profile
    , uint depthBits
    , uint stencilBits
    , uint antiAliasingLevel);

  const Version& getVersion() const;
  void setVersion(const Version& version);
  ContextProfile getProfile() const;
  void setProfile(ContextProfile value);
  uint getDepthBits() const;
  void setDepthBits(uint value);
  uint getStencilBits() const;
  void setStencilBits(uint value);
  uint getAntialiasingLevel() const;
  void setAntialiasingLevel(uint value);

public:
  static const ContextSettings Default;

private:
  Version mVersion;
  ContextProfile mProfile;
  uint mDepthBits;
  uint mStencilBits;
  uint mAntiAliasingLevel;
};

HOU_GL_API bool operator==(const ContextSettings& l
  , const ContextSettings& r);
HOU_GL_API bool operator!=(const ContextSettings& l
  , const ContextSettings& r);

}

}

#endif
