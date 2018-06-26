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



non_negative<float> get_doppler_factor()
{
  return static_cast<float>(al::get_doppler_factor());
}



void set_doppler_factor(non_negative<float> dopplerFactor)
{
  al::set_doppler_factor(static_cast<ALfloat>(dopplerFactor));
}



positive<float> get_speed_of_sound()
{
  return static_cast<float>(al::get_speed_of_sound());
}



void set_speed_of_sound(positive<float> speedOfSound)
{
  al::set_speed_of_sound(static_cast<ALfloat>(speedOfSound));
}

}  // namespace sound_model

}  // namespace hou
