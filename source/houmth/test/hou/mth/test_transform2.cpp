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

class TestTransform2 : public Test {};

}



TEST_F(TestTransform2, DefaultConstructor)
{
  trans2f t;
  mat4x4f tmRef
  {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.to_mat4x4());
}



TEST_F(TestTransform2, ConversionConstructor)
{
  trans2d td;
  trans2f tf(td);
  mat4x4f tmRef
  {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, tf.to_mat4x4());
}



TEST_F(TestTransform2, BuildTranslation)
{
  trans2f t = trans2f::translation(vec2f(2.f, 3.f));
  mat4x4f tmRef
  {
    1.f, 0.f, 0.f, 2.f,
    0.f, 1.f, 0.f, 3.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.to_mat4x4());
}



TEST_F(TestTransform2, BuildRotation)
{
  trans2f tr;
  mat4x4f tmRef;

  tr = trans2f::rotation(rot2f(pi_f / 2.f));
  tmRef =
  {
    0.f, -1.f, 0.f, 0.f,
    1.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, tr.to_mat4x4());

  tr = trans2f::rotation(rot2f(-pi_f / 6.f));
  tmRef =
  {
    sqrt(3.f)/2.f, 0.5f, 0.f, 0.f,
    -0.5f, sqrt(3.f)/2.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, tr.to_mat4x4());
}



TEST_F(TestTransform2, BuildScale)
{
  trans2f t = trans2f::scale(vec2f(2.f, 3.f));
  mat4x4f tmRef
  {
    2.f, 0.f, 0.f, 0.f,
    0.f, 3.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.to_mat4x4());
}



TEST_F(TestTransform2, BuildShear)
{
  trans2f t = trans2f::shear(2.f, 3.f);
  mat4x4f tmRef
  {
    1.f, 2.f, 0.f, 0.f,
    3.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.to_mat4x4());
}



TEST_F(TestTransform2, BuildOrthographicProjection)
{
  trans2f t = trans2f::orthographic_projection(rectf(50.f, 100.f, 200.f, 400.f));

  matrix<float, 4, 4> tmRef
  {
    0.01f, 0.f, 0.f, -1.5f,
    0.f, 0.005, 0.f, -1.5f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.to_mat4x4());
}



