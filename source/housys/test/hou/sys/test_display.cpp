// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/display.hpp"
#include "hou/sys/sys_exceptions.hpp"

using namespace hou;
using namespace testing;



// namespace
// {
// 
// class test_display : public Test
// {
// public:
//   test_display();
//   ~test_display();
// };
// 
// using test_display_death_test = test_display;
// 
// 
// 
// test_display::test_display()
// {
//   display::set_connected_callback(nullptr);
//   display::set_disconnected_callback(nullptr);
// }
// 
// 
// 
// test_display::~test_display()
// {
//   display::set_connected_callback(nullptr);
//   display::set_disconnected_callback(nullptr);
// }
// 
// }  // namespace
// 
// 
// 
// TEST_F(test_display, get_count)
// {
//   EXPECT_LT(0u, display::get_count());
// }
// 
// 
// 
// TEST_F(test_display, get_name)
// {
//   for(uint i = 0; i < display::get_count(); ++i)
//   {
//     EXPECT_NE("", display::get_name(i));
//   }
// }
// 
// 
// 
// TEST_F(test_display, get_physical_size)
// {
//   for(uint i = 0; i < display::get_count(); ++i)
//   {
//     EXPECT_NE(vec2u::zero(), display::get_physical_size(i));
//   }
// }
// 
// 
// 
// TEST_F(test_display, get_physical_size_error_invalid_id)
// {
//   EXPECT_ERROR_N(display::get_physical_size(display::get_count()),
//     invalid_display_id, display::get_count());
// }
// 
// 
// 
// TEST_F(test_display_death_test, get_name_error_invalid_id)
// {
//   EXPECT_ERROR_N(display::get_name(display::get_count()), invalid_display_id,
//     display::get_count());
// }
// 
// 
// 
// TEST_F(test_display, get_position)
// {
//   for(uint i = 0; i < display::get_count(); ++i)
//   {
//     display::get_position(i);
//     SUCCEED();
//   }
// }
// 
// 
// 
// TEST_F(test_display_death_test, get_position_error_invalid_id)
// {
//   EXPECT_ERROR_N(display::get_position(display::get_count()),
//     invalid_display_id, display::get_count());
// }
// 
// 
// 
// TEST_F(test_display, get_size)
// {
//   for(uint i = 0; i < display::get_count(); ++i)
//   {
//     EXPECT_NE(vec2u::zero(), display::get_size(i));
//   }
// }
// 
// 
// 
// TEST_F(test_display, get_size_error_invalid_id)
// {
//   EXPECT_ERROR_N(display::get_size(display::get_count()), invalid_display_id,
//     display::get_count());
// }
// 
// 
// 
// TEST_F(test_display, get_depth_bit_count)
// {
//   for(uint i = 0; i < display::get_count(); ++i)
//   {
//     EXPECT_NE(0u, display::get_depth_bit_count(i));
//   }
// }
// 
// 
// 
// TEST_F(test_display, get_depth_bit_count_error_invalid_id)
// {
//   EXPECT_ERROR_N(display::get_depth_bit_count(display::get_count()),
//     invalid_display_id, display::get_count());
// }
// 
// 
// 
// TEST_F(test_display, get_refresh_rate)
// {
//   for(uint i = 0; i < display::get_count(); ++i)
//   {
//     EXPECT_NE(0u, display::get_refresh_rate(i));
//   }
// }
// 
// 
// 
// TEST_F(test_display, get_refresh_rate_error_invalid_id)
// {
//   EXPECT_ERROR_N(display::get_refresh_rate(display::get_count()),
//     invalid_display_id, display::get_count());
// }
// 
// 
// 
// TEST_F(test_display, get_video_mode)
// {
//   for(uint i = 0; i < display::get_count(); ++i)
//   {
//     video_mode vm = display::get_video_mode(i);
//     EXPECT_NE(vec2u::zero(), vm.get_size());
//     EXPECT_NE(0u, vm.get_depth_bit_count());
//     EXPECT_NE(0u, vm.get_refresh_rate());
//   }
// }
// 
// 
// 
// TEST_F(test_display, get_video_mode_error_invalid_id)
// {
//   EXPECT_ERROR_N(display::get_video_mode(display::get_count()),
//     invalid_display_id, display::get_count());
// }
// 
// 
// 
// TEST_F(test_display, get_supported_video_modes)
// {
//   for(uint i = 0; i < display::get_count(); ++i)
//   {
//     std::set<video_mode> modes = display::get_supported_video_modes(i);
//     for(const auto& vm : modes)
//     {
//       EXPECT_NE(vec2u::zero(), vm.get_size());
//       EXPECT_NE(0u, vm.get_depth_bit_count());
//       EXPECT_NE(0u, vm.get_refresh_rate());
//     }
//   }
// }
// 
// 
// 
// TEST_F(test_display, get_supported_video_modes_error_invalid_id)
// {
//   EXPECT_ERROR_N(display::get_supported_video_modes(display::get_count()),
//     invalid_display_id, display::get_count());
// }
// 
// 
// 
// TEST_F(test_display, set_connected_callback_return_value)
// {
//   int checker = 0;
//   auto f1 = [&](uint i) { checker = i; };
//   auto f2 = [&](uint i) { checker = i * 2; };
// 
//   EXPECT_EQ(nullptr, display::set_connected_callback(f1));
//   EXPECT_EQ(0, checker);
//   display::set_connected_callback(f2)(1u);
//   EXPECT_EQ(1, checker);
//   display::set_connected_callback(f1)(1u);
//   EXPECT_EQ(2, checker);
//   display::set_connected_callback(nullptr)(1u);
//   EXPECT_EQ(1, checker);
// }
// 
// 
// 
// TEST_F(test_display, set_disconnected_callback_return_value)
// {
//   int checker = 0;
//   auto f1 = [&]() { checker = 1; };
//   auto f2 = [&]() { checker = 2; };
// 
//   EXPECT_EQ(nullptr, display::set_disconnected_callback(f1));
//   EXPECT_EQ(0, checker);
//   display::set_disconnected_callback(f2)();
//   EXPECT_EQ(1, checker);
//   display::set_disconnected_callback(f1)();
//   EXPECT_EQ(2, checker);
//   display::set_disconnected_callback(nullptr)();
//   EXPECT_EQ(1, checker);
// }
// 
// 
// 
// TEST_F(test_display, display_callback)
// {
//   int checker1 = -1;
//   auto f1 = [&](uint i) { checker1 = i; };
// 
//   int checker2 = -1;
//   auto f2 = [&]() { ++checker2; };
// 
//   EXPECT_EQ(nullptr, display::set_connected_callback(f1));
//   EXPECT_EQ(nullptr, display::set_disconnected_callback(f2));
// 
//   GLFWdisplayfun cb = glfwSetdisplayCallback(nullptr);
// 
//   int displays_n = 0;
//   GLFWdisplay** displays = glfwGetdisplays(&displays_n);
//   for(int i = 0; i < displays_n; ++i)
//   {
//     EXPECT_EQ(i - 1, checker1);
//     EXPECT_EQ(i - 1, checker2);
//     cb(displays[i], GLFW_CONNECTED);
//     EXPECT_EQ(i, checker1);
//     EXPECT_EQ(i - 1, checker2);
//     cb(displays[i], GLFW_DISCONNECTED);
//     EXPECT_EQ(i, checker1);
//     EXPECT_EQ(i, checker2);
//   }
// 
//   EXPECT_NO_ERROR(cb(nullptr, GLFW_CONNECTED));
//   EXPECT_NO_ERROR(cb(nullptr, GLFW_DISCONNECTED));
// }
// 
// 
// 
// TEST_F(test_display, display_connected_callback)
// {
//   int checker = -1;
//   auto f = [&](uint i) { checker = i; };
// 
//   EXPECT_EQ(nullptr, display::set_connected_callback(f));
// 
//   GLFWdisplayfun cb = glfwSetdisplayCallback(nullptr);
// 
//   int displays_n = 0;
//   GLFWdisplay** displays = glfwGetdisplays(&displays_n);
//   for(int i = 0; i < displays_n; ++i)
//   {
//     EXPECT_EQ(i-1, checker);
//     cb(displays[i], GLFW_DISCONNECTED);
//     EXPECT_EQ(i-1, checker);
//     cb(displays[i], GLFW_CONNECTED);
//     EXPECT_EQ(i, checker);
//   }
// 
//   EXPECT_NO_ERROR(cb(nullptr, GLFW_CONNECTED));
//   EXPECT_NO_ERROR(cb(nullptr, GLFW_DISCONNECTED));
// }
// 
// 
// 
// TEST_F(test_display, display_disconnected_callback)
// {
//   int checker = -1;
//   auto f = [&]() { ++checker; };
// 
//   EXPECT_EQ(nullptr, display::set_disconnected_callback(f));
// 
//   GLFWdisplayfun cb = glfwSetdisplayCallback(nullptr);
// 
//   int displays_n = 0;
//   GLFWdisplay** displays = glfwGetdisplays(&displays_n);
//   for(int i = 0; i < displays_n; ++i)
//   {
//     EXPECT_EQ(i-1, checker);
//     cb(displays[i], GLFW_CONNECTED);
//     EXPECT_EQ(i-1, checker);
//     cb(displays[i], GLFW_DISCONNECTED);
//     EXPECT_EQ(i, checker);
//   }
// 
//   EXPECT_NO_ERROR(cb(nullptr, GLFW_CONNECTED));
//   EXPECT_NO_ERROR(cb(nullptr, GLFW_DISCONNECTED));
// }
