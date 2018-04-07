#include "hou/Test.hpp"

#include "hou/cor/CorError.hpp"

#include "hou/mth/Quaternion.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestQuaternion : public Test {};
class TestQuaternionDeathTest : public TestQuaternion {};

}



TEST_F(TestQuaternion, DefaultConstructor)
{
  Quatf q;
  EXPECT_FLOAT_EQ(0.f, q.x());
  EXPECT_FLOAT_EQ(0.f, q.y());
  EXPECT_FLOAT_EQ(0.f, q.z());
  EXPECT_FLOAT_EQ(0.f, q.w());
}



TEST_F(TestQuaternion, ElementConstructor)
{
  Quatf q(1.f, 2.f, 3.f, 4.f);
  EXPECT_FLOAT_EQ(1.f, q.x());
  EXPECT_FLOAT_EQ(2.f, q.y());
  EXPECT_FLOAT_EQ(3.f, q.z());
  EXPECT_FLOAT_EQ(4.f, q.w());
}



TEST_F(TestQuaternion, InitializerListConstructor)
{
  Quatf q{1.f, 2.f, 3.f, 4.f};
  EXPECT_FLOAT_EQ(1.f, q.x());
  EXPECT_FLOAT_EQ(2.f, q.y());
  EXPECT_FLOAT_EQ(3.f, q.z());
  EXPECT_FLOAT_EQ(4.f, q.w());
}



TEST_F(TestQuaternion, ConversionConstructor)
{
  Quatd qd{1., 2., 3., 4.};
  Quatf qf(qd);
  EXPECT_FLOAT_EQ(1.f, qf.x());
  EXPECT_FLOAT_EQ(2.f, qf.y());
  EXPECT_FLOAT_EQ(3.f, qf.z());
  EXPECT_FLOAT_EQ(4.f, qf.w());
}



