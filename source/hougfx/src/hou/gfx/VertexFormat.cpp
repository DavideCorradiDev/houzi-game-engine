// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/VertexFormat.hpp"

#include "hou/gl/GlVertexArrayHandle.hpp"



namespace hou
{

uint VertexFormat::getMaxAttribFormatCount()
{
  return gl::getMaxVertexAttribs();
}



VertexFormat::VertexFormat(ptrdiff_t offset, uint stride,
  const span<const VertexAttribFormat>& vertexAttribFormats)
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



bool operator==(const VertexFormat& lhs, const VertexFormat& rhs)
{
  return lhs.getOffset() == rhs.getOffset()
    && lhs.getStride() == rhs.getStride()
    && lhs.getVertexAttribFormats() == rhs.getVertexAttribFormats();
}



bool operator!=(const VertexFormat& lhs, const VertexFormat& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const VertexFormat& vf)
{
  return os << "{Offset = " << vf.getOffset() << ", Stride = " << vf.getStride()
            << ", VertexAttribFormats = " << vf.getVertexAttribFormats() << "}";
}

}  // namespace hou
