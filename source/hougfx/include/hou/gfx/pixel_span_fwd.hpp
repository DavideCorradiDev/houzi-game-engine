#ifndef HOU_GFX_PIXEL_SPAN_FWD_HPP
#define HOU_GFX_PIXEL_SPAN_FWD_HPP

#include "hou/gfx/gfx_config.hpp"



namespace hou
{

template <size_t Dim>
class pixel_span;

using pixel_span_2 = pixel_span<2u>;
using pixel_span_3 = pixel_span<3u>;

}  // namespace hou

#endif
