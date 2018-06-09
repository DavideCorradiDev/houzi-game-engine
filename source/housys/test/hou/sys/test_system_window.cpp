// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/display.hpp"
#include "hou/sys/display_mode.hpp"
#include "hou/sys/system_window.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_system_window : public Test
{};

class test_system_window_death_test : public test_system_window
{};

}  // namespace



TEST_F(test_system_window, creation)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_NE(nullptr, w.get_impl());
  EXPECT_NE(0u, w.get_uid());
  EXPECT_LT(w.get_display_index(), display::get_count());
  display::mode curr_mode = display::get_current_mode(w.get_display_index());
  display::mode w_mode
    = display::get_closest_supported_mode(w.get_display_index(),
      display::mode(w.get_size(), curr_mode.get_format(),
        curr_mode.get_refresh_rate()));
  EXPECT_EQ(w_mode, w.get_display_mode());
  EXPECT_EQ(u8"TestWindow", w.get_title());
  EXPECT_EQ(vec2u(32u, 64u), w.get_size());
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
}



TEST_F(test_system_window, move_constructor)
{
  system_window w_dummy(u8"TestWindow", vec2u(32u, 64u));
  window_impl impl = w_dummy.get_impl();
  uint32_t uid = w_dummy.get_uid();
  system_window w(std::move(w_dummy));
  EXPECT_EQ(impl, w.get_impl());
  EXPECT_EQ(uid, w.get_uid());
  EXPECT_EQ(nullptr, w_dummy.get_impl());
  EXPECT_EQ(0u, w_dummy.get_uid());
}



TEST_F(test_system_window, title)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_EQ(u8"TestWindow", w.get_title());
  w.set_title(u8"NewTitle");
  EXPECT_EQ(u8"NewTitle", w.get_title());
}



TEST_F(test_system_window, size)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_EQ(vec2u(32u, 64u), w.get_size());
  w.set_size(vec2u(8u, 32u));
  EXPECT_EQ(vec2u(8u, 32u), w.get_size());
}



TEST_F(test_system_window, min_size)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_EQ(vec2u::zero(), w.get_min_size());
  w.set_min_size(vec2u(6u, 10u));
  EXPECT_EQ(vec2u(6u, 10u), w.get_min_size());
}



TEST_F(test_system_window, min_size_auto_resizing)
{
  system_window w(u8"TestWindow", vec2u(8u, 8u));

  w.set_min_size(vec2u(16u, 32u));
  EXPECT_EQ(vec2u(16u, 32u), w.get_min_size());
  EXPECT_EQ(vec2u(16u, 32u), w.get_size());

  w.set_min_size(vec2u(64u, 32u));
  EXPECT_EQ(vec2u(64u, 32u), w.get_min_size());
  EXPECT_EQ(vec2u(64u, 32u), w.get_size());

  w.set_min_size(vec2u(64u, 128u));
  EXPECT_EQ(vec2u(64u, 128u), w.get_min_size());
  EXPECT_EQ(vec2u(64u, 128u), w.get_size());
}



TEST_F(test_system_window, max_size)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  uint max_int = narrow_cast<uint>(std::numeric_limits<int>::max());
  EXPECT_EQ(vec2u(max_int, max_int), w.get_max_size());
  w.set_max_size(vec2u(6u, 10u));
  EXPECT_EQ(vec2u(6u, 10u), w.get_max_size());
}



TEST_F(test_system_window, max_size_auto_resizing)
{
  system_window w(u8"TestWindow", vec2u(8u, 8u));

  w.set_max_size(vec2u(6u, 7u));
  EXPECT_EQ(vec2u(6u, 7u), w.get_max_size());
  EXPECT_EQ(vec2u(6u, 7u), w.get_size());

  w.set_max_size(vec2u(5u, 7u));
  EXPECT_EQ(vec2u(5u, 7u), w.get_max_size());
  EXPECT_EQ(vec2u(5u, 7u), w.get_size());

  w.set_max_size(vec2u(5u, 4u));
  EXPECT_EQ(vec2u(5u, 4u), w.get_max_size());
  EXPECT_EQ(vec2u(5u, 4u), w.get_size());
}



