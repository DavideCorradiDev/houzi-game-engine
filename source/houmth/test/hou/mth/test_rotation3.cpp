// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/matrix.hpp"
#include "hou/mth/rotation3.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_rotation3 : public Test
{};

class test_rotation3_param_f
  : public test_rotation3
  , public WithParamInterface<float>
{};

class test_rotation3_death_test : public test_rotation3
{};

}  // namespace



TEST_F(test_rotation3, default_constructor)
{
  rot3f r;
  HOU_EXPECT_FLOAT_CLOSE(quatf::identity(), r.get_quaternion());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), r.get_vector());
  HOU_EXPECT_FLOAT_CLOSE(mat3x3f::identity(), r.get_matrix());
}



TEST_F(test_rotation3, constructor_quaternion)
{
  quatf quat_ref(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  vec3f vec_ref(0.4275166f, -0.4275166f, 0.8550332f);
  // clang-format off
  mat3x3f mat_ref
    ( 0.5833333f, -0.7904401f, -0.1868867f
    , 0.6237735f, 0.5833333f, -0.52022f
    , 0.52022f, 0.1868867f, 0.8333333f);
  // clang-format on

  rot3f r_quat(quat_ref);
  HOU_EXPECT_CLOSE(quat_ref, r_quat.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vec_ref, r_quat.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(mat_ref, r_quat.get_matrix(), 1.e-6f);
}



TEST_F(test_rotation3, constructor_non_unit_quaternion)
{
  quatf quat(2.f, 4.f, 5.f, -6.f);
  EXPECT_FLOAT_EQ(9.f, norm(quat));

  rot3f r(quat);
  HOU_EXPECT_FLOAT_CLOSE(normalized(quat), r.get_quaternion());
}



TEST_F(test_rotation3_death_test, constructor_failure_zero_quaternion)
{
  HOU_EXPECT_ERROR(
    rot3f(quatf::zero()), std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(test_rotation3, constructor_vector)
{
  quatf quat_ref(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  vec3f vec_ref(0.4275166f, -0.4275166f, 0.8550332f);
  // clang-format off
  mat3x3f mat_ref
    ( 0.5833333f, -0.7904401f, -0.1868867f
    , 0.6237735f, 0.5833333f, -0.52022f
    , 0.52022f, 0.1868867f, 0.8333333f);
  // clang-format on

  rot3f r_vec(vec_ref);
  HOU_EXPECT_CLOSE(quat_ref, r_vec.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vec_ref, r_vec.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(mat_ref, r_vec.get_matrix(), 1.e-6f);
}



TEST_F(test_rotation3, constructor_matrix)
{
  quatf quat_ref(0.f, 0.f, -0.7071068f, 0.7071068f);
  vec3f vec_ref(0.f, 0.f, -1.5707963f);
  mat3x3f mat_ref(0.f, 1.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f, 1.f);

  rot3f r_mat(mat_ref);
  HOU_EXPECT_CLOSE(quat_ref, r_mat.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vec_ref, r_mat.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(mat_ref, r_mat.get_matrix(), 1.e-6f);
}



TEST_F(test_rotation3, constructor_matrix_null_root_function)
{
  quatf quat_ref(0.f, 1.f, 0.f, 0.f);
  vec3f vec_ref(0.f, pi_f, 0.f);
  mat3x3f mat_ref(-1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f);

  rot3f r_mat(mat_ref);
  HOU_EXPECT_CLOSE(quat_ref, r_mat.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vec_ref, r_mat.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(mat_ref, r_mat.get_matrix(), 1.e-6f);
}



TEST_F(test_rotation3, constructor_matrix_small_root_function)
{
  quatf quat_ref(0.707107f, 0.707107f, 0.f, 0.f);
  vec3f vec_ref(2.2214417f, 2.2214417f, 0.f);
  mat3x3f mat_ref(0.f, 1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, -1.f);

  rot3f r_mat(mat_ref);
  HOU_EXPECT_CLOSE(quat_ref, r_mat.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vec_ref, r_mat.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(mat_ref, r_mat.get_matrix(), 1.e-6f);
}



TEST_F(test_rotation3, constructor_matrix_low_precision)
{
  rot3f rot_ref
    = rot3f::x(pi_f / 3.f) * rot3f::z(pi_f / 4.f) * rot3f::y(pi_f / 2.f);
  rot3f rot(rot_ref.get_matrix());
  HOU_EXPECT_FLOAT_CLOSE(rot_ref, rot);
}



TEST_F(test_rotation3, constructor_non_rotation_matrix)
{
  quatf quat_ref(0.119523f, -0.239046f, 0.119523f, 0.956183f);
  vec3f vec_ref(0.2426f, -0.485199f, 0.2426f);
  // clang-format off
  mat3x3f mat_ref
  {
    0.857143f, -0.285714f, -0.428571f,
    0.171429f, 0.942857f, -0.285714f,
    0.485714f, 0.171429f, 0.857143f,
  };
  // clang-format on

  rot3f r_mat(mat3x3f{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f});
  HOU_EXPECT_CLOSE(quat_ref, r_mat.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vec_ref, r_mat.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(mat_ref, r_mat.get_matrix(), 1.e-6f);

  HOU_EXPECT_CLOSE(1.f, norm(r_mat.get_quaternion()), 1.e-6f);
  HOU_EXPECT_CLOSE(mat3x3f::identity(),
    r_mat.get_matrix() * transpose(r_mat.get_matrix()), 1.e-6f);
  HOU_EXPECT_CLOSE(1.f, det(r_mat.get_matrix()), 1.e-6f);
}



TEST_F(test_rotation3, constructor_zero_matrix)
{
  quatf quat_ref(0.f, 0.f, 1.f, 0.f);
  vec3f vec_ref(0.f, 0.f, pi_f);
  mat3x3f mat_ref(-1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f);

  rot3f r_mat(mat3x3f::zero());
  HOU_EXPECT_CLOSE(quat_ref, r_mat.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vec_ref, r_mat.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(mat_ref, r_mat.get_matrix(), 1.e-6f);

  HOU_EXPECT_CLOSE(1.f, norm(r_mat.get_quaternion()), 1.e-6f);
  HOU_EXPECT_CLOSE(mat3x3f::identity(),
    r_mat.get_matrix() * transpose(r_mat.get_matrix()), 1.e-6f);
  HOU_EXPECT_CLOSE(1.f, det(r_mat.get_matrix()), 1.e-6f);
}



TEST_F(test_rotation3, conversion_constructor)
{
  quatd qd(1., 2., 3., 4.);
  rot3d rd(qd);
  quatf qf_ref(rd.get_quaternion());
  rot3f rf(rd);

  HOU_EXPECT_FLOAT_CLOSE(qf_ref, rf.get_quaternion());
}



TEST_F(test_rotation3, comparison_operators)
{
  quatf q1(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  quatf q2(q1);
  quatf q3(quatf::identity());

  rot3f r1(q1);
  rot3f r2(q2);
  rot3f r3(q3);

  EXPECT_TRUE(r1 == r2);
  EXPECT_FALSE(r1 == r3);

  EXPECT_FALSE(r1 != r2);
  EXPECT_TRUE(r1 != r3);
}



TEST_F(test_rotation3, float_comparison)
{
  quatf q1(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  quatf q2(q1);
  quatf q3(0.204124101f, -0.2041241f, 0.4082483f, 0.8660254f);
  quatf q4(0.2041241f, -0.2141241f, 0.4082483f, 0.8660254f);
  quatf q5(0.3041241f, -0.2141241f, 0.4082483f, 0.8660254f);

  rot3f r1(q1);
  rot3f r2(q2);
  rot3f r3(q3);
  rot3f r4(q4);
  rot3f r5(q5);

  EXPECT_TRUE(close(r1, r2));
  EXPECT_TRUE(close(r1, r3));
  EXPECT_FALSE(close(r1, r4));
  EXPECT_FALSE(close(r1, r5));

  EXPECT_TRUE(close(r1, r2, 1.e-2f));
  EXPECT_TRUE(close(r1, r3, 1.e-2f));
  EXPECT_TRUE(close(r1, r4, 1.e-2f));
  EXPECT_FALSE(close(r1, r5, 1.e-2f));
}



TEST_F(test_rotation3, multiplication)
{
  quatf q1(1.f, 2.f, 3.f, 4.f);
  q1.normalize();
  quatf q2(-3.f, 7.f, -1.f, 3.f);
  q2.normalize();
  quatf q_ref = q1 * q2;

  rot3f r1(q1);
  rot3f r2(q2);
  rot3f r_ref(q_ref);
  HOU_EXPECT_FLOAT_CLOSE(r_ref, r1 * r2);
  r1 *= r2;
  HOU_EXPECT_FLOAT_CLOSE(r_ref, r1);
}



TEST_F(test_rotation3, inversion)
{
  quatf q(1.f, 2.f, 3.f, 4.f);
  q.normalize();
  quatf q_ref = inverse(q);

  rot3f r(q);
  rot3f r_ref(q_ref);
  HOU_EXPECT_FLOAT_CLOSE(r_ref, inverse(r));
  r.invert();
  HOU_EXPECT_FLOAT_CLOSE(r_ref, r);
}



TEST_F(test_rotation3, output_stream_operator)
{
  quatf quat_ref(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  rot3f r(quat_ref);
  HOU_EXPECT_OUTPUT("(0.204124,-0.204124,0.408248,0.866025)", r);
}



TEST_P(test_rotation3_param_f, rotationX)
{
  rot3f r = rot3f::x(GetParam());
  quatf q_ref(std::sin(GetParam() / 2.f), 0.f, 0.f, std::cos(GetParam() / 2.f));
  vec3f v_ref(GetParam(), 0.f, 0.f);
  // clang-format off
  mat3x3f m_ref =
  {
    1.f, 0.f, 0.f,
    0.f, std::cos(GetParam()), -std::sin(GetParam()),
    0.f, std::sin(GetParam()), std::cos(GetParam()),
  };
  // clang-format on
  HOU_EXPECT_CLOSE(q_ref, r.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(v_ref, r.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(m_ref, r.get_matrix(), 1.e-6f);
}



TEST_P(test_rotation3_param_f, rotationY)
{
  rot3f r = rot3f::y(GetParam());
  quatf q_ref(0.f, std::sin(GetParam() / 2.f), 0.f, std::cos(GetParam() / 2.f));
  vec3f v_ref(0.f, GetParam(), 0.f);
  // clang-format off
  mat3x3f m_ref =
  {
    std::cos(GetParam()), 0.f, std::sin(GetParam()),
    0.f, 1.f, 0.f,
    -std::sin(GetParam()), 0.f, std::cos(GetParam()),
  };
  // clang-format on
  HOU_EXPECT_CLOSE(q_ref, r.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(v_ref, r.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(m_ref, r.get_matrix(), 1.e-6f);
}



TEST_P(test_rotation3_param_f, rotationZ)
{
  rot3f r = rot3f::z(GetParam());
  quatf q_ref(0.f, 0.f, std::sin(GetParam() / 2.f), std::cos(GetParam() / 2.f));
  vec3f v_ref(0.f, 0.f, GetParam());
  // clang-format off
  mat3x3f m_ref =
  {
    std::cos(GetParam()), -std::sin(GetParam()), 0.f,
    std::sin(GetParam()), std::cos(GetParam()), 0.f,
    0.f, 0.f, 1.f,
  };
  // clang-format on
  HOU_EXPECT_CLOSE(q_ref, r.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(v_ref, r.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(m_ref, r.get_matrix(), 1.e-6f);
}



INSTANTIATE_TEST_CASE_P(test_rotation3_param_f, test_rotation3_param_f,
  Values(pi_f / 2.f, pi_f / 6.f), );
