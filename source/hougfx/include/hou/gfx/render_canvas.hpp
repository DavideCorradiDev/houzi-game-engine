// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_RENDER_CANVAS_HPP
#define HOU_GFX_RENDER_CANVAS_HPP

#include "hou/gfx/render_surface.hpp"

#include "hou/gfx/gfx_config.hpp"



namespace hou
{

/**
 * Surface for off-screen rendering.
 */
class HOU_GFX_API render_canvas final : public render_surface
{
public:
  /**
   * Creates a RenderTexutre with the desired size and sample count.
   *
   * \param size the size.
   *
   * \param sample_count the sample count.
   */
  render_canvas(const vec2u& size, uint sample_count = 1u);

  // render_surface overrides.
  void clear(const color& color) final;
};

}  // namespace hou

#endif
