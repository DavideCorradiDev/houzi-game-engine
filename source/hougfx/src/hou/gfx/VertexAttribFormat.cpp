// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/VertexAttribFormat.hpp"

#include "hou/cor/std_string.hpp"



namespace hou
{

VertexAttribFormat::VertexAttribFormat(
  GlType type, uint elementCount, uint byteOffset, bool mustBeNormalized)
  : mType(type)
  , mElementCount(elementCount)
  , mByteOffset(byteOffset)
  , mMustBeNormalized(mustBeNormalized)
{}



GlType VertexAttribFormat::getType() const
{
  return mType;
}



uint VertexAttribFormat::getElementCount() const
{
  return mElementCount;
}



uint VertexAttribFormat::getByteOffset() const
{
  return mByteOffset;
}



bool VertexAttribFormat::mustBeNormalized() const
{
  return mMustBeNormalized;
}



bool operator==(const VertexAttribFormat& lhs, const VertexAttribFormat& rhs)
{
  return lhs.getType() == rhs.getType()
    && lhs.getElementCount() == rhs.getElementCount()
    && lhs.getByteOffset() == rhs.getByteOffset()
    && lhs.mustBeNormalized() == rhs.mustBeNormalized();
}



bool operator!=(const VertexAttribFormat& lhs, const VertexAttribFormat& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const VertexAttribFormat& vf)
{
  return os << "{Type = " << vf.getType()
            << ", ElementCount = " << vf.getElementCount()
            << ", ByteOffset = " << vf.getByteOffset()
            << ", MustBeNormalized = " << to_string(vf.mustBeNormalized())
            << "}";
}

}  // namespace hou
