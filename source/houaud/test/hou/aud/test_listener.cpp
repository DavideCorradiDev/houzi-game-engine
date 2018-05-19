// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/test_aud_base_test_specific_context.hpp"

#include "hou/aud/listener.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/matrix.hpp"
#include "hou/mth/rotation3.hpp"

using namespace hou;



namespace
{

class test_listener : public test_aud_base_test_specific_context
{};

class test_listener_death_test : public test_listener
{};

}  // namespace



TEST_F(test_listener, gain)
{
  EXPECT_FLOAT_EQ(1.f, listener::get_gain());
  listener::set_gain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, listener::get_gain());
}



TEST_F(test_listener_death_test, invalid_gain)
{
  EXPECT_PRECOND_ERROR(listener::set_gain(-1.f));
}



TEST_F(test_listener, position)
{
  EXPECT_FLOAT_CLOSE(vec3f::zero(), listener::get_position());
  listener::set_position(vec3f(1.f, 2.f, 3.f));
  EXPECT_FLOAT_CLOSE(vec3f(1.f, 2.f, 3.f), listener::get_position());
}



TEST_F(test_listener, velocity)
{
  EXPECT_FLOAT_CLOSE(vec3f::zero(), listener::get_velocity());
  listener::set_velocity(vec3f(1.f, 2.f, 3.f));
  EXPECT_FLOAT_CLOSE(vec3f(1.f, 2.f, 3.f), listener::get_velocity());
}



TEST_F(test_listener, orientation)
{
  EXPECT_FLOAT_CLOSE(rot3f::identity(), listener::get_orientation());

  rot3f or_ref
    = rot3f::x(pi_f / 3.f) * rot3f::z(pi_f / 4.f) * rot3f::y(pi_f / 2.f);
  listener::set_orientation(or_ref);
  EXPECT_FLOAT_CLOSE(or_ref, listener::get_orientation());
}
