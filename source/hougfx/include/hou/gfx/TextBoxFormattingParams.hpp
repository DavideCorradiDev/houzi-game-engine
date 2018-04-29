// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_BOX_FORMATTING_PARAMS_HPP
#define HOU_GFX_TEXT_BOX_FORMATTING_PARAMS_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/mth/matrix.hpp"

#include "hou/gfx/TextFlow.hpp"



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
   * \param textFlow the text flow direction.
   * \param maxSize the maximum text box size.
   */
  text_box_formatting_params(TextFlow textFlow, const vec2f& maxSize);

  /** Retrieves the text flow parameter.
   *
   * \return the text flow parameter.
   */
  TextFlow get_text_flow() const;

  /** Retrieves the maximum text box size.
   *
   * \return the maximum text box size.
   */
  const vec2f& get_max_size() const;

private:
  TextFlow m_text_flow;
  vec2f m_max_size;
};

}  // namespace hou

#endif
