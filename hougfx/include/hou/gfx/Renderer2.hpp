// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_MESH_2_RENDERER_HPP
#define HOU_GFX_MESH_2_RENDERER_HPP

#include "hou/gfx/GfxExport.hpp"
#include "hou/cor/NonCopyable.hpp"

#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/Vertex2.hpp"
#include "hou/gfx/Mesh2ShaderProgram.hpp"
#include "hou/gfx/TextShaderProgram.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/mth/Transform2Fwd.hpp"



namespace hou
{

class Color;
class Font;
class RenderFont;
class RenderSurface;

/** Class capable of rendering Mesh2 objects and text.
 */
class HOU_GFX_API Renderer2
  : public NonCopyable
{
public:
  /** Creates a Renderer2 object.
   */
  Renderer2();

  /** Move constructor.
   *
   *  \other the other Renderer2 object.
   */
  Renderer2(Renderer2&& other);

  /** Draws a text onto a RenderSurface.
   *
   *  \param target the RenderSurface to be drawn onto.
   *  \param text the text to be drawn.
   *  \param font the font to use to draw the text.
   *  \param color the color to use to draw the mesh.
   *  \param trans the transform to use to draw the mesh.
   */
  void draw
    ( RenderSurface& target
    , const std::string& text
    , Font& font
    , const Color& color
    , const Trans2f& trans);

  void draw
    ( RenderSurface& target
    , const std::string& text
    , const RenderFont& font
    , const Color& color
    , const Trans2f& trans);

private:
  Texture2 mDefaultTexture;
  Mesh2ShaderProgram mShaderProgram;
  TextShaderProgram mTextShaderProgram;
};

}

#endif

