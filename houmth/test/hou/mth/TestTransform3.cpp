// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"

#include "hou/mth/MthUtils.hpp"
#include "hou/mth/Rectangle.hpp"
#include "hou/mth/Transform3.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestTransform3 : public Test {};

}



TEST_F(TestTransform3, DefaultConstructor)
{
  Trans3f t;
  Mat4x4f tmRef
  {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.toMat4x4());
}



TEST_F(TestTransform3, ConversionConstructor)
{
  Trans3d td;
  Trans3f tf(td);
  Mat4x4f tmRef
  {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, tf.toMat4x4());
}



TEST_F(TestTransform3, BuildTranslation)
{
  Trans3f t = Trans3f::translation(Vec3f(2.f, 3.f, 4.f));
  Mat4x4f tmRef
  {
    1.f, 0.f, 0.f, 2.f,
    0.f, 1.f, 0.f, 3.f,
    0.f, 0.f, 1.f, 4.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.toMat4x4());
}



TEST_F(TestTransform3, BuildRotationX)
{
  Trans3f tr = Trans3f::rotation(Rot3f::x(-PI_F / 6.f));
  Mat4x4f tmRef =
  {
    1.f,  0.f,           0.f,           0.f,
    0.f,  sqrt(3.f)/2.f, 0.5f,          0.f,
    0.f, -0.5f,          sqrt(3.f)/2.f, 0.f,
    0.f,  0.f,           0.f,           1.f,
  };
  HOU_EXPECT_CLOSE(tmRef, tr.toMat4x4(), 1.e-6f);
}



TEST_F(TestTransform3, BuildRotationY)
{
  Trans3f tr = Trans3f::rotation(Rot3f::y(-PI_F / 6.f));
  Mat4x4f tmRef =
  {
    sqrt(3.f)/2.f, 0.f, -0.5f,          0.f,
    0.f,           1.f,  0.f,           0.f,
    0.5f,          0.f,  sqrt(3.f)/2.f, 0.f,
    0.f,           0.f,  0.f,           1.f,
  };
  HOU_EXPECT_CLOSE(tmRef, tr.toMat4x4(), 1.e-6f);
}



TEST_F(TestTransform3, BuildRotationZ)
{
  Trans3f tr = Trans3f::rotation(Rot3f::z(-PI_F / 6.f));
  Mat4x4f tmRef =
  {
     sqrt(3.f)/2.f, 0.5f,          0.f, 0.f,
    -0.5f,          sqrt(3.f)/2.f, 0.f, 0.f,
     0.f,           0.f,           1.f, 0.f,
     0.f,           0.f,           0.f, 1.f,
  };
  HOU_EXPECT_CLOSE(tmRef, tr.toMat4x4(), 1.e-6f);
}



TEST_F(TestTransform3, BuildScale)
{
  Trans3f t = Trans3f::scale(Vec3f(2.f, 3.f, 4.f));
  Mat4x4f tmRef
  {
    2.f, 0.f, 0.f, 0.f,
    0.f, 3.f, 0.f, 0.f,
    0.f, 0.f, 4.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.toMat4x4());
}



TEST_F(TestTransform3, BuildShear)
{
  Trans3f t = Trans3f::shear(2.f, 3.f, 4.f, 5.f, 6.f, 7.f);
  Mat4x4f tmRef
  {
    1.f, 2.f, 3.f, 0.f,
    4.f, 1.f, 5.f, 0.f,
    6.f, 7.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };
  HOU_EXPECT_FLOAT_CLOSE(tmRef, t.toMat4x4());
}



TEST_F(TestTransform3, Inversion)
{
  Trans3f t;
  Trans3f tInv1;
  Trans3f tInv2;
  Trans3f identity;

  t = Trans3f::scale(Vec3f(0.5f, -1.f, 1.f))
    * Trans3f::shear(-025.f, 0.5f, 0.f, 0.f, 0.f, 0.f)
    * Trans3f::rotation(Rot3f(Vec3f(-4.f, 1.f, 0.5f) * degToRad(90.f)))
    * Trans3f::translation(Vec3f(-4.f, 7.f, 1.f));
  tInv1 = inverse(t);
  tInv2 = t;
  tInv2.invert();

  HOU_EXPECT_CLOSE(identity, (t * tInv1), 1.e-5);
  HOU_EXPECT_CLOSE(identity, (t * tInv2), 1.e-5);

  t = Trans3f::rotation(Rot3f::z(degToRad(30.f)))
    * Trans3f::translation(Vec3f(-4.f, 7.f, 9.f));
  tInv1 = inverse(t);
  tInv2 = t;
  tInv2.invert();

  HOU_EXPECT_CLOSE(identity, (t * tInv1), 1.e-6);
  HOU_EXPECT_CLOSE(identity, (t * tInv2), 1.e-6);
}



TEST_F(TestTransform3, Composition)
{
  Trans3f t1
    = Trans3f::scale(Vec3f(0.5f, -5.f, 1.2f))
    * Trans3f::shear(-2.f, 3.f, 4.f, 5.f, 0.5f, 0.3f)
    * Trans3f::rotation(Rot3f(Vec3f(1.f, 0.5f, -1.2f) * degToRad(30.f)))
    * Trans3f::translation(Vec3f(-4.f, 7.f, 0.1f));
  Trans3f t2
    = Trans3f::scale(Vec3f(1.5f, 2.f, 3.f))
    * Trans3f::shear(-1.5f, -4.f, 1.f, 1.f, 0.8f, 0.5f)
    * Trans3f::rotation(Rot3f::z(degToRad(-120.f)))
    * Trans3f::translation(Vec3f(11.f, 5.f, -1.f));
  Trans3f t3 = t1;
  t3 *= t2;
  Trans3f t4 = t1 * t2;
  Mat4x4f tmRef = t1.toMat4x4() * t2.toMat4x4();

  HOU_EXPECT_FLOAT_CLOSE(tmRef, t3.toMat4x4());
  HOU_EXPECT_FLOAT_CLOSE(t3, t4);
}



