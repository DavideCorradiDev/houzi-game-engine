// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_RENDER_BUFFER_FWD_HPP
#define HOU_GFX_RENDER_BUFFER_FWD_HPP

namespace hou
{

class VertexBuffer;

template <typename T, bool dynamicStorage>
class VertexBufferT;

template <typename T>
using StaticVertexBuffer = VertexBufferT<T, false>;

template <typename T>
using DynamicVertexBuffer = VertexBufferT<T, true>;

}  // namespace hou

#endif
