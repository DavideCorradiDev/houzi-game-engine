#include "hou/Test.hpp"

#include "hou/cor/cor_error.hpp"

#include "hou/mth/quaternion.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestQuaternion : public Test {};
class TestQuaternionDeathTest : public TestQuaternion {};

}



TEST_F(TestQuaternion, DefaultConstructor)
{
  quatf q;
  EXPECT_FLOAT_EQ(0.f, q.x());
  EXPECT_FLOAT_EQ(0.f, q.y());
  EXPECT_FLOAT_EQ(0.f, q.z());
  EXPECT_FLOAT_EQ(0.f, q.w());
}



TEST_F(TestQuaternion, ElementConstructor)
{
  quatf q(1.f, 2.f, 3.f, 4.f);
  EXPECT_FLOAT_EQ(1.f, q.x());
  EXPECT_FLOAT_EQ(2.f, q.y());
  EXPECT_FLOAT_EQ(3.f, q.z());
  EXPECT_FLOAT_EQ(4.f, q.w());
}



TEST_F(TestQuaternion, InitializerListConstructor)
{
  quatf q{1.f, 2.f, 3.f, 4.f};
  EXPECT_FLOAT_EQ(1.f, q.x());
  EXPECT_FLOAT_EQ(2.f, q.y());
  EXPECT_FLOAT_EQ(3.f, q.z());
  EXPECT_FLOAT_EQ(4.f, q.w());
}



TEST_F(TestQuaternion, ConversionConstructor)
{
  quatd qd{1., 2., 3., 4.};
  quatf qf(qd);
  EXPECT_FLOAT_EQ(1.f, qf.x());
  EXPECT_FLOAT_EQ(2.f, qf.y());
  EXPECT_FLOAT_EQ(3.f, qf.z());
  EXPECT_FLOAT_EQ(4.f, qf.w());
}



