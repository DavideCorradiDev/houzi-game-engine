// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_FWD_HPP
#define HOU_GFX_TEXTURE_FWD_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/gfx/texture_type.hpp"



namespace hou
{

class texture;

template <texture_type type>
class texture_t;

/** 1 dimensional texture. */
using texture1 = texture_t<texture_type::texture1>;

/** 1 dimensional texture array. */
using texture1_array = texture_t<texture_type::texture1_array>;

/** 2 dimensional texture. */
using texture2 = texture_t<texture_type::texture2>;

/** 2 dimensional texture array. */
using texture2_array = texture_t<texture_type::texture2_array>;

/** 3 dimensional texture. */
using texture3 = texture_t<texture_type::texture3>;

/** 2 dimensional multisampled texture. */
using multisample_texture2 = texture_t<texture_type::multisample_texture2>;

/** 2 dimensional multisampled texture array. */
using multisample_texture2_array
  = texture_t<texture_type::multisample_texture2_array>;

}  // namespace hou

#endif
