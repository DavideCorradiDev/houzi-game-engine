// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_TYPE_HPP
#define HOU_GFX_TEXTURE_TYPE_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gl/OpenGl.hpp"

#include <iostream>



namespace hou
{

enum class TextureType : GLenum
{
  Texture1 = GL_TEXTURE_1D,
  Texture1Array = GL_TEXTURE_1D_ARRAY,
  Texture2 = GL_TEXTURE_2D,
  Texture2Array = GL_TEXTURE_2D_ARRAY,
  Texture3 = GL_TEXTURE_3D,
  MultisampleTexture2 = GL_TEXTURE_2D_MULTISAMPLE,
  MultisampleTexture2Array = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
  // BufferTexture = GL_TEXTURE_BUFFER,
  // RectangleTexture = GL_TEXTURE_RECTANGLE,
  // CubeMapTexture = GL_TEXTURE_CUBE_MAP,
  // CubeMapArrayTexture = GL_TEXTURE_CUBE_MAP_ARRAY,
};

HOU_GFX_API std::ostream& operator<<(std::ostream& os, TextureType type);

constexpr size_t getTextureTypeDimensionCount(TextureType t);
constexpr bool isTextureTypeMipMapped(TextureType t);
constexpr bool isTextureTypeMultisampled(TextureType t);

}  // namespace hou



#include "hou/gfx/TextureType.inl"

#endif