TEST_F(TestQuaternionDeathTest, InitializerListConstructorWrongSize)
{
  HOU_EXPECT_ERROR(Quatf q({1.f, 2.f, 3.f}), std::logic_error
    , getText(CorError::Precondition));
  HOU_EXPECT_ERROR(Quatf q({1.f, 2.f, 3.f, 4.f, 5.f}), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestQuaternion, ElementAccessOperators)
{
  Quatf q{1.f, 2.f, 3.f, 4.f};
  q.x() = 5.f;
  q.y() = 6.f;
  q.z() = 7.f;
  q.w() = 8.f;
  EXPECT_FLOAT_EQ(5.f, q.x());
  EXPECT_FLOAT_EQ(6.f, q.y());
  EXPECT_FLOAT_EQ(7.f, q.z());
  EXPECT_FLOAT_EQ(8.f, q.w());
}



TEST_F(TestQuaternion, Data)
{
  Quatf q{1.f, 2.f, 3.f, 4.f};
  float dataRef[] = {1.f, 2.f, 3.f, 4.f};
  HOU_EXPECT_ARRAY_FLOAT_CLOSE(dataRef, q.data(), 4u);
}



TEST_F(TestQuaternion, ComparisonOperators)
{
  Quatf q1(1.f, 2.f, 3.f, 4.f);
  Quatf q2 = q1;
  Quatf q3(0.f, 2.f, 3.f, 4.f);
  Quatf q4(1.f, 5.f, 3.f, 4.f);
  Quatf q5(1.f, 2.f, 9.f, 4.f);
  Quatf q6(1.f, 2.f, 3.f, -4.f);

  EXPECT_TRUE(q1 == q2);
  EXPECT_FALSE(q1 == q3);
  EXPECT_FALSE(q1 == q4);
  EXPECT_FALSE(q1 == q5);
  EXPECT_FALSE(q1 == q6);
  EXPECT_FALSE(q1 != q2);
  EXPECT_TRUE(q1 != q3);
  EXPECT_TRUE(q1 != q4);
  EXPECT_TRUE(q1 != q5);
  EXPECT_TRUE(q1 != q6);
}



TEST_F(TestQuaternion, FloatingPointComparison)
{
  Quatf q1(1.f, 2.3456f, 3.f, 4.5678f);
  Quatf q2 = q1;
  Quatf q3(1.f, 2.3457f, 3.f, 4.5678f);
  Quatf q4(1.f, 2.3457f, 3.f, 4.5578f);

  EXPECT_TRUE(close(q1, q2));
  EXPECT_TRUE(close(q1, q3, 1e-3f));
  EXPECT_FALSE(close(q1, q3, 1e-4f));
  EXPECT_TRUE(close(q1, q4, 1e-1f));
  EXPECT_FALSE(close(q1, q4, 1e-2f));
}



TEST_F(TestQuaternion, Addition)
{
  Quatf q1(1.f, 2.f, 3.f, 4.f);
  Quatf q2(5.f, -1.f, 5.f, 7.f);
  EXPECT_EQ(Quatf(6.f, 1.f, 8.f, 11.f), q1 + q2);
  q1 += q2;
  EXPECT_EQ(Quatf(6.f, 1.f, 8.f, 11.f), q1);
}



TEST_F(TestQuaternion, Subtraction)
{
  Quatf q1(1.f, 2.f, 3.f, 4.f);
  Quatf q2(5.f, -1.f, 5.f, 7.f);
  EXPECT_EQ(Quatf(-4.f, 3.f, -2.f, -3.f), q1 - q2);
  q1 -= q2;
  EXPECT_EQ(Quatf(-4.f, 3.f, -2.f, -3.f), q1);
}



TEST_F(TestQuaternion, Opposite)
{
  Quatf q1(1.f, 2.f, 3.f, -4.f);
  EXPECT_EQ(Quatf(-1.f, -2.f, -3.f, 4.f), -q1);
}



TEST_F(TestQuaternion, Multiplication)
{
  Quatf q1(1.f, 2.f, 3.f, 4.f);
  Quatf q2(5.f, -1.f, 5.f, 7.f);
  EXPECT_EQ(Quatf(40.f, 20.f, 30.f, 10.f), q1 * q2);
  q1 *= q2;
  EXPECT_EQ(Quatf(40.f, 20.f, 30.f, 10.f), q1);
}



TEST_F(TestQuaternion, ScalarMultiplication)
{
  Quatf q(1.f, 2.f, -3.f, 4.f);
  EXPECT_EQ(Quatf(2.f, 4.f, -6.f, 8.f), q * 2.f);
  EXPECT_EQ(Quatf(2.f, 4.f, -6.f, 8.f), 2.f * q);
  q *= 2.f;
  EXPECT_EQ(Quatf(2.f, 4.f, -6.f, 8.f), q);
}



TEST_F(TestQuaternion, MixedScalarMultiplication)
{
  Quatf q(1.f, 2.f, -3.f, 4.f);
  EXPECT_EQ(Quatf(2.f, 4.f, -6.f, 8.f), q * 2);
  EXPECT_EQ(Quatf(2.f, 4.f, -6.f, 8.f), 2 * q);
  q *= 2;
  EXPECT_EQ(Quatf(2.f, 4.f, -6.f, 8.f), q);
}



TEST_F(TestQuaternion, ScalarDivision)
{
  Quatf q(1.f, 2.f, -3.f, 4.f);
  EXPECT_EQ(Quatf(0.5f, 1.f, -1.5f, 2.f), q / 2.f);
  q /= 2.f;
  EXPECT_EQ(Quatf(0.5f, 1.f, -1.5f, 2.f), q);
}



TEST_F(TestQuaternion, MixedScalarDivision)
{
  Quatf q(1.f, 2.f, -3.f, 4.f);
  EXPECT_EQ(Quatf(0.5f, 1.f, -1.5f, 2.f), q / 2);
  q /= 2;
  EXPECT_EQ(Quatf(0.5f, 1.f, -1.5f, 2.f), q);
}



TEST_F(TestQuaternion, Inversion)
{
  Quatf q(2.f, -1.f, -3.f, 4.f);
  Quatf qInv = inverse(q);
  HOU_EXPECT_FLOAT_CLOSE(Quatf(-2.f, 1.f, 3.f, 4.f) / 30.f, qInv);
  HOU_EXPECT_FLOAT_CLOSE(Quatf::identity(), q * qInv);
  q.invert();
  HOU_EXPECT_FLOAT_CLOSE(Quatf(-2.f, 1.f, 3.f, 4.f) / 30.f, q);
}



TEST_F(TestQuaternion, InversionFailureNullDeterminant)
{
  Quatf q;
  HOU_EXPECT_ERROR(inverse(q), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestQuaternion, Conjugation)
{
  Quatf q(2.f, 4.f, 5.f, -6.f);
  Quatf qConj = conjugate(q);
  HOU_EXPECT_FLOAT_CLOSE(Quatf(-2.f, -4.f, -5.f, -6.f), qConj);
  q.conjugate();
  HOU_EXPECT_FLOAT_CLOSE(Quatf(-2.f, -4.f, -5.f, -6.f), q);
}



TEST_F(TestQuaternion, Norm)
{
  Quatf q(2.f, 4.f, 5.f, -6.f);
  EXPECT_FLOAT_EQ(81.f, squareNorm(q));
  EXPECT_FLOAT_EQ(9.f, norm(q));
}



TEST_F(TestQuaternion, Normalization)
{
  Quatf q(2.f, 4.f, 5.f, -6.f);

  Quatf qNorm = normalized(q);
  HOU_EXPECT_FLOAT_CLOSE(q / 9.f, qNorm);
  EXPECT_FLOAT_EQ(1.f, squareNorm(qNorm));
  EXPECT_FLOAT_EQ(1.f, norm(qNorm));

  q.normalize();
  HOU_EXPECT_FLOAT_CLOSE(qNorm, q);
  EXPECT_FLOAT_EQ(1.f, squareNorm(q));
  EXPECT_FLOAT_EQ(1.f, norm(q));
}



TEST_F(TestQuaternion, NormalizationFailureNullNorm)
{
  HOU_EXPECT_ERROR(normalized(Quatf::zero()), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestQuaternion, Zero)
{
  HOU_EXPECT_FLOAT_CLOSE(Quatf(0.f, 0.f, 0.f, 0.f), Quatf::zero());
}



TEST_F(TestQuaternion, Identity)
{
  HOU_EXPECT_FLOAT_CLOSE(Quatf(0.f, 0.f, 0.f, 1.f), Quatf::identity());
}



TEST_F(TestQuaternion, OutputStreamOperator)
{
  Quatf q{1.f, 2.f, 3.f, 4.f};
  HOU_EXPECT_OUTPUT("(1,2,3,4)", q);
}

