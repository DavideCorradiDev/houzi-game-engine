#include "hou/cor/stopwatch.hpp"
#include "hou/gfx/font.hpp"
#include "hou/gfx/formatted_text.hpp"
#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/mesh.hpp"
#include "hou/gfx/mesh2_shader_program.hpp"
#include "hou/gfx/render_window.hpp"
#include "hou/gfx/text_shader_program.hpp"
#include "hou/gfx/vertex2.hpp"
#include "hou/mth/transform2.hpp"
#include "hou/sys/binary_file_in.hpp"
#include "hou/sys/color.hpp"
#include "hou/sys/window_event.hpp"

using namespace hou;



int main()
{
  static const std::string dataDir = u8"source/demo/data/";
  graphic_context ctx;
  graphic_context::set_current(ctx);
  render_window rw(u8"text Rendering Demo", vec2u(800u, 600u),
    window_style::windowed_resizable, 8u);
  rw.set_visible(true);
  trans2f proj = trans2f::orthographic_projection(rw.get_viewport());
  mesh2_shader_program m2Rnd;
  text_shader_program textRnd;
  mesh2 fpsRect = create_rectangle_mesh2(vec2f(128.f, 32.f));
  std::vector<uint> fontSizes{0, 2, 4, 8, 16, 32, 64};
  size_t currentSizeIdx = 3;
  font ph_font(std::make_unique<binary_file_in>(dataDir + u8"NotoSans-Regular.ttf"));
  font chineseFont(
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
  ph_font.set_pixel_height(fontSizes[currentSizeIdx]);
  chineseFont.set_pixel_height(fontSizes[currentSizeIdx]);
  uint linesNum = 38;
  for(uint i = 0u; i < linesNum; ++i)
  {
    text.append(textLine);
    chineseText.append(chineseTextLine);
  }
  trans2f textTrans = trans2f::translation(vec2f(128.f, 200.f));


  std::cout << "Drawing " << textLine.size() * linesNum << " characters."
            << std::endl;
  text_flow textFlow = text_flow::LeftRight;
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
        if(we.get_key_data().scan_code == scan_code::down
          || we.get_key_data().scan_code == scan_code::up
          || we.get_key_data().scan_code == scan_code::r_shift)
        {
          if(we.get_key_data().scan_code == scan_code::down)
          {
            if(currentSizeIdx > 0)
            {
              --currentSizeIdx;
            }
          }
          else if(we.get_key_data().scan_code == scan_code::up)
          {
            if(currentSizeIdx < fontSizes.size() - 1)
            {
              ++currentSizeIdx;
            }
          }
          else if(we.get_key_data().scan_code == scan_code::r_shift)
          {
            printChinese = !printChinese;
          }
          ph_font.set_pixel_height(fontSizes[currentSizeIdx]);
          chineseFont.set_pixel_height(fontSizes[currentSizeIdx]);
        }
        else if(we.get_key_data().scan_code == scan_code::a)
        {
          textFlow = text_flow::RightLeft;
        }
        else if(we.get_key_data().scan_code == scan_code::d)
        {
          textFlow = text_flow::LeftRight;
        }
        else if(we.get_key_data().scan_code == scan_code::w)
        {
          textFlow = text_flow::BottomTop;
        }
        else if(we.get_key_data().scan_code == scan_code::s)
        {
          textFlow = text_flow::TopBottom;
        }
        else if(we.get_key_data().scan_code == scan_code::k)
        {
          maxTBoxSize.x() = std::max(0.f, maxTBoxSize.x() - maxTBoxIncrement);
        }
        else if(we.get_key_data().scan_code == scan_code::semicolon)
        {
          maxTBoxSize.x() = std::min(640.f, maxTBoxSize.x() + maxTBoxIncrement);
        }
        else if(we.get_key_data().scan_code == scan_code::o)
        {
          maxTBoxSize.y() = std::max(0.f, maxTBoxSize.y() - maxTBoxIncrement);
        }
        else if(we.get_key_data().scan_code == scan_code::l)
        {
          maxTBoxSize.y() = std::min(640.f, maxTBoxSize.y() + maxTBoxIncrement);
        }
      }
      break;
      case hou::window_event_type::resized:
        rw.set_viewport(rw.get_default_viewport());
        proj = trans2f::orthographic_projection(rw.get_viewport());
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
      case hou::window_event_type::text_entered:
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
    font& fontToRender = printChinese ? chineseFont : ph_font;

    if(maxTBoxSize.x() == 0.f || maxTBoxSize.y() == 0.f)
    {
      mesh2 dot = create_ellipse_mesh2(vec2f(16.f, 16.f), 32u);
      m2Rnd.draw(rw, dot, color::red,
        proj * textTrans * trans2f::translation(vec2f(-8.f, -8.f)));
    }
    else
    {
      vec2f bboxTrans;
      switch(textFlow)
      {
      case text_flow::LeftRight:
        bboxTrans.y() = -fontToRender.get_pixel_line_spacing();
        break;
      case text_flow::RightLeft:
        bboxTrans.x() = -maxTBoxSize.x();
        bboxTrans.y() = -fontToRender.get_pixel_line_spacing();
        break;
      case text_flow::TopBottom:
        bboxTrans.x() = -0.5f * fontToRender.get_pixel_max_advance();
        break;
      case text_flow::BottomTop:
        bboxTrans.x() = -0.5f * fontToRender.get_pixel_max_advance();
        bboxTrans.y() = -maxTBoxSize.y();
        break;
      default:
        break;
      }

      mesh2 bbox = create_rectangle_outline_mesh2(maxTBoxSize, 1u);
      m2Rnd.draw(rw, bbox, color::red,
        proj * textTrans * trans2f::translation(bboxTrans));
    }

    text_box_formatting_params tbfp(textFlow, maxTBoxSize);
    formatted_text ft(textToRender, fontToRender, tbfp);
    mesh2 textBox
      = create_rectangle_outline_mesh2(ft.get_bounding_box().get_size(), 1u);
    m2Rnd.draw(rw, textBox, color::white,
      proj * textTrans
        * trans2f::translation(ft.get_bounding_box().get_position()));
    textRnd.draw(rw, ft, color::white, proj * textTrans);

    std::chrono::nanoseconds timePerFrame = timer.reset();
    m2Rnd.draw(rw, fpsRect, color::black, proj);
    formatted_text fpsText(
      to_string(1.f
        /
        std::chrono::duration_cast<std::chrono::duration<float>>(timePerFrame)
            .count()),
      ph_font);
    textRnd.draw(rw, fpsText, color::white, proj * trans2f::translation(-fpsText.get_bounding_box().get_position()));
    rw.display();
  }

  return 0;
}
