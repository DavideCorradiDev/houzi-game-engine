// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/mth/MathFunctions.hpp"
#include "hou/mth/Rectangle.hpp"
#include "hou/mth/Rotation2.hpp"
#include "hou/mth/Transform2.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestTransform2 : public Test {};

}



TEST_F(TestTransform2, DefaultConstructor)
{
  Trans2f t;
  Mat4x4f tmRef
  {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.toMat4x4());
}



TEST_F(TestTransform2, ConversionConstructor)
{
  Trans2d td;
  Trans2f tf(td);
  Mat4x4f tmRef
  {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, tf.toMat4x4());
}



TEST_F(TestTransform2, BuildTranslation)
{
  Trans2f t = Trans2f::translation(Vec2f(2.f, 3.f));
  Mat4x4f tmRef
  {
    1.f, 0.f, 0.f, 2.f,
    0.f, 1.f, 0.f, 3.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.toMat4x4());
}



TEST_F(TestTransform2, BuildRotation)
{
  Trans2f tr;
  Mat4x4f tmRef;

  tr = Trans2f::rotation(Rot2f(PI_F / 2.f));
  tmRef =
  {
    0.f, -1.f, 0.f, 0.f,
    1.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, tr.toMat4x4());

  tr = Trans2f::rotation(Rot2f(-PI_F / 6.f));
  tmRef =
  {
    sqrt(3.f)/2.f, 0.5f, 0.f, 0.f,
    -0.5f, sqrt(3.f)/2.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, tr.toMat4x4());
}



TEST_F(TestTransform2, BuildScale)
{
  Trans2f t = Trans2f::scale(Vec2f(2.f, 3.f));
  Mat4x4f tmRef
  {
    2.f, 0.f, 0.f, 0.f,
    0.f, 3.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.toMat4x4());
}



TEST_F(TestTransform2, BuildShear)
{
  Trans2f t = Trans2f::shear(2.f, 3.f);
  Mat4x4f tmRef
  {
    1.f, 2.f, 0.f, 0.f,
    3.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.toMat4x4());
}



TEST_F(TestTransform2, BuildOrthographicProjection)
{
  Trans2f t = Trans2f::orthographicProjection(Rectf(50.f, 100.f, 200.f, 400.f));

  Matrix<float, 4, 4> tmRef
  {
    0.01f, 0.f, 0.f, -1.5f,
    0.f, 0.005, 0.f, -1.5f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.toMat4x4());
}



TEST_F(TestTransform2, Inversion)
{
  // TODO: this matrix inversion has lower precision than 1.e-6. Check if it can
  // be improved.
  // Trans2f t
  //   = Trans2f::scale(Vec2f(0.5f, -5.f);
  //   * Trans2f::shear(Vec2f(-025.f, 0.3f);
  //   * Trans2f::rotation(degToRad(45.f))
  //   * Trans2f::translation(Vec2f(-4.f, 7.f));

  Trans2f t;
  Trans2f tInv1;
  Trans2f tInv2;
  Trans2f identity;

  t = Trans2f::scale(Vec2f(0.5f, -1.f))
    * Trans2f::shear(-025.f, 0.3f)
    * Trans2f::rotation(Rot2f(degToRad(90.f)))
    * Trans2f::translation(Vec2f(-4.f, 7.f));
  tInv1 = inverse(t);
  tInv2 = t;
  tInv2.invert();

  HOU_EXPECT_CLOSE(identity, (t * tInv1), 1.e-6);
  HOU_EXPECT_CLOSE(identity, (t * tInv2), 1.e-6);

  t = Trans2f::rotation(Rot2f(degToRad(30.f)))
    * Trans2f::translation(Vec2f(-4.f, 7.f));
  tInv1 = inverse(t);
  tInv2 = t;
  tInv2.invert();

  HOU_EXPECT_CLOSE(identity, (t * tInv1), 1.e-6);
  HOU_EXPECT_CLOSE(identity, (t * tInv2), 1.e-6);
}



TEST_F(TestTransform2, Composition)
{
  Trans2f t1
    = Trans2f::scale(Vec2f(0.5f, -5.f))
    * Trans2f::shear(-2.f, 3.f)
    * Trans2f::rotation(Rot2f(degToRad(30.f)))
    * Trans2f::translation(Vec2f(-4.f, 7.f));
  Trans2f t2
    = Trans2f::scale(Vec2f(1.5f, 2.f))
    * Trans2f::shear(-1.5f, -4.f)
    * Trans2f::rotation(Rot2f(degToRad(-120.f)))
    * Trans2f::translation(Vec2f(11.f, 5.f));
  Trans2f t3 = t1;
  t3 *= t2;
  Trans2f t4 = t1 * t2;
  Mat4x4f tmRef = t1.toMat4x4() * t2.toMat4x4();

  HOU_EXPECT_FLOAT_CLOSE(tmRef, t3.toMat4x4());
  HOU_EXPECT_FLOAT_CLOSE(t3, t4);
}



