#include "hou/cor/cor_error.hpp"



namespace hou
{

std::string get_text(cor_error ec)
{
  switch(ec)
  {
    case cor_error::invalid_enum:
      return u8"Invalid enum (%d).";
    case cor_error::overflow:
      return u8"Variable overflow.";
    case cor_error::post_condition:
      return u8"post_condition check failure";
    case cor_error::pre_condition:
      return u8"pre_condition check failure";
    default:
      return u8"";
  }
}

}

