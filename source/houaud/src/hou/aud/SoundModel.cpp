#include "hou/aud/SoundModel.hpp"

#include "hou/al/al_state.hpp"

#include "hou/cor/error.hpp"



namespace hou
{

namespace SoundModel
{

SoundDistanceModel get_distance_model()
{
  return SoundDistanceModel(al::get_distance_model());
}



void set_distance_model(SoundDistanceModel model)
{
  al::set_distance_model(static_cast<ALenum>(model));
}



float get_doppler_factor()
{
  return static_cast<float>(al::get_doppler_factor());
}



void set_doppler_factor(float dopplerFactor)
{
  HOU_EXPECT(dopplerFactor >= 0.f);
  al::set_doppler_factor(static_cast<ALfloat>(dopplerFactor));
}



float get_speed_of_sound()
{
  return static_cast<float>(al::get_speed_of_sound());
}



void set_speed_of_sound(float speedOfSound)
{
  HOU_EXPECT(speedOfSound > 0.f);
  al::set_speed_of_sound(static_cast<ALfloat>(speedOfSound));
}

}  // namespace SoundModel

}  // namespace hou
