// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_RENDER_TEXTURE_HPP
#define HOU_GFX_RENDER_TEXTURE_HPP

#include "hou/gfx/GfxExport.hpp"
#include "hou/gfx/RenderSurface.hpp"



namespace hou
{

/** Surface for off-screen rendering.
 */
class HOU_GFX_API RenderTexture
  : public RenderSurface
{
public:
  /** Creates a RenderTexutre with the desired size and sample count.
   *
   *  \param size the size.
   *  \param sampleCount the sample count.
   */
  RenderTexture(const Vec2u& size, uint sampleCount);

  /** Move constructor.
   *
   *  \param other the other RenderTexture.
   */
  RenderTexture(RenderTexture&& other);

  /** Destructor.
   */
  virtual ~RenderTexture();

  //. RenderSurface overrides.
  void setSize(const Vec2u& size) override;
  Texture2 toTexture() const override;
};

}

#endif

