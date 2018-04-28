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

class TestTransform3 : public Test {};

}



TEST_F(TestTransform3, DefaultConstructor)
{
  trans3f t;
  mat4x4f tmRef
  {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.to_mat4x4());
}



TEST_F(TestTransform3, ConversionConstructor)
{
  trans3d td;
  trans3f tf(td);
  mat4x4f tmRef
  {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, tf.to_mat4x4());
}



TEST_F(TestTransform3, BuildTranslation)
{
  trans3f t = trans3f::translation(vec3f(2.f, 3.f, 4.f));
  mat4x4f tmRef
  {
    1.f, 0.f, 0.f, 2.f,
    0.f, 1.f, 0.f, 3.f,
    0.f, 0.f, 1.f, 4.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.to_mat4x4());
}



TEST_F(TestTransform3, BuildRotationX)
{
  trans3f tr = trans3f::rotation(Rot3f::x(-pi_f / 6.f));
  mat4x4f tmRef =
  {
    1.f,  0.f,           0.f,           0.f,
    0.f,  sqrt(3.f)/2.f, 0.5f,          0.f,
    0.f, -0.5f,          sqrt(3.f)/2.f, 0.f,
    0.f,  0.f,           0.f,           1.f,
  };
  HOU_EXPECT_CLOSE(tmRef, tr.to_mat4x4(), 1.e-6f);
}



TEST_F(TestTransform3, BuildRotationY)
{
  trans3f tr = trans3f::rotation(Rot3f::y(-pi_f / 6.f));
  mat4x4f tmRef =
  {
    sqrt(3.f)/2.f, 0.f, -0.5f,          0.f,
    0.f,           1.f,  0.f,           0.f,
    0.5f,          0.f,  sqrt(3.f)/2.f, 0.f,
    0.f,           0.f,  0.f,           1.f,
  };
  HOU_EXPECT_CLOSE(tmRef, tr.to_mat4x4(), 1.e-6f);
}



TEST_F(TestTransform3, BuildRotationZ)
{
  trans3f tr = trans3f::rotation(Rot3f::z(-pi_f / 6.f));
  mat4x4f tmRef =
  {
     sqrt(3.f)/2.f, 0.5f,          0.f, 0.f,
    -0.5f,          sqrt(3.f)/2.f, 0.f, 0.f,
     0.f,           0.f,           1.f, 0.f,
     0.f,           0.f,           0.f, 1.f,
  };
  HOU_EXPECT_CLOSE(tmRef, tr.to_mat4x4(), 1.e-6f);
}



TEST_F(TestTransform3, BuildScale)
{
  trans3f t = trans3f::scale(vec3f(2.f, 3.f, 4.f));
  mat4x4f tmRef
  {
    2.f, 0.f, 0.f, 0.f,
    0.f, 3.f, 0.f, 0.f,
    0.f, 0.f, 4.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.to_mat4x4());
}



TEST_F(TestTransform3, BuildShear)
{
  trans3f t = trans3f::shear(2.f, 3.f, 4.f, 5.f, 6.f, 7.f);
  mat4x4f tmRef
  {
    1.f, 2.f, 3.f, 0.f,
    4.f, 1.f, 5.f, 0.f,
    6.f, 7.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.to_mat4x4());
}



