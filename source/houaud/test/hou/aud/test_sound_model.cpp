// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/test_aud_base_test_specific_context.hpp"

#include "hou/aud/sound_model.hpp"

using namespace hou;



namespace
{

class test_sound_model : public test_aud_base_test_specific_context
{};

class test_sound_model_death_test : public test_sound_model
{};

}  // namespace



TEST_F(test_sound_model, sound_distance_model)
{
  EXPECT_EQ(sound_distance_model::inverse_distance_clamped,
    sound_model::get_distance_model());

  std::vector<sound_distance_model> distance_models{
    sound_distance_model::inverse_distance,
    sound_distance_model::inverse_distance_clamped,
    sound_distance_model::linear_distance,
    sound_distance_model::linear_distance_clamped,
    sound_distance_model::exponent_distance,
    sound_distance_model::exponent_distance_clamped,
  };

  for(auto dm : distance_models)
  {
    sound_model::set_distance_model(dm);
    EXPECT_EQ(dm, sound_model::get_distance_model());
  }
}



TEST_F(test_sound_model, doppler_factor)
{
  EXPECT_FLOAT_EQ(1.f, sound_model::get_doppler_factor());

  std::vector<float> doppler_factor_values{0.f, 0.5f, 1.f, 3.f, 10.f};

  for(auto df : doppler_factor_values)
  {
    sound_model::set_doppler_factor(df);
    EXPECT_FLOAT_EQ(df, sound_model::get_doppler_factor());
  }
}



TEST_F(test_sound_model, doppler_factor_error_negative_value)
{
  HOU_EXPECT_PRECONDITION(sound_model::set_doppler_factor(-1.f));
}



TEST_F(test_sound_model, speed_of_sound)
{
  EXPECT_FLOAT_EQ(343.3f, sound_model::get_speed_of_sound());

  std::vector<float> speed_of_sound_values{0.5f, 1.f, 3.f, 10.f, 343.3f, 700.f};

  for(auto df : speed_of_sound_values)
  {
    sound_model::set_speed_of_sound(df);
    EXPECT_FLOAT_EQ(df, sound_model::get_speed_of_sound());
  }
}



TEST_F(test_sound_model, speed_of_sound_error_negative_or_null_value)
{
  HOU_EXPECT_PRECONDITION(sound_model::set_speed_of_sound(0.f));
  HOU_EXPECT_PRECONDITION(sound_model::set_speed_of_sound(-1.f));
}
