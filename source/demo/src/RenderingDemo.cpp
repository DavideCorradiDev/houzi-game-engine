#include "hou/gfx/Vertex2.hpp"
#include "hou/gfx/GraphicContext.hpp"
#include "hou/gfx/RenderWindow.hpp"
#include "hou/gfx/TextureChannelMapping.hpp"
#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/Mesh2ShaderProgram.hpp"
#include "hou/gfx/TextShaderProgram.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/rotation2.hpp"
#include "hou/mth/transform2.hpp"

#include "hou/sys/Color.hpp"
#include "hou/cor/clock.hpp"
#include "hou/sys/Keyboard.hpp"
#include "hou/sys/WindowEvent.hpp"
#include "hou/sys/WindowStyle.hpp"

using namespace hou;



class TransformData
{
public:
  TransformData();

  trans2f computeTransform() const;

public:
  vec2f m_position;
  vec2f mScale;
  vec2f mShear;
  float mRotation;
};



TransformData::TransformData()
  : m_position(0.f, 0.f)
  , mScale(1.f, 1.f)
  , mShear(0.f, 0.f)
  , mRotation(0.f)
{}



trans2f TransformData::computeTransform() const
{
  return trans2f::translation(m_position)
    *trans2f::rotation(rot2f(deg_to_rad(mRotation)))
    * trans2f::scale(mScale)
    * trans2f::shear(mShear.x(), mShear.y());
}



class DrawableShape
  : public non_copyable
{
public:
  DrawableShape(const Texture2& texture);

  virtual Mesh2 generateMesh() const = 0;
  void draw(RenderSurface& rt, Mesh2ShaderProgram& renderer, const trans2f& t) const;

  void handleInput();

public:
  Color mColor;
  TransformData mTransformData;
  vec2f mOrigin;
  vec2f m_size;
  float mThickness;
  float mPoints;
  bool mDrawWithTexture;
  const Texture2* mTexture;
};




DrawableShape::DrawableShape(const Texture2& texture)
  : non_copyable()
  , mColor(Color::White)
  , mTransformData()
  , mOrigin(0.f, 0.f)
  , m_size(32.f, 32.f)
  , mThickness(1.f)
  , mPoints(16)
  , mDrawWithTexture(false)
  , mTexture(&texture)
{}



void DrawableShape::draw(RenderSurface& rt, Mesh2ShaderProgram& renderer, const trans2f& t) const
{
  if(mDrawWithTexture)
  {
    renderer.draw(rt, generateMesh(), *mTexture, mColor, t * mTransformData.computeTransform());
  }
  else
  {
    renderer.draw(rt, generateMesh(), mColor, t * mTransformData.computeTransform());
  }
}



