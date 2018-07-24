// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/mesh2.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/rectangle.hpp"



namespace hou
{

namespace
{

mesh2 create_generic_rectangle_mesh2(
  float l, float t, float w, float h, float tl, float tt, float tw, float th);



mesh2 create_generic_rectangle_mesh2(
  float l, float t, float w, float h, float tl, float tt, float tw, float th)
{
  float r = l + w;
  float b = t + h;
  float tr = tl + tw;
  float tb = tt + th;
  return mesh2(mesh_draw_mode::triangle_fan, mesh_fill_mode::fill,
    std::vector<vertex2>{vertex2(vec2f(l, t), vec2f(tl, tt), color::white()),
      vertex2(vec2f(l, b), vec2f(tl, tb), color::white()),
      vertex2(vec2f(r, b), vec2f(tr, tb), color::white()),
      vertex2(vec2f(r, t), vec2f(tr, tt), color::white())});
}

}  // namespace



mesh2 create_rectangle_mesh2(const vec2f& size)
{
  return create_generic_rectangle_mesh2(
    0.f, 0.f, size.x(), size.y(), 0.f, 0.f, 1.f, 1.f);
}



mesh2 create_rectangle_outline_mesh2(const vec2f& size, float thickness)
{
  rectf er(vec2f::zero(), size);
  vec2f tv(thickness, thickness);
  rectf ir(tv, size - 2 * tv);
  return mesh2(mesh_draw_mode::triangle_strip, mesh_fill_mode::fill,
    std::vector<vertex2>{
      vertex2(vec2f(er.l(), er.t()), vec2f::zero(), color::white()),
      vertex2(vec2f(ir.l(), ir.t()), vec2f::zero(), color::white()),
      vertex2(vec2f(er.l(), er.b()), vec2f::zero(), color::white()),
      vertex2(vec2f(ir.l(), ir.b()), vec2f::zero(), color::white()),
      vertex2(vec2f(er.r(), er.b()), vec2f::zero(), color::white()),
      vertex2(vec2f(ir.r(), ir.b()), vec2f::zero(), color::white()),
      vertex2(vec2f(er.r(), er.t()), vec2f::zero(), color::white()),
      vertex2(vec2f(ir.r(), ir.t()), vec2f::zero(), color::white()),
      vertex2(vec2f(er.l(), er.t()), vec2f::zero(), color::white()),
      vertex2(vec2f(ir.l(), ir.t()), vec2f::zero(), color::white())});
}



mesh2 create_ellipse_mesh2(const vec2f& size, uint point_count)
{
  vec2f radius = size / 2.f;

  std::vector<vertex2> vertices(point_count + 2);
  vertices[0].set_position(radius);
  vertices[0].set_color(color::white());

  float t = 0.f;
  float dt = 2.f * pi<float>() / point_count;
  for(size_t i = 1; i < vertices.size(); ++i)
  {
    vec2f dPos(radius.x() * cosf(t), radius.y() * sinf(t));
    vertices[i].set_position(radius + dPos);
    vertices[i].set_color(color::white());
    t += dt;
  }
  return mesh2(mesh_draw_mode::triangle_fan, mesh_fill_mode::fill, vertices);
}



mesh2 create_ellipse_outline_mesh2(
  const vec2f& size, uint point_count, float thickness)
{
  vec2f e_radius = size / 2.f;
  vec2f i_radius = e_radius - vec2f(thickness, thickness);

  float t = 0.f;
  float dt = 2 * pi<float>() / point_count;
  std::vector<vertex2> vertices(2 * point_count + 2);
  for(size_t i = 0; i < vertices.size(); ++i)
  {
    float c = cosf(t);
    float s = sinf(t);

    vec2f ed_pos(e_radius.x() * c, e_radius.y() * s);
    vertices[i].set_position(e_radius + ed_pos);
    vertices[i].set_color(color::white());
    ++i;
    HOU_DEV_ASSERT(i < vertices.size());

    vec2f idPos(i_radius.x() * c, i_radius.y() * s);
    vertices[i].set_position(e_radius + idPos);
    vertices[i].set_color(color::white());

    t += dt;
  }
  return mesh2(mesh_draw_mode::triangle_strip, mesh_fill_mode::fill, vertices);
}



mesh2 create_texture_quad_mesh2(const rectf& rect, const vec2f& tex_size)
{
  return create_generic_rectangle_mesh2(0.f, 0.f, rect.w(), rect.h(),
    rect.x() / tex_size.x(), rect.y() / tex_size.y(), rect.w() / tex_size.x(),
    rect.h() / tex_size.y());
}

}
