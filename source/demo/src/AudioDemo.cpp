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

#include "hou/al/AlContext.hpp"
#include "hou/al/AlDevice.hpp"
#include "hou/al/AlListener.hpp"

#include "hou/aud/AudioContext.hpp"
#include "hou/aud/AudioBuffer.hpp"
#include "hou/aud/MemoryAudioSource.hpp"
#include "hou/aud/OggFileIn.hpp"
#include "hou/aud/StreamingAudioSource.hpp"
#include "hou/aud/WavFileIn.hpp"

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

  std::vector<std::string> deviceNames = AudioContext::getDeviceNames();
  std::cout << "Available devices:" << std::endl;
  for(const auto& deviceName : deviceNames) {
    std::cout << deviceName << std::endl;
  }

  AudioContext ac;
  AudioContext::set_current(ac);

  ALfloat listenerPos[] = {0.f, 0.f, 0.f};
  ALfloat listenerVel[] = {0.f, 0.f, 0.f};
  ALfloat listenerOri[] = {0.f, 0.f, 0.f, 0.f, 1.f, 0.f};
  al::setListenerPosition(listenerPos);
  al::setListenerVelocity(listenerVel);
  al::setListenerOrientation(listenerOri);

  // std::string filename = dataDir + u8"test.wav";
  std::string filename = "source/houaud/test/data/TestWav-Stereo-16-44100.wav";
  // std::string longFilename = dataDir + u8"longsound.wav";
  std::string longFilename = dataDir + u8"test.ogg";
  AudioBuffer buffer = AudioBuffer(WavFileIn(filename));
  MemoryAudioSource source(&buffer);
  StreamingAudioSource sas(std::make_unique<OggFileIn>(longFilename));
  sas.setLooping(false);

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
    rnd.draw(rw, to_string(sas.getSamplePos()) + " / " + to_string(sas.get_sample_count())
      , ph_font, color::white, proj * offsetTrans);
    rw.display();
  }

  std::cout << "Success!" << std::endl;
  return 0;
}