void DrawableShape::handleInput()
{
  static const float deltaPos = 4.f;
  static const float deltaRot = 4.f;
  static const float deltaScale = 0.1f;
  static const float deltaShear = 0.1f;
  static const uint deltaCol = 4u;
  static const float deltaThickness = 1.f;
  static const uint deltaPoints = 4u;
  static const uint minPoints = 2u;

  if(Keyboard::isKeyPressed(ScanCode::A))
  {
    mTransformData.m_position.x() += deltaPos;
  }
  if(Keyboard::isKeyPressed(ScanCode::Z))
  {
    mTransformData.m_position.x() -= deltaPos;
  }
  if(Keyboard::isKeyPressed(ScanCode::S))
  {
    mTransformData.m_position.y() += deltaPos;
  }
  if(Keyboard::isKeyPressed(ScanCode::X))
  {
    mTransformData.m_position.y() -= deltaPos;
  }

  if(Keyboard::isKeyPressed(ScanCode::D))
  {
    mTransformData.mRotation += deltaRot;
  }
  if(Keyboard::isKeyPressed(ScanCode::C))
  {
    mTransformData.mRotation -= deltaRot;
  }

  if(Keyboard::isKeyPressed(ScanCode::F))
  {
    mTransformData.mScale.x() += deltaScale;
  }
  if(Keyboard::isKeyPressed(ScanCode::V))
  {
    mTransformData.mScale.x() -= deltaScale;
  }
  if(Keyboard::isKeyPressed(ScanCode::G))
  {
    mTransformData.mScale.y() += deltaScale;
  }
  if(Keyboard::isKeyPressed(ScanCode::B))
  {
    mTransformData.mScale.y() -= deltaScale;
  }

  if(Keyboard::isKeyPressed(ScanCode::H))
  {
    mTransformData.mShear.x() += deltaShear;
  }
  if(Keyboard::isKeyPressed(ScanCode::N))
  {
    mTransformData.mShear.x() -= deltaShear;
  }
  if(Keyboard::isKeyPressed(ScanCode::J))
  {
    mTransformData.mShear.y() += deltaShear;
  }
  if(Keyboard::isKeyPressed(ScanCode::M))
  {
    mTransformData.mShear.y() -= deltaShear;
  }

  if(Keyboard::isKeyPressed(ScanCode::Num1))
  {
    mColor.setRed(mColor.getRed() + deltaCol);
  }
  if(Keyboard::isKeyPressed(ScanCode::Q))
  {
    mColor.setRed(mColor.getRed() - deltaCol);
  }
  if(Keyboard::isKeyPressed(ScanCode::Num2))
  {
    mColor.setGreen(mColor.getGreen() + deltaCol);
  }
  if(Keyboard::isKeyPressed(ScanCode::W))
  {
    mColor.setGreen(mColor.getGreen() - deltaCol);
  }
  if(Keyboard::isKeyPressed(ScanCode::Num3))
  {
    mColor.setBlue(mColor.getBlue() + deltaCol);
  }
  if(Keyboard::isKeyPressed(ScanCode::E))
  {
    mColor.setBlue(mColor.getBlue() - deltaCol);
  }
  if(Keyboard::isKeyPressed(ScanCode::Num4))
  {
    mColor.setAlpha(mColor.getAlpha() + deltaCol);
  }
  if(Keyboard::isKeyPressed(ScanCode::R))
  {
    mColor.setAlpha(mColor.getAlpha() - deltaCol);
  }

  if(Keyboard::isKeyPressed(ScanCode::Num5))
  {
    mOrigin.x() += deltaPos;
  }
  if(Keyboard::isKeyPressed(ScanCode::T))
  {
    mOrigin.x() -= deltaPos;
  }
  if(Keyboard::isKeyPressed(ScanCode::Num6))
  {
    mOrigin.y() += deltaPos;
  }
  if(Keyboard::isKeyPressed(ScanCode::Y))
  {
    mOrigin.y() -= deltaPos;
  }

  if(Keyboard::isKeyPressed(ScanCode::Num7))
  {
    m_size.x() += deltaPos;
  }
  if(Keyboard::isKeyPressed(ScanCode::U))
  {
    m_size.x() -= deltaPos;
  }
  if(Keyboard::isKeyPressed(ScanCode::Num8))
  {
    m_size.y() += deltaPos;
  }
  if(Keyboard::isKeyPressed(ScanCode::I))
  {
    m_size.y() -= deltaPos;
  }

  if(Keyboard::isKeyPressed(ScanCode::Num9))
  {
    mThickness += deltaThickness;
  }
  if(Keyboard::isKeyPressed(ScanCode::O))
  {
    mThickness -= deltaThickness;
  }

  if(Keyboard::isKeyPressed(ScanCode::Num0))
  {
    mPoints += deltaPoints;
  }
  if(Keyboard::isKeyPressed(ScanCode::P))
  {
    mPoints -= deltaPoints;
    if(mPoints < minPoints)
    {
      mPoints = minPoints;
    }
  }

  if(Keyboard::isKeyPressed(ScanCode::K))
  {
    mDrawWithTexture = true;
  }
  if(Keyboard::isKeyPressed(ScanCode::Comma))
  {
    mDrawWithTexture = false;
  }
}



