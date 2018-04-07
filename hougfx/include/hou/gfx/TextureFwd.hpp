// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_TEXTURE_FWD_HPP
#define HOU_GFX_TEXTURE_FWD_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gfx/TextureType.hpp"



namespace hou
{

class Texture;

template <TextureType type>
class TextureTemplate;

using Texture1 = TextureTemplate<TextureType::Texture1>;
using Texture1Array = TextureTemplate<TextureType::Texture1Array>;
using Texture2 = TextureTemplate<TextureType::Texture2>;
using Texture2Array = TextureTemplate<TextureType::Texture2Array>;
using Texture3 = TextureTemplate<TextureType::Texture3>;
using MultisampleTexture2 = TextureTemplate<TextureType::MultisampleTexture2>;
using MultisampleTexture2Array
  = TextureTemplate<TextureType::MultisampleTexture2Array>;

}  // namespace hou

#endif
