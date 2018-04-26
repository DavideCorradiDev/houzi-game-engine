#include <iostream>
#include <cassert>

#include "hou/gfx/GraphicContext.hpp"
#include "hou/gfx/RenderWindow.hpp"
#include "hou/gfx/Font.hpp"
#include "hou/gfx/TextShaderProgram.hpp"
#include "hou/sys/Color.hpp"
#include "hou/sys/WindowEvent.hpp"
#include "hou/sys/BinaryFileIn.hpp"

#include "hou/sys/File.hpp"

#include "hou/cor/StdArray.hpp"
#include "hou/cor/StdVector.hpp"
#include "hou/cor/Stopwatch.hpp"
#include "hou/mth/Transform2.hpp"

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
  GraphicContext ctx;
  GraphicContext::setCurrent(ctx);
  RenderWindow rw(u8"Sprite benchmark", Vec2u(800u, 600u), WindowStyle::Windowed);
  rw.setVisible(true);
  rw.setVerticalSyncMode(VerticalSyncMode::Disabled);

  TextShaderProgram rnd;
  Font font(std::make_unique<BinaryFileIn>("demo/data/NotoMono-Regular.ttf"));
  Trans2f proj = Trans2f::orthographicProjection(rw.getViewport());
  Trans2f textTrans = Trans2f::translation(Vec2f(0.f, static_cast<float>(font.getLineSpacing())));
  Trans2f offsetTrans = Trans2f::translation(Vec2f(100.f, static_cast<float>(font.getLineSpacing())));

  //****************

  std::vector<std::string> deviceNames = AudioContext::getDeviceNames();
  std::cout << "Available devices:" << std::endl;
  for(const auto& deviceName : deviceNames) {
    std::cout << deviceName << std::endl;
  }

  AudioContext ac;
  AudioContext::setCurrent(ac);

  ALfloat listenerPos[] = {0.f, 0.f, 0.f};
  ALfloat listenerVel[] = {0.f, 0.f, 0.f};
  ALfloat listenerOri[] = {0.f, 0.f, 0.f, 0.f, 1.f, 0.f};
  al::setListenerPosition(listenerPos);
  al::setListenerVelocity(listenerVel);
  al::setListenerOrientation(listenerOri);

  // std::string filename = "demo/data/test.wav";
  std::string filename = "houaud/test/data/TestWav-Stereo-16-44100.wav";
  // std::string longFilename = "demo/data/longsound.wav";
  std::string longFilename = "demo/data/test.ogg";
  AudioBuffer buffer = AudioBuffer(WavFileIn(filename));
  MemoryAudioSource source(&buffer);
  StreamingAudioSource sas(std::make_unique<OggFileIn>(longFilename));
  sas.setLooping(false);

  bool running = true;
  Stopwatch timer;
  timer.start();
  while(running)
  {
    rw.updateEventQueue();
    while(!rw.isEventQueueEmpty())
    {
      WindowEvent we = rw.popEvent();
      switch(we.getType())
      {
        case WindowEventType::Closed:
          running = false;
          break;
        case WindowEventType::KeyPressed:
          if(we.getKeyData().scanCode == ScanCode::Enter)
          {
            sas.play();
          }
          else if(we.getKeyData().scanCode == ScanCode::Backspace)
          {
            sas.stop();
          }
          else if(we.getKeyData().scanCode == ScanCode::RShift)
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
    rw.clear(Color::Black);
    std::chrono::nanoseconds timePerFrame = timer.reset();
    rnd.draw(rw, toString(sas.getSamplePos()) + " / " + toString(sas.getSampleCount())
      , font, Color::White, proj * offsetTrans);
    rw.display();
  }

  std::cout << "Success!" << std::endl;
  return 0;
}
