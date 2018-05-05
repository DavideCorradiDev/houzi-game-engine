#include "hou/aud/sound_model.hpp"

#include "hou/al/al_state.hpp"

#include "hou/cor/assertions.hpp"



namespace hou
{

namespace sound_model
{

sound_distance_model get_distance_model()
{
  return sound_distance_model(al::get_distance_model());
}



void set_distance_model(sound_distance_model model)
{
  al::set_distance_model(static_cast<ALenum>(model));
}



float get_doppler_factor()
{
  return static_cast<float>(al::get_doppler_factor());
}



void set_doppler_factor(float dopplerFactor)
{
  HOU_PRECOND(dopplerFactor >= 0.f);
  al::set_doppler_factor(static_cast<ALfloat>(dopplerFactor));
}



float get_speed_of_sound()
{
  return static_cast<float>(al::get_speed_of_sound());
}



void set_speed_of_sound(float speedOfSound)
{
  HOU_PRECOND(speedOfSound > 0.f);
  al::set_speed_of_sound(static_cast<ALfloat>(speedOfSound));
}

}  // namespace sound_model

}  // namespace hou
