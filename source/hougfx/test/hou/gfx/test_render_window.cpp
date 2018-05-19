// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/render_window.hpp"
#include "hou/gfx/texture.hpp"

#include "hou/sys/video_mode.hpp"
#include "hou/sys/window_event.hpp"

using namespace hou;



namespace
{

class test_render_window : public test_gfx_base
{};

class test_render_window_death_test : public test_render_window
{};

}  // namespace



TEST_F(test_render_window, creation_windowed)
{
  std::string title_ref(u8"Test");
  vec2u size_ref(16u, 32u);
  vec2u screen_size = video_mode::get_desktop_mode().get_resolution();
  vec2i pos_ref = static_cast<vec2i>(screen_size - size_ref) / 2;
  window_style style_ref = window_style::windowed;
  image2_rgba icon_ref;
  uint samples_ref = 1u;

  render_window w(title_ref, size_ref, style_ref, samples_ref);

  EXPECT_NE(0u, w.get_uid());
  EXPECT_NE(nullptr, w.get_handle());
  EXPECT_EQ(style_ref, w.get_style());
  EXPECT_EQ(pos_ref, w.get_client_position());
  EXPECT_EQ(size_ref, w.get_client_size());
  EXPECT_EQ(
    graphic_context::get_rendering_color_byte_count(), w.get_bytes_per_pixel());
  EXPECT_EQ(title_ref, w.get_title());
  EXPECT_EQ(icon_ref, w.get_icon());
  EXPECT_FALSE(w.is_visible());
  EXPECT_FALSE(w.is_mouse_cursor_grabbed());
  EXPECT_FALSE(w.is_key_repeat_enabled());

  EXPECT_EQ(recti(vec2i::zero(), size_ref), w.get_default_viewport());
  EXPECT_EQ(recti(vec2i::zero(), size_ref), w.get_viewport());
  EXPECT_EQ(size_ref, w.get_size());
  EXPECT_EQ(samples_ref, w.get_sample_count());
  EXPECT_FALSE(w.is_multisampled());
  EXPECT_EQ(texture2(size_ref).get_image<pixel_format::rgba>(),
    w.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_window, creation_windowed_multisampled)
{
  std::string title_ref(u8"Test");
  vec2u size_ref(16u, 32u);
  vec2u screen_size = video_mode::get_desktop_mode().get_resolution();
  vec2i pos_ref = static_cast<vec2i>(screen_size - size_ref) / 2;
  window_style style_ref = window_style::windowed;
  image2_rgba icon_ref;
  uint samples_ref = 4u;

  render_window w(title_ref, size_ref, style_ref, samples_ref);

  EXPECT_NE(0u, w.get_uid());
  EXPECT_NE(nullptr, w.get_handle());
  EXPECT_EQ(style_ref, w.get_style());
  EXPECT_EQ(pos_ref, w.get_client_position());
  EXPECT_EQ(size_ref, w.get_client_size());
  EXPECT_EQ(
    graphic_context::get_rendering_color_byte_count(), w.get_bytes_per_pixel());
  EXPECT_EQ(title_ref, w.get_title());
  EXPECT_EQ(icon_ref, w.get_icon());
  EXPECT_FALSE(w.is_visible());
  EXPECT_FALSE(w.is_mouse_cursor_grabbed());
  EXPECT_FALSE(w.is_key_repeat_enabled());

  EXPECT_EQ(recti(vec2i::zero(), size_ref), w.get_default_viewport());
  EXPECT_EQ(recti(vec2i::zero(), size_ref), w.get_viewport());
  EXPECT_EQ(size_ref, w.get_size());
  EXPECT_EQ(samples_ref, w.get_sample_count());
  EXPECT_TRUE(w.is_multisampled());
  EXPECT_EQ(texture2(size_ref).get_image<pixel_format::rgba>(),
    w.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_window, creation_fullscreen)
{
  std::string title_ref(u8"Test");
  vec2u screen_size = video_mode::get_desktop_mode().get_resolution();
  vec2u size_ref = screen_size;
  vec2i pos_ref = static_cast<vec2i>(screen_size - size_ref) / 2;
  window_style style_ref = window_style::fullscreen;
  image2_rgba icon_ref;
  uint samples_ref = 1u;

  render_window w(title_ref, size_ref, style_ref, samples_ref);

  EXPECT_NE(0u, w.get_uid());
  EXPECT_NE(nullptr, w.get_handle());
  EXPECT_EQ(style_ref, w.get_style());
  EXPECT_EQ(pos_ref, w.get_client_position());
  EXPECT_EQ(size_ref, w.get_client_size());
  EXPECT_EQ(
    graphic_context::get_rendering_color_byte_count(), w.get_bytes_per_pixel());
  EXPECT_EQ(title_ref, w.get_title());
  EXPECT_EQ(icon_ref, w.get_icon());
  EXPECT_FALSE(w.is_visible());
  EXPECT_FALSE(w.is_mouse_cursor_grabbed());
  EXPECT_FALSE(w.is_key_repeat_enabled());

  EXPECT_EQ(recti(vec2i::zero(), size_ref), w.get_default_viewport());
  EXPECT_EQ(recti(vec2i::zero(), size_ref), w.get_viewport());
  EXPECT_EQ(size_ref, w.get_size());
  EXPECT_EQ(samples_ref, w.get_sample_count());
  EXPECT_FALSE(w.is_multisampled());
  EXPECT_EQ(texture2(size_ref).get_image<pixel_format::rgba>(),
    w.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_window, set_client_rect)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2i pos_ref(2, 3);
  vec2u size_ref(14u, 17u);
  w.set_client_rect(pos_ref, size_ref);

  EXPECT_EQ(pos_ref, w.get_client_position());
  EXPECT_EQ(size_ref, w.get_client_size());
  EXPECT_EQ(size_ref, w.get_size());
}



TEST_F(test_render_window, set_client_rect_null_size_x)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u size_ref(0u, 17u);
  w.set_client_rect(vec2i::zero(), size_ref);
  EXPECT_EQ(size_ref, w.get_client_size());

  size_ref.x() = 1u;
  EXPECT_EQ(size_ref, w.get_size());
}



TEST_F(test_render_window, set_client_rect_null_size_y)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u size_ref(13u, 0u);
  w.set_client_rect(vec2i::zero(), size_ref);
  EXPECT_EQ(size_ref, w.get_client_size());

  size_ref.y() = 1u;
  EXPECT_EQ(size_ref, w.get_size());
}



