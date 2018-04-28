// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/TextStream.hpp"



namespace hou
{

TextStream::TextPosition TextStream::createPositionObject(long value)
{
  return TextPosition(value);
}



long TextStream::convertPositionObject(TextStream::TextPosition pos)
{
  return pos.mValue;
}



const TextStream::TextPosition TextStream::TextPosition::Start(0u);



TextStream::TextPosition::TextPosition(long value)
  : mValue(value)
{}



bool operator==(TextStream::TextPosition lhs, TextStream::TextPosition rhs)
{
  return lhs.mValue == rhs.mValue;
}



bool operator!=(TextStream::TextPosition lhs, TextStream::TextPosition rhs)
{
  return lhs.mValue != rhs.mValue;
}



std::ostream& operator<<(std::ostream& os, TextStream::TextPosition p)
{
  return os << p;
}

}


