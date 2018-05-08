// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FRAME_BUFFER_HPP
#define HOU_GFX_FRAME_BUFFER_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gfx/framebuffer_blit_filter.hpp"
#include "hou/gfx/framebuffer_blit_mask.hpp"

#include "hou/gfx/gfx_export.hpp"

#include "hou/mth/rectangle_fwd.hpp"

#include "hou/gl/gl_framebuffer_handle.hpp"



namespace hou
{

class texture;

/** Represents a user defined framebuffer.
 */
class HOU_GFX_API framebuffer : public non_copyable
{
public:
  /** Binds a framebuffer as the target for drawing operations.
   *
   * \param fb the framebuffer.
   *
   * \throws hou::precondition_violation if fb is not complete.
   */
  static void bind_draw_target(const framebuffer& fb);

  /** Binds a framebuffer as the source framebuffer.
   *
   * \param fb the framebuffer.
   *
   * \throws hou::precondition_violation if fb is not complete.
   */
  static void bind_read_target(const framebuffer& fb);

  /** Binds a framebuffer as both target and source.
   *
   * \param fb the framebuffer.
   *
   * \throws hou::precondition_violation if fb is not complete.
   */
  static void bind(const framebuffer& fb);

  /** Unbinds the current draw framebuffer.
   */
  static void unbind_draw_target();

  /** Unbinds the current read framebuffer.
   */
  static void unbind_read_target();

  /** Unbinds the current draw and read framebuffer objects.
   */
  static void unbind();

  /** Retrieves the number of available slots for color attachments in a
   * framebuffer.
   *
   * \return the number of available slots for color attachments.
   */
  static uint get_color_attachment_point_count();

public:
  /** default constructor.
   */
  framebuffer();

  /** Move constructor.
   *
   * \param other the other framebuffer.
   */
  framebuffer(framebuffer&& other) noexcept;

  /** Retrieves a reference to the OpenGL framebuffer handle.
   *
   * \return a reference to the OpenGL framebuffer handle.
   */
  const gl::framebuffer_handle& get_handle() const noexcept;

  /** Checks if this framebuffer is currently bound as draw target.
   *
   * \return the result of the check.
   */
  bool is_bound_to_draw_target() const;

  /** Checks if this framebuffer is currently bound as read target.
   *
   * \return the result of the check.
   */
  bool is_bound_to_read_target() const;

  /** Checks if this framebuffer is complete.
   *
   * Only complete framebuffer objects can be bound or used as source or
   * destination for blit destination. Using an incomplete framebuffer will
   * cause an exception to be thrown.
   *
   * \return the result of the check.
   */
  bool is_complete() const;

  /** Sets a color attachment for this framebuffer.
   *
   * \param attachment_point an index representing the desired attachment point.
   * Its value must be lower than the maximum number of available attachment
   * points.
   *
   * \param tex the texture to be attached. The format of the
   * texture must be r, rg, rgb, or rgba.
   *
   * \param mipmap_level the mip map level
   * to bind. It must be a valid mip map level of texture.
   *
   * \throws hou::precondition_violation if attachment_point is greater or equal
   * than the number of allowed attachments, if mipmap_level is greater or equal
   * then the number of mipmap levels of tex, or if the format of tex is not r,
   * rg, rgb, or rgba.
   */
  void set_color_attachment(
    uint attachment_point, const texture& tex, uint mipmap_level = 0u);

  /** Sets the depth attachment for this framebuffer.
   *
   * \param tex the texture to be attached. The format of the texture must
   * be depth or depth_stencil.
   *
   * \param mipmap_level the mip map level to bind. It must be a valid mip map
   * level of texture.
   *
   * \throws hou::precondition_violation if mipmap_level is greater or equal
   * then the number of mipmap levels of tex, or if the format of tex is not
   * depth or depth_stencil.
   */
  void set_depth_attachment(const texture& tex, uint mipmap_level = 0u);

  /** Sets the stencil attachment for this framebuffer.
   *
   * \param tex the texture to be attached. The format of the texture must
   * be stencil or depth_stencil.
   *
   * \param mipmap_level the mip map level to bind. It must be a valid mip map
   * level of texture.
   *
   * \throws hou::precondition_violation if mipmap_level is greater or equal
   * then the number of mipmap levels of tex, or if the format of tex is not
   * stencil or depth_stencil.
   */
  void set_stencil_attachment(const texture& tex, uint mipmap_level = 0u);

