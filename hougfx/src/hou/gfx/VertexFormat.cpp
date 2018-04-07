// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/VertexFormat.hpp"

#include "hou/gl/GlVertexArrayHandle.hpp"



namespace hou
{

uint VertexFormat::getMaxAttribFormatCount()
{
  return gl::getMaxVertexAttribs();
}



VertexFormat::VertexFormat(ptrdiff_t offset, uint stride,
  const Span<const VertexAttribFormat>& vertexAttribFormats)
  : mOffset(offset)
  , mStride(stride)
  , mVertexAttribFormats(vertexAttribFormats.begin(), vertexAttribFormats.end())
{
  HOU_EXPECT(mVertexAttribFormats.size() <= getMaxAttribFormatCount());
}



VertexFormat::VertexFormat(ptrdiff_t offset, uint stride,
    std::vector<VertexAttribFormat>&& vertexAttribFormats)
  : mOffset(offset)
  , mStride(stride)
  , mVertexAttribFormats(std::move(vertexAttribFormats))
{
  HOU_EXPECT(mVertexAttribFormats.size() <= getMaxAttribFormatCount());
}



ptrdiff_t VertexFormat::getOffset() const
{
  return mOffset;
}



uint VertexFormat::getStride() const
{
  return mStride;
}



const std::vector<VertexAttribFormat>& VertexFormat::getVertexAttribFormats()
  const
{
  return mVertexAttribFormats;
}



bool operator==(const VertexFormat& l, const VertexFormat& r)
{
  return l.getOffset() == r.getOffset() && l.getStride() == r.getStride()
    && l.getVertexAttribFormats() == r.getVertexAttribFormats();
}



bool operator!=(const VertexFormat& l, const VertexFormat& r)
{
  return !(l == r);
}



std::ostream& operator<<(std::ostream& os, const VertexFormat& r)
{
  return os << "{Offset = " << r.getOffset() << ", Stride = " << r.getStride()
            << ", VertexAttribFormats = " << r.getVertexAttribFormats() << "}";
}

}  // namespace hou