TEST_F(test_render_window, set_client_rect_null_size)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u size_ref = vec2u::zero();
  w.set_client_rect(vec2i::zero(), size_ref);
  EXPECT_EQ(size_ref, w.get_client_size());

  size_ref.x() = 1u;
  size_ref.y() = 1u;
  EXPECT_EQ(size_ref, w.get_size());
}



TEST_F(test_render_window, set_client_size)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u size_ref(14u, 17u);
  w.set_client_size(size_ref);

  EXPECT_EQ(size_ref, w.get_client_size());
  EXPECT_EQ(size_ref, w.get_size());
}



TEST_F(test_render_window, set_client_size_null_size_x)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u size_ref(0u, 17u);
  w.set_client_size(size_ref);
  EXPECT_EQ(size_ref, w.get_client_size());

  size_ref.x() = 1u;
  EXPECT_EQ(size_ref, w.get_size());
}



TEST_F(test_render_window, set_client_size_null_size_y)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u size_ref(13u, 0u);
  w.set_client_size(size_ref);
  EXPECT_EQ(size_ref, w.get_client_size());

  size_ref.y() = 1u;
  EXPECT_EQ(size_ref, w.get_size());
}



TEST_F(test_render_window, set_client_size_null_size)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u size_ref = vec2u::zero();
  w.set_client_size(size_ref);
  EXPECT_EQ(size_ref, w.get_client_size());

  size_ref.x() = 1u;
  size_ref.y() = 1u;
  EXPECT_EQ(size_ref, w.get_size());
}



