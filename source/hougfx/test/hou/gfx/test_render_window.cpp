// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/render_window.hpp"
#include "hou/gfx/texture.hpp"

#include "hou/sys/display.hpp"
#include "hou/sys/event.hpp"

using namespace hou;



namespace
{

class test_render_window : public test_gfx_base
{};

class test_render_window_death_test : public test_render_window
{};

}  // namespace



TEST_F(test_render_window, creation)
{
  render_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_NE(nullptr, w.get_impl());
  EXPECT_NE(0u, w.get_uid());

  EXPECT_LT(w.get_display_index(), display::get_count());
  display_mode curr_mode = display::get_current_mode(w.get_display_index());
  display_mode w_mode
    = display::get_closest_supported_mode(w.get_display_index(),
      display_mode(w.get_window_size(), curr_mode.get_format(),
        curr_mode.get_refresh_rate()));
  EXPECT_EQ(w_mode, w.get_display_mode());
  EXPECT_EQ(window_mode::windowed, w.get_mode());

  EXPECT_EQ(u8"TestWindow", w.get_title());
  EXPECT_EQ(image2_rgba(), w.get_icon());

  EXPECT_EQ(vec2u(32u, 64u), w.get_window_size());
  EXPECT_EQ(vec2u::zero(), w.get_min_size());
  uint max_int = narrow_cast<uint>(std::numeric_limits<int>::max());
  EXPECT_EQ(vec2u(max_int, max_int), w.get_max_size());
  recti bounds = display::get_usable_bounds(w.get_display_index());
  EXPECT_EQ(bounds.get_position() + (bounds.get_size() - vec2i(32, 64)) / 2,
    w.get_position());

  EXPECT_FALSE(w.is_visible());
  EXPECT_FALSE(w.is_minimized());
  EXPECT_FALSE(w.is_maximized());
  EXPECT_FALSE(w.get_grab());
  EXPECT_FALSE(w.is_resizable());
  EXPECT_FALSE(w.is_bordered());

  EXPECT_EQ(
    recti(vec2i(0, 0), w.get_framebuffer_size()), w.get_default_viewport());
  EXPECT_EQ(recti(vec2i(0, 0), w.get_framebuffer_size()), w.get_viewport());
  EXPECT_EQ(vec2u(32u, 64u), w.get_framebuffer_size());
  EXPECT_EQ(1u, w.get_sample_count());
  EXPECT_FALSE(w.is_multisampled());
  EXPECT_EQ(texture2(w.get_framebuffer_size()).get_image<pixel_format::rgba>(),
    w.to_texture().get_image<pixel_format::rgba>());

  EXPECT_EQ(render_window::vsync_mode::disabled, w.get_vsync_mode());
}



TEST_F(test_render_window, creation_multisampled)
{
  render_window w(u8"TestWindow", vec2u(32u, 64u), 2u);

  EXPECT_EQ(2u, w.get_sample_count());
  EXPECT_TRUE(w.is_multisampled());
}



TEST_F(test_render_window, set_size)
{
  render_window w(u8"Test", vec2u(32u, 16u), 4u);

  vec2u size_ref(14u, 17u);
  w.set_size(size_ref);

  EXPECT_EQ(size_ref, w.get_window_size());
  EXPECT_EQ(size_ref, w.get_framebuffer_size());
}



TEST_F(test_render_window, set_size_null_size_x)
{
  render_window w(u8"Test", vec2u(32u, 16u), 4u);

  vec2u size_ref(0u, 17u);
  w.set_size(size_ref);

  EXPECT_EQ(size_ref, w.get_window_size());
  size_ref.x() = 1u;
  EXPECT_EQ(size_ref, w.get_framebuffer_size());
}



TEST_F(test_render_window, set_size_null_size_y)
{
  render_window w(u8"Test", vec2u(32u, 16u), 4u);

  vec2u size_ref(13u, 0u);
  w.set_size(size_ref);

  EXPECT_EQ(size_ref, w.get_window_size());
  size_ref.y() = 1u;
  EXPECT_EQ(size_ref, w.get_framebuffer_size());
}



TEST_F(test_render_window, set_size_null_size)
{
  render_window w(u8"Test", vec2u(32u, 16u), 4u);

  vec2u size_ref = vec2u::zero();
  w.set_size(size_ref);

  EXPECT_EQ(size_ref, w.get_window_size());
  size_ref.x() = 1u;
  size_ref.y() = 1u;
  EXPECT_EQ(size_ref, w.get_framebuffer_size());
}



TEST_F(test_render_window, set_vsync_mode)
{
  render_window w(u8"Test", vec2u(32u, 16u), 4u);
  EXPECT_EQ(render_window::vsync_mode::disabled, w.get_vsync_mode());
  EXPECT_EQ(gl::vsync_mode::disabled, gl::get_vsync_mode());

  w.set_vsync_mode(render_window::vsync_mode::enabled);
  EXPECT_EQ(render_window::vsync_mode::enabled, w.get_vsync_mode());
  EXPECT_EQ(gl::vsync_mode::enabled, gl::get_vsync_mode());

  w.set_vsync_mode(render_window::vsync_mode::adaptive);
  EXPECT_EQ(render_window::vsync_mode::adaptive, w.get_vsync_mode());
  EXPECT_EQ(gl::vsync_mode::adaptive, gl::get_vsync_mode());

  w.set_vsync_mode(render_window::vsync_mode::disabled);
  EXPECT_EQ(render_window::vsync_mode::disabled, w.get_vsync_mode());
  EXPECT_EQ(gl::vsync_mode::disabled, gl::get_vsync_mode());
}



TEST_F(test_render_window, set_samples)
{
  render_window w(u8"Test", vec2u(32u, 16u), 1u);

  w.set_sample_count(1u);
  EXPECT_EQ(1u, w.get_sample_count());
  EXPECT_FALSE(w.is_multisampled());

  w.set_sample_count(2u);
  EXPECT_EQ(2u, w.get_sample_count());
  EXPECT_TRUE(w.is_multisampled());

  w.set_sample_count(render_window::get_max_sample_count());
  EXPECT_EQ(render_window::get_max_sample_count(), w.get_sample_count());
  EXPECT_TRUE(w.is_multisampled());
}



TEST_F(test_render_window_death_test, set_samples_too_large)
{
  render_window w(u8"Test", vec2u(32u, 16u), 1u);
  EXPECT_PRECOND_ERROR(
    w.set_sample_count(render_window::get_max_sample_count() + 1u));
}



TEST_F(test_render_window, resize_frame_buffer_on_pop_resized_event)
{
  vec2u oldSize(vec2u(32u, 16u));
  render_window w(u8"Test", oldSize, 4u);
  vec2u new_size(vec2u(12u, 8u));

  EXPECT_EQ(oldSize, w.get_window_size());
  EXPECT_EQ(oldSize, w.get_framebuffer_size());

  event::generate_window_resized(w, new_size);
  event::process_all();
  EXPECT_EQ(new_size, w.get_window_size());
  EXPECT_EQ(new_size, w.get_framebuffer_size());
}