TEST_F(TestTransform2, VectorTransformation)
{
  Trans2f t
    = Trans2f::scale(Vec2f(0.5f, -5.f))
    * Trans2f::shear(-2.f, 3.f)
    * Trans2f::rotation(Rot2f(degToRad(30.f)))
    * Trans2f::translation(Vec2f(-4.f, 7.f));
  Vec2f v(3.f, -13.f);
  v = t.transformVector(v);

  // Perform the transformation using the homogeneous transformation matrix
  // and a 4d vector and compare the results.
  // 4th element == 0 -> vector
  Matrix<float, 4, 1> hv{3.f, -13.f, 0.f, 0.f};
  hv = t.toMat4x4() * hv;
  Vec2f vRef(hv(0), hv(1));

  HOU_EXPECT_FLOAT_CLOSE(vRef, v);
}



TEST_F(TestTransform2, PointTransformation)
{
  Trans2f t
    = Trans2f::scale(Vec2f(0.5f, -5.f))
    * Trans2f::shear(-2.f, 3.f)
    * Trans2f::rotation(Rot2f(degToRad(30.f)))
    * Trans2f::translation(Vec2f(-4.f, 7.f));
  Vec2f v(3.f, -13.f);
  v = t.transformPoint(v);

  // Perform the transformation using the homogeneous transformation matrix
  // and a 4d point and compare the results.
  // 4th element == 1 -> point
  Matrix<float, 4, 1> hv{3.f, -13.f, 0.f, 1.f};
  hv = t.toMat4x4() * hv;
  Vec2f vRef(hv(0), hv(1));

  HOU_EXPECT_FLOAT_CLOSE(vRef, v);
}



TEST_F(TestTransform2, ComparisonOperators)
{
  Trans2f t1
    = Trans2f::rotation(Rot2f(degToRad(30.f)))
    * Trans2f::translation(Vec2f(-4.f, 7.f));
  Trans2f t2 = t1;
  Trans2f t3
    = Trans2f::rotation(Rot2f(degToRad(30.f)))
    * Trans2f::translation(Vec2f(-5.f, 7.f));
  Trans2f t4
    = Trans2f::rotation(Rot2f(degToRad(45.f)))
    * Trans2f::translation(Vec2f(-4.f, 7.f));

  EXPECT_TRUE(t1 == t2);
  EXPECT_FALSE(t1 == t3);
  EXPECT_FALSE(t1 == t4);
  EXPECT_FALSE(t1 != t2);
  EXPECT_TRUE(t1 != t3);
  EXPECT_TRUE(t1 != t4);
}



TEST_F(TestTransform2, FloatingPointComparison)
{
  Trans2f t1
    = Trans2f::scale(Vec2f(0.5f, -5.f))
    * Trans2f::shear(-2.f, 3.f)
    * Trans2f::rotation(Rot2f(degToRad(30.f)))
    * Trans2f::translation(Vec2f(-4.f, 7.f));
  Trans2f t2
    = Trans2f::scale(Vec2f(1.5f, 2.f))
    * Trans2f::shear(-1.5f, -4.f)
    * Trans2f::rotation(Rot2f(degToRad(-120.f)))
    * Trans2f::translation(Vec2f(11.f, 5.f));
  Trans2f t3 = t1;
  Trans2f t4
    = Trans2f::scale(Vec2f(0.5001f, -5.f))
    * Trans2f::shear(-2.f, 3.f)
    * Trans2f::rotation(Rot2f(degToRad(30.f)))
    * Trans2f::translation(Vec2f(-4.f, 7.f));

  EXPECT_FALSE(close(t1, t2));
  EXPECT_TRUE(close(t1, t3));
  EXPECT_TRUE(close(t1, t4, 1.e-2f));
  EXPECT_FALSE(close(t1, t4, 1.e-3f));
}



TEST_F(TestTransform2, Identity)
{
  HOU_EXPECT_FLOAT_CLOSE(Trans2f(), Trans2f::identity());
}



TEST_F(TestTransform2, OutputStreamOperator)
{
  Trans2f t
    = Trans2f::scale(Vec2f(2.f, 3.f))
    * Trans2f::shear(1.f, 1.f)
    * Trans2f::translation(Vec2f(2.f, 3.f));
  const char* output = "(2, 2, 0, 10)\n(3, 3, 0, 15)\n(0, 0, 1, 0)\n(0, 0, 0, 1)";

  HOU_EXPECT_OUTPUT(output, t);
}

