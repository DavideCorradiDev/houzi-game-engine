#include "hou/mth/Transform2.hpp"
#include "hou/gfx/Font.hpp"
#include "hou/gfx/Mesh2.hpp"
#include "hou/gfx/RenderContext.hpp"
#include "hou/gfx/RenderWindow.hpp"
#include "hou/gfx/RenderFont.hpp"
#include "hou/gfx/Renderer2.hpp"
#include "hou/sys/Color.hpp"
#include "hou/cor/Stopwatch.hpp"
#include "hou/sys/WindowEvent.hpp"
#include "hou/sys/BinaryFileIn.hpp"

using namespace hou;



int main()
{
  RenderContext ctx;
  RenderWindow rw(u8"Text Rendering Demo", Vec2u(800u, 600u), 8u
    , WindowStyle::Windowed);
  rw.setVisible(true);
  Trans2f proj = Trans2f::orthographicProjection(rw.getViewport());
  Renderer2 rnd;
  Mesh2 fpsRect = createRectangleMesh2(Vec2f(128.f, 32.f));
  std::vector<uint> fontSizes{0, 2, 4, 8, 16, 32, 64};
  size_t currentSizeIdx = 3;
  Font font(std::make_unique<BinaryFileIn>("demo/data/NotoMono-Regular.ttf"));
  Font chineseFont(std::make_unique<BinaryFileIn>("demo/data/NotoSansCJKsc-Regular.otf"));
  std::vector<Utf32::CodeUnit> characters;
  for(Utf32::CodeUnit c = 0; c < 256; ++c)
  {
    if(c != 'a') characters.push_back(c);
  }

  std::vector<Utf32::CodeUnit> chineseCharacters;
  chineseCharacters.push_back(0x0020);
  chineseCharacters.push_back(0xff0c);
  for(Utf32::CodeUnit c = 0x2000; c < 0x206f; ++c)
  {
    chineseCharacters.push_back(c);
  }
  for(Utf32::CodeUnit c = 0x3000; c < 0x303f; ++c)
  {
    chineseCharacters.push_back(c);
  }
  for(Utf32::CodeUnit c = 0x4e00; c < 0x9fff; ++c)
  {
    chineseCharacters.push_back(c);
  }

  bool printChinese = false;
  std::string textLine = u8"Lorem ipsum dolor sit amet, consectetur adipiscing "
    " elit. Duis venenatis mi neque, id ullamcorper tellus\n";
  std::string text;
  std::string chineseTextLine = u8"\u5154\u5B50\u6CA1\u6709\u6C57\u817A\uFF0C\u6240\u4EE5\u4E0D\u4F1A\u6D41\u6C57\uFF0C\u8033\u6735\u53EF\u4EE5\u6563\u70ED\u3002\n";
  std::string chineseText;
  font.setPixelHeight(fontSizes[currentSizeIdx]);
  chineseFont.setPixelHeight(fontSizes[currentSizeIdx]);
  auto renderFont = std::make_unique<RenderFont>(characters, font);
  uint linesNum = 38;
  for(uint i = 0u; i < linesNum; ++i)
  {
    text.append(textLine);
    chineseText.append(chineseTextLine);
  }
  Trans2f textTrans = Trans2f::translation(Vec2f(0.f, static_cast<float>(font.getLineSpacing() / 64)));


  std::cout << "Drawing " << textLine.size() * linesNum << " characters." << std::endl;
  bool useRenderCache = false;

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
        {
          running = false;
          break;
        }
        case WindowEventType::KeyReleased:
        {
          if(we.getKeyData().scanCode == ScanCode::Enter)
          {
            useRenderCache = !useRenderCache;
          }
          else if(we.getKeyData().scanCode == ScanCode::Down
            || we.getKeyData().scanCode == ScanCode::Up
            || we.getKeyData().scanCode == ScanCode::RShift)
          {
            if(we.getKeyData().scanCode == ScanCode::Down)
            {
              if(currentSizeIdx > 0)
              {
                --currentSizeIdx;
              }
            }
            else if(we.getKeyData().scanCode == ScanCode::Up)
            {
              if(currentSizeIdx < fontSizes.size() - 1)
              {
                ++currentSizeIdx;
              }
            }
            else if(we.getKeyData().scanCode == ScanCode::RShift)
            {
              printChinese = !printChinese;
            }
            font.setPixelHeight(fontSizes[currentSizeIdx]);
            chineseFont.setPixelHeight(fontSizes[currentSizeIdx]);
            if(printChinese)
            {
              renderFont = std::make_unique<RenderFont>(chineseCharacters, chineseFont);
            }
            else
            {
              renderFont = std::make_unique<RenderFont>(characters, font);
            }
          }
        }
        case hou::WindowEventType::FocusGained:
        case hou::WindowEventType::FocusLost:
        case hou::WindowEventType::Resized:
        case hou::WindowEventType::KeyPressed:
        case hou::WindowEventType::TextEntered:
        case hou::WindowEventType::MouseMoved:
        case hou::WindowEventType::MouseEntered:
        case hou::WindowEventType::MouseLeft:
        case hou::WindowEventType::MouseButtonPressed:
        case hou::WindowEventType::MouseButtonReleased:
        case hou::WindowEventType::MouseWheelMoved:
        case hou::WindowEventType::Empty:
          break;
      }
    }

    rw.clear(Color::Black);
    std::chrono::nanoseconds timePerFrame = timer.reset();
    // std::cout << timePerFrame.count() << " ns  = " << std::chrono::duration_cast<std::chrono::duration<float>>(timePerFrame).count() << "s" << std::endl;
    const std::string& textToRender = printChinese ? chineseText : text;
    if(useRenderCache)
    {
      rnd.draw(rw, textToRender, *renderFont, Color::White, proj * textTrans);
    }
    else
    {
      Font& fontToRender = printChinese ? chineseFont : font;
      rnd.draw(rw, textToRender, fontToRender, Color::White, proj * textTrans);
    }
    rnd.draw(rw, fpsRect, Color::Black, proj);
    rnd.draw(rw, toString(1.f / std::chrono::duration_cast<std::chrono::duration<float>>(timePerFrame).count()), font, Color::White, proj * textTrans);
    rw.display();
  }

  return 0;
}

