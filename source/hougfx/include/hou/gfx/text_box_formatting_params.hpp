// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_BOX_FORMATTING_PARAMS_HPP
#define HOU_GFX_TEXT_BOX_FORMATTING_PARAMS_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/mth/matrix.hpp"

#include "hou/gfx/text_flow.hpp"



namespace hou
{

/** Represents a collection of text box formatting parameters.
 */
class HOU_GFX_API text_box_formatting_params
{
public:
  /** default parameters.
   */
  static const text_box_formatting_params standard;

public:
  /** Creates an object with the given parameters.
   *
   * \param text_flow the text flow direction.
   *
   * \param max_size the maximum text box size.
   */
  text_box_formatting_params(
    text_flow text_flow, const vec2f& max_size) noexcept;

  /** Retrieves the text flow parameter.
   *
   * \return the text flow parameter.
   */
  text_flow get_text_flow() const noexcept;

  /** Retrieves the maximum text box size.
   *
   * \return the maximum text box size.
   */
  const vec2f& get_max_size() const noexcept;

private:
  text_flow m_text_flow;
  vec2f m_max_size;
};

}  // namespace hou

#endif
