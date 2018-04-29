#include <iostream>
#include <cassert>

#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/render_window.hpp"
#include "hou/gfx/font.hpp"
#include "hou/gfx/text_shader_program.hpp"
#include "hou/sys/color.hpp"
#include "hou/sys/window_event.hpp"
#include "hou/sys/binary_file_in.hpp"

#include "hou/sys/file.hpp"

#include "hou/cor/std_array.hpp"
#include "hou/cor/std_vector.hpp"
#include "hou/cor/stopwatch.hpp"
#include "hou/mth/transform2.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_device.hpp"
#include "hou/al/al_listener.hpp"

#include "hou/aud/audio_context.hpp"
#include "hou/aud/audio_buffer.hpp"
#include "hou/aud/memory_audio_source.hpp"
#include "hou/aud/ogg_file_in.hpp"
#include "hou/aud/streaming_audio_source.hpp"
#include "hou/aud/wav_file_in.hpp"

using namespace hou;




int main()
{
  static const std::string dataDir = u8"source/demo/data/";
  graphic_context ctx;
  graphic_context::set_current(ctx);
  render_window rw(u8"Sprite benchmark", vec2u(800u, 600u), window_style::windowed);
  rw.set_visible(true);
  rw.set_vertical_sync_mode(vertical_sync_mode::disabled);

  text_shader_program rnd;
  font ph_font(std::make_unique<binary_file_in>(dataDir + u8"NotoMono-Regular.ttf"));
  trans2f proj = trans2f::orthographic_projection(rw.get_viewport());
  trans2f textTrans = trans2f::translation(vec2f(0.f, static_cast<float>(ph_font.get_line_spacing())));
  trans2f offsetTrans = trans2f::translation(vec2f(100.f, static_cast<float>(ph_font.get_line_spacing())));

  //****************

  std::vector<std::string> deviceNames = audio_context::get_device_names();
  std::cout << "Available devices:" << std::endl;
  for(const auto& deviceName : deviceNames) {
    std::cout << deviceName << std::endl;
  }

  audio_context ac;
  audio_context::set_current(ac);

  ALfloat listenerPos[] = {0.f, 0.f, 0.f};
  ALfloat listenerVel[] = {0.f, 0.f, 0.f};
  ALfloat listenerOri[] = {0.f, 0.f, 0.f, 0.f, 1.f, 0.f};
  al::set_listener_position(listenerPos);
  al::set_listener_velocity(listenerVel);
  al::set_listener_orientation(listenerOri);

  // std::string filename = dataDir + u8"test.wav";
  std::string filename = "source/houaud/test/data/TestWav-Stereo-16-44100.wav";
  // std::string longFilename = dataDir + u8"longsound.wav";
  std::string longFilename = dataDir + u8"test.ogg";
  audio_buffer buffer = audio_buffer(wav_file_in(filename));
  memory_audio_source source(&buffer);
  streaming_audio_source sas(std::make_unique<ogg_file_in>(longFilename));
  sas.set_looping(false);

  bool running = true;
  stopwatch timer;
  timer.start();
  while(running)
  {
    rw.update_event_queue();
    while(!rw.is_event_queue_empty())
    {
      window_event we = rw.pop_event();
      switch(we.get_type())
      {
        case window_event_type::closed:
          running = false;
          break;
        case window_event_type::key_pressed:
          if(we.get_key_data().scan_code == scan_code::Enter)
          {
            sas.play();
          }
          else if(we.get_key_data().scan_code == scan_code::Backspace)
          {
            sas.stop();
          }
          else if(we.get_key_data().scan_code == scan_code::RShift)
          {
            sas.pause();
          }
          else
          {
            source.play();
          }
          break;
        default:
          break;
      }
    }
    rw.clear(color::black);
    std::chrono::nanoseconds timePerFrame = timer.reset();
    rnd.draw(rw, to_string(sas.get_sample_pos()) + " / " + to_string(sas.get_sample_count())
      , ph_font, color::white, proj * offsetTrans);
    rw.display();
  }

  std::cout << "Success!" << std::endl;
  return 0;
}
