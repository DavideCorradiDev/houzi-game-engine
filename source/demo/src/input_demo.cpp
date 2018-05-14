#include "hou/mth/transform2.hpp"

#include "hou/gfx/mesh2.hpp"
#include "hou/sys/color.hpp"
#include "hou/gfx/font.hpp"
#include "hou/gfx/vertex2.hpp"
#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/render_window.hpp"
#include "hou/gfx/texture.hpp"
#include "hou/gfx/mesh2_shader_program.hpp"
#include "hou/gfx/text_shader_program.hpp"

#include "hou/cor/clock.hpp"
#include "hou/sys/binary_file_in.hpp"
#include "hou/sys/image.hpp"
#include "hou/sys/keyboard.hpp"
#include "hou/sys/mouse.hpp"
#include "hou/sys/window_event.hpp"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <list>
#include <vector>



namespace
{

class KeyInfo
{
public:
  KeyInfo(const hou::trans2f& trans, const hou::mesh2& quad
    , hou::key_code key, hou::scan_code sc);

  const hou::trans2f& getTrans() const;
  const hou::mesh2& getQuad() const;
  hou::key_code getKey() const;
  hou::scan_code getScanCode() const;

private:
  hou::trans2f mTrans;
  const hou::mesh2* mQuad;
  hou::key_code m_key;
  hou::scan_code mScanCode;
};



KeyInfo::KeyInfo(const hou::trans2f& trans, const hou::mesh2& quad
    , hou::key_code key, hou::scan_code sc)
  : mTrans(trans)
  , mQuad(&quad)
  , m_key(key)
  , mScanCode(sc)
{}



const hou::trans2f& KeyInfo::getTrans() const
{
  return mTrans;
}



const hou::mesh2& KeyInfo::getQuad() const
{
  return *mQuad;
}



hou::key_code KeyInfo::getKey() const
{
  return m_key;
}



hou::scan_code KeyInfo::getScanCode() const
{
  return mScanCode;
}

}



