// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_MESH_2_RENDERER_HPP
#define HOU_GFX_MESH_2_RENDERER_HPP

#include "hou/gfx/GfxExport.hpp"
#include "hou/cor/NonCopyable.hpp"

#include "hou/gfx/Mesh2Fwd.hpp"
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

  /** Draws a Mesh2 object onto a RenderSurface.
   *
   *  \param target the RenderSurface to be drawn onto.
   *  \param mesh the Mesh2 to be drawn.
   *  \param color the color to use to draw the mesh.
   *  \param trans the transform to use to draw the mesh.
   */
  void draw
    ( RenderSurface& target
    , const Mesh2& mesh
    , const Color& color
    , const Trans2f& trans);

  /** Draws a textured Mesh2 object onto a RenderSurface.
   *
   *  \param target the RenderSurface to be drawn onto.
   *  \param mesh the Mesh2 to be drawn.
   *  \param texture the texture to be used.
   *  \param color the color to use to draw the mesh.
   *  \param trans the transform to use to draw the mesh.
   */
  void draw
    ( RenderSurface& target
    , const Mesh2& mesh
    , const Texture2& texture
    , const Color& color
    , const Trans2f& trans);

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

