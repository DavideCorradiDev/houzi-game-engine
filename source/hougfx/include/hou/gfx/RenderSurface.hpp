// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_RENDER_SURFACE_HPP
#define HOU_GFX_RENDER_SURFACE_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/gfx_export.hpp"

#include "hou/gfx/framebuffer.hpp"
#include "hou/gfx/texture.hpp"

#include "hou/mth/matrix_fwd.hpp"
#include "hou/mth/rectangle.hpp"

#include <memory>



namespace hou
{

class color;

/** Abstract base class for surfaces that can be rendered onto.
 */
class HOU_GFX_API render_surface : public non_copyable
{
public:
  /** Makes this render_surface the current render source.
   *
   *  \param rs the render surface.
   */
  static void set_current_render_source(const render_surface& rs);

  /** Sets the default render surface as the render source.
   *
   *  The default render source is that of the currently bound ph_window.
   */
  static void set_default_render_source();

  /** Makes this render_surface the current render target.
   *
   *  \param rs the render surface.
   */
  static void set_current_render_target(const render_surface& rs);

  /** Sets the default render surface as the render target.
   *
   *  The default render target is that of the currently bound ph_window.
   */
  static void set_default_render_target();

  /** Retrieves the maximum allowed size for the render surface..
   *
   * \return a vector containing the maximum size on each dimension.
   */
  static vec2u get_max_size();

  /** Retrieves the maximum amount of samples per ph_pixel.
   *
   * \return the maximum amount of samples per ph_pixel.
   */
  static uint get_max_sample_count();

public:
  /** Builds a render_surface with the given size and sample count.
   *
   *  Throws if the required sample count is larger than the maximum supported
   * or 0. Throws if the required area of the surface is 0. Throws if the
   * required area is larger than the maximum supported ph_texture size.
   *
   *  \param size the size.
   *  \param sampleCount the sample count.
   */
  render_surface(const vec2u& size, uint sampleCount = 1u);

  /** Move constructor.
   *
   *  \param other the other render_surface.
   */
  render_surface(render_surface&& other);

  /** Destructor.
   */
  virtual ~render_surface() = 0;

  /** Gets the default viewport ph_rectangle.
   *
   *  The default viewport ph_rectangle has the top left corner at the origin
   *  and side lengths equal to the size of the render_surface.
   *
   *  \return the default viewport ph_rectangle.
   */
  recti get_default_viewport() const;

  /** Gets the current viewport ph_rectangle.
   *
   *  The viewport ph_rectangle represents the area of the render_surface which is
   *  drawn onto.
   *  For a newly created render_surface the viewport ph_rectangle is the default
   *  viewport ph_rectangle.
   *
   *  \return the current viewport ph_rectangle.
   */
  const recti& get_viewport() const;

  /** Sets the current viewport ph_rectangle.
   *
   *  \param viewport the desired viewport ph_rectangle.
   */
  void set_viewport(const recti& viewport);

  /** Gets the size of the render_surface.
   *
   *  \return the size of the render surface.
   */
  vec2u get_size() const;

  /** Checks if the render_surface is multisampled.
   *
   *  \return true if the number of samples of the render_surface is greater than
   *  one.
   */
  bool is_multisampled() const;

  /** Gets the number of samples of the render_surface.
   *
   *  \return the number of samples of the render_surface.
   */
  uint get_sample_count() const;

  /** Clears the render_surface to the desired ph_color.
   *
   *  \param ph_color the desired ph_color.
   */
  void clear(const color& ph_color);

  /** Creates a texture2 from this render_surface.
   *
   *  The generated texture2 has rgba format.
   *  Throws if the render_surface is multisampled. Only single sampled
   *  render_surface objects can be converted to textures.
   *
   *  \return the texture2 create from this render_surface.
   */
  texture2 to_texture() const;

  /** Checks if this render_surface is the current render source.
   *
   *  \return true if this is the current render source.
   */
  bool is_current_render_source() const;

  /** Checks if this render_surface is the current render target.
   *
   *  \return true if this is the current render target.
   */
  bool is_current_render_target() const;

  /** Blits the render_surface onto another render_surface.
   *
   *  Throws if blitting is performed between two render_surface objects with
   *  different sample count and source and destination rectangles with
   *  different size.
   *  Blitting between two render_surface objects with different sample count
   *  but source and destination ph_rectangle with the same size, or with
   *  source and destination ph_rectangle with same size but different sample count
   *  is possible.
   *  If the size of the source and destination ph_rectangle is the same but
   *  inverted, it counts as the same for the purpose of this check.
   *
   *  \param dst the destination render_surface.
   *  \param srcRect the source ph_rectangle of the blit operation.
   *  \param dstRect the destination ph_rectangle of the blit operation.
   */
  friend HOU_GFX_API void blit(const render_surface& src, const recti& srcRect,
    render_surface& dst, const recti& dstRect,
    framebuffer_blit_filter filter = framebuffer_blit_filter::nearest);

  friend HOU_GFX_API void blit(const render_surface& src, const recti& srcRect,
    texture& dst, const recti& dstRect,
    framebuffer_blit_filter filter = framebuffer_blit_filter::nearest);

  friend HOU_GFX_API void blit(const texture& src, const recti& srcRect,
    render_surface& dst, const recti& dstRect,
    framebuffer_blit_filter filter = framebuffer_blit_filter::nearest);

protected:
  void build_framebuffer(const vec2u& size, uint sampleCount);

private:
  using attachment_type = texture2;
  using multisample_attachment_type = multisample_texture2;

private:
  framebuffer m_framebuffer;
  std::unique_ptr<texture> m_color_attachment;
  std::unique_ptr<texture> m_depth_stencil_attachment;
  uint m_sample_count;
  recti m_viewport;
};

}  // namespace hou

#endif
