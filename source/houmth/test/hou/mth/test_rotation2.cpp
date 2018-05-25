#include "hou/Test.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/matrix.hpp"
#include "hou/mth/rotation2.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_rotation2 : public Test
{};

class test_rotation2_death_test : public test_rotation2
{};

}  // namespace



TEST_F(test_rotation2, default_constructor)
{
  rot2f r;
  EXPECT_FLOAT_CLOSE(0.f, r.get_angle());
  EXPECT_FLOAT_CLOSE(mat2x2f::identity(), r.get_matrix());
}



TEST_F(test_rotation2, constructor_angle)
{
  float angle_ref = pi_f / 2.f;
  mat2x2f m_ref(0.f, -1.f, 1.f, 0.f);
  rot2f r(angle_ref);
  EXPECT_FLOAT_CLOSE(angle_ref, r.get_angle());
  EXPECT_FLOAT_CLOSE(m_ref, r.get_matrix());
}



TEST_F(test_rotation2, constructor_angle_overflow)
{
  float angle_ref = -pi_f / 2.f;
  mat2x2f m_ref(0.f, 1.f, -1.f, 0.f);
  rot2f r(3.f * pi_f / 2.f);
  EXPECT_CLOSE(angle_ref, r.get_angle(), 1.e-6f);
  EXPECT_CLOSE(m_ref, r.get_matrix(), 1.e-6f);
}



TEST_F(test_rotation2, constructor_angle_underflow)
{
  float angle_ref = pi_f / 2.f;
  mat2x2f m_ref(0.f, -1.f, 1.f, 0.f);
  rot2f r(-3.f * pi_f / 2.f);
  EXPECT_CLOSE(angle_ref, r.get_angle(), 1.e-6f);
  EXPECT_CLOSE(m_ref, r.get_matrix(), 1.e-6f);
}



TEST_F(test_rotation2, constructor_matrix)
{
  float angle_ref = pi_f / 2.f;
  mat2x2f m_ref(0.f, -1.f, 1.f, 0.f);
  rot2f r(m_ref);
  EXPECT_FLOAT_CLOSE(angle_ref, r.get_angle());
  EXPECT_FLOAT_CLOSE(m_ref, r.get_matrix());
}



TEST_F(test_rotation2_death_test, constructor_matrix_failure_invalid_matrix)
{
  EXPECT_PRECOND_ERROR(rot2f r(mat2x2f::zero()));
}



TEST_F(test_rotation2, conversion_constructor)
{
  rot2d rd;
  rot2f rf;
  EXPECT_FLOAT_CLOSE(0.f, rf.get_angle());
  EXPECT_FLOAT_CLOSE(mat2x2f::identity(), rf.get_matrix());
}



TEST_F(test_rotation2, comparison_operators)
{
  rot2f r1(pi_f / 6.f);
  rot2f r2(r1);
  rot2f r3(-pi_f / 3.f);

  EXPECT_TRUE(r1 == r2);
  EXPECT_FALSE(r1 == r3);
  EXPECT_FALSE(r1 != r2);
  EXPECT_TRUE(r1 != r3);
}



TEST_F(test_rotation2, floating_point_comparison)
{
  rot2f r1(0.23456f);
  rot2f r2(r1);
  rot2f r3(0.234561f);
  rot2f r4(0.23556f);

  EXPECT_TRUE(close(r1, r2));
  EXPECT_FALSE(close(r1, r3));
  EXPECT_FALSE(close(r1, r4));
  EXPECT_TRUE(close(r1, r2, 1.e-5f));
  EXPECT_TRUE(close(r1, r3, 1.e-5f));
  EXPECT_FALSE(close(r1, r4, 1.e-5f));
  EXPECT_TRUE(close(r1, r2, 1.e-2f));
  EXPECT_TRUE(close(r1, r3, 1.e-2f));
  EXPECT_TRUE(close(r1, r4, 1.e-2f));
}



TEST_F(test_rotation2, multiplication)
{
  rot2f r1(pi_f / 4.f);
  rot2f r2(pi_f);
  rot2f r_ref(-3.f * pi_f / 4.f);
  EXPECT_FLOAT_CLOSE(r_ref, r1 * r2);
  r1 *= r2;
  EXPECT_FLOAT_CLOSE(r_ref, r1);
}



TEST_F(test_rotation2, inversion)
{
  rot2f r(pi_f / 4.f);
  rot2f r_inv_ref(-pi_f / 4.f);
  rot2f r_inv = inverse(r);
  EXPECT_FLOAT_CLOSE(r_inv_ref, r_inv);
  EXPECT_FLOAT_CLOSE(rot2f::identity(), r_inv * r);
  r.invert();
  EXPECT_FLOAT_CLOSE(r_inv_ref, r);
}



TEST_F(test_rotation2, output_stream_operator)
{
  rot2f r(0.5f);
  EXPECT_OUTPUT("{angle = 0.5}", r);
}