TEST_F(TestTransform3, VectorTransformation)
{
  Trans3f t
    = Trans3f::scale(Vec3f(0.5f, -5.f, 2.f))
    * Trans3f::shear(-2.f, 3.f, 1.f, -1.f, 2.f, 3.f)
    * Trans3f::rotation(Rot3f(Vec3f(0.f, 1.f, -0.5f) * degToRad(30.f)))
    * Trans3f::translation(Vec3f(-4.f, 7.f, 5.f));
  Vec3f v(3.f, -13.f, 10.f);
  v = t.transformVector(v);

  // Perform the transformation using the homogeneous transformation matrix
  // and a 4d vector and compare the results.
  // 4th element == 0 -> vector
  Mat4x1f hv{3.f, -13.f, 10.f, 0.f};
  hv = t.toMat4x4() * hv;
  Vec3f vRef(hv(0), hv(1), hv(2));

  HOU_EXPECT_FLOAT_CLOSE(vRef, v);
}



TEST_F(TestTransform3, PointTransformation)
{
  Trans3f t
    = Trans3f::scale(Vec3f(0.5f, -5.f, 2.f))
    * Trans3f::shear(-2.f, 3.f, 1.f, -1.f, 2.f, 3.f)
    * Trans3f::rotation(Rot3f(Vec3f(0.f, 1.f, -0.5f) * degToRad(30.f)))
    * Trans3f::translation(Vec3f(-4.f, 7.f, 5.f));
  Vec3f v(3.f, -13.f, 10.f);
  v = t.transformPoint(v);

  // Perform the transformation using the homogeneous transformation matrix
  // and a 4d point and compare the results.
  // 4th element == 1 -> point
  Mat4x1f hv{3.f, -13.f, 10.f, 1.f};
  hv = t.toMat4x4() * hv;
  Vec3f vRef(hv(0), hv(1), hv(2));

  HOU_EXPECT_FLOAT_CLOSE(vRef, v);
}



TEST_F(TestTransform3, ComparisonOperators)
{
  Trans3f t1
    = Trans3f::rotation(Rot3f::z(degToRad(30.f)))
    * Trans3f::translation(Vec3f(-4.f, 7.f, 0.f));
  Trans3f t2 = t1;
  Trans3f t3
    = Trans3f::rotation(Rot3f::z(degToRad(30.f)))
    * Trans3f::translation(Vec3f(-4.f, 8.f, 0.f));
  Trans3f t4
    = Trans3f::rotation(Rot3f::z(degToRad(45.f)))
    * Trans3f::translation(Vec3f(-4.f, 7.f, 0.f));

  EXPECT_TRUE(t1 == t2);
  EXPECT_FALSE(t1 == t3);
  EXPECT_FALSE(t1 == t4);
  EXPECT_FALSE(t1 != t2);
  EXPECT_TRUE(t1 != t3);
  EXPECT_TRUE(t1 != t4);
}



TEST_F(TestTransform3, FloatingPointComparison)
{
  Trans3f t1
    = Trans3f::scale(Vec3f(0.5f, -5.f, 2.f))
    * Trans3f::shear(-2.f, 3.f, 4.f, 5.f, 6.f, 7.f)
    * Trans3f::rotation(Rot3f::z(degToRad(30.f)))
    * Trans3f::translation(Vec3f(-4.f, 7.f, 0.f));
  Trans3f t2
    = Trans3f::scale(Vec3f(1.5f, 2.f, 2.f))
    * Trans3f::shear(-1.5f, -4.f, 3.f, 2.f, 1.f, 4.f)
    * Trans3f::rotation(Rot3f::z(degToRad(-120.f)))
    * Trans3f::translation(Vec3f(11.f, 5.f, 0.f));
  Trans3f t3 = t1;
  Trans3f t4
    = Trans3f::scale(Vec3f(0.5001f, -5.f, 2.0001f))
    * Trans3f::shear(-2.f, 3.f, 4.f, 5.f, 6.f, 7.f)
    * Trans3f::rotation(Rot3f::z(degToRad(30.f)))
    * Trans3f::translation(Vec3f(-4.f, 7.f, 0.f));

  EXPECT_FALSE(close(t1, t2));
  EXPECT_TRUE(close(t1, t3));
  EXPECT_TRUE(close(t1, t4, 1.e-2f));
  EXPECT_FALSE(close(t1, t4, 1.e-3f));
}



TEST_F(TestTransform3, Identity)
{
  HOU_EXPECT_FLOAT_CLOSE(Trans3f(), Trans3f::identity());
}



TEST_F(TestTransform3, OutputStreamOperator)
{
  Trans3f t
    = Trans3f::scale(Vec3f(2.f, 3.f, 4.f))
    * Trans3f::shear(1.f, 1.f, 2.f, 2.f, 3.f, 3.f)
    * Trans3f::translation(Vec3f(2.f, 3.f, 4.f));
  const char* output = "(2, 2, 2, 18)\n(6, 3, 6, 45)\n(12, 12, 4, 76)\n(0, 0, 0, 1)";
  HOU_EXPECT_OUTPUT(output, t);
}

