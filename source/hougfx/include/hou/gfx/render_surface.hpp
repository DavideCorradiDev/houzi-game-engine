// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_RENDER_SURFACE_HPP
#define HOU_GFX_RENDER_SURFACE_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gfx/framebuffer.hpp"
#include "hou/gfx/multisampled_texture2.hpp"
#include "hou/gfx/texture2.hpp"

#include "hou/gfx/gfx_config.hpp"

#include "hou/mth/matrix_fwd.hpp"
#include "hou/mth/rectangle.hpp"

#include <memory>



namespace hou
{

class color;

/**
 * Abstract base class for surfaces that can be rendered onto.
 *
 * The view port of the render surface will not be adjusted if the size of the
 * window changes for any reason. It must be adjusted manually. This can
 * normally be achieved simply by reacting to resizing events from the window
 * event queue.
 */
class HOU_GFX_API render_surface : public non_copyable
{
public:
  /**
   * Makes this render_surface the current render source.
   *
   * \param rs the render surface.
   */
  static void set_current_render_source(const render_surface& rs);

  /**
   * Sets the default render surface as the render source.
   *
   * The default render source is that of the currently bound window.
   */
  static void set_default_render_source();

  /**
   * Makes this render_surface the current render target.
   *
   * \param rs the render surface.
   */
  static void set_current_render_target(const render_surface& rs);

  /**
   * Sets the default render surface as the render target.
   *
   * The default render target is that of the currently bound window.
   */
  static void set_default_render_target();

  /**
   * Retrieves the maximum allowed size for the render surface.
   *
   * \return a vector containing the maximum size on each dimension.
   */
  static vec2u get_max_size();

  /**
   * Retrieves the maximum amount of samples per pixel.
   *
   * \return the maximum amount of samples per pixel.
   */
  static positive<uint> get_max_sample_count();

public:
  /**
   * Builds a render_surface with the given size and sample count.
   *
   * Throws if the required sample count is larger than the maximum supported
   * or 0. Throws if the required area of the surface is 0. Throws if the
   * required area is larger than the maximum supported texture size.
   *
   * \param size the size.
   *
   * \param sample_count the sample count.
   */
  render_surface(const vec2u& size, positive<uint> sample_count = 1u);

  /**
   * Move constructor.
   *
   * \param other the other render_surface.
   */
  render_surface(render_surface&& other) = default;

  /**
   * Gets the default viewport rectangle.
   *
   * The default viewport rectangle has the top left corner at the origin
   * and side lengths equal to the size of the render_surface.
   *
   * \return the default viewport rectangle.
   */
  recti get_default_viewport() const;

  /**
   * Gets the current viewport rectangle.
   *
   * The viewport rectangle represents the area of the render_surface which is
   * drawn onto.
   * For a newly created render_surface the viewport rectangle is the default
   * viewport rectangle.
   *
   * \return the current viewport rectangle.
   */
  const recti& get_viewport() const noexcept;

  /**
   * Sets the current viewport rectangle.
   *
   * \param viewport the desired viewport rectangle.
   */
  void set_viewport(const recti& viewport);

  /**
   * Gets the size.
   *
   * \return the size.
   */
  vec2u get_size() const;

  /**
   * Sets the size.
   *
   * \note the contents of the render surface will be deleted.
   *
   * \param size the size.
   */
  void set_size(const vec2u& size);

  /**
   * Checks if the render surface is multisampled.
   *
   * \return true if the number of samples of the render surface is greater than
   * one.
   */
  bool is_multisampled() const noexcept;

  /**
   * Gets the number of samples.
   *
   * \return the number of samples.
   */
  positive<uint> get_sample_count() const noexcept;

  /**
   * Sets the number of samples.
   *
   * \note the contents of the render surface will be deleted.
   *
   * \param sample_count the number of samples.
   */
  void set_sample_count(positive<uint> sample_count);

  /**
   * Clears the render_surface to the desired color.
   *
   * \param color the desired color.
   */
  void clear(const color& color);

  /**
   * Creates a texture2 from this render_surface.
   *
   * The generated texture2 has rgba format.
   * Throws if the render_surface is multisampled. Only single sampled
   * render_surface objects can be converted to textures.
   *
   * \return the texture2 create from this render_surface.
   */
  texture2 to_texture() const;

  /**
   * Copies the content of the render_surface onto the current window
   * framebuffer and swaps the current window framebuffers.
   */
  void display() const;

  /**
   * Checks if this render_surface is the current render source.
   *
   * \return true if this is the current render source.
   */
  bool is_current_render_source() const;

  /**
   * Checks if this render_surface is the current render target.
   *
   *  \return true if this is the current render target.
   */
  bool is_current_render_target() const;


protected:
  /**
   * Rebuilds the framebuffer and associated textures.
   *
   * Each time size or sample_count change this function should be called.
   *
   * \param size the new size.
   *
   * \param sample_count the new sample count.
   */
  void build_framebuffer(const vec2u& size, positive<uint> sample_count);

private:
  friend HOU_GFX_API void blit(const render_surface& src, const recti& src_rect,
    render_surface& dst, const recti& dst_rect, framebuffer_blit_filter filter);

  friend HOU_GFX_API void blit(const render_surface& src, const recti& src_rect,
    texture& dst, const recti& dst_rect, framebuffer_blit_filter filter);

  friend HOU_GFX_API void blit(const texture& src, const recti& src_rect,
    render_surface& dst, const recti& dst_rect, framebuffer_blit_filter filter);

private:
  using attachment_type = texture2;
  using multisample_attachment_type = multisampled_texture2;

private:
  framebuffer m_framebuffer;
  std::unique_ptr<texture2_base> m_color_attachment;
  std::unique_ptr<texture2_base> m_depth_stencil_attachment;
  recti m_viewport;
};

/**
 * Blits the render_surface onto another render_surface.
 *
 * Throws if blitting is performed between two render_surface objects with
 * different sample count and source and destination rectangles with
 * different size.
 *
 * Blitting between two render_surface objects with different sample count
 * but source and destination rectangle with the same size, or with
 * source and destination rectangle with same size but different sample count
 * is possible.
 *
 * If the size of the source and destination rectangle is the same but
 * inverted, it counts as the same for the purpose of this check.
 *
 * \param src the source render_surface.
 *
 * \param dst the destination render_surface.
 *
 * \param src_rect the source rectangle of the blit operation.
 *
 * \param dst_rect the destination rectangle of the blit operation.
 *
 * \param filter the blit filter.
 *
 * \throws hou::precondition_violation if one argument doesn't satisfies the
 * consttraints.
 */
HOU_GFX_API void blit(const render_surface& src, const recti& src_rect,
  render_surface& dst, const recti& dst_rect,
  framebuffer_blit_filter filter = framebuffer_blit_filter::nearest);

}  // namespace hou

#endif
