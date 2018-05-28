#include "hou/test.hpp"

#include "hou/mth/quaternion.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_quaternion : public Test
{};

class test_quaternion_death_test : public test_quaternion
{};

}  // namespace



TEST_F(test_quaternion, default_constructor)
{
  quatf q;
  EXPECT_FLOAT_EQ(0.f, q.x());
  EXPECT_FLOAT_EQ(0.f, q.y());
  EXPECT_FLOAT_EQ(0.f, q.z());
  EXPECT_FLOAT_EQ(0.f, q.w());
}



TEST_F(test_quaternion, element_constructor)
{
  quatf q(1.f, 2.f, 3.f, 4.f);
  EXPECT_FLOAT_EQ(1.f, q.x());
  EXPECT_FLOAT_EQ(2.f, q.y());
  EXPECT_FLOAT_EQ(3.f, q.z());
  EXPECT_FLOAT_EQ(4.f, q.w());
}



TEST_F(test_quaternion, conversion_constructor)
{
  quatd qd{1., 2., 3., 4.};
  quatf qf(qd);
  EXPECT_FLOAT_EQ(1.f, qf.x());
  EXPECT_FLOAT_EQ(2.f, qf.y());
  EXPECT_FLOAT_EQ(3.f, qf.z());
  EXPECT_FLOAT_EQ(4.f, qf.w());
}



TEST_F(test_quaternion, element_access_operators)
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



TEST_F(test_quaternion, data)
{
  quatf q{1.f, 2.f, 3.f, 4.f};
  float data_ref[] = {1.f, 2.f, 3.f, 4.f};
  EXPECT_ARRAY_FLOAT_CLOSE(data_ref, q.data(), 4u);
}



TEST_F(test_quaternion, comparison_operators)
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



TEST_F(test_quaternion, floating_point_comparison)
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



TEST_F(test_quaternion, addition)
{
  quatf q1(1.f, 2.f, 3.f, 4.f);
  quatf q2(5.f, -1.f, 5.f, 7.f);
  EXPECT_EQ(quatf(6.f, 1.f, 8.f, 11.f), q1 + q2);
  q1 += q2;
  EXPECT_EQ(quatf(6.f, 1.f, 8.f, 11.f), q1);
}



TEST_F(test_quaternion, subtraction)
{
  quatf q1(1.f, 2.f, 3.f, 4.f);
  quatf q2(5.f, -1.f, 5.f, 7.f);
  EXPECT_EQ(quatf(-4.f, 3.f, -2.f, -3.f), q1 - q2);
  q1 -= q2;
  EXPECT_EQ(quatf(-4.f, 3.f, -2.f, -3.f), q1);
}



TEST_F(test_quaternion, opposite)
{
  quatf q1(1.f, 2.f, 3.f, -4.f);
  EXPECT_EQ(quatf(-1.f, -2.f, -3.f, 4.f), -q1);
}



TEST_F(test_quaternion, multiplication)
{
  quatf q1(1.f, 2.f, 3.f, 4.f);
  quatf q2(5.f, -1.f, 5.f, 7.f);
  EXPECT_EQ(quatf(40.f, 20.f, 30.f, 10.f), q1 * q2);
  q1 *= q2;
  EXPECT_EQ(quatf(40.f, 20.f, 30.f, 10.f), q1);
}



TEST_F(test_quaternion, scalar_multiplication)
{
  quatf q(1.f, 2.f, -3.f, 4.f);
  EXPECT_EQ(quatf(2.f, 4.f, -6.f, 8.f), q * 2.f);
  EXPECT_EQ(quatf(2.f, 4.f, -6.f, 8.f), 2.f * q);
  q *= 2.f;
  EXPECT_EQ(quatf(2.f, 4.f, -6.f, 8.f), q);
}



TEST_F(test_quaternion, mixed_scalar_multiplication)
{
  quatf q(1.f, 2.f, -3.f, 4.f);
  EXPECT_EQ(quatf(2.f, 4.f, -6.f, 8.f), q * 2);
  EXPECT_EQ(quatf(2.f, 4.f, -6.f, 8.f), 2 * q);
  q *= 2;
  EXPECT_EQ(quatf(2.f, 4.f, -6.f, 8.f), q);
}



TEST_F(test_quaternion, scalar_division)
{
  quatf q(1.f, 2.f, -3.f, 4.f);
  EXPECT_EQ(quatf(0.5f, 1.f, -1.5f, 2.f), q / 2.f);
  q /= 2.f;
  EXPECT_EQ(quatf(0.5f, 1.f, -1.5f, 2.f), q);
}



TEST_F(test_quaternion, mixed_scalar_division)
{
  quatf q(1.f, 2.f, -3.f, 4.f);
  EXPECT_EQ(quatf(0.5f, 1.f, -1.5f, 2.f), q / 2);
  q /= 2;
  EXPECT_EQ(quatf(0.5f, 1.f, -1.5f, 2.f), q);
}



TEST_F(test_quaternion, inverse)
{
  quatf q(2.f, -1.f, -3.f, 4.f);
  quatf qInv = inverse(q);
  EXPECT_FLOAT_CLOSE(quatf(-2.f, 1.f, 3.f, 4.f) / 30.f, qInv);
  EXPECT_FLOAT_CLOSE(quatf::identity(), q * qInv);
  q.invert();
  EXPECT_FLOAT_CLOSE(quatf(-2.f, 1.f, 3.f, 4.f) / 30.f, q);
}



TEST_F(test_quaternion, inverse_failure_null_determinant)
{
  quatf q;
  EXPECT_ERROR_0(inverse(q), inversion_error);
  EXPECT_ERROR_0(q.invert(), inversion_error);
}



TEST_F(test_quaternion, conjugation)
{
  quatf q(2.f, 4.f, 5.f, -6.f);
  quatf q_conj = conjugate(q);
  EXPECT_FLOAT_CLOSE(quatf(-2.f, -4.f, -5.f, -6.f), q_conj);
  q.conjugate();
  EXPECT_FLOAT_CLOSE(quatf(-2.f, -4.f, -5.f, -6.f), q);
}



TEST_F(test_quaternion, norm)
{
  quatf q(2.f, 4.f, 5.f, -6.f);
  EXPECT_FLOAT_EQ(81.f, square_norm(q));
  EXPECT_FLOAT_EQ(9.f, norm(q));
}



TEST_F(test_quaternion, normalization)
{
  quatf q(2.f, 4.f, 5.f, -6.f);

  quatf q_norm = normalized(q);
  EXPECT_FLOAT_CLOSE(q / 9.f, q_norm);
  EXPECT_FLOAT_EQ(1.f, square_norm(q_norm));
  EXPECT_FLOAT_EQ(1.f, norm(q_norm));

  q.normalize();
  EXPECT_FLOAT_CLOSE(q_norm, q);
  EXPECT_FLOAT_EQ(1.f, square_norm(q));
  EXPECT_FLOAT_EQ(1.f, norm(q));
}



TEST_F(test_quaternion, normalization_failure_null_norm)
{
  EXPECT_PRECOND_ERROR(normalized(quatf::zero()));
}



TEST_F(test_quaternion, zero)
{
  EXPECT_FLOAT_CLOSE(quatf(0.f, 0.f, 0.f, 0.f), quatf::zero());
}



TEST_F(test_quaternion, identity)
{
  EXPECT_FLOAT_CLOSE(quatf(0.f, 0.f, 0.f, 1.f), quatf::identity());
}



TEST_F(test_quaternion, output_stream_operator)
{
  quatf q{1.f, 2.f, 3.f, 4.f};
  EXPECT_OUTPUT("(1,2,3,4)", q);
}
