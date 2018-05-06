// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/rectangle.hpp"
#include "hou/mth/transform3.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_transform3 : public Test
{};

}  // namespace



TEST_F(test_transform3, default_constructor)
{
  trans3f t;
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



TEST_F(test_transform3, conversion_constructor)
{
  trans3d td;
  trans3f tf(td);
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



TEST_F(test_transform3, build_translation)
{
  trans3f t = trans3f::translation(vec3f(2.f, 3.f, 4.f));
  // clang-format off
  mat4x4f tm_ref
  {
    1.f, 0.f, 0.f, 2.f,
    0.f, 1.f, 0.f, 3.f,
    0.f, 0.f, 1.f, 4.f,
    0.f, 0.f, 0.f, 1.f,
  };
  // clang-format on
  EXPECT_FLOAT_CLOSE(tm_ref, t.to_mat4x4());
}



TEST_F(test_transform3, build_rotation_x)
{
  trans3f tr = trans3f::rotation(rot3f::x(-pi_f / 6.f));
  // clang-format off
  mat4x4f tm_ref =
  {
    1.f,  0.f,           0.f,           0.f,
    0.f,  sqrt(3.f)/2.f, 0.5f,          0.f,
    0.f, -0.5f,          sqrt(3.f)/2.f, 0.f,
    0.f,  0.f,           0.f,           1.f,
  };
  // clang-format on
  EXPECT_CLOSE(tm_ref, tr.to_mat4x4(), 1.e-6f);
}



TEST_F(test_transform3, build_rotation_y)
{
  trans3f tr = trans3f::rotation(rot3f::y(-pi_f / 6.f));
  // clang-format off
  mat4x4f tm_ref =
  {
    sqrt(3.f)/2.f, 0.f, -0.5f,          0.f,
    0.f,           1.f,  0.f,           0.f,
    0.5f,          0.f,  sqrt(3.f)/2.f, 0.f,
    0.f,           0.f,  0.f,           1.f,
  };
  // clang-format on
  EXPECT_CLOSE(tm_ref, tr.to_mat4x4(), 1.e-6f);
}



TEST_F(test_transform3, build_rotation_z)
{
  trans3f tr = trans3f::rotation(rot3f::z(-pi_f / 6.f));
  // clang-format off
  mat4x4f tm_ref =
  {
     sqrt(3.f)/2.f, 0.5f,          0.f, 0.f,
    -0.5f,          sqrt(3.f)/2.f, 0.f, 0.f,
     0.f,           0.f,           1.f, 0.f,
     0.f,           0.f,           0.f, 1.f,
  };
  // clang-format on
  EXPECT_CLOSE(tm_ref, tr.to_mat4x4(), 1.e-6f);
}



TEST_F(test_transform3, build_scale)
{
  trans3f t = trans3f::scale(vec3f(2.f, 3.f, 4.f));
  // clang-format off
  mat4x4f tm_ref
  {
    2.f, 0.f, 0.f, 0.f,
    0.f, 3.f, 0.f, 0.f,
    0.f, 0.f, 4.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  // clang-format on
  EXPECT_FLOAT_CLOSE(tm_ref, t.to_mat4x4());
}



TEST_F(test_transform3, build_shear)
{
  trans3f t = trans3f::shear(2.f, 3.f, 4.f, 5.f, 6.f, 7.f);
  // clang-format off
  mat4x4f tm_ref
  {
    1.f, 2.f, 3.f, 0.f,
    4.f, 1.f, 5.f, 0.f,
    6.f, 7.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  // clang-format on
  EXPECT_FLOAT_CLOSE(tm_ref, t.to_mat4x4());
}



TEST_F(test_transform3, inversion)
{
  trans3f t;
  trans3f t_inv1;
  trans3f t_inv2;
  trans3f identity;

  t = trans3f::scale(vec3f(0.5f, -1.f, 1.f))
    * trans3f::shear(-025.f, 0.5f, 0.f, 0.f, 0.f, 0.f)
    * trans3f::rotation(rot3f(vec3f(-4.f, 1.f, 0.5f) * deg_to_rad(90.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 1.f));
  t_inv1 = inverse(t);
  t_inv2 = t;
  t_inv2.invert();

  EXPECT_CLOSE(identity, (t * t_inv1), 1.e-5);
  EXPECT_CLOSE(identity, (t * t_inv2), 1.e-5);

  t = trans3f::rotation(rot3f::z(deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 9.f));
  t_inv1 = inverse(t);
  t_inv2 = t;
  t_inv2.invert();

  EXPECT_CLOSE(identity, (t * t_inv1), 1.e-6);
  EXPECT_CLOSE(identity, (t * t_inv2), 1.e-6);
}



TEST_F(test_transform3, composition)
{
  trans3f t1 = trans3f::scale(vec3f(0.5f, -5.f, 1.2f))
    * trans3f::shear(-2.f, 3.f, 4.f, 5.f, 0.5f, 0.3f)
    * trans3f::rotation(rot3f(vec3f(1.f, 0.5f, -1.2f) * deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 0.1f));
  trans3f t2 = trans3f::scale(vec3f(1.5f, 2.f, 3.f))
    * trans3f::shear(-1.5f, -4.f, 1.f, 1.f, 0.8f, 0.5f)
    * trans3f::rotation(rot3f::z(deg_to_rad(-120.f)))
    * trans3f::translation(vec3f(11.f, 5.f, -1.f));
  trans3f t3 = t1;
  t3 *= t2;
  trans3f t4 = t1 * t2;
  mat4x4f tm_ref = t1.to_mat4x4() * t2.to_mat4x4();

  EXPECT_FLOAT_CLOSE(tm_ref, t3.to_mat4x4());
  EXPECT_FLOAT_CLOSE(t3, t4);
}



TEST_F(test_transform3, vector_transformation)
{
  trans3f t = trans3f::scale(vec3f(0.5f, -5.f, 2.f))
    * trans3f::shear(-2.f, 3.f, 1.f, -1.f, 2.f, 3.f)
    * trans3f::rotation(rot3f(vec3f(0.f, 1.f, -0.5f) * deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 5.f));
  vec3f v(3.f, -13.f, 10.f);
  v = t.transform_vector(v);

  // Perform the transformation using the homogeneous transformation matrix
  // and a 4d vector and compare the results.
  // 4th element == 0 -> vector
  mat4x1f hv{3.f, -13.f, 10.f, 0.f};
  hv = t.to_mat4x4() * hv;
  vec3f v_ref(hv(0), hv(1), hv(2));

  EXPECT_FLOAT_CLOSE(v_ref, v);
}



TEST_F(test_transform3, point_transformation)
{
  trans3f t = trans3f::scale(vec3f(0.5f, -5.f, 2.f))
    * trans3f::shear(-2.f, 3.f, 1.f, -1.f, 2.f, 3.f)
    * trans3f::rotation(rot3f(vec3f(0.f, 1.f, -0.5f) * deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 5.f));
  vec3f v(3.f, -13.f, 10.f);
  v = t.transform_point(v);

  // Perform the transformation using the homogeneous transformation matrix
  // and a 4d point and compare the results.
  // 4th element == 1 -> point
  mat4x1f hv{3.f, -13.f, 10.f, 1.f};
  hv = t.to_mat4x4() * hv;
  vec3f v_ref(hv(0), hv(1), hv(2));

  EXPECT_FLOAT_CLOSE(v_ref, v);
}



TEST_F(test_transform3, comparison_operators)
{
  trans3f t1 = trans3f::rotation(rot3f::z(deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 0.f));
  trans3f t2 = t1;
  trans3f t3 = trans3f::rotation(rot3f::z(deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 8.f, 0.f));
  trans3f t4 = trans3f::rotation(rot3f::z(deg_to_rad(45.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 0.f));

  EXPECT_TRUE(t1 == t2);
  EXPECT_FALSE(t1 == t3);
  EXPECT_FALSE(t1 == t4);
  EXPECT_FALSE(t1 != t2);
  EXPECT_TRUE(t1 != t3);
  EXPECT_TRUE(t1 != t4);
}



TEST_F(test_transform3, floating_point_comparison)
{
  trans3f t1 = trans3f::scale(vec3f(0.5f, -5.f, 2.f))
    * trans3f::shear(-2.f, 3.f, 4.f, 5.f, 6.f, 7.f)
    * trans3f::rotation(rot3f::z(deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 0.f));
  trans3f t2 = trans3f::scale(vec3f(1.5f, 2.f, 2.f))
    * trans3f::shear(-1.5f, -4.f, 3.f, 2.f, 1.f, 4.f)
    * trans3f::rotation(rot3f::z(deg_to_rad(-120.f)))
    * trans3f::translation(vec3f(11.f, 5.f, 0.f));
  trans3f t3 = t1;
  trans3f t4 = trans3f::scale(vec3f(0.5001f, -5.f, 2.0001f))
    * trans3f::shear(-2.f, 3.f, 4.f, 5.f, 6.f, 7.f)
    * trans3f::rotation(rot3f::z(deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 0.f));

  EXPECT_FALSE(close(t1, t2));
  EXPECT_TRUE(close(t1, t3));
  EXPECT_TRUE(close(t1, t4, 1.e-2f));
  EXPECT_FALSE(close(t1, t4, 1.e-3f));
}



TEST_F(test_transform3, identity)
{
  EXPECT_FLOAT_CLOSE(trans3f(), trans3f::identity());
}



TEST_F(test_transform3, output_stream_operator)
{
  trans3f t = trans3f::scale(vec3f(2.f, 3.f, 4.f))
    * trans3f::shear(1.f, 1.f, 2.f, 2.f, 3.f, 3.f)
    * trans3f::translation(vec3f(2.f, 3.f, 4.f));
  const char* output
    = "(2, 2, 2, 18)\n(6, 3, 6, 45)\n(12, 12, 4, 76)\n(0, 0, 0, 1)";
  EXPECT_OUTPUT(output, t);
}
