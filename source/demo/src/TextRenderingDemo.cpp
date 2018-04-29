#include "hou/cor/stopwatch.hpp"
#include "hou/gfx/Font.hpp"
#include "hou/gfx/FormattedText.hpp"
#include "hou/gfx/GraphicContext.hpp"
#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/Mesh2ShaderProgram.hpp"
#include "hou/gfx/RenderWindow.hpp"
#include "hou/gfx/TextShaderProgram.hpp"
#include "hou/gfx/Vertex2.hpp"
#include "hou/mth/transform2.hpp"
#include "hou/sys/binary_file_in.hpp"
#include "hou/sys/color.hpp"
#include "hou/sys/window_event.hpp"

using namespace hou;



int main()
{
  static const std::string dataDir = u8"source/demo/data/";
  GraphicContext ctx;
  GraphicContext::set_current(ctx);
  RenderWindow rw(u8"text Rendering Demo", vec2u(800u, 600u),
    window_style::windowed_resizable, 8u);
  rw.set_visible(true);
  trans2f proj = trans2f::orthographic_projection(rw.getViewport());
  Mesh2ShaderProgram m2Rnd;
  TextShaderProgram textRnd;
  Mesh2 fpsRect = createRectangleMesh2(vec2f(128.f, 32.f));
  std::vector<uint> fontSizes{0, 2, 4, 8, 16, 32, 64};
  size_t currentSizeIdx = 3;
  Font font(std::make_unique<binary_file_in>(dataDir + u8"NotoSans-Regular.ttf"));
  Font chineseFont(
    std::make_unique<binary_file_in>(dataDir + u8"NotoSansCJKsc-Regular.otf"));
  std::vector<utf32::code_unit> characters;
  for(utf32::code_unit c = 0; c < 256; ++c)
  {
    if(c != 'a')
      characters.push_back(c);
  }

  std::vector<utf32::code_unit> chineseCharacters;
  chineseCharacters.push_back(0x0020);
  chineseCharacters.push_back(0xff0c);
  for(utf32::code_unit c = 0x2000; c < 0x206f; ++c)
  {
    chineseCharacters.push_back(c);
  }
  for(utf32::code_unit c = 0x3000; c < 0x303f; ++c)
  {
    chineseCharacters.push_back(c);
  }
  for(utf32::code_unit c = 0x4e00; c < 0x9fff; ++c)
  {
    chineseCharacters.push_back(c);
  }

  bool printChinese = false;
  std::string textLine
    = u8"Lorem ipsum dolor sit amet, consectetur adipiscing "
      "elit. Duis venenatis mi neque, id ullamcorper tellus\n";
  std::string text;
  std::string chineseTextLine
    = u8"\u5154\u5B50\u6CA1\u6709\u6C57\u817A\uFF0C\u6240\u4EE5\u4E0D\u4F1A"
      u8"\u6D41\u6C57\uFF0C\u8033\u6735\u53EF\u4EE5\u6563\u70ED\u3002\n";
  std::string chineseText;
  font.setPixelHeight(fontSizes[currentSizeIdx]);
  chineseFont.setPixelHeight(fontSizes[currentSizeIdx]);
  uint linesNum = 38;
  for(uint i = 0u; i < linesNum; ++i)
  {
    text.append(textLine);
    chineseText.append(chineseTextLine);
  }
  trans2f textTrans = trans2f::translation(vec2f(128.f, 200.f));


  std::cout << "Drawing " << textLine.size() * linesNum << " characters."
            << std::endl;
  TextFlow textFlow = TextFlow::LeftRight;
  vec2f maxTBoxSize;
  const float maxTBoxIncrement = 32.f;

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
      {
        running = false;
        break;
      }
      case window_event_type::key_released:
      {
        if(we.get_key_data().scan_code == scan_code::Down
          || we.get_key_data().scan_code == scan_code::Up
          || we.get_key_data().scan_code == scan_code::RShift)
        {
          if(we.get_key_data().scan_code == scan_code::Down)
          {
            if(currentSizeIdx > 0)
            {
              --currentSizeIdx;
            }
          }
          else if(we.get_key_data().scan_code == scan_code::Up)
          {
            if(currentSizeIdx < fontSizes.size() - 1)
            {
              ++currentSizeIdx;
            }
          }
          else if(we.get_key_data().scan_code == scan_code::RShift)
          {
            printChinese = !printChinese;
          }
          font.setPixelHeight(fontSizes[currentSizeIdx]);
          chineseFont.setPixelHeight(fontSizes[currentSizeIdx]);
        }
        else if(we.get_key_data().scan_code == scan_code::A)
        {
          textFlow = TextFlow::RightLeft;
        }
        else if(we.get_key_data().scan_code == scan_code::D)
        {
          textFlow = TextFlow::LeftRight;
        }
        else if(we.get_key_data().scan_code == scan_code::W)
        {
          textFlow = TextFlow::BottomTop;
        }
        else if(we.get_key_data().scan_code == scan_code::S)
        {
          textFlow = TextFlow::TopBottom;
        }
        else if(we.get_key_data().scan_code == scan_code::K)
        {
          maxTBoxSize.x() = std::max(0.f, maxTBoxSize.x() - maxTBoxIncrement);
        }
        else if(we.get_key_data().scan_code == scan_code::Semicolon)
        {
          maxTBoxSize.x() = std::min(640.f, maxTBoxSize.x() + maxTBoxIncrement);
        }
        else if(we.get_key_data().scan_code == scan_code::O)
        {
          maxTBoxSize.y() = std::max(0.f, maxTBoxSize.y() - maxTBoxIncrement);
        }
        else if(we.get_key_data().scan_code == scan_code::L)
        {
          maxTBoxSize.y() = std::min(640.f, maxTBoxSize.y() + maxTBoxIncrement);
        }
      }
      break;
      case hou::window_event_type::resized:
        rw.set_viewport(rw.getDefaultViewport());
        proj = trans2f::orthographic_projection(rw.getViewport());
        std::cout << "window resized: (" << we.get_size_data().x << ", "
                  << we.get_size_data().y << ")" << std::endl;
        std::cout << "window client size: " << transpose(rw.get_client_size())
                  << std::endl;
        std::cout << "window framebuffer size: " << transpose(rw.get_size())
                  << std::endl;
        break;
      case hou::window_event_type::focus_gained:
      case hou::window_event_type::focus_lost:
      case hou::window_event_type::key_pressed:
      case hou::window_event_type::TextEntered:
      case hou::window_event_type::mouse_moved:
      case hou::window_event_type::mouse_entered:
      case hou::window_event_type::mouse_left:
      case hou::window_event_type::mouse_button_pressed:
      case hou::window_event_type::mouse_button_released:
      case hou::window_event_type::mouse_wheel_moved:
      case hou::window_event_type::empty:
        break;
      }
    }

    rw.clear(color::black);

    const std::string& textToRender = printChinese ? chineseText : text;
    Font& fontToRender = printChinese ? chineseFont : font;

    if(maxTBoxSize.x() == 0.f || maxTBoxSize.y() == 0.f)
    {
      Mesh2 dot = createEllipseMesh2(vec2f(16.f, 16.f), 32u);
      m2Rnd.draw(rw, dot, color::red,
        proj * textTrans * trans2f::translation(vec2f(-8.f, -8.f)));
    }
    else
    {
      vec2f bboxTrans;
      switch(textFlow)
      {
      case TextFlow::LeftRight:
        bboxTrans.y() = -fontToRender.getPixelLineSpacing();
        break;
      case TextFlow::RightLeft:
        bboxTrans.x() = -maxTBoxSize.x();
        bboxTrans.y() = -fontToRender.getPixelLineSpacing();
        break;
      case TextFlow::TopBottom:
        bboxTrans.x() = -0.5f * fontToRender.getMaxPixelAdvance();
        break;
      case TextFlow::BottomTop:
        bboxTrans.x() = -0.5f * fontToRender.getMaxPixelAdvance();
        bboxTrans.y() = -maxTBoxSize.y();
        break;
      default:
        break;
      }

      Mesh2 bbox = createRectangleOutlineMesh2(maxTBoxSize, 1u);
      m2Rnd.draw(rw, bbox, color::red,
        proj * textTrans * trans2f::translation(bboxTrans));
    }

    TextBoxFormattingParams tbfp(textFlow, maxTBoxSize);
    FormattedText ft(textToRender, fontToRender, tbfp);
    Mesh2 textBox
      = createRectangleOutlineMesh2(ft.getBoundingBox().get_size(), 1u);
    m2Rnd.draw(rw, textBox, color::white,
      proj * textTrans
        * trans2f::translation(ft.getBoundingBox().get_position()));
    textRnd.draw(rw, ft, color::white, proj * textTrans);

    std::chrono::nanoseconds timePerFrame = timer.reset();
    m2Rnd.draw(rw, fpsRect, color::black, proj);
    FormattedText fpsText(
      to_string(1.f
        /
        std::chrono::duration_cast<std::chrono::duration<float>>(timePerFrame)
            .count()),
      font);
    textRnd.draw(rw, fpsText, color::white, proj * trans2f::translation(-fpsText.getBoundingBox().get_position()));
    rw.display();
  }

  return 0;
}
