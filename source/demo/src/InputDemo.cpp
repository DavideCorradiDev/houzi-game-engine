#include "hou/cor/basic_types.hpp"

#include "hou/mth/transform2.hpp"

#include "hou/gfx/Mesh.hpp"
#include "hou/sys/color.hpp"
#include "hou/gfx/Font.hpp"
#include "hou/gfx/Vertex2.hpp"
#include "hou/gfx/GraphicContext.hpp"
#include "hou/gfx/RenderWindow.hpp"
#include "hou/gfx/Texture.hpp"
#include "hou/gfx/Mesh2ShaderProgram.hpp"
#include "hou/gfx/TextShaderProgram.hpp"

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
  KeyInfo(const hou::trans2f& trans, const hou::Mesh2& quad
    , hou::key_code key, hou::scan_code sc);

  const hou::trans2f& getTrans() const;
  const hou::Mesh2& getQuad() const;
  hou::key_code getKey() const;
  hou::scan_code getScanCode() const;

private:
  hou::trans2f mTrans;
  const hou::Mesh2* mQuad;
  hou::key_code m_key;
  hou::scan_code mScanCode;
};



KeyInfo::KeyInfo(const hou::trans2f& trans, const hou::Mesh2& quad
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



const hou::Mesh2& KeyInfo::getQuad() const
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
  hou::GraphicContext ctx;
  hou::GraphicContext::setCurrent(ctx);
  hou::RenderWindow wnd(u8"Input Demo", hou::vec2u(800u, 600u),
    hou::window_style::windowed_resizable);
  wnd.set_visible(true);
  wnd.set_key_repeat_enabled(false);
  wnd.set_mouse_cursor_grabbed(false);
  hou::Mesh2ShaderProgram meshRnd;
  hou::TextShaderProgram textRnd;

  std::string iconFilename = dataDir + u8"monkey.png";
  hou::image2RGBA iconRGBA = hou::png_read_file<hou::pixel_format::rgba>(iconFilename);
  hou::image2RGB iconRGB = hou::png_read_file<hou::pixel_format::rgb>(iconFilename);
  hou::image2RG iconRG = hou::png_read_file<hou::pixel_format::rg>(iconFilename);
  hou::image2R iconR = hou::png_read_file<hou::pixel_format::r>(iconFilename);

  hou::Texture2 keyboardTex(hou::png_read_file<hou::pixel_format::rgba>(dataDir + u8"keyboard.png"));
  hou::Texture2 keyboardKeysTex(hou::png_read_file<hou::pixel_format::rgba>(dataDir + u8"keyboardkeys.png"));
  hou::Texture2 mouseTex(hou::png_read_file<hou::pixel_format::rgba>(dataDir + u8"mouse.png"));
  hou::Texture2 mousebuttonsTex(hou::png_read_file<hou::pixel_format::rgba>(dataDir + u8"mousebuttons.png"));

  hou::Font font(std::make_unique<hou::binary_file_in>(dataDir + u8"NotoMono-Regular.ttf"));

  hou::Mesh2 keyboardQuad = hou::createTextureQuadMesh2
    ( hou::rectf(0, 0, keyboardTex.get_size().x(), keyboardTex.get_size().y())
    , keyboardTex.get_size());
  hou::Mesh2 key1Quad = hou::createTextureQuadMesh2
    ( hou::rectf(72, 0, 16, 16)
    , keyboardKeysTex.get_size());
  hou::Mesh2 key1hQuad = hou::createTextureQuadMesh2
    ( hou::rectf(0, 16, 24, 16)
    , keyboardKeysTex.get_size());
  hou::Mesh2 key2Quad = hou::createTextureQuadMesh2
    ( hou::rectf(24, 16, 32, 16)
    , keyboardKeysTex.get_size());
  hou::Mesh2 key2hQuad = hou::createTextureQuadMesh2
    ( hou::rectf(56, 16, 40, 16)
    , keyboardKeysTex.get_size());
  hou::Mesh2 key4hQuad = hou::createTextureQuadMesh2
    ( hou::rectf(0, 0, 72, 16)
    , keyboardKeysTex.get_size());
  hou::Mesh2 keyEnterQuad = hou::createTextureQuadMesh2
    ( hou::rectf(96, 0, 24, 32)
    , keyboardKeysTex.get_size());
  hou::Mesh2 keyVertQuad = hou::createTextureQuadMesh2
    ( hou::rectf(120, 0, 16, 32)
    , keyboardKeysTex.get_size());
  hou::Mesh2 mouseQuad = hou::createTextureQuadMesh2
    ( hou::rectf(0, 0, mouseTex.get_size().x(), mouseTex.get_size().y())
    , mouseTex.get_size());
  hou::Mesh2 mouseBtnQuad = hou::createTextureQuadMesh2
    ( hou::rectf(0, 0, 16, 25)
    , mousebuttonsTex.get_size());
  hou::Mesh2 mouseWheelQuad = hou::createTextureQuadMesh2
    ( hou::rectf(16, 0, 6, 12)
    , mousebuttonsTex.get_size());
  hou::Mesh2 mouseBtnXQuad = hou::createTextureQuadMesh2
    ( hou::rectf(17, 12, 5, 9)
    , mousebuttonsTex.get_size());

  hou::Mesh2 eventRect = hou::createRectangleMesh2(evSize - hou::vec2f(4.f, 4.f));

  hou::Mesh2 keyboardLed = hou::createRectangleMesh2(hou::vec2f(8.f, 4.f));

  hou::trans2f projTrans = hou::trans2f::orthographic_projection(hou::rectf(0.f, 0.f, wnd.get_size().x()
    , wnd.get_size().y()));

  std::list<hou::window_event> eventQueue;

  // Initialization of key information
  std::vector<KeyInfo> keyMap;

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(16.f, 8.f)), key1Quad
    , hou::key_code::Escape, hou::scan_code::Escape));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(40.f, 8.f)), key1Quad
    , hou::key_code::F1, hou::scan_code::F1));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(56.f, 8.f)), key1Quad
    , hou::key_code::F2, hou::scan_code::F2));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(72.f, 8.f)), key1Quad
    , hou::key_code::F3, hou::scan_code::F3));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(88.f, 8.f)), key1Quad
    , hou::key_code::F4, hou::scan_code::F4));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(112.f, 8.f)), key1Quad
    , hou::key_code::F5, hou::scan_code::F5));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(128.f, 8.f)), key1Quad
    , hou::key_code::F6, hou::scan_code::F6));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(144.f, 8.f)), key1Quad
    , hou::key_code::F7, hou::scan_code::F7));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(160.f, 8.f)), key1Quad
    , hou::key_code::F8, hou::scan_code::F8));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(184.f, 8.f)), key1Quad
    , hou::key_code::F9, hou::scan_code::F9));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(200.f, 8.f)), key1Quad
    , hou::key_code::F10, hou::scan_code::F10));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(216.f, 8.f)), key1Quad
    , hou::key_code::F11, hou::scan_code::F11));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(232.f, 8.f)), key1Quad
    , hou::key_code::F12, hou::scan_code::F12));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(256.f, 8.f)), key1Quad
    , hou::key_code::PrintScreen, hou::scan_code::PrintScreen));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 8.f)), key1Quad
    , hou::key_code::ScrollLock, hou::scan_code::ScrollLock));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(288.f, 8.f)), key1Quad
    , hou::key_code::Pause, hou::scan_code::Pause));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(256.f, 32.f)), key1Quad
    , hou::key_code::Insert, hou::scan_code::Insert));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 32.f)), key1Quad
    , hou::key_code::Home, hou::scan_code::Home));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(288.f, 32.f)), key1Quad
    , hou::key_code::PageUp, hou::scan_code::PageUp));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(256.f, 48.f)), key1Quad
    , hou::key_code::Delete, hou::scan_code::Delete));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 48.f)), key1Quad
    , hou::key_code::End, hou::scan_code::End));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(288.f, 48.f)), key1Quad
    , hou::key_code::PageDown, hou::scan_code::PageDown));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 80.f)), key1Quad
    , hou::key_code::Up, hou::scan_code::Up));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(256.f, 96.f)), key1Quad
    , hou::key_code::Left, hou::scan_code::Left));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 96.f)), key1Quad
    , hou::key_code::Down, hou::scan_code::Down));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(288.f, 96.f)), key1Quad
    , hou::key_code::Right, hou::scan_code::Right));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 32.f)), key1Quad
    , hou::key_code::Tilde, hou::scan_code::Tilde));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(24.f, 32.f)), key1Quad
    , hou::key_code::Num1, hou::scan_code::Num1));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(40.f, 32.f)), key1Quad
    , hou::key_code::Num2, hou::scan_code::Num2));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(56.f, 32.f)), key1Quad
    , hou::key_code::Num3, hou::scan_code::Num3));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(72.f, 32.f)), key1Quad
    , hou::key_code::Num4, hou::scan_code::Num4));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(88.f, 32.f)), key1Quad
    , hou::key_code::Num5, hou::scan_code::Num5));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(104.f, 32.f)), key1Quad
    , hou::key_code::Num6, hou::scan_code::Num6));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(120.f, 32.f)), key1Quad
    , hou::key_code::Num7, hou::scan_code::Num7));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(136.f, 32.f)), key1Quad
    , hou::key_code::Num8, hou::scan_code::Num8));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(152.f, 32.f)), key1Quad
    , hou::key_code::Num9, hou::scan_code::Num9));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(168.f, 32.f)), key1Quad
    , hou::key_code::Num0, hou::scan_code::Num0));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(184.f, 32.f)), key1Quad
    , hou::key_code::Dash, hou::scan_code::Dash));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(200.f, 32.f)), key1Quad
    , hou::key_code::Equal, hou::scan_code::Equal));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(216.f, 32.f)), key2Quad
    , hou::key_code::Backspace, hou::scan_code::Backspace));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 48.f)), key1hQuad
    , hou::key_code::Tab, hou::scan_code::Tab));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(32.f, 48.f)), key1Quad
    , hou::key_code::Q, hou::scan_code::Q));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(48.f, 48.f)), key1Quad
    , hou::key_code::W, hou::scan_code::W));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(64.f, 48.f)), key1Quad
    , hou::key_code::E, hou::scan_code::E));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(80.f, 48.f)), key1Quad
    , hou::key_code::R, hou::scan_code::R));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(96.f, 48.f)), key1Quad
    , hou::key_code::T, hou::scan_code::T));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(112.f, 48.f)), key1Quad
    , hou::key_code::Y, hou::scan_code::Y));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(128.f, 48.f)), key1Quad
    , hou::key_code::U, hou::scan_code::U));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(144.f, 48.f)), key1Quad
    , hou::key_code::I, hou::scan_code::I));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(160.f, 48.f)), key1Quad
    , hou::key_code::O, hou::scan_code::O));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(176.f, 48.f)), key1Quad
    , hou::key_code::P, hou::scan_code::P));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(192.f, 48.f)), key1Quad
    , hou::key_code::LBracket, hou::scan_code::LBracket));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(208.f, 48.f)), key1Quad
    , hou::key_code::RBracket, hou::scan_code::RBracket));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(224.f, 48.f)), keyEnterQuad
    , hou::key_code::Enter, hou::scan_code::Enter));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 64.f)), key2Quad
    , hou::key_code::CapsLock, hou::scan_code::CapsLock));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(40.f, 64.f)), key1Quad
    , hou::key_code::A, hou::scan_code::A));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(56.f, 64.f)), key1Quad
    , hou::key_code::S, hou::scan_code::S));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(72.f, 64.f)), key1Quad
    , hou::key_code::D, hou::scan_code::D));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(88.f, 64.f)), key1Quad
    , hou::key_code::F, hou::scan_code::F));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(104.f, 64.f)), key1Quad
    , hou::key_code::G, hou::scan_code::G));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(120.f, 64.f)), key1Quad
    , hou::key_code::H, hou::scan_code::H));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(136.f, 64.f)), key1Quad
    , hou::key_code::J, hou::scan_code::J));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(152.f, 64.f)), key1Quad
    , hou::key_code::K, hou::scan_code::K));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(168.f, 64.f)), key1Quad
    , hou::key_code::L, hou::scan_code::L));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(184.f, 64.f)), key1Quad
    , hou::key_code::Semicolon, hou::scan_code::Semicolon));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(200.f, 64.f)), key1Quad
    , hou::key_code::Quote, hou::scan_code::Quote));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(216.f, 64.f)), key1Quad
    , hou::key_code::Backslash, hou::scan_code::Backslash));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 80.f)), key2hQuad
    , hou::key_code::LShift, hou::scan_code::LShift));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(48.f, 80.f)), key1Quad
    , hou::key_code::Z, hou::scan_code::Z));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(64.f, 80.f)), key1Quad
    , hou::key_code::X, hou::scan_code::X));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(80.f, 80.f)), key1Quad
    , hou::key_code::C, hou::scan_code::C));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(96.f, 80.f)), key1Quad
    , hou::key_code::V, hou::scan_code::V));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(112.f, 80.f)), key1Quad
    , hou::key_code::B, hou::scan_code::B));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(128.f, 80.f)), key1Quad
    , hou::key_code::N, hou::scan_code::N));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(144.f, 80.f)), key1Quad
    , hou::key_code::M, hou::scan_code::M));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(160.f, 80.f)), key1Quad
    , hou::key_code::Comma, hou::scan_code::Comma));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(176.f, 80.f)), key1Quad
    , hou::key_code::Period, hou::scan_code::Period));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(192.f, 80.f)), key1Quad
    , hou::key_code::Slash, hou::scan_code::Slash));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(208.f, 80.f)), key2hQuad
    , hou::key_code::RShift, hou::scan_code::RShift));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 96.f)), key1hQuad
    , hou::key_code::LCtrl, hou::scan_code::LCtrl));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(32.f, 96.f)), key1hQuad
    , hou::key_code::LSystem, hou::scan_code::LSystem));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(56.f, 96.f)), key1hQuad
    , hou::key_code::LAlt, hou::scan_code::LAlt));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(80.f, 96.f)), key4hQuad
    , hou::key_code::Space, hou::scan_code::Space));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(152.f, 96.f)), key1hQuad
    , hou::key_code::RAlt, hou::scan_code::RAlt));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(176.f, 96.f)), key1hQuad
    , hou::key_code::RSystem, hou::scan_code::RSystem));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(200.f, 96.f)), key1hQuad
    , hou::key_code::Apps, hou::scan_code::Apps));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(224.f, 96.f)), key1hQuad
    , hou::key_code::RCtrl, hou::scan_code::RCtrl));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 32.f)), key1Quad
    , hou::key_code::NumLock, hou::scan_code::NumLock));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(328.f, 32.f)), key1Quad
    , hou::key_code::Divide, hou::scan_code::Divide));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 32.f)), key1Quad
    , hou::key_code::Multiply, hou::scan_code::Multiply));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(360.f, 32.f)), key1Quad
    , hou::key_code::Subtract, hou::scan_code::Subtract));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 48.f)), key1Quad
    , hou::key_code::Numpad7, hou::scan_code::Numpad7));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(328.f, 48.f)), key1Quad
    , hou::key_code::Numpad8, hou::scan_code::Numpad8));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 48.f)), key1Quad
    , hou::key_code::Numpad9, hou::scan_code::Numpad9));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(360.f, 48.f)), keyVertQuad
    , hou::key_code::Add, hou::scan_code::Add));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 64.f)), key1Quad
    , hou::key_code::Numpad4, hou::scan_code::Numpad4));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(328.f, 64.f)), key1Quad
    , hou::key_code::Numpad5, hou::scan_code::Numpad5));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 64.f)), key1Quad
    , hou::key_code::Numpad6, hou::scan_code::Numpad6));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 80.f)), key1Quad
    , hou::key_code::Numpad1, hou::scan_code::Numpad1));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(328.f, 80.f)), key1Quad
    , hou::key_code::Numpad2, hou::scan_code::Numpad2));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 80.f)), key1Quad
    , hou::key_code::Numpad3, hou::scan_code::Numpad3));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(360.f, 80.f)), keyVertQuad
    , hou::key_code::Enter, hou::scan_code::Enter));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 96.f)), key2Quad
    , hou::key_code::Numpad0, hou::scan_code::Numpad0));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 96.f)), key1Quad
    , hou::key_code::Decimal, hou::scan_code::Decimal));

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
          if(hou::checkBit(data.modifier_keys, hou::modifier_keys::ctrl))
          {
            if(data.scan_code == hou::scan_code::Num1)
            {
              wnd.set_icon(iconR);
            }
            else if(data.scan_code == hou::scan_code::Num2)
            {
              wnd.set_icon(iconRG);
            }
            else if(data.scan_code == hou::scan_code::Num3)
            {
              wnd.set_icon(iconRGB);
            }
            else if(data.scan_code == hou::scan_code::Num4)
            {
              wnd.set_icon(iconRGBA);
            }
            else if(data.scan_code == hou::scan_code::Num5)
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
        case hou::window_event_type::TextEntered:
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
      textRnd.draw(wnd, "KEYBOARD KEY CODE", font, hou::color::red
        , projTrans * keyboard1TextTrans);
      meshRnd.draw(wnd, keyboardQuad, keyboardTex, hou::color::white
        , projTrans * keyboard1Trans);
      textRnd.draw(wnd, "KEYBOARD SCAN CODE", font, hou::color::yellow
        , projTrans * keyboard2TextTrans);
      meshRnd.draw(wnd, keyboardQuad, keyboardTex, hou::color::white
        , projTrans * keyboard2Trans);
      meshRnd.draw(wnd, mouseQuad, mouseTex, hou::color::white
        , projTrans * mouseTrans);
      std::string mousePosText = hou::format_string("SCREEN MOUSE CURSOR POSITION: (%d, %d)"
        , hou::mouse::get_position().x(), hou::mouse::get_position().y());
      textRnd.draw(wnd, mousePosText, font, hou::color::green
        , projTrans * mousePosTextTrans);
      std::string mouseRelPosText = hou::format_string("WINDOW MOUSE CURSOR POSITION: (%d, %d)"
        , hou::mouse::get_position(wnd).x(), hou::mouse::get_position(wnd).y());
      textRnd.draw(wnd, mouseRelPosText, font, hou::color::green
        , projTrans * mouseRelPosTextTrans);
      textRnd.draw(wnd
        , "PRESS CTRL+O TO MOVE THE MOUSE CURSOR TO THE SCREEN ORIGIN", font
        , hou::color::green, projTrans * mouseHintText1Trans);
      textRnd.draw(wnd
        , "PRESS CTRL+P TO MOVE THE MOUSE CURSOR TO THE WINDOW ORIGIN", font
        , hou::color::green, projTrans * mouseHintText2Trans);

      // Draw events in queue.
      hou::trans2f evTrans;
      for(const auto& ev : eventQueue)
      {
        meshRnd.draw(wnd, eventRect, hou::color::green, projTrans * eventQueueTrans * evTrans);
        std::stringstream ss;
        ss << ev;
        if(ev.get_type() == hou::window_event_type::TextEntered)
        {
          ss << "  " <<  hou::convertEncoding<hou::utf32, hou::utf8>(std::u32string(1, ev.get_text_data().code_point)) << "\n";
        }
        textRnd.draw(wnd, ss.str(), font, hou::color::black
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
        , hou::keyboard::is_key_toggled(hou::key_code::NumLock)
        ? hou::color::red : hou::color::black
        , projTrans * keyboard1Trans * hou::trans2f::translation(hou::vec2f(312.f, 8.f)));
      meshRnd.draw(wnd
        , keyboardLed
        , hou::keyboard::is_key_toggled(hou::key_code::CapsLock)
        ? hou::color::red : hou::color::black
        , projTrans * keyboard1Trans * hou::trans2f::translation(hou::vec2f(328.f, 8.f)));
      meshRnd.draw(wnd
        , keyboardLed
        , hou::keyboard::is_key_toggled(hou::key_code::ScrollLock)
        ? hou::color::red : hou::color::black
        , projTrans * keyboard1Trans * hou::trans2f::translation(hou::vec2f(344.f, 8.f)));

      meshRnd.draw(wnd
        , keyboardLed
        , hou::keyboard::is_key_toggled(hou::scan_code::NumLock)
        ? hou::color::yellow : hou::color::black
        , projTrans * keyboard2Trans * hou::trans2f::translation(hou::vec2f(312.f, 8.f)));
      meshRnd.draw(wnd
        , keyboardLed
        , hou::keyboard::is_key_toggled(hou::scan_code::CapsLock)
        ? hou::color::yellow : hou::color::black
        , projTrans * keyboard2Trans * hou::trans2f::translation(hou::vec2f(328.f, 8.f)));
      meshRnd.draw(wnd
        , keyboardLed
        , hou::keyboard::is_key_toggled(hou::scan_code::ScrollLock)
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

      if(hou::keyboard::is_key_pressed(hou::key_code::LCtrl)
        && hou::keyboard::is_key_pressed(hou::key_code::O))
      {
        hou::mouse::set_position(hou::vec2i(0, 0));
      }
      else if(hou::keyboard::is_key_pressed(hou::key_code::LCtrl)
        && hou::keyboard::is_key_pressed(hou::key_code::P))
      {
        hou::mouse::set_position(hou::vec2i(0, 0), wnd);
      }

      wnd.display();
    }
  }
}