TEST_F(test_render_window, set_frame_rect)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2i pos_ref(12, 13);
  vec2u size_ref(60u, 100u);
  w.set_frame_rect(pos_ref, size_ref);

  EXPECT_EQ(pos_ref, w.get_frame_position());
  EXPECT_EQ(size_ref, w.get_frame_size());
  EXPECT_EQ(w.get_client_size(), w.get_size());
}



TEST_F(test_render_window, set_frame_rect_null_size_x)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u size_ref(0u, 42u);
  w.set_frame_rect(vec2i::zero(), size_ref);
  EXPECT_EQ(size_ref, w.get_frame_size());

  vec2u texSize_ref = w.get_client_size();
  texSize_ref.x() = 1u;
  EXPECT_EQ(texSize_ref, w.get_size());
}



TEST_F(test_render_window, set_frame_rect_null_size_y)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u size_ref(42u, 0u);
  w.set_frame_rect(vec2i::zero(), size_ref);
  EXPECT_EQ(size_ref, w.get_frame_size());

  vec2u texSize_ref = w.get_client_size();
  texSize_ref.y() = 1u;
  EXPECT_EQ(texSize_ref, w.get_size());
}



TEST_F(test_render_window, set_frame_rect_null_size)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u size_ref = vec2u::zero();
  w.set_frame_rect(vec2i::zero(), size_ref);
  EXPECT_EQ(size_ref, w.get_frame_size());

  vec2u texSize_ref = w.get_client_size();
  texSize_ref.x() = 1u;
  texSize_ref.y() = 1u;
  EXPECT_EQ(texSize_ref, w.get_size());
}



TEST_F(test_render_window, set_frame_size)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  w.setFrameSize(vec2u(60u, 70u));

  EXPECT_EQ(w.get_client_size(), w.get_size());
}



TEST_F(test_render_window, set_frame_size_null_size_x)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u size_ref(0u, 42u);
  w.setFrameSize(size_ref);
  EXPECT_EQ(size_ref, w.get_frame_size());

  vec2u texSize_ref = w.get_client_size();
  texSize_ref.x() = 1u;
  EXPECT_EQ(texSize_ref, w.get_size());
}



TEST_F(test_render_window, set_frame_size_null_size_y)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u size_ref(42u, 0u);
  w.setFrameSize(size_ref);
  EXPECT_EQ(size_ref, w.get_frame_size());

  vec2u texSize_ref = w.get_client_size();
  texSize_ref.y() = 1u;
  EXPECT_EQ(texSize_ref, w.get_size());
}



TEST_F(test_render_window, set_frame_size_null_size)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u size_ref = vec2u::zero();
  w.setFrameSize(size_ref);
  EXPECT_EQ(size_ref, w.get_frame_size());

  vec2u texSize_ref = w.get_client_size();
  texSize_ref.x() = 1u;
  texSize_ref.y() = 1u;
  EXPECT_EQ(texSize_ref, w.get_size());
}



TEST_F(test_render_window, set_vertical_sync_mode)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);
  w.set_vertical_sync_mode(vertical_sync_mode::enabled);
  w.set_vertical_sync_mode(vertical_sync_mode::disabled);
  SUCCEED();
}



TEST_F(test_render_window, set_samples)
{
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 1u);

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
  render_window w(u8"Test", vec2u(32u, 16u), window_style::windowed, 1u);
  EXPECT_PRECOND_ERROR(
    w.set_sample_count(render_window::get_max_sample_count() + 1u));
}



TEST_F(test_render_window, resize_frame_buffer_on_pop_resized_event)
{
  vec2u oldSize(vec2u(32u, 16u));
  render_window w(u8"Test", oldSize, window_style::windowed, 4u);
  vec2u newSize(vec2u(12u, 8u));

  window_event ev = window_event::resized(newSize.x(), newSize.y());
  w.push_event(ev);
  EXPECT_EQ(oldSize, w.get_client_size());
  EXPECT_EQ(oldSize, w.get_size());

  EXPECT_EQ(ev, w.pop_event());
  EXPECT_EQ(newSize, w.get_client_size());
  EXPECT_EQ(newSize, w.get_size());
}
