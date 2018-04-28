#include "hou/aud/SoundModel.hpp"

#include "hou/al/AlState.hpp"

#include "hou/cor/error.hpp"



namespace hou
{

namespace SoundModel
{

SoundDistanceModel getDistanceModel()
{
  return SoundDistanceModel(al::getDistanceModel());
}



void setDistanceModel(SoundDistanceModel model)
{
  al::setDistanceModel(static_cast<ALenum>(model));
}



float getDopplerFactor()
{
  return static_cast<float>(al::getDopplerFactor());
}



void setDopplerFactor(float dopplerFactor)
{
  HOU_EXPECT(dopplerFactor >= 0.f);
  al::setDopplerFactor(static_cast<ALfloat>(dopplerFactor));
}



float getSpeedOfSound()
{
  return static_cast<float>(al::getSpeedOfSound());
}



void setSpeedOfSound(float speedOfSound)
{
  HOU_EXPECT(speedOfSound > 0.f);
  al::setSpeedOfSound(static_cast<ALfloat>(speedOfSound));
}

}  // namespace SoundModel

}  // namespace hou