TEST_F(test_system_window, position)
{
  system_window w(u8"TestWindow", vec2u(16u, 8u));

  recti bounds = display::get_usable_bounds(w.get_display_index());
  EXPECT_EQ(bounds.get_position() + (bounds.get_size() - vec2i(16, 8)) / 2,
    w.get_position());
  w.set_position(vec2i(8, 32));
  EXPECT_EQ(vec2i(8, 32), w.get_position());
}



TEST_F(test_system_window, visibility)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_FALSE(w.is_visible());
  w.hide();
  EXPECT_FALSE(w.is_visible());
  w.show();
  EXPECT_TRUE(w.is_visible());
  w.show();
  EXPECT_TRUE(w.is_visible());
  w.hide();
  EXPECT_FALSE(w.is_visible());
}



TEST_F(test_system_window, minimization_and_maximization)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_FALSE(w.is_minimized());
  EXPECT_FALSE(w.is_maximized());

  w.minimize();
  EXPECT_TRUE(w.is_minimized());
  EXPECT_FALSE(w.is_maximized());

  w.restore();
  EXPECT_FALSE(w.is_minimized());
  EXPECT_FALSE(w.is_maximized());

  w.maximize();
  EXPECT_FALSE(w.is_minimized());
  EXPECT_TRUE(w.is_maximized());

  w.restore();
  EXPECT_FALSE(w.is_minimized());
  EXPECT_FALSE(w.is_maximized());

  w.minimize();

  w.maximize();
  EXPECT_FALSE(w.is_minimized());
  EXPECT_TRUE(w.is_maximized());

  w.minimize();
  EXPECT_TRUE(w.is_minimized());
  EXPECT_FALSE(w.is_maximized());
}



TEST_F(test_system_window, test_grab)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_FALSE(w.get_grab());
  w.set_grab(false);
  EXPECT_FALSE(w.get_grab());
  w.set_grab(true);
  EXPECT_TRUE(w.get_grab());
  w.set_grab(true);
  EXPECT_TRUE(w.get_grab());
  w.set_grab(false);
  EXPECT_FALSE(w.get_grab());
}



TEST_F(test_system_window, test_raise)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));
  w.raise();
  SUCCEED();
}

