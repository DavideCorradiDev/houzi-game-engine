// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/VertexAttribFormat.hpp"

#include "hou/cor/std_string.hpp"



namespace hou
{

VertexAttribFormat::VertexAttribFormat(
  gl_type type, uint elementCount, uint byteOffset, bool mustBeNormalized)
  : m_type(type)
  , m_element_count(elementCount)
  , mByteOffset(byteOffset)
  , mMustBeNormalized(mustBeNormalized)
{}



gl_type VertexAttribFormat::get_type() const
{
  return m_type;
}



uint VertexAttribFormat::getElementCount() const
{
  return m_element_count;
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
  return lhs.get_type() == rhs.get_type()
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
  return os << "{Type = " << vf.get_type()
            << ", ElementCount = " << vf.getElementCount()
            << ", byte_offset = " << vf.getByteOffset()
            << ", MustBeNormalized = " << to_string(vf.mustBeNormalized())
            << "}";
}

}  // namespace hou
