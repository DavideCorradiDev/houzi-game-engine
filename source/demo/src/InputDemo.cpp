#include "hou/cor/basic_types.hpp"

#include "hou/mth/transform2.hpp"

#include "hou/gfx/Mesh.hpp"
#include "hou/sys/Color.hpp"
#include "hou/gfx/Font.hpp"
#include "hou/gfx/Vertex2.hpp"
#include "hou/gfx/GraphicContext.hpp"
#include "hou/gfx/RenderWindow.hpp"
#include "hou/gfx/Texture.hpp"
#include "hou/gfx/Mesh2ShaderProgram.hpp"
#include "hou/gfx/TextShaderProgram.hpp"

#include "hou/cor/clock.hpp"
#include "hou/sys/BinaryFileIn.hpp"
#include "hou/sys/Image.hpp"
#include "hou/sys/Keyboard.hpp"
#include "hou/sys/Mouse.hpp"
#include "hou/sys/WindowEvent.hpp"

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
    , hou::KeyCode key, hou::ScanCode sc);

  const hou::trans2f& getTrans() const;
  const hou::Mesh2& getQuad() const;
  hou::KeyCode getKey() const;
  hou::ScanCode getScanCode() const;

private:
  hou::trans2f mTrans;
  const hou::Mesh2* mQuad;
  hou::KeyCode mKey;
  hou::ScanCode mScanCode;
};



KeyInfo::KeyInfo(const hou::trans2f& trans, const hou::Mesh2& quad
    , hou::KeyCode key, hou::ScanCode sc)
  : mTrans(trans)
  , mQuad(&quad)
  , mKey(key)
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



hou::KeyCode KeyInfo::getKey() const
{
  return mKey;
}



