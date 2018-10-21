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

  hou::memory_audio_source memory_as(
    std::make_shared<hou::audio_buffer>(hou::wav_file_in(wav_file)));
  memory_as.set_looping(true);
  hou::threaded_audio_source threaded_as(
    std::make_unique<hou::ogg_file_in>(ogg_file));
  threaded_as.set_looping(true);
  hou::streaming_audio_source streaming_as(
    std::make_unique<hou::ogg_file_in>(ogg_file));
  streaming_as.set_looping(true);

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
          memory_as.play();
        }
        else if(sc == hou::scan_code::f2)
        {
          memory_as.replay();
        }
        else if(sc == hou::scan_code::f3)
        {
          memory_as.pause();
        }
        else if(sc == hou::scan_code::f4)
        {
          memory_as.stop();
        }
        else if(sc == hou::scan_code::f5)
        {
          threaded_as.play();
        }
        else if(sc == hou::scan_code::f6)
        {
          threaded_as.replay();
        }
        else if(sc == hou::scan_code::f7)
        {
          threaded_as.pause();
        }
        else if(sc == hou::scan_code::f8)
        {
          threaded_as.stop();
        }
        else if(sc == hou::scan_code::f9)
        {
          streaming_as.play();
        }
        else if(sc == hou::scan_code::f10)
        {
          streaming_as.replay();
        }
        else if(sc == hou::scan_code::f11)
        {
          streaming_as.pause();
        }
        else if(sc == hou::scan_code::f12)
        {
          streaming_as.stop();
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

  print_audio_source_properties(std::cout, "Memory", memory_as);
  print_audio_source_properties(std::cout, "Threaded", threaded_as);
  print_audio_source_properties(std::cout, "Streaming", streaming_as);

  std::cout << "Controls:" << std::endl;
  std::cout << "    f1: play memory source" << std::endl;
  std::cout << "    f2: replay memory source" << std::endl;
  std::cout << "    f3: pause memory source" << std::endl;
  std::cout << "    f4: stop memory source" << std::endl;
  std::cout << "    f5: play threaded source" << std::endl;
  std::cout << "    f6: replay threaded source" << std::endl;
  std::cout << "    f7: pause threaded source" << std::endl;
  std::cout << "    f8: stop threaded source" << std::endl;
  std::cout << "    f9: play streaming source" << std::endl;
  std::cout << "    f10: replay streaming source" << std::endl;
  std::cout << "    f11: pause streaming source" << std::endl;
  std::cout << "    f12: stop streaming source" << std::endl;
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
    streaming_as.update();
  }

  return EXIT_SUCCESS;
}
