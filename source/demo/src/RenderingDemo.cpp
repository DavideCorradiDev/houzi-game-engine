#include "hou/gfx/Vertex2.hpp"
#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/RenderWindow.hpp"
#include "hou/gfx/TextureChannelMapping.hpp"
#include "hou/gfx/mesh.hpp"
#include "hou/gfx/mesh2_shader_program.hpp"
#include "hou/gfx/TextShaderProgram.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/rotation2.hpp"
#include "hou/mth/transform2.hpp"

#include "hou/sys/color.hpp"
#include "hou/cor/clock.hpp"
#include "hou/sys/keyboard.hpp"
#include "hou/sys/window_event.hpp"
#include "hou/sys/window_style.hpp"

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
  void draw(RenderSurface& rt, mesh2_shader_program& renderer, const trans2f& t) const;

  void handleInput();

public:
  color mColor;
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
  , mColor(color::white)
  , mTransformData()
  , mOrigin(0.f, 0.f)
  , m_size(32.f, 32.f)
  , mThickness(1.f)
  , mPoints(16)
  , mDrawWithTexture(false)
  , mTexture(&texture)
{}



void DrawableShape::draw(RenderSurface& rt, mesh2_shader_program& renderer, const trans2f& t) const
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

  if(keyboard::is_key_pressed(scan_code::A))
  {
    mTransformData.m_position.x() += deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::Z))
  {
    mTransformData.m_position.x() -= deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::S))
  {
    mTransformData.m_position.y() += deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::X))
  {
    mTransformData.m_position.y() -= deltaPos;
  }

  if(keyboard::is_key_pressed(scan_code::D))
  {
    mTransformData.mRotation += deltaRot;
  }
  if(keyboard::is_key_pressed(scan_code::C))
  {
    mTransformData.mRotation -= deltaRot;
  }

  if(keyboard::is_key_pressed(scan_code::F))
  {
    mTransformData.mScale.x() += deltaScale;
  }
  if(keyboard::is_key_pressed(scan_code::V))
  {
    mTransformData.mScale.x() -= deltaScale;
  }
  if(keyboard::is_key_pressed(scan_code::G))
  {
    mTransformData.mScale.y() += deltaScale;
  }
  if(keyboard::is_key_pressed(scan_code::B))
  {
    mTransformData.mScale.y() -= deltaScale;
  }

  if(keyboard::is_key_pressed(scan_code::H))
  {
    mTransformData.mShear.x() += deltaShear;
  }
  if(keyboard::is_key_pressed(scan_code::N))
  {
    mTransformData.mShear.x() -= deltaShear;
  }
  if(keyboard::is_key_pressed(scan_code::J))
  {
    mTransformData.mShear.y() += deltaShear;
  }
  if(keyboard::is_key_pressed(scan_code::M))
  {
    mTransformData.mShear.y() -= deltaShear;
  }

  if(keyboard::is_key_pressed(scan_code::Num1))
  {
    mColor.set_red(mColor.get_red() + deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::Q))
  {
    mColor.set_red(mColor.get_red() - deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::Num2))
  {
    mColor.set_green(mColor.get_green() + deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::W))
  {
    mColor.set_green(mColor.get_green() - deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::Num3))
  {
    mColor.set_blue(mColor.get_blue() + deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::E))
  {
    mColor.set_blue(mColor.get_blue() - deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::Num4))
  {
    mColor.set_alpha(mColor.get_alpha() + deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::R))
  {
    mColor.set_alpha(mColor.get_alpha() - deltaCol);
  }

  if(keyboard::is_key_pressed(scan_code::Num5))
  {
    mOrigin.x() += deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::T))
  {
    mOrigin.x() -= deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::Num6))
  {
    mOrigin.y() += deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::Y))
  {
    mOrigin.y() -= deltaPos;
  }

  if(keyboard::is_key_pressed(scan_code::Num7))
  {
    m_size.x() += deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::U))
  {
    m_size.x() -= deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::Num8))
  {
    m_size.y() += deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::I))
  {
    m_size.y() -= deltaPos;
  }

  if(keyboard::is_key_pressed(scan_code::Num9))
  {
    mThickness += deltaThickness;
  }
  if(keyboard::is_key_pressed(scan_code::O))
  {
    mThickness -= deltaThickness;
  }

  if(keyboard::is_key_pressed(scan_code::Num0))
  {
    mPoints += deltaPoints;
  }
  if(keyboard::is_key_pressed(scan_code::P))
  {
    mPoints -= deltaPoints;
    if(mPoints < minPoints)
    {
      mPoints = minPoints;
    }
  }

  if(keyboard::is_key_pressed(scan_code::K))
  {
    mDrawWithTexture = true;
  }
  if(keyboard::is_key_pressed(scan_code::Comma))
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
  graphic_context ctx;
  graphic_context::set_current(ctx);

  std::string wndTitle(u8"Rendering Demo");
  vec2u wndSize(800u, 600u);
  uint wndSamples = 16u;
  window_style wndStyle = window_style::windowed;
  std::unique_ptr<RenderWindow> wnd(
    std::make_unique<RenderWindow>(wndTitle, wndSize, wndStyle, wndSamples));
  wnd->set_visible(true);

  mesh2_shader_program m2rend;

  Texture2 shapeTex = Texture2(png_read_file<pixel_format::r>(dataDir + u8"monalisa.png"), TextureFormat::r, 4u);
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
    // window Events handling.
    wnd->update_event_queue();
    while(!wnd->is_event_queue_empty())
    {
      window_event we = wnd->pop_event();
      switch(we.get_type())
      {
        case window_event_type::closed:
        {
          running = false;
          break;
        }
        case window_event_type::key_released:
        {
          const auto& data = we.get_key_data();
          if(data.scan_code == scan_code::Escape)
          {
            running = false;
          }
          else if(data.scan_code == scan_code::F1)
          {
            currentShape = 0;
          }
          else if(data.scan_code == scan_code::F2)
          {
            currentShape = 1;
          }
          else if(data.scan_code == scan_code::F3)
          {
            currentShape = 2;
          }
          else if(data.scan_code == scan_code::F4)
          {
            currentShape = 3;
          }
          else if(data.scan_code == scan_code::F5)
          {
            currentShape = 4;
          }
          else if(data.scan_code == scan_code::Add)
          {
            if(wndSamples < 32)
            {
              wndSamples *= 2;
            }
            std::cout << "Samples: " << wndSamples << std::endl;
            wnd->setSampleCount(wndSamples);
          }
          else if(data.scan_code == scan_code::Subtract)
          {
            if(wndSamples > 1)
            {
              wndSamples /= 2;
            }
            std::cout << "Samples: " << wndSamples << std::endl;
            wnd->setSampleCount(wndSamples);
          }
          else if(data.scan_code == scan_code::Decimal)
          {
            wndStyle = window_style::fullscreen;
            wnd.reset();
            wnd = std::make_unique<RenderWindow>(wndTitle, wndSize
              , wndStyle, wndSamples);
            wnd->set_visible(true);
          }
          else if(data.scan_code == scan_code::Numpad0)
          {
            wndStyle = window_style::windowed;
            wnd.reset();
            wnd = std::make_unique<RenderWindow>(wndTitle, wndSize
              , wndStyle, wndSamples);
            wnd->set_visible(true);
          }
          break;
        }
        case hou::window_event_type::focus_gained:
        case hou::window_event_type::focus_lost:
        case hou::window_event_type::resized:
        case hou::window_event_type::key_pressed:
        case hou::window_event_type::TextEntered:
        case hou::window_event_type::mouse_moved:
        case hou::window_event_type::mouse_entered:
        case hou::window_event_type::mouse_left:
        case hou::window_event_type::mouse_button_pressed:
        case hou::window_event_type::mouse_button_released:
        case hou::window_event_type::mouse_wheel_moved:
          break;
      }
    }

    // Update frame.
    if((loopClock.get_elapsed_time() - lastUpdateTime) >= frameTime)
    {
      lastUpdateTime += frameTime;

      shapes[currentShape]->handleInput();

      static const int viewportDelta = 4;
      if(keyboard::is_key_pressed(scan_code::Divide))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.x() += viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::Numpad8))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.x() -= viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::Multiply))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.y() += viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::Numpad9))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.y() -= viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::Numpad5))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.w() += viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::Numpad2))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.w() -= viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::Numpad6))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.h() += viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::Numpad3))
      {
        recti currentViewport = wnd->getViewport();
        currentViewport.h() -= viewportDelta;
        wnd->set_viewport(currentViewport);
      }

      wnd->clear(color::grey);

      trans2f projTrans = trans2f::orthographic_projection(wnd->getViewport());

      Mesh2 viewportMesh = createRectangleOutlineMesh2(wnd->getViewport().get_size(), 1);
      m2rend.draw(*wnd, viewportMesh, color::white
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
