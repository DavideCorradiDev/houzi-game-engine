#include "hou/cor/CorError.hpp"



namespace hou
{

std::string getText(CorError ec)
{
  switch(ec)
  {
    case CorError::InvalidEnum:
      return u8"Invalid enum (%d).";
    case CorError::Overflow:
      return u8"Variable overflow.";
    case CorError::Postcondition:
      return u8"Postcondition check failure";
    case CorError::Precondition:
      return u8"Precondition check failure";
    default:
      return u8"";
  }
}

}