class RectangleShape
  : public DrawableShape
{
public:
  RectangleShape(const Texture2& texture)
    : DrawableShape(texture)
  {}

  Mesh2 generateMesh() const override
  {
    return createRectangleMesh2(m_size);
  }
};



class RectangleOutlineShape
  : public DrawableShape
{
public:
  RectangleOutlineShape(const Texture2& texture)
    : DrawableShape(texture)
  {}

  Mesh2 generateMesh() const override
  {
    return createRectangleOutlineMesh2(m_size, mThickness);
  }
};



class EllipseShape
  : public DrawableShape
{
public:
  EllipseShape(Texture2& texture)
    : DrawableShape(texture)
  {}

  Mesh2 generateMesh() const override
  {
    return createEllipseMesh2(m_size, mPoints);
  }
};



class EllipseOutlineShape
  : public DrawableShape
{
public:
  EllipseOutlineShape(const Texture2& texture)
    : DrawableShape(texture)
  {}

  Mesh2 generateMesh() const override
  {
    return createEllipseOutlineMesh2(m_size, mPoints, mThickness);
  }
};



class TextureQuadShape
  : public DrawableShape
{
public:
  TextureQuadShape(const Texture2& texture)
    : DrawableShape(texture)
  {}

  Mesh2 generateMesh() const override
  {
    return createTextureQuadMesh2(rectf(mOrigin, m_size), mTexture->get_size());
  }
};