  /** Sets the depth and stencil attachment for this framebuffer.
   *
   * \param tex the texture to be attached. The format of the texture must
   * be depth_stencil.
   *
   * \param mipmap_level the mip map level to bind. It must be a valid mip map
   * level of texture.
   *
   * \throws hou::precondition_violation if mipmap_level is greater or equal
   * then the number of mipmap levels of tex, or if the format of tex is not
   * depth_stencil.
   */
  void set_depth_stencil_attachment(const texture& tex, uint mipmap_level = 0u);

  /** Checks if this framebuffer has a multisample attachment.
   *
   * \return the result of the check.
   */
  bool has_multisample_attachment() const;

private:
  gl::framebuffer_handle m_handle;
  bool m_has_multisample_color_attachment;
  bool m_has_multisample_depth_attachment;
  bool m_has_multisample_stencil_attachment;
};

/** Copies a rectangular region of a framebuffer into another framebuffer.
 *
 * The following constraints must be observed, or an exception will be thrown:
 *
 * * src and dst must be complete framebuffer objects.
 *
 * * If src or dst are multisampled, src_rect and dst_rect must have the same
 * size.
 *
 * * If mask contains depth or stencil, filter must be set to nearest.
 *
 * \param src the source framebuffer.
 *
 * \param src_rect the source rectangle.
 *
 * \param dst the destination framebuffer.
 *
 * \param dst_rect the destination rectangle.
 *
 * \param mask a bitfield specifying what attachments to blit.
 *
 * \param filter the filter to apply for this operation.
 *
 * \throws hou::precondition_violation if one condition on the arguments is
 * violated.
 */
HOU_GFX_API void blit(const framebuffer& src, const recti& src_rect,
  framebuffer& dst, const recti& dst_rect, framebuffer_blit_mask mask,
  framebuffer_blit_filter filter = framebuffer_blit_filter::nearest);

/** Copies a rectangular region of a framebuffer into a texture.
 *
 * The following constraints must be observed, or an exception will be thrown:
 *
 * * src must be complete framebuffer object.
 *
 * * If src or dst are multisampled, src_rect and dst_rect must have the same
 * size.
 *
 * \param src the source framebuffer.
 *
 * \param src_rect the source rectangle.
 *
 * \param dst the destination texture.
 *
 * \param dst_rect the destination rectangle.
 *
 * \param filter the filter to apply for this operation.
 *
 * \throws hou::precondition_violation if one condition on the arguments is
 * violated.
 */
HOU_GFX_API void blit(const framebuffer& src, const recti& src_rect,
  texture& dst, const recti& dst_rect,
  framebuffer_blit_filter filter = framebuffer_blit_filter::nearest);

/** Copies a rectangular region of a texture into a framebuffer.
 *
 * The following constraints must be observed, or an exception will be thrown:
 * * dst must be complete framebuffer object.
 * * If src or dst are multisampled, src_rect and dst_rect must have the same
 * size.
 *
 * \param src the source texture.
 *
 * \param src_rect the source rectangle.
 *
 * \param dst the destination framebuffer.
 *
 * \param dst_rect the destination rectangle.
 *
 * \param filter the filter to apply for this operation.
 *
 * \throws hou::precondition_violation if one condition on the arguments is
 * violated.
 */
HOU_GFX_API void blit(const texture& src, const recti& src_rect,
  framebuffer& dst, const recti& dst_rect,
  framebuffer_blit_filter filter = framebuffer_blit_filter::nearest);

/** Copies a rectangular region of a texture into a framebuffer.
 *
 * The following constraints must be observed, or an exception will be thrown:
 *
 * * dst must be complete framebuffer object.
 *
 * * If src or dst are multisampled, src_rect and dst_rect must have the same
 * size.
 *
 * \param src the source texture.
 *
 * \param src_rect the source rectangle.
 *
 * \param dst the destination texture.
 *
 * \param dst_rect the destination rectangle.
 *
 * \param filter the filter to apply for this operation.
 *
 * \throws hou::precondition_violation if one condition on the arguments is
 * violated.
 */
HOU_GFX_API void blit(const texture& src, const recti& src_rect, texture& dst,
  const recti& dst_rect,
  framebuffer_blit_filter filter = framebuffer_blit_filter::nearest);

}  // namespace hou

#endif
