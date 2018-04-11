// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_RENDER_BUFFER_FWD_HPP
#define HOU_GFX_RENDER_BUFFER_FWD_HPP

namespace hou
{

class RenderBuffer;

template <typename T, bool dynamicStorage>
class RenderBufferT;

template <typename T>
using StaticRenderBuffer = RenderBufferT<T, false>;

template <typename T>
using DynamicRenderBuffer = RenderBufferT<T, true>;

}  // namespace hou

#endif