TEST_F(TestTransform3, Inversion)
{
  trans3f t;
  trans3f tInv1;
  trans3f tInv2;
  trans3f identity;

  t = trans3f::scale(vec3f(0.5f, -1.f, 1.f))
    * trans3f::shear(-025.f, 0.5f, 0.f, 0.f, 0.f, 0.f)
    * trans3f::rotation(Rot3f(vec3f(-4.f, 1.f, 0.5f) * deg_to_rad(90.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 1.f));
  tInv1 = inverse(t);
  tInv2 = t;
  tInv2.invert();

  HOU_EXPECT_CLOSE(identity, (t * tInv1), 1.e-5);
  HOU_EXPECT_CLOSE(identity, (t * tInv2), 1.e-5);

  t = trans3f::rotation(Rot3f::z(deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 9.f));
  tInv1 = inverse(t);
  tInv2 = t;
  tInv2.invert();

  HOU_EXPECT_CLOSE(identity, (t * tInv1), 1.e-6);
  HOU_EXPECT_CLOSE(identity, (t * tInv2), 1.e-6);
}



TEST_F(TestTransform3, Composition)
{
  trans3f t1
    = trans3f::scale(vec3f(0.5f, -5.f, 1.2f))
    * trans3f::shear(-2.f, 3.f, 4.f, 5.f, 0.5f, 0.3f)
    * trans3f::rotation(Rot3f(vec3f(1.f, 0.5f, -1.2f) * deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 0.1f));
  trans3f t2
    = trans3f::scale(vec3f(1.5f, 2.f, 3.f))
    * trans3f::shear(-1.5f, -4.f, 1.f, 1.f, 0.8f, 0.5f)
    * trans3f::rotation(Rot3f::z(deg_to_rad(-120.f)))
    * trans3f::translation(vec3f(11.f, 5.f, -1.f));
  trans3f t3 = t1;
  t3 *= t2;
  trans3f t4 = t1 * t2;
  mat4x4f tmRef = t1.to_mat4x4() * t2.to_mat4x4();

  HOU_EXPECT_FLOAT_CLOSE(tmRef, t3.to_mat4x4());
  HOU_EXPECT_FLOAT_CLOSE(t3, t4);
}



TEST_F(TestTransform3, VectorTransformation)
{
  trans3f t
    = trans3f::scale(vec3f(0.5f, -5.f, 2.f))
    * trans3f::shear(-2.f, 3.f, 1.f, -1.f, 2.f, 3.f)
    * trans3f::rotation(Rot3f(vec3f(0.f, 1.f, -0.5f) * deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 5.f));
  vec3f v(3.f, -13.f, 10.f);
  v = t.transform_vector(v);

  // Perform the transformation using the homogeneous transformation ph_matrix
  // and a 4d vector and compare the results.
  // 4th element == 0 -> vector
  Mat4x1f hv{3.f, -13.f, 10.f, 0.f};
  hv = t.to_mat4x4() * hv;
  vec3f vRef(hv(0), hv(1), hv(2));

  HOU_EXPECT_FLOAT_CLOSE(vRef, v);
}



TEST_F(TestTransform3, PointTransformation)
{
  trans3f t
    = trans3f::scale(vec3f(0.5f, -5.f, 2.f))
    * trans3f::shear(-2.f, 3.f, 1.f, -1.f, 2.f, 3.f)
    * trans3f::rotation(Rot3f(vec3f(0.f, 1.f, -0.5f) * deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 5.f));
  vec3f v(3.f, -13.f, 10.f);
  v = t.transform_point(v);

  // Perform the transformation using the homogeneous transformation ph_matrix
  // and a 4d point and compare the results.
  // 4th element == 1 -> point
  Mat4x1f hv{3.f, -13.f, 10.f, 1.f};
  hv = t.to_mat4x4() * hv;
  vec3f vRef(hv(0), hv(1), hv(2));

  HOU_EXPECT_FLOAT_CLOSE(vRef, v);
}



TEST_F(TestTransform3, ComparisonOperators)
{
  trans3f t1
    = trans3f::rotation(Rot3f::z(deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 0.f));
  trans3f t2 = t1;
  trans3f t3
    = trans3f::rotation(Rot3f::z(deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 8.f, 0.f));
  trans3f t4
    = trans3f::rotation(Rot3f::z(deg_to_rad(45.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 0.f));

  EXPECT_TRUE(t1 == t2);
  EXPECT_FALSE(t1 == t3);
  EXPECT_FALSE(t1 == t4);
  EXPECT_FALSE(t1 != t2);
  EXPECT_TRUE(t1 != t3);
  EXPECT_TRUE(t1 != t4);
}



TEST_F(TestTransform3, FloatingPointComparison)
{
  trans3f t1
    = trans3f::scale(vec3f(0.5f, -5.f, 2.f))
    * trans3f::shear(-2.f, 3.f, 4.f, 5.f, 6.f, 7.f)
    * trans3f::rotation(Rot3f::z(deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 0.f));
  trans3f t2
    = trans3f::scale(vec3f(1.5f, 2.f, 2.f))
    * trans3f::shear(-1.5f, -4.f, 3.f, 2.f, 1.f, 4.f)
    * trans3f::rotation(Rot3f::z(deg_to_rad(-120.f)))
    * trans3f::translation(vec3f(11.f, 5.f, 0.f));
  trans3f t3 = t1;
  trans3f t4
    = trans3f::scale(vec3f(0.5001f, -5.f, 2.0001f))
    * trans3f::shear(-2.f, 3.f, 4.f, 5.f, 6.f, 7.f)
    * trans3f::rotation(Rot3f::z(deg_to_rad(30.f)))
    * trans3f::translation(vec3f(-4.f, 7.f, 0.f));

  EXPECT_FALSE(close(t1, t2));
  EXPECT_TRUE(close(t1, t3));
  EXPECT_TRUE(close(t1, t4, 1.e-2f));
  EXPECT_FALSE(close(t1, t4, 1.e-3f));
}



TEST_F(TestTransform3, Identity)
{
  HOU_EXPECT_FLOAT_CLOSE(trans3f(), trans3f::identity());
}



TEST_F(TestTransform3, OutputStreamOperator)
{
  trans3f t
    = trans3f::scale(vec3f(2.f, 3.f, 4.f))
    * trans3f::shear(1.f, 1.f, 2.f, 2.f, 3.f, 3.f)
    * trans3f::translation(vec3f(2.f, 3.f, 4.f));
  const char* output = "(2, 2, 2, 18)\n(6, 3, 6, 45)\n(12, 12, 4, 76)\n(0, 0, 0, 1)";
  HOU_EXPECT_OUTPUT(output, t);
}

