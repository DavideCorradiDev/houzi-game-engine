// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_VERTEX_ATTRIB_FORMAT_HPP
#define HOU_GFX_VERTEX_ATTRIB_FORMAT_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"

#include "hou/gfx/GlType.hpp"

#include <iostream>



namespace hou
{

class HOU_GFX_API VertexAttribFormat
{
public:
  VertexAttribFormat(
    GlType type, uint elementCount, uint byteOffset, bool mustBeNormalized);

  GlType getType() const;
  uint getElementCount() const;
  uint getByteOffset() const;
  bool mustBeNormalized() const;

private:
  GlType mType;
  uint mElementCount;
  uint mByteOffset;
  GLboolean mMustBeNormalized;
};

HOU_GFX_API bool operator==(
  const VertexAttribFormat& l, const VertexAttribFormat& r);
HOU_GFX_API bool operator!=(
  const VertexAttribFormat& l, const VertexAttribFormat& r);
HOU_GFX_API std::ostream& operator<<(
  std::ostream& os, const VertexAttribFormat& vf);

}  // namespace hou

#endif
