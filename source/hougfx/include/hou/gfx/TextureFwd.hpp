// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_FWD_HPP
#define HOU_GFX_TEXTURE_FWD_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gfx/TextureType.hpp"



namespace hou
{

class Texture;

template <TextureType type>
class TextureT;

using Texture1 = TextureT<TextureType::Texture1>;
using Texture1Array = TextureT<TextureType::Texture1Array>;
using Texture2 = TextureT<TextureType::Texture2>;
using Texture2Array = TextureT<TextureType::Texture2Array>;
using Texture3 = TextureT<TextureType::Texture3>;
using MultisampleTexture2 = TextureT<TextureType::MultisampleTexture2>;
using MultisampleTexture2Array
  = TextureT<TextureType::MultisampleTexture2Array>;

}  // namespace hou

#endif
