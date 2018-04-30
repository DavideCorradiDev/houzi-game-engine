#include "hou/gfx/vertex2.hpp"
#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/render_window.hpp"
#include "hou/gfx/texture_channel_mapping.hpp"
#include "hou/gfx/mesh.hpp"
#include "hou/gfx/mesh2_shader_program.hpp"
#include "hou/gfx/text_shader_program.hpp"

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
  DrawableShape(const texture2& ph_texture);

  virtual mesh2 generateMesh() const = 0;
  void draw(render_surface& rt, mesh2_shader_program& renderer, const trans2f& t) const;

  void handleInput();

public:
  color m_color;
  TransformData mTransformData;
  vec2f mOrigin;
  vec2f m_size;
  float mThickness;
  float mPoints;
  bool mDrawWithTexture;
  const texture2* mTexture;
};




DrawableShape::DrawableShape(const texture2& ph_texture)
  : non_copyable()
  , m_color(color::white)
  , mTransformData()
  , mOrigin(0.f, 0.f)
  , m_size(32.f, 32.f)
  , mThickness(1.f)
  , mPoints(16)
  , mDrawWithTexture(false)
  , mTexture(&ph_texture)
{}



void DrawableShape::draw(render_surface& rt, mesh2_shader_program& renderer, const trans2f& t) const
{
  if(mDrawWithTexture)
  {
    renderer.draw(rt, generateMesh(), *mTexture, m_color, t * mTransformData.computeTransform());
  }
  else
  {
    renderer.draw(rt, generateMesh(), m_color, t * mTransformData.computeTransform());
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

  if(keyboard::is_key_pressed(scan_code::a))
  {
    mTransformData.m_position.x() += deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::z))
  {
    mTransformData.m_position.x() -= deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::s))
  {
    mTransformData.m_position.y() += deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::x))
  {
    mTransformData.m_position.y() -= deltaPos;
  }

  if(keyboard::is_key_pressed(scan_code::d))
  {
    mTransformData.mRotation += deltaRot;
  }
  if(keyboard::is_key_pressed(scan_code::c))
  {
    mTransformData.mRotation -= deltaRot;
  }

  if(keyboard::is_key_pressed(scan_code::f))
  {
    mTransformData.mScale.x() += deltaScale;
  }
  if(keyboard::is_key_pressed(scan_code::v))
  {
    mTransformData.mScale.x() -= deltaScale;
  }
  if(keyboard::is_key_pressed(scan_code::g))
  {
    mTransformData.mScale.y() += deltaScale;
  }
  if(keyboard::is_key_pressed(scan_code::b))
  {
    mTransformData.mScale.y() -= deltaScale;
  }

  if(keyboard::is_key_pressed(scan_code::h))
  {
    mTransformData.mShear.x() += deltaShear;
  }
  if(keyboard::is_key_pressed(scan_code::n))
  {
    mTransformData.mShear.x() -= deltaShear;
  }
  if(keyboard::is_key_pressed(scan_code::j))
  {
    mTransformData.mShear.y() += deltaShear;
  }
  if(keyboard::is_key_pressed(scan_code::m))
  {
    mTransformData.mShear.y() -= deltaShear;
  }

  if(keyboard::is_key_pressed(scan_code::num1))
  {
    m_color.set_red(m_color.get_red() + deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::q))
  {
    m_color.set_red(m_color.get_red() - deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::num2))
  {
    m_color.set_green(m_color.get_green() + deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::w))
  {
    m_color.set_green(m_color.get_green() - deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::num3))
  {
    m_color.set_blue(m_color.get_blue() + deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::e))
  {
    m_color.set_blue(m_color.get_blue() - deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::num4))
  {
    m_color.set_alpha(m_color.get_alpha() + deltaCol);
  }
  if(keyboard::is_key_pressed(scan_code::r))
  {
    m_color.set_alpha(m_color.get_alpha() - deltaCol);
  }

  if(keyboard::is_key_pressed(scan_code::num5))
  {
    mOrigin.x() += deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::t))
  {
    mOrigin.x() -= deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::num6))
  {
    mOrigin.y() += deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::y))
  {
    mOrigin.y() -= deltaPos;
  }

  if(keyboard::is_key_pressed(scan_code::num7))
  {
    m_size.x() += deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::u))
  {
    m_size.x() -= deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::num8))
  {
    m_size.y() += deltaPos;
  }
  if(keyboard::is_key_pressed(scan_code::i))
  {
    m_size.y() -= deltaPos;
  }

  if(keyboard::is_key_pressed(scan_code::num9))
  {
    mThickness += deltaThickness;
  }
  if(keyboard::is_key_pressed(scan_code::o))
  {
    mThickness -= deltaThickness;
  }

  if(keyboard::is_key_pressed(scan_code::num0))
  {
    mPoints += deltaPoints;
  }
  if(keyboard::is_key_pressed(scan_code::p))
  {
    mPoints -= deltaPoints;
    if(mPoints < minPoints)
    {
      mPoints = minPoints;
    }
  }

  if(keyboard::is_key_pressed(scan_code::k))
  {
    mDrawWithTexture = true;
  }
  if(keyboard::is_key_pressed(scan_code::comma))
  {
    mDrawWithTexture = false;
  }
}



class RectangleShape
  : public DrawableShape
{
public:
  RectangleShape(const texture2& ph_texture)
    : DrawableShape(ph_texture)
  {}

  mesh2 generateMesh() const override
  {
    return create_rectangle_mesh2(m_size);
  }
};



