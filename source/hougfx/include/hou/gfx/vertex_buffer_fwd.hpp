// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_RENDER_BUFFER_FWD_HPP
#define HOU_GFX_RENDER_BUFFER_FWD_HPP

namespace hou
{

class vertex_buffer;

template <typename T, bool DynamicStorage>
class vertex_buffer_t;

/** Unmodifiable vertex buffer. */
template <typename T>
using static_vertex_buffer = vertex_buffer_t<T, false>;

/** Modifiable vertex buffer. */
template <typename T>
using dynamic_vertex_buffer = vertex_buffer_t<T, true>;

}  // namespace hou

#endif
