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
#include "hou/aud/memory_audio_source.hpp"
#include "hou/aud/ogg_file_in.hpp"
#include "hou/aud/streaming_audio_source.hpp"
#include "hou/aud/threaded_audio_source.hpp"
#include "hou/aud/wav_file_in.hpp"

#include "hou/cor/std_chrono.hpp"

#include <iostream>



void print_audio_source_properties(std::ostream& os,
  const std::string& source_name, const hou::audio_source& as);

void print_audio_source_properties(
  std::ostream& os, const std::string& source_name, const hou::audio_source& as)
{
  using seconds = std::chrono::duration<float, std::ratio<1>>;
  os << source_name << " source properties:\n";
  os << "    Format: " << as.get_format() << "\n";
  os << "    Channel count: " << as.get_channel_count() << "\n";
  os << "    Bytes per sample: " << as.get_bytes_per_sample() << "\n";
  os << "    Sample rate: " << as.get_sample_rate() << "\n";
  os << "    Sample count: " << as.get_sample_count() << "\n";
  os << "    Duration: " << seconds(as.get_duration()) << "\n";
  os << std::endl;
}



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
  hou::memory_audio_source memory_as(wav_buffer);
  memory_as.set_max_gain(2.f);

  hou::streaming_audio_source streaming_as(
    std::make_unique<hou::wav_file_in>(wav_file));
  streaming_as.set_max_gain(memory_as.get_max_gain());

  hou::threaded_audio_source threaded_as(
    std::make_unique<hou::wav_file_in>(wav_file));
  threaded_as.set_max_gain(memory_as.get_max_gain());

  hou::not_null<hou::audio_source*> current_as = &memory_as;

  // Source properties.
  bounded<float> gain(1.f, 0.f, memory_as.get_max_gain());
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
          memory_as.set_buffer(wav_buffer);
          streaming_as.set_stream(std::make_unique<hou::wav_file_in>(wav_file));
          threaded_as.set_stream(std::make_unique<hou::wav_file_in>(wav_file));
          // change to wav.
        }
        else if(sc == hou::scan_code::num2)
        {
          memory_as.set_buffer(ogg_buffer);
          streaming_as.set_stream(std::make_unique<hou::ogg_file_in>(ogg_file));
          threaded_as.set_stream(std::make_unique<hou::ogg_file_in>(ogg_file));
          // change to ogg.
        }
        else if(sc == hou::scan_code::q)
        {
          current_as->stop();
          current_as = &memory_as;
        }
        else if(sc == hou::scan_code::w)
        {
          current_as->stop();
          current_as = &streaming_as;
        }
        else if(sc == hou::scan_code::e)
        {
          current_as->stop();
          current_as = &threaded_as;
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
          memory_as.set_looping(!memory_as.is_looping());
          streaming_as.set_looping(memory_as.is_looping());
          threaded_as.set_looping(memory_as.is_looping());
        }
        else if(sc == hou::scan_code::a)
        {
          gain -= 0.25f;
          memory_as.set_gain(gain.get());
          streaming_as.set_gain(memory_as.get_gain());
          threaded_as.set_gain(memory_as.get_gain());
        }
        else if(sc == hou::scan_code::s)
        {
          gain += 0.25f;
          memory_as.set_gain(gain.get());
          streaming_as.set_gain(memory_as.get_gain());
          threaded_as.set_gain(memory_as.get_gain());
        }
        else if(sc == hou::scan_code::d)
        {
          pitch -= 0.1f;
          memory_as.set_pitch(pitch.get());
          streaming_as.set_pitch(memory_as.get_pitch());
          threaded_as.set_pitch(memory_as.get_pitch());
        }
        else if(sc == hou::scan_code::f)
        {
          pitch += 0.1f;
          memory_as.set_pitch(pitch.get());
          streaming_as.set_pitch(memory_as.get_pitch());
          threaded_as.set_pitch(memory_as.get_pitch());
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
  std::cout << "    A: play from file stream with multi-threading" << std::endl;
  std::cout << "    U: play" << std::endl;
  std::cout << "    I: replay" << std::endl;
  std::cout << "    O: pause" << std::endl;
  std::cout << "    P: stop" << std::endl;
  std::cout << "    L: toggle looping" << std::endl;
  std::cout << "    A: reduce gain" << std::endl;
  std::cout << "    S: increase gain" << std::endl;
  std::cout << "    D: reduce pitch" << std::endl;
  std::cout << "    F: increase pitch" << std::endl;
  std::cout << "    Z: skip half second forward" << std::endl;
  std::cout << "    X: skip half second backward" << std::endl;

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
    streaming_as.update();
  }

  return EXIT_SUCCESS;
}