class RectangleOutlineShape
  : public DrawableShape
{
public:
  RectangleOutlineShape(const texture2& ph_texture)
    : DrawableShape(ph_texture)
  {}

  mesh2 generateMesh() const override
  {
    return create_rectangle_outline_mesh2(m_size, mThickness);
  }
};



class EllipseShape
  : public DrawableShape
{
public:
  EllipseShape(texture2& ph_texture)
    : DrawableShape(ph_texture)
  {}

  mesh2 generateMesh() const override
  {
    return create_ellipse_mesh2(m_size, mPoints);
  }
};



class EllipseOutlineShape
  : public DrawableShape
{
public:
  EllipseOutlineShape(const texture2& ph_texture)
    : DrawableShape(ph_texture)
  {}

  mesh2 generateMesh() const override
  {
    return create_ellipse_outline_mesh2(m_size, mPoints, mThickness);
  }
};



class TextureQuadShape
  : public DrawableShape
{
public:
  TextureQuadShape(const texture2& ph_texture)
    : DrawableShape(ph_texture)
  {}

  mesh2 generateMesh() const override
  {
    return create_texture_quad_mesh2(rectf(mOrigin, m_size), mTexture->get_size());
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
  std::unique_ptr<render_window> wnd(
    std::make_unique<render_window>(wndTitle, wndSize, wndStyle, wndSamples));
  wnd->set_visible(true);

  mesh2_shader_program m2rend;

  texture2 shapeTex = texture2(png_read_file<pixel_format::r>(dataDir + u8"monalisa.png"), texture_format::r, 4u);
  shapeTex.setChannelMapping(texture_channel_mapping::luminosity);
  shapeTex.set_wrap_mode(texture2::wrap_mode{texture_wrap_mode::mirrored_repeat, texture_wrap_mode::clamp_to_edge});


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
          if(data.scan_code == scan_code::escape)
          {
            running = false;
          }
          else if(data.scan_code == scan_code::f1)
          {
            currentShape = 0;
          }
          else if(data.scan_code == scan_code::f2)
          {
            currentShape = 1;
          }
          else if(data.scan_code == scan_code::f3)
          {
            currentShape = 2;
          }
          else if(data.scan_code == scan_code::f4)
          {
            currentShape = 3;
          }
          else if(data.scan_code == scan_code::f5)
          {
            currentShape = 4;
          }
          else if(data.scan_code == scan_code::add)
          {
            if(wndSamples < 32)
            {
              wndSamples *= 2;
            }
            std::cout << "Samples: " << wndSamples << std::endl;
            wnd->set_sample_count(wndSamples);
          }
          else if(data.scan_code == scan_code::subtract)
          {
            if(wndSamples > 1)
            {
              wndSamples /= 2;
            }
            std::cout << "Samples: " << wndSamples << std::endl;
            wnd->set_sample_count(wndSamples);
          }
          else if(data.scan_code == scan_code::decimal)
          {
            wndStyle = window_style::fullscreen;
            wnd.reset();
            wnd = std::make_unique<render_window>(wndTitle, wndSize
              , wndStyle, wndSamples);
            wnd->set_visible(true);
          }
          else if(data.scan_code == scan_code::numpad0)
          {
            wndStyle = window_style::windowed;
            wnd.reset();
            wnd = std::make_unique<render_window>(wndTitle, wndSize
              , wndStyle, wndSamples);
            wnd->set_visible(true);
          }
          break;
        }
        case hou::window_event_type::focus_gained:
        case hou::window_event_type::focus_lost:
        case hou::window_event_type::resized:
        case hou::window_event_type::key_pressed:
        case hou::window_event_type::text_entered:
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
      if(keyboard::is_key_pressed(scan_code::divide))
      {
        recti currentViewport = wnd->get_viewport();
        currentViewport.x() += viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::numpad8))
      {
        recti currentViewport = wnd->get_viewport();
        currentViewport.x() -= viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::multiply))
      {
        recti currentViewport = wnd->get_viewport();
        currentViewport.y() += viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::numpad9))
      {
        recti currentViewport = wnd->get_viewport();
        currentViewport.y() -= viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::numpad5))
      {
        recti currentViewport = wnd->get_viewport();
        currentViewport.w() += viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::numpad2))
      {
        recti currentViewport = wnd->get_viewport();
        currentViewport.w() -= viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::numpad6))
      {
        recti currentViewport = wnd->get_viewport();
        currentViewport.h() += viewportDelta;
        wnd->set_viewport(currentViewport);
      }
      if(keyboard::is_key_pressed(scan_code::numpad3))
      {
        recti currentViewport = wnd->get_viewport();
        currentViewport.h() -= viewportDelta;
        wnd->set_viewport(currentViewport);
      }

      wnd->clear(color::grey);

      trans2f projTrans = trans2f::orthographic_projection(wnd->get_viewport());

      mesh2 viewportMesh = create_rectangle_outline_mesh2(wnd->get_viewport().get_size(), 1);
      m2rend.draw(*wnd, viewportMesh, color::white
        , projTrans * trans2f::translation(wnd->get_viewport().get_position()));

      for(const auto& shapePtr : shapes)
      {
        shapePtr->draw(*wnd, m2rend, projTrans);
      }
      wnd->display();
    }
  }

  return 0;
}
