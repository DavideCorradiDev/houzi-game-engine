// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

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
  // Setup.
  hou::cor_module::initialize();
  hou::mth_module::initialize();
  hou::sys_module::initialize();
  hou::al_module::initialize();
  hou::aud_module::initialize();

  hou::audio_context actx;
  hou::audio_context::set_current(actx);

  // Resources.
  const std::string data_dir = u8"source/demo/data/";
  const std::string wav_file = data_dir + u8"test.wav";
  const std::string ogg_file = data_dir + u8"test.ogg";

  hou::memory_audio_source wav_source(
    std::make_shared<hou::audio_buffer>(hou::wav_file_in(wav_file)));
  wav_source.set_looping(true);
  hou::threaded_audio_source ogg_source(
    std::make_unique<hou::ogg_file_in>(ogg_file));
  ogg_source.set_looping(true);

  // Event callbacks.
  bool loop = true;
  auto on_quit = [&loop](hou::event::timestamp) { loop = false; };
  hou::event::set_quit_callback(on_quit);

  auto on_key_pressed
    = [&](hou::event::timestamp, hou::window::uid_type, hou::scan_code sc,
        hou::key_code, hou::modifier_keys, bool is_repeat) {
        if(is_repeat)
        {
          return;
        }
        if(sc == hou::scan_code::f1)
        {
          wav_source.play();
        }
        else if(sc == hou::scan_code::f2)
        {
          wav_source.replay();
        }
        else if(sc == hou::scan_code::f3)
        {
          wav_source.pause();
        }
        else if(sc == hou::scan_code::f4)
        {
          wav_source.stop();
        }
        else if(sc == hou::scan_code::f5)
        {
          ogg_source.play();
        }
        else if(sc == hou::scan_code::f6)
        {
          ogg_source.replay();
        }
        else if(sc == hou::scan_code::f7)
        {
          ogg_source.pause();
        }
        else if(sc == hou::scan_code::f8)
        {
          ogg_source.stop();
        }
      };
  hou::event::set_key_pressed_callback(on_key_pressed);

  // Print information.
  std::cout << "Available audio devices:" << std::endl;
  for(const auto& dev_name : hou::audio_context::get_device_names())
  {
    std::cout << "    " << dev_name << std::endl;
  }
  std::cout << std::endl;

  print_audio_source_properties(std::cout, "Wav", wav_source);
  print_audio_source_properties(std::cout, "Ogg", ogg_source);

  std::cout << "Controls:" << std::endl;
  std::cout << "    f1: play wav source" << std::endl;
  std::cout << "    f2: replay wav source" << std::endl;
  std::cout << "    f3: pause wav source" << std::endl;
  std::cout << "    f4: stop wav source" << std::endl;
  std::cout << "    f5: play ogg source" << std::endl;
  std::cout << "    f6: replay ogg source" << std::endl;
  std::cout << "    f7: pause ogg source" << std::endl;
  std::cout << "    f8: stop ogg source" << std::endl;
  std::cout << std::endl;

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
  }

  return EXIT_SUCCESS;
}
