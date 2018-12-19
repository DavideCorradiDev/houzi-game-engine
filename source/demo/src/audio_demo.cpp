// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "bounded.hpp"

#include "hou/al/al_module.hpp"
#include "hou/aud/aud_module.hpp"
#include "hou/cor/cor_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/sys/sys_module.hpp"

#include "hou/sys/event.hpp"
#include "hou/sys/window.hpp"

#include "hou/aud/audio_context.hpp"
#include "hou/aud/buffer_audio_source.hpp"
#include "hou/aud/ogg_file_in.hpp"
#include "hou/aud/manual_stream_audio_source.hpp"
#include "hou/aud/automatic_stream_audio_source.hpp"
#include "hou/aud/wav_file_in.hpp"

#include "hou/cor/std_chrono.hpp"

#include <iostream>



int main(int, char**)
{
  // Initialization.
  hou::cor_module::initialize();
  hou::mth_module::initialize();
  hou::sys_module::initialize();
  hou::al_module::initialize();
  hou::aud_module::initialize();

  // Audio context.
  hou::audio_context actx;
  hou::audio_context::set_current(actx);

  // Audio files' paths.
  const std::string data_dir = u8"source/demo/data/";
  const std::string wav_file = data_dir + u8"test.wav";
  const std::string ogg_file = data_dir + u8"test.ogg";

  // Event callbacks.
  bool loop = true;
  auto on_quit = [&loop](hou::event::timestamp) { loop = false; };
  hou::event::set_quit_callback(on_quit);

  // Audio buffers.
  auto wav_buffer
    = std::make_shared<hou::audio_buffer>(hou::wav_file_in(wav_file));
  auto ogg_buffer
    = std::make_shared<hou::audio_buffer>(hou::ogg_file_in(ogg_file));

  // Audio sources.
  hou::buffer_audio_source buffer_as(wav_buffer);
  buffer_as.set_max_gain(2.f);

  hou::manual_stream_audio_source manual_stream_as(
    std::make_unique<hou::wav_file_in>(wav_file));
  manual_stream_as.set_max_gain(buffer_as.get_max_gain());

  hou::automatic_stream_audio_source automatic_stream_as(
    std::make_unique<hou::wav_file_in>(wav_file));
  automatic_stream_as.set_max_gain(buffer_as.get_max_gain());

  hou::not_null<hou::audio_source*> current_as = &buffer_as;

  // Source properties.
  bounded<float> gain(1.f, 0.f, buffer_as.get_max_gain());
  bounded<float> pitch(1.f, 0.5f, 1.5f);
  std::chrono::milliseconds skip(500);

  auto on_key_pressed
    = [&](hou::event::timestamp, hou::window::uid_type, hou::scan_code sc,
        hou::key_code, hou::modifier_keys, bool is_repeat) {
        if(is_repeat)
        {
          return;
        }
        if(sc == hou::scan_code::num1)
        {
          buffer_as.set_buffer(wav_buffer);
          manual_stream_as.set_stream(std::make_unique<hou::wav_file_in>(wav_file));
          automatic_stream_as.set_stream(std::make_unique<hou::wav_file_in>(wav_file));
          // change to wav.
        }
        else if(sc == hou::scan_code::num2)
        {
          buffer_as.set_buffer(ogg_buffer);
          manual_stream_as.set_stream(std::make_unique<hou::ogg_file_in>(ogg_file));
          automatic_stream_as.set_stream(std::make_unique<hou::ogg_file_in>(ogg_file));
          // change to ogg.
        }
        else if(sc == hou::scan_code::q)
        {
          current_as->stop();
          current_as = &buffer_as;
        }
        else if(sc == hou::scan_code::w)
        {
          current_as->stop();
          current_as = &manual_stream_as;
        }
        else if(sc == hou::scan_code::e)
        {
          current_as->stop();
          current_as = &automatic_stream_as;
        }
        else if(sc == hou::scan_code::u)
        {
          current_as->play();
        }
        else if(sc == hou::scan_code::i)
        {
          current_as->replay();
        }
        else if(sc == hou::scan_code::o)
        {
          current_as->pause();
        }
        else if(sc == hou::scan_code::p)
        {
          current_as->stop();
        }
        else if(sc == hou::scan_code::l)
        {
          buffer_as.set_looping(!buffer_as.is_looping());
          manual_stream_as.set_looping(buffer_as.is_looping());
          automatic_stream_as.set_looping(buffer_as.is_looping());
        }
        else if(sc == hou::scan_code::a)
        {
          gain -= 0.25f;
          buffer_as.set_gain(gain.get());
          manual_stream_as.set_gain(buffer_as.get_gain());
          automatic_stream_as.set_gain(buffer_as.get_gain());
        }
        else if(sc == hou::scan_code::s)
        {
          gain += 0.25f;
          buffer_as.set_gain(gain.get());
          manual_stream_as.set_gain(buffer_as.get_gain());
          automatic_stream_as.set_gain(buffer_as.get_gain());
        }
        else if(sc == hou::scan_code::d)
        {
          pitch -= 0.1f;
          buffer_as.set_pitch(pitch.get());
          manual_stream_as.set_pitch(buffer_as.get_pitch());
          automatic_stream_as.set_pitch(buffer_as.get_pitch());
        }
        else if(sc == hou::scan_code::f)
        {
          pitch += 0.1f;
          buffer_as.set_pitch(pitch.get());
          manual_stream_as.set_pitch(buffer_as.get_pitch());
          automatic_stream_as.set_pitch(buffer_as.get_pitch());
        }
        else if(sc == hou::scan_code::z)
        {
          current_as->set_time_pos(current_as->get_time_pos() - skip);
        }
        else if(sc == hou::scan_code::x)
        {
          current_as->set_time_pos(current_as->get_time_pos() + skip);
        }
      };
  hou::event::set_key_pressed_callback(on_key_pressed);

  // Print information.
  std::cout << "Controls:" << std::endl;
  std::cout << "    1: play wav file" << std::endl;
  std::cout << "    2: play ogg file" << std::endl;
  std::cout << "    Q: play from memory" << std::endl;
  std::cout << "    W: play from file stream" << std::endl;
  std::cout << "    E: play from file stream with multi-threading" << std::endl;
  std::cout << "    U: play" << std::endl;
  std::cout << "    I: replay" << std::endl;
  std::cout << "    O: pause" << std::endl;
  std::cout << "    P: stop" << std::endl;
  std::cout << "    L: toggle looping" << std::endl;
  std::cout << "    A: reduce gain" << std::endl;
  std::cout << "    S: increase gain" << std::endl;
  std::cout << "    D: reduce pitch" << std::endl;
  std::cout << "    F: increase pitch" << std::endl;
  std::cout << "    Z: skip half second backward" << std::endl;
  std::cout << "    X: skip half second forward" << std::endl;

  // Window.
  hou::window wnd("AudioDemo", hou::vec2u(640u, 480u));
  wnd.set_bordered(true);
  wnd.set_visible(true);
  wnd.raise();
  wnd.focus();

  // Main loop.
  while(loop)
  {
    hou::event::process_all();
    manual_stream_as.update();
  }

  return EXIT_SUCCESS;
}
