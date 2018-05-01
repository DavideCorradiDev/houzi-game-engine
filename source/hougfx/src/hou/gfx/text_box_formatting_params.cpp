#include "hou/gfx/text_box_formatting_params.hpp"



namespace hou
{

const text_box_formatting_params text_box_formatting_params::standard(
  text_flow::LeftRight, vec2f::zero());



text_box_formatting_params::text_box_formatting_params(
  text_flow text_flow, const vec2f& max_size)
  : m_text_flow(text_flow)
  , m_max_size(max_size)
{}



text_flow text_box_formatting_params::get_text_flow() const
{
  return m_text_flow;
}



const vec2f& text_box_formatting_params::get_max_size() const
{
  return m_max_size;
}

}  // namespace hou