TEST_F(TestQuaternionDeathTest, InitializerListConstructorWrongSize)
{
  HOU_EXPECT_ERROR(quatf q({1.f, 2.f, 3.f}), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(quatf q({1.f, 2.f, 3.f, 4.f, 5.f}), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestQuaternion, ElementAccessOperators)
{
  quatf q{1.f, 2.f, 3.f, 4.f};
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
  quatf q{1.f, 2.f, 3.f, 4.f};
  float dataRef[] = {1.f, 2.f, 3.f, 4.f};
  HOU_EXPECT_ARRAY_FLOAT_CLOSE(dataRef, q.data(), 4u);
}



TEST_F(TestQuaternion, ComparisonOperators)
{
  quatf q1(1.f, 2.f, 3.f, 4.f);
  quatf q2 = q1;
  quatf q3(0.f, 2.f, 3.f, 4.f);
  quatf q4(1.f, 5.f, 3.f, 4.f);
  quatf q5(1.f, 2.f, 9.f, 4.f);
  quatf q6(1.f, 2.f, 3.f, -4.f);

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
  quatf q1(1.f, 2.3456f, 3.f, 4.5678f);
  quatf q2 = q1;
  quatf q3(1.f, 2.3457f, 3.f, 4.5678f);
  quatf q4(1.f, 2.3457f, 3.f, 4.5578f);

  EXPECT_TRUE(close(q1, q2));
  EXPECT_TRUE(close(q1, q3, 1e-3f));
  EXPECT_FALSE(close(q1, q3, 1e-4f));
  EXPECT_TRUE(close(q1, q4, 1e-1f));
  EXPECT_FALSE(close(q1, q4, 1e-2f));
}



TEST_F(TestQuaternion, Addition)
{
  quatf q1(1.f, 2.f, 3.f, 4.f);
  quatf q2(5.f, -1.f, 5.f, 7.f);
  EXPECT_EQ(quatf(6.f, 1.f, 8.f, 11.f), q1 + q2);
  q1 += q2;
  EXPECT_EQ(quatf(6.f, 1.f, 8.f, 11.f), q1);
}



TEST_F(TestQuaternion, Subtraction)
{
  quatf q1(1.f, 2.f, 3.f, 4.f);
  quatf q2(5.f, -1.f, 5.f, 7.f);
  EXPECT_EQ(quatf(-4.f, 3.f, -2.f, -3.f), q1 - q2);
  q1 -= q2;
  EXPECT_EQ(quatf(-4.f, 3.f, -2.f, -3.f), q1);
}



TEST_F(TestQuaternion, Opposite)
{
  quatf q1(1.f, 2.f, 3.f, -4.f);
  EXPECT_EQ(quatf(-1.f, -2.f, -3.f, 4.f), -q1);
}



TEST_F(TestQuaternion, Multiplication)
{
  quatf q1(1.f, 2.f, 3.f, 4.f);
  quatf q2(5.f, -1.f, 5.f, 7.f);
  EXPECT_EQ(quatf(40.f, 20.f, 30.f, 10.f), q1 * q2);
  q1 *= q2;
  EXPECT_EQ(quatf(40.f, 20.f, 30.f, 10.f), q1);
}



TEST_F(TestQuaternion, ScalarMultiplication)
{
  quatf q(1.f, 2.f, -3.f, 4.f);
  EXPECT_EQ(quatf(2.f, 4.f, -6.f, 8.f), q * 2.f);
  EXPECT_EQ(quatf(2.f, 4.f, -6.f, 8.f), 2.f * q);
  q *= 2.f;
  EXPECT_EQ(quatf(2.f, 4.f, -6.f, 8.f), q);
}



TEST_F(TestQuaternion, MixedScalarMultiplication)
{
  quatf q(1.f, 2.f, -3.f, 4.f);
  EXPECT_EQ(quatf(2.f, 4.f, -6.f, 8.f), q * 2);
  EXPECT_EQ(quatf(2.f, 4.f, -6.f, 8.f), 2 * q);
  q *= 2;
  EXPECT_EQ(quatf(2.f, 4.f, -6.f, 8.f), q);
}



TEST_F(TestQuaternion, ScalarDivision)
{
  quatf q(1.f, 2.f, -3.f, 4.f);
  EXPECT_EQ(quatf(0.5f, 1.f, -1.5f, 2.f), q / 2.f);
  q /= 2.f;
  EXPECT_EQ(quatf(0.5f, 1.f, -1.5f, 2.f), q);
}



TEST_F(TestQuaternion, MixedScalarDivision)
{
  quatf q(1.f, 2.f, -3.f, 4.f);
  EXPECT_EQ(quatf(0.5f, 1.f, -1.5f, 2.f), q / 2);
  q /= 2;
  EXPECT_EQ(quatf(0.5f, 1.f, -1.5f, 2.f), q);
}



TEST_F(TestQuaternion, Inversion)
{
  quatf q(2.f, -1.f, -3.f, 4.f);
  quatf qInv = inverse(q);
  HOU_EXPECT_FLOAT_CLOSE(quatf(-2.f, 1.f, 3.f, 4.f) / 30.f, qInv);
  HOU_EXPECT_FLOAT_CLOSE(quatf::identity(), q * qInv);
  q.invert();
  HOU_EXPECT_FLOAT_CLOSE(quatf(-2.f, 1.f, 3.f, 4.f) / 30.f, q);
}



TEST_F(TestQuaternion, InversionFailureNullDeterminant)
{
  quatf q;
  HOU_EXPECT_ERROR(inverse(q), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestQuaternion, Conjugation)
{
  quatf q(2.f, 4.f, 5.f, -6.f);
  quatf qConj = conjugate(q);
  HOU_EXPECT_FLOAT_CLOSE(quatf(-2.f, -4.f, -5.f, -6.f), qConj);
  q.conjugate();
  HOU_EXPECT_FLOAT_CLOSE(quatf(-2.f, -4.f, -5.f, -6.f), q);
}



TEST_F(TestQuaternion, Norm)
{
  quatf q(2.f, 4.f, 5.f, -6.f);
  EXPECT_FLOAT_EQ(81.f, square_norm(q));
  EXPECT_FLOAT_EQ(9.f, norm(q));
}



TEST_F(TestQuaternion, Normalization)
{
  quatf q(2.f, 4.f, 5.f, -6.f);

  quatf qNorm = normalized(q);
  HOU_EXPECT_FLOAT_CLOSE(q / 9.f, qNorm);
  EXPECT_FLOAT_EQ(1.f, square_norm(qNorm));
  EXPECT_FLOAT_EQ(1.f, norm(qNorm));

  q.normalize();
  HOU_EXPECT_FLOAT_CLOSE(qNorm, q);
  EXPECT_FLOAT_EQ(1.f, square_norm(q));
  EXPECT_FLOAT_EQ(1.f, norm(q));
}



TEST_F(TestQuaternion, NormalizationFailureNullNorm)
{
  HOU_EXPECT_ERROR(normalized(quatf::zero()), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestQuaternion, zero)
{
  HOU_EXPECT_FLOAT_CLOSE(quatf(0.f, 0.f, 0.f, 0.f), quatf::zero());
}



TEST_F(TestQuaternion, Identity)
{
  HOU_EXPECT_FLOAT_CLOSE(quatf(0.f, 0.f, 0.f, 1.f), quatf::identity());
}



TEST_F(TestQuaternion, OutputStreamOperator)
{
  quatf q{1.f, 2.f, 3.f, 4.f};
  HOU_EXPECT_OUTPUT("(1,2,3,4)", q);
}

