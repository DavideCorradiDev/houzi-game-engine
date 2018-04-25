#include "hou/mth/Transform2.hpp"
#include "hou/gfx/Font.hpp"
#include "hou/gfx/Vertex2.hpp"
#include "hou/gfx/GraphicContext.hpp"
#include "hou/gfx/FormattedText.hpp"
#include "hou/gfx/RenderWindow.hpp"
#include "hou/gfx/Mesh2ShaderProgram.hpp"
#include "hou/gfx/TextShaderProgram.hpp"
#include "hou/gfx/Mesh.hpp"
#include "hou/sys/Color.hpp"
#include "hou/cor/Stopwatch.hpp"
#include "hou/sys/WindowEvent.hpp"
#include "hou/sys/BinaryFileIn.hpp"

using namespace hou;



int main()
{
  GraphicContext ctx;
  GraphicContext::setCurrent(ctx);
  RenderWindow rw(u8"Text Rendering Demo", Vec2u(800u, 600u)
    , WindowStyle::WindowedResizable, 8u);
  rw.setVisible(true);
  Trans2f proj = Trans2f::orthographicProjection(rw.getViewport());
  Mesh2ShaderProgram m2Rnd;
  TextShaderProgram textRnd;
  Mesh2 fpsRect = createRectangleMesh2(Vec2f(128.f, 32.f));
  std::vector<uint> fontSizes{0, 2, 4, 8, 16, 32, 64};
  size_t currentSizeIdx = 3;
  Font font(std::make_unique<BinaryFileIn>("demo/data/NotoSans-Regular.ttf"));
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
    "elit. Duis venenatis mi neque, id ullamcorper tellus\n";
  std::string text;
  std::string chineseTextLine = u8"\u5154\u5B50\u6CA1\u6709\u6C57\u817A\uFF0C\u6240\u4EE5\u4E0D\u4F1A\u6D41\u6C57\uFF0C\u8033\u6735\u53EF\u4EE5\u6563\u70ED\u3002\n";
  std::string chineseText;
  font.setPixelHeight(fontSizes[currentSizeIdx]);
  chineseFont.setPixelHeight(fontSizes[currentSizeIdx]);
  uint linesNum = 38;
  for(uint i = 0u; i < linesNum; ++i)
  {
    text.append(textLine);
    chineseText.append(chineseTextLine);
  }
  Trans2f textTrans = Trans2f::translation(Vec2f(128.f, 200.f));


  std::cout << "Drawing " << textLine.size() * linesNum << " characters." << std::endl;
  TextFlow textFlow = TextFlow::LeftRight;
  TextAnchoring textAnchoring = TextAnchoring::TopLeft;
  Vec2f maxTBoxSize;
  const float maxTBoxIncrement = 32.f;

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
          if(we.getKeyData().scanCode == ScanCode::Down
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
          }
          else if(we.getKeyData().scanCode == ScanCode::A)
          {
            textFlow = TextFlow::RightLeft;
          }
          else if(we.getKeyData().scanCode == ScanCode::D)
          {
            textFlow = TextFlow::LeftRight;
          }
          else if(we.getKeyData().scanCode == ScanCode::W)
          {
            textFlow = TextFlow::BottomTop;
          }
          else if(we.getKeyData().scanCode == ScanCode::S)
          {
            textFlow = TextFlow::TopBottom;
          }
          else if(we.getKeyData().scanCode == ScanCode::T)
          {
            textAnchoring = TextAnchoring::TopLeft;
          }
          else if(we.getKeyData().scanCode == ScanCode::Y)
          {
            textAnchoring = TextAnchoring::TopCenter;
          }
          else if(we.getKeyData().scanCode == ScanCode::U)
          {
            textAnchoring = TextAnchoring::TopRight;
          }
          else if(we.getKeyData().scanCode == ScanCode::G)
          {
            textAnchoring = TextAnchoring::CenterLeft;
          }
          else if(we.getKeyData().scanCode == ScanCode::H)
          {
            textAnchoring = TextAnchoring::Center;
          }
          else if(we.getKeyData().scanCode == ScanCode::J)
          {
            textAnchoring = TextAnchoring::CenterRight;
          }
          else if(we.getKeyData().scanCode == ScanCode::B)
          {
            textAnchoring = TextAnchoring::BottomLeft;
          }
          else if(we.getKeyData().scanCode == ScanCode::N)
          {
            textAnchoring = TextAnchoring::BottomCenter;
          }
          else if(we.getKeyData().scanCode == ScanCode::M)
          {
            textAnchoring = TextAnchoring::BottomRight;
          }
          else if(we.getKeyData().scanCode == ScanCode::I)
          {
            textAnchoring = TextAnchoring::Baseline;
          }
          else if(we.getKeyData().scanCode == ScanCode::K)
          {
            maxTBoxSize.x() = std::max(0.f, maxTBoxSize.x() - maxTBoxIncrement);
          }
          else if(we.getKeyData().scanCode == ScanCode::Semicolon)
          {
            maxTBoxSize.x() = std::min(640.f, maxTBoxSize.x() + maxTBoxIncrement);
          }
          else if(we.getKeyData().scanCode == ScanCode::O)
          {
            maxTBoxSize.y() = std::max(0.f, maxTBoxSize.y() - maxTBoxIncrement);
          }
          else if(we.getKeyData().scanCode == ScanCode::L)
          {
            maxTBoxSize.y() = std::min(640.f, maxTBoxSize.y() + maxTBoxIncrement);
          }
        }
        break;
        case hou::WindowEventType::Resized:
          rw.setViewport(rw.getDefaultViewport());
          proj = Trans2f::orthographicProjection(rw.getViewport());
          std::cout << "Window resized: (" << we.getSizeData().sizeX << ", "
                    << we.getSizeData().sizeY << ")" << std::endl;
          std::cout << "Window client size: " << transpose(rw.getClientSize())
                    << std::endl;
          std::cout << "Window framebuffer size: " << transpose(rw.getSize())
                    << std::endl;
          break;
        case hou::WindowEventType::FocusGained:
        case hou::WindowEventType::FocusLost:
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

    if(maxTBoxSize.x() == 0.f || maxTBoxSize.y() == 0.f)
    {
      Mesh2 dot = createEllipseMesh2(Vec2f(16.f, 16.f), 32u);
      m2Rnd.draw(rw, dot, Color::Red, proj * textTrans * Trans2f::translation(Vec2f(-8.f, -8.f)));
    }
    else
    {
      Mesh2 bbox = createRectangleOutlineMesh2(maxTBoxSize, 1u);
      m2Rnd.draw(rw, bbox, Color::Red, proj * textTrans);
    }

    const std::string& textToRender = printChinese ? chineseText : text;
    Font& fontToRender = printChinese ? chineseFont : font;
    TextBoxFormattingParams tbfp(textFlow, textAnchoring, maxTBoxSize);
    FormattedText ft(textToRender, fontToRender, tbfp);
    Mesh2 textBox
      = createRectangleOutlineMesh2(ft.getBoundingBox().getSize(), 1u);
    m2Rnd.draw(rw, textBox, Color::White,
      proj * textTrans
        * Trans2f::translation(ft.getBoundingBox().getPosition()));
    textRnd.draw(rw, ft, Color::White, proj * textTrans);

    std::chrono::nanoseconds timePerFrame = timer.reset();
    // m2Rnd.draw(rw, fpsRect, Color::Black, proj);
    // FormattedText fpsText(
    //   toString(1.f
    //     / std::chrono::duration_cast<std::chrono::duration<float>>(timePerFrame)
    //         .count()),
    //   font);
    // textRnd.draw(rw, fpsText, Color::White, proj * textTrans);
    rw.display();
  }

  return 0;
}
