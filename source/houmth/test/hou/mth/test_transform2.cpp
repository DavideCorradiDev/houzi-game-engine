// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/rectangle.hpp"
#include "hou/mth/rotation2.hpp"
#include "hou/mth/transform2.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_transform2 : public Test
{};

}  // namespace



TEST_F(test_transform2, default_constructor)
{
  trans2f t;
  // clang-format off
  mat4x4f tm_ref
  {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  // clang-format on
  EXPECT_FLOAT_CLOSE(tm_ref, t.to_mat4x4());
}



TEST_F(test_transform2, conversion_constructor)
{
  trans2d td;
  trans2f tf(td);
  // clang-format off
  mat4x4f tm_ref
  {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  // clang-format on
  EXPECT_FLOAT_CLOSE(tm_ref, tf.to_mat4x4());
}



TEST_F(test_transform2, build_translation)
{
  trans2f t = trans2f::translation(vec2f(2.f, 3.f));
  // clang-format off
  mat4x4f tm_ref
  {
    1.f, 0.f, 0.f, 2.f,
    0.f, 1.f, 0.f, 3.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  // clang-format on
  EXPECT_FLOAT_CLOSE(tm_ref, t.to_mat4x4());
}



TEST_F(test_transform2, build_rotation)
{
  trans2f tr;
  mat4x4f tm_ref;

  tr = trans2f::rotation(rot2f(pi_f / 2.f));
  // clang-format off
  tm_ref =
  {
    0.f, -1.f, 0.f, 0.f,
    1.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  // clang-format on
  EXPECT_FLOAT_CLOSE(tm_ref, tr.to_mat4x4());

  tr = trans2f::rotation(rot2f(-pi_f / 6.f));
  // clang-format off
  tm_ref =
  {
    sqrt(3.f)/2.f, 0.5f, 0.f, 0.f,
    -0.5f, sqrt(3.f)/2.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  // clang-format on
  EXPECT_FLOAT_CLOSE(tm_ref, tr.to_mat4x4());
}



TEST_F(test_transform2, build_scale)
{
  trans2f t = trans2f::scale(vec2f(2.f, 3.f));
  // clang-format off
  mat4x4f tm_ref
  {
    2.f, 0.f, 0.f, 0.f,
    0.f, 3.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  // clang-format on
  EXPECT_FLOAT_CLOSE(tm_ref, t.to_mat4x4());
}



TEST_F(test_transform2, build_shear)
{
  trans2f t = trans2f::shear(2.f, 3.f);
  // clang-format off
  mat4x4f tm_ref
  {
    1.f, 2.f, 0.f, 0.f,
    3.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  // clang-format on
  EXPECT_FLOAT_CLOSE(tm_ref, t.to_mat4x4());
}



TEST_F(test_transform2, build_orthographic_projection)
{
  trans2f t
    = trans2f::orthographic_projection(rectf(50.f, 100.f, 200.f, 400.f));

  // clang-format off
  matrix<float, 4, 4> tm_ref
  {
    0.01f, 0.f, 0.f, -1.5f,
    0.f, 0.005, 0.f, -1.5f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  // clang-format on
  EXPECT_FLOAT_CLOSE(tm_ref, t.to_mat4x4());
}



TEST_F(test_transform2, inversion)
{
  // TODO: this matrix inversion has lower precision than 1.e-6. Check if it
  // can be improved. trans2f t
  //   = trans2f::scale(vec2f(0.5f, -5.f);
  //   * trans2f::shear(vec2f(-025.f, 0.3f);
  //   * trans2f::rotation(deg_to_rad(45.f))
  //   * trans2f::translation(vec2f(-4.f, 7.f));

  trans2f t;
  trans2f t_inv1;
  trans2f t_inv2;
  trans2f identity;

  t = trans2f::scale(vec2f(0.5f, -1.f)) * trans2f::shear(-025.f, 0.3f)
    * trans2f::rotation(rot2f(deg_to_rad(90.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  t_inv1 = inverse(t);
  t_inv2 = t;
  t_inv2.invert();

  EXPECT_CLOSE(identity, (t * t_inv1), 1.e-6);
  EXPECT_CLOSE(identity, (t * t_inv2), 1.e-6);

  t = trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  t_inv1 = inverse(t);
  t_inv2 = t;
  t_inv2.invert();

  EXPECT_CLOSE(identity, (t * t_inv1), 1.e-6);
  EXPECT_CLOSE(identity, (t * t_inv2), 1.e-6);
}



TEST_F(test_transform2, composition)
{
  trans2f t1 = trans2f::scale(vec2f(0.5f, -5.f)) * trans2f::shear(-2.f, 3.f)
    * trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  trans2f t2 = trans2f::scale(vec2f(1.5f, 2.f)) * trans2f::shear(-1.5f, -4.f)
    * trans2f::rotation(rot2f(deg_to_rad(-120.f)))
    * trans2f::translation(vec2f(11.f, 5.f));
  trans2f t3 = t1;
  t3 *= t2;
  trans2f t4 = t1 * t2;
  mat4x4f tm_ref = t1.to_mat4x4() * t2.to_mat4x4();

  EXPECT_FLOAT_CLOSE(tm_ref, t3.to_mat4x4());
  EXPECT_FLOAT_CLOSE(t3, t4);
}



TEST_F(test_transform2, vector_transformation)
{
  trans2f t = trans2f::scale(vec2f(0.5f, -5.f)) * trans2f::shear(-2.f, 3.f)
    * trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  vec2f v(3.f, -13.f);
  v = t.transform_vector(v);

  // Perform the transformation using the homogeneous transformation matrix
  // and a 4d vector and compare the results.
  // 4th element == 0 -> vector
  matrix<float, 4, 1> hv{3.f, -13.f, 0.f, 0.f};
  hv = t.to_mat4x4() * hv;
  vec2f v_ref(hv(0), hv(1));

  EXPECT_FLOAT_CLOSE(v_ref, v);
}



TEST_F(test_transform2, point_transformation)
{
  trans2f t = trans2f::scale(vec2f(0.5f, -5.f)) * trans2f::shear(-2.f, 3.f)
    * trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  vec2f v(3.f, -13.f);
  v = t.transform_point(v);

  // Perform the transformation using the homogeneous transformation matrix
  // and a 4d point and compare the results.
  // 4th element == 1 -> point
  matrix<float, 4, 1> hv{3.f, -13.f, 0.f, 1.f};
  hv = t.to_mat4x4() * hv;
  vec2f v_ref(hv(0), hv(1));

  EXPECT_FLOAT_CLOSE(v_ref, v);
}



TEST_F(test_transform2, comparison_operators)
{
  trans2f t1 = trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  trans2f t2 = t1;
  trans2f t3 = trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-5.f, 7.f));
  trans2f t4 = trans2f::rotation(rot2f(deg_to_rad(45.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));

  EXPECT_TRUE(t1 == t2);
  EXPECT_FALSE(t1 == t3);
  EXPECT_FALSE(t1 == t4);
  EXPECT_FALSE(t1 != t2);
  EXPECT_TRUE(t1 != t3);
  EXPECT_TRUE(t1 != t4);
}



TEST_F(test_transform2, floating_point_comparison)
{
  trans2f t1 = trans2f::scale(vec2f(0.5f, -5.f)) * trans2f::shear(-2.f, 3.f)
    * trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  trans2f t2 = trans2f::scale(vec2f(1.5f, 2.f)) * trans2f::shear(-1.5f, -4.f)
    * trans2f::rotation(rot2f(deg_to_rad(-120.f)))
    * trans2f::translation(vec2f(11.f, 5.f));
  trans2f t3 = t1;
  trans2f t4 = trans2f::scale(vec2f(0.5001f, -5.f)) * trans2f::shear(-2.f, 3.f)
    * trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));

  EXPECT_FALSE(close(t1, t2));
  EXPECT_TRUE(close(t1, t3));
  EXPECT_TRUE(close(t1, t4, 1.e-2f));
  EXPECT_FALSE(close(t1, t4, 1.e-3f));
}



TEST_F(test_transform2, identity)
{
  EXPECT_FLOAT_CLOSE(trans2f(), trans2f::identity());
}



TEST_F(test_transform2, output_stream_operator)
{
  trans2f t = trans2f::scale(vec2f(2.f, 3.f)) * trans2f::shear(1.f, 1.f)
    * trans2f::translation(vec2f(2.f, 3.f));
  const char* output
    = "(2, 2, 0, 10)\n(3, 3, 0, 15)\n(0, 0, 1, 0)\n(0, 0, 0, 1)";

  EXPECT_OUTPUT(output, t);
}
