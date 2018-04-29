// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_FWD_HPP
#define HOU_GFX_TEXTURE_FWD_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gfx/TextureType.hpp"



namespace hou
{

class texture;

template <TextureType type>
class texture_t;

using texture1 = texture_t<TextureType::texture1>;
using texture1_array = texture_t<TextureType::texture1_array>;
using texture2 = texture_t<TextureType::texture2>;
using texture2_array = texture_t<TextureType::texture2_array>;
using texture3 = texture_t<TextureType::texture3>;
using multisample_texture2 = texture_t<TextureType::multisample_texture2>;
using multisample_texture2_array
  = texture_t<TextureType::multisample_texture2_array>;

}  // namespace hou

#endif