int main()
{
  static const std::string dataDir = u8"source/demo/data/";
  // Constants
  static const std::chrono::nanoseconds frameTime = std::chrono::nanoseconds(1000000000 / 60);
  static const hou::trans2f keyboard1TextTrans = hou::trans2f::translation(hou::vec2f(8.f, 16.f));
  static const hou::trans2f keyboard1Trans = hou::trans2f::translation(hou::vec2f(8.f, 24.f));
  static const hou::trans2f keyboard2TextTrans = hou::trans2f::translation(hou::vec2f(408.f, 16.f));
  static const hou::trans2f keyboard2Trans = hou::trans2f::translation(hou::vec2f(408.f, 24.f));
  static const hou::trans2f mouseTrans = hou::trans2f::translation(hou::vec2f(8.f, 152.f));
  static const hou::trans2f mousePosTextTrans = hou::trans2f::translation(hou::vec2f(80.f, 176.f));
  static const hou::trans2f mouseRelPosTextTrans = hou::trans2f::translation(hou::vec2f(80.f, 198.f));
  static const hou::trans2f mouseHintText1Trans = hou::trans2f::translation(hou::vec2f(380.f, 176.f));
  static const hou::trans2f mouseHintText2Trans = hou::trans2f::translation(hou::vec2f(380.f, 198.f));
  static const hou::trans2f eventQueueTrans = hou::trans2f::translation(hou::vec2f(10.f, 250.f));
  static const size_t maxEventQueueSize = 4;
  static const hou::vec2f evSize((800.f - 20.f) / maxEventQueueSize, (800.f - 20.f) / maxEventQueueSize);

  // Initialization of objects used for rendering.
  hou::graphic_context ctx;
  hou::graphic_context::set_current(ctx);
  hou::render_window wnd(u8"Input Demo", hou::vec2u(800u, 600u),
    hou::window_style::windowed_resizable);
  wnd.set_visible(true);
  wnd.set_key_repeat_enabled(false);
  wnd.set_mouse_cursor_grabbed(false);
  hou::mesh2_shader_program meshRnd;
  hou::text_shader_program textRnd;

  std::string iconFilename = dataDir + u8"monkey.png";
  hou::image2_rgba iconRGBA = hou::png_read_file<hou::pixel_format::rgba>(iconFilename);
  hou::image2_rgb iconRGB = hou::png_read_file<hou::pixel_format::rgb>(iconFilename);
  hou::image2_rg iconRG = hou::png_read_file<hou::pixel_format::rg>(iconFilename);
  hou::image2_r iconR = hou::png_read_file<hou::pixel_format::r>(iconFilename);

  hou::texture2 keyboardTex(hou::png_read_file<hou::pixel_format::rgba>(dataDir + u8"keyboard.png"));
  hou::texture2 keyboardKeysTex(hou::png_read_file<hou::pixel_format::rgba>(dataDir + u8"keyboardkeys.png"));
  hou::texture2 mouseTex(hou::png_read_file<hou::pixel_format::rgba>(dataDir + u8"mouse.png"));
  hou::texture2 mousebuttonsTex(hou::png_read_file<hou::pixel_format::rgba>(dataDir + u8"mousebuttons.png"));

  hou::font fnt = hou::font(hou::binary_file_in(dataDir + u8"NotoMono-Regular.ttf"));

  hou::mesh2 keyboardQuad = hou::create_texture_quad_mesh2
    ( hou::rectf(0, 0, keyboardTex.get_size().x(), keyboardTex.get_size().y())
    , keyboardTex.get_size());
  hou::mesh2 key1Quad = hou::create_texture_quad_mesh2
    ( hou::rectf(72, 0, 16, 16)
    , keyboardKeysTex.get_size());
  hou::mesh2 key1hQuad = hou::create_texture_quad_mesh2
    ( hou::rectf(0, 16, 24, 16)
    , keyboardKeysTex.get_size());
  hou::mesh2 key2Quad = hou::create_texture_quad_mesh2
    ( hou::rectf(24, 16, 32, 16)
    , keyboardKeysTex.get_size());
  hou::mesh2 key2hQuad = hou::create_texture_quad_mesh2
    ( hou::rectf(56, 16, 40, 16)
    , keyboardKeysTex.get_size());
  hou::mesh2 key4hQuad = hou::create_texture_quad_mesh2
    ( hou::rectf(0, 0, 72, 16)
    , keyboardKeysTex.get_size());
  hou::mesh2 keyEnterQuad = hou::create_texture_quad_mesh2
    ( hou::rectf(96, 0, 24, 32)
    , keyboardKeysTex.get_size());
  hou::mesh2 keyVertQuad = hou::create_texture_quad_mesh2
    ( hou::rectf(120, 0, 16, 32)
    , keyboardKeysTex.get_size());
  hou::mesh2 mouseQuad = hou::create_texture_quad_mesh2
    ( hou::rectf(0, 0, mouseTex.get_size().x(), mouseTex.get_size().y())
    , mouseTex.get_size());
  hou::mesh2 mouseBtnQuad = hou::create_texture_quad_mesh2
    ( hou::rectf(0, 0, 16, 25)
    , mousebuttonsTex.get_size());
  hou::mesh2 mouseWheelQuad = hou::create_texture_quad_mesh2
    ( hou::rectf(16, 0, 6, 12)
    , mousebuttonsTex.get_size());
  hou::mesh2 mouseBtnXQuad = hou::create_texture_quad_mesh2
    ( hou::rectf(17, 12, 5, 9)
    , mousebuttonsTex.get_size());

  hou::mesh2 eventRect = hou::create_rectangle_mesh2(evSize - hou::vec2f(4.f, 4.f));

  hou::mesh2 keyboardLed = hou::create_rectangle_mesh2(hou::vec2f(8.f, 4.f));

  hou::trans2f projTrans = hou::trans2f::orthographic_projection(hou::rectf(0.f, 0.f, wnd.get_size().x()
    , wnd.get_size().y()));

  std::list<hou::window_event> eventQueue;

  // Initialization of key information
  std::vector<KeyInfo> keyMap;

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(16.f, 8.f)), key1Quad
    , hou::key_code::escape, hou::scan_code::escape));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(40.f, 8.f)), key1Quad
    , hou::key_code::f1, hou::scan_code::f1));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(56.f, 8.f)), key1Quad
    , hou::key_code::f2, hou::scan_code::f2));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(72.f, 8.f)), key1Quad
    , hou::key_code::f3, hou::scan_code::f3));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(88.f, 8.f)), key1Quad
    , hou::key_code::f4, hou::scan_code::f4));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(112.f, 8.f)), key1Quad
    , hou::key_code::f5, hou::scan_code::f5));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(128.f, 8.f)), key1Quad
    , hou::key_code::f6, hou::scan_code::f6));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(144.f, 8.f)), key1Quad
    , hou::key_code::f7, hou::scan_code::f7));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(160.f, 8.f)), key1Quad
    , hou::key_code::f8, hou::scan_code::f8));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(184.f, 8.f)), key1Quad
    , hou::key_code::f9, hou::scan_code::f9));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(200.f, 8.f)), key1Quad
    , hou::key_code::f10, hou::scan_code::f10));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(216.f, 8.f)), key1Quad
    , hou::key_code::f11, hou::scan_code::f11));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(232.f, 8.f)), key1Quad
    , hou::key_code::f12, hou::scan_code::f12));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(256.f, 8.f)), key1Quad
    , hou::key_code::print_screen, hou::scan_code::print_screen));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 8.f)), key1Quad
    , hou::key_code::scroll_lock, hou::scan_code::scroll_lock));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(288.f, 8.f)), key1Quad
    , hou::key_code::pause, hou::scan_code::pause));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(256.f, 32.f)), key1Quad
    , hou::key_code::ins, hou::scan_code::ins));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 32.f)), key1Quad
    , hou::key_code::home, hou::scan_code::home));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(288.f, 32.f)), key1Quad
    , hou::key_code::page_up, hou::scan_code::page_up));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(256.f, 48.f)), key1Quad
    , hou::key_code::del, hou::scan_code::del));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 48.f)), key1Quad
    , hou::key_code::end, hou::scan_code::end));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(288.f, 48.f)), key1Quad
    , hou::key_code::page_down, hou::scan_code::page_down));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 80.f)), key1Quad
    , hou::key_code::up, hou::scan_code::up));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(256.f, 96.f)), key1Quad
    , hou::key_code::left, hou::scan_code::left));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 96.f)), key1Quad
    , hou::key_code::down, hou::scan_code::down));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(288.f, 96.f)), key1Quad
    , hou::key_code::right, hou::scan_code::right));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 32.f)), key1Quad
    , hou::key_code::tilde, hou::scan_code::tilde));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(24.f, 32.f)), key1Quad
    , hou::key_code::num1, hou::scan_code::num1));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(40.f, 32.f)), key1Quad
    , hou::key_code::num2, hou::scan_code::num2));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(56.f, 32.f)), key1Quad
    , hou::key_code::num3, hou::scan_code::num3));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(72.f, 32.f)), key1Quad
    , hou::key_code::num4, hou::scan_code::num4));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(88.f, 32.f)), key1Quad
    , hou::key_code::num5, hou::scan_code::num5));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(104.f, 32.f)), key1Quad
    , hou::key_code::num6, hou::scan_code::num6));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(120.f, 32.f)), key1Quad
    , hou::key_code::num7, hou::scan_code::num7));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(136.f, 32.f)), key1Quad
    , hou::key_code::num8, hou::scan_code::num8));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(152.f, 32.f)), key1Quad
    , hou::key_code::num9, hou::scan_code::num9));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(168.f, 32.f)), key1Quad
    , hou::key_code::num0, hou::scan_code::num0));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(184.f, 32.f)), key1Quad
    , hou::key_code::dash, hou::scan_code::dash));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(200.f, 32.f)), key1Quad
    , hou::key_code::equal, hou::scan_code::equal));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(216.f, 32.f)), key2Quad
    , hou::key_code::backspace, hou::scan_code::backspace));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 48.f)), key1hQuad
    , hou::key_code::tab, hou::scan_code::tab));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(32.f, 48.f)), key1Quad
    , hou::key_code::q, hou::scan_code::q));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(48.f, 48.f)), key1Quad
    , hou::key_code::w, hou::scan_code::w));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(64.f, 48.f)), key1Quad
    , hou::key_code::e, hou::scan_code::e));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(80.f, 48.f)), key1Quad
    , hou::key_code::r, hou::scan_code::r));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(96.f, 48.f)), key1Quad
    , hou::key_code::t, hou::scan_code::t));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(112.f, 48.f)), key1Quad
    , hou::key_code::y, hou::scan_code::y));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(128.f, 48.f)), key1Quad
    , hou::key_code::u, hou::scan_code::u));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(144.f, 48.f)), key1Quad
    , hou::key_code::i, hou::scan_code::i));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(160.f, 48.f)), key1Quad
    , hou::key_code::o, hou::scan_code::o));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(176.f, 48.f)), key1Quad
    , hou::key_code::p, hou::scan_code::p));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(192.f, 48.f)), key1Quad
    , hou::key_code::l_bracket, hou::scan_code::l_bracket));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(208.f, 48.f)), key1Quad
    , hou::key_code::r_bracket, hou::scan_code::r_bracket));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(224.f, 48.f)), keyEnterQuad
    , hou::key_code::enter, hou::scan_code::enter));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 64.f)), key2Quad
    , hou::key_code::caps_lock, hou::scan_code::caps_lock));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(40.f, 64.f)), key1Quad
    , hou::key_code::a, hou::scan_code::a));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(56.f, 64.f)), key1Quad
    , hou::key_code::s, hou::scan_code::s));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(72.f, 64.f)), key1Quad
    , hou::key_code::d, hou::scan_code::d));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(88.f, 64.f)), key1Quad
    , hou::key_code::f, hou::scan_code::f));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(104.f, 64.f)), key1Quad
    , hou::key_code::g, hou::scan_code::g));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(120.f, 64.f)), key1Quad
    , hou::key_code::h, hou::scan_code::h));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(136.f, 64.f)), key1Quad
    , hou::key_code::j, hou::scan_code::j));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(152.f, 64.f)), key1Quad
    , hou::key_code::k, hou::scan_code::k));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(168.f, 64.f)), key1Quad
    , hou::key_code::l, hou::scan_code::l));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(184.f, 64.f)), key1Quad
    , hou::key_code::semicolon, hou::scan_code::semicolon));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(200.f, 64.f)), key1Quad
    , hou::key_code::quote, hou::scan_code::quote));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(216.f, 64.f)), key1Quad
    , hou::key_code::backslash, hou::scan_code::backslash));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 80.f)), key2hQuad
    , hou::key_code::l_shift, hou::scan_code::l_shift));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(48.f, 80.f)), key1Quad
    , hou::key_code::z, hou::scan_code::z));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(64.f, 80.f)), key1Quad
    , hou::key_code::x, hou::scan_code::x));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(80.f, 80.f)), key1Quad
    , hou::key_code::c, hou::scan_code::c));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(96.f, 80.f)), key1Quad
    , hou::key_code::v, hou::scan_code::v));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(112.f, 80.f)), key1Quad
    , hou::key_code::b, hou::scan_code::b));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(128.f, 80.f)), key1Quad
    , hou::key_code::n, hou::scan_code::n));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(144.f, 80.f)), key1Quad
    , hou::key_code::m, hou::scan_code::m));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(160.f, 80.f)), key1Quad
    , hou::key_code::comma, hou::scan_code::comma));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(176.f, 80.f)), key1Quad
    , hou::key_code::period, hou::scan_code::period));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(192.f, 80.f)), key1Quad
    , hou::key_code::slash, hou::scan_code::slash));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(208.f, 80.f)), key2hQuad
    , hou::key_code::r_shift, hou::scan_code::r_shift));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 96.f)), key1hQuad
    , hou::key_code::l_ctrl, hou::scan_code::l_ctrl));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(32.f, 96.f)), key1hQuad
    , hou::key_code::l_system, hou::scan_code::l_system));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(56.f, 96.f)), key1hQuad
    , hou::key_code::l_alt, hou::scan_code::l_alt));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(80.f, 96.f)), key4hQuad
    , hou::key_code::space, hou::scan_code::space));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(152.f, 96.f)), key1hQuad
    , hou::key_code::r_alt, hou::scan_code::r_alt));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(176.f, 96.f)), key1hQuad
    , hou::key_code::r_system, hou::scan_code::r_system));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(200.f, 96.f)), key1hQuad
    , hou::key_code::apps, hou::scan_code::apps));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(224.f, 96.f)), key1hQuad
    , hou::key_code::r_ctrl, hou::scan_code::r_ctrl));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 32.f)), key1Quad
    , hou::key_code::num_lock, hou::scan_code::num_lock));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(328.f, 32.f)), key1Quad
    , hou::key_code::divide, hou::scan_code::divide));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 32.f)), key1Quad
    , hou::key_code::multiply, hou::scan_code::multiply));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(360.f, 32.f)), key1Quad
    , hou::key_code::subtract, hou::scan_code::subtract));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 48.f)), key1Quad
    , hou::key_code::numpad7, hou::scan_code::numpad7));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(328.f, 48.f)), key1Quad
    , hou::key_code::numpad8, hou::scan_code::numpad8));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 48.f)), key1Quad
    , hou::key_code::numpad9, hou::scan_code::numpad9));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(360.f, 48.f)), keyVertQuad
    , hou::key_code::add, hou::scan_code::add));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 64.f)), key1Quad
    , hou::key_code::numpad4, hou::scan_code::numpad4));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(328.f, 64.f)), key1Quad
    , hou::key_code::numpad5, hou::scan_code::numpad5));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 64.f)), key1Quad
    , hou::key_code::numpad6, hou::scan_code::numpad6));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 80.f)), key1Quad
    , hou::key_code::numpad1, hou::scan_code::numpad1));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(328.f, 80.f)), key1Quad
    , hou::key_code::numpad2, hou::scan_code::numpad2));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 80.f)), key1Quad
    , hou::key_code::numpad3, hou::scan_code::numpad3));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(360.f, 80.f)), keyVertQuad
    , hou::key_code::enter, hou::scan_code::enter));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 96.f)), key2Quad
    , hou::key_code::numpad0, hou::scan_code::numpad0));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 96.f)), key1Quad
    , hou::key_code::decimal, hou::scan_code::decimal));

  // Main loop.
  bool running = true;
  std::chrono::nanoseconds lastUpdateTime(frameTime);
  hou::clock p_clock;
  while(running)
  {
    // Process event queue.
    wnd.update_event_queue();
    while(!wnd.is_event_queue_empty())
    {
      hou::window_event we = wnd.pop_event();
      switch(we.get_type())
      {
        case hou::window_event_type::closed:
        {
          running = false;
          break;
        }
        case hou::window_event_type::key_pressed:
        {
          auto data = we.get_key_data();
          if(hou::check_bit(data.modifier_keys, hou::modifier_keys::ctrl))
          {
            if(data.scan_code == hou::scan_code::num1)
            {
              wnd.set_icon(iconR);
            }
            else if(data.scan_code == hou::scan_code::num2)
            {
              wnd.set_icon(iconRG);
            }
            else if(data.scan_code == hou::scan_code::num3)
            {
              wnd.set_icon(iconRGB);
            }
            else if(data.scan_code == hou::scan_code::num4)
            {
              wnd.set_icon(iconRGBA);
            }
            else if(data.scan_code == hou::scan_code::num5)
            {
              wnd.set_system_icon();
            }
          }
          break;
        }
        case hou::window_event_type::focus_gained:
        case hou::window_event_type::focus_lost:
        case hou::window_event_type::resized:
        case hou::window_event_type::key_released:
        case hou::window_event_type::text_entered:
        case hou::window_event_type::mouse_moved:
        case hou::window_event_type::mouse_entered:
        case hou::window_event_type::mouse_left:
        case hou::window_event_type::mouse_button_pressed:
        case hou::window_event_type::mouse_button_released:
        case hou::window_event_type::mouse_wheel_moved:
          break;
      }
      eventQueue.push_back(we);
      while(eventQueue.size() > maxEventQueueSize) {
        eventQueue.pop_front();
      }
    }

    // Update cycle
    if((p_clock.get_elapsed_time() - lastUpdateTime) >= frameTime)
    {
      lastUpdateTime += frameTime;

      // Draw static images.
      wnd.clear(hou::color::black);
      textRnd.draw(wnd, "KEYBOARD KEY CODE", fnt, hou::color::red
        , projTrans * keyboard1TextTrans);
      meshRnd.draw(wnd, keyboardQuad, keyboardTex, hou::color::white
        , projTrans * keyboard1Trans);
      textRnd.draw(wnd, "KEYBOARD SCAN CODE", fnt, hou::color::yellow
        , projTrans * keyboard2TextTrans);
      meshRnd.draw(wnd, keyboardQuad, keyboardTex, hou::color::white
        , projTrans * keyboard2Trans);
      meshRnd.draw(wnd, mouseQuad, mouseTex, hou::color::white
        , projTrans * mouseTrans);
      std::string mousePosText = hou::format_string("SCREEN MOUSE CURSOR POSITION: (%d, %d)"
        , hou::mouse::get_position().x(), hou::mouse::get_position().y());
      textRnd.draw(wnd, mousePosText, fnt, hou::color::green
        , projTrans * mousePosTextTrans);
      std::string mouseRelPosText = hou::format_string("WINDOW MOUSE CURSOR POSITION: (%d, %d)"
        , hou::mouse::get_position(wnd).x(), hou::mouse::get_position(wnd).y());
      textRnd.draw(wnd, mouseRelPosText, fnt, hou::color::green
        , projTrans * mouseRelPosTextTrans);
      textRnd.draw(wnd
        , "PRESS CTRL+O TO MOVE THE MOUSE CURSOR TO THE SCREEN ORIGIN", fnt
        , hou::color::green, projTrans * mouseHintText1Trans);
      textRnd.draw(wnd
        , "PRESS CTRL+P TO MOVE THE MOUSE CURSOR TO THE WINDOW ORIGIN", fnt
        , hou::color::green, projTrans * mouseHintText2Trans);

      // Draw events in queue.
      hou::trans2f evTrans;
      for(const auto& ev : eventQueue)
      {
        meshRnd.draw(wnd, eventRect, hou::color::green, projTrans * eventQueueTrans * evTrans);
        std::stringstream ss;
        ss << ev;
        if(ev.get_type() == hou::window_event_type::text_entered)
        {
          ss << "  " <<  hou::convert_encoding<hou::utf8, hou::utf32>(std::u32string(1, ev.get_text_data().code_point)) << "\n";
        }
        textRnd.draw(wnd, ss.str(), fnt, hou::color::black
          , projTrans * eventQueueTrans * evTrans * hou::trans2f::translation(hou::vec2f(4.f, 16.f)));
        evTrans *= hou::trans2f::translation(hou::vec2f(evSize.x(), 0.f));
      }

      // Draw pressed keys
      for(const auto& info : keyMap)
      {
        if(hou::keyboard::is_key_pressed(info.getKey()))
        {
          meshRnd.draw(wnd
            , info.getQuad()
            , keyboardKeysTex
            , hou::color::red
            , projTrans * keyboard1Trans * info.getTrans());
        }
        if(hou::keyboard::is_key_pressed(info.getScanCode()))
        {
          meshRnd.draw(wnd
            , info.getQuad()
            , keyboardKeysTex
            , hou::color::yellow
            , projTrans * keyboard2Trans * info.getTrans());
        }
      }

      // Draw keyboard LEDs
      meshRnd.draw(wnd
        , keyboardLed
        , hou::keyboard::is_key_toggled(hou::key_code::num_lock)
        ? hou::color::red : hou::color::black
        , projTrans * keyboard1Trans * hou::trans2f::translation(hou::vec2f(312.f, 8.f)));
      meshRnd.draw(wnd
        , keyboardLed
        , hou::keyboard::is_key_toggled(hou::key_code::caps_lock)
        ? hou::color::red : hou::color::black
        , projTrans * keyboard1Trans * hou::trans2f::translation(hou::vec2f(328.f, 8.f)));
      meshRnd.draw(wnd
        , keyboardLed
        , hou::keyboard::is_key_toggled(hou::key_code::scroll_lock)
        ? hou::color::red : hou::color::black
        , projTrans * keyboard1Trans * hou::trans2f::translation(hou::vec2f(344.f, 8.f)));

      meshRnd.draw(wnd
        , keyboardLed
        , hou::keyboard::is_key_toggled(hou::scan_code::num_lock)
        ? hou::color::yellow : hou::color::black
        , projTrans * keyboard2Trans * hou::trans2f::translation(hou::vec2f(312.f, 8.f)));
      meshRnd.draw(wnd
        , keyboardLed
        , hou::keyboard::is_key_toggled(hou::scan_code::caps_lock)
        ? hou::color::yellow : hou::color::black
        , projTrans * keyboard2Trans * hou::trans2f::translation(hou::vec2f(328.f, 8.f)));
      meshRnd.draw(wnd
        , keyboardLed
        , hou::keyboard::is_key_toggled(hou::scan_code::scroll_lock)
        ? hou::color::yellow : hou::color::black
        , projTrans * keyboard2Trans * hou::trans2f::translation(hou::vec2f(344.f, 8.f)));

      // Draw mouse buttons.
      if(hou::mouse::is_button_pressed(hou::mouse_button::lb))
      {
        meshRnd.draw(wnd
          , mouseBtnQuad
          , mousebuttonsTex
          , hou::color::green
          , projTrans * mouseTrans * hou::trans2f::translation(hou::vec2f(11.f, 7.f)));
      }
      if(hou::mouse::is_button_pressed(hou::mouse_button::rb))
      {
        meshRnd.draw(wnd
          , mouseBtnQuad
          , mousebuttonsTex
          , hou::color::green
          , projTrans * mouseTrans * hou::trans2f::translation(hou::vec2f(37.f, 7.f)));
      }
      if(hou::mouse::is_button_pressed(hou::mouse_button::mb))
      {
        meshRnd.draw(wnd
          , mouseWheelQuad
          , mousebuttonsTex
          , hou::color::green
          , projTrans * mouseTrans * hou::trans2f::translation(hou::vec2f(29.f, 13.f)));
      }
      if(hou::mouse::is_button_pressed(hou::mouse_button::xb1))
      {
        meshRnd.draw(wnd
          , mouseBtnXQuad
          , mousebuttonsTex
          , hou::color::green
          , projTrans * mouseTrans * hou::trans2f::translation(hou::vec2f(5.f, 32.f)));
      }
      if(hou::mouse::is_button_pressed(hou::mouse_button::xb2))
      {
        meshRnd.draw(wnd
          , mouseBtnXQuad
          , mousebuttonsTex
          , hou::color::green
          , projTrans * mouseTrans * hou::trans2f::translation(hou::vec2f(54.f, 32.f)));
      }

      if(hou::keyboard::is_key_pressed(hou::key_code::l_ctrl)
        && hou::keyboard::is_key_pressed(hou::key_code::o))
      {
        hou::mouse::set_position(hou::vec2i(0, 0));
      }
      else if(hou::keyboard::is_key_pressed(hou::key_code::l_ctrl)
        && hou::keyboard::is_key_pressed(hou::key_code::p))
      {
        hou::mouse::set_position(hou::vec2i(0, 0), wnd);
      }

      wnd.display();
    }
  }
}