hou::ScanCode KeyInfo::getScanCode() const
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
    hou::WindowStyle::WindowedResizable);
  wnd.setVisible(true);
  wnd.setKeyRepeatEnabled(false);
  wnd.setMouseCursorGrabbed(false);
  hou::Mesh2ShaderProgram meshRnd;
  hou::TextShaderProgram textRnd;

  std::string iconFilename = dataDir + u8"monkey.png";
  hou::Image2RGBA iconRGBA = hou::pngReadFile<hou::PixelFormat::RGBA>(iconFilename);
  hou::Image2RGB iconRGB = hou::pngReadFile<hou::PixelFormat::RGB>(iconFilename);
  hou::Image2RG iconRG = hou::pngReadFile<hou::PixelFormat::RG>(iconFilename);
  hou::Image2R iconR = hou::pngReadFile<hou::PixelFormat::R>(iconFilename);

  hou::Texture2 keyboardTex(hou::pngReadFile<hou::PixelFormat::RGBA>(dataDir + u8"keyboard.png"));
  hou::Texture2 keyboardKeysTex(hou::pngReadFile<hou::PixelFormat::RGBA>(dataDir + u8"keyboardkeys.png"));
  hou::Texture2 mouseTex(hou::pngReadFile<hou::PixelFormat::RGBA>(dataDir + u8"mouse.png"));
  hou::Texture2 mousebuttonsTex(hou::pngReadFile<hou::PixelFormat::RGBA>(dataDir + u8"mousebuttons.png"));

  hou::Font font(std::make_unique<hou::BinaryFileIn>(dataDir + u8"NotoMono-Regular.ttf"));

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

  std::list<hou::WindowEvent> eventQueue;

  // Initialization of key information
  std::vector<KeyInfo> keyMap;

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(16.f, 8.f)), key1Quad
    , hou::KeyCode::Escape, hou::ScanCode::Escape));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(40.f, 8.f)), key1Quad
    , hou::KeyCode::F1, hou::ScanCode::F1));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(56.f, 8.f)), key1Quad
    , hou::KeyCode::F2, hou::ScanCode::F2));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(72.f, 8.f)), key1Quad
    , hou::KeyCode::F3, hou::ScanCode::F3));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(88.f, 8.f)), key1Quad
    , hou::KeyCode::F4, hou::ScanCode::F4));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(112.f, 8.f)), key1Quad
    , hou::KeyCode::F5, hou::ScanCode::F5));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(128.f, 8.f)), key1Quad
    , hou::KeyCode::F6, hou::ScanCode::F6));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(144.f, 8.f)), key1Quad
    , hou::KeyCode::F7, hou::ScanCode::F7));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(160.f, 8.f)), key1Quad
    , hou::KeyCode::F8, hou::ScanCode::F8));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(184.f, 8.f)), key1Quad
    , hou::KeyCode::F9, hou::ScanCode::F9));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(200.f, 8.f)), key1Quad
    , hou::KeyCode::F10, hou::ScanCode::F10));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(216.f, 8.f)), key1Quad
    , hou::KeyCode::F11, hou::ScanCode::F11));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(232.f, 8.f)), key1Quad
    , hou::KeyCode::F12, hou::ScanCode::F12));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(256.f, 8.f)), key1Quad
    , hou::KeyCode::PrintScreen, hou::ScanCode::PrintScreen));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 8.f)), key1Quad
    , hou::KeyCode::ScrollLock, hou::ScanCode::ScrollLock));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(288.f, 8.f)), key1Quad
    , hou::KeyCode::Pause, hou::ScanCode::Pause));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(256.f, 32.f)), key1Quad
    , hou::KeyCode::Insert, hou::ScanCode::Insert));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 32.f)), key1Quad
    , hou::KeyCode::Home, hou::ScanCode::Home));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(288.f, 32.f)), key1Quad
    , hou::KeyCode::PageUp, hou::ScanCode::PageUp));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(256.f, 48.f)), key1Quad
    , hou::KeyCode::Delete, hou::ScanCode::Delete));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 48.f)), key1Quad
    , hou::KeyCode::End, hou::ScanCode::End));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(288.f, 48.f)), key1Quad
    , hou::KeyCode::PageDown, hou::ScanCode::PageDown));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 80.f)), key1Quad
    , hou::KeyCode::Up, hou::ScanCode::Up));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(256.f, 96.f)), key1Quad
    , hou::KeyCode::Left, hou::ScanCode::Left));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(272.f, 96.f)), key1Quad
    , hou::KeyCode::Down, hou::ScanCode::Down));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(288.f, 96.f)), key1Quad
    , hou::KeyCode::Right, hou::ScanCode::Right));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 32.f)), key1Quad
    , hou::KeyCode::Tilde, hou::ScanCode::Tilde));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(24.f, 32.f)), key1Quad
    , hou::KeyCode::Num1, hou::ScanCode::Num1));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(40.f, 32.f)), key1Quad
    , hou::KeyCode::Num2, hou::ScanCode::Num2));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(56.f, 32.f)), key1Quad
    , hou::KeyCode::Num3, hou::ScanCode::Num3));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(72.f, 32.f)), key1Quad
    , hou::KeyCode::Num4, hou::ScanCode::Num4));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(88.f, 32.f)), key1Quad
    , hou::KeyCode::Num5, hou::ScanCode::Num5));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(104.f, 32.f)), key1Quad
    , hou::KeyCode::Num6, hou::ScanCode::Num6));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(120.f, 32.f)), key1Quad
    , hou::KeyCode::Num7, hou::ScanCode::Num7));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(136.f, 32.f)), key1Quad
    , hou::KeyCode::Num8, hou::ScanCode::Num8));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(152.f, 32.f)), key1Quad
    , hou::KeyCode::Num9, hou::ScanCode::Num9));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(168.f, 32.f)), key1Quad
    , hou::KeyCode::Num0, hou::ScanCode::Num0));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(184.f, 32.f)), key1Quad
    , hou::KeyCode::Dash, hou::ScanCode::Dash));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(200.f, 32.f)), key1Quad
    , hou::KeyCode::Equal, hou::ScanCode::Equal));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(216.f, 32.f)), key2Quad
    , hou::KeyCode::Backspace, hou::ScanCode::Backspace));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 48.f)), key1hQuad
    , hou::KeyCode::Tab, hou::ScanCode::Tab));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(32.f, 48.f)), key1Quad
    , hou::KeyCode::Q, hou::ScanCode::Q));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(48.f, 48.f)), key1Quad
    , hou::KeyCode::W, hou::ScanCode::W));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(64.f, 48.f)), key1Quad
    , hou::KeyCode::E, hou::ScanCode::E));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(80.f, 48.f)), key1Quad
    , hou::KeyCode::R, hou::ScanCode::R));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(96.f, 48.f)), key1Quad
    , hou::KeyCode::T, hou::ScanCode::T));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(112.f, 48.f)), key1Quad
    , hou::KeyCode::Y, hou::ScanCode::Y));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(128.f, 48.f)), key1Quad
    , hou::KeyCode::U, hou::ScanCode::U));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(144.f, 48.f)), key1Quad
    , hou::KeyCode::I, hou::ScanCode::I));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(160.f, 48.f)), key1Quad
    , hou::KeyCode::O, hou::ScanCode::O));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(176.f, 48.f)), key1Quad
    , hou::KeyCode::P, hou::ScanCode::P));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(192.f, 48.f)), key1Quad
    , hou::KeyCode::LBracket, hou::ScanCode::LBracket));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(208.f, 48.f)), key1Quad
    , hou::KeyCode::RBracket, hou::ScanCode::RBracket));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(224.f, 48.f)), keyEnterQuad
    , hou::KeyCode::Enter, hou::ScanCode::Enter));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 64.f)), key2Quad
    , hou::KeyCode::CapsLock, hou::ScanCode::CapsLock));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(40.f, 64.f)), key1Quad
    , hou::KeyCode::A, hou::ScanCode::A));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(56.f, 64.f)), key1Quad
    , hou::KeyCode::S, hou::ScanCode::S));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(72.f, 64.f)), key1Quad
    , hou::KeyCode::D, hou::ScanCode::D));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(88.f, 64.f)), key1Quad
    , hou::KeyCode::F, hou::ScanCode::F));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(104.f, 64.f)), key1Quad
    , hou::KeyCode::G, hou::ScanCode::G));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(120.f, 64.f)), key1Quad
    , hou::KeyCode::H, hou::ScanCode::H));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(136.f, 64.f)), key1Quad
    , hou::KeyCode::J, hou::ScanCode::J));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(152.f, 64.f)), key1Quad
    , hou::KeyCode::K, hou::ScanCode::K));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(168.f, 64.f)), key1Quad
    , hou::KeyCode::L, hou::ScanCode::L));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(184.f, 64.f)), key1Quad
    , hou::KeyCode::Semicolon, hou::ScanCode::Semicolon));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(200.f, 64.f)), key1Quad
    , hou::KeyCode::Quote, hou::ScanCode::Quote));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(216.f, 64.f)), key1Quad
    , hou::KeyCode::Backslash, hou::ScanCode::Backslash));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 80.f)), key2hQuad
    , hou::KeyCode::LShift, hou::ScanCode::LShift));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(48.f, 80.f)), key1Quad
    , hou::KeyCode::Z, hou::ScanCode::Z));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(64.f, 80.f)), key1Quad
    , hou::KeyCode::X, hou::ScanCode::X));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(80.f, 80.f)), key1Quad
    , hou::KeyCode::C, hou::ScanCode::C));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(96.f, 80.f)), key1Quad
    , hou::KeyCode::V, hou::ScanCode::V));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(112.f, 80.f)), key1Quad
    , hou::KeyCode::B, hou::ScanCode::B));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(128.f, 80.f)), key1Quad
    , hou::KeyCode::N, hou::ScanCode::N));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(144.f, 80.f)), key1Quad
    , hou::KeyCode::M, hou::ScanCode::M));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(160.f, 80.f)), key1Quad
    , hou::KeyCode::Comma, hou::ScanCode::Comma));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(176.f, 80.f)), key1Quad
    , hou::KeyCode::Period, hou::ScanCode::Period));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(192.f, 80.f)), key1Quad
    , hou::KeyCode::Slash, hou::ScanCode::Slash));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(208.f, 80.f)), key2hQuad
    , hou::KeyCode::RShift, hou::ScanCode::RShift));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(8.f, 96.f)), key1hQuad
    , hou::KeyCode::LCtrl, hou::ScanCode::LCtrl));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(32.f, 96.f)), key1hQuad
    , hou::KeyCode::LSystem, hou::ScanCode::LSystem));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(56.f, 96.f)), key1hQuad
    , hou::KeyCode::LAlt, hou::ScanCode::LAlt));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(80.f, 96.f)), key4hQuad
    , hou::KeyCode::Space, hou::ScanCode::Space));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(152.f, 96.f)), key1hQuad
    , hou::KeyCode::RAlt, hou::ScanCode::RAlt));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(176.f, 96.f)), key1hQuad
    , hou::KeyCode::RSystem, hou::ScanCode::RSystem));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(200.f, 96.f)), key1hQuad
    , hou::KeyCode::Apps, hou::ScanCode::Apps));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(224.f, 96.f)), key1hQuad
    , hou::KeyCode::RCtrl, hou::ScanCode::RCtrl));

  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 32.f)), key1Quad
    , hou::KeyCode::NumLock, hou::ScanCode::NumLock));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(328.f, 32.f)), key1Quad
    , hou::KeyCode::Divide, hou::ScanCode::Divide));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 32.f)), key1Quad
    , hou::KeyCode::Multiply, hou::ScanCode::Multiply));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(360.f, 32.f)), key1Quad
    , hou::KeyCode::Subtract, hou::ScanCode::Subtract));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 48.f)), key1Quad
    , hou::KeyCode::Numpad7, hou::ScanCode::Numpad7));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(328.f, 48.f)), key1Quad
    , hou::KeyCode::Numpad8, hou::ScanCode::Numpad8));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 48.f)), key1Quad
    , hou::KeyCode::Numpad9, hou::ScanCode::Numpad9));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(360.f, 48.f)), keyVertQuad
    , hou::KeyCode::Add, hou::ScanCode::Add));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 64.f)), key1Quad
    , hou::KeyCode::Numpad4, hou::ScanCode::Numpad4));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(328.f, 64.f)), key1Quad
    , hou::KeyCode::Numpad5, hou::ScanCode::Numpad5));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 64.f)), key1Quad
    , hou::KeyCode::Numpad6, hou::ScanCode::Numpad6));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 80.f)), key1Quad
    , hou::KeyCode::Numpad1, hou::ScanCode::Numpad1));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(328.f, 80.f)), key1Quad
    , hou::KeyCode::Numpad2, hou::ScanCode::Numpad2));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 80.f)), key1Quad
    , hou::KeyCode::Numpad3, hou::ScanCode::Numpad3));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(360.f, 80.f)), keyVertQuad
    , hou::KeyCode::Enter, hou::ScanCode::Enter));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(312.f, 96.f)), key2Quad
    , hou::KeyCode::Numpad0, hou::ScanCode::Numpad0));
  keyMap.push_back(KeyInfo(hou::trans2f::translation(hou::vec2f(344.f, 96.f)), key1Quad
    , hou::KeyCode::Decimal, hou::ScanCode::Decimal));

  // Main loop.
  bool running = true;
  std::chrono::nanoseconds lastUpdateTime(frameTime);
  hou::clock p_clock;
  while(running)
  {
    // Process event queue.
    wnd.updateEventQueue();
    while(!wnd.isEventQueueEmpty())
    {
      hou::WindowEvent we = wnd.popEvent();
      switch(we.getType())
      {
        case hou::WindowEventType::Closed:
        {
          running = false;
          break;
        }
        case hou::WindowEventType::KeyPressed:
        {
          auto data = we.getKeyData();
          if(hou::checkBit(data.modifierKeys, hou::ModifierKeys::Ctrl))
          {
            if(data.scanCode == hou::ScanCode::Num1)
            {
              wnd.setIcon(iconR);
            }
            else if(data.scanCode == hou::ScanCode::Num2)
            {
              wnd.setIcon(iconRG);
            }
            else if(data.scanCode == hou::ScanCode::Num3)
            {
              wnd.setIcon(iconRGB);
            }
            else if(data.scanCode == hou::ScanCode::Num4)
            {
              wnd.setIcon(iconRGBA);
            }
            else if(data.scanCode == hou::ScanCode::Num5)
            {
              wnd.setSystemIcon();
            }
          }
          break;
        }
        case hou::WindowEventType::FocusGained:
        case hou::WindowEventType::FocusLost:
        case hou::WindowEventType::Resized:
        case hou::WindowEventType::KeyReleased:
        case hou::WindowEventType::TextEntered:
        case hou::WindowEventType::MouseMoved:
        case hou::WindowEventType::MouseEntered:
        case hou::WindowEventType::MouseLeft:
        case hou::WindowEventType::MouseButtonPressed:
        case hou::WindowEventType::MouseButtonReleased:
        case hou::WindowEventType::MouseWheelMoved:
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
      wnd.clear(hou::Color::Black);
      textRnd.draw(wnd, "KEYBOARD KEY CODE", font, hou::Color::Red
        , projTrans * keyboard1TextTrans);
      meshRnd.draw(wnd, keyboardQuad, keyboardTex, hou::Color::White
        , projTrans * keyboard1Trans);
      textRnd.draw(wnd, "KEYBOARD SCAN CODE", font, hou::Color::Yellow
        , projTrans * keyboard2TextTrans);
      meshRnd.draw(wnd, keyboardQuad, keyboardTex, hou::Color::White
        , projTrans * keyboard2Trans);
      meshRnd.draw(wnd, mouseQuad, mouseTex, hou::Color::White
        , projTrans * mouseTrans);
      std::string mousePosText = hou::format_string("SCREEN MOUSE CURSOR POSITION: (%d, %d)"
        , hou::Mouse::get_position().x(), hou::Mouse::get_position().y());
      textRnd.draw(wnd, mousePosText, font, hou::Color::Green
        , projTrans * mousePosTextTrans);
      std::string mouseRelPosText = hou::format_string("WINDOW MOUSE CURSOR POSITION: (%d, %d)"
        , hou::Mouse::get_position(wnd).x(), hou::Mouse::get_position(wnd).y());
      textRnd.draw(wnd, mouseRelPosText, font, hou::Color::Green
        , projTrans * mouseRelPosTextTrans);
      textRnd.draw(wnd
        , "PRESS CTRL+O TO MOVE THE MOUSE CURSOR TO THE SCREEN ORIGIN", font
        , hou::Color::Green, projTrans * mouseHintText1Trans);
      textRnd.draw(wnd
        , "PRESS CTRL+P TO MOVE THE MOUSE CURSOR TO THE WINDOW ORIGIN", font
        , hou::Color::Green, projTrans * mouseHintText2Trans);

      // Draw events in queue.
      hou::trans2f evTrans;
      for(const auto& ev : eventQueue)
      {
        meshRnd.draw(wnd, eventRect, hou::Color::Green, projTrans * eventQueueTrans * evTrans);
        std::stringstream ss;
        ss << ev;
        if(ev.getType() == hou::WindowEventType::TextEntered)
        {
          ss << "  " <<  hou::convertEncoding<hou::utf32, hou::utf8>(std::u32string(1, ev.getTextData().codePoint)) << "\n";
        }
        textRnd.draw(wnd, ss.str(), font, hou::Color::Black
          , projTrans * eventQueueTrans * evTrans * hou::trans2f::translation(hou::vec2f(4.f, 16.f)));
        evTrans *= hou::trans2f::translation(hou::vec2f(evSize.x(), 0.f));
      }

      // Draw pressed keys
      for(const auto& info : keyMap)
      {
        if(hou::Keyboard::isKeyPressed(info.getKey()))
        {
          meshRnd.draw(wnd
            , info.getQuad()
            , keyboardKeysTex
            , hou::Color::Red
            , projTrans * keyboard1Trans * info.getTrans());
        }
        if(hou::Keyboard::isKeyPressed(info.getScanCode()))
        {
          meshRnd.draw(wnd
            , info.getQuad()
            , keyboardKeysTex
            , hou::Color::Yellow
            , projTrans * keyboard2Trans * info.getTrans());
        }
      }

      // Draw keyboard LEDs
      meshRnd.draw(wnd
        , keyboardLed
        , hou::Keyboard::isKeyToggled(hou::KeyCode::NumLock)
        ? hou::Color::Red : hou::Color::Black
        , projTrans * keyboard1Trans * hou::trans2f::translation(hou::vec2f(312.f, 8.f)));
      meshRnd.draw(wnd
        , keyboardLed
        , hou::Keyboard::isKeyToggled(hou::KeyCode::CapsLock)
        ? hou::Color::Red : hou::Color::Black
        , projTrans * keyboard1Trans * hou::trans2f::translation(hou::vec2f(328.f, 8.f)));
      meshRnd.draw(wnd
        , keyboardLed
        , hou::Keyboard::isKeyToggled(hou::KeyCode::ScrollLock)
        ? hou::Color::Red : hou::Color::Black
        , projTrans * keyboard1Trans * hou::trans2f::translation(hou::vec2f(344.f, 8.f)));

      meshRnd.draw(wnd
        , keyboardLed
        , hou::Keyboard::isKeyToggled(hou::ScanCode::NumLock)
        ? hou::Color::Yellow : hou::Color::Black
        , projTrans * keyboard2Trans * hou::trans2f::translation(hou::vec2f(312.f, 8.f)));
      meshRnd.draw(wnd
        , keyboardLed
        , hou::Keyboard::isKeyToggled(hou::ScanCode::CapsLock)
        ? hou::Color::Yellow : hou::Color::Black
        , projTrans * keyboard2Trans * hou::trans2f::translation(hou::vec2f(328.f, 8.f)));
      meshRnd.draw(wnd
        , keyboardLed
        , hou::Keyboard::isKeyToggled(hou::ScanCode::ScrollLock)
        ? hou::Color::Yellow : hou::Color::Black
        , projTrans * keyboard2Trans * hou::trans2f::translation(hou::vec2f(344.f, 8.f)));

      // Draw mouse buttons.
      if(hou::Mouse::isButtonPressed(hou::MouseButton::LB))
      {
        meshRnd.draw(wnd
          , mouseBtnQuad
          , mousebuttonsTex
          , hou::Color::Green
          , projTrans * mouseTrans * hou::trans2f::translation(hou::vec2f(11.f, 7.f)));
      }
      if(hou::Mouse::isButtonPressed(hou::MouseButton::RB))
      {
        meshRnd.draw(wnd
          , mouseBtnQuad
          , mousebuttonsTex
          , hou::Color::Green
          , projTrans * mouseTrans * hou::trans2f::translation(hou::vec2f(37.f, 7.f)));
      }
      if(hou::Mouse::isButtonPressed(hou::MouseButton::MB))
      {
        meshRnd.draw(wnd
          , mouseWheelQuad
          , mousebuttonsTex
          , hou::Color::Green
          , projTrans * mouseTrans * hou::trans2f::translation(hou::vec2f(29.f, 13.f)));
      }
      if(hou::Mouse::isButtonPressed(hou::MouseButton::XB1))
      {
        meshRnd.draw(wnd
          , mouseBtnXQuad
          , mousebuttonsTex
          , hou::Color::Green
          , projTrans * mouseTrans * hou::trans2f::translation(hou::vec2f(5.f, 32.f)));
      }
      if(hou::Mouse::isButtonPressed(hou::MouseButton::XB2))
      {
        meshRnd.draw(wnd
          , mouseBtnXQuad
          , mousebuttonsTex
          , hou::Color::Green
          , projTrans * mouseTrans * hou::trans2f::translation(hou::vec2f(54.f, 32.f)));
      }

      if(hou::Keyboard::isKeyPressed(hou::KeyCode::LCtrl)
        && hou::Keyboard::isKeyPressed(hou::KeyCode::O))
      {
        hou::Mouse::set_position(hou::vec2i(0, 0));
      }
      else if(hou::Keyboard::isKeyPressed(hou::KeyCode::LCtrl)
        && hou::Keyboard::isKeyPressed(hou::KeyCode::P))
      {
        hou::Mouse::set_position(hou::vec2i(0, 0), wnd);
      }

      wnd.display();
    }
  }
}
