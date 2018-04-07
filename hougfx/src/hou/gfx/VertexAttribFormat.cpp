// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/VertexAttribFormat.hpp"

#include "hou/cor/StdString.hpp"



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



bool operator==(const VertexAttribFormat& l, const VertexAttribFormat& r)
{
  return l.getType() == r.getType()
    && l.getElementCount() == r.getElementCount()
    && l.getByteOffset() == r.getByteOffset()
    && l.mustBeNormalized() == r.mustBeNormalized();
}



bool operator!=(const VertexAttribFormat& l, const VertexAttribFormat& r)
{
  return !(l == r);
}



std::ostream& operator<<(std::ostream& os, const VertexAttribFormat& vf)
{
  return os << "{Type = " << vf.getType()
            << ", ElementCount = " << vf.getElementCount()
            << ", ByteOffset = " << vf.getByteOffset()
            << ", MustBeNormalized = " << toString(vf.mustBeNormalized())
            << "}";
}

}  // namespace hou
