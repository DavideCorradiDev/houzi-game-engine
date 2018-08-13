#ifndef HOU_GFX_PIXEL_VIEW_FWD_HPP
#define HOU_GFX_PIXEL_VIEW_FWD_HPP

#include "hou/gfx/gfx_config.hpp"



namespace hou
{

template <size_t Dim>
class pixel_view;

using pixel_view2 = pixel_view<2u>;
using pixel_view3 = pixel_view<3u>;

}  // namespace hou

#endif
