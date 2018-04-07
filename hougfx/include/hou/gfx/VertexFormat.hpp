// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_VERTEX_FORMAT
#define HOU_GFX_VERTEX_FORMAT

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/StdVector.hpp"
#include "hou/cor/Span.hpp"

#include "hou/gfx/VertexAttribFormat.hpp"

#include <iostream>



namespace hou
{

class HOU_GFX_API VertexFormat
{
public:
  static uint getMaxAttribFormatCount();

public:
  VertexFormat(ptrdiff_t offset, uint stride,
    const Span<const VertexAttribFormat>& vertexAttribFormats);
  VertexFormat(ptrdiff_t offset, uint stride,
    std::vector<VertexAttribFormat>&& vertexAttribFormats);

  ptrdiff_t getOffset() const;
  uint getStride() const;
  const std::vector<VertexAttribFormat>& getVertexAttribFormats() const;

private:
  ptrdiff_t mOffset;
  uint mStride;
  std::vector<VertexAttribFormat> mVertexAttribFormats;
};

HOU_GFX_API bool operator==(const VertexFormat& l, const VertexFormat& r);
HOU_GFX_API bool operator!=(const VertexFormat& l, const VertexFormat& r);
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const VertexFormat& r);

}  // namespace hou

#endif
