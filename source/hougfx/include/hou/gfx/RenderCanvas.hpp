// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_RENDER_CANVAS_HPP
#define HOU_GFX_RENDER_CANVAS_HPP

#include "hou/gfx/GfxExport.hpp"
#include "hou/gfx/RenderSurface.hpp"



namespace hou
{

/** Surface for off-screen rendering.
 */
class HOU_GFX_API RenderCanvas
  : public RenderSurface
{
public:
  /** Creates a RenderTexutre with the desired size and sample count.
   *
   *  \param size the size.
   *  \param sampleCount the sample count.
   */
  RenderCanvas(const vec2u& size, uint sampleCount = 1u);

  /** Move constructor.
   *
   *  \param other the other RenderCanvas.
   */
  RenderCanvas(RenderCanvas&& other);

  /** Destructor.
   */
  virtual ~RenderCanvas();
};

}

#endif