TEST_F(TestTransform2, Inversion)
{
  // TODO: this ph_matrix inversion has lower precision than 1.e-6. Check if it can
  // be improved.
  // trans2f t
  //   = trans2f::scale(vec2f(0.5f, -5.f);
  //   * trans2f::shear(vec2f(-025.f, 0.3f);
  //   * trans2f::rotation(deg_to_rad(45.f))
  //   * trans2f::translation(vec2f(-4.f, 7.f));

  trans2f t;
  trans2f tInv1;
  trans2f tInv2;
  trans2f identity;

  t = trans2f::scale(vec2f(0.5f, -1.f))
    * trans2f::shear(-025.f, 0.3f)
    * trans2f::rotation(rot2f(deg_to_rad(90.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  tInv1 = inverse(t);
  tInv2 = t;
  tInv2.invert();

  HOU_EXPECT_CLOSE(identity, (t * tInv1), 1.e-6);
  HOU_EXPECT_CLOSE(identity, (t * tInv2), 1.e-6);

  t = trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  tInv1 = inverse(t);
  tInv2 = t;
  tInv2.invert();

  HOU_EXPECT_CLOSE(identity, (t * tInv1), 1.e-6);
  HOU_EXPECT_CLOSE(identity, (t * tInv2), 1.e-6);
}



TEST_F(TestTransform2, Composition)
{
  trans2f t1
    = trans2f::scale(vec2f(0.5f, -5.f))
    * trans2f::shear(-2.f, 3.f)
    * trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  trans2f t2
    = trans2f::scale(vec2f(1.5f, 2.f))
    * trans2f::shear(-1.5f, -4.f)
    * trans2f::rotation(rot2f(deg_to_rad(-120.f)))
    * trans2f::translation(vec2f(11.f, 5.f));
  trans2f t3 = t1;
  t3 *= t2;
  trans2f t4 = t1 * t2;
  mat4x4f tmRef = t1.to_mat4x4() * t2.to_mat4x4();

  HOU_EXPECT_FLOAT_CLOSE(tmRef, t3.to_mat4x4());
  HOU_EXPECT_FLOAT_CLOSE(t3, t4);
}



TEST_F(TestTransform2, VectorTransformation)
{
  trans2f t
    = trans2f::scale(vec2f(0.5f, -5.f))
    * trans2f::shear(-2.f, 3.f)
    * trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  vec2f v(3.f, -13.f);
  v = t.transform_vector(v);

  // Perform the transformation using the homogeneous transformation ph_matrix
  // and a 4d vector and compare the results.
  // 4th element == 0 -> vector
  matrix<float, 4, 1> hv{3.f, -13.f, 0.f, 0.f};
  hv = t.to_mat4x4() * hv;
  vec2f vRef(hv(0), hv(1));

  HOU_EXPECT_FLOAT_CLOSE(vRef, v);
}



TEST_F(TestTransform2, PointTransformation)
{
  trans2f t
    = trans2f::scale(vec2f(0.5f, -5.f))
    * trans2f::shear(-2.f, 3.f)
    * trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  vec2f v(3.f, -13.f);
  v = t.transform_point(v);

  // Perform the transformation using the homogeneous transformation ph_matrix
  // and a 4d point and compare the results.
  // 4th element == 1 -> point
  matrix<float, 4, 1> hv{3.f, -13.f, 0.f, 1.f};
  hv = t.to_mat4x4() * hv;
  vec2f vRef(hv(0), hv(1));

  HOU_EXPECT_FLOAT_CLOSE(vRef, v);
}



TEST_F(TestTransform2, ComparisonOperators)
{
  trans2f t1
    = trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  trans2f t2 = t1;
  trans2f t3
    = trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-5.f, 7.f));
  trans2f t4
    = trans2f::rotation(rot2f(deg_to_rad(45.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));

  EXPECT_TRUE(t1 == t2);
  EXPECT_FALSE(t1 == t3);
  EXPECT_FALSE(t1 == t4);
  EXPECT_FALSE(t1 != t2);
  EXPECT_TRUE(t1 != t3);
  EXPECT_TRUE(t1 != t4);
}



TEST_F(TestTransform2, FloatingPointComparison)
{
  trans2f t1
    = trans2f::scale(vec2f(0.5f, -5.f))
    * trans2f::shear(-2.f, 3.f)
    * trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));
  trans2f t2
    = trans2f::scale(vec2f(1.5f, 2.f))
    * trans2f::shear(-1.5f, -4.f)
    * trans2f::rotation(rot2f(deg_to_rad(-120.f)))
    * trans2f::translation(vec2f(11.f, 5.f));
  trans2f t3 = t1;
  trans2f t4
    = trans2f::scale(vec2f(0.5001f, -5.f))
    * trans2f::shear(-2.f, 3.f)
    * trans2f::rotation(rot2f(deg_to_rad(30.f)))
    * trans2f::translation(vec2f(-4.f, 7.f));

  EXPECT_FALSE(close(t1, t2));
  EXPECT_TRUE(close(t1, t3));
  EXPECT_TRUE(close(t1, t4, 1.e-2f));
  EXPECT_FALSE(close(t1, t4, 1.e-3f));
}



TEST_F(TestTransform2, Identity)
{
  HOU_EXPECT_FLOAT_CLOSE(trans2f(), trans2f::identity());
}



TEST_F(TestTransform2, OutputStreamOperator)
{
  trans2f t
    = trans2f::scale(vec2f(2.f, 3.f))
    * trans2f::shear(1.f, 1.f)
    * trans2f::translation(vec2f(2.f, 3.f));
  const char* output = "(2, 2, 0, 10)\n(3, 3, 0, 15)\n(0, 0, 1, 0)\n(0, 0, 0, 1)";

  HOU_EXPECT_OUTPUT(output, t);
}

