// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_FWD_HPP
#define HOU_GFX_TEXTURE_FWD_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gfx/texture_type.hpp"



namespace hou
{

class texture;

template <texture_type type>
class texture_t;

using texture1 = texture_t<texture_type::texture1>;
using texture1_array = texture_t<texture_type::texture1_array>;
using texture2 = texture_t<texture_type::texture2>;
using texture2_array = texture_t<texture_type::texture2_array>;
using texture3 = texture_t<texture_type::texture3>;
using multisample_texture2 = texture_t<texture_type::multisample_texture2>;
using multisample_texture2_array
  = texture_t<texture_type::multisample_texture2_array>;

}  // namespace hou

#endif