// TEST_F(test_system_window, create_windowed)
// {
//   std::string title_ref("system_window");
//   vec2u size_ref(300u, 600u);
//   vec2u screen_size = video_mode::get_desktop_mode().get_resolution();
//   vec2i pos_ref = static_cast<vec2i>(screen_size - size_ref) / 2;
//   uint bbp_ref = 4u;
//   window_style style_ref = window_style::windowed;
//   image2_rgba icon_ref;
//
//   system_window w(title_ref, video_mode(size_ref, bbp_ref), style_ref);
//
//   EXPECT_NE(nullptr, w.get_handle());
//   EXPECT_NE(0u, w.get_uid());
//   EXPECT_EQ(title_ref, w.get_title());
//   EXPECT_EQ(pos_ref, w.get_client_position());
//   EXPECT_EQ(size_ref, w.get_client_size());
//   EXPECT_EQ(bbp_ref, w.get_bytes_per_pixel());
//   EXPECT_EQ(style_ref, w.get_style());
//   EXPECT_EQ(icon_ref, w.get_icon());
//   EXPECT_FALSE(w.is_visible());
//   EXPECT_FALSE(w.is_mouse_cursor_grabbed());
//   EXPECT_FALSE(w.is_key_repeat_enabled());
// }
//
//
//
// TEST_F(test_system_window, create_windowed_resizable)
// {
//   std::string title_ref("system_window");
//   vec2u size_ref(300u, 600u);
//   vec2u screen_size = video_mode::get_desktop_mode().get_resolution();
//   vec2i pos_ref = static_cast<vec2i>(screen_size - size_ref) / 2;
//   uint bbp_ref = 4u;
//   window_style style_ref = window_style::windowed_resizable;
//   image2_rgba icon_ref;
//
//   system_window w(title_ref, video_mode(size_ref, bbp_ref), style_ref);
//
//   EXPECT_NE(nullptr, w.get_handle());
//   EXPECT_NE(0u, w.get_uid());
//   EXPECT_EQ(title_ref, w.get_title());
//   EXPECT_EQ(pos_ref, w.get_client_position());
//   EXPECT_EQ(size_ref, w.get_client_size());
//   EXPECT_EQ(bbp_ref, w.get_bytes_per_pixel());
//   EXPECT_EQ(style_ref, w.get_style());
//   EXPECT_EQ(icon_ref, w.get_icon());
//   EXPECT_FALSE(w.is_visible());
//   EXPECT_FALSE(w.is_mouse_cursor_grabbed());
//   EXPECT_FALSE(w.is_key_repeat_enabled());
// }
//
//
//
// TEST_F(test_system_window, create_fullscreen)
// {
//   std::string title_ref("system_window");
//   vec2u size_ref(video_mode::get_desktop_mode().get_resolution());
//   vec2i pos_ref(0, 0);
//   uint bbp_ref(video_mode::get_desktop_mode().get_bytes_per_pixel());
//   window_style style_ref = window_style::fullscreen;
//   image2_rgba icon_ref;
//
//   system_window w(title_ref, video_mode(size_ref, bbp_ref), style_ref);
//
//   EXPECT_NE(nullptr, w.get_handle());
//   EXPECT_NE(0u, w.get_uid());
//   EXPECT_EQ(title_ref, w.get_title());
//   EXPECT_EQ(pos_ref, w.get_client_position());
//   EXPECT_EQ(pos_ref, w.get_frame_position());
//   EXPECT_EQ(size_ref, w.get_client_size());
//   EXPECT_EQ(size_ref, w.get_frame_size());
//   EXPECT_EQ(bbp_ref, w.get_bytes_per_pixel());
//   EXPECT_EQ(style_ref, w.get_style());
//   EXPECT_EQ(icon_ref, w.get_icon());
//   EXPECT_FALSE(w.is_visible());
//   EXPECT_FALSE(w.is_mouse_cursor_grabbed());
//   EXPECT_FALSE(w.is_key_repeat_enabled());
// }
//
//
//
// TEST_F(
//   test_system_window_death_test, create_fullscreen_error_invalid_video_mode)
// {
//   EXPECT_PRECOND_ERROR(system_window w1(
//     "Win", video_mode(vec2u::zero(), 32), window_style::fullscreen));
// }
//
//
//
// TEST_F(test_system_window_death_test,
//   create_fullscreen_error_fullscreen_window_already_existing)
// {
//   system_window w2(
//     "Win", video_mode::get_desktop_mode(), window_style::fullscreen);
//   EXPECT_PRECOND_ERROR(system_window w3(
//     "Win", video_mode::get_desktop_mode(), window_style::fullscreen));
// }
//
//
//
// TEST_F(test_system_window, create_window_multithreaded_environment)
// {
//   // When creating windows some global system state is modified.
//   // This test checks if everything runs fine when multiple threads try to
//   // create a window.
//   auto thread_fun = []() {
//     system_window w(
//       "Win", video_mode(vec2u::zero(), 0), window_style::windowed);
//     std::this_thread::sleep_for(std::chrono::milliseconds(2));
//   };
//
//   system_window w(
//     "Win", video_mode::get_desktop_mode(), window_style::fullscreen);
//
//   std::thread t1(thread_fun);
//   std::thread t2(thread_fun);
//   std::thread t3(thread_fun);
//   std::thread t4(thread_fun);
//
//   t1.join();
//   t2.join();
//   t3.join();
//   t4.join();
//
//   SUCCEED();
// }
//
//
//
// TEST_F(test_system_window, move_constructor)
// {
//   std::string title_ref("system_window");
//   vec2u size_ref(300u, 600u);
//   vec2u screen_size = video_mode::get_desktop_mode().get_resolution();
//   vec2i pos_ref = static_cast<vec2i>(screen_size - size_ref) / 2;
//   uint bbp_ref = 4u;
//   window_style style_ref = window_style::windowed;
//   image2_rgba icon_ref;
//
//   system_window w_dummy(title_ref, video_mode(size_ref, bbp_ref), style_ref);
//   window_handle handle_ref = w_dummy.get_handle();
//
//   system_window w(std::move(w_dummy));
//
//   EXPECT_EQ(handle_ref, w.get_handle());
//   EXPECT_NE(0u, w.get_uid());
//   EXPECT_EQ(title_ref, w.get_title());
//   EXPECT_EQ(pos_ref, w.get_client_position());
//   EXPECT_EQ(size_ref, w.get_client_size());
//   EXPECT_EQ(bbp_ref, w.get_bytes_per_pixel());
//   EXPECT_EQ(style_ref, w.get_style());
//   EXPECT_EQ(icon_ref, w.get_icon());
//   EXPECT_FALSE(w.is_visible());
//   EXPECT_FALSE(w.is_mouse_cursor_grabbed());
//   EXPECT_FALSE(w.is_key_repeat_enabled());
// }
//
//
//
// TEST_F(test_system_window, uid_generation)
// {
//   system_window first_window(
//     "Win", video_mode(vec2u::zero(), 0), window_style::windowed);
//   uint32_t firstUid = first_window.get_uid() + 1u;
//
//   for(size_t i = 0; i < 5u; ++i)
//   {
//     system_window w(
//       "Win", video_mode(vec2u::zero(), 0), window_style::windowed);
//     EXPECT_EQ(firstUid + i, w.get_uid());
//   }
// }
//
//
//
// TEST_F(test_system_window, frame_rect)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   vec2i pos(10, 20);
//   vec2u size(30u, 40u);
//   w.set_frame_rect(pos, size);
//   EXPECT_EQ(pos, w.get_frame_position());
//   EXPECT_EQ(size, w.get_frame_size());
// }
//
//
//
// TEST_F(test_system_window, frame_position)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   vec2i refPos = vec2i(30, 40);
//   w.set_frame_position(refPos);
//   EXPECT_EQ(refPos, w.get_frame_position());
// }
//
//
//
// TEST_F(test_system_window, frame_size)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   vec2u refSize = vec2u(30u, 40u);
//   w.setFrameSize(refSize);
//   EXPECT_EQ(refSize, w.get_frame_size());
// }
//
//
//
// TEST_F(test_system_window, client_rect)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   vec2i pos(10, 20);
//   vec2u size(30u, 40u);
//   w.set_client_rect(pos, size);
//   EXPECT_EQ(pos, w.get_client_position());
//   EXPECT_EQ(size, w.get_client_size());
// }
//
//
//
// TEST_F(test_system_window, client_position)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   vec2i refPos = vec2i(30, 40);
//   w.set_client_position(refPos);
//   EXPECT_EQ(refPos, w.get_client_position());
// }
//
//
//
// TEST_F(test_system_window, client_size)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   vec2u refSize = vec2u(30u, 40u);
//   w.set_client_size(refSize);
//   EXPECT_EQ(refSize, w.get_client_size());
// }
//
//
//
// TEST_F(test_system_window, title)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   std::string refTitle(u8"NewTitle");
//   w.set_title(refTitle);
//   EXPECT_EQ(refTitle, w.get_title());
// }
//
//
//
// TEST_F(test_system_window, icon)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   EXPECT_EQ(image2_rgba(), w.get_icon());
//   image2_rgba refIcon(png_image_file::read<format::rgba>(
//     get_data_dir() + u8"TestImage.png"));
//   w.set_icon(refIcon);
//   EXPECT_EQ(refIcon, w.get_icon());
//   w.set_system_icon();
//   EXPECT_EQ(image2_rgba(), w.get_icon());
// }
//
//
//
// TEST_F(test_system_window, visibility)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   EXPECT_FALSE(w.is_visible());
//
//   w.set_visible(true);
//   EXPECT_TRUE(w.is_visible());
//
//   w.set_visible(false);
//   EXPECT_FALSE(w.is_visible());
// }
//
//
//
// TEST_F(test_system_window, cursor_grabbed)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   EXPECT_FALSE(w.is_mouse_cursor_grabbed());
//
//   w.set_mouse_cursor_grabbed(true);
//   EXPECT_TRUE(w.is_mouse_cursor_grabbed());
//
//   w.set_mouse_cursor_grabbed(false);
//   EXPECT_FALSE(w.is_mouse_cursor_grabbed());
// }
//
//
//
// TEST_F(test_system_window, key_repeat_enabled)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   EXPECT_FALSE(w.is_key_repeat_enabled());
//
//   w.set_key_repeat_enabled(true);
//   EXPECT_TRUE(w.is_key_repeat_enabled());
//
//   w.set_key_repeat_enabled(false);
//   EXPECT_FALSE(w.is_key_repeat_enabled());
// }
//
//
//
// TEST_F(test_system_window, focus)
// {
//   system_window w1(
//     "Win1", video_mode(vec2u(640u, 480u), 32u), window_style::windowed);
//   system_window w2(
//     "Win2", video_mode(vec2u(640u, 480u), 32u), window_style::windowed);
//   w1.set_visible(true);
//   w2.set_visible(true);
//
//   if(w1.request_focus())
//   {
//     EXPECT_TRUE(w1.has_focus());
//     EXPECT_FALSE(w2.has_focus());
//   }
//   else
//   {
//     // Failed to take focus. Just pass.
//     SUCCEED();
//   }
// }
//
//
//
// TEST_F(test_system_window, event_queue_push_and_pop)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   window_event e1(window_event::closed());
//   window_event e2(window_event::focus_gained());
//   window_event e3(window_event::focus_lost());
//
//   EXPECT_TRUE(w.is_event_queue_empty());
//
//   w.push_event(e1);
//   w.push_event(e2);
//   w.push_event(e3);
//
//   EXPECT_FALSE(w.is_event_queue_empty());
//
//   EXPECT_EQ(e1, w.pop_event());
//   EXPECT_EQ(e2, w.pop_event());
//   EXPECT_EQ(e3, w.pop_event());
//
//   EXPECT_TRUE(w.is_event_queue_empty());
//
//   EXPECT_EQ(window_event::empty(), w.pop_event());
// }
//
//
//
// TEST_F(test_system_window, event_queue_wait_event)
// {
//   window_event ev_ref = window_event::focus_gained();
//   system_window w("Win", video_mode(vec2u::zero(), 0),
//   window_style::windowed); auto thread_fun = [&ev_ref, &w]() {
//     // This thread will wait for an event, which will be generated by the
//     // main thread.
//     window_event ev = w.wait_event();
//     EXPECT_EQ(ev_ref, ev);
//   };
//   std::thread t1(thread_fun);
//
//   w.push_event(ev_ref);
//
//   t1.join();
//
//   SUCCEED();
// }
//
//
//
// TEST_F(test_system_window, generate_resize_event_on_set_frame_size)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   EXPECT_TRUE(w.is_event_queue_empty());
//
//   w.setFrameSize(vec2u(200u, 400u));
//   window_event ev_ref
//     = window_event::resized(w.get_client_size().x(),
//     w.get_client_size().y());
//   EXPECT_FALSE(w.is_event_queue_empty());
//   EXPECT_EQ(ev_ref, w.pop_event());
//   EXPECT_TRUE(w.is_event_queue_empty());
// }
//
//
//
// TEST_F(test_system_window,
//   do_not_generate_resize_event_on_set_frame_size_with_same_size)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   EXPECT_TRUE(w.is_event_queue_empty());
//
//   w.setFrameSize(w.get_frame_size());
//   EXPECT_TRUE(w.is_event_queue_empty());
// }
//
//
//
// TEST_F(test_system_window, generate_resize_event_on_set_frame_rect)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   EXPECT_TRUE(w.is_event_queue_empty());
//
//   w.set_frame_rect(vec2i(32, 64), vec2u(200u, 400u));
//   window_event ev_ref
//     = window_event::resized(w.get_client_size().x(),
//     w.get_client_size().y());
//   EXPECT_FALSE(w.is_event_queue_empty());
//   EXPECT_EQ(ev_ref, w.pop_event());
//   EXPECT_TRUE(w.is_event_queue_empty());
// }
//
//
//
// TEST_F(test_system_window,
//   do_not_generate_resize_event_on_set_frame_rect_with_same_size)
// {
//   system_window w(
//     "Win", video_mode(vec2u(200u, 400u), 32u), window_style::windowed);
//   EXPECT_TRUE(w.is_event_queue_empty());
//
//   w.set_frame_rect(vec2i(32, 64), w.get_frame_size());
//   EXPECT_TRUE(w.is_event_queue_empty());
// }
//
//
//
// TEST_F(test_system_window, do_not_generate_resize_event_on_set_frame_pos)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   EXPECT_TRUE(w.is_event_queue_empty());
//
//   w.set_frame_position(vec2i(32, 64));
//   EXPECT_TRUE(w.is_event_queue_empty());
// }
//
//
//
// TEST_F(test_system_window, generate_resize_event_on_set_client_size)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   EXPECT_TRUE(w.is_event_queue_empty());
//
//   w.set_client_size(vec2u(200u, 400u));
//   window_event ev_ref
//     = window_event::resized(w.get_client_size().x(),
//     w.get_client_size().y());
//   EXPECT_FALSE(w.is_event_queue_empty());
//   EXPECT_EQ(ev_ref, w.pop_event());
//   EXPECT_TRUE(w.is_event_queue_empty());
// }
//
//
//
// TEST_F(test_system_window,
//   do_not_generate_resize_event_on_set_client_size_with_same_size)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   EXPECT_TRUE(w.is_event_queue_empty());
//
//   w.set_client_size(w.get_client_size());
//   EXPECT_TRUE(w.is_event_queue_empty());
// }
//
//
//
// TEST_F(test_system_window, generate_resize_event_on_set_client_rect)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   EXPECT_TRUE(w.is_event_queue_empty());
//
//   w.set_client_rect(vec2i(32, 64), vec2u(200u, 400u));
//   window_event ev_ref
//     = window_event::resized(w.get_client_size().x(),
//     w.get_client_size().y());
//   EXPECT_FALSE(w.is_event_queue_empty());
//   EXPECT_EQ(ev_ref, w.pop_event());
//   EXPECT_TRUE(w.is_event_queue_empty());
// }
//
//
//
// TEST_F(test_system_window,
//   do_not_generate_resize_event_on_set_client_rect_with_same_size)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   EXPECT_TRUE(w.is_event_queue_empty());
//
//   w.set_client_rect(vec2i(32, 64), w.get_client_size());
//   EXPECT_TRUE(w.is_event_queue_empty());
// }
//
//
//
// TEST_F(test_system_window, do_not_generate_resize_event_on_set_client_pos)
// {
//   system_window w(
//     "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
//   EXPECT_TRUE(w.is_event_queue_empty());
//
//   w.set_client_position(vec2i(32, 64));
//   EXPECT_TRUE(w.is_event_queue_empty());
// }
//
//
//
// NOTES:
// - no test for mouse grabbing.
// - no test for key repeat.
// - no test for update_event_queue and translation of system messages to
//   window_event objects.