int main()
{
  static const std::string dataDir = u8"source/demo/data/";
  GraphicContext ctx;
  GraphicContext::setCurrent(ctx);

  std::string wndTitle(u8"Rendering Demo");
  vec2u wndSize(800u, 600u);
  uint wndSamples = 16u;
  WindowStyle wndStyle = WindowStyle::Windowed;
  std::unique_ptr<RenderWindow> wnd(
    std::make_unique<RenderWindow>(wndTitle, wndSize, wndStyle, wndSamples));
  wnd->setVisible(true);

  Mesh2ShaderProgram m2rend;

  Texture2 shapeTex = Texture2(pngReadFile<PixelFormat::R>(dataDir + u8"monalisa.png"), TextureFormat::R, 4u);
  shapeTex.setChannelMapping(TextureChannelMapping::Luminosity);
  shapeTex.setWrapMode(Texture2::WrapMode{TextureWrapMode::MirroredRepeat, TextureWrapMode::ClampToEdge});


  std::vector<std::unique_ptr<DrawableShape>> shapes;

  shapes.push_back(std::make_unique<RectangleShape>(shapeTex));
  shapes.back()->mTransformData.m_position = vec2f(16.f, 16.f);

  shapes.push_back(std::make_unique<RectangleOutlineShape>(shapeTex));
  shapes.back()->mTransformData.m_position = vec2f(64.f, 16.f);

  shapes.push_back(std::make_unique<EllipseShape>(shapeTex));
  shapes.back()->mTransformData.m_position = vec2f(112.f, 16.f);

  shapes.push_back(std::make_unique<EllipseOutlineShape>(shapeTex));
  shapes.back()->mTransformData.m_position = vec2f(160.f, 16.f);

  shapes.push_back(std::make_unique<TextureQuadShape>(shapeTex));
  shapes.back()->mTransformData.m_position = vec2f(204.f, 16.f);

  size_t currentShape = 0;

  bool running = true;
  const std::chrono::nanoseconds frameTime(1000000000 / 60);
  std::chrono::nanoseconds lastUpdateTime(frameTime);
  hou::clock loopClock;
  while(running)
  {
    // Window Events handling.
    wnd->updateEventQueue();
    while(!wnd->isEventQueueEmpty())
    {
      WindowEvent we = wnd->popEvent();
      switch(we.getType())
      {
        case WindowEventType::Closed:
        {
          running = false;
          break;
        }
        case WindowEventType::KeyReleased:
        {
          const auto& data = we.getKeyData();
          if(data.scanCode == ScanCode::Escape)
          {
            running = false;
          }
          else if(data.scanCode == ScanCode::F1)
          {
            currentShape = 0;
          }
          else if(data.scanCode == ScanCode::F2)
          {
            currentShape = 1;
          }
          else if(data.scanCode == ScanCode::F3)
          {
            currentShape = 2;
          }
          else if(data.scanCode == ScanCode::F4)
          {
            currentShape = 3;
          }
          else if(data.scanCode == ScanCode::F5)
          {
            currentShape = 4;
          }
          else if(data.scanCode == ScanCode::Add)
          {
            if(wndSamples < 32)
            {
              wndSamples *= 2;
            }
            std::cout << "Samples: " << wndSamples << std::endl;
            wnd->setSampleCount(wndSamples);
          }
          else if(data.scanCode == ScanCode::Subtract)
          {
            if(wndSamples > 1)
            {
              wndSamples /= 2;
            }
            std::cout << "Samples: " << wndSamples << std::endl;
            wnd->setSampleCount(wndSamples);
          }
          else if(data.scanCode == ScanCode::Decimal)
          {
            wndStyle = WindowStyle::Fullscreen;
            wnd.reset();
            wnd = std::make_unique<RenderWindow>(wndTitle, wndSize
              , wndStyle, wndSamples);
            wnd->setVisible(true);
          }
          else if(data.scanCode == ScanCode::Numpad0)
          {
            wndStyle = WindowStyle::Windowed;
            wnd.reset();
            wnd = std::make_unique<RenderWindow>(wndTitle, wndSize
              , wndStyle, wndSamples);
            wnd->setVisible(true);
          }
          break;
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
          break;
      }
    }

    // Update frame.
    if((loopClock.get_elapsed_time() - lastUpdateTime) >= frameTime)
    {
      lastUpdateTime += frameTime;

      shapes[currentShape]->handleInput();

      static const int viewportDelta = 4;
      if(Keyboard::isKeyPressed(ScanCode::Divide))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.x() += viewportDelta;
        wnd->setViewport(currentViewport);
      }
      if(Keyboard::isKeyPressed(ScanCode::Numpad8))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.x() -= viewportDelta;
        wnd->setViewport(currentViewport);
      }
      if(Keyboard::isKeyPressed(ScanCode::Multiply))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.y() += viewportDelta;
        wnd->setViewport(currentViewport);
      }
      if(Keyboard::isKeyPressed(ScanCode::Numpad9))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.y() -= viewportDelta;
        wnd->setViewport(currentViewport);
      }
      if(Keyboard::isKeyPressed(ScanCode::Numpad5))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.w() += viewportDelta;
        wnd->setViewport(currentViewport);
      }
      if(Keyboard::isKeyPressed(ScanCode::Numpad2))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.w() -= viewportDelta;
        wnd->setViewport(currentViewport);
      }
      if(Keyboard::isKeyPressed(ScanCode::Numpad6))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.h() += viewportDelta;
        wnd->setViewport(currentViewport);
      }
      if(Keyboard::isKeyPressed(ScanCode::Numpad3))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.h() -= viewportDelta;
        wnd->setViewport(currentViewport);
      }

      wnd->clear(Color::Grey);

      trans2f projTrans = trans2f::orthographic_projection(wnd->getViewport());

      Mesh2 viewportMesh = createRectangleOutlineMesh2(wnd->getViewport().get_size(), 1);
      m2rend.draw(*wnd, viewportMesh, Color::White
        , projTrans * trans2f::translation(wnd->getViewport().get_position()));

      for(const auto& shapePtr : shapes)
      {
        shapePtr->draw(*wnd, m2rend, projTrans);
      }
      wnd->display();
    }
  }

  return 0;
}